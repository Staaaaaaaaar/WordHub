#include "wordwidget.h"
#include "ui_wordwidget.h"

WordWidget::WordWidget(QString word, WordDatabase* ptr, QWidget *parent)
    : QWidget(parent)
    , word(word)
    , DBptr(ptr)
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
    // 外层主布局
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    this->setLayout(mainLayout);

    // 滚动区域
    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);

    // 滚动内容容器
    QWidget* scrollContent = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(scrollContent);
    layout->setAlignment(Qt::AlignTop);

    // 获取所有分类
    QVector<Category> allCategories;
    if (DBptr) {
        // allCategories = DBptr->getAllCategories();
        // 调试用
        allCategories = { Category{0, "测试分类1", ""}, Category{1, "测试分类2", ""} };
    }

    // 分类颜色映射（可自定义更多颜色）
    QStringList colorList = {
        "#f44336", "#2196f3", "#4caf50", "#ff9800", "#9c27b0", "#00bcd4", "#e91e63", "#8bc34a", "#ffc107", "#607d8b"
    };

    for (const Word& word : wordList)
    {
        QGroupBox* wordBox = new QGroupBox(scrollContent);
        QVBoxLayout* wordLayout = new QVBoxLayout(wordBox);

        // 单词和音标+收藏按钮同行
        QWidget* topRowWidget = new QWidget(wordBox);
        QHBoxLayout* topRowLayout = new QHBoxLayout(topRowWidget);
        topRowLayout->setContentsMargins(0, 0, 0, 0);

        QLabel* wordLabel = new QLabel(word.g_word(), topRowWidget);
        QFont wordFont = wordLabel->font();
        wordFont.setPointSize(14);
        wordFont.setBold(true);
        wordLabel->setFont(wordFont);

        QStringList phoneticList;
        for (const Phonetic& ph : word.phonetics) {
            if (!ph.text.isEmpty())
                phoneticList << ph.text;
        }
        QLabel* pronLabel = new QLabel(phoneticList.isEmpty() ? "" : "[" + phoneticList.join(" / ") + "]", topRowWidget);
        pronLabel->setStyleSheet("color: #666;");

        // 收藏按钮（下拉选择分类收藏，美化样式）
        QPushButton* favButton = new QPushButton("收藏", topRowWidget);
        favButton->setCheckable(false);
        // favButton->setStyleSheet(
        //     "QPushButton {"
        //     "  border: 1px solid #bbb;"
        //     "  border-radius: 12px;"
        //     "  background:rgb(242, 173, 173);"
        //     "  color: rgb(0, 0, 0);"
        //     "  padding: 3px 14px;"
        //     "  font-size: 10pt;"
        //     "}"
        //     "QPushButton::menu-indicator { image: none; }"
        // );

        // 下拉菜单
        QMenu* favMenu = new QMenu(favButton);
        // favMenu->setStyleSheet(
        //     "QMenu {"
        //     "  background: #fff;"
        //     "  border: 1px solid #ccc;"
        //     "  border-radius: 6px;"
        //     "  padding: 4px;"
        //     "}"
        //     "QMenu::item {"
        //     "  padding: 5px 16px;"
        //     "  border-radius: 4px;"
        //     "  font-size: 10pt;"
        //     "}"
        //     "QMenu::item:selected {"
        //     "  background:rgb(230, 165, 165);"
        //     "  color: rgb(0, 0, 0);"
        //     "}"
        // );

        // 分类收藏项（多选）
        QList<QAction*> catActions;
        QVector<Category> wordCats;
        if (DBptr) {
            // 调试用
            wordCats = { Category{0, "测试分类1", ""}, Category{1, "测试分类2", ""} };
            // wordCats = DBptr->getCategoriesByName(word.g_word());
        }
        for (int i = 0; i < allCategories.size(); ++i) {
            const Category& cat = allCategories[i];
            QAction* act = new QAction(cat.name, favMenu);
            act->setCheckable(true);
            act->setData(cat.id);
            // 判断当前单词是否已在该分类，可根据DBptr->isWordInCategory(word.id, cat.id)实现
            // act->setChecked(DBptr && DBptr->isWordInCategory(word.id, cat.id));
            act->setChecked(false); // 如需联动数据库请替换此行
            favMenu->addAction(act);
            catActions.append(act);
        }

        favMenu->addSeparator();
        QAction* newCatAction = favMenu->addAction("新建分类");
        favButton->setMenu(favMenu);

        connect(newCatAction, &QAction::triggered, this, [this, word]() {
            bool ok = false;
            QString catName = QInputDialog::getText(this, "新建分类", "请输入分类名称：", QLineEdit::Normal, "", &ok);
            if (ok && !catName.trimmed().isEmpty() && DBptr) {
            //int newCatId = DBptr->addCategory(catName.trimmed());
            //if (newCatId >= 0) {
               // DBptr->assignWordToCategory(word.id, newCatId);
                // 刷新UI
               // this->setupUI(DBptr->getWordsByName(word.g_word()));
           // }
            }
        });



        connect(favMenu, &QMenu::triggered, this, [this, word, catActions](QAction* act) {
            if (!DBptr) return;
            bool ok = false;
            int catId = act->data().toInt(&ok);
            if (ok && catId >= 0) {
                if (act->isChecked()) {
                    DBptr->assignWordToCategory(word.id, catId);
                } else {
                    DBptr->removeWordFromCategory(word.id, catId);
                }
                // 更新页面布局
                this->setupUI(DBptr->getWordsByName(word.g_word()));
            }
        });

        topRowLayout->addWidget(wordLabel);
        topRowLayout->addWidget(pronLabel);
        topRowLayout->addStretch();
        topRowLayout->addWidget(favButton);

        wordLayout->addWidget(topRowWidget);

        // 分类标签

        // if (wordCats.isEmpty() && DBptr) {
        //     // 兼容：通过所有分类遍历判断
        //     QVector<Category> allCats = DBptr->getAllCategories();
        //     for (const Category& cat : allCats) {
        //         QVector<Word> ws = DBptr->getWordsByCategory(cat.id);
        //         for (const Word& w : ws) {
        //             if (w.id == word.id) {
        //                 wordCats.append(cat);
        //                 break;
        //             }
        //         }
        //     }
        // }
        
        if (!wordCats.isEmpty()) {
            QWidget* tagWidget = new QWidget(wordBox);
            QHBoxLayout* tagLayout = new QHBoxLayout(tagWidget);
            tagLayout->setContentsMargins(0, 0, 0, 0);
            int colorIdx = 0;
            for (const Category& cat : wordCats) {
                QLabel* tag = new QLabel(cat.name, tagWidget);
                QString color = colorList.at(colorIdx % colorList.size());
                tag->setStyleSheet(QString(
                    "background:%1;"
                    "color:#fff;"
                    "border-radius:5px;"
                    "padding:2px 12px;"
                    "margin-right:8px;"
                    "font-size:6pt;"
                    "font-weight:normal;"
                    "box-shadow: 0 1px 3px rgba(0,0,0,0.08);"
                    "border: 1px solid #eee;"
                ).arg(color));
                tagLayout->addWidget(tag);
                colorIdx++;
            }
            tagLayout->addStretch();
            wordLayout->addWidget(tagWidget);
        }

        // 学习信息
        QString reviewInfo = QString("复习次数: %1 | 难度: %2 | 最后复习: %3")
                                 .arg(word.reviewCount)
                                 .arg(word.difficulty)
                                 .arg(word.lastReviewed.toString("yyyy-MM-dd hh:mm"));
        QLabel* infoLabel = new QLabel(reviewInfo, wordBox);
        infoLabel->setStyleSheet("color: #888; font-size: 10px;");


        wordLayout->addWidget(infoLabel);

        // 释义部分
        for (auto it = word.meanings.constBegin(); it != word.meanings.constEnd(); ++it) {
            QString partOfSpeech = it.key();
            const QVector<Definition>& defs = it.value();

            QLabel* posLabel = new QLabel(partOfSpeech, wordBox);
            posLabel->setStyleSheet("font-weight:bold; color:#444; margin-top:6px;");
            wordLayout->addWidget(posLabel);

            QString lastDefinition;
            for (const Definition& def : defs) {
                if (def.definition == lastDefinition)
                    continue;
                lastDefinition = def.definition;

                QLabel* meaningLabel = new QLabel(def.definition, wordBox);
                meaningLabel->setWordWrap(true);
                meaningLabel->setStyleSheet("margin-left:10px; margin-bottom:2px;");
                wordLayout->addWidget(meaningLabel);

                QStringList exampleList;
                if (!def.example.isEmpty()) {
                    exampleList = def.example.split("\n", Qt::SkipEmptyParts);
                }
                int exampleCount = exampleList.size();
                int showCount = qMin(5, exampleCount);
                QVector<QLabel*> exampleLabels;
                for (int i = 0; i < showCount; ++i) {
                    QLabel* exampleLabel = new QLabel("例句: " + exampleList[i], wordBox);
                    exampleLabel->setWordWrap(true);
                    exampleLabel->setStyleSheet("color: #555; font-style: italic; margin-left:20px;");
                    wordLayout->addWidget(exampleLabel);
                    exampleLabels.append(exampleLabel);
                }
                if (exampleCount > 5) {
                    QPushButton* moreBtn = new QPushButton("更多", wordBox);
                    moreBtn->setStyleSheet("color:#0078d7; background:transparent; border:none; text-decoration:underline; margin-left:20px;");
                    wordLayout->addWidget(moreBtn);

                    QVector<QLabel*> moreExampleLabels;
                    for (int i = 5; i < exampleCount; ++i) {
                        QLabel* exampleLabel = new QLabel("例句: " + exampleList[i], wordBox);
                        exampleLabel->setWordWrap(true);
                        exampleLabel->setStyleSheet("color: #555; font-style: italic; margin-left:20px;");
                        exampleLabel->setVisible(false);
                        wordLayout->addWidget(exampleLabel);
                        moreExampleLabels.append(exampleLabel);
                    }
                    connect(moreBtn, &QPushButton::clicked, this, [moreExampleLabels, moreBtn]() {
                        for (QLabel* l : moreExampleLabels) l->setVisible(true);
                        moreBtn->setVisible(false);
                    });
                }
            }
        }

        wordBox->setStyleSheet("QGroupBox { border: 1px solid #ddd; border-radius: 5px; margin-top: 5px; }");
        wordBox->setContentsMargins(5, 5, 5, 5);

        layout->addWidget(wordBox);
    }
    layout->addStretch();

    scrollContent->setLayout(layout);
    scrollArea->setWidget(scrollContent);
    mainLayout->addWidget(scrollArea);
}

void WordWidget::connectSignals(){

}
