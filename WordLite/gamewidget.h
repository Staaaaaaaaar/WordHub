#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>

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

private:
    Ui::GameWidget *ui;
};

#endif // GAMEWIDGET_H
