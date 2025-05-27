#include "../back_head/database.h"

WordDatabase::WordDatabase()
{
    QString dataDir = QCoreApplication::applicationDirPath() + "/datas/";
    QDir dir(dataDir);
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            qFatal("无法创建数据目录2!");
        }
    }
}

WordDatabase::~WordDatabase()
{
    if (m_db.isOpen()) {
        m_db.close();
    }
}

bool WordDatabase::isOpen() const {
    return m_db.isOpen();
}
void WordDatabase::close() {
    if (m_db.isOpen()) {
        m_db.close();
    }
}

bool WordDatabase::initDatabase(const QString &name) // 创建链接，打开已有数据库
{
    m_connectionName=name;
    const QString dbPath = QCoreApplication::applicationDirPath() +"/datas/"+ name +".db";
    QFileInfo fileInfo(dbPath);
    if (!fileInfo.exists() || !fileInfo.isFile()) {
        qInfo() << "指定的数据库文件不存在:" << dbPath;
        return false;
    }

    Path=dbPath;

    if (!openDatabase(Path, false)) { // 新建数据库并创建表
        return false;
    }

    qInfo()<<"加载数据库成功\n";

    // 测试用，测试完成后注释掉
    insertSampleData();
    // 测试用，测试完成后注释掉

    return true;
}

bool WordDatabase::NewDatabase(const QString &name) // 创建链接，创建新的数据库
{
    m_connectionName=name;
    QString dataDir = QCoreApplication::applicationDirPath() + "/datas/";
    QString dbPath = dataDir + name + ".db";
    QFileInfo fileInfo(dbPath);
    QDir dir(fileInfo.absolutePath()); // 获取目录部分（dataDir）

    if (!dir.exists() && !dir.mkpath(".")) {
        qFatal("无法创建数据目录: %s", qPrintable(dir.path()));
        return false;
    }
    Path=dbPath;

    if (!openDatabase(Path, true)) { // 新建数据库并创建表
        return false;
    }
    qInfo()<<"新建数据库成功\n";

    insertSampleData(); // 仅在新建时插入示例数据
    return true;
}

bool WordDatabase::openDatabase(const QString &dbPath, bool isNew) {
    if (QSqlDatabase::contains(m_connectionName)) {
        QSqlDatabase::removeDatabase(m_connectionName);
    }

    m_db = QSqlDatabase::addDatabase("QSQLITE", m_connectionName);
    m_db.setDatabaseName(dbPath);

    if (!m_db.open()) {
        qDebug() << "无法打开数据库:" << m_db.lastError().text();
        return false;
    }

    if (isNew) { // 新建数据库时创建表和索引
        if (!createTables()) {
            m_db.close();
            return false;
        }
    }
    return true;
}

bool WordDatabase::createTables()
{
    if (!createWordTable() || 
        !createCategoryTable() || 
        !createUserTable() || 
        !createLearningRecordTable() || 
        !createWordCategoryTable()) {
        return false;
    }

    // 创建索引
    QSqlQuery query(m_db);
    query.exec("CREATE INDEX IF NOT EXISTS idx_words_word ON Words (word)");
    query.exec("CREATE INDEX IF NOT EXISTS idx_categories_name ON Categories (name)");
    query.exec("CREATE INDEX IF NOT EXISTS idx_users_username ON Users (username)");

    return true;
}

bool WordDatabase::createWordTable()
{
    QSqlQuery query(m_db); // 指定使用m_db连接;
    return query.exec(
        "CREATE TABLE IF NOT EXISTS Words ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "word TEXT NOT NULL, "
        "pronunciation TEXT, "
        "meaning TEXT NOT NULL, "
        "example TEXT, "
        "last_reviewed DATETIME, "
        "review_count INTEGER DEFAULT 0, "
        "difficulty INTEGER DEFAULT 3"
        ")"
    );
}

bool WordDatabase::createCategoryTable()
{
    QSqlQuery query(m_db); // 指定使用m_db连接
    return query.exec(
        "CREATE TABLE IF NOT EXISTS Categories ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "description TEXT"
        ")"
    );
}

