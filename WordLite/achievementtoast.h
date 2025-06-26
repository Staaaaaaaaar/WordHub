#ifndef ACHIEVEMENTTOAST_H
#define ACHIEVEMENTTOAST_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QPropertyAnimation>
#include <QHBoxLayout>
#include "achievementwidget.h" // 为了使用 Achievement 结构体

class AchievementToast : public QWidget
{
    Q_OBJECT

public:
    explicit AchievementToast(QWidget *parent = nullptr);
    void showAchievement(const Achievement &achievement);

private:
    QLabel *iconLabel;
    QLabel *titleLabel;
    QLabel *descLabel;
    QPropertyAnimation *animation;
};

#endif // ACHIEVEMENTTOAST_H