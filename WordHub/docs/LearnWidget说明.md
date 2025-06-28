# LearnWidget 类文档

**文件位置**：UI/learnwidget.h, UI/learnwidget.cpp
**负责人**: [郑星浩](https://github.com/Staaaaaaaaar)

## 概述
LearnWidget 是 WordHub 应用程序的单词学习主界面，集成了单词学习、复习、测试、词库管理和自定义词库导入等核心功能。用户可在此界面选择词库、进行学习与测试、查看学习进度和统计图表，并灵活管理自定义词库。LearnWidget 通过多页面切换和丰富的交互控件，提升学习效率和体验。

## 设计理念
- **模块化与可扩展性**：词库、学习、测试等功能分区明确，便于后续扩展和维护。
- **交互友好**：采用 QStackedWidget 管理多页面，按钮、进度条、图表等控件直观展示学习进度。
- **自定义支持**：支持用户导入自定义词库，满足个性化学习需求。
- **数据驱动**：所有学习、测试数据均与数据库实时同步，保证数据一致性。
- **高可用性**：界面切换、数据刷新、测试流程等均有异常处理，保证流畅体验。

## UI对象介绍
- `Ui::LearnWidget *ui`  
  Qt Designer 生成的 UI 指针，包含主界面所有控件。
- `QStackedWidget* stackedWidget`  
  管理学习、复习、测试、词库信息等多页面切换。
- `QToolButton* learnButton/reviewButton/testButton/viewAllWordsButton/refreshButton/resetButton`  
  各功能入口及操作按钮。
- `QTableWidget* wordsListWidget`  
  单词列表与测试结果展示表格。
- `QProgressBar* progressBar`  
  学习进度条。
- `QWidget* defaultBox/showWidget`  
  词库选择区与词库信息区。
- `QLabel* testWordLabel`  
  测试题目单词显示。
- `QLabel* label_0 ~ label_3`  
  测试选项标签。

## 主要成员变量
- `WordDatabase* DBptr`  
  当前词库数据库对象。
- `QList<QString> defaultDictNames`  
  默认词库名称列表。
- `QList<DictButton*> defaultButtons`  
  默认词库按钮列表。
- `QList<DictButton*> customizeButtons`  
  自定义词库按钮列表。
- `DictButton* addDictButton`  
  “添加词库”按钮。
- `QString dictName`  
  当前选中的词库名称。
- `QVector<Word> wordsList`  
  当前显示的单词列表。
- `QVector<bool> testResults`  
  测试结果记录。
- `QVector<QLabel*> optionLabels`  
  测试选项标签。
- `int currentTestIndex`  
  当前测试单词索引。
- `int currentSelected`  
  当前选中的测试选项。
- `QString correctAnswer`  
  当前题目的正确答案。

## 普通成员函数
- `setupUI()`  
  初始化主界面、词库按钮、布局等。
- `connectSignals()`  
  连接所有按钮与槽函数。
- `addButtonsToGrid(QGridLayout *grid, const QList<DictButton*> &buttons, int columns)`  
  辅助函数，将按钮添加到网格布局。
- `initDictWidget()`  
  初始化词库信息界面（学习进度、统计图表）。
- `initWordsWidget()`  
  初始化单词列表界面。
- `initCheckout()`  
  初始化测试结果界面。
- `initTestWidget()`  
  初始化测试界面。
- `showTestForWord(int idx)`  
  显示指定单词的测试题。

## 信号
- *（如有自定义信号请在此补充）*

## 槽函数
- `on_addDictButton_clicked()`  
  处理添加词库逻辑。
- `on_dictButton_clicked()`  
  处理词库按钮点击，切换词库。
- `on_reviewButton_clicked()`  
  进入复习模式。
- `on_learnButton_clicked()`  
  进入学习模式。
- `on_testButton_clicked()`  
  进入测试模式。
- `on_refreshButton_clicked_1()`  
  刷新学习单词列表。
- `on_refreshButton_clicked_2()`  
  刷新复习单词列表。
- `on_viewAllWordsButton_clicked()`  
  查看当前词库所有单词。
- `on_resetButton_clicked()`  
  重置学习记录。
