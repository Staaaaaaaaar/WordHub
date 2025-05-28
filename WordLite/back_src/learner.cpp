#include "./back_head/learner.h"
#include <QCoreApplication>

// 静态成员初始化
const QString Learner::DB_CONNECTION_NAME = "LearnerDB";
const QString Learner::DB_FILENAME = "user_data.sqlite";

// 修改：实现getUserDir方法
const QString& Learner::getUserDir()
{
    static QString userDir = QCoreApplication::applicationDirPath() + "/User";
    qDebug() << "获取用户目录:" << userDir;
    return userDir;
}

Learner::Learner()
{
    qDebug() << "初始化Learner对象";
    
    // 初始化数据库
    if (!initDatabase()) {
        qDebug() << "数据库初始化失败，使用临时数据";
        m_name = "Guest";
        m_startLearningTime = QDateTime::currentDateTime();
        m_totalLearned = 0;
        return;
    }
    
    // 尝试加载用户数据
    if (!loadUserData()) {
        // 没有用户数据，创建默认用户
        qDebug() << "未找到用户数据，创建默认Guest用户";
        m_name = "Guest";
        m_startLearningTime = QDateTime::currentDateTime();
        m_totalLearned = 0;
        saveUserData();
    }
}

Learner::~Learner()
{
    qDebug() << "析构Learner对象";
    
    if (m_db.isOpen()) {
        qDebug() << "关闭数据库连接";
        m_db.close();
    }
    
    if (QSqlDatabase::contains(DB_CONNECTION_NAME)) {
        qDebug() << "移除数据库连接";
        QSqlDatabase::removeDatabase(DB_CONNECTION_NAME);
    }
}

bool Learner::initDatabase()
{
    // 确保用户目录存在
    QDir userDir(getUserDir());
    if (!userDir.exists()) {
        qDebug() << "创建用户目录:" << getUserDir();
        if (!userDir.mkpath(".")) {
            qDebug() << "无法创建用户目录:" << getUserDir();
            return false;
        }
    }
    
    // 设置数据库文件路径
    QString dbPath = userDir.absoluteFilePath(DB_FILENAME);
    qDebug() << "数据库文件路径:" << dbPath;
    
    // 检查数据库文件是否存在
    QFileInfo dbFile(dbPath);
    qDebug() << "数据库文件是否存在:" << dbFile.exists();
    
    // 检查是否已存在连接
    if (QSqlDatabase::contains(DB_CONNECTION_NAME)) {
        qDebug() << "使用已存在的数据库连接";
        m_db = QSqlDatabase::database(DB_CONNECTION_NAME);
    } else {
        // 创建新的数据库连接
        qDebug() << "创建新的数据库连接";
        m_db = QSqlDatabase::addDatabase("QSQLITE", DB_CONNECTION_NAME);
        m_db.setDatabaseName(dbPath);
    }
    
    if (!m_db.open()) {
        qDebug() << "无法打开数据库:" << m_db.lastError().text();
        return false;
    }
    
    qDebug() << "数据库连接成功";
    
    // 检查并创建用户表
    if (!createUserTable()) {
        qDebug() << "创建用户表失败";
        return false;
    }
    
    return true;
}

bool Learner::createUserTable()
{
    QSqlQuery query(m_db);
    
    // 创建用户表（移除IF NOT EXISTS检查，直接执行创建）
    qDebug() << "执行创建用户表操作";
    bool result = query.exec(
        "CREATE TABLE user_info ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT UNIQUE, "
        "hash_password TEXT, "
        "head_image_path TEXT, "
        "start_learning_time TEXT, "
        "total_learned INTEGER)"
    );
    
    if (!result) {
        // 如果表已存在，会返回错误，但这是预期的
        QSqlError error = query.lastError();
        if (error.nativeErrorCode() == "1") { // SQLITE_ERROR (1) 表示表已存在
            qDebug() << "用户表已存在，跳过创建";
            return true;
        }
        
        qDebug() << "创建用户表失败:" << error.text() << "错误码:" <<error.nativeErrorCode();
        return false;
    }
    
    qDebug() << "用户表创建成功";
    return true;
}

QString Learner::hashPassword(const QString& password) const
{
    QByteArray hashed = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    return hashed.toHex();
}

bool Learner::loadUserData()
{
    QSqlQuery query(m_db);
    
    // 检查数据库是否打开
    if (!m_db.isOpen()) {
        qDebug() << "数据库未打开，无法加载数据";
        return false;
    }
    
    // 查询用户数据
    qDebug() << "查询用户数据";
    query.exec("SELECT * FROM user_info LIMIT 1"); // 表名为user_info
    if (query.next()) {
        m_name = query.value("name").toString(); // 表字段为name
        m_hashPassword = query.value("hash_password").toString(); // 表字段为hash_password
        m_headImagePath = query.value("head_image_path").toString(); // 表字段为head_image_path
        m_startLearningTime = QDateTime::fromString(query.value("start_learning_time").toString(), Qt::ISODate); // 表字段为start_learning_time
        m_totalLearned = query.value("total_learned").toInt(); // 表字段为total_learned
    }
    
    qDebug() << "未找到用户数据";
    return false;
}

