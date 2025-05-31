#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "back_head/learner.h"
#include "mainwindow.h"
#include "registerwidget.h"

loginWidget::loginWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::loginWidget)
{
    ui->setupUi(this);
    connect(ui->loginButton,&QToolButton::clicked,this,&loginWidget::judgeLogin);
    connect(ui->registerButton,&QToolButton::clicked,this,&loginWidget::skipToRegister);
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
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
    this->close();
}
