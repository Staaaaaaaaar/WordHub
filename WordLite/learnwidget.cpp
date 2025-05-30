#include "learnwidget.h"
#include "ui_learnwidget.h"
#include <random>


LearnWidget::LearnWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LearnWidget)
{
    ui->setupUi(this);

    DBptr = new WordDatabase();
    //初始化defaultDictNames
    defaultDictNames = DBptr->getlist();
    //设置UI和连接信号槽
    setupUI();
    connectSignals();

}

LearnWidget::~LearnWidget()
{
    delete ui;
}
void LearnWidget::setupUI()
{
    //设置初始界面
    ui->stackedWidget->setCurrentIndex(0);
    //设置添加词库按钮
    addDictButton = new DictButton("+");


    // 响应式布局：用QScrollArea+QWidget+QGridLayout
    QWidget* defaultContainer = new QWidget;
    QGridLayout* defaultGrid = new QGridLayout(defaultContainer);
    defaultGrid->setSpacing(10);
    defaultGrid->setContentsMargins(10, 10, 10, 10);

    int columns = 4; // 可根据窗口宽度动态调整
    for (int i = 0; i < defaultDictNames.size(); ++i) {
        DictButton* btn = new DictButton(defaultDictNames[i]);
        int row = i / columns;
        int col = i % columns;
        defaultGrid->addWidget(btn, row, col);
        // 可连接信号
        connect(btn, &QToolButton::clicked, this, &LearnWidget::on_dictButton_clicked);
    }
    // 添加“+”按钮
    int addRow = defaultDictNames.size() / columns;
    int addCol = defaultDictNames.size() % columns;
    defaultGrid->addWidget(addDictButton, addRow, addCol);
    connect(addDictButton, &QToolButton::clicked, this, &LearnWidget::on_addDictButton_clicked);

    defaultContainer->setLayout(defaultGrid);
    QScrollArea* defaultScroll = new QScrollArea;
    defaultScroll->setWidgetResizable(true);
    defaultScroll->setWidget(defaultContainer);
    // 为defaultBox新建布局
    QVBoxLayout* defaultBoxLayout = new QVBoxLayout();
    defaultBoxLayout->addWidget(defaultScroll);
    ui->defaultBox->setLayout(defaultBoxLayout);



    for (int i = 0; i < 4; ++i) {
        QPushButton* btn = nullptr;
        switch (i) {
        case 0: btn = ui->pushButton_0; break;
        case 1: btn = ui->pushButton_1; break;
        case 2: btn = ui->pushButton_2; break;
        case 3: btn = ui->pushButton_3; break;
        }
        btn->setStyleSheet("QPushButton {"
                          "    text-align: left;"
                          "    padding: 5px;"
                          "    border: 1px solid gray;"
                          "    border-radius: 3px;"
                          "    word-wrap: break-word;"  // 这里控制文本的换行
                          "}");
    }
}


void LearnWidget::connectSignals()
{
    //点击词库跳转到词库信息界面
    for (DictButton* dictButton : std::as_const(defaultButtons)) {
        connect(dictButton, &QToolButton::clicked, this, &LearnWidget::on_dictButton_clicked);
    }
    for (DictButton* dictButton : std::as_const(customizeButtons)) {
        connect(dictButton, &QToolButton::clicked, this, &LearnWidget::on_dictButton_clicked);
    }
    //点击“+”添加自定义词库
    connect(addDictButton, &QToolButton::clicked, this, &LearnWidget::on_addDictButton_clicked);
    //跳转到words界面
    connect(ui->learnButton, &QToolButton::clicked, this, &LearnWidget::on_learnButton_clicked);
    connect(ui->reviewButton, &QToolButton::clicked, this, &LearnWidget::on_reviewButton_clicked);
    //跳转到测试界面
    connect(ui->testButton, &QToolButton::clicked, this, &LearnWidget::on_testButton_clicked);
    //返回
    connect(ui->backButton, &QToolButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(0);});
    connect(ui->backButton_2, &QToolButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(1);});
    connect(ui->backButton_3, &QToolButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(2);
        initWordsWidget();
    });


}

