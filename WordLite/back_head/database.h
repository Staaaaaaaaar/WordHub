#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
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
    QString example;
    QDateTime lastReviewed=QDateTime::currentDateTime(); // 初始化为添加时的时间
    int reviewCount=0;
    int difficulty=0; // 1-5，1表示最简单，5表示最难

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

class WordDatabase : public QObject
{
    Q_OBJECT
public:

    explicit WordDatabase(const QString &connectionName = "defaultConnection");

    ~WordDatabase();

    bool isOpen() const;
    void close();

    // 初始化数据库连接
    bool initDatabase(const QString &dbPath);
    
    // 单词管理
    bool addWord(const Word &word); // 添加一个单词对象 已实现
    bool deleteWord(int id); // 删除某个id的单词 已实现
    QVector<Word> getAllWords(); // 获取某个库中的所有词汇 已实现
    Word getWordById(int id); // 根据id获取单词 已实现
    QVector<Word> getWordsByCategory(int categoryId); // 获取某个分类下的所有词汇 已实现
    QVector<Word> getWordsToReview(int userId, int count = 20); // 某个用户指定数目的词汇进行复习 已实现基本的选择办法
    
    // 分类管理(可以进行自定义分类)
    bool addCategory(const Category &category);// 添加一个分类对象 已实现
    bool deleteCategory(int id); // 删除一个分类对象 已实现
    QVector<Category> getAllCategories();// 获取某个库中的所有分类 已实现
    Category getCategoryById(int id);  // 根据id获取一个分类对象 已实现
    bool assignWordToCategory(int wordId, int categoryId); // 将一个词汇与分类关联起来 已实现
    bool removeWordFromCategory(int wordId, int categoryId); // 从某个分类中移除单词 已实现
    
    // 用户管理
    bool addUser(const QString &username, const QString &password);
    bool authenticateUser(const QString &username, const QString &password);
    int getUserId(const QString &username);
    
    // 学习记录管理
    bool addLearningRecord(const LearningRecord &record); // 添加一个学习记录对象 已实现
    QVector<LearningRecord> getUserLearningRecords(int userId, int days = 30);
    double getLearningAccuracy(int userId, int days = 30); // 已学习比例 已实现
    
    // 数据库工具方法
    bool createTables();
    bool insertSampleData();

private:
    QSqlDatabase m_db;
    QString m_connectionName; // 存储连接名称
    bool createWordTable();
    bool createCategoryTable();
    bool createUserTable();
    bool createLearningRecordTable();
    bool createWordCategoryTable();
};

#endif // DATABASE_H
