#include "../back_head/database.h"


WordDatabase::WordDatabase() {
    QString dataDir = QCoreApplication::applicationDirPath() + "/datas/";
    QDir dir(dataDir);
    if (!dir.exists()) dir.mkpath(".");

}

WordDatabase::~WordDatabase() {
    if (m_db.isOpen()) m_db.close();
}

bool WordDatabase::isOpen() const {
    return m_db.isOpen();
}

void WordDatabase::close() {
    m_db.close();
}

// bool WordDatabase::initDatabase(const QString &name) {
//     m_connectionName = name;
//     QString dbPath = QCoreApplication::applicationDirPath() + "/datas/" + name + ".db";
//     if (!QFile::exists(dbPath)) {
//         qInfo() << "数据库文件不存在:" << dbPath;
//         return false;
//     }
//     Path = dbPath;
//     return openDatabase(Path, false);
// }

// bool WordDatabase::NewDatabase(const QString &name) {
//     m_connectionName = name;
//     QString dbPath = QCoreApplication::applicationDirPath() + "/datas/" + name + ".db";
//     Path = dbPath;
//     insertSampleData();
//     return openDatabase(Path, true);
// }

// bool WordDatabase::openDatabase(const QString &dbPath, bool isNew) {
//     if (QSqlDatabase::contains(m_connectionName))
//         QSqlDatabase::removeDatabase(m_connectionName);

//     m_db = QSqlDatabase::addDatabase("QSQLITE", m_connectionName);
//     m_db.setDatabaseName(dbPath);

//     if (!m_db.open()) {
//         qDebug() << "打开数据库失败:" << m_db.lastError().text();
//         return false;
//     }

//     if (isNew && !createTables()) {
//         m_db.close();
//         return false;
//     }
//     return true;
// }

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
    // insertSampleData();
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

    // insertSampleData(); // 仅在新建时插入示例数据

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

bool WordDatabase::execSql(const QString &sql) {
    QSqlQuery query(m_db);
    if (!query.exec(sql)) {
        qWarning() << "SQL执行失败:" << query.lastError().text() << "\nSQL:" << sql;
        return false;
    }

    return true;
}

bool WordDatabase::createTables() {
    if (!createWordTable() || !createCategoryTable() || !createUserTable() ||
        !createLearningRecordTable() || !createWordCategoryTable() ||
        !createPhoneticsTable() || !createPartsOfSpeechTable() ||
        !createDefinitionsTable() || !createSynonymsTable() ||
        !createAntonymsTable()) {
        return false;
    }

    // 创建索引
    QSqlQuery query(m_db);
    query.exec("CREATE UNIQUE INDEX IF NOT EXISTS idx_words_word ON Words(word)");
    query.exec("CREATE INDEX IF NOT EXISTS idx_phonetics_word_id ON Phonetics(word_id)");
    query.exec("CREATE INDEX IF NOT EXISTS idx_definitions_word_id ON Definitions(word_id)");
    query.exec("CREATE INDEX IF NOT EXISTS idx_definitions_pos_id ON Definitions(pos_id)");
    query.exec("CREATE INDEX IF NOT EXISTS idx_categories_name ON Categories(name)");
    return true;
}

bool WordDatabase::createWordTable() {
    return execSql("CREATE TABLE IF NOT EXISTS Words ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "word TEXT NOT NULL UNIQUE, "
                   "last_reviewed DATETIME, "
                   "review_count INTEGER DEFAULT 0, "
                   "difficulty INTEGER DEFAULT 3"
                   ")");
}

bool WordDatabase::createCategoryTable() {
    return execSql("CREATE TABLE IF NOT EXISTS Categories ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "name TEXT NOT NULL, "
                   "description TEXT"
                   ")");
}

bool WordDatabase::createUserTable() {
    return execSql("CREATE TABLE IF NOT EXISTS Users ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "username TEXT NOT NULL UNIQUE, "
                   "password TEXT NOT NULL"
                   ")");
}

