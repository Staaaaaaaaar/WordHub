#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include <QVector>
#include <QDateTime>

struct Word // 存储单词的基本信息，包括单词、发音、释义、例句等，同时记录学习相关信息如最后复习时间、复习次数和难度。
{
    int id;
    QString word;
    QString pronunciation;
    QString meaning;
    QString example;
    QDateTime lastReviewed;
    int reviewCount;
    int difficulty; // 1-5，1表示最简单，5表示最难
};

struct Category // 存储单词的分类信息，如基础词汇、学术词汇等。
{

    QString name;
    QString description;
    int id;
};

struct LearningRecord // 学习记录
{
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
    bool addWord(const Word &word);
    bool updateWord(const Word &word);
    bool deleteWord(int id);
    QVector<Word> getAllWords();
    Word getWordById(int id);
    QVector<Word> getWordsByCategory(int categoryId);
    QVector<Word> getWordsToReview(int userId, int count = 20);
    
    // 分类管理
    bool addCategory(const Category &category);
    bool updateCategory(const Category &category);
    bool deleteCategory(int id);
    QVector<Category> getAllCategories();
    Category getCategoryById(int id);
    bool assignWordToCategory(int wordId, int categoryId);
    bool removeWordFromCategory(int wordId, int categoryId);
    
    // 用户管理
    bool addUser(const QString &username, const QString &password);
    bool authenticateUser(const QString &username, const QString &password);
    int getUserId(const QString &username);
    
    // 学习记录管理
    bool addLearningRecord(const LearningRecord &record);
    QVector<LearningRecord> getUserLearningRecords(int userId, int days = 30);
    double getLearningAccuracy(int userId, int days = 30);
    
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

#endif // WORDDATABASE_H
