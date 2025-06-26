#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Forward-declare classes to improve compile times and avoid circular includes
class UserWidget;
class QueryWidget;
class LearnWidget;
class AchievementWidget;
class GameWidget;
struct Achievement;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Public pointers to child widgets
    UserWidget* userWidget;
    QueryWidget* queryWidget;
    LearnWidget* learnWidget;
    AchievementWidget* achievementWidget;
    GameWidget* gameWidget;

    // Public methods for setup and signals
    void setupUI();
    void connectSignals();
    void exitSignal();

signals:
    void gameWidgerInit();

public slots:
    // Slots for status messages and achievement popups
    void showMes(QString message, int timeout);
    void clearMes();
    void showAchievementToast(const Achievement &achievement);

private:
    // The UI pointer, which was missing
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
