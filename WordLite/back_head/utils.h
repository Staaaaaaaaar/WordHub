#ifndef UTILS_H
#define UTILS_H

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include <QVector>
#include <QDateTime>
#include <QMap>

/**
 * @brief 音标结构体，存储单词的音标和发音信息
 */
struct Phonetic {
    QString text; // 音标文本，例如："/ˈwɜːd/"
    QString audio; // 发音音频URL，例如："https://example.com/audio/word.mp3"
};

/**
 * @brief 单词释义结构体，包含释义内容、例句、同义词和反义词
 */
struct Definition {
    Definition(){}
    Definition(QString dedinition):definition(dedinition){}
    QString definition; // 单词释义内容
    QString example; // 例句
    QVector<QString> synonyms; // 同义词列表
    QVector<QString> antonyms; // 反义词列表
};

/**
 * @brief 单词结构体，存储单词的完整信息
 *
 * 包含单词基本信息、音标、按词性分类的释义以及学习记录
 */
class Word {
public:
    int id; // 单词ID，数据库中的唯一标识
    QString word; // 单词文本，例如："hello"
    QVector<Phonetic> phonetics; // 单词的音标列表，支持多音标（如英式、美式）
    QMap<QString, QVector<Definition>> meanings; // 按词性分类的释义，key为词性（如"n."、"v."）
    QDateTime lastReviewed; // 最后复习时间，用于间隔重复算法
    int reviewCount; // 复习次数，用于计算复习间隔
    int difficulty; // 难度等级（1-5），1表示简单，5表示困难

    Word(QString word = ""): word(word), reviewCount(0), difficulty(3) {}


    QString g_word()const{return word;}
    QVector<Phonetic> g_phonrtics()const{return phonetics;}
    int g_id()const{return id;}
    QMap<QString, QVector<Definition>> g_meanings()const{return meanings;}
    QDateTime g_lastReviewed()const{return lastReviewed;}
    int g_reviewCount()const{return reviewCount;}
    int g_difficulty()const{return difficulty;}

    QString getoneMeaning();

    bool isEmpty(){return word.isEmpty();}
};

// 输出运算符重载，方便调试
QDebug operator<<(QDebug o, const Word& w);

/**
 * @brief 单词分类结构体
 */
class Category {
public:
    int id; // 分类ID
    QString name; // 分类名称，例如："常用词汇"
    QString description; // 分类描述
};

/**
 * @brief 学习记录结构体
 */
class LearningRecord {
public:
    int id; // 记录ID
    int wordId; // 关联的单词ID
    int userId; // 关联的用户ID
    QDateTime timestamp; // 学习时间戳
    bool correct; // 是否正确回答
    int difficulty; // 标记的难度
};


#endif // UTILS_H
