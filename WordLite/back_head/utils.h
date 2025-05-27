#ifndef UTILS_H
#define UTILS_H

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include <QVector>
#include <QDateTime>
#include <QMap>

// 音标和发音结构体
struct Phonetic {
    QString text;
    QString audio;
};

// 定义结构体来存储每个释义的信息
struct Definition {
    QString definition;
    QString example;
    QVector<QString> synonyms;
    QVector<QString> antonyms;
};

class Word // 存储单词的基本信息，包括单词、发音、释义、例句等，同时记录学习相关信息如最后复习时间、复习次数和难度。
{
public:
    int id;
    QString word;
    QVector<Phonetic> phonetics;
    QMap<QString, QVector<Definition>> meanings;
    QDateTime lastReviewed=QDateTime::currentDateTime(); // 初始化为添加时的时间
    int reviewCount=0; // 复习次数
    int difficulty=0; // 1-5，1表示最简单，5表示最难（或者是用户的掌握程度）

    Word(QString word,QString meaning="none"):word(word){}
    Word(){}
};

QDebug operator<<(QDebug o,const Word& w);

class Category // 存储单词的分类信息，如基础词汇、学术词汇等。
{
public:
    QString name;
    QString description;
    int id;
};

QDebug operator<<(QDebug o,const Category c);

class LearningRecord // 学习记录
{
public:
    int id;
    int wordId;
    int userId;
    QDateTime timestamp;
    bool correct;
    int difficulty;
};

#endif // UTILS_H
