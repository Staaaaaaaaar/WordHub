#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "../back_head/learner.h"
#include "mainwindow.h"
#include "registerwidget.h"
#include "darktheme_win.h" // 新增头文件
#include <QIcon> // 确保包含头文件

loginWidget::loginWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::loginWidget)
{
    // 恢复为标准UI加载方式
    ui->setupUi(this);

    // 设置窗口标题
    setWindowTitle("login");

    // 设置窗口图标（Logo）
    // 请确保您有一个logo.png文件，并已将其添加到项目的资源文件(.qrc)中
    // 路径以 :/ 开始表示从资源文件加载。
    setWindowIcon(QIcon(":/icons/img/t_logo.png"));

    setFixedSize(350, 300); // 设置固定大小

    // 连接原有的信号槽
    connect(ui->loginButton,&QToolButton::clicked,this,&loginWidget::judgeLogin);
    connect(ui->registerButton,&QToolButton::clicked,this,&loginWidget::skipToRegister);
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);

    // --- 新增代码：设置回车键导航 ---
    // 在用户名输入框按回车，焦点移至密码框
    // 使用 lambda 解决 setFocus 的重载问题
    connect(ui->userLineEdit, &QLineEdit::returnPressed, this, [=](){
        ui->passwordLineEdit->setFocus();
    });
    // 在密码输入框按回车，触发登录判断
    connect(ui->passwordLineEdit, &QLineEdit::returnPressed, this, &loginWidget::judgeLogin);
}

loginWidget::~loginWidget()
{
    delete ui;
}



bool loginWidget::readUser()
{
    QString userName=ui->userLineEdit->text();
    Learner * learner=Learner::getInstance();
    bool isUsernameValid=learner->verifyUserName(userName);
    return isUsernameValid;
}

bool loginWidget::comparePassword(const QString & username)
{
    QString password=ui->passwordLineEdit->text();
    Learner * learner=Learner::getInstance();
    bool isPasswordValid=learner->verifyPasswordU(username,password);
    return isPasswordValid;
}

void loginWidget::judgeLogin()
{
    if (readUser())
    {
        QString username=ui->userLineEdit->text();
        qDebug()<<"用户验证成功";
        if (comparePassword(username))
        {
            MainWindow * w=new MainWindow();
            w->show();
            setDarkTitleBar(w->winId()); // 应用深色标题栏
            this->close();
        }
        else
        {
            ui->textLabel->setText("用户名或密码错误");
            QFont font("黑体",12);
            ui->textLabel->setFont(font);
            ui->textLabel->setAlignment(Qt::AlignCenter);
        }
    }
    else
    {
        ui->textLabel->setText("用户名或密码错误");
        QFont font("黑体",12);
        ui->textLabel->setFont(font);
        ui->textLabel->setAlignment(Qt::AlignCenter);
    }
}

void loginWidget::skipToRegister()
{
    registerWidget *r=new registerWidget();
    r->show();
    setDarkTitleBar(r->winId()); // 应用深色标题栏
    this->close();
}
