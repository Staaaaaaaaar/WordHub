#include "../back_head/Learner.h"
#include <QStandardPaths>
#include <QCoreApplication> // 新增头文件

// 静态成员初始化
Learner* Learner::instance = nullptr;
const QString Learner::DB_CONNECTION_NAME = "learner_db_connection";
const QString Learner::DB_FILENAME = "learning_data.db";

Learner* Learner::getInstance() {
    if (!instance) {
        instance = new Learner();
    }
    return instance;
}

// 修改静态路径获取方式
const QString& Learner::getUserDir() {
    static QString dir = QCoreApplication::applicationDirPath() + "/User/";
    return dir;
}

QString Learner::getUserDatabasePath() {
    return getUserDir() + DB_FILENAME;
}

QString Learner::getUserAvatarPath() {
    return getUserDir() + "Avatars/";
}

Learner::Learner() {
    if (!initDatabase() || !loadUserData()) {
        qWarning() << "Failed to initialize user data";
    }
}


Learner::~Learner() {
    if (m_db.isOpen()) {
        m_db.close();
    }
    QSqlDatabase::removeDatabase(DB_CONNECTION_NAME);
}

bool Learner::initDatabase() {
    QDir userDir(getUserDir());
    if (!userDir.exists()) {
        userDir.mkpath(".");  // 创建User目录
        userDir.mkpath("Avatars"); // 创建头像子目录
    }

    m_db = QSqlDatabase::addDatabase("QSQLITE", DB_CONNECTION_NAME);
    m_db.setDatabaseName(getUserDatabasePath());

    if (!m_db.open()) {
        qCritical() << "Database error:" << m_db.lastError();
        return false;
    }
    return createUserTable();
}

bool Learner::createUserTable() {
    QSqlQuery query(m_db);
    return query.exec(
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT UNIQUE NOT NULL,"
        "hash_password TEXT NOT NULL,"
        "start_time DATETIME NOT NULL,"
        "total_learned INTEGER DEFAULT 0,"
        "avatar_path TEXT)");
}

QString Learner::hashPassword(const QString& password) const {
    return QCryptographicHash::hash(
               password.toUtf8(), QCryptographicHash::Sha256).toHex();
}

bool Learner::loadUserData() {
    QSqlQuery query(m_db);
    query.exec("SELECT * FROM users LIMIT 1");
    if (query.next()) {
        m_name = query.value("username").toString();
        m_hashPassword = query.value("hash_password").toString();
        m_startLearningTime = query.value("start_time").toDateTime();
        m_totalLearned = query.value("total_learned").toInt();
        m_headImage = query.value("avatar_path").toString();
        return true;
    }
    return false;
}

bool Learner::saveUserData() {
    QSqlQuery query(m_db);
    query.prepare("REPLACE INTO users (username, hash_password, start_time, total_learned, avatar_path) "
                  "VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(m_name);
    query.addBindValue(m_hashPassword);
    query.addBindValue(m_startLearningTime);
    query.addBindValue(m_totalLearned);
    query.addBindValue(m_headImage);
    return query.exec();
}

// 用户管理函数实现
bool Learner::createNewUser(const QString& username, const QString& password) {
    if (isUserLoggedIn()) return false;

    m_name = username;
    m_hashPassword = hashPassword(password);
    m_startLearningTime = QDateTime::currentDateTime();
    qDebug()<<"创建用户"<<hashPassword(password)<<' '<<password;
    return saveUserData();
}

bool Learner::resetUser(bool confirm) {
    if (!confirm) return false;
    QSqlQuery("DELETE FROM users", m_db).exec();
    m_name.clear();
    m_hashPassword.clear();
    m_headImage.clear();
    m_totalLearned = 0;

    // 同时重置所有数据库中保存的学习记录
    for(auto name:WordDatabase::getlist())
    {
        WordDatabase db;
        db.initDatabase(name);
        db.resetLearningRecords();
    }
    return true;
}

// setter 方法需要自动保存
void Learner::setName(const QString& newName) {
    m_name = newName;
    saveUserData();
}

void Learner::setPassword(const QString& password) {
    m_hashPassword = hashPassword(password);
    saveUserData();
}


bool Learner::verifyPassword(const QString& password) const
{
    bool result = hashPassword(password) == m_hashPassword;
    qDebug() << "密码验证结果: " << (result ? "成功" : "失败");
    return result;
}


bool Learner::isUserLoggedIn() const
{
    // 改为检查数据库中是否存在用户（而非仅内存状态）
    QSqlQuery query(m_db);
    query.exec("SELECT COUNT(*) FROM users"); // 修正表名
    if (query.next()) {
        return query.value(0).toInt() > 0;
    }
    return false;
}

bool Learner::verifyUserName(const QString & username)const
{
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM users WHERE username = ?");
    query.addBindValue(username);
    if (query.exec() && query.next())
    {
        return true;
    }
    return false;
}

bool Learner::verifyPasswordU(const QString & username,const QString & password)const
{
    QSqlQuery query(m_db);
    query.prepare("SELECT hash_password FROM users WHERE username = ?");
    query.addBindValue(username);
    if (query.exec() && query.next()) {
        QString storedHash = query.value(0).toString();
        QString inputHash = hashPassword(password);
        //qDebug()<<storedHash<<' '<<inputHash;
        qDebug()<<"密码比对"<<hashPassword(password)<<' '<<password;
        bool result = inputHash == storedHash;
        qDebug() << "密码验证结果: " << (result ? "成功" : "失败");
        return result;
    }
    qDebug() << "未找到该用户名";
    return false;
}