bool Learner::saveUserData()
{
    QSqlQuery query(m_db);
    
    // 检查数据库是否打开
    if (!m_db.isOpen()) {
        qDebug() << "数据库未打开，无法保存数据";
        return false;
    }
    
    // 检查用户是否已存在
    query.prepare("SELECT id FROM user_info WHERE name = ?");
    query.addBindValue(m_name);
    
    if (!query.exec()) {
        qDebug() << "查询用户失败:" << query.lastError().text();
        return false;
    }
    
    bool userExists = query.next();
    
    if (userExists) {
        // 用户已存在，更新记录
        qDebug() << "更新现有用户数据: " << m_name;
        query.prepare(
            "UPDATE user_info SET "
            "hash_password = ?, "
            "head_image_path = ?, "
            "start_learning_time = ?, "
            "total_learned = ? "
            "WHERE name = ?"
        );
    } else {
        // 用户不存在，插入新记录
        qDebug() << "插入新用户数据: " << m_name;
        query.prepare(
            "INSERT INTO user_info (name, hash_password, head_image_path, start_learning_time, total_learned) "
            "VALUES (?, ?, ?, ?, ?)"
        );
    }
    
    query.addBindValue(m_hashPassword);
    query.addBindValue(m_headImagePath);
    query.addBindValue(m_startLearningTime.toString(Qt::ISODate));
    query.addBindValue(m_totalLearned);
    query.addBindValue(m_name);
    
    if (!query.exec()) {
        qDebug() << "保存用户数据失败:" << query.lastError().text();
        return false;
    }
    
    qDebug() << "用户数据保存成功: " << m_name;
    return true;
}

void Learner::setName(const QString& newName)
{
    qDebug() << "设置用户名: " << newName;
    m_name = newName;
    saveUserData();
}

void Learner::setPassword(const QString& password)
{
    qDebug() << "设置密码 (已加密)";
    m_hashPassword = hashPassword(password);
    saveUserData();
}

bool Learner::verifyPassword(const QString& password) const
{
    bool result = hashPassword(password) == m_hashPassword;
    qDebug() << "密码验证结果: " << (result ? "成功" : "失败");
    return result;
}

void Learner::setHeadImagePath(const QString& newPath)
{
    qDebug() << "设置头像路径: " << newPath;
    m_headImagePath = newPath;
    saveUserData();
}

void Learner::setTotalLearned(int value)
{
    qDebug() << "设置学习总数: " << value;
    m_totalLearned = value;
    saveUserData();
}

bool Learner::createNewUser(const QString& username, const QString& password)
{
    qDebug() << "尝试创建新用户: " << username;
    
    // 先检查是否已存在用户
    if (isUserLoggedIn() && m_name != "Guest") {
        qDebug() << "已有用户登录，无法创建新用户";
        return false;
    }
    
    // 创建新用户
    m_name = username;
    m_hashPassword = hashPassword(password);
    m_headImagePath = ":/images/default_avatar.png";
    m_startLearningTime = QDateTime::currentDateTime();
    m_totalLearned = 0;
    
    bool result = saveUserData();
    qDebug() << "创建新用户结果: " << (result ? "成功" : "失败");
    return result;
}

bool Learner::resetUser(bool confirm)
{
    qDebug() << "尝试重置用户 (确认:" << confirm << ")";
    
    if (!confirm) {
        qDebug() << "重置操作需要确认参数";
        return false;
    }
    
    // 检查数据库是否打开
    if (!m_db.isOpen()) {
        qDebug() << "数据库未打开，无法重置用户";
        return false;
    }
    
    QSqlQuery query(m_db);
    
    // 删除现有用户记录
    if (!query.exec("DELETE FROM user_info")) {
        qDebug() << "删除用户记录失败:" << query.lastError().text();
        return false;
    }
    
    qDebug() << "用户记录已删除，重置为Guest用户";
    
    // 重置为默认用户
    m_name = "Guest";
    m_hashPassword.clear();
    m_headImagePath.clear();
    m_startLearningTime = QDateTime::currentDateTime();
    m_totalLearned = 0;
    
    // 保存Guest用户信息
    bool result = saveUserData();
    qDebug() << "重置用户结果: " << (result ? "成功" : "失败");
    return result;
}

bool Learner::isUserLoggedIn() const
{
    // 改为检查数据库中是否存在用户（而非仅内存状态）
    QSqlQuery query(m_db);
    query.exec("SELECT COUNT(*) FROM user_info");
    if (query.next()) {
        return query.value(0).toInt() > 0;
    }
    return false;
}
