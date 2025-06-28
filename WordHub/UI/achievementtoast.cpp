#include "achievementtoast.h"
#include <QScreen>
#include <QGuiApplication>

AchievementToast::AchievementToast(QWidget *parent)
    : QWidget(parent)
{
    // 修改点 2: 移除 Qt::Tool 和 Qt::WindowStaysOnTopHint 标志。
    // 这使得控件成为一个真正的子控件，其绘制将被父窗口裁剪。
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_DeleteOnClose);

    // 主体框架
    QWidget *mainWidget = new QWidget(this);
    mainWidget->setObjectName("mainWidget");
    mainWidget->setStyleSheet(
        "#mainWidget {"
        "   background-color: rgba(40, 40, 40, 0.9);"
        "   border-radius: 10px;"
        "   border: 1px solid #444;"
        "}"
    );

    iconLabel = new QLabel(this);
    titleLabel = new QLabel(this);
    descLabel = new QLabel(this);

    // 为所有标签设置透明背景，防止出现渲染瑕疵
    iconLabel->setStyleSheet("background-color: transparent;");
    titleLabel->setStyleSheet("font-size: 14px; font-weight: bold; color: #FFD700; background-color: transparent;");
    descLabel->setStyleSheet("font-size: 12px; color: white; background-color: transparent;");

    QVBoxLayout *textLayout = new QVBoxLayout();
    textLayout->addWidget(titleLabel);
    textLayout->addWidget(descLabel);
    textLayout->setSpacing(2);

    QHBoxLayout *mainLayout = new QHBoxLayout(mainWidget);
    mainLayout->addWidget(iconLabel, 0, Qt::AlignCenter);
    mainLayout->addLayout(textLayout);
    mainLayout->setContentsMargins(15, 10, 15, 10);
    mainLayout->setSpacing(10);

    // 使用一个布局来容纳 mainWidget，以便整个 toast 可以正确调整大小
    QHBoxLayout *baseLayout = new QHBoxLayout(this);
    baseLayout->addWidget(mainWidget);
    baseLayout->setContentsMargins(0,0,0,0);
    setLayout(baseLayout);

    animation = new QPropertyAnimation(this, "pos", this);
}

void AchievementToast::showAchievement(const Achievement &achievement)
{
    titleLabel->setText(achievement.title);
    descLabel->setText("新成就已解锁！");
    QPixmap pixmap(achievement.iconPath);
    iconLabel->setPixmap(pixmap.scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    adjustSize(); // 根据内容调整大小

    QWidget *parent = parentWidget();
    if (!parent) return;

    // 修改点 1: 将位置计算基准点改为右下角。
    QRect parentContents = parent->contentsRect();
    int margin = 10; // 边距

    // 最终显示的位置（在父窗口右下角）
    QPoint endPos(parentContents.width() - this->width() - margin,
                  parentContents.height() - this->height() - margin);
    // 动画开始的位置（在窗口右侧外）
    QPoint startPos(parentContents.width(), endPos.y());

    this->move(startPos);
    this->show();
    this->raise(); // 修改点 2: 提升层级，确保显示在最上层

    // 设置动画
    animation->setDuration(400); // 动画时长
    animation->setStartValue(startPos);
    animation->setEndValue(endPos);
    animation->setEasingCurve(QEasingCurve::OutCubic); // 缓动曲线
    animation->start();

    // 3秒后自动关闭
    QTimer::singleShot(3000, this, [this, endPos, startPos](){
        // 创建消失动画
        animation->setStartValue(endPos);
        animation->setEndValue(startPos);
        animation->start();
        // 动画结束后关闭窗口
        connect(animation, &QPropertyAnimation::finished, this, &QWidget::close);
    });
}