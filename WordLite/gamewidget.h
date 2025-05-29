#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include "guess_word_widget.h"

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

private:
    Ui::GameWidget *ui;
    guess_word_widget *guessWordWidget;
};

#endif // GAMEWIDGET_H