bool WordDatabase::createUserTable()
{
    QSqlQuery query(m_db); // 指定使用m_db连接
    return query.exec(
        "CREATE TABLE IF NOT EXISTS Users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "username TEXT UNIQUE NOT NULL, "
        "password TEXT NOT NULL"
        ")"
    );
}

bool WordDatabase::createLearningRecordTable()
{
    QSqlQuery query(m_db); // 指定使用m_db连接
    return query.exec(
        "CREATE TABLE IF NOT EXISTS LearningRecords ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "word_id INTEGER NOT NULL, "
        "user_id INTEGER NOT NULL, "
        "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP, "
        "correct BOOLEAN NOT NULL, "
        "difficulty INTEGER NOT NULL, "
        "FOREIGN KEY (word_id) REFERENCES Words(id), "
        "FOREIGN KEY (user_id) REFERENCES Users(id)"
        ")"
    );
}

bool WordDatabase::createWordCategoryTable()
{
    QSqlQuery query(m_db); // 指定使用m_db连接
    return query.exec(
        "CREATE TABLE IF NOT EXISTS WordCategories ("
        "word_id INTEGER NOT NULL, "
        "category_id INTEGER NOT NULL, "
        "PRIMARY KEY (word_id, category_id), "
        "FOREIGN KEY (word_id) REFERENCES Words(id), "
        "FOREIGN KEY (category_id) REFERENCES Categories(id)"
        ")"
    );
}

bool WordDatabase::addWord(const Word &word)
{
    QSqlQuery query(m_db);
    query.prepare(
        "INSERT INTO Words (word, pronunciation, meaning, example, last_reviewed, review_count, difficulty) "
        "VALUES (:word, :pronunciation, :meaning, :example, :last_reviewed, :review_count, :difficulty)"
    );
    query.bindValue(":word", word.word);
    query.bindValue(":pronunciation", word.pronunciation);
    query.bindValue(":meaning", word.meaning);
    query.bindValue(":example", word.example);
    query.bindValue(":last_reviewed", word.lastReviewed);
    query.bindValue(":review_count", word.reviewCount);
    query.bindValue(":difficulty", word.difficulty);
    
    return query.exec();
}

bool WordDatabase::addCategory(const Category &category)
{
    QSqlQuery query(m_db);
    query.prepare(
        "INSERT INTO Categories (name, description) "
        "VALUES (:name, :description)"
    );
    query.bindValue(":name", category.name);
    query.bindValue(":description", category.description);
    
    return query.exec();
}

QVector<Word> WordDatabase::getWordsByName(const QString &wordName)
{
    QVector<Word> words;
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM Words WHERE word = :word");
    query.bindValue(":word", wordName);

    if (query.exec()) {
        while (query.next()) {
            Word word;
            word.id = query.value("id").toInt();
            word.word = query.value("word").toString();
            word.pronunciation = query.value("pronunciation").toString();
            word.meaning = query.value("meaning").toString();
            word.example = query.value("example").toString();
            word.lastReviewed = query.value("last_reviewed").toDateTime();
            word.reviewCount = query.value("review_count").toInt();
            word.difficulty = query.value("difficulty").toInt();
            words.append(word);
        }
    }
    return words;
}

QVector<Category> WordDatabase::getCategoriesByName(const QString &categoryName)
{
    QVector<Category> categories;
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM Categories WHERE name = :name");
    query.bindValue(":name", categoryName);

    if (query.exec()) {
        while (query.next()) {
            Category category;
            category.id = query.value("id").toInt();
            category.name = query.value("name").toString();
            category.description = query.value("description").toString();
            categories.append(category);
        }
    }

    return categories;
}

// ??? 是否应该在这里实现存疑
bool WordDatabase::addUser(const QString &username, const QString &password)
{
    QSqlQuery query(m_db);
    query.prepare(
        "INSERT INTO Users (username, password) "
        "VALUES (:username, :password)"
    );
    query.bindValue(":username", username);
    query.bindValue(":password", password); // 实际应用中应加密存储
    
    return query.exec();
}
// ???

