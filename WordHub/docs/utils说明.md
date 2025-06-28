### `utils` - 核心数据结构

**负责人**: [刘继轩](https://github.com/stibiums)

#### 功能与用途
`utils.h` 文件定义了整个项目中使用到的核心数据实体结构。这些结构体和类作为数据传输对象（DTO），在程序的不同模块（UI、业务逻辑、数据访问）之间传递信息。

---

### `Phonetic` 结构体
音标结构体，存储单词的音标和发音信息。

#### 属性
- `QString text`: 音标文本，例如：`"/ˈwɜːd/"`。
- `QString audio`: 发音音频的 URL 链接。

---

### `Definition` 结构体
单词释义结构体，包含释义内容、例句、同义词和反义词。

#### 属性
- `QString definition`: 单词释义的具体内容。
- `QString example`: 与该释义对应的例句。
- `QVector<QString> synonyms`: 同义词列表。
- `QVector<QString> antonyms`: 反义词列表。

---

### `Word` 类
单词类，存储一个单词的完整信息，是系统中最核心的数据实体。

#### 属性
- `int id`: 单词在数据库中的唯一标识。
- `QString word`: 单词文本，例如：`"hello"`。
- `QVector<Phonetic> phonetics`: 单词的音标列表，支持多音标（如英式、美式）。
- `QMap<QString, QVector<Definition>> meanings`: 按词性分类的释义，key为词性（如`"n."`、`"v."`）。
- `QDateTime lastReviewed`: 最后复习时间，用于间隔重复算法。
- `int reviewCount`: 复习次数。
- `int difficulty`: 难度等级（1-5），1表示简单，5表示困难。

#### 方法
- `QString getoneMeaning()`: 从所有词性中随机获取一条释义。
    - **返回值**: `QString`，格式为 "词性:释义内容"。
- `bool isEmpty()`: 检查单词文本是否为空。
    - **返回值**: `bool`，如果 `word` 属性为空则返回 `true`。
- `QDebug operator<<(QDebug o, const Word& w)`: `QDebug` 输出运算符重载，用于方便地打印单词的完整信息以供调试。

---

### `Category` 类
单词分类（词库）类。

#### 属性
- `int id`: 分类在数据库中的唯一标识。
- `QString name`: 分类名称，例如：`"CET4核心词汇"`。
- `QString description`: 对该分类的详细描述。

---

### `LearningRecord` 类
学习记录类，记录用户的每一次学习行为。

#### 属性
- `int id`: 记录在数据库中的唯一标识。
- `int wordId`: 关联的单词 ID。
- `int userId`: 关联的用户 ID。
- `QDateTime timestamp`: 本次学习发生的时间戳。
- `bool correct`: 本次学习回答是否正确。
- `int difficulty`: 学习时单词的难度。