void LearnWidget::addButtonsToGrid(QGridLayout *grid, const QList<DictButton*> &buttons, int columns)
{
    for (int i = 0; i < buttons.size(); ++i) {
        int row = i / columns;
        int col = i % columns;
        grid->addWidget(buttons.at(i), row, col);
    }
}
void LearnWidget::initDictWidget()
{
    QString name = qobject_cast<DictButton*>(sender())->text();
    ui->dictName->setText(name);
}
void LearnWidget::initWordsWidget()
{
    ui->wordsListWidget->clear();
    ui->wordsListWidget->setColumnCount(2); // 强制只有两列
    ui->wordsListWidget->setRowCount(wordsList.size());
    QStringList headers;
    headers << "单词" << "释义";
    ui->wordsListWidget->setHorizontalHeaderLabels(headers);

    ui->wordsListWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->wordsListWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->wordsListWidget->verticalHeader()->setVisible(false);
    ui->wordsListWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->wordsListWidget->setSelectionMode(QAbstractItemView::NoSelection);

    for (int i = 0; i < wordsList.size(); ++i) {
        const Word& word = wordsList[i];
        // 单词
        QTableWidgetItem* wordItem = new QTableWidgetItem(word.word);
        wordItem->setFont(QFont(wordItem->font().family(), wordItem->font().pointSize(), QFont::Bold));
        wordItem->setTextAlignment(Qt::AlignCenter);
        ui->wordsListWidget->setItem(i, 0, wordItem);

        // 释义（多词性分段，分行显示）
        QStringList meaningLines;
        for (auto it = word.meanings.constBegin(); it != word.meanings.constEnd(); ++it) {
            QString pos = it.key();
            QStringList defs;
            QString lastDef;
            for (const Definition& def : it.value()) {
                if (def.definition != lastDef) {
                    defs << def.definition;
                    lastDef = def.definition;
                }
            }
            meaningLines << QString("%1\n%2").arg(pos, defs.join("; "));
        }
        QTableWidgetItem* defItem = new QTableWidgetItem(meaningLines.join("\n"));
        defItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        ui->wordsListWidget->setItem(i, 1, defItem);
    }
    // 自动调整列宽和行高，使内容自适应
    ui->wordsListWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->wordsListWidget->horizontalHeader()->setStretchLastSection(true);
    ui->wordsListWidget->resizeRowsToContents();
}

void LearnWidget::initCheckout()
{
    // 清空并设置表头
    ui->wordsListWidget->clear();
    ui->wordsListWidget->setColumnCount(2);
    ui->wordsListWidget->setRowCount(wordsList.size());
    QStringList headers;
    headers << "单词" << "释义";
    ui->wordsListWidget->setHorizontalHeaderLabels(headers);
    ui->wordsListWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->wordsListWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->wordsListWidget->verticalHeader()->setVisible(false);
    ui->wordsListWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->wordsListWidget->setSelectionMode(QAbstractItemView::NoSelection);

    for (int i = 0; i < wordsList.size(); ++i) {
        const Word& word = wordsList[i];
        // 单词
        QTableWidgetItem* wordItem = new QTableWidgetItem(word.word);
        wordItem->setFont(QFont(wordItem->font().family(), wordItem->font().pointSize(), QFont::Bold));
        wordItem->setTextAlignment(Qt::AlignCenter);

        // 释义
        QStringList meaningLines;
        for (auto it = word.meanings.constBegin(); it != word.meanings.constEnd(); ++it) {
            QString pos = it.key();
            QStringList defs;
            QString lastDef;
            for (const Definition& def : it.value()) {
                if (def.definition != lastDef) {
                    defs << def.definition;
                    lastDef = def.definition;
                }
            }
            meaningLines << QString("%1\n%2").arg(pos, defs.join("; "));
        }
        QTableWidgetItem* defItem = new QTableWidgetItem(meaningLines.join("\n"));
        defItem->setTextAlignment(Qt::AlignCenter);

        // 根据正误设置样式
        if (i < testResults.size() && testResults[i]) {
            wordItem->setBackground(QColor(200, 255, 200)); // 正确绿色
            defItem->setBackground(QColor(200, 255, 200));
        } else {
            wordItem->setBackground(QColor(255, 200, 200)); // 错误红色
            defItem->setBackground(QColor(255, 200, 200));
        }

        ui->wordsListWidget->setItem(i, 0, wordItem);
        ui->wordsListWidget->setItem(i, 1, defItem);
    }
    ui->wordsListWidget->resizeRowsToContents();

    // 设置按钮文本
    ui->testButton->setText("重新测试");
}

