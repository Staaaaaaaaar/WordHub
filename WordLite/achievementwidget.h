#ifndef ACHIEVEMENTWIDGET_H
#define ACHIEVEMENTWIDGET_H

#include <QWidget>

namespace Ui {
class AchievementWidget;
}

class AchievementWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AchievementWidget(QWidget *parent = nullptr);
    ~AchievementWidget();

private:
    Ui::AchievementWidget *ui;
};

#endif // ACHIEVEMENTWIDGET_H
