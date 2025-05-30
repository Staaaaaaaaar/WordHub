#include "learnwidget.h"
#include "ui_learnwidget.h"


LearnWidget::LearnWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LearnWidget)
{
    ui->setupUi(this);

    DBptr = new WordDatabase();
    //初始化defaultDictNames
    defaultDictNames = DBptr->getlist();
    //设置UI和连接信号槽
    setupUI();
    connectSignals();

}

LearnWidget::~LearnWidget()
{
    delete ui;
}
void LearnWidget::setupUI()
{
    //设置初始界面
    ui->stackedWidget->setCurrentIndex(0);
    //设置添加词库按钮
    addDictButton = new DictButton("+");


    // 响应式布局：用QScrollArea+QWidget+QGridLayout
    QWidget* defaultContainer = new QWidget;
    QGridLayout* defaultGrid = new QGridLayout(defaultContainer);
    defaultGrid->setSpacing(10);
    defaultGrid->setContentsMargins(10, 10, 10, 10);

    int columns = 4; // 可根据窗口宽度动态调整
    for (int i = 0; i < defaultDictNames.size(); ++i) {
        DictButton* btn = new DictButton(defaultDictNames[i]);
        int row = i / columns;
        int col = i % columns;
        defaultGrid->addWidget(btn, row, col);
        // 可连接信号
        connect(btn, &QToolButton::clicked, this, &LearnWidget::on_dictButton_clicked);
    }
    // 添加“+”按钮
    int addRow = defaultDictNames.size() / columns;
    int addCol = defaultDictNames.size() % columns;
    defaultGrid->addWidget(addDictButton, addRow, addCol);
    connect(addDictButton, &QToolButton::clicked, this, &LearnWidget::on_addDictButton_clicked);

    defaultContainer->setLayout(defaultGrid);
    QScrollArea* defaultScroll = new QScrollArea;
    defaultScroll->setWidgetResizable(true);
    defaultScroll->setWidget(defaultContainer);
    // 为defaultBox新建布局
    QVBoxLayout* defaultBoxLayout = new QVBoxLayout();
    defaultBoxLayout->addWidget(defaultScroll);
    ui->defaultBox->setLayout(defaultBoxLayout);


}


void LearnWidget::connectSignals()
{
    //点击词库跳转到词库信息界面
    for (DictButton* dictButton : std::as_const(defaultButtons)) {
        connect(dictButton, &QToolButton::clicked, this, &LearnWidget::on_dictButton_clicked);
    }
    for (DictButton* dictButton : std::as_const(customizeButtons)) {
        connect(dictButton, &QToolButton::clicked, this, &LearnWidget::on_dictButton_clicked);
    }
    //点击“+”添加自定义词库
    connect(addDictButton, &QToolButton::clicked, this, &LearnWidget::on_addDictButton_clicked);
    //跳转到words界面
    connect(ui->learnButton, &QToolButton::clicked, this, &LearnWidget::on_learnButton_clicked);
    connect(ui->reviewButton, &QToolButton::clicked, this, &LearnWidget::on_reviewButton_clicked);
    //跳转到测试界面
    connect(ui->testButton, &QToolButton::clicked, this, &LearnWidget::on_testButton_clicked);
    //返回
    connect(ui->backButton, &QToolButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(0);});
    connect(ui->backButton_2, &QToolButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(1);});
    connect(ui->backButton_3, &QToolButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(2);});
}

void LearnWidget::addButtonsToGrid(QGridLayout *grid, const QList<DictButton*> &buttons, int columns)
{
    for (int i = 0; i < buttons.size(); ++i) {
        int row = i / columns;
        int col = i % columns;
        grid->addWidget(buttons.at(i), row, col);
    }
}
void LearnWidget::initDictWidget()
{
    QString name = qobject_cast<DictButton*>(sender())->text();
    ui->dictName->setText(name);
}
void LearnWidget::initWordsWidget()
{

}
void LearnWidget::initTestWidget()
{

}

void LearnWidget::on_addDictButton_clicked()
{
    //浏览文件
}
void LearnWidget::on_dictButton_clicked()
{
    //跳转到词库信息界面
    ui->stackedWidget->setCurrentIndex(1);
    QString name = qobject_cast<DictButton*>(sender())->text();
    DBptr->initDatabase(name);
    //初始化界面
    initDictWidget();
}
void LearnWidget::on_reviewButton_clicked()
{
    //跳转到words界面
    ui->stackedWidget->setCurrentIndex(2);
}


void LearnWidget::on_learnButton_clicked()
{
    //跳转到words界面
    ui->stackedWidget->setCurrentIndex(2);
}
void LearnWidget::on_testButton_clicked()
{
    //跳转到测试界面
    ui->stackedWidget->setCurrentIndex(3);
    //初始化界面
    initTestWidget();
}






DictButton::DictButton(QString text) //传入字典指针
{
    this->setText(text);
    this->setFixedSize(60, 60); // 设置固定大小
}

DictButton::~DictButton()
{

}




