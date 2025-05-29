// loadword.cpp

#include "../back_head/loadword.h"

// 辅助函数：从 JSON 对象中提取音标信息（过滤空音标）
QVector<Phonetic> Wordloader::extractPhonetics(const QJsonObject& phoneticsObj) {
    QVector<Phonetic> phonetics;
    for (const auto& key : {"uk", "us"}) {
        if (phoneticsObj.contains(key)) {
            QJsonObject phoneticObj = phoneticsObj[key].toObject();
            QString text = phoneticObj["text"].toString().trimmed();
            QString audio = phoneticObj["audio"].toString().trimmed();
            if (!text.isEmpty()) { // 过滤空音标文本
                Phonetic phonetic;
                phonetic.text = text;
                phonetic.audio = audio.isEmpty() ? "N/A" : audio; // 音频为空时设为默认值
                phonetics.append(phonetic);
            }
        }
    }
    return phonetics;
}

// 辅助函数：从 JSON 对象中提取释义信息（处理空定义和空例句）
QMap<QString, QVector<Definition>> Wordloader::extractMeanings(const QJsonObject& wordInfo) {
    QMap<QString, QVector<Definition>> meanings;
    QString pos = wordInfo["pos"].toString().trimmed();
    if (pos.isEmpty()) {
        pos = "unknown"; // 设置更合理的默认词性
    }

    QVector<Definition> definitions;
    QJsonObject definitionObj = wordInfo["definition"].toObject();
    QString englishDef = definitionObj["english"].toString().trimmed();

    if (!englishDef.isEmpty()) { // 仅当定义存在时处理
        // 创建基础定义（无例句）
        Definition baseDef(englishDef);

        // 处理例句
        QJsonArray examplesArray = wordInfo["examples"].toArray();
        for (const auto& exampleValue : examplesArray) {
            QJsonObject exampleObj = exampleValue.toObject();
            QString englishExample = exampleObj["english"].toString().trimmed();

            if (!englishExample.isEmpty()) { // 过滤空例句
                Definition newDef(baseDef); // 复制基础定义
                newDef.example = englishExample; // 添加例句
                definitions.append(newDef);
            }
        }

        // 如果没有例句，添加基础定义（仅定义）
        if (definitions.isEmpty()) {
            definitions.append(baseDef);
        }
    } else {
        qDebug() << "警告：单词定义为空，跳过释义";
        return meanings; // 跳过无定义的单词
    }

    meanings[pos] = definitions;
    return meanings;
}

// 从 JSON 文件导入单词到数据库
bool Wordloader::importWordsFromJson(const QString& jsonFilePath, const QString& dbName) {
    WordDatabase db;
    if (!db.NewDatabase(dbName)) {
        qDebug() << "无法创建新的数据库";
        return false;
    }

    QFile file(jsonFilePath);
    if (!file.exists()) {
        qDebug() << "文件不存在:" << jsonFilePath;
        return false;
    }

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "打开文件失败:" << file.errorString();
        return false;
    }

    // 直接读取文件内容到QByteArray
    QByteArray jsonData = file.readAll();
    file.close();

    // 使用QString::fromUtf8()替代QTextStream和QTextCodec
    QString jsonString = QString::fromUtf8(jsonData);

    // 解析JSON
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8(), &parseError);
    if (jsonDoc.isNull()) {
        qDebug() << "JSON解析失败，错误类型:" << parseError.error
                 << ", 错误信息:" << parseError.errorString();
        return false;
    }

    QJsonObject jsonObj = jsonDoc.object();
    int successCount = 0, failCount = 0;

    for (const auto& key : jsonObj.keys()) {
        QJsonObject wordInfo = jsonObj[key].toObject();
        QString wordText = wordInfo["word"].toString().trimmed();

        if (wordText.isEmpty()) {
            qDebug() << "跳过空单词条目";
            continue;
        }

        Word word(wordText);

        // 提取音标（过滤空音标）
        word.phonetics = extractPhonetics(wordInfo["phonetics"].toObject());
        if (word.phonetics.isEmpty()) {
            qDebug() << "警告：单词" << wordText << "无有效音标，使用默认值";
            Phonetic defaultPhonetic;
            defaultPhonetic.text = "N/A";
            word.phonetics.append(defaultPhonetic);
        }

        // 提取释义（处理空定义和空例句）
        word.meanings = extractMeanings(wordInfo);
        if (word.meanings.isEmpty()) {
            qDebug() << "警告：单词" << wordText << "无有效释义，跳过导入";
            failCount++;
            continue;
        }

        // 插入数据库
        if (db.addWord(word)) {
            successCount++;
        } else {
            qDebug() << "无法插入单词:" << wordText;
            failCount++;
        }
    }

    qDebug() << "导入完成：成功" << successCount << "条，失败" << failCount << "条";
    return successCount > 0;
}