void LearnWidget::initTestWidget()
{
    //初始化测试状态
    currentTestIndex = 0;
    testResults.clear();
    testResults.resize(wordsList.size());
    std::fill(testResults.begin(), testResults.end(), false);
    currentSelected = -1;

    // 确保 optionButtons 有 4 个元素且全部已初始化
    optionButtons.resize(4);
    for (int i = 0; i < 4; ++i)
    {
        QPushButton* btn = nullptr;
        switch (i) {
        case 0: btn = ui->pushButton_0; break;
        case 1: btn = ui->pushButton_1; break;
        case 2: btn = ui->pushButton_2; break;
        case 3: btn = ui->pushButton_3; break;
        }
        optionButtons[i] = btn;
        // 防止重复连接
        btn->disconnect();
        connect(btn, &QPushButton::clicked, this, [=]() {
            currentSelected = i;
            for (int j = 0; j < 4; ++j) {
                if (j==i){
                    optionButtons[j]->setStyleSheet("QPushButton {"
                          "    text-align: left;"
                          "    padding: 5px;"
                          "    border: 1px solid gray;"
                          "    border-radius: 3px;"
                          "    word-wrap: break-word;"  // 这里控制文本的换行
                          "    background-color: lightblue;"
                          "}");
                }
                else{
                    optionButtons[j]->setStyleSheet("QPushButton {"
                          "    text-align: left;"
                          "    padding: 5px;"
                          "    border: 1px solid gray;"
                          "    border-radius: 3px;"
                          "    word-wrap: break-word;"  // 这里控制文本的换行
                          "}");
                }
            }
        });
    }

    // 连接确定按钮
    disconnect(ui->testConfirmButton, nullptr, nullptr, nullptr);
    connect(ui->testConfirmButton, &QPushButton::clicked, this, [=]() {
        if (currentSelected == -1) return; // 未选择
        int wordId = wordsList[currentTestIndex].id;
        bool correct = (optionButtons[currentSelected]->text() == correctAnswer);
        testResults[currentTestIndex] = correct;
        DBptr->updateWordLearningInfo(wordId, correct, -int(correct));

        // 显示正误反馈
        for (int i = 0; i < 4; ++i) {
            if (optionButtons[i]->text() == correctAnswer) {
                optionButtons[i]->setStyleSheet(
                    "QPushButton {"
                    "    text-align: left;"
                    "    padding: 5px;"
                    "    border: 1px solid gray;"
                    "    border-radius: 3px;"
                    "    word-wrap: break-word;"  // 这里控制文本的换行
                    "    background-color: lightgreen;"
                    "}"
                );
            } else if (i == currentSelected) {
                optionButtons[i]->setStyleSheet("QPushButton {"
                    "    text-align: left;"
                    "    padding: 5px;"
                    "    border: 1px solid gray;"
                    "    border-radius: 3px;"
                    "    word-wrap: break-word;"  // 这里控制文本的换行
                    "    background-color: pink;"
                    "}"
                );
            } else {
                optionButtons[i]->setStyleSheet("QPushButton {"
                    "    text-align: left;"
                    "    padding: 5px;"
                    "    border: 1px solid gray;"
                    "    border-radius: 3px;"
                    "    word-wrap: break-word;"  // 这里控制文本的换行
                    "}"
                );
            }
        }

        QTimer::singleShot(700, this, [=]() {
            currentTestIndex++;
            if (currentTestIndex < wordsList.size()) {
                showTestForWord(currentTestIndex);
            } else {
                ui->stackedWidget->setCurrentIndex(2);
                initCheckout();
            }
        });
    });
}

