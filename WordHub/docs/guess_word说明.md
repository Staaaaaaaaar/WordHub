### `guess_word`模块说明
**负责人**：[郑嘉祺](https://github.com/missswiftie)
#### 功能与用途
- `guess_word`类实现了猜词游戏模块，通过从数据库中随机抽取单词，调用deepseek的API生成这个单词的释义，并给出有关单词的提示，实现猜词功能。
#### 游戏python部分`python_reasoner`
- `get_database`函数获取数据库路径。
- **参数**：`database`为数据库代号
- **返回值**：返回指定数据库文件路径。
- `get_word`函数实现在指定数据库中随机选择单词。
- **参数**：`database`为数据库编号。
- **返回值**：返回随机抽取的单词，如果文件打开出现错误，返回word本身
- `unicode_unescape`函数通过正则表达式解决AI生成中文内容的编码问题。
- `get_word_and_description`函数通过deepseek获取`get_word`中指定单词的英文描述。
- **参数**：无
- **返回值**：返回deepseek生成的描述。
- `get_translation`函数获取上述生成描述的汉语翻译，并对描述中的一些重点词汇进行解析。
- **参数**：`description`为`get_word_and_description`函数生成的英文描述。
- **返回值**：返回英文描述的中文翻译。
- `main`函数执行翻译程序，返回数据格式如下所示
```json
{
        "status":"success",
        "word":,
        "description":,
        "translation":
}
```
#### 游戏后端`guess_word`部分
- `processingPython`函数启用python解释器以及`python_reasoner.py`脚本，执行脚本并获取单词，描述以及翻译信息。
- **参数**：无。
- **返回值**：返回一个map，键为"word"，"description"，"translation"，值分别对应单词，英文描述，中文翻译。
#### 游戏前端`guess_word_widget`部分
##### 属性
- `m_word`存储待猜测的单词，是`QString`类型。
- `m_description`存储待猜测的单词的英文描述，是`QString`类型。
- `m_translation`存储待猜测单词描述的翻译，是`QString`类型。
- `m_guesser`是后端类对象，负责执行后端类。
- `m_watcher`是`QFutureWatcher<std::map<QString, QString>>`类型，负责监测python进程。
##### 槽函数及信号
- `onBeginButtonClicked`表示按下“开始游戏”按钮后执行的操作，启动python进程。
- `handleProcessingFinished`信号在python进程结束之后被触发，在框中显示单词的英文描述，并将单词、描述和翻译分别存在`m_word`,`m_description`,`m_translation`变量中。
- `on_exitButton_clicked`信号在按下“结束游戏”时触发，退出猜词游戏界面。
- `onRuleButtonClicked`信号在按下“游戏规则”时触发，在框中显示游戏规则。
- `onAnswerButtonClicked`信号在按下“查看答案”时触发，在框中显示单词的答案和单词英文描述的详细翻译。
- `onCommitButtonClicked`信号在按下“确定答案”时触发，判断玩家猜测的答案的正误。
- 同时，通过在合适的时间禁用某些按钮（例如在没开始游戏之前不能查看答案）来使得游玩体验更好更合理。