bool WordDatabase::createLearningRecordTable() {
    return execSql("CREATE TABLE IF NOT EXISTS LearningRecords ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "word_id INTEGER NOT NULL, "
                   "user_id INTEGER NOT NULL, "
                   "timestamp DATETIME NOT NULL, "
                   "correct BOOLEAN NOT NULL, "
                   "difficulty INTEGER, "
                   "FOREIGN KEY(word_id) REFERENCES Words(id) ON DELETE CASCADE, "
                   "FOREIGN KEY(user_id) REFERENCES Users(id) ON DELETE CASCADE"
                   ")");
}

bool WordDatabase::createWordCategoryTable() {
    return execSql("CREATE TABLE IF NOT EXISTS WordCategories ("
                   "word_id INTEGER NOT NULL, "
                   "category_id INTEGER NOT NULL, "
                   "PRIMARY KEY(word_id, category_id), "
                   "FOREIGN KEY(word_id) REFERENCES Words(id) ON DELETE CASCADE, "
                   "FOREIGN KEY(category_id) REFERENCES Categories(id) ON DELETE CASCADE"
                   ")");
}

bool WordDatabase::createPhoneticsTable() {
    return execSql("CREATE TABLE IF NOT EXISTS Phonetics ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "word_id INTEGER NOT NULL, "
                   "text TEXT, "
                   "audio TEXT, "
                   "FOREIGN KEY(word_id) REFERENCES Words(id) ON DELETE CASCADE"
                   ")");
}

bool WordDatabase::createPartsOfSpeechTable() {
    return execSql("CREATE TABLE IF NOT EXISTS PartsOfSpeech ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "name TEXT NOT NULL UNIQUE"
                   ")");
}

bool WordDatabase::createDefinitionsTable() {
    return execSql("CREATE TABLE IF NOT EXISTS Definitions ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "word_id INTEGER NOT NULL, "
                   "pos_id INTEGER NOT NULL, "
                   "definition TEXT NOT NULL, "
                   "example TEXT, "
                   "FOREIGN KEY(word_id) REFERENCES Words(id) ON DELETE CASCADE, "
                   "FOREIGN KEY(pos_id) REFERENCES PartsOfSpeech(id)"
                   ")");
}

bool WordDatabase::createSynonymsTable() {
    return execSql("CREATE TABLE IF NOT EXISTS Synonyms ("
                   "definition_id INTEGER NOT NULL, "
                   "term TEXT NOT NULL, "
                   "FOREIGN KEY(definition_id) REFERENCES Definitions(id) ON DELETE CASCADE, "
                   "PRIMARY KEY(definition_id, term)"
                   ")");
}

bool WordDatabase::createAntonymsTable() {
    return execSql("CREATE TABLE IF NOT EXISTS Antonyms ("
                   "definition_id INTEGER NOT NULL, "
                   "term TEXT NOT NULL, "
                   "FOREIGN KEY(definition_id) REFERENCES Definitions(id) ON DELETE CASCADE, "
                   "PRIMARY KEY(definition_id, term)"
                   ")");
}

// -------------------- 单词管理方法 --------------------
bool WordDatabase::addWord(const Word &word) {
    if (word.word.isEmpty()) return false;

    // 1. 插入主表
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO Words (word, last_reviewed, review_count, difficulty) "
                  "VALUES (:word, :last_reviewed, :review_count, :difficulty)");
    query.bindValue(":word", word.word);
    query.bindValue(":last_reviewed", word.lastReviewed);
    query.bindValue(":review_count", word.reviewCount);
    query.bindValue(":difficulty", word.difficulty);
    if (!query.exec()) return false;
    int wordId = query.lastInsertId().toInt();

    // 2. 插入音标（事务保证一致性）
    m_db.transaction();
    if (!savePhonetics(wordId, word.phonetics)) {
        m_db.rollback();
        return false;
    }

    // 3. 插入释义及关联数据
    if (!saveDefinitions(wordId, word.meanings)) {
        m_db.rollback();
        return false;
    }

    return m_db.commit();
}

bool WordDatabase::savePhonetics(int wordId, const QVector<Phonetic> &phonetics) {
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO Phonetics (word_id, text, audio) VALUES (:word_id, :text, :audio)");
    for (const Phonetic &ph : phonetics) {
        query.bindValue(":word_id", wordId);
        query.bindValue(":text", ph.text);
        query.bindValue(":audio", ph.audio);
        if (!query.exec()) return false;
    }
    return true;
}