bool WordDatabase::authenticateUser(const QString &username, const QString &password)
{
    QSqlQuery query(m_db);
    query.prepare(
        "SELECT id FROM Users WHERE username = :username AND password = :password"
    );
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    
    if (query.exec() && query.next()) {
        return true;
    }
    return false;
}

int WordDatabase::getUserId(const QString &username)
{
    QSqlQuery query(m_db);
    query.prepare("SELECT id FROM Users WHERE username = :username");
    query.bindValue(":username", username);
    
    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return -1;
}

bool WordDatabase::addLearningRecord(const LearningRecord &record)
{
    QSqlQuery query(m_db);
    query.prepare(
        "INSERT INTO LearningRecords (word_id, user_id, correct, difficulty) "
        "VALUES (:word_id, :user_id, :correct, :difficulty)"
    );
    query.bindValue(":word_id", record.wordId);
    query.bindValue(":user_id", record.userId);
    query.bindValue(":correct", record.correct);
    query.bindValue(":difficulty", record.difficulty);
    
    if (query.exec()) {
        // 更新单词的最后复习时间和复习次数
        QSqlQuery updateQuery;
        updateQuery.prepare(
            "UPDATE Words SET last_reviewed = CURRENT_TIMESTAMP, "
            "review_count = review_count + 1 "
            "WHERE id = :word_id"
        );
        updateQuery.bindValue(":word_id", record.wordId);
        return updateQuery.exec();
    }
    return false;
}

QVector<Word> WordDatabase::getAllWords()
{
    QVector<Word> words;
    QSqlQuery query(m_db);
    query.exec("SELECT * FROM Words");

    while (query.next()) {
        Word word;
        word.id = query.value("id").toInt();
        word.word = query.value("word").toString();
        word.pronunciation = query.value("pronunciation").toString();
        word.meaning = query.value("meaning").toString();
        word.example = query.value("example").toString();
        word.lastReviewed = query.value("last_reviewed").toDateTime();
        word.reviewCount = query.value("review_count").toInt();
        word.difficulty = query.value("difficulty").toInt();
        words.append(word);
    }
    
    return words;
}

QVector<Category> WordDatabase::getAllCategories()
{
    QVector<Category> categories;

    // 显式使用当前数据库连接（m_db）
    QSqlQuery query(m_db);

    // 执行查询
    if (!query.exec("SELECT * FROM Categories")) {
        qWarning() << "查询分类失败:" << query.lastError().text();
        return categories; // 返回空向量表示失败
    }

    // 遍历结果集
    while (query.next()) {
        Category category;
        category.id = query.value("id").toInt();
        category.name = query.value("name").toString();
        category.description = query.value("description").toString();
        categories.append(category);
    }

    return categories;
}

Category WordDatabase::getCategoryById(int id)
{
    Category category;
    QSqlQuery query(m_db);

    // 准备SQL查询
    query.prepare("SELECT id, name, description FROM Categories WHERE id = :id");
    query.bindValue(":id", id);

    // 执行查询
    if (!query.exec()) {
        qWarning() << "查询分类失败:" << query.lastError().text();
        return category; // 返回空对象
    }

    // 检查是否有结果
    if (query.next()) {
        // 从查询结果中提取数据
        category.id = query.value("id").toInt();
        category.name = query.value("name").toString();
        category.description = query.value("description").toString();
    } else {
        qWarning() << "未找到ID为" << id << "的分类";
    }

    return category;
}

bool WordDatabase::assignWordToCategory(int wordId, int categoryId)
{
    QSqlQuery query(m_db);
    query.prepare(
        "INSERT INTO WordCategories (word_id, category_id) "
        "VALUES (:word_id, :category_id)"
    );
    query.bindValue(":word_id", wordId);
    query.bindValue(":category_id", categoryId);
    
    return query.exec();
}

