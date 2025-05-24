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

void LearnWidget::addButton(DictButton* dictButtton)
{
    // ui->gridLayout_2->addItem(dictButtton, );
}


DictButton::DictButton() //传入字典指针
{

}

DictButton::~DictButton()
{

}

