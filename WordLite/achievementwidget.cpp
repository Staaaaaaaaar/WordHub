#include "achievementwidget.h"
#include "ui_achievementwidget.h"

AchievementWidget::AchievementWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AchievementWidget)
{
    ui->setupUi(this);
}

AchievementWidget::~AchievementWidget()
{
    delete ui;
}
