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
    UserWidget* userWidget = new UserWidget;
    QueryWidget* queryWidget = new QueryWidget;
    LearnWidget* learnWidget = new LearnWidget;
    ReviewWidget* reviewWidget = new ReviewWidget;
    AchievementWidget* achievementWidget = new AchievementWidget;
    GameWidget* gameWidget = new GameWidget;

    ui->stackedWidget->addWidget(userWidget);
    ui->stackedWidget->addWidget(queryWidget);
    ui->stackedWidget->addWidget(learnWidget);
    ui->stackedWidget->addWidget(reviewWidget);
    ui->stackedWidget->addWidget(achievementWidget);
    ui->stackedWidget->addWidget(gameWidget);

}

void MainWindow::connectSignals(){
    //设置默认定位
    ui->stackedWidget->setCurrentIndex(0);
    //用户界面
    connect(ui->userButton, &QToolButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(0);
    });
    //查询界面
    connect(ui->queryButton, &QToolButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(1);
    });
    //学习界面
    connect(ui->learnButton, &QToolButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(2);
    });
    //复习界面
    connect(ui->reviewButton, &QToolButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(3);
    });
    //成就界面
    connect(ui->achievementButton, &QToolButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(4);
    });
    //游戏界面
    connect(ui->gameButton, &QToolButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(5);
    });
}


