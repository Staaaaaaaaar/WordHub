#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置默认定位
    ui->stackedWidget->setCurrentIndex(0);
    //用户界面
    connect(ui->btn_user, &QToolButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(0);
    });
    //查询界面
    connect(ui->btn_query, &QToolButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(1);
    });
    //学习界面
    connect(ui->btn_learn, &QToolButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(2);
    });
    //复习界面
    connect(ui->btn_review, &QToolButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(3);
    });
    //成就界面
    connect(ui->btn_achievement, &QToolButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(4);
    });
    //游戏界面
    connect(ui->btn_game, &QToolButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(5);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
