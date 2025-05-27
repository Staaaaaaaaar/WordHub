#include "achievementwidget.h"
#include "ui_achievementwidget.h"

AchievementWidget::AchievementWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AchievementWidget)
    , scrollArea(nullptr)
    , scrollContent(nullptr)
    , scrollLayout(nullptr)
{
    ui->setupUi(this);
    setupUI();
    connectSignals();
    refreshAchievements(); // 构造时刷新成就显示
}

AchievementWidget::~AchievementWidget()
{
    delete ui;
}

void AchievementWidget::setupUI()
{
    // 主布局
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->setSpacing(10);

    // 滚动区域
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);

    // 滚动内容
    scrollContent = new QWidget();
    scrollLayout = new QVBoxLayout();
    scrollLayout->setAlignment(Qt::AlignTop);
    scrollContent->setLayout(scrollLayout);
    scrollArea->setWidget(scrollContent);

    mainLayout->addWidget(scrollArea);
    setLayout(mainLayout);
}

void AchievementWidget::connectSignals()
{
    // 连接外部信号示例（需要与实际信号源连接）
    // connect(externalObject, SIGNAL(achievementUnlocked(int)),
    //         this, SLOT(refreshAchievements()));
}

QVector<Achievement> getAchievementsFromSource()
{
    return {
        {1, "初出茅庐", "完成首次学习", true, QDateTime::currentDateTime(), ":/icons/achievement1.png"},
        {2, "持之以恒", "连续学习7天", false, QDateTime(), ":/icons/locked.png"},
        {3, "大师之路", "掌握500个单词", false, QDateTime(), ":/icons/locked.png"},
        {4, "百尺竿头", "累计学习100天", false, QDateTime(), ":/icons/locked.png"},
        {5, "词海无涯", "累计学习1000个单词", false, QDateTime(), ":/icons/locked.png"},
        {6, "日积月累", "连续学习30天", false, QDateTime(), ":/icons/locked.png"},
        {7, "坚持不懈", "连续学习100天", false, QDateTime(), ":/icons/locked.png"},
        {8, "词霸达人", "掌握2000个单词", false, QDateTime(), ":/icons/locked.png"},
        {9, "学无止境", "累计学习365天", false, QDateTime(), ":/icons/locked.png"},
        {10, "全成就达成", "解锁所有成就", false, QDateTime(), ":/icons/locked.png"},
        // 隐藏成就
        {101, "？？？", "发现彩蛋", false, QDateTime(), ":/icons/hidden.png"},
        {102, "？？？", "在凌晨4点学习", false, QDateTime(), ":/icons/hidden.png"},
        {103, "？？？", "一天内学习超过10次", false, QDateTime(), ":/icons/hidden.png"},
        {104, "？？？", "连续30天未中断", false, QDateTime(), ":/icons/hidden.png"}
    };
}

void AchievementWidget::refreshAchievements()
{
    // 清空旧内容
    QLayoutItem* item;
    while ((item = scrollLayout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            item->widget()->deleteLater();
        }
        delete item;
    }

    QVector<Achievement> achievements = getAchievementsFromSource();

    for (const Achievement &achievement : achievements) {
        QWidget *itemWidget = new QWidget();
        QHBoxLayout *hLayout = new QHBoxLayout(itemWidget);
        hLayout->setContentsMargins(28, 18, 28, 18); // 更大内边距
        hLayout->setSpacing(28); // 更大间距

        // 图标
        QLabel *iconLabel = new QLabel();
        QPixmap pixmap(achievement.iconPath);
        if (!achievement.unlocked)
            pixmap = pixmap.scaled(56, 56, Qt::KeepAspectRatio, Qt::SmoothTransformation); // 更大图标
        iconLabel->setPixmap(pixmap);
        iconLabel->setFixedSize(68, 68); // 更大图标区域

        // 文字信息
        QVBoxLayout *textLayout = new QVBoxLayout();
        textLayout->setSpacing(8); // 更大行间距
        QLabel *titleLabel = new QLabel(achievement.title);
        QFont titleFont = titleLabel->font();
        titleFont.setBold(true);
        titleFont.setPointSize(16); // 更大字体
        titleLabel->setFont(titleFont);

        QLabel *detailLabel = new QLabel(
            achievement.unlocked
                ? QString("%1\n达成时间: %2").arg(achievement.description)
                    .arg(achievement.unlockDate.toString("yyyy-MM-dd"))
                : achievement.description
        );
        detailLabel->setWordWrap(true);

        // 仅为整体和图标添加边框，白底黑字
        itemWidget->setStyleSheet(
            "background:#fff;"
            "border: 2px solid #222;" // 整体黑色边框
            "border-radius: 18px;"
            "margin-bottom: 8px;"
        );
        iconLabel->setStyleSheet(
            "border: 2px solid #222;" // 图标黑色边框
            "border-radius: 12px;"
            "background:#fff;"
        );
        // 取消文字label的边框，仅设置颜色和字体
        titleLabel->setStyleSheet("color: #000; font-size: 16pt; padding-bottom: 4px;");
        detailLabel->setStyleSheet(
            achievement.unlocked
            ? "color: #000; font-size: 12pt;"
            : "color: #000; font-size: 12pt; font-style: italic;"
        );

        textLayout->addWidget(titleLabel);
        textLayout->addWidget(detailLabel);
        hLayout->addWidget(iconLabel, 0, Qt::AlignTop);
        hLayout->addLayout(textLayout);
        itemWidget->setLayout(hLayout);

        scrollLayout->addWidget(itemWidget);
    }

    scrollLayout->addStretch();
}
