#include "querywidget.h"
#include "ui_querywidget.h"

QueryWidget::QueryWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QueryWidget)
{
    ui->setupUi(this);


    //初始化成员变量
    wordDataBase = new WordDatabase();
    wordDBList = WordDatabase::getlist();
    dictionaryAPI = new DictionaryAPI();

    // 设置UI和连接信号槽
    setupUI();
    connectSignals();
}

QueryWidget::~QueryWidget()
{
    ui->tabWidget->clear();
    delete ui;
}

void QueryWidget::setupUI()
{
    // 设置TabBar的样式
    // ui->tabWidget->setStyleSheet(
    //     // 主体蓝紫渐变风格，圆角，阴影，hover高亮
    //     "QTabBar::tab {"
    //     "  color: #fff;"
    //     "  background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #5c8dff, stop:1 #7c5cff);"
    //     "  border: 1px solid #7c9cff;"
    //     "  min-width: 40ex;"
    //     "  min-height: 6ex;"
    //     "  padding: 7px 22px;"
    //     "  border-top-left-radius: 12px;"
    //     "  border-top-right-radius: 12px;"
    //     "  margin-right: 4px;"
    //     "  font-size: 12pt;"
    //     "  font-weight: bold;"
    //     "  box-shadow: 0 2px 8px rgba(92,141,255,0.10);"
    //     "  transition: background 0.2s;"
    //     "}"
    //     "QTabBar::tab:selected {"
    //     "  background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #505cff, stop:1 #9c27b0);"
    //     "  color: #fff;"
    //     "  margin-top: 1ex;"
    //     "  border-bottom: 2px solid #fff;"
    //     "  box-shadow: 0 4px 16px rgba(124,92,255,0.13);"
    //     "}"
    //     "QTabBar::tab:hover {"
    //     "  background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #6ca0ff, stop:1 #a27cff);"
    //     "  color: #fff;"
    //     "}"
    //     "QTabBar::close-button {"
    //     "  image: url(:/image/close.png);"
    //     "  subcontrol-position: right;"
    //     "  margin-left: 10px;"
    //     "  background: transparent;"
    //     "  border-radius: 8px;"
    //     "  width: 18px;"
    //     "  height: 18px;"
    //     "}"
    //     "QTabBar::close-button:hover {"
    //     "  background: #ff4d4f;"
    //     "  border: 1px solid #fff;"
    //     "}"
    //     "QTabWidget::pane {"
    //     "  border-top: 2px solid #7c9cff;"
    //     "  border-radius: 10px;"
    //     "  top: -1px;"
    //     "  background: #f8faff;"
    //     "}"
    // );


    //设置comboBox
    ui->comboBox->clear();
    for (const QString &DBname: std::as_const(wordDBList))
    {
        ui->comboBox->addItem(DBname);
    }
    wordDataBase->closeCurrentDatabase(); // 关闭当前数据库连接
    //初始化连接
    if (!wordDBList.isEmpty()) wordDataBase->initDatabase(wordDBList.first());

}

void QueryWidget::connectSignals()
{
    connect(ui->searchEdit, &QLineEdit::returnPressed, this, &QueryWidget::on_searchEdit_returnPressed);
    connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, &QueryWidget::on_tabWidget_tabCloseRequested);
    connect(ui->comboBox, &QComboBox::currentTextChanged, this, &QueryWidget::on_comboBox_currentTextChanged);
    connect(ui->useAPICheckBox, &QCheckBox::toggled, this, [this](bool checked){
        useAPI = checked;
    });
}


void QueryWidget::on_searchEdit_returnPressed()
{
    QString cur_word = ui->searchEdit->text().trimmed();

    // 判断是否已有wordWidget
    for (int index = 0; index < ui->tabWidget->count(); index++)
    {
        if (ui->tabWidget->tabBar()->tabText(index) == cur_word)
        {
            ui->tabWidget->setCurrentIndex(index);
            // emit sendMes(cur_word + "查询完成", 500);
            ui->searchEdit->clear();
            return;
        }
    }

    QVector<Word> wordList;

    if (useAPI && dictionaryAPI)
    {

        Word apiWord = dictionaryAPI->getWordInfo(cur_word);
        if (!apiWord.g_word().isEmpty())
        {
            wordList.append(apiWord);
        }
        else
        {
            // emit sendMes("API未找到相关单词", 3000);
            return;
        }
        // emit sendMes("API查询成功", 500);
    }
    else
    {
        wordList = wordDataBase->getWordsByName(cur_word);
        if (wordList.isEmpty())
        {
            return;
        }
        // emit sendMes("查询成功", 500);
    }

    wordWidget = new WordWidget(cur_word, wordDataBase, useAPI, this);
    wordWidget->setupUI(wordList);
    ui->tabWidget->addTab(wordWidget, cur_word);
    ui->tabWidget->setCurrentWidget(wordWidget);

    // emit sendMes(cur_word + "查询完成", 3000);
    ui->searchEdit->clear();

    // 成就部分
    emit sendId(3);

}


