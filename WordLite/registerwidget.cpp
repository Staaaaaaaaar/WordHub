#include "registerwidget.h"
#include "ui_registerwidget.h"
#include "back_head/learner.h"
#include "MainWindow.h"

registerWidget::registerWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::registerWidget)
{
    ui->setupUi(this);
    connect(ui->registerButton,&QToolButton::clicked,this,&registerWidget::saveUser);
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    ui->verifyLineEdit->setEchoMode(QLineEdit::Password);
}

registerWidget::~registerWidget()
{
    delete ui;
}

void registerWidget::saveUser()
{
    QString userName=ui->userLineEdit->text();
    QString password=ui->passwordLineEdit->text();
    QString verify=ui->verifyLineEdit->text();
    if (password!=verify)
    {
        qDebug()<<password<<' '<<verify;
        ui->textLabel->setText("注册失败，密码不一致");
        QFont font("黑体",12);
        ui->textLabel->setFont(font);
        ui->textLabel->setAlignment(Qt::AlignCenter);
    }
    else
    {
        Learner * learner=Learner::getInstance();
        learner->resetUser(true);
        learner->createNewUser(userName,password);
        skip();
    }
}

void registerWidget::skip()
{
    MainWindow *w=new MainWindow();
    w->show();
    this->close();
}