void LearnWidget::showTestForWord(int idx)
{
    if (idx < 0 || idx >= wordsList.size()) return;
    currentSelected = -1;
    ui->testWordLabel->setText(wordsList[idx].word);

    // 获取四个释义选项
    options = DBptr->FourmeaningtoChoice(wordsList[idx].id);
    if (options.size() < 4) {
        // 补齐到4个选项，防止越界
        while (options.size() < 4) options << "";
    }
    correctAnswer = options[0];
    //测试样例
    // options.clear();
    // options << "a fruit" << "a tech company" << "to move swiftly on foot" << "an act or spell of running";
    // correctAnswer = options[0];

    // 随机打乱选项顺序
    QVector<QString> shuffledOptions = options;
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(shuffledOptions.begin(), shuffledOptions.end(), g);

    // 设置按钮文本和样式
    for (int i = 0; i < 4; ++i) {
        optionButtons[i]->setText(shuffledOptions[i]);
        optionButtons[i]->setChecked(false);
        optionButtons[i]->setStyleSheet(
            "QPushButton {"
            "    text-align: left;"
            "    padding: 5px;"
            "    border: 1px solid gray;"
            "    border-radius: 3px;"
            "    word-wrap: break-word;"  // 这里控制文本的换行
            "}"
        );
    }
}

void LearnWidget::on_addDictButton_clicked()
{
    //浏览文件
}
void LearnWidget::on_dictButton_clicked()
{
    //跳转到词库信息界面
    ui->stackedWidget->setCurrentIndex(1);
    QString name = qobject_cast<DictButton*>(sender())->text();
    DBptr->initDatabase(name);
    //初始化界面
    initDictWidget();
}
void LearnWidget::on_reviewButton_clicked()
{
    //跳转到words界面
    ui->stackedWidget->setCurrentIndex(2);
    ui->testButton->setText("开始测试");
    wordsList.clear();
    wordsList = DBptr->getWordsToReview(20);

    disconnect(ui->refreshButton, nullptr, nullptr, nullptr);
    // 重新连接刷新按钮
    connect(ui->refreshButton, &QToolButton::clicked, this, &LearnWidget::on_refreshButton_clicked_2);

    // 初始化单词列表界面
    initWordsWidget();
}


void LearnWidget::on_learnButton_clicked()
{
    //跳转到words界面
    ui->stackedWidget->setCurrentIndex(2);
    ui->testButton->setText("开始测试");
    wordsList.clear();
    wordsList = DBptr->getRandomWords(20);

    disconnect(ui->refreshButton, nullptr, nullptr, nullptr);
    connect(ui->refreshButton, &QToolButton::clicked, this, &LearnWidget::on_refreshButton_clicked_1);

    // 初始化单词列表界面
    initWordsWidget();
}
void LearnWidget::on_testButton_clicked()
{
    //跳转到测试界面
    ui->stackedWidget->setCurrentIndex(3);
    //初始化准备
    initTestWidget();
    //显示第一个单词
    showTestForWord(0);
}

void LearnWidget::on_refreshButton_clicked_1()
{
    ui->testButton->setText("开始测试");
    //重新获取wordsList
    wordsList.clear();
    wordsList = DBptr->getRandomWords(20);

    initWordsWidget();
}
void LearnWidget::on_refreshButton_clicked_2()
{
    ui->testButton->setText("开始测试");
    //重新获取wordsList
    wordsList.clear();
    wordsList = DBptr->getWordsToReview(20);

    initWordsWidget();
}




DictButton::DictButton(QString text) //传入字典指针
{
    this->setText(text);
    this->setFixedSize(120, 80); // 设置固定大小
}

DictButton::~DictButton()
{

}



