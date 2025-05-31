#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    // 设置UI和连接信号槽
    setupUI();
    connectSignals();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupUI(){
    userWidget = new UserWidget(this);
    queryWidget = new QueryWidget(this);
    learnWidget = new LearnWidget(this);
    achievementWidget = new AchievementWidget(this);
    gameWidget = new GameWidget(this);

    ui->stackedWidget->addWidget(userWidget);
    ui->stackedWidget->addWidget(queryWidget);
    ui->stackedWidget->addWidget(learnWidget);
    ui->stackedWidget->addWidget(achievementWidget);
    ui->stackedWidget->addWidget(gameWidget);

}

void MainWindow::connectSignals(){
    //设置默认定位
    ui->stackedWidget->setCurrentIndex(0);
    //用户界面
    connect(ui->userButton, &QToolButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(0);
        // learnWidget->setupUI();
    });
    //查询界面
    connect(ui->queryButton, &QToolButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(1);
        queryWidget->setupUI();
        // learnWidget->setupUI();
    });
    //学习界面
    connect(ui->learnButton, &QToolButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(2);
        // learnWidget->setupUI();
        // emit learnWidgerInit();
    });
    //成就界面
    connect(ui->achievementButton, &QToolButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(3);
        // learnWidget->setupUI();
    });
    //游戏界面
    connect(ui->gameButton, &QToolButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(4);
        // learnWidget->setupUI();
        gameWidget->setupUI();
        // emit gameWidgerInit();
    });

    connect(queryWidget, SIGNAL(sendMes(QString,int)), this, SLOT(showMes(QString,int)));
    connect(queryWidget, SIGNAL(clearMes()), this, SLOT(clearMes()));

    // connect(this, SIGNAL(learnWidgerInit()), learnWidget, SLOT());
    // connect(this, SIGNAL(gameWidgerInit()), gameWidget, SLOT());

}

void MainWindow::showMes(QString message, int timeout)
{
    ui->statusbar->showMessage(message, timeout);
}
void MainWindow::clearMes()
{
    ui->statusbar->clearMessage();
}

