// loadword.cpp

#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDebug>
#include <QTextStream> // 确保已有

#include <QJsonParseError> // 若之前未包含

#include "../back_head/database.h"
#include "../back_head/utils.h"

// 辅助函数：从 JSON 对象中提取音标信息（过滤空音标）
QVector<Phonetic> extractPhonetics(const QJsonObject& phoneticsObj) {
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
QMap<QString, QVector<Definition>> extractMeanings(const QJsonObject& wordInfo) {
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
bool importWordsFromJson(const QString& jsonFilePath, const QString& dbName) {
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
