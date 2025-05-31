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
    testAchievements = {
        {1, "初次相遇", "成功登录一次应用", false, QDateTime(), ":/icons/achievement_login.png"},
        {2, "启程之星", "进行首次学习", false, QDateTime(), ":/icons/achievement1.png"},
        {3, "探索之门", "首次查询单词释义", false, QDateTime(), ":/icons/achievement_query.png"},
        {4, "游戏新手", "首次参与单词游戏", false, QDateTime(), ":/icons/achievement_game.png"},
        {5, "七日之约", "连续学习7天", false, QDateTime(), ":/icons/locked.png"},
        {6, "月度坚持", "连续学习30天", false, QDateTime(), ":/icons/locked.png"},
        {7, "百日不辍", "连续学习100天", false, QDateTime(), ":/icons/locked.png"},
        {8, "百日筑基", "累计学习100天", false, QDateTime(), ":/icons/locked.png"},
        {9, "学海无涯", "累计学习365天", false, QDateTime(), ":/icons/locked.png"},
        {10, "词汇大师", "掌握500个单词", false, QDateTime(), ":/icons/locked.png"},
        {11, "词海遨游", "累计学习1000个单词", false, QDateTime(), ":/icons/locked.png"},
        {12, "词霸精英", "掌握2000个单词", false, QDateTime(), ":/icons/locked.png"},
        {13, "荣耀全开", "解锁所有成就", false, QDateTime(), ":/icons/locked.png"},
        // 隐藏成就
        {14, "？？？", "？？？", false, QDateTime(), ":/icons/hidden.png"},
        {15, "？？？", "？？？", false, QDateTime(), ":/icons/hidden.png"}
    };
    refreshUI(); // 构造时刷新成就显示
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


QVector<Achievement> AchievementWidget::getAchievementsFromSource()
{
    return testAchievements;
}

void AchievementWidget::refreshAchievements(int idx)
{
    if (idx >= 0 && idx < testAchievements.size()) {
        testAchievements[idx].unlocked = true;
        testAchievements[idx].unlockDate = QDateTime::currentDateTime();
    }
    refreshUI();
}
void AchievementWidget::refreshUI()
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
    std::sort(achievements.begin(), achievements.end(), [](const Achievement &a, const Achievement &b) {
        if (a.unlocked != b.unlocked)
            return a.unlocked > b.unlocked; // 已达成的优先
        return a.id < b.id; // 其余按id升序
    });

    for (const Achievement &achievement : achievements) {
        QWidget *itemWidget = new QWidget();
        QHBoxLayout *hLayout = new QHBoxLayout(itemWidget);
        hLayout->setContentsMargins(28, 18, 28, 18); // 更大内边距
        hLayout->setSpacing(28); // 更大间距

        // 图标
        // QLabel *iconLabel = new QLabel();
        // QPixmap pixmap(achievement.iconPath);
        // if (!achievement.unlocked)
        //     pixmap = pixmap.scaled(56, 56, Qt::KeepAspectRatio, Qt::SmoothTransformation); // 更大图标
        // iconLabel->setPixmap(pixmap);
        // iconLabel->setFixedSize(68, 68); // 更大图标区域

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

        // 简约美化样式
        itemWidget->setStyleSheet(
            "background:rgb(142, 142, 142);"
            "border-radius: 14px;"
            // "border: 1px solidrgb(207, 207, 207);"
            "box-shadow: 0 2px 8px rgba(0,0,0,0.03);"
        );
        titleLabel->setStyleSheet(
            "color: rgb(53, 53, 53);"
            "font-weight: 600;"
            "letter-spacing: 0.5px;"
        );
        detailLabel->setStyleSheet(
            "color: rgb(255, 255, 255);"
            "font-size: 13px;"
        );

        textLayout->addWidget(titleLabel);
        textLayout->addWidget(detailLabel);
        // hLayout->addWidget(iconLabel, 0, Qt::AlignTop);
        hLayout->addLayout(textLayout);
        itemWidget->setLayout(hLayout);

        scrollLayout->addWidget(itemWidget);
    }

    scrollLayout->addStretch();
}
