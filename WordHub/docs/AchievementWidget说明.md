# AchievementWidget 类文档

**文件位置**：UI/achievementwidget.h, UI/achievementwidget.cpp
**负责人**: [郑星浩](https://github.com/Staaaaaaaaar)

## 概述
AchievementWidget 是 WordHub 应用程序的成就展示与管理界面，负责集中展示所有成就、显示解锁状态、处理成就解锁逻辑，并通过信号与主窗口协作弹出成就提示。该界面支持滚动浏览、动态刷新，用户可直观了解自己的学习成就与进度。

## 设计理念
- **可视化与激励**：通过列表和美化样式直观展示成就，激励用户持续学习。
- **解耦通信**：采用 Qt 信号槽机制，成就解锁与弹窗提示解耦，便于维护和扩展。
- **数据驱动**：成就状态与数据库实时同步，保证成就展示的准确性和一致性。
- **高可用性**：支持动态刷新和外部事件触发，保证成就界面始终反映最新状态。

## UI对象介绍
- `Ui::AchievementWidget *ui`  
  Qt Designer 生成的 UI 指针，包含主界面所有控件。
- `QScrollArea *scrollArea`  
  成就列表滚动区域，支持大量成就的浏览。
- `QWidget *scrollContent`  
  滚动区域内容容器，承载成就项。
- `QVBoxLayout *scrollLayout`  
  成就列表布局，垂直排列所有成就项。

## 主要成员变量
- `Ui::AchievementWidget *ui`
- `QScrollArea *scrollArea`
- `QWidget *scrollContent`
- `QVBoxLayout *scrollLayout`

## 普通成员函数
- `setupUI()`  
  初始化滚动区域和主布局。
- `connectSignals()`  
  连接外部信号（如登录成功等）。
- `refreshUI()`  
  刷新成就列表显示。
- `QVector<Achievement> loadAchievements()`  
  加载所有成就及其解锁状态。

## 信号
- `achievementUnlocked(const Achievement &achievement)`  
  成就解锁时发出，主窗口可弹窗提示。

## 槽函数
- `unlockAchievement(int achievementId)`  
  解锁指定成就，并发出解锁信号。