// 启发式过滤无效行
bool Wordloader::isInvalidLine(const QString& line) {
    QString trimmedLine = line.trimmed();

    // 过滤纯数字、纯符号或空行
    if (trimmedLine.isEmpty() || !trimmedLine.contains(QRegularExpression("[a-zA-Z]")))
        return true;

    // 过滤单行字母（如"A", "B", "C"）但保留单词行
    if (trimmedLine.length() == 1 && trimmedLine.at(0).isLetter())
        return true;

    // // 过滤包含大量中文的标题行
    // int chineseCount = 0;
    // for (QChar c : trimmedLine) {
    //     if (c.unicode() >= 0x4E00 && c.unicode() <= 0x9FFF)
    //         chineseCount++;
    // }
    // if (chineseCount > 3)  // 超过3个中文字符视为标题行
    //     return true;

    // 过滤纯符号行
    if (trimmedLine.contains(QRegularExpression("^[\\s\\(\\)\\[\\]\\-]+$")))
        return true;

    return false;
}

// 提取单词的正则表达式（兼容多种格式）
QStringList Wordloader::extractWords(const QString& text) {
    QStringList words;
    QStringList lines = text.split('\n', Qt::SkipEmptyParts);

    // 进一步改进的正则表达式：
    // 1. 匹配以字母开头的单词
    // 2. 允许单词后面有括号（如"a (an)"）
    // 3. 允许单词后面有逗号和词性（如"abandon,v."）
    // 4. 忽略方括号内的音标和后面的内容
    // 5. 更灵活地处理标点符号和分隔符
    QRegularExpression re("^([a-zA-Z-]+)(?:\\s+\\([a-zA-Z-]+\\))?(?:[\\s,;./]+[a-z./]+)?(?:\\s+|\\[|$)");

    for (const QString& line : lines) {
        QString trimmedLine = line.trimmed();

        // 过滤无效行
        if (isInvalidLine(trimmedLine))
            continue;

        // 匹配单词
        QRegularExpressionMatch match = re.match(trimmedLine);
        if (match.hasMatch()) {
            QString word = match.captured(1);
            words.append(word);
        }
    }

    return words;
}


bool Wordloader::importWordFromTXT(const QString& TXTFilePath, const QString& dbName,const QString& search_dbname,bool use_API)
{
    WordDatabase db;
    if (!db.NewDatabase(dbName)) {
        qDebug() << "无法创建新的数据库";
        return false;
    }

    QFile file(TXTFilePath);
    if (!file.exists()) {
        qDebug() << "文件不存在:" << TXTFilePath;
        return false;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "打开文件失败:" << file.errorString();
        return false;
    }

    // 直接读取文件内容到QString，自动处理UTF-8编码
    QString content = QString::fromUtf8(file.readAll());
    file.close();

    bool local=true;
    WordDatabase search;
    if(!search.initDatabase(search_dbname))
    {
        qDebug() << "无法加载本地词典";
        local=false;
    }

    int importedWords = 0, totalWords = 0;

    // 提取单词
    QStringList words = extractWords(content);
    qDebug() << "成功提取" << words.size() << "个单词";

    for (const QString& line : words)
    {
        QString word = line.trimmed();
        if (!word.isEmpty()) {
            totalWords++;
            if(local)
            {
                qInfo()<<"尝试从本地数据库查找/n";
                QVector<Word> search_word=search.getWordsByName(word);
                if(!search_word.isEmpty())
                {
                    Word newWord=search_word[0];
                    newWord.difficulty = 3; // 默认难度
                    newWord.reviewCount = 0; // 默认复习次数
                    // newWord.lastReviewed = QDateTime::currentDateTime(); // 当前时间

                    // 插入数据库
                    if (db.addWord(newWord)) {
                        importedWords++;
                        continue; // 成功添加后跳过
                    } else {
                        qDebug() << "无法插入单词:" << word;
                    }
                }
            }

            if(use_API)
            {
                DictionaryAPI api;
                qInfo()<<"调用网络api进行查找/n";
                Word newWord=api.getWordInfo(word);
                newWord.difficulty = 3; // 默认难度
                newWord.reviewCount = 0; // 默认复习次数
                //newWord.lastReviewed = QDateTime::currentDateTime(); // 当前时间
                // 给本地也插入一份，避免总是调用网络api
                if (search.addWord(newWord)) {
                    qDebug()<<"成功补充信息到本地数据库";
                } else {
                    qDebug() << "无法插入单词:" << word;
                }
                // 插入数据库
                if (db.addWord(newWord)) {
                    importedWords++;
                    continue; // 成功添加后跳过
                } else {
                    qDebug() << "无法插入单词:" << word;
                }
            }

        }
    }

    qInfo() << "导入完成：成功" << importedWords << "条，失败" << totalWords-importedWords    << "条";
    return importedWords > 0;
}
