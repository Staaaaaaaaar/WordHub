#include "querywidget.h"
#include "ui_querywidget.h"

QueryWidget::QueryWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QueryWidget)
{
    ui->setupUi(this);
}

QueryWidget::~QueryWidget()
{
    ui->tabWidget->clear();
    delete ui;
}

void QueryWidget::on_searchEdit_returnPressed()
{
    //获取查询内容
    QString word = ui->searchEdit->text();
    //判断是否已有wordWidget

    //判断word是否是个有效查询

    //生成一个实例wordWidget
    WordWidget* wordWidget = new WordWidget(word);
    //将wordWidget装入tabWidget并显示
    ui->tabWidget->addTab(wordWidget, word);
    ui->tabWidget->setCurrentWidget(wordWidget);
}


void QueryWidget::on_tabWidget_tabCloseRequested(int index)
{
    //把wordWidget移除tabWidget并析构该对象
    QWidget* tmp = ui->tabWidget->widget(index);
    ui->tabWidget->removeTab(index);
    delete tmp;
}

