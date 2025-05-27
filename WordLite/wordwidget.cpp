#include "wordwidget.h"
#include "ui_wordwidget.h"

WordWidget::WordWidget(QString word, QWidget *parent)
    : QWidget(parent)
    , word(word)
    , ui(new Ui::WordWidget)
{
    ui->setupUi(this);

    // 设置UI和连接信号槽
    connectSignals();
}

WordWidget::~WordWidget()
{
    delete ui;
}

void WordWidget::setupUI(QVector<Word> wordList)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    this->setLayout(layout);

    for (const Word& word : wordList)
    {
        // 单词卡片容器
        QGroupBox* wordBox = new QGroupBox(this);
        QVBoxLayout* wordLayout = new QVBoxLayout(wordBox);

        // 单词和发音+收藏按钮同行
        QWidget* topRowWidget = new QWidget(wordBox);
        QHBoxLayout* topRowLayout = new QHBoxLayout(topRowWidget);
        topRowLayout->setContentsMargins(0, 0, 0, 0);

        QLabel* wordLabel = new QLabel(word.g_word(), topRowWidget);
        QFont wordFont = wordLabel->font();
        wordFont.setPointSize(14);
        wordFont.setBold(true);
        wordLabel->setFont(wordFont);

        QLabel* pronLabel = new QLabel("[" + word.g_prounuciation() + "]", topRowWidget);
        pronLabel->setStyleSheet("color: #666;");

        QPushButton* favButton = new QPushButton("收藏", topRowWidget);
        favButton->setCheckable(true);
        favButton->setStyleSheet("QPushButton { border: 1px solid #f90; border-radius: 4px; background: #fffbe6; } QPushButton:checked { background: #ffe066; }");
        // 可以根据需要连接信号槽
        // connect(favButton, &QPushButton::clicked, this, [word](){
        // });

        topRowLayout->addWidget(wordLabel);
        topRowLayout->addWidget(pronLabel);
        topRowLayout->addStretch();
        topRowLayout->addWidget(favButton);

        // 释义
        QLabel* meaningLabel = new QLabel(word.g_meaning(), wordBox);
        meaningLabel->setWordWrap(true);

        // 例句
        QLabel* exampleLabel = new QLabel("例句: " + word.g_example(), wordBox);
        exampleLabel->setWordWrap(true);
        exampleLabel->setStyleSheet("color: #555; font-style: italic;");

        // 学习信息
        QString reviewInfo = QString("复习次数: %1 | 难度: %2 | 最后复习: %3")
                                 .arg(word.g_reviewCount())
                                 .arg(word.g_difficulty())
                                 .arg(word.g_lastReviewed().toString("yyyy-MM-dd hh:mm"));
        QLabel* infoLabel = new QLabel(reviewInfo, wordBox);
        infoLabel->setStyleSheet("color: #888; font-size: 10px;");

        wordLayout->addWidget(topRowWidget);
        wordLayout->addWidget(meaningLabel);
        if (!word.g_example().isEmpty()) {
            wordLayout->addWidget(exampleLabel);
        }
        wordLayout->addWidget(infoLabel);

        wordBox->setStyleSheet("QGroupBox { border: 1px solid #ddd; border-radius: 5px; margin-top: 5px; }");
        wordBox->setContentsMargins(5, 5, 5, 5);

        layout->addWidget(wordBox);
    }
    layout->addStretch();
}

void WordWidget::connectSignals(){

}