QVector<Word> WordDatabase::getWordsByCategory(int categoryId)
{
    QVector<Word> words;
    QSqlQuery query(m_db);
    query.prepare(
        "SELECT w.* FROM Words w "
        "JOIN WordCategories wc ON w.id = wc.word_id "
        "WHERE wc.category_id = :category_id"
    );
    query.bindValue(":category_id", categoryId);
    
    if (query.exec()) {
        while (query.next()) {
            Word word;
            word.id = query.value("id").toInt();
            word.word = query.value("word").toString();
            word.pronunciation = query.value("pronunciation").toString();
            word.meaning = query.value("meaning").toString();
            word.example = query.value("example").toString();
            word.lastReviewed = query.value("last_reviewed").toDateTime();
            word.reviewCount = query.value("review_count").toInt();
            word.difficulty = query.value("difficulty").toInt();
            words.append(word);
        }
    }
    
    return words;
}

QVector<Word> WordDatabase::getWordsToReview(int userId, int count)
{
    QVector<Word> words;
    
    // 这里实现一个简单的复习算法：
    // 1. 优先复习未复习过的单词
    // 2. 其次复习难度较高的单词
    // 3. 最后复习最近未复习的单词
    
    QSqlQuery query(m_db);
    query.prepare(
        "SELECT w.* FROM Words w "
        "LEFT JOIN (SELECT word_id FROM LearningRecords WHERE user_id = :user_id) lr "
        "ON w.id = lr.word_id "
        "WHERE lr.word_id IS NULL "  // 未复习过的单词
        "ORDER BY RANDOM() "
        "LIMIT :count/2"
    );
    query.bindValue(":user_id", userId);
    query.bindValue(":count", count);
    
    if (query.exec()) {
        while (query.next()) {
            Word word;
            word.id = query.value("id").toInt();
            word.word = query.value("word").toString();
            word.pronunciation = query.value("pronunciation").toString();
            word.meaning = query.value("meaning").toString();
            word.example = query.value("example").toString();
            word.lastReviewed = query.value("last_reviewed").toDateTime();
            word.reviewCount = query.value("review_count").toInt();
            word.difficulty = query.value("difficulty").toInt();
            words.append(word);
        }
    }
    
    // 如果未复习的单词不够，补充一些需要复习的单词
    if (words.size() < count) {
        QSqlQuery query2(m_db);
        query2.prepare(
            "SELECT w.* FROM Words w "
            "JOIN LearningRecords lr ON w.id = lr.word_id "
            "WHERE lr.user_id = :user_id "
            "GROUP BY w.id "
            "ORDER BY "
            "  CASE WHEN w.difficulty >= 4 THEN 0 ELSE 1 END, "  // 优先难度高的
            "  w.last_reviewed ASC "  // 优先最近未复习的
            "LIMIT :remaining_count"
        );
        query2.bindValue(":user_id", userId);
        query2.bindValue(":remaining_count", count - words.size());
        
        if (query2.exec()) {
            while (query2.next()) {
                Word word;
                word.id = query2.value("id").toInt();
                word.word = query2.value("word").toString();
                word.pronunciation = query2.value("pronunciation").toString();
                word.meaning = query2.value("meaning").toString();
                word.example = query2.value("example").toString();
                word.lastReviewed = query2.value("last_reviewed").toDateTime();
                word.reviewCount = query2.value("review_count").toInt();
                word.difficulty = query2.value("difficulty").toInt();
                words.append(word);
            }
        }
    }
    
    return words;
}

double WordDatabase::getLearningAccuracy(int userId, int days)
{
    QSqlQuery query(m_db);
    query.prepare(
        "SELECT AVG(correct) FROM LearningRecords "
        "WHERE user_id = :user_id "
        "AND timestamp >= DATE('now', :days || ' day')"
    );
    query.bindValue(":user_id", userId);
    query.bindValue(":days", -days);
    
    if (query.exec() && query.next()) {
        return query.value(0).toDouble() * 100.0; // 转换为百分比
    }
    return 0.0;
}

