# 核心数据结构文档 (utils.h)

**负责人**: [刘继轩](https://github.com/stibiums)

## 一、概述
`utils.h` 文件定义了整个项目中使用到的核心数据实体结构。这些结构体和类作为数据传输对象（DTO），在程序的不同模块（UI、业务逻辑、数据访问）之间传递信息。它们是整个系统数据结构的基础，负责承载程序运行中的核心数据。

## 二、设计理念

*   **`Word`**: 这是系统中最核心的实体类。它不仅仅是一个字符串，而是一个包含了单词所有属性的聚合体。
    *   **设计理念**: 我们将与一个单词相关的所有信息，如音标 (`QVector<Phonetic>`)、多词性释义 (`QMap<QString, QVector<Definition>>`) 以及学习状态 (`lastReviewed`, `reviewCount`, `difficulty`) 都封装在此类中。这种设计使得单词对象可以在不同模块间自由传递，每个模块都能获取到所需信息，而无需频繁查询数据库。
    *   **关键实现**: `meanings` 采用 `QMap` 结构，键为词性，值为该词性下的所有释义，完美地映射了真实世界词典的结构。

*   **`Phonetic` & `Definition`**: 这两个结构体是 `Word` 类的辅助数据容器。
    *   **设计理念**: 它们将复杂的单词属性进一步拆分，使得 `Word` 类的结构更加清晰。`Phonetic` 存储音标文本和发音URL，`Definition` 则聚合了释义、例句、同反义词，体现了“组合优于继承”的设计原则。

*   **`Category`**: 代表一个“词库”或“单词本”。
    *   **设计理念**: 通过引入 `Category`，我们实现了多词库管理的功能。用户可以自由切换学习范围（如 CET4, GRE），或创建自己的个性化词库，为功能扩展提供了良好的基础。

*   **`LearningRecord`**: 记录用户的每一次学习行为。
    *   **设计理念**: 这是一个事件记录类，用于数据统计和分析。每当用户完成一次单词测试，就会生成一个 `LearningRecord` 对象并存入数据库。它是实现艾宾浩斯遗忘曲线、计算学习正确率和生成热力图的数据来源。

## 三、Phonetic 结构体
音标结构体，存储单词的音标和发音信息。
### 属性
- `QString text`: 音标文本，例如：`"/ˈwɜːd/"`。
- `QString audio`: 发音音频的 URL 链接。

## 四、Definition 结构体
单词释义结构体，包含释义内容、例句、同义词和反义词。
### 属性
- `QString definition`: 单词释义的具体内容。
- `QString example`: 与该释义对应的例句。
- `QVector<QString> synonyms`: 同义词列表。
- `QVector<QString> antonyms`: 反义词列表。

## 五、Word 类
单词类，存储一个单词的完整信息，是系统中最核心的数据实体。
### 属性
- `int id`: 单词在数据库中的唯一标识。
- `QString word`: 单词文本，例如：`"hello"`。
- `QVector<Phonetic> phonetics`: 单词的音标列表，支持多音标（如英式、美式）。
- `QMap<QString, QVector<Definition>> meanings`: 按词性分类的释义，key为词性（如`"n."`、`"v."`）。
- `QDateTime lastReviewed`: 最后复习时间，用于间隔重复算法。
- `int reviewCount`: 复习次数。
- `int difficulty`: 难度等级（1-5），1表示简单，5表示困难。
### 方法
- `QString getoneMeaning()`: 从所有词性中随机获取一条释义。
    - **返回值**: `QString`，格式为 "词性:释义内容"。
- `bool isEmpty()`: 检查单词文本是否为空。
    - **返回值**: `bool`，如果 `word` 属性为空则返回 `true`。
- `QDebug operator<<(QDebug o, const Word& w)`: `QDebug` 输出运算符重载，用于方便地打印单词的完整信息以供调试。

## 六、Category 类
单词分类（词库）类。
### 属性
- `int id`: 分类在数据库中的唯一标识。
- `QString name`: 分类名称，例如：`"CET4核心词汇"`。
- `QString description`: 对该分类的详细描述。

## 七、LearningRecord 类
学习记录类，记录用户的每一次学习行为。
### 属性
- `int id`: 记录在数据库中的唯一标识。
- `int wordId`: 关联的单词 ID。
- `int userId`: 关联的用户 ID。
- `QDateTime timestamp`: 本次学习发生的时间戳。
- `bool correct`: 本次学习回答是否正确。
- `int difficulty`: 学习时单词的难度。