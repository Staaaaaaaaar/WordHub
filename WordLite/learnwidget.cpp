#include "learnwidget.h"
#include "ui_learnwidget.h"

LearnWidget::LearnWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LearnWidget)
{
    ui->setupUi(this);
}

LearnWidget::~LearnWidget()
{
    delete ui;
}
