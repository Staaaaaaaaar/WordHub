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

#include "./utils.h"


class WordDatabase : public QObject
{
    Q_OBJECT
public:

    explicit WordDatabase();

    ~WordDatabase();

    bool isOpen() const;
    void close();

    // 初始化数据库连接
    bool initDatabase(const QString &dbPath); // 加载已有的数据库
    bool NewDatabase(const QString &dbPath); // 创建全新的数据库
    
    // 单词管理
    bool addWord(const Word &word); // 添加一个单词对象 已实现
    bool deleteWord(int id); // 删除某个id的单词 已实现
    QVector<Word> getAllWords(); // 获取某个库中的所有词汇 已实现
    Word getWordById(int id); // 根据id获取单词 已实现
    QVector<Word> getWordsByName(const QString &wordName);// 直接查找某个单词 已实现
    QVector<Word> getWordsByCategory(int categoryId); // 获取某个分类下的所有词汇 已实现
    QVector<Word> getWordsToReview(int userId, int count = 20); // 某个用户指定数目的词汇进行复习 已实现基本的选择办法
    
    // 分类管理(可以进行自定义分类)
    bool addCategory(const Category &category);// 添加一个分类对象 已实现
    bool deleteCategory(int id); // 删除一个分类对象 已实现
    QVector<Category> getAllCategories();// 获取某个库中的所有分类 已实现
    Category getCategoryById(int id);  // 根据id获取一个分类对象 已实现
    QVector<Category> getCategoriesByName(const QString &categoryName); // 根据名称查找某个分类对象 已实现
    bool assignWordToCategory(int wordId, int categoryId); // 将一个词汇与分类关联起来 已实现
    bool removeWordFromCategory(int wordId, int categoryId); // 从某个分类中移除单词 已实现
    
    // 用户管理 // 这部分没有经过测试，还没想好是否应该在这里实现
    bool addUser(const QString &username, const QString &password); // 添加用户
    bool authenticateUser(const QString &username, const QString &password);  // 用户认证
    int getUserId(const QString &username); // 获取用户id
    
    // 学习记录管理
    bool addLearningRecord(const LearningRecord &record); // 添加一个学习记录对象 已实现
    QVector<LearningRecord> getUserLearningRecords(int userId, int days = 30);
    double getLearningAccuracy(int userId, int days = 30); // 已学习比例 已实现
    
    // 数据库工具方法
    bool createTables();
    bool insertSampleData();
    static QMap<QString,QString> getpath (); // 获取key为数据库名称，value为存储路径的 map  已实现
    static QVector<QString> getlist(); // 获取当前已有的数据库名称列表 已实现
    const QString& getPath(){return Path;} // 获取当前数据库的路径 已实现

private:
    QSqlDatabase m_db;
    QString Path;
    QString m_connectionName; // 存储连接名称
    bool createWordTable();
    bool createCategoryTable();
    bool createUserTable();
    bool createLearningRecordTable();
    bool createWordCategoryTable();
    bool openDatabase(const QString &dbPath, bool isNew);
};

#endif // DATABASE_H
