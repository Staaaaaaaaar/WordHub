// dictionaryapi.cpp
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
    }

    // 设置发音
    if (firstEntry.contains("phonetics") && firstEntry["phonetics"].isArray()) {
        QJsonArray phonetics = firstEntry["phonetics"].toArray();
        for (const QJsonValue& phonetic : phonetics) {
            QJsonObject phonObj = phonetic.toObject();
            if (phonObj.contains("text") && phonObj["text"].isString()) {
                newWord.pronunciation = phonObj["text"].toString();
                break;
            }
        }
    }

    // 设置释义
    QStringList allMeanings;
    if (firstEntry.contains("meanings") && firstEntry["meanings"].isArray()) {
        QJsonArray meanings = firstEntry["meanings"].toArray();
        for (const QJsonValue& meaning : meanings) {
            QJsonObject meaningObj = meaning.toObject();
            QString partOfSpeech = "";
            if (meaningObj.contains("partOfSpeech") && meaningObj["partOfSpeech"].isString()) {
                partOfSpeech = meaningObj["partOfSpeech"].toString() + ". ";
            }

            if (meaningObj.contains("definitions") && meaningObj["definitions"].isArray()) {
                QJsonArray definitions = meaningObj["definitions"].toArray();
                for (const QJsonValue& definition : definitions) {
                    QJsonObject defObj = definition.toObject();
                    if (defObj.contains("definition") && defObj["definition"].isString()) {
                        allMeanings.append(partOfSpeech + defObj["definition"].toString());
                    }
                }
            }
        }
    }
    newWord.meaning = allMeanings.join("\n");

    // 设置例句
    if (firstEntry.contains("meanings") && firstEntry["meanings"].isArray()) {
        QJsonArray meanings = firstEntry["meanings"].toArray();
        for (const QJsonValue& meaning : meanings) {
            QJsonObject meaningObj = meaning.toObject();
            if (meaningObj.contains("definitions") && meaningObj["definitions"].isArray()) {
                QJsonArray definitions = meaningObj["definitions"].toArray();
                for (const QJsonValue& definition : definitions) {
                    QJsonObject defObj = definition.toObject();
                    if (defObj.contains("example") && defObj["example"].isString()) {
                        newWord.example = defObj["example"].toString();
                        break;
                    }
                }
                if (!newWord.example.isEmpty()) break;
            }
        }
    }

    // 初始化学习相关信息
    newWord.lastReviewed = QDateTime::currentDateTime();
    newWord.reviewCount = 0;
    newWord.difficulty = 0;

    return newWord;
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

            if (!currentWord.g_word().isEmpty()) {
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
