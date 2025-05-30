#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <userwidget.h>
#include <querywidget.h>
#include <learnwidget.h>
#include <achievementwidget.h>
#include <gamewidget.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    UserWidget* userWidget;
    QueryWidget* queryWidget;
    LearnWidget* learnWidget;
    AchievementWidget* achievementWidget;
    GameWidget* gameWidget;

    // 设置UI和连接信号槽
    void setupUI();
    void connectSignals();

private slots:
    void showMes(QString message, int timeout=0);
    void clearMes();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
