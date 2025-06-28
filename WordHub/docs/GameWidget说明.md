# GameWidget 类文档

**文件位置**：UI/gamewidget.h, UI/gamewidget.cpp
**负责人**: [郑星浩](https://github.com/Staaaaaaaaar)

## 作用
负责单词游戏的主界面，支持多种游戏（如猜单词、Wordle），并动态管理游戏子界面。

## 主要成员变量
- `Ui::GameWidget *ui`  
  Qt Designer 生成的UI指针。
- `guess_word_widget *guessWordWidget`  
  猜单词游戏界面。
- `Wordle *wordle`  
  Wordle游戏界面指针（动态创建/销毁）。

## 主要成员函数
- `setupUI()`  
  初始化游戏主界面。
- `connectSignals()`  
  连接按钮与各游戏界面的信号槽。
- `onGuessWordWidgetExit()`  
  处理猜单词游戏退出，返回主菜单。
- `onWordleButtonClicked()`  
  动态创建/切换到Wordle游戏界面。
- `returnToGameMenu()`  
  返回游戏主菜单。
- `onBeginSignalCome()`  
  预留，处理游戏开始信号。
- `onAnswerSignalCome()`  
  预留，处理答题信号。

## 主要信号
- `sendId(int id)`  
  游戏内成就解锁信号。
