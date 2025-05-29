#ifndef LEARNER_H
#define LEARNER_H

#include <QString>
#include <QDateTime>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QCryptographicHash>
#include <QDir>
#include "database.h"
class Learner
{
private:
    // 单例模式核心成员
    static Learner* instance;

    // 数据库配置
public:
    static const QString DB_CONNECTION_NAME;  // 需要在cpp文件初始化
    static const QString DB_FILENAME;
private:
    // 实例成员
    QString m_hashPassword;
    QDateTime m_startLearningTime;
    int m_totalLearned = 0;
    QString m_name;
    QString m_headImage;
    QSqlDatabase m_db;

    // 私有构造函数实现单例
    Learner();
    ~Learner();

    // 禁止拷贝
    Learner(const Learner&) = delete;
    Learner& operator=(const Learner&) = delete;
public:
    // 静态方法
    static const QString& getUserDir();
private:
    // 数据库操作
    bool initDatabase();
    bool createUserTable();
    QString hashPassword(const QString& password) const;
    bool loadUserData();
    bool saveUserData();

public:
    // 单例访问点
    static Learner* getInstance();

    // 添加用户目录访问方法
    static QString getUserDatabasePath();
    static QString getUserAvatarPath();

    // 用户信息管理
    void setName(const QString& newName);
    void setPassword(const QString& password);
    bool verifyPassword(const QString& password) const;
    void setHeadImage(const QString& name){m_headImage=name;};
    void setTotalLearned(int value){m_totalLearned=value;};

    // 用户状态操作
    bool createNewUser(const QString& username, const QString& password);
    bool resetUser(bool confirm = false);
    bool isUserLoggedIn() const;

    // 访问器
    QDateTime getStartTime() const { return m_startLearningTime; }
    QString getName() const { return m_name; }
    QString getHeadImage() const { return m_headImage; }
    int getTotalLearned() const { return m_totalLearned; }
};

#endif // LEARNER_H
