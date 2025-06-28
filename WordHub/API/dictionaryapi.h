#ifndef DICTIONARYAPI_H
#define DICTIONARYAPI_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QEventLoop>
#include <QTimer>
#include "../back_head/utils.h"

class DictionaryAPI : public QObject
{
    Q_OBJECT
public:
    explicit DictionaryAPI(QObject *parent = nullptr);

    // 同步方法：返回Word对象
    Word getWordInfo(const QString& word);

    // 异步方法：通过信号返回结果
    void getWordInfoAsync(const QString& word);

signals:
    void wordInfoReceived(const Word& word);
    void errorOccurred(const QString& errorMessage);

private slots:
    void onReplyFinished(QNetworkReply* reply);

private:
    QNetworkAccessManager* manager;
    Word currentWord;  // 存储当前查询的单词
    bool requestFinished;  // 请求是否完成的标志
    QString errorMessage;  // 错误信息

    /**
     * @brief 从API返回的JSON数组创建Word对象
     * @param apiResult API返回的JSON数组
     * @return 解析后的Word对象
     */
    Word createWordFromApiResult(const QJsonArray& apiResult);

    /**
     * @brief 解析音标信息
     * @param phoneticsArray 音标JSON数组
     * @param word 要填充的Word对象
     */
    void parsePhonetics(const QJsonArray& phoneticsArray, Word& word);

    /**
     * @brief 解析释义信息
     * @param meaningsArray 释义JSON数组
     * @param word 要填充的Word对象
     */
    void parseMeanings(const QJsonArray& meaningsArray, Word& word);
};

#endif // DICTIONARYAPI_H
