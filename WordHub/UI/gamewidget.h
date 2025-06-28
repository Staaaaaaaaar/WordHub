#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include "guess_word_widget.h"
#include "wordle.h"

namespace Ui {
class GameWidget;
}

class GameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameWidget(QWidget *parent = nullptr);
    ~GameWidget();

    // 设置UI和连接信号槽
    void setupUI();
    void connectSignals();

private slots:
    void onGuessWordWidgetExit();
    void onBeginSignalCome();
    void onAnswerSignalCome();
    void returnToGameMenu();
    void onWordleButtonClicked(); // <--- 在这里添加新的槽函数声明
signals:
    void sendId(int id);
private:
    Ui::GameWidget *ui;
    guess_word_widget *guessWordWidget;
    Wordle *wordle;
};

#endif // GAMEWIDGET_H
