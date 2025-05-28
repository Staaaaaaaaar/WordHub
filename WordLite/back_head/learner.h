#ifndef LEARNER_H
#define LEARNER_H

#include <QString>
#include <QDateTime>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QCryptographicHash>
#include <QDir>
#include <QDebug>

class Learner
{
private:
    QString m_hashPassword;
    QDateTime m_startLearningTime;
    int m_totalLearned;
    QString m_name;
    QString m_headImagePath;
    
    // 数据库连接
    QSqlDatabase m_db;
    static const QString DB_CONNECTION_NAME; // 数据库连接名称
    static const QString DB_FILENAME; // SQLite数据库文件名
    
    // 修改：将USER_DIR改为私有静态方法
    static const QString& getUserDir();

    // 初始化数据库连接
    bool initDatabase();
    
    // 创建用户表
    bool createUserTable();
    
    // 加密密码
    QString hashPassword(const QString& password) const;
    
    // 从数据库加载用户数据
    bool loadUserData();
    
    // 保存用户数据到数据库
    bool saveUserData();

public:
    Learner();
    ~Learner();

    // 用户信息设置
    void setName(const QString& newName);
    void setPassword(const QString& password);
    bool verifyPassword(const QString& password) const;
    QDateTime getStartTime() const { return m_startLearningTime; }
    void setHeadImagePath(const QString& newPath);
    void setTotalLearned(int value);
    int getTotalLearned() const { return m_totalLearned; }

    // 用户管理
    bool createNewUser(const QString& username, const QString& password);
    bool resetUser(bool confirm = false);
    bool isUserLoggedIn() const;
    
    // 获取用户信息
    QString getName() const { return m_name; }
    QString getHeadImagePath() const { return m_headImagePath; }
};

#endif // LEARNER_H