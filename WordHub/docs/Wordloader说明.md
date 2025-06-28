### `Wordloader` 类

#### 功能与用途
`Wordloader` 类用于从不同格式的文件中导入单词到数据库。它支持从 JSON 词典文件和 TXT 文件导入单词，并且可以选择是否使用网络词典 API 来获取单词信息。

#### 属性
无

#### 方法
- `bool importWordsFromJson(const QString& jsonFilePath, const QString& dbName)`：从 JSON 词典文件导入单词到指定数据库。
- `bool importWordFromTXT(const QString& TXTFilePath, const QString& dbName, const QString& search_dbname, bool use_API=false)`：从 TXT 文件导入单词到指定数据库，可选择是否使用网络词典 API。
- `QVector<Phonetic> extractPhonetics(const QJsonObject& phoneticsObj)`：从 JSON 对象中提取音标信息。
- `QMap<QString, QVector<Definition>> extractMeanings(const QJsonObject& wordInfo)`：从 JSON 对象中提取释义信息。
- `QStringList extractWords(const QString& text)`：使用正则表达式从文本中提取单词。
- `bool isInvalidLine(const QString& line)`：启发式过滤无效行。