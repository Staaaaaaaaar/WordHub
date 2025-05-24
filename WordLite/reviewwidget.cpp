#include "reviewwidget.h"
#include "ui_reviewwidget.h"

ReviewWidget::ReviewWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ReviewWidget)
{
    ui->setupUi(this);
}

ReviewWidget::~ReviewWidget()
{
    delete ui;
}
