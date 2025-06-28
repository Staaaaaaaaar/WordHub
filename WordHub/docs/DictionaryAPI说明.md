
### `DictionaryAPI` 类

#### 功能与用途
`DictionaryAPI` 类用于与网络词典 API 进行交互，获取单词的详细信息。它提供了同步和异步两种方式来获取单词信息。

#### 属性
- `QNetworkAccessManager* manager`：网络访问管理器，用于发送网络请求。
- `Word currentWord`：存储当前查询的单词信息。
- `bool requestFinished`：请求是否完成的标志。
- `QString errorMessage`：错误信息。

#### 方法
- `explicit DictionaryAPI(QObject *parent = nullptr)`：构造函数，初始化网络访问管理器。
- `Word getWordInfo(const QString& word)`：同步方法，返回指定单词的详细信息。
- `void getWordInfoAsync(const QString& word)`：异步方法，通过信号返回指定单词的详细信息。
- `void onReplyFinished(QNetworkReply* reply)`：处理网络请求完成的槽函数。
- `Word createWordFromApiResult(const QJsonArray& apiResult)`：从 API 返回的 JSON 数组创建 Word 对象。
- `void parsePhonetics(const QJsonArray& phoneticsArray, Word& word)`：解析音标信息并填充到 Word 对象中。
- `void parseMeanings(const QJsonArray& meaningsArray, Word& word)`：解析释义信息并填充到 Word 对象中。

### 信号
- `void wordInfoReceived(const Word& word)`：当成功获取单词信息时发出的信号。
- `void errorOccurred(const QString& errorMessage)`：当发生错误时发出的信号。