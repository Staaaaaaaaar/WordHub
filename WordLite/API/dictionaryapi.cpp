#include "dictionaryapi.h"

DictionaryAPI::DictionaryAPI(QObject *parent)
    : QObject(parent), requestFinished(false)
{
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &DictionaryAPI::onReplyFinished);
}

Word DictionaryAPI::getWordInfo(const QString& word)
{
    // 重置状态
    requestFinished = false;
    currentWord = Word();
    errorMessage.clear();

    // 构建请求
    QString url = QString("https://api.dictionaryapi.dev/api/v2/entries/en/%1").arg(word);
    QNetworkRequest request{QUrl(url)};
    request.setHeader(QNetworkRequest::UserAgentHeader, "VocabularyLearningApp/1.0");

    // 发送请求
    manager->get(request);

    // 创建事件循环，阻塞直到请求完成
    QEventLoop loop;
    QTimer timer;
    timer.setSingleShot(true);

    // 连接信号，当请求完成或超时退出事件循环
    connect(this, &DictionaryAPI::wordInfoReceived, &loop, &QEventLoop::quit);
    connect(this, &DictionaryAPI::errorOccurred, &loop, &QEventLoop::quit);
    connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);

    // 设置超时时间（例如10秒）
    timer.start(10000);

    // 阻塞当前线程，直到事件循环退出
    loop.exec();

    // 检查是否超时
    if (!requestFinished) {
        errorMessage = "Request timed out";
        emit errorOccurred(errorMessage);
    }

    return currentWord;
}

void DictionaryAPI::getWordInfoAsync(const QString& word)
{
    // 异步版本：不阻塞线程，通过信号返回结果
    QString url = QString("https://api.dictionaryapi.dev/api/v2/entries/en/%1").arg(word);
    QNetworkRequest request{QUrl(url)};
    request.setHeader(QNetworkRequest::UserAgentHeader, "VocabularyLearningApp/1.0");
    manager->get(request);
}

Word DictionaryAPI::createWordFromApiResult(const QJsonArray& apiResult)
{
    Word newWord;

    // 检查 API 结果是否有效
    if (apiResult.isEmpty()) {
        return newWord;
    }

    // 获取第一个词条
    QJsonObject firstEntry = apiResult[0].toObject();

    // 设置单词
    if (firstEntry.contains("word") && firstEntry["word"].isString()) {
        newWord.word = firstEntry["word"].toString();
    } else {
        return newWord; // 如果没有单词，返回空对象
    }

    // 解析音标信息
    if (firstEntry.contains("phonetics") && firstEntry["phonetics"].isArray()) {
        parsePhonetics(firstEntry["phonetics"].toArray(), newWord);
    }

    // 解析释义信息
    if (firstEntry.contains("meanings") && firstEntry["meanings"].isArray()) {
        parseMeanings(firstEntry["meanings"].toArray(), newWord);
    }

    // 初始化学习相关信息
    newWord.lastReviewed = QDateTime::currentDateTime();
    newWord.reviewCount = 0;
    newWord.difficulty = 0;

    return newWord;
}

void DictionaryAPI::parsePhonetics(const QJsonArray& phoneticsArray, Word& word)
{
    for (const QJsonValue& phoneticValue : phoneticsArray) {
        if (!phoneticValue.isObject()) continue;

        QJsonObject phoneticObj = phoneticValue.toObject();
        Phonetic phonetic;

        // 提取音标文本
        if (phoneticObj.contains("text") && phoneticObj["text"].isString()) {
            phonetic.text = phoneticObj["text"].toString();
        }

        // 提取发音音频
        if (phoneticObj.contains("audio") && phoneticObj["audio"].isString()) {
            QString audioUrl = phoneticObj["audio"].toString();
            // 确保URL有效（如果是相对URL，添加协议前缀）
            if (!audioUrl.isEmpty() && !audioUrl.startsWith("http")) {
                audioUrl = "https:" + audioUrl;
            }
            phonetic.audio = audioUrl;
        }

        // 仅添加有效的音标信息
        if (!phonetic.text.isEmpty() || !phonetic.audio.isEmpty()) {
            word.phonetics.append(phonetic);
        }
    }
}

void DictionaryAPI::parseMeanings(const QJsonArray& meaningsArray, Word& word)
{
    for (const QJsonValue& meaningValue : meaningsArray) {
        if (!meaningValue.isObject()) continue;

        QJsonObject meaningObj = meaningValue.toObject();

        // 获取词性
        QString partOfSpeech = "";
        if (meaningObj.contains("partOfSpeech") && meaningObj["partOfSpeech"].isString()) {
            partOfSpeech = meaningObj["partOfSpeech"].toString();
        }

        if (partOfSpeech.isEmpty()) continue;

        // 解析该词性下的所有释义
        if (meaningObj.contains("definitions") && meaningObj["definitions"].isArray()) {
            QJsonArray definitionsArray = meaningObj["definitions"].toArray();

            for (const QJsonValue& definitionValue : definitionsArray) {
                if (!definitionValue.isObject()) continue;

                QJsonObject definitionObj = definitionValue.toObject();
                Definition definition;

                // 提取释义内容
                if (definitionObj.contains("definition") && definitionObj["definition"].isString()) {
                    definition.definition = definitionObj["definition"].toString();
                }

                // 提取例句
                if (definitionObj.contains("example") && definitionObj["example"].isString()) {
                    definition.example = definitionObj["example"].toString();
                }

                // 提取同义词
                if (definitionObj.contains("synonyms") && definitionObj["synonyms"].isArray()) {
                    QJsonArray synonymsArray = definitionObj["synonyms"].toArray();
                    for (const QJsonValue& synonymValue : synonymsArray) {
                        if (synonymValue.isString()) {
                            definition.synonyms.append(synonymValue.toString());
                        }
                    }
                }

                // 提取反义词
                if (definitionObj.contains("antonyms") && definitionObj["antonyms"].isArray()) {
                    QJsonArray antonymsArray = definitionObj["antonyms"].toArray();
                    for (const QJsonValue& antonymValue : antonymsArray) {
                        if (antonymValue.isString()) {
                            definition.antonyms.append(antonymValue.toString());
                        }
                    }
                }

                // 仅添加有效的释义
                if (!definition.definition.isEmpty()) {
                    word.meanings[partOfSpeech].append(definition);
                }
            }
        }
    }
}

void DictionaryAPI::onReplyFinished(QNetworkReply* reply)
{
    requestFinished = true;

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);

        if (!doc.isNull() && doc.isArray()) {
            QJsonArray resultArray = doc.array();
            currentWord = createWordFromApiResult(resultArray);

            if (!currentWord.word.isEmpty()) {
                emit wordInfoReceived(currentWord);
            } else {
                errorMessage = "Failed to parse word information";
                emit errorOccurred(errorMessage);
            }
        } else {
            errorMessage = "Invalid response format";
            emit errorOccurred(errorMessage);
        }
    } else {
        errorMessage = reply->errorString();
        emit errorOccurred(errorMessage);
    }

    reply->deleteLater();
}
