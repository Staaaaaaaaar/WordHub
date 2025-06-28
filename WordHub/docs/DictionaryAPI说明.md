# DictionaryAPI 类文档

**负责人**: [刘继轩](https://github.com/stibiums)

## 一、概述
`DictionaryAPI` 类封装了对第三方开源 [API](https://github.com/meetDeveloper/freeDictionaryAPI) 的网络请求。它能够根据一个单词字符串，获取其完整的结构化信息，并将其解析为程序内部的 `Word` 对象。

## 二、设计理念
`DictionaryAPI` 是“外部世界网关”。
*   **设计理念**: 它将所有与特定网络API相关的细节（如URL构造、HTTP请求、JSON解析）全部封装起来，对内仅暴露一个简单的、返回 `Word` 对象的接口。这种设计使得网络请求的发起方（如`Wordloader`）无需关心网络通信的复杂性。如果未来需要更换词典API，只需修改 `DictionaryAPI` 内部的实现，而所有调用它的代码都无需改动。

## 三、属性
- `QNetworkAccessManager* manager`: **[私有]** 网络访问管理器，用于发送网络请求。

## 四、方法
- `Word getWordInfo(const QString& word)`: **同步方法**。发起网络请求并阻塞当前线程，直到请求完成或超时。
    - **参数**: `word` 为要查询的单词。
    - **返回值**: `Word`，一个包含完整信息的单词对象。如果失败则返回一个空 `Word` 对象。
- `void getWordInfoAsync(const QString& word)`: **异步方法**。立即返回，不阻塞线程，通过信号返回结果。
    - **参数**: `word` 为要查询的单词。

## 五、信号
- `void wordInfoReceived(const Word& word)`: 当异步请求成功并解析完成后，发出此信号。
    - **参数**: `word` 为填充好数据的 `Word` 对象。
- `void errorOccurred(const QString& errorMessage)`: 当网络请求或数据解析过程中发生错误时，发出此信号。
    - **参数**: `errorMessage` 为描述错误的字符串。

## 六、私有槽函数
- `void onReplyFinished(QNetworkReply* reply)`: 在网络请求完成后被自动调用，是所有处理逻辑的入口。
