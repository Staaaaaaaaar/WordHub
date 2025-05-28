#ifndef LOADWORD_H
#define LOADWORD_H

#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDebug>
#include <QTextStream> // 确保已有
#include <QJsonParseError> // 若之前未包含
#include <QRegularExpression>
#include "./database.h"
#include "../API/dictionaryapi.h"
#include "./utils.h"

class Wordloader
{
public:
    Wordloader(){}
    ~Wordloader(){}
    // 从 JSON 词典文件导入单词到数据库
    bool importWordsFromJson(const QString& jsonFilePath, const QString& dbName);
    // 从txt文件导入单词到数据库
    // 先调用本地的牛津数据库尽心索引，如果没有则调用网络词典api获取信息(需要将use_API设置为true)
    bool importWordFromTXT(const QString& TXTFilePath, const QString& dbName,const QString& search_dbname,bool use_API=false);

private:
    QVector<Phonetic> extractPhonetics(const QJsonObject& phoneticsObj); // 辅助函数：从 JSON 对象中提取音标信息（过滤空音标）
    QMap<QString, QVector<Definition>> extractMeanings(const QJsonObject& wordInfo);// 辅助函数：从 JSON 对象中提取释义信息（处理空定义和空例句）

    QStringList extractWords(const QString& text); // 正则表达式提取单词
    bool isInvalidLine(const QString& line);// 启发式过滤无效行

};

#endif // LOADWORD_H
