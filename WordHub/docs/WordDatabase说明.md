### `WordDatabase` 类

**负责人**: [刘继轩](https://github.com/stibiums)

#### 功能与用途
`WordDatabase` 类负责与 SQLite 数据库交互，管理单词、分类、用户和学习记录。它提供了一系列方法用于数据库的初始化、单词和分类的增删改查、用户认证以及学习记录的管理。同时，还支持获取随机单词、按复习次数筛选单词以及更新单词学习信息等功能。

#### 属性
- `QSqlDatabase m_db`：数据库连接对象。
- `QString Path`：当前数据库的路径。
- `QString m_connectionName`：数据库连接的名称。

#### 方法

##### 数据库状态管理
- `bool isOpen() const`：检查数据库是否打开。
    - **返回值**：若数据库已打开，返回 `true`；否则返回 `false`。
- `void close()`：关闭数据库连接。

##### 数据库操作
- `bool initDatabase(const QString &name)`：打开已有的数据库。
    - **参数**：`name` 为数据库名称。
    - **返回值**：若成功打开数据库，返回 `true`；否则返回 `false`。
- `bool NewDatabase(const QString &name)`：创建新的数据库。
    - **参数**：`name` 为数据库名称。
    - **返回值**：若成功创建并打开数据库，返回 `true`；否则返回 `false`。
- `int getTotalWordCount(int categoryId = -1)`：获取数据库中单词的总数。
    - **参数**：`categoryId` 为分类 ID，默认为 `-1`，表示不指定分类。
    - **返回值**：返回数据库中符合条件的单词总数。

##### 单词管理
- `bool addWord(const Word &word)`：向数据库中添加新单词。
    - **参数**：`word` 为要添加的单词对象。
    - **返回值**：若添加成功，返回 `true`；否则返回 `false`。
- `bool deleteWord(int id)`：根据单词 ID 删除单词。
    - **参数**：`id` 为要删除的单词 ID。
    - **返回值**：若删除成功，返回 `true`；否则返回 `false`。
- `QVector<Word> getAllWords()`：获取数据库中所有的单词。
    - **返回值**：返回包含所有单词的向量。
- `Word getWordById(int id)`：根据单词 ID 获取单词信息。
    - **参数**：`id` 为要查询的单词 ID。
    - **返回值**：返回对应的单词对象，若未找到则返回空的单词对象。
- `QVector<Word> getWordsByName(const QString &wordName)`：根据单词名称查找单词。
    - **参数**：`wordName` 为要查找的单词名称。
    - **返回值**：返回包含符合条件的单词的向量。
- `QVector<Word> getWordsByCategory(int categoryId)`：获取指定分类下的所有单词。
    - **参数**：`categoryId` 为分类 ID。
    - **返回值**：返回包含指定分类下所有单词的向量。
- `QVector<Word> getWordsToReview(int count = 20, int userId = 1)`：获取需要复习的单词（基于间隔重复算法）。
    - **参数**：`count` 为要获取的单词数量，默认为 20；`userId` 为用户 ID，默认为 1。
    - **返回值**：返回包含需要复习的单词的向量。
- `QVector<Word> getRandomWords(int count, int categoryId = -1)`：从指定分类中随机获取指定数量的单词。
    - **参数**：`count` 为要获取的单词数量；`categoryId` 为分类 ID，默认为 `-1`，表示不指定分类。
    - **返回值**：返回包含随机单词的向量。
- `QVector<Word> getWordsByReviewCount(int maxReviewCount, int count = -1, int categoryId = -1)`：获取复习次数小于等于指定值的单词。
    - **参数**：`maxReviewCount` 为最大复习次数；`count` 为要获取的单词数量，默认为 `-1`，表示不限制数量；`categoryId` 为分类 ID，默认为 `-1`，表示不指定分类。
    - **返回值**：返回包含符合条件的单词的向量。
- `bool updateWordLearningInfo(int wordId, bool correct, int difficultyChange = 0, int userId = 1)`：更新单词学习信息并添加学习记录。
    - **参数**：`wordId` 为单词 ID；`correct` 表示本次学习是否正确；`difficultyChange` 为难度变化值，默认为 0；`userId` 为用户 ID，默认为 1。
    - **返回值**：若更新和添加记录成功，返回 `true`；否则返回 `false`。

##### 分类管理
- `bool addCategory(const Category &category)`：添加新的分类。
    - **参数**：`category` 为要添加的分类对象。
    - **返回值**：若添加成功，返回 `true`；否则返回 `false`。
- `bool deleteCategory(int id)`：根据分类 ID 删除分类。
    - **参数**：`id` 为要删除的分类 ID。
    - **返回值**：若删除成功，返回 `true`；否则返回 `false`。
- `QVector<Category> getAllCategories()`：获取所有的分类。
    - **返回值**：返回包含所有分类的向量。
- `Category getCategoryById(int id)`：根据分类 ID 获取分类信息。
    - **参数**：`id` 为要查询的分类 ID。
    - **返回值**：返回对应的分类对象，若未找到则返回空的分类对象。
- `QVector<Category> getCategoriesByName(const QString &categoryName)`：根据分类名称查找分类。
    - **参数**：`categoryName` 为要查找的分类名称。
    - **返回值**：返回包含符合条件的分类的向量。
- `bool assignWordToCategory(int wordId, int categoryId)`：将单词添加到指定分类中。
    - **参数**：`wordId` 为单词 ID；`categoryId` 为分类 ID。
    - **返回值**：若添加成功，返回 `true`；否则返回 `false`。
- `bool removeWordFromCategory(int wordId, int categoryId)`：将单词从指定分类中移除。
    - **参数**：`wordId` 为单词 ID；`categoryId` 为分类 ID。
    - **返回值**：若移除成功，返回 `true`；否则返回 `false`。

##### 用户管理
- `bool addUser(const QString &username, const QString &password)`：添加新用户。
    - **参数**：`username` 为用户名；`password` 为密码。
    - **返回值**：若添加成功，返回 `true`；否则返回 `false`。
- `bool authenticateUser(const QString &username, const QString &password)`：验证用户的用户名和密码。
    - **参数**：`username` 为用户名；`password` 为密码。
    - **返回值**：若验证成功，返回 `true`；否则返回 `false`。
- `int getUserId(const QString &username)`：根据用户名获取用户 ID。
    - **参数**：`username` 为用户名。
    - **返回值**：返回对应的用户 ID，若未找到则返回 -1。

##### 学习记录管理
- `bool addLearningRecord(const LearningRecord &record)`：添加学习记录。
    - **参数**：`record` 为要添加的学习记录对象。
    - **返回值**：若添加成功，返回 `true`；否则返回 `false`。
- `QVector<LearningRecord> getUserLearningRecords(int days = 30, int userId = 1)`：获取指定用户在指定天数内的学习记录。
    - **参数**：`days` 为天数，默认为 30；`userId` 为用户 ID，默认为 1。
    - **返回值**：返回包含学习记录的向量。
- `double getLearningAccuracy(int days = 30, int userId = 1)`：计算指定用户在指定天数内的学习准确率。
    - **参数**：`days` 为天数，默认为 30；`userId` 为用户 ID，默认为 1。
    - **返回值**：返回学习准确率。
- `int getTotalLearningRecordCount(int days = -1, int userId = 1)`：获取数据库中学习记录的总数。
    - **参数**：`days` 为天数，默认为 `-1`，表示不限制天数；`userId` 为用户 ID，默认为 1。
    - **返回值**：返回符合条件的学习记录总数。
- `bool resetLearningRecords()`：重置学习当前数据库的学习记录。
    - **返回值**：若重置成功，返回 `true`；否则返回 `false`。

##### 工具方法
- `bool createTables()`：创建数据库的表结构。
    - **返回值**：若创建成功，返回 `true`；否则返回 `false`。
- `bool insertSampleData()`：插入示例数据。
    - **返回值**：若插入成功，返回 `true`；否则返回 `false`。
- `static QMap<QString, QString> getpath()`：获取所有数据库文件的路径。
    - **返回值**：返回包含数据库名称和路径的映射。
- `static QVector<QString> getlist()`：获取所有数据库的名称。
    - **返回值**：返回包含所有数据库名称的向量。
- `const QString& getPath()`：获取当前数据库的路径。
    - **返回值**：返回当前数据库的路径。

##### 私有方法
- `bool openDatabase(const QString &dbPath, bool isNew)`：打开数据库。
    - **参数**：`dbPath` 为数据库文件路径；`isNew` 表示是否为新数据库。
    - **返回值**：若成功打开数据库，返回 `true`；否则返回 `false`。
- `bool execSql(const QString &sql)`：执行 SQL 语句。
    - **参数**：`sql` 为要执行的 SQL 语句。
    - **返回值**：若执行成功，返回 `true`；否则返回 `false`。
- `int getOrCreatePartOfSpeech(const QString &posName)`：获取或创建词性。
    - **参数**：`posName` 为词性名称。
    - **返回值**：返回词性的 ID，若失败则返回 -1。
- `bool savePhonetics(int wordId, const QVector<Phonetic> &phonetics)`：保存音标。
    - **参数**：`wordId` 为单词 ID；`phonetics` 为音标向量。
    - **返回值**：若保存成功，返回 `true`；否则返回 `false`。
- `bool saveDefinitions(int wordId, const QMap<QString, QVector<Definition>> &meanings)`：保存释义。
    - **参数**：`wordId` 为单词 ID；`meanings` 为释义映射。
    - **返回值**：若保存成功，返回 `true`；否则返回 `false`。
- `bool loadPhonetics(int wordId, QVector<Phonetic> &phonetics)`：加载音标。
    - **参数**：`wordId` 为单词 ID；`phonetics` 为音标向量。
    - **返回值**：若加载成功，返回 `true`；否则返回 `false`。
- `bool loadDefinitions(int wordId, QMap<QString, QVector<Definition>> &meanings)`：加载释义。
    - **参数**：`wordId` 为单词 ID；`meanings` 为释义映射。
    - **返回值**：若加载成功，返回 `true`；否则返回 `false`。
- `bool createWordTable()`：创建单词表。
    - **返回值**：若创建成功，返回 `true`；否则返回 `false`。
- `bool createCategoryTable()`：创建分类表。
    - **返回值**：若创建成功，返回 `true`；否则返回 `false`。
- `bool createUserTable()`：创建用户表。
    - **返回值**：若创建成功，返回 `true`；否则返回 `false`。
- `bool createLearningRecordTable()`：创建学习记录表。
    - **返回值**：若创建成功，返回 `true`；否则返回 `false`。
- `bool createWordCategoryTable()`：创建单词 - 分类关联表。
    - **返回值**：若创建成功，返回 `true`；否则返回 `false`。
- `bool createPhoneticsTable()`：创建音标表。
    - **返回值**：若创建成功，返回 `true`；否则返回 `false`。
- `bool createPartsOfSpeechTable()`：创建词性表。
    - **返回值**：若创建成功，返回 `true`；否则返回 `false`。
- `bool createDefinitionsTable()`：创建释义表。
    - **返回值**：若创建成功，返回 `true`；否则返回 `false`。
- `bool createSynonymsTable()`：创建同义词表。
    - **返回值**：若创建成功，返回 `true`；否则返回 `false`。
- `bool createAntonymsTable()`：创建反义词表。
    - **返回值**：若创建成功，返回 `true`；否则返回 `false`。