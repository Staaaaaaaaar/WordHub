#include "querywidget.h"
#include "ui_querywidget.h"

QueryWidget::QueryWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QueryWidget)
{
    ui->setupUi(this);


    //初始化成员变量
    wordDataBase = new WordDatabase;
    wordDBList = WordDatabase::getlist();


    // 设置UI和连接信号槽
    setupUI();
    connectSignals();

}

QueryWidget::~QueryWidget()
{
    ui->tabWidget->clear();
    delete ui;
}

void QueryWidget::setupUI()
{
    //设置comboBox
    for (const QString &DBname: std::as_const(wordDBList))
    {
        ui->comboBox->addItem(DBname);
    }
    //初始化连接
    if (!wordDBList.isEmpty()) wordDataBase->initDatabase(wordDBList.first());

}

void QueryWidget::connectSignals()
{
    connect(ui->searchEdit, &QLineEdit::returnPressed, this, &QueryWidget::on_searchEdit_returnPressed);
    connect(ui->comboBox, &QComboBox::currentTextChanged, this, &QueryWidget::on_comboBox_currentTextChanged);

    connect(wordWidget, SIGNAL(WordWidget::sendMes(QString,int)), this, SLOT(showMes(QString,int)));
    connect(wordWidget, SIGNAL(WordWidget::clearMes()), this, SLOT(clearMes()));
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
            emit sendMes(cur_word + "查询完成", 3000);
            return;
        }
    }
    //判断word是否是个有效查询
    QVector<Word> wordList = wordDataBase->getWordsByName(cur_word);
    if (wordList.isEmpty())
    {
        emit sendMes("未找到相关单词", 3000);
        return;
    }
    //生成一个实例wordWidget
    wordWidget = new WordWidget(cur_word, wordDataBase, this);
    wordWidget->setupUI(wordList);
    //将wordWidget装入tabWidget并显示
    ui->tabWidget->addTab(wordWidget, cur_word);
    ui->tabWidget->setCurrentWidget(wordWidget);

    //向mainWindow发射信号
    emit sendMes(cur_word + "查询完成", 3000);
}


void QueryWidget::on_tabWidget_tabCloseRequested(int index)
{
    //把wordWidget移除tabWidget并析构该对象
    QWidget* tmp = ui->tabWidget->widget(index);
    ui->tabWidget->removeTab(index);
    delete tmp;
}


void QueryWidget::on_comboBox_currentTextChanged(const QString &DBname)
{
    emit sendMes("正在连接数据库 "+DBname);
    if (wordDataBase->initDatabase(DBname)) emit sendMes("成功连接数据库 "+DBname, 3000);
    else emit sendMes("连接失败", 3000);
}

void QueryWidget::showMes(QString message, int timeout)
{
    emit sendMes(message, timeout);
}
void QueryWidget::clearMess()
{
    emit clearMes();
}
