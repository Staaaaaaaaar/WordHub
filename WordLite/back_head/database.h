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

class WordDatabase : public QObject {
    Q_OBJECT
public:
    explicit WordDatabase();

    ~WordDatabase();

    // 数据库状态管理
    bool isOpen() const;
    void close();
    static void resetAll();

    // 数据库操作
    bool initDatabase(const QString &name); // 打开已有数据库
    bool NewDatabase(const QString &name); // 创建新数据库
    // 新增：获取数据库中单词的总数
    int getTotalWordCount(int categoryId = -1);


    // 单词管理
    bool addWord(const Word &word); // 添加新单词
    bool deleteWord(int id); // 删除单词
    QVector<Word> getAllWords(); // 获取所有单词
    Word getWordById(int id); // 根据ID获取单词
    bool ifWordinCategory(int wordid,int categoryid); // 判断某个单词是否属于某个分类
    QVector<Word> getWordsByName(const QString &wordName); // 按名称查找单词
    QVector<Word> getWordsByCategory(int categoryId); // 获取指定分类下的单词
    QVector<Word> getWordsToReview(int count = 20,int userId=1); // 获取需要复习的单词（基于间隔重复算法）
    // 新增：从指定分类中随机获取指定数量的单词
    QVector<Word> getRandomWords(int count, int categoryId = -1);
    // 新增：获取复习次数小于等于指定值的单词
    QVector<Word> getWordsByReviewCount(int maxReviewCount, int count = -1, int categoryId = -1);

    //learning 处理学习过程中的事件

    // 新增：更新单词学习信息并添加学习记录
    bool updateWordLearningInfo(int wordId, bool correct, int difficultyChange=0, int userId=1);
    // 输入正在学习单词的id，返回该单词的正确释义和3个其他选项；返回列表第一项是输入单词的释义
    QVector<QString> FourmeaningtoChoice(int wordid);
    // difficult==1 认为是已经掌握
    QVector<Word> getWordsWithDifficultyOne(int categoryId = -1);
    int learnednum();

    // 静态方法：获取所有词库中总共学习的单词数量
    static int getAllTotalWordCount();

    // 静态方法：获取所有词库中指定天数内每天学习单词的数量
    static QVector<int> getAllDailyLearningCountInDays(int days = 30, int userId = 1);

    // 静态方法：获取所有词库中指定天数内每天学习的正确率
    static QVector<double> getAllDailyLearningAccuracyInDays(int days = 30, int userId = 1);

    // 静态方法：获取所有词库中指定天数内总的学习正确率
    static double getAllLearningAccuracy(int days = 30, int userId = 1);


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
    QVector<LearningRecord> getUserLearningRecords(int days = 30,int userId=1); // 获取用户学习记录
    double getLearningAccuracy(int days = 30,int userId=1); // 计算学习准确率
    // 新增：获取数据库中学习记录的总数
    int getTotalLearningRecordCount(int days = -1,int userId =1);
    // 在连续多少天内每一天的学习数目
    QVector<int> getDailyLearningCountInDays(int days = 30, int userId = 1);
    // 在连续多少天内每一天的学习正确率
    QVector<double> getDailyLearningAccuracyInDays(int days = 30, int userId = 1);
    // 重置学习当前数据库的学习记录
    bool resetLearningRecords();

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