// 根据ID删除单词
bool WordDatabase::deleteWord(int id)
{
    QSqlQuery query(m_db);

    // 首先检查单词是否存在
    query.prepare("SELECT id FROM Words WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec() || !query.next()) {
        qWarning() << "删除单词失败: 未找到ID为" << id << "的单词";
        return false;
    }

    // 开始事务
    m_db.transaction();

    // 1. 删除单词-分类关联
    query.prepare("DELETE FROM WordCategories WHERE word_id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        m_db.rollback();
        qWarning() << "删除单词分类关联失败:" << query.lastError().text();
        return false;
    }

    // 2. 删除学习记录
    query.prepare("DELETE FROM LearningRecords WHERE word_id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        m_db.rollback();
        qWarning() << "删除学习记录失败:" << query.lastError().text();
        return false;
    }

    // 3. 删除单词本身
    query.prepare("DELETE FROM Words WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        m_db.rollback();
        qWarning() << "删除单词失败:" << query.lastError().text();
        return false;
    }

    // 提交事务
    if (!m_db.commit()) {
        qWarning() << "提交事务失败:" << m_db.lastError().text();
        return false;
    }

    qInfo() << "成功删除单词，ID:" << id;
    return true;
}

// 根据ID获取单词
Word WordDatabase::getWordById(int id)
{
    Word word;
    QSqlQuery query(m_db);

    query.prepare(
        "SELECT id, word, pronunciation, meaning, example, last_reviewed, review_count, difficulty "
        "FROM Words WHERE id = :id"
        );
    query.bindValue(":id", id);

    if (!query.exec()) {
        qWarning() << "查询单词失败:" << query.lastError().text();
        return word;
    }

    if (query.next()) {
        word.id = query.value("id").toInt();
        word.word = query.value("word").toString();
        word.pronunciation = query.value("pronunciation").toString();
        word.meaning = query.value("meaning").toString();
        word.example = query.value("example").toString();
        word.lastReviewed = query.value("last_reviewed").toDateTime();
        word.reviewCount = query.value("review_count").toInt();
        word.difficulty = query.value("difficulty").toInt();
    } else {
        qWarning() << "未找到ID为" << id << "的单词";
    }

    return word;
}

// 删除分类
bool WordDatabase::deleteCategory(int id)
{
    QSqlQuery query(m_db);

    // 检查分类是否存在
    query.prepare("SELECT id FROM Categories WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec() || !query.next()) {
        qWarning() << "删除分类失败: 未找到ID为" << id << "的分类";
        return false;
    }

    // 开始事务
    m_db.transaction();

    // 1. 删除单词-分类关联
    query.prepare("DELETE FROM WordCategories WHERE category_id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        m_db.rollback();
        qWarning() << "删除单词分类关联失败:" << query.lastError().text();
        return false;
    }

    // 2. 删除分类
    query.prepare("DELETE FROM Categories WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        m_db.rollback();
        qWarning() << "删除分类失败:" << query.lastError().text();
        return false;
    }

    // 提交事务
    if (!m_db.commit()) {
        qWarning() << "提交事务失败:" << m_db.lastError().text();
        return false;
    }

    qInfo() << "成功删除分类，ID:" << id;
    return true;
}

// 从分类中移除单词
bool WordDatabase::removeWordFromCategory(int wordId, int categoryId)
{
    QSqlQuery query(m_db);

    // 检查关联是否存在
    query.prepare(
        "SELECT word_id FROM WordCategories "
        "WHERE word_id = :wordId AND category_id = :categoryId"
        );
    query.bindValue(":wordId", wordId);
    query.bindValue(":categoryId", categoryId);

    if (!query.exec() || !query.next()) {
        qWarning() << "移除单词分类关联失败: 未找到关联 (wordId=" << wordId
                   << ", categoryId=" << categoryId << ")";
        return false;
    }

    // 删除关联
    query.prepare(
        "DELETE FROM WordCategories "
        "WHERE word_id = :wordId AND category_id = :categoryId"
        );
    query.bindValue(":wordId", wordId);
    query.bindValue(":categoryId", categoryId);

    if (!query.exec()) {
        qWarning() << "移除单词分类关联失败:" << query.lastError().text();
        return false;
    }

    qInfo() << "成功从分类中移除单词 (wordId=" << wordId
            << ", categoryId=" << categoryId << ")";
    return true;
}