void QueryWidget::on_tabWidget_tabCloseRequested(int index)
{
    QWidget* widget = ui->tabWidget->widget(index);
    ui->tabWidget->removeTab(index);
    if (widget) {
        widget->deleteLater();
    }
}


void QueryWidget::on_comboBox_currentTextChanged(const QString &DBname)
{
    emit sendMes("正在连接数据库 "+DBname);
    wordDataBase->closeCurrentDatabase(); // 关闭当前数据库连接
    if (wordDataBase->initDatabase(DBname))
    {
        emit sendMes("成功连接数据库 "+DBname, 1000);
        //清空tab
        ui->tabWidget->clear();
    }
    else emit sendMes("连接失败", 1000);
}

void QueryWidget::sendMess(QString message, int timeout)
{
    emit this->sendMes(message, timeout);
}
void QueryWidget::clearMess()
{
    emit this->clearMes();
}



// WordWidget


WordWidget::WordWidget(QString word, WordDatabase* ptr, bool& useapi, QWidget *parent)
    : QWidget(parent)
    , word(word)
    , useAPI(useapi)
    , DBptr(ptr)
{
    // 设置UI和连接信号槽
    connectSignals();
}

WordWidget::~WordWidget()
{
}

void WordWidget::setupUI(QVector<Word> wordList)
{
    // 清空所有子控件（包括QScrollArea等）
    QLayout* oldLayout = this->layout();
    if (oldLayout) {
        QLayoutItem* item;
        while ((item = oldLayout->takeAt(0)) != nullptr) {
            if (QWidget* w = item->widget()) {
                w->deleteLater();
            }
            delete item;
        }
        delete oldLayout;
    }
    // 彻底删除所有子控件
    QList<QWidget*> children = this->findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly);
    for (int i = 0; i < children.size(); ++i) {
        children.at(i)->deleteLater();
    }

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
        allCategories = DBptr->getAllCategories();
        // 调试用
        // allCategories = { Category{0, "测试分类1", ""}, Category{1, "测试分类2", ""} };
    }

    // 分类颜色映射（可自定义更多颜色）
    QStringList colorList = {
        " #e57373", // 柔和红
        " #64b5f6", // 柔和蓝
        " #81c784", // 柔和绿
        " #ffb74d", // 柔和橙
        " #ba68c8", // 柔和紫
        " #4dd0e1", // 柔和青
        " #f06292", // 柔和粉
        " #aed581", // 柔和浅绿
        " #ffd54f", // 柔和黄
        " #90a4ae"  // 柔和灰蓝
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

        // 仅当不是API模式时显示收藏按钮
        QPushButton* favButton = nullptr;
        QMenu* favMenu = nullptr;
        if (!useAPI) {
            favButton = new QPushButton("收藏", topRowWidget);
            favButton->setCheckable(false);
            favMenu = new QMenu(favButton);

            // 分类收藏项（多选）
            QList<QAction*> catActions;
            QVector<Category> wordCats;
            if (DBptr) {
                // 调试用
                // wordCats = { Category{0, "测试分类1", ""}, Category{1, "测试分类2", ""} };
                wordCats = DBptr->getCategoriesByName(word.g_word());
            }
            for (int i = 0; i < allCategories.size(); ++i) {
                const Category& cat = allCategories[i];
                QWidget* actionWidget = new QWidget(favMenu);
                QHBoxLayout* actionLayout = new QHBoxLayout(actionWidget);
                actionLayout->setContentsMargins(0, 0, 0, 0);
                actionLayout->setSpacing(6);

                // 分类多选项
                QAction* act = new QAction(cat.name, favMenu);
                act->setCheckable(true);
                act->setData(cat.id);
                if (DBptr)
                    act->setChecked(DBptr->ifWordinCategory(word.g_id(), cat.id));
                catActions.append(act);

                // 用QToolButton做删除按钮
                QToolButton* delBtn = new QToolButton(actionWidget);
                delBtn->setText("✕");
                delBtn->setToolTip("删除该分类");
                delBtn->setStyleSheet("QToolButton { color: #f44336; background: transparent; border: none; font-weight: bold; }"
                          "QToolButton:hover { color: #fff; background: #f44336; border-radius: 6px; }");
                delBtn->setCursor(Qt::PointingHandCursor);

                // 关联删除分类
                connect(delBtn, &QToolButton::clicked, this, [this, cat, word]() {
                if (!DBptr) return;
                if (QMessageBox::question(this, "删除分类", "确定要删除分类 \"" + cat.name + "\" 吗？") == QMessageBox::Yes) {
                    if (DBptr->deleteCategory(cat.id)) {
                    emit sendMes("分类已删除: " + cat.name, 3000);
                    this->setupUI(DBptr->getWordsByName(word.g_word()));
                    } else {
                    emit sendMes("删除分类失败", 3000);
                    }
                }
                });

                // 用QWidgetAction将QAction和删除按钮组合
                QWidgetAction* widgetAction = new QWidgetAction(favMenu);
                // 分类复选框
                QCheckBox* checkBox = new QCheckBox(cat.name, actionWidget);
                checkBox->setChecked(act->isChecked());
                actionLayout->addWidget(checkBox);
                actionLayout->addWidget(delBtn);

                widgetAction->setDefaultWidget(actionWidget);
                favMenu->addAction(widgetAction);

                // 复选框和QAction同步
                connect(checkBox, &QCheckBox::toggled, this, [=]() {
                act->setChecked(checkBox->isChecked());
                });
                connect(act, &QAction::toggled, this, [=]() {
                checkBox->setChecked(act->isChecked());
                });

                // 收藏/取消收藏逻辑
                connect(checkBox, &QCheckBox::toggled, this, [this, checkBox, word, cat]() {
                if (!DBptr) return;
                if (checkBox->isChecked()) {
                    DBptr->assignWordToCategory(word.id, cat.id);
                    emit sendMes("收藏成功", 3000);
                } else {
                    DBptr->removeWordFromCategory(word.id, cat.id);
                    emit sendMes("取消收藏成功", 3000);
                }
                this->setupUI(DBptr->getWordsByName(word.g_word()));
                });
            }

            favMenu->addSeparator();
            QAction* newCatAction = favMenu->addAction("新建分类");
            favButton->setMenu(favMenu);
            // 隐藏下拉箭头
            favButton->setStyleSheet("QPushButton::menu-indicator { image: none; width: 0px; } QPushButton { min-width: 70px; }");

            connect(newCatAction, &QAction::triggered, this, [this, word]() {
                bool ok = false;
                QString catName = QInputDialog::getText(this, "新建分类", "请输入分类名称：", QLineEdit::Normal, "", &ok);
                if (!ok || catName.trimmed().isEmpty() || !DBptr) return;

                QString catDesc = QInputDialog::getText(this, "新建分类", "请输入分类描述（可选）：", QLineEdit::Normal, "", &ok);
                // catDesc 可为空

                Category newCat;
                newCat.name = catName.trimmed();
                newCat.description = catDesc.trimmed();

                bool okk = DBptr->addCategory(newCat);
                if (okk) {
                    emit sendMes("新分类已创建: " + newCat.name, 3000);
                    // 刷新UI
                    this->setupUI(DBptr->getWordsByName(word.g_word()));

                }
                else {
                    emit sendMes("创建分类失败", 3000);
                }
            });
        }


        topRowLayout->addWidget(wordLabel);
        topRowLayout->addWidget(pronLabel);
        topRowLayout->addStretch();
        if (!useAPI && favButton) {
            topRowLayout->addWidget(favButton);
        }

        wordLayout->addWidget(topRowWidget);

        // 仅当不是API模式时显示分类标签和学习信息
        if (!useAPI) {
            // 分类标签
            QVector<Category> wordCats;
            if (DBptr) {
                wordCats = DBptr->getCategoriesByName(word.g_word());
            }
            if (wordCats.isEmpty() && DBptr) {
                QVector<Category> allCats = DBptr->getAllCategories();
                for (int i = 0; i < allCats.size(); ++i) {
                    const Category& cat = allCats.at(i);
                    QVector<Word> ws = DBptr->getWordsByCategory(cat.id);
                    for (int j = 0; j < ws.size(); ++j) {
                        const Word& w = ws.at(j);
                        if (w.id == word.id) {
                            wordCats.append(cat);
                            break;
                        }
                    }
                }
            }
            if (!wordCats.isEmpty()) {
                QWidget* tagWidget = new QWidget(wordBox);
                QHBoxLayout* tagLayout = new QHBoxLayout(tagWidget);
                tagLayout->setContentsMargins(0, 0, 0, 0);
                for (int i = 0; i < wordCats.size(); ++i) {
                    const Category& cat = wordCats.at(i);
                    QLabel* tag = new QLabel(cat.name, tagWidget);
                    int colorIdx = cat.id % colorList.size();
                    QString color = colorList.at(colorIdx);
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
        }

        // 释义部分（所有模式都显示）
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

void WordWidget::connectSignals()
{

}
