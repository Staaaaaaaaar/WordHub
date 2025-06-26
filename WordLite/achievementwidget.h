#ifndef ACHIEVEMENTWIDGET_H
#define ACHIEVEMENTWIDGET_H

#include <QWidget>
#include <QDateTime>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QGroupBox>
#include <QLabel>
#include <QMessageBox> // 新增
#include "back_head/learner.h" // 新增

namespace Ui {
class AchievementWidget;
}

struct Achievement {
    int id;
    QString title;
    QString description;
    bool unlocked;
    QDateTime unlockDate;
    QString iconPath;
};

class AchievementWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AchievementWidget(QWidget *parent = nullptr);
    ~AchievementWidget();

    // 移除 testAchievements 成员变量

    // 设置UI和连接信号槽
    void setupUI();
    void connectSignals();
    void refreshUI();
    QVector<Achievement> loadAchievements(); // 修改：从数据源加载成就

public slots:
    void unlockAchievement(int achievementId); // 新增：解锁成就并刷新UI

signals:
    void achievementUnlocked(const Achievement &achievement); // 新增信号

private:
    Ui::AchievementWidget *ui;

    QScrollArea *scrollArea;
    QWidget *scrollContent;
    QVBoxLayout *scrollLayout;
};

#endif // ACHIEVEMENTWIDGET_H