QMap<QString, QString> WordDatabase::getpath()
{
    QMap<QString, QString> dbPaths;
    QDir dataDir(QCoreApplication::applicationDirPath() + "/datas");

    if (!dataDir.exists()) {
        qWarning() << "数据目录不存在:" << dataDir.path();
        return dbPaths;
    }

    // 获取所有.db文件
    QStringList filters;
    filters << "*.db";
    QFileInfoList files = dataDir.entryInfoList(filters, QDir::Files);

    // 构建数据库名称到路径的映射
    for (const QFileInfo &file : files) {
        QString dbName = file.baseName();  // 文件名（不含扩展名）
        QString dbPath = file.absoluteFilePath();
        dbPaths.insert(dbName, dbPath);
    }

    return dbPaths;
}

QVector<QString> WordDatabase::getlist()
{
    QVector<QString> dbNames;
    QDir dataDir(QCoreApplication::applicationDirPath() + "/datas");

    if (!dataDir.exists()) {
        qWarning() << "数据目录不存在:" << dataDir.path();
        return dbNames;
    }

    // 获取所有.db文件
    QStringList filters;
    filters << "*.db";
    QStringList files = dataDir.entryList(filters, QDir::Files);

    // 提取数据库名称（不含扩展名）
    for (const QString &fileName : files) {
        dbNames.append(fileName.left(fileName.lastIndexOf('.')));
    }

    return dbNames;
}

bool WordDatabase::insertSampleData() // 测试用
{
    // 添加示例分类并获取分类ID
    int category1Id = 1, category2Id = 2, category3Id = 3;

    {
        Category category;
        category.name = "基础词汇";
        category.description = "日常生活中常用的基础单词";

        if (addCategory(category)) {

         }
    }

    {
        Category category;
        category.name = "学术词汇";
        category.description = "学术领域中使用的专业词汇";
        if (addCategory(category)) {

        }
    }

    {
        Category category;
        category.name = "商务词汇";
        category.description = "商务场景中使用的专业词汇";

        if (addCategory(category)) {

        }
    }

    // 添加示例单词并获取单词ID
    int word1Id = 1, word2Id = 2, word3Id = 3;

    {
        Word word;
        word.word = "apple";
        word.pronunciation = "/ˈæpl/";
        word.meaning = "苹果";
        word.example = "I like to eat apples in the morning.";
        word.difficulty = 1;

        if (addWord(word)) {

        }
    }

    {
        Word word;
        word.word = "abstraction";
        word.pronunciation = "/æbˈstrækʃn/";
        word.meaning = "抽象；抽象概念";
        word.example = "In computer science, abstraction is a key concept.";
        word.difficulty = 4;
        QSqlQuery query;
        if (addWord(word)) {

        }
    }

    {
        Word word;
        word.word = "negotiation";
        word.pronunciation = "/nɪˌɡəʊʃiˈeɪʃn/";
        word.meaning = "谈判；协商";
        word.example = "We had a successful negotiation with the client.";
        word.difficulty = 3;
        QSqlQuery query;
        if (addWord(word)) {

        }
    }

    // 分配单词到分类
    if (word1Id > 0 && category1Id > 0) assignWordToCategory(word1Id, category1Id);
    if (word2Id > 0 && category2Id > 0) assignWordToCategory(word2Id, category2Id);
    if (word3Id > 0 && category3Id > 0) assignWordToCategory(word3Id, category3Id);

    // 添加示例用户
    addUser("user1", "password1");

    return true;
}


