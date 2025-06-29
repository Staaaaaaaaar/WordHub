# QueryWidget 类文档

**文件位置**：UI/querywidget.h, UI/querywidget.cpp
**负责人**: [郑星浩](https://github.com/Staaaaaaaaar)

## 概述
QueryWidget 是 WordHub 应用程序的单词查询主界面，支持本地词库和在线 API 查询，允许用户切换不同词库，并以多标签页（Tab）形式展示查询结果。用户可快速查找单词释义、音标、例句等详细信息，并进行多词库管理。QueryWidget 通过灵活的界面布局和信号槽机制，实现高效、便捷的单词查询体验。

## 设计理念
- **多源查询**：支持本地数据库与在线 API 查询，满足不同场景下的查词需求。
- **多标签页管理**：每次查询结果以 Tab 形式展示，便于多词对比和历史回溯。
- **词库灵活切换**：下拉框快速切换不同词库，支持自定义扩展。
- **交互友好**：界面简洁，操作直观，支持回车快捷查询、Tab 关闭等便捷操作。
- **解耦通信**：通过信号槽机制与主窗口、成就系统等模块解耦协作。

## UI对象介绍
- `Ui::QueryWidget *ui`  
  Qt Designer 生成的 UI 指针，包含主界面所有控件。
- `QTabWidget* tabWidget`  
  多标签页控件，展示每次查询的单词详情。
- `QLineEdit* searchEdit`  
  单词输入框，支持回车快捷查询。
- `QComboBox* comboBox`
  词库选择下拉框。
- `QCheckBox* useAPICheckBox`  
  是否启用 API 查询模式的勾选框。

## 主要成员变量
- `WordWidget* wordWidget`  
  当前显示的单词详情控件。
- `WordDatabase* wordDataBase`  
  当前使用的单词数据库对象。
- `DictionaryAPI* dictionaryAPI`  
  在线词典API对象。
- `bool useAPI`  
  是否启用API查询模式。
- `QString defaultWordDB`  
  默认词库名称。
- `QVector<QString> wordDBList`  
  可用词库名称列表。

## 普通成员函数
- `setupUI()`  
  初始化界面，包括Tab样式、词库下拉框等。
- `connectSignals()`  
  连接UI控件与槽函数，如查询、切换词库、API开关等。

## 信号
- `sendMes(QString message, int timeout=0)`  
  发送消息提示信号。
- `clearMes()`  
  清除消息提示信号。
- `sendId(int id)`  
  发送成就解锁信号。

## 槽函数
- `on_searchEdit_returnPressed()`  
  处理回车查询单词逻辑。
- `on_tabWidget_tabCloseRequested(int index)`  
  关闭Tab页。
- `on_comboBox_currentTextChanged(const QString &DBname)`  
  切换词库。
- `sendMess(QString message, int timeout)`  
  发送消息信号（转发）。
- `clearMess()`  
  清除消息信号（转发）。
