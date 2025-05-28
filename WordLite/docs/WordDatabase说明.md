
### `WordDatabase` 类

#### 功能与用途
`WordDatabase` 类负责与 SQLite 数据库交互，管理单词、分类、用户和学习记录。它提供了一系列方法用于数据库的初始化、单词和分类的增删改查、用户认证以及学习记录的管理。

#### 属性
- `QSqlDatabase m_db`：数据库连接对象。
- `QString Path`：当前数据库的路径。
- `QString m_connectionName`：数据库连接的名称。

#### 方法
- **数据库状态管理**
  - `bool isOpen() const`：检查数据库是否打开。
  - `void close()`：关闭数据库连接。
- **数据库操作**
  - `bool initDatabase(const QString &name)`：打开已有的数据库。
  - `bool NewDatabase(const QString &name)`：创建新的数据库。
- **单词管理**
  - `bool addWord(const Word &word)`：向数据库中添加新单词。
  - `bool deleteWord(int id)`：根据单词 ID 删除单词。
  - `QVector<Word> getAllWords()`：获取数据库中所有的单词。
  - `Word getWordById(int id)`：根据单词 ID 获取单词信息。
  - `QVector<Word> getWordsByName(const QString &wordName)`：根据单词名称查找单词。
  - `QVector<Word> getWordsByCategory(int categoryId)`：获取指定分类下的所有单词。
  - `QVector<Word> getWordsToReview(int userId, int count = 20)`：获取需要复习的单词（基于间隔重复算法）。
- **分类管理**
  - `bool addCategory(const Category &category)`：添加新的分类。
  - `bool deleteCategory(int id)`：根据分类 ID 删除分类。
  - `QVector<Category> getAllCategories()`：获取所有的分类。
  - `Category getCategoryById(int id)`：根据分类 ID 获取分类信息。
  - `QVector<Category> getCategoriesByName(const QString &categoryName)`：根据分类名称查找分类。
  - `bool assignWordToCategory(int wordId, int categoryId)`：将单词添加到指定分类中。
  - `bool removeWordFromCategory(int wordId, int categoryId)`：将单词从指定分类中移除。
- **用户管理**
  - `bool addUser(const QString &username, const QString &password)`：添加新用户。
  - `bool authenticateUser(const QString &username, const QString &password)`：验证用户的用户名和密码。
  - `int getUserId(const QString &username)`：根据用户名获取用户 ID。
- **学习记录管理**
  - `bool addLearningRecord(const LearningRecord &record)`：添加学习记录。
  - `QVector<LearningRecord> getUserLearningRecords(int userId, int days = 30)`：获取指定用户在指定天数内的学习记录。
  - `double getLearningAccuracy(int userId, int days = 30)`：计算指定用户在指定天数内的学习准确率。
- **工具方法**
  - `bool createTables()`：创建数据库的表结构。
  - `bool insertSampleData()`：插入示例数据。
  - `static QMap<QString, QString> getpath()`：获取所有数据库文件的路径。
  - `static QVector<QString> getlist()`：获取所有数据库的名称。
  - `const QString& getPath()`：获取当前数据库的路径。


