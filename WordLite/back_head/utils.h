#ifndef UTILS_H
#define UTILS_H

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include <QVector>
#include <QDateTime>

class Word // 存储单词的基本信息，包括单词、发音、释义、例句等，同时记录学习相关信息如最后复习时间、复习次数和难度。
{
public:
    int id;
    QString word;
    QString pronunciation;
    QString meaning;
    QString example;// 例句
    QDateTime lastReviewed=QDateTime::currentDateTime(); // 初始化为添加时的时间
    int reviewCount=0; // 复习次数
    int difficulty=0; // 1-5，1表示最简单，5表示最难（或者是用户的掌握程度）

    Word(QString word,QString meaning="none"):word(word),meaning(meaning){}
    Word(){}
    // 成员外部接口
    int g_id()const{return id;}
    QString g_word()const{return word;}
    QString g_prounuciation()const{return pronunciation;}
    QString g_meaning()const{return meaning;}
    QString g_example()const{return example;}
    QDateTime g_lastReviewed()const{return lastReviewed;}
    int g_reviewCount()const{return reviewCount;}
    int g_difficulty()const{return difficulty;}
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
