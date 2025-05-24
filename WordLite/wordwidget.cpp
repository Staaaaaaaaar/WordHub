#include "wordwidget.h"
#include "ui_wordwidget.h"

WordWidget::WordWidget(QString word, QWidget *parent)
    : QWidget(parent)
    , word(word)
    , ui(new Ui::WordWidget)
{
    ui->setupUi(this);

    // 设置UI和连接信号槽
    setupUI();
    connectSignals();
}

WordWidget::~WordWidget()
{
    delete ui;
}

void WordWidget::setupUI(){


}

void WordWidget::connectSignals(){

}
