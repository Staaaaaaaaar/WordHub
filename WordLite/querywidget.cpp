#include "querywidget.h"
#include "ui_querywidget.h"

QueryWidget::QueryWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QueryWidget)
{
    ui->setupUi(this);

    // 设置UI和连接信号槽
    setupUI();
    connectSignals();
    //初始化数据库连接
    wordDataBase = new WordDatabase;
    wordDBList = WordDatabase::getlist();
    // wordDataBase->initDatabase();
}

QueryWidget::~QueryWidget()
{
    ui->tabWidget->clear();
    delete ui;
}

void QueryWidget::setupUI()
{
    //设置comboBox
    for (QString DBname: wordDBList)
    {
        ui->comboBox->addItem(DBname);
    }
}

void QueryWidget::connectSignals()
{
    connect(ui->searchEdit, &QLineEdit::returnPressed, this, &QueryWidget::on_searchEdit_returnPressed);

}


void QueryWidget::on_searchEdit_returnPressed()
{
    //向mainWindow发射信号
    emit sendMes("正在查询...");
    //获取查询内容
    QString cur_word = ui->searchEdit->text();
    //判断是否已有wordWidget
    for (int index = 0; index < ui->tabWidget->count(); index++)
    {
        if (ui->tabWidget->tabBar()->tabText(index) == cur_word)
        {
            ui->tabWidget->setCurrentIndex(index);
            return;
        }
    }
    //判断word是否是个有效查询

    //生成一个实例wordWidget
    WordWidget* wordWidget = new WordWidget(cur_word);
    //将wordWidget装入tabWidget并显示
    ui->tabWidget->addTab(wordWidget, cur_word);
    ui->tabWidget->setCurrentWidget(wordWidget);

    //向mainWindow发射信号
    emit clearMes();
}


void QueryWidget::on_tabWidget_tabCloseRequested(int index)
{
    //把wordWidget移除tabWidget并析构该对象
    QWidget* tmp = ui->tabWidget->widget(index);
    ui->tabWidget->removeTab(index);
    delete tmp;
}

