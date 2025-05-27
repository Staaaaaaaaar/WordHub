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

#include <QMap>
#include <QCoreApplication>
#include <QDir>
#include <set>
#include "./utils.h"


/**
 * @brief 单词数据库管理类
 *
 * 负责与SQLite数据库交互，管理单词、分类、用户和学习记录
 */
class WordDatabase : public QObject {
    Q_OBJECT
public:
    explicit WordDatabase();

    ~WordDatabase();

    // 数据库状态管理
    bool isOpen() const;
    void close();

    // 数据库操作
    bool initDatabase(const QString &name); // 打开已有数据库
    bool NewDatabase(const QString &name); // 创建新数据库

    // 单词管理
    bool addWord(const Word &word); // 添加新单词
    bool deleteWord(int id); // 删除单词
    QVector<Word> getAllWords(); // 获取所有单词
    Word getWordById(int id); // 根据ID获取单词
    QVector<Word> getWordsByName(const QString &wordName); // 按名称查找单词
    QVector<Word> getWordsByCategory(int categoryId); // 获取指定分类下的单词
    QVector<Word> getWordsToReview(int userId, int count = 20); // 获取需要复习的单词（基于间隔重复算法）

    // 分类管理
    bool addCategory(const Category &category); // 添加分类
    bool deleteCategory(int id); // 删除分类
    QVector<Category> getAllCategories(); // 获取所有分类
    Category getCategoryById(int id); // 根据ID获取分类
    QVector<Category> getCategoriesByName(const QString &categoryName); // 按名称查找分类
    bool assignWordToCategory(int wordId, int categoryId); // 将单词添加到分类
    bool removeWordFromCategory(int wordId, int categoryId); // 将单词从分类中移除

    // 用户管理
    bool addUser(const QString &username, const QString &password); // 添加用户
    bool authenticateUser(const QString &username, const QString &password); // 验证用户
    int getUserId(const QString &username); // 获取用户ID

    // 学习记录管理

    bool addLearningRecord(const LearningRecord &record); // 添加学习记录
    QVector<LearningRecord> getUserLearningRecords(int userId, int days = 30); // 获取用户学习记录
    double getLearningAccuracy(int userId, int days = 30); // 计算学习准确率

    // 工具方法
    bool createTables(); // 创建数据库表结构
    bool insertSampleData(); // 插入示例数据
    static QMap<QString, QString> getpath(); // 获取所有数据库文件路径
    static QVector<QString> getlist(); // 获取所有数据库名称
    const QString& getPath() { return Path; } // 获取当前数据库路径

private:
    QSqlDatabase m_db; // 数据库连接
    QString Path; // 当前数据库路径
    QString m_connectionName; // 数据库连接名称

    // 表创建方法
    bool createWordTable(); // 创建单词表
    bool createCategoryTable(); // 创建分类表
    bool createUserTable(); // 创建用户表
    bool createLearningRecordTable(); // 创建学习记录表
    bool createWordCategoryTable(); // 创建单词-分类关联表
    bool createPhoneticsTable(); // 创建音标表
    bool createPartsOfSpeechTable(); // 创建词性表
    bool createDefinitionsTable(); // 创建释义表
    bool createSynonymsTable(); // 创建同义词表
    bool createAntonymsTable(); // 创建反义词表

    // 辅助方法
    bool openDatabase(const QString &dbPath, bool isNew); // 打开数据库
    bool execSql(const QString &sql); // 执行SQL语句
    int getOrCreatePartOfSpeech(const QString &posName); // 获取或创建词性
    bool savePhonetics(int wordId, const QVector<Phonetic> &phonetics); // 保存音标
    bool saveDefinitions(int wordId, const QMap<QString, QVector<Definition>> &meanings); // 保存释义
    bool loadPhonetics(int wordId, QVector<Phonetic> &phonetics); // 加载音标
    bool loadDefinitions(int wordId, QMap<QString, QVector<Definition>> &meanings); // 加载释义

};

#endif // DATABASE_H
