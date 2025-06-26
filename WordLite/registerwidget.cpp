#include "registerwidget.h"
#include "ui_registerwidget.h"
#include "back_head/learner.h"
#include "MainWindow.h"
#include "darktheme_win.h" // 新增头文件
#include <QIcon> 

registerWidget::registerWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::registerWidget)
{
    ui->setupUi(this);
    setWindowTitle("register");
    setWindowIcon(QIcon(":/icons/favicon_logosc/t_logo.png"));
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
    MainWindow *w = new MainWindow();
    w->show();
    setDarkTitleBar(w->winId()); // 应用深色标题栏

    // 使用新的方法解锁“初次相遇”成就
    w->achievementWidget->unlockAchievement(1);

    this->close();
}
