# WordWidget 类文档

**文件位置**：UI/querywidget.h, UI/querywidget.cpp
**负责人**: [郑星浩](https://github.com/Staaaaaaaaar)

## 概述
WordWidget 是 WordHub 应用程序中用于展示单词详细信息的界面组件。它支持显示单词的音标、释义、例句、分类标签、学习信息，并提供收藏和分类管理等交互功能。WordWidget 支持本地词库和 API 查询两种模式，界面内容根据模式动态调整，帮助用户高效管理和学习单词。

## 设计理念
- **信息丰富**：集成音标、释义、例句、分类、学习记录等多维度信息，提升单词学习的全面性。
- **交互友好**：支持一键收藏、分类管理、动态展开例句等操作，提升用户体验。
- **模式兼容**：兼容本地词库与 API 查询，自动适配不同数据源的展示需求。
- **动态布局**：采用滚动区域和自适应布局，保证内容展示的灵活性和美观性。

## UI对象介绍
- `QVBoxLayout* mainLayout`  
  主体布局，承载所有内容。
- `QScrollArea* scrollArea`  
  滚动区域，支持内容溢出时滚动浏览。
- `QWidget* scrollContent`  
  滚动内容容器，包含所有单词详细信息。
- `QGroupBox* wordBox`  
  单词信息分组框，包含单词、音标、收藏按钮等。
- `QLabel* wordLabel/pronLabel`  
  单词文本和音标显示标签。
- `QPushButton* favButton`  
  收藏/分类管理按钮（本地词库模式下）。
- `QMenu* favMenu`  
  分类管理菜单。

## 主要成员变量
- `QString word`  
  当前展示的单词。
- `bool useAPI`  
  是否为API模式（只读）。
- `WordDatabase* DBptr`  
  词库数据库指针。

## 普通成员函数
- `setupUI(QVector<Word> wordList)`  
  根据传入的单词列表，动态生成详细信息界面，包括分类、释义、例句等。
- `connectSignals()`  
  连接收藏、分类管理等相关信号槽。

## 信号
- `sendMes(QString message, int timeout=0)`  
  发送消息提示信号。
- `clearMes()`  
  清除消息提示信号。

## 槽函数
- *（如有自定义槽函数请在此补充）*