bool WordDatabase::saveDefinitions(int wordId, const QMap<QString, QVector<Definition>> &meanings) {
    QSqlQuery query(m_db);
    for (const QString &pos : meanings.keys()) {
        int posId = getOrCreatePartOfSpeech(pos);
        if (posId == -1) return false;

        for (const Definition &def : meanings.value(pos)) {
            // 插入释义
            query.prepare("INSERT INTO Definitions (word_id, pos_id, definition, example) "
                          "VALUES (:word_id, :pos_id, :definition, :example)");
            query.bindValue(":word_id", wordId);
            query.bindValue(":pos_id", posId);
            query.bindValue(":definition", def.definition);
            query.bindValue(":example", def.example);
            if (!query.exec()) return false;
            int defId = query.lastInsertId().toInt();

            // 插入同义词
            for (const QString &syn : def.synonyms) {
                query.prepare("INSERT OR IGNORE INTO Synonyms (definition_id, term) VALUES (:def_id, :term)");
                query.bindValue(":def_id", defId);
                query.bindValue(":term", syn);
                if (!query.exec()) return false;
            }

            // 插入反义词
            for (const QString &ant : def.antonyms) {
                query.prepare("INSERT OR IGNORE INTO Antonyms (definition_id, term) VALUES (:def_id, :term)");
                query.bindValue(":def_id", defId);
                query.bindValue(":term", ant);
                if (!query.exec()) return false;
            }
        }
    }
    return true;
}

int WordDatabase::getOrCreatePartOfSpeech(const QString &posName) {
    QSqlQuery query(m_db);
    query.prepare("SELECT id FROM PartsOfSpeech WHERE name = :name");
    query.bindValue(":name", posName);
    if (query.exec() && query.next()) return query.value(0).toInt();

    query.prepare("INSERT INTO PartsOfSpeech (name) VALUES (:name)");
    query.bindValue(":name", posName);
    if (query.exec()) return query.lastInsertId().toInt();

    // 尝试再次查询（可能是并发插入导致）
    query.prepare("SELECT id FROM PartsOfSpeech WHERE name = :name");
    query.bindValue(":name", posName);
    if (query.exec() && query.next()) return query.value(0).toInt();

    return -1;
}

Word WordDatabase::getWordById(int id) {
    Word word;
    // 1. 查询主表
    QSqlQuery query(m_db);
    query.prepare("SELECT id, word, last_reviewed, review_count, difficulty "
                  "FROM Words WHERE id = :id");
    query.bindValue(":id", id);
    if (!query.exec() || !query.next()) return word;
    word.id = id;
    word.word = query.value("word").toString();
    word.lastReviewed = query.value("last_reviewed").toDateTime();
    word.reviewCount = query.value("review_count").toInt();
    word.difficulty = query.value("difficulty").toInt();

    // 2. 加载音标
    loadPhonetics(id, word.phonetics);

    // 3. 加载释义及关联数据
    loadDefinitions(id, word.meanings);

    return word;
}

bool WordDatabase::loadPhonetics(int wordId, QVector<Phonetic> &phonetics) {
    QSqlQuery query(m_db);
    query.prepare("SELECT text, audio FROM Phonetics WHERE word_id = :word_id");
    query.bindValue(":word_id", wordId);
    if (!query.exec()) return false;

    phonetics.clear();
    while (query.next()) {
        Phonetic ph;
        ph.text = query.value("text").toString();
        ph.audio = query.value("audio").toString();
        phonetics.append(ph);
    }
    return true;
}

