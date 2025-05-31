#include "userwidget.h"
#include "ui_userwidget.h"
#include "back_head/learner.h"
#include "back_head/database.h"
#include <QPainter>
#include <QTimer>
#define Min(x,y) x>y?y : x

UserWidget::UserWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserWidget)
{
    ui->setupUi(this);
    connect(ui->clearButton,&QToolButton::clicked,this,&UserWidget::clear);
    connect(ui->refreshButton,&QToolButton::clicked,this,&UserWidget::refresh);
    setUser();
    setTotalAcc();
    setDays();
    setAcc();
    //setPic();
    update();
    qDebug()<<ui->accWidget->height()<<' '<<ui->accWidget->width();
}

UserWidget::~UserWidget()
{
    delete ui;
}

void UserWidget::setUser()
{
    Learner * learner=Learner::getInstance();
    ui->userLabel->setText(learner->getName());
    QFont *font=new QFont("黑体",16);
    font->setBold(true);
    ui->userLabel->setFont(*font);
    ui->userLabel->setAlignment(Qt::AlignCenter);
}

void UserWidget::setPic()
{

}

void UserWidget::setDays()
{
    dailyLearningData=WordDatabase::getAllDailyLearningCountInDays(30,1);
}

void UserWidget::setAcc()
{
    dailyLearningAcc=WordDatabase::getAllDailyLearningAccuracyInDays(30,1);
}

void UserWidget::setTotalAcc()
{
    double acc=(WordDatabase::getAllLearningAccuracy(30,1));
    ui->accLabel->setText("累计正确率："+QString::number(acc,'f',4));
    QFont *font=new QFont("黑体",16);
    font->setBold(true);
    ui->accLabel->setFont(*font);
    ui->accLabel->setAlignment(Qt::AlignCenter);
}

void UserWidget::paintEvent(QPaintEvent *event)
{
    qDebug()<<"paint";
    Q_UNUSED(event);
    QPainter painter(this);
    QRect dayRect=ui->dayWidget->geometry();
    QRect accRect=ui->accWidget->geometry();
    painter.save();
    painter.translate(dayRect.topLeft());
    int max_count=100;
    for (int i=0;i<10;++i)
    {
        for (int j=0;j<3;++j)
        {
            int count=dailyLearningData[j*10+i];
            int colorValue=Min(255,count*255/max_count);
            QColor color(255-colorValue,255,255-colorValue);
            int x=MARGIN*(i+1)+WIDTH*i;
            int y=MARGIN*(j+1)+WIDTH*j;
            painter.fillRect(x,y,WIDTH,WIDTH,color);
            painter.setPen(Qt::green);
            painter.drawRect(x,y,WIDTH,WIDTH);
        }
    }
    painter.restore();  // 恢复状态

    // 绘制正确率统计
    painter.save();
    painter.translate(accRect.topLeft());
    for (int i=0;i<10;++i)
    {
        for (int j=0;j<3;++j)
        {
            double acc=dailyLearningAcc[j*10+i];
            int colorValue=Min(255,static_cast<int>(acc*255));
            QColor color(255,255-colorValue,255-colorValue);
            int x=MARGIN*(i+1)+WIDTH*i;
            int y=MARGIN*(j+1)+WIDTH*j;
            painter.fillRect(x,y,WIDTH,WIDTH,color);
            painter.setPen(Qt::red);
            painter.drawRect(x,y,WIDTH,WIDTH);
        }
    }
}

void UserWidget::clear()
{
    WordDatabase::resetAll();
    ui->clearLabel->setText("已清空");
    QFont *font=new QFont("黑体",16);
    font->setBold(true);
    ui->clearLabel->setFont(*font);
    ui->clearLabel->setAlignment(Qt::AlignCenter);
    refresh();
    QTimer::singleShot(1000,this,[=](){ui->clearLabel->setText("");});
}

void UserWidget::refresh()
{
    setUser();
    setTotalAcc();
    setDays();
    setAcc();
    //setPic();
    update();
}
