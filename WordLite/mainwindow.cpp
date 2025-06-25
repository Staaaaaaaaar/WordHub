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
        // 断开learnWidget的数据库连接
        learnWidget->DBptr->closeCurrentDatabase();
        // learnWidget->setupUI();
    });
    //学习界面
    connect(ui->learnButton, &QToolButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(2);
        // 断开queryWidget的数据库连接
        queryWidget->wordDataBase->closeCurrentDatabase();
        // learnWidget->setupUI();
        // emit learnWidgerInit();
    });

    //复习界面
    // connect(ui->reviewButton, &QToolButton::clicked, this, [=](){
    //     ui->stackedWidget->setCurrentIndex(3);
    // });

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
        // 断开queryWidget的数据库连接
        queryWidget->wordDataBase->closeCurrentDatabase();
        // 断开learnWidget的数据库连接
        learnWidget->DBptr->closeCurrentDatabase();
    });

    //退出
    connect(ui->exitButton,&QToolButton::clicked,this,&MainWindow::exitSignal);

    connect(queryWidget, SIGNAL(sendMes(QString,int)), this, SLOT(showMes(QString,int)));
    connect(queryWidget, SIGNAL(clearMes()), this, SLOT(clearMes()));

    connect(queryWidget, &QueryWidget::sendId, this, [=](int id){
        if (!achievementWidget->testAchievements[id].unlocked) {
            achievementWidget->refreshAchievements(id); // 标记为达成并更新UI
            showMes("达成成就：" + achievementWidget->testAchievements[id].title, 2000);
        }
    });
    connect(learnWidget, &LearnWidget::sendId, this, [=](int id){
        if (!achievementWidget->testAchievements[id].unlocked) {
            achievementWidget->refreshAchievements(id); // 标记为达成并更新UI
            showMes("达成成就：" + achievementWidget->testAchievements[id].title, 2000);
        }
    });
    connect(gameWidget, &GameWidget::sendId, this, [=](int id){
        if (!achievementWidget->testAchievements[id].unlocked) {
            achievementWidget->refreshAchievements(id); // 标记为达成并更新UI
            showMes("达成成就：" + achievementWidget->testAchievements[id].title, 2000);
        }
    });

    // connect(this, SIGNAL(ach_register(int)), achievementWidget, SLOT(refreshAchievements(int)));
    

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
    this->hide();
    loginWidget *l = new loginWidget();
    l->setAttribute(Qt::WA_DeleteOnClose);
    l->show();
}