bool WordDatabase::loadDefinitions(int wordId, QMap<QString, QVector<Definition>> &meanings) {
    QSqlQuery query(m_db);
    query.prepare(
        "SELECT d.id, pos.name AS pos, d.definition, d.example "
        "FROM Definitions d "
        "JOIN PartsOfSpeech pos ON d.pos_id = pos.id "
        "WHERE d.word_id = :word_id"
        );
    query.bindValue(":word_id", wordId);
    if (!query.exec()) return false;

    QMap<int, Definition> defMap; // 存储definition_id到Definition的映射
    QMap<int, QString> posMap;    // 存储definition_id到词性的映射

    // 先加载基本释义
    while (query.next()) {
        int defId = query.value("id").toInt();
        QString pos = query.value("pos").toString();
        QString defText = query.value("definition").toString();
        QString example = query.value("example").toString();

        Definition def;
        def.definition = defText;
        def.example = example;

        defMap[defId] = def;
        posMap[defId] = pos;

        if (!meanings.contains(pos)) {
            meanings[pos] = QVector<Definition>();
        }
    }

    // 加载同义词
    query.prepare("SELECT definition_id, term FROM Synonyms WHERE definition_id IN (SELECT id FROM Definitions WHERE word_id = :word_id)");
    query.bindValue(":word_id", wordId);
    if (query.exec()) {
        while (query.next()) {
            int defId = query.value("definition_id").toInt();
            QString syn = query.value("term").toString();

            if (defMap.contains(defId)) {
                defMap[defId].synonyms.append(syn);
            }
        }
    }

    // 加载反义词
    query.prepare("SELECT definition_id, term FROM Antonyms WHERE definition_id IN (SELECT id FROM Definitions WHERE word_id = :word_id)");
    query.bindValue(":word_id", wordId);
    if (query.exec()) {
        while (query.next()) {
            int defId = query.value("definition_id").toInt();
            QString ant = query.value("term").toString();

            if (defMap.contains(defId)) {
                defMap[defId].antonyms.append(ant);
            }
        }
    }

    // 将所有释义添加到结果中
    for (auto it = defMap.begin(); it != defMap.end(); ++it) {
        int defId = it.key();
        QString pos = posMap[defId];
        Definition def = it.value();

        // 使用标准库容器去重（跨Qt版本兼容）
        std::set<QString> uniqueSynonyms(def.synonyms.begin(), def.synonyms.end());
        def.synonyms.clear();
        def.synonyms.reserve(uniqueSynonyms.size());
        for (const QString &syn : uniqueSynonyms) {
            def.synonyms.append(syn);
        }

        std::set<QString> uniqueAntonyms(def.antonyms.begin(), def.antonyms.end());
        def.antonyms.clear();
        def.antonyms.reserve(uniqueAntonyms.size());
        for (const QString &ant : uniqueAntonyms) {
            def.antonyms.append(ant);
        }

        meanings[pos].append(def);
    }

    return true;
}

QVector<Word> WordDatabase::getAllWords() {
    QVector<Word> words;
    QSqlQuery query(m_db);
    if (!query.exec("SELECT id FROM Words ORDER BY word")) {
        return words;
    }

    while (query.next()) {
        int id = query.value("id").toInt();
        words.append(getWordById(id));
    }
    return words;
}

QVector<Word> WordDatabase::getWordsByName(const QString &wordName) {
    QVector<Word> words;
    QSqlQuery query(m_db);
    query.prepare("SELECT id FROM Words WHERE word = :word");
    query.bindValue(":word", wordName);
    if (!query.exec()) {
        return words;
    }

    while (query.next()) {
        int id = query.value("id").toInt();
        words.append(getWordById(id));
    }
    return words;
}

QVector<Word> WordDatabase::getWordsByCategory(int categoryId) {
    QVector<Word> words;
    QSqlQuery query(m_db);
    query.prepare(
        "SELECT w.id FROM Words w "
        "JOIN WordCategories wc ON w.id = wc.word_id "
        "WHERE wc.category_id = :category_id"
        );
    query.bindValue(":category_id", categoryId);
    if (!query.exec()) {
        return words;
    }

    while (query.next()) {
        int id = query.value("id").toInt();
        words.append(getWordById(id));
    }
    return words;
}

