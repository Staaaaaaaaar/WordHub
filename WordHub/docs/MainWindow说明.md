# MainWindow 类文档

**文件位置**：UI/mainwindow.h, UI/mainwindow.cpp
**负责人**: [郑星浩](https://github.com/Staaaaaaaaar)

## 概述
MainWindow 是 WordHub 应用程序的主窗口类，负责集成和管理所有核心功能模块，包括用户信息、单词查询、学习、成就展示和单词游戏等界面。它通过 QStackedWidget 实现各功能界面的切换，并协调各子窗口之间的数据流与信号传递，保证用户在不同功能间的无缝切换和良好体验。MainWindow 还负责全局状态栏消息、成就弹窗等全局交互。

## 设计理念
- **模块化**：各功能界面（如用户、查询、学习、成就、游戏）均以独立的 QWidget 子类实现，便于维护和扩展。
- **解耦与信号槽机制**：通过 Qt 的信号槽机制，各子界面之间低耦合通信，主窗口统一协调成就解锁、消息提示等全局事件。
- **资源管理**：主窗口负责子界面的创建、切换和资源释放，确保数据库连接等资源不会冲突。
- **用户体验**：支持深色标题栏、状态栏消息提示、成就弹窗等细节优化，提升整体交互体验。

## UI对象介绍
- `Ui::MainWindow *ui`  
  Qt Designer 生成的 UI 指针，包含主窗口的所有控件对象，如 QStackedWidget、QToolButton、状态栏等。
- `QStackedWidget* stackedWidget`  
  用于切换不同功能界面的核心控件。
- `QToolButton* userButton/queryButton/learnButton/achievementButton/gameButton/exitButton`  
  用于切换各功能界面和退出应用的按钮。
- `QStatusBar* statusbar`  
  用于显示全局提示信息。

## 主要成员变量
- `UserWidget* userWidget`  
  用户信息界面。
- `QueryWidget* queryWidget`  
  单词查询界面。
- `LearnWidget* learnWidget`  
  单词学习界面。
- `AchievementWidget* achievementWidget`  
  成就展示与管理界面。
- `GameWidget* gameWidget`  
  单词游戏界面。

## 普通成员函数
- `setupUI()`  
  初始化所有子界面并将其加入主窗口的 QStackedWidget。
- `connectSignals()`  
  连接主窗口与各子界面之间的信号槽，实现界面切换、消息提示、成就弹窗等功能。
- `exitSignal()`  
  处理退出主窗口并返回登录界面的逻辑。

## 信号
- `void gameWidgerInit();`  
  游戏界面初始化信号。

## 槽函数
- `void showMes(QString message, int timeout);`  
  在状态栏显示提示信息。
- `void clearMes();`  
  清除状态栏信息。
- `void showAchievementToast(const Achievement &achievement);`  
  弹出成就解锁提示。
