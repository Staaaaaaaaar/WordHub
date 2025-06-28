# Learner 类文档

**负责人**: [刘继轩](https://github.com/stibiums)

## 一、概述
`Learner` 类是一个单例类，用于管理学习者的用户信息和数据。它使用 SQLite 数据库来存储用户数据，包括用户名、密码哈希、开始学习时间、总学习量和头像路径等。

## 二、类定义
```cpp
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
    QString m_headImagePath;
    QSqlDatabase m_db;

    // 私有构造函数实现单例
    Learner();
    ~Learner();

    // 禁止拷贝
    Learner(const Learner&) = delete;
    Learner& operator=(const Learner&) = delete;

    // 静态方法
    static const QString& getUserDir();

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
    void setHeadImagePath(const QString& newPath);
    void setTotalLearned(int value);

    // 用户状态操作
    bool createNewUser(const QString& username, const QString& password);
    bool resetUser(bool confirm = false);
    bool isUserLoggedIn() const;

    // 访问器
    QDateTime getStartTime() const;
    QString getName() const;
    QString getHeadImagePath() const;
    int getTotalLearned() const;
};
```

## 三、静态成员变量
### `DB_CONNECTION_NAME`
- **类型**：`const QString`
- **描述**：数据库连接的名称，用于在 `QSqlDatabase` 中标识该连接。
- **注意事项**：需要在 `.cpp` 文件中进行初始化。

### `DB_FILENAME`
- **类型**：`const QString`
- **描述**：SQLite 数据库文件的名称。

## 四、静态方法

### `getInstance()`
- **功能**：获取 `Learner` 类的单例实例。
- **返回值**：`Learner*`，指向 `Learner` 类单例实例的指针。
- **用法示例**：
```cpp
Learner* learner = Learner::getInstance();
```

### `getUserDir()`
- **功能**：获取用户数据存储目录的路径。
- **返回值**：`const QString&`，用户数据存储目录的路径。
- **注意事项**：返回的是静态常量引用，避免不必要的字符串复制。

### `getUserDatabasePath()`
- **功能**：获取用户数据库文件的完整路径。
- **返回值**：`QString`，用户数据库文件的完整路径。
- **用法示例**：
```cpp
QString dbPath = Learner::getUserDatabasePath();
```

### `getUserAvatarPath()`
- **功能**：获取用户头像存储目录的路径。
- **返回值**：`QString`，用户头像存储目录的路径。
- **用法示例**：
```cpp
QString avatarPath = Learner::getUserAvatarPath();
```

## 五、构造函数和析构函数

### `Learner()`
- **功能**：私有构造函数，用于初始化 `Learner` 类的实例。在构造过程中，会尝试初始化数据库并加载用户数据。
- **注意事项**：如果数据库初始化或用户数据加载失败，会输出警告信息。

### `~Learner()`
- **功能**：析构函数，用于关闭数据库连接并从 `QSqlDatabase` 中移除该连接。

## 六、数据库操作方法

### `initDatabase()`
- **功能**：初始化数据库连接，创建用户数据存储目录和头像子目录，并尝试打开数据库。如果数据库打开成功，会调用 `createUserTable()` 方法创建用户表。
- **返回值**：`bool`，如果数据库初始化成功返回 `true`，否则返回 `false`。

### `createUserTable()`
- **功能**：创建用户数据表 `users`，用于存储用户的相关信息。
- **返回值**：`bool`，如果表创建成功返回 `true`，否则返回 `false`。

### `hashPassword(const QString& password) const`
- **功能**：对输入的密码进行哈希处理，使用 `QCryptographicHash::Sha256` 算法。
- **参数**：
  - `password`：需要进行哈希处理的密码字符串。
- **返回值**：`QString`，经过哈希处理后的密码字符串。

### `loadUserData()`
- **功能**：从数据库中加载用户数据到 `Learner` 类的实例中。
- **返回值**：`bool`，如果成功加载用户数据返回 `true`，否则返回 `false`。

### `saveUserData()`
- **功能**：将 `Learner` 类实例中的用户数据保存到数据库中。
- **返回值**：`bool`，如果数据保存成功返回 `true`，否则返回 `false`。

## 七、用户信息管理方法

### `setName(const QString& newName)`
- **功能**：设置用户的名称，并将新名称保存到数据库中。
- **参数**：
  - `newName`：新的用户名称。

### `setPassword(const QString& password)`
- **功能**：设置用户的密码，对密码进行哈希处理后保存到数据库中。
- **参数**：
  - `password`：新的用户密码。

### `verifyPassword(const QString& password) const`
- **功能**：验证输入的密码是否与存储的哈希密码匹配。
- **参数**：
  - `password`：需要验证的密码字符串。
- **返回值**：`bool`，如果密码匹配返回 `true`，否则返回 `false`。
- **注意事项**：会输出密码验证结果的调试信息。

### `setHeadImagePath(const QString& newPath)`
- **功能**：设置用户的头像路径。如果源文件不在目标头像目录，会将文件复制到目标目录。
- **参数**：
  - `newPath`：新的头像文件路径。
- **注意事项**：如果文件复制失败，头像路径可能不会被更新。

### `setTotalLearned(int value)`
- **功能**：设置用户的总学习量。
- **参数**：
  - `value`：新的总学习量。

## 八、用户状态操作方法

### `createNewUser(const QString& username, const QString& password)`
- **功能**：创建一个新用户，将用户名和哈希后的密码保存到数据库中，并记录开始学习时间。
- **参数**：
  - `username`：新用户的名称。
  - `password`：新用户的密码。
- **返回值**：`bool`，如果用户创建成功返回 `true`，如果用户已经登录则返回 `false`。

### `resetUser(bool confirm = false)`
- **功能**：重置用户数据，将数据库中的用户信息删除，并清空 `Learner` 类实例中的相关数据。同时会清空所有单词数据库中有关学习记录的部分。
- **参数**：
  - `confirm`：确认是否重置用户数据，默认为 `false`。
- **返回值**：`bool`，如果确认重置且操作成功返回 `true`，否则返回 `false`。

### `isUserLoggedIn() const`
- **功能**：检查用户是否已经登录，通过查询数据库中是否存在用户记录来判断。
- **返回值**：`bool`，如果用户已登录返回 `true`，否则返回 `false`。
- **注意事项**：SQL 查询语句中的表名可能需要根据实际情况进行调整。

## 九、访问器方法

### `getStartTime() const`
- **功能**：获取用户开始学习的时间。
- **返回值**：`QDateTime`，用户开始学习的时间。

### `getName() const`
- **功能**：获取用户的名称。
- **返回值**：`QString`，用户的名称。

### `getHeadImagePath() const`
- **功能**：获取用户的头像路径。
- **返回值**：`QString`，用户的头像路径。

### `getTotalLearned() const`
- **功能**：获取用户的总学习量。
- **返回值**：`int`，用户的总学习量。