QVector<Word> WordDatabase::getWordsToReview(int userId, int count) {
    QVector<Word> words;

    // 使用SM-2算法的简化版本选择需要复习的单词
    // 基本逻辑：根据难度和上次复习时间计算复习优先级
    QSqlQuery query(m_db);
    query.prepare(
        "SELECT w.id, "
        "   (CASE "
        "       WHEN w.difficulty = 1 THEN 1.0 "  // 简单 - 长间隔
        "       WHEN w.difficulty = 2 THEN 1.5 "  // 较简单
        "       WHEN w.difficulty = 3 THEN 2.0 "  // 中等
        "       WHEN w.difficulty = 4 THEN 3.0 "  // 较难
        "       ELSE 4.0 END) * "  // 困难 - 短间隔
        "   JULIANDAY('now') - JULIANDAY(w.last_reviewed) AS days_since_review, "
        "   w.review_count "
        "FROM Words w "
        "LEFT JOIN LearningRecords lr ON w.id = lr.word_id AND lr.user_id = :user_id "
        "GROUP BY w.id "
        "HAVING days_since_review > (CASE "
        "       WHEN w.review_count = 0 THEN 0 "  // 新单词立即复习
        "       WHEN w.review_count = 1 THEN 1 "  // 第1次复习后1天
        "       WHEN w.review_count = 2 THEN 3 "  // 第2次复习后3天
        "       WHEN w.review_count = 3 THEN 7 "  // 第3次复习后7天
        "       WHEN w.review_count = 4 THEN 14 " // 第4次复习后14天
        "       ELSE 30 END) / (CASE "  // 5次及以上复习后30天
        "       WHEN w.difficulty = 1 THEN 2.0 "  // 简单单词间隔加倍
        "       WHEN w.difficulty = 2 THEN 1.5 "
        "       WHEN w.difficulty = 3 THEN 1.0 "
        "       WHEN w.difficulty = 4 THEN 0.7 "  // 困难单词间隔缩短
        "       ELSE 0.5 END) "  // 极难单词间隔减半
        "ORDER BY days_since_review DESC "
        "LIMIT :count"
        );
    query.bindValue(":user_id", userId);
    query.bindValue(":count", count);

    if (!query.exec()) {
        return words;
    }

    while (query.next()) {
        int id = query.value("id").toInt();
        words.append(getWordById(id));
    }
    return words;
}

bool WordDatabase::deleteWord(int id) {
    QSqlQuery query(m_db);
    query.prepare("SELECT id FROM Words WHERE id = :id");
    query.bindValue(":id", id);
    if (!query.exec() || !query.next()) return false;

    m_db.transaction();

    // 1. 删除单词-分类关联
    query.prepare("DELETE FROM WordCategories WHERE word_id = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        m_db.rollback();
        return false;
    }

    // 2. 删除学习记录
    query.prepare("DELETE FROM LearningRecords WHERE word_id = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        m_db.rollback();
        return false;
    }

    // 3. 删除单词（会通过外键约束自动删除关联的音标、释义等）
    query.prepare("DELETE FROM Words WHERE id = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        m_db.rollback();
        return false;
    }

    return m_db.commit();
}

// -------------------- 分类管理方法 --------------------
bool WordDatabase::addCategory(const Category &category) {
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO Categories (name, description) VALUES (:name, :description)");
    query.bindValue(":name", category.name);
    query.bindValue(":description", category.description);
    return query.exec();
}

bool WordDatabase::deleteCategory(int id) {
    QSqlQuery query(m_db);
    query.prepare("DELETE FROM Categories WHERE id = :id");
    query.bindValue(":id", id);
    return query.exec();
}

QVector<Category> WordDatabase::getAllCategories() {
    QVector<Category> categories;
    QSqlQuery query(m_db);
    if (!query.exec("SELECT id, name, description FROM Categories ORDER BY name")) {
        return categories;
    }

    while (query.next()) {
        Category category;
        category.id = query.value("id").toInt();
        category.name = query.value("name").toString();
        category.description = query.value("description").toString();
        categories.append(category);
    }
    return categories;
}

Category WordDatabase::getCategoryById(int id) {
    Category category;
    QSqlQuery query(m_db);
    query.prepare("SELECT id, name, description FROM Categories WHERE id = :id");
    query.bindValue(":id", id);
    if (!query.exec() || !query.next()) {
        return category;
    }

    category.id = id;
    category.name = query.value("name").toString();
    category.description = query.value("description").toString();
    return category;
}

QVector<Category> WordDatabase::getCategoriesByName(const QString &categoryName) {
    QVector<Category> categories;
    QSqlQuery query(m_db);
    query.prepare("SELECT id, name, description FROM Categories WHERE name LIKE :name");
    query.bindValue(":name", "%" + categoryName + "%");
    if (!query.exec()) {
        return categories;
    }

    while (query.next()) {
        Category category;
        category.id = query.value("id").toInt();
        category.name = query.value("name").toString();
        category.description = query.value("description").toString();
        categories.append(category);
    }
    return categories;
}

