#include "learnwidget.h"
#include "ui_learnwidget.h"

LearnWidget::LearnWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LearnWidget)
{
    ui->setupUi(this);
    //初始化defaultButtons

    //初始化customizeButtons

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
    //设置按钮间距
    ui->defaultLayout->setSpacing(10);
    ui->customizeLayout->setSpacing(10);
    //设置边距
    ui->defaultLayout->setContentsMargins(10, 10, 10, 10);
    ui->customizeLayout->setContentsMargins(10, 10, 10, 10);

    //设置默认词库
    defaultButtons.clear();
    for (int i = 0; i < 6; ++i) {
        defaultButtons.append(new DictButton(QString("默认%1").arg(i+1)));
    }
    addButtonsToGrid(ui->defaultLayout, defaultButtons, 4);

    //设置自定义词库
    customizeButtons.clear();
    for (int i = 0; i < 5; ++i) {
        customizeButtons.append(new DictButton(QString("自定义%1").arg(i+1)));
    }
    // customizeButtons.append(addDictButton);
    addButtonsToGrid(ui->customizeLayout, customizeButtons+QList<DictButton*>(1, addDictButton), 4);
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
    //跳转到测试界面
    connect(ui->testButton, &QToolButton::clicked, this, &LearnWidget::on_testButton_clicked);
    //返回
    connect(ui->backButton, &QToolButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(0);});
    connect(ui->backButton_2, &QToolButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(1);});
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

}
void LearnWidget::initTestWidget()
{

}


void LearnWidget::on_dictButton_clicked()
{
    //跳转到词库信息界面
    ui->stackedWidget->setCurrentIndex(1);
    //初始化界面
    initDictWidget();
}
void LearnWidget::on_addDictButton_clicked()
{
    //浏览文件
}
void LearnWidget::on_testButton_clicked()
{
    //跳转到测试界面
    ui->stackedWidget->setCurrentIndex(2);
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

