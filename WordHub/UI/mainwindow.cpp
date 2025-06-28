#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginwidget.h"
#include "achievementtoast.h"
#include "darktheme_win.h"

// 新增：包含所有子窗口部件的头文件
#include "userwidget.h"
#include "querywidget.h"
#include "learnwidget.h"
#include "achievementwidget.h"
#include "gamewidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 新增：为MainWindow也设置图标和标题
    setWindowTitle("WordHub");
    setWindowIcon(QIcon(":/icons/img/logo.png"));

    // 限制窗口大小
    setMinimumSize(800, 600);

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
    // 设置默认定位
    ui->stackedWidget->setCurrentIndex(0);

    // 核心思路：在激活任何新界面前，先统一关闭其他可能占用数据库的界面。
    // 这样可以确保任何时候只有一个界面持有数据库连接。

    // 用户界面
    connect(ui->userButton, &QToolButton::clicked, this, [=](){
        queryWidget->wordDataBase->closeCurrentDatabase();
        learnWidget->DBptr->closeCurrentDatabase();
        ui->stackedWidget->setCurrentIndex(0);
        // userWidget->setupUI(); // 如果用户界面也需要初始化，取消此行注释
    });

    // 查询界面
    connect(ui->queryButton, &QToolButton::clicked, this, [=](){
        // 先关闭其他界面的数据库
        learnWidget->DBptr->closeCurrentDatabase();
        // 再激活自己
        ui->stackedWidget->setCurrentIndex(1);
        queryWidget->setupUI(); // queryWidget的setupUI会打开它自己的数据库
    });

    // 学习界面
    connect(ui->learnButton, &QToolButton::clicked, this, [=](){
        // 先关闭其他界面的数据库
        queryWidget->wordDataBase->closeCurrentDatabase();
        // 再激活自己
        ui->stackedWidget->setCurrentIndex(2);
        learnWidget->setupUI(); // learnWidget的setupUI会打开它自己的数据库
    });

    // 成就界面
    connect(ui->achievementButton, &QToolButton::clicked, this, [=](){
        queryWidget->wordDataBase->closeCurrentDatabase();
        learnWidget->DBptr->closeCurrentDatabase();
        ui->stackedWidget->setCurrentIndex(3);
        achievementWidget->refreshUI(); // 刷新成就界面
    });

    // 游戏界面
    connect(ui->gameButton, &QToolButton::clicked, this, [=](){
        queryWidget->wordDataBase->closeCurrentDatabase();
        learnWidget->DBptr->closeCurrentDatabase();
        ui->stackedWidget->setCurrentIndex(4);
        gameWidget->setupUI();
    });

    //退出
    connect(ui->exitButton,&QToolButton::clicked,this,&MainWindow::exitSignal);

    connect(queryWidget, SIGNAL(sendMes(QString,int)), this, SLOT(showMes(QString,int)));
    connect(queryWidget, SIGNAL(clearMes()), this, SLOT(clearMes()));

    connect(queryWidget, &QueryWidget::sendId, achievementWidget, &AchievementWidget::unlockAchievement);
    connect(learnWidget, &LearnWidget::sendId, achievementWidget, &AchievementWidget::unlockAchievement);
    connect(gameWidget, &GameWidget::sendId, achievementWidget, &AchievementWidget::unlockAchievement);

    connect(achievementWidget, &AchievementWidget::achievementUnlocked, this, &MainWindow::showAchievementToast);

    // --- 修改：使用正确的成员变量指针进行连接 ---
    connect(userWidget, &UserWidget::requestUnlockAchievement,
            achievementWidget, &AchievementWidget::unlockAchievement);
}

void MainWindow::showMes(QString message, int timeout)
{
    ui->statusbar->showMessage(message, timeout);
}
void MainWindow::clearMes()
{
    ui->statusbar->clearMessage();
}

void MainWindow::exitSignal()
{
    this->close(); // 使用 close() 替代 hide()，确保主窗口被销毁
    loginWidget *l = new loginWidget();
    l->setAttribute(Qt::WA_DeleteOnClose);
    l->show();
    // 为新创建的登录窗口应用深色标题栏
    setDarkTitleBar(l->winId());
}

// 新增：实现成就弹窗的槽函数
void MainWindow::showAchievementToast(const Achievement &achievement)
{
    AchievementToast *toast = new AchievementToast(this);
    toast->showAchievement(achievement);
}

