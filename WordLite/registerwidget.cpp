#include "registerwidget.h"
#include "ui_registerwidget.h"
#include "back_head/learner.h"
#include "MainWindow.h"
#include "loginwidget.h"
#include "darktheme_win.h"
#include "achievementwidget.h" // 新增：包含 AchievementWidget 的完整定义
#include <QIcon>
#include <QTimer>
#include <QFont>

registerWidget::registerWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::registerWidget)
{
    ui->setupUi(this);
    setWindowTitle("register");
    setWindowIcon(QIcon(":/icons/favicon_logosc/t_logo.png"));
    setFixedSize(350, 350);
    connect(ui->registerButton,&QToolButton::clicked,this,&registerWidget::saveUser);
    connect(ui->backButton, &QToolButton::clicked, this, &registerWidget::goBackToLogin); // 新增连接
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    ui->verifyLineEdit->setEchoMode(QLineEdit::Password);

    // --- 新增代码：设置回车键导航 ---
    // 在用户名输入框按回车，焦点移至密码框
    // 使用 lambda 解决 setFocus 的重载问题
    connect(ui->userLineEdit, &QLineEdit::returnPressed, this, [=](){
        ui->passwordLineEdit->setFocus();
    });
    // 在密码输入框按回车，焦点移至确认密码框
    // 使用 lambda 解决 setFocus 的重载问题
    connect(ui->passwordLineEdit, &QLineEdit::returnPressed, this, [=](){
        ui->verifyLineEdit->setFocus();
    });
    // 在确认密码输入框按回车，触发注册
    connect(ui->verifyLineEdit, &QLineEdit::returnPressed, this, &registerWidget::saveUser);
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

    // 检查用户名是否为空
    if (userName.isEmpty())
    {
        ui->textLabel->setText("注册失败，用户名不能为空");
        QFont font("黑体",12);
        ui->textLabel->setFont(font);
        ui->textLabel->setAlignment(Qt::AlignCenter);
        // 3秒后自动清除提示信息
        QTimer::singleShot(3000, ui->textLabel, &QLabel::clear);
        return; // 提前返回，不继续执行
    }

    // 检查密码是否为空
    if (password.isEmpty())
    {
        ui->textLabel->setText("注册失败，密码不能为空");
        QFont font("黑体",12);
        ui->textLabel->setFont(font);
        ui->textLabel->setAlignment(Qt::AlignCenter);
        // 3秒后自动清除提示信息
        QTimer::singleShot(3000, ui->textLabel, &QLabel::clear);
        return; // 提前返回，不继续执行
    }

    // 检查两次密码是否一致
    if (password!=verify)
    {
        qDebug()<<password<<' '<<verify;
        ui->textLabel->setText("注册失败，密码不一致");
        QFont font("黑体",12);
        ui->textLabel->setFont(font);
        ui->textLabel->setAlignment(Qt::AlignCenter);
        // 3秒后自动清除提示信息
        QTimer::singleShot(3000, ui->textLabel, &QLabel::clear);
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

    // 现在编译器知道 unlockAchievement 是什么了
    w->achievementWidget->unlockAchievement(1);

    this->close();
}

// 新增：返回登录界面的槽函数实现
void registerWidget::goBackToLogin()
{
    loginWidget *l = new loginWidget();
    l->show();
    // 修复：变量名应为 l，而不是 w
    setDarkTitleBar(l->winId());
    this->close(); // 关闭当前的注册窗口
}
