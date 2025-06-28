# Learner 类文档

**负责人**: [刘继轩](https://github.com/stibiums)

## 一、概述
`Learner` 类是一个单例类，作为项目的核心业务逻辑层。它负责管理当前用户的全局状态，包括个人信息、学习进度、数据库连接以及成就系统。它隔离了UI层和数据层，所有上层UI的请求都通过 `Learner` 实例进行分发和处理。

## 二、属性
- `WordDatabase* db`: 指向当前用户所使用词库数据库的指针。
- `static Learner* instance`: **[私有]** 指向单例实例的静态指针。
- `int m_userId`: **[私有]** 当前用户的ID。
- `QString m_name`: **[私有]** 当前用户名。
- `QDateTime m_startLearningTime`: **[私有]** 用户首次学习的时间。
- `QMap<int, QDateTime> m_unlockedAchievements`: **[私有]** 存储已解锁成就ID和解锁时间的映射。
- `QSqlDatabase m_db`: **[私有]** 用于存储用户和成就等全局信息的数据库连接。

## 三、方法

### 静态方法
- `static Learner* getInstance()`: 获取 `Learner` 类的全局唯一实例。
    - **返回值**: `Learner*`，指向 `Learner` 类单例实例的指针。
- `static QString getUserDatabasePath()`: 获取用户全局数据库文件 (`learning_data.db`) 的完整路径。
    - **返回值**: `QString`，数据库文件的绝对路径。
- `static QString getUserAvatarPath()`: 获取用户头像的存储目录路径。
    - **返回值**: `QString`，头像目录的绝对路径。

### 用户信息管理
- `void setName(const QString& newName)`: 设置用户的名称，并同步更新到数据库。
- `void setPassword(const QString& password)`: 设置用户的密码，对密码进行哈希处理后保存到数据库。
- `bool verifyPassword(const QString& password) const`: 验证输入的密码是否与存储的哈希密码匹配。
    - **返回值**: `bool`，如果密码匹配返回 `true`，否则返回 `false`。
- `void setHeadImagePath(const QString& newPath)`: 设置用户的头像路径。如果源文件不在目标目录，会自动复制。

### 用户状态操作
- `bool createNewUser(const QString& username, const QString& password)`: 创建一个新用户，并初始化其数据。
    - **返回值**: `bool`，如果用户创建成功返回 `true`。
- `bool isUserLoggedIn() const`: 检查用户是否已经登录（通过查询数据库中是否存在用户记录）。
    - **返回值**: `bool`，如果用户已登录返回 `true`，否则返回 `false`。
- `bool resetUser(bool confirm = false)`: 重置用户数据，清空数据库中所有与该用户相关的信息。
    - **参数**: `confirm` 必须为 `true` 才会执行重置。
    - **返回值**: `bool`，如果操作成功返回 `true`。

### 成就系统管理
- `bool unlockAchievement(int achievementId)`: 解锁一个指定的成就。
    - **描述**: 如果该成就未被解锁，则将其信息写入数据库并更新内存中的状态。
    - **返回值**: `bool`，如果本次调用成功解锁了一个新成就，返回 `true`。
- `const QMap<int, QDateTime>& getUnlockedAchievements() const`: 获取一个包含所有已解锁成就ID和解锁时间的 `QMap`。
    - **返回值**: `const QMap<int, QDateTime>&`，对内部已解锁成就映射的常量引用。

### 访问器 (Getters)
- `QDateTime getStartTime() const`: 获取用户开始学习的时间。
- `QString getName() const`: 获取当前用户名。
- `QString getHeadImagePath() const`: 获取当前用户头像的路径。
- `int getUserId() const`: 获取当前用户ID。