bool WordDatabase::assignWordToCategory(int wordId, int categoryId) {
    QSqlQuery query(m_db);
    query.prepare("INSERT OR IGNORE INTO WordCategories (word_id, category_id) VALUES (:word_id, :category_id)");
    query.bindValue(":word_id", wordId);
    query.bindValue(":category_id", categoryId);
    return query.exec();
}

bool WordDatabase::removeWordFromCategory(int wordId, int categoryId) {
    QSqlQuery query(m_db);
    query.prepare("DELETE FROM WordCategories WHERE word_id = :word_id AND category_id = :category_id");
    query.bindValue(":word_id", wordId);
    query.bindValue(":category_id", categoryId);
    return query.exec();
}

// -------------------- 用户管理方法 --------------------
bool WordDatabase::addUser(const QString &username, const QString &password) {
    // 注意：实际应用中应该对密码进行加密存储
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO Users (username, password) VALUES (:username, :password)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    return query.exec();
}

bool WordDatabase::authenticateUser(const QString &username, const QString &password) {
    QSqlQuery query(m_db);
    query.prepare("SELECT id FROM Users WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    return query.exec() && query.next();
}

int WordDatabase::getUserId(const QString &username) {
    QSqlQuery query(m_db);
    query.prepare("SELECT id FROM Users WHERE username = :username");
    query.bindValue(":username", username);
    if (!query.exec() || !query.next()) {
        return -1;
    }
    return query.value("id").toInt();
}

// -------------------- 学习记录管理方法 --------------------
bool WordDatabase::addLearningRecord(const LearningRecord &record) {
    QSqlQuery query(m_db);
    query.prepare(
        "INSERT INTO LearningRecords (word_id, user_id, timestamp, correct, difficulty) "
        "VALUES (:word_id, :user_id, :timestamp, :correct, :difficulty)"
        );
    query.bindValue(":word_id", record.wordId);
    query.bindValue(":user_id", record.userId);
    query.bindValue(":timestamp", record.timestamp);
    query.bindValue(":correct", record.correct);
    query.bindValue(":difficulty", record.difficulty);

    if (!query.exec()) {
        return false;
    }

    // 更新单词的最后复习时间和复习次数
    query.prepare(
        "UPDATE Words SET "
        "   last_reviewed = :timestamp, "
        "   review_count = review_count + 1, "
        "   difficulty = :difficulty "
        "WHERE id = :word_id"
        );
    query.bindValue(":timestamp", record.timestamp);
    query.bindValue(":difficulty", record.difficulty);
    query.bindValue(":word_id", record.wordId);

    return query.exec();
}

QVector<LearningRecord> WordDatabase::getUserLearningRecords(int userId, int days) {
    QVector<LearningRecord> records;
    QSqlQuery query(m_db);


    if (days > 0) {
        query.prepare(
            "SELECT id, word_id, user_id, timestamp, correct, difficulty "
            "FROM LearningRecords "
            "WHERE user_id = :user_id AND timestamp >= DATE('now', :days || ' days') "
            "ORDER BY timestamp DESC"
            );
        query.bindValue(":user_id", userId);
        query.bindValue(":days", -days);
    } else {
        query.prepare(
            "SELECT id, word_id, user_id, timestamp, correct, difficulty "
            "FROM LearningRecords "
            "WHERE user_id = :user_id "
            "ORDER BY timestamp DESC"
            );
        query.bindValue(":user_id", userId);
    }

    if (!query.exec()) {
        return records;
    }

    while (query.next()) {
        LearningRecord record;
        record.id = query.value("id").toInt();
        record.wordId = query.value("word_id").toInt();
        record.userId = userId;
        record.timestamp = query.value("timestamp").toDateTime();
        record.correct = query.value("correct").toBool();
        record.difficulty = query.value("difficulty").toInt();
        records.append(record);
    }
    return records;
}

double WordDatabase::getLearningAccuracy(int userId, int days) {
    QSqlQuery query(m_db);

    if (days > 0) {
        query.prepare(
            "SELECT AVG(correct) AS accuracy "
            "FROM LearningRecords "
            "WHERE user_id = :user_id AND timestamp >= DATE('now', :days || ' days')"
            );
        query.bindValue(":user_id", userId);
        query.bindValue(":days", -days);
    } else {
        query.prepare(
            "SELECT AVG(correct) AS accuracy "
            "FROM LearningRecords "
            "WHERE user_id = :user_id"
            );
        query.bindValue(":user_id", userId);
    }

    if (!query.exec() || !query.next()) {
        return 0.0;
    }

    return query.value("accuracy").toDouble() * 100.0; // 转换为百分比
}

// -------------------- 数据库工具方法 --------------------
bool WordDatabase::insertSampleData() {
    // 插入示例词性
    QVector<QString> posList = {"n.", "v.", "adj.", "adv.", "prep.", "pron.", "conj.", "interj."};
    for (const QString &pos : posList) {
        if (getOrCreatePartOfSpeech(pos) == -1) {
            return false;
        }
    }

    // 插入示例分类
    Category category;
    category.name = "常用词汇";
    category.description = "日常生活中最常用的基础词汇";
    if (!addCategory(category)) {
        return false;
    }
    int commonCategoryId = getCategoryById(1).id;

    // 插入示例单词
    Word word;

    // 示例单词1: apple
    word.word = "apple";
    word.difficulty = 1;

    // 添加音标
    Phonetic phonetic;
    phonetic.text = "/ˈæpl/";
    phonetic.audio = "https://example.com/audio/apple.mp3";
    word.phonetics.append(phonetic);

    // 添加释义（名词）
    Definition def;
    def.definition = "a round fruit with red, green, or yellow skin and firm white flesh";
    def.example = "She took a bite of the apple.";
    def.synonyms = {"fruit", "pome"};
    word.meanings["n."].append(def);

    if (!addWord(word)) {
        qInfo()<<"插入失败";
        return false;
    }
    int appleId = getWordsByName("apple").first().id;
    assignWordToCategory(appleId, commonCategoryId);

    // 示例单词2: beautiful
    word = Word();
    word.word = "beautiful";
    word.difficulty = 2;

    phonetic.text = "/ˈbjuːtɪfl/";
    phonetic.audio = "https://example.com/audio/beautiful.mp3";
    word.phonetics.clear();
    word.phonetics.append(phonetic);

    def = Definition();
    def.definition = "pleasing the senses or mind aesthetically";
    def.example = "She has beautiful eyes.";
    def.synonyms = {"attractive", "gorgeous", "lovely"};
    def.antonyms = {"ugly", "unattractive"};
    word.meanings["adj."].append(def);

    if (!addWord(word)) {
        return false;
    }
    int beautifulId = getWordsByName("beautiful").first().id;
    assignWordToCategory(beautifulId, commonCategoryId);

    // 插入示例用户
    if (!addUser("admin", "admin")) {
        return false;
    }

    // 插入示例学习记录
    LearningRecord record;
    record.wordId = appleId;
    record.userId = getUserId("admin");
    record.timestamp = QDateTime::currentDateTime().addDays(-1);
    record.correct = true;
    record.difficulty = 1;

    if (!addLearningRecord(record)) {
        return false;
    }

    record.wordId = beautifulId;
    record.timestamp = QDateTime::currentDateTime().addDays(-2);
    record.correct = false;
    record.difficulty = 2;

    return addLearningRecord(record);
}

QMap<QString, QString> WordDatabase::getpath() {
    QMap<QString, QString> dbPaths;
    QDir dataDir(QCoreApplication::applicationDirPath() + "/datas");
    if (!dataDir.exists()) return dbPaths;

    QStringList filters{"*.db"};
    foreach (QFileInfo file, dataDir.entryInfoList(filters, QDir::Files)) {
        dbPaths[file.baseName()] = file.absoluteFilePath();
    }
    return dbPaths;
}

QVector<QString> WordDatabase::getlist() {
    QVector<QString> dbNames;
    QDir dataDir(QCoreApplication::applicationDirPath() + "/datas");
    if (!dataDir.exists()) return dbNames;

    QStringList files = dataDir.entryList({"*.db"}, QDir::Files);
    foreach (QString file, files) {
        dbNames.append(file.left(file.lastIndexOf('.')));
    }
    return dbNames;
}

