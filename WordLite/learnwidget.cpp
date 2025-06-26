#include "learnwidget.h"
#include "ui_learnwidget.h"

// 全局样式表定义（用于QLabel模拟按钮）
static const char* kLabelNormalStyle =
    "QLabel {"
    "    padding: 5px;"
    "    border: 1px solid gray;"
    "    border-radius: 3px;"
    // "    background: white;"
    // "    color: black;"
    // "    font-size: 15px;"
    "}";

static const char* kLabelSelectedStyle =
    "QLabel {"
    "    padding: 5px;"
    "    border: 1px solid gray;"
    "    border-radius: 3px;"
    "    background: lightblue;"
    "    color: black;"
    // "    font-size: 15px;"
    "}";

static const char* kLabelCorrectStyle =
    "QLabel {"
    "    padding: 5px;"
    "    border: 1px solid gray;"
    "    border-radius: 3px;"
    "    background: lightgreen;"
    "    color: black;"
    // "    font-size: 15px;"
    "}";

static const char* kLabelWrongStyle =
    "QLabel {"
    "    padding: 5px;"
    "    border: 1px solid gray;"
    "    border-radius: 3px;"
    "    background: pink;"
    "    color: black;"
    // "    font-size: 15px;"
    "}";


LearnWidget::LearnWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LearnWidget)
{
    ui->setupUi(this);

    DBptr = new WordDatabase();
    //初始化defaultDictNames
    defaultDictNames = DBptr->getlist();
    // 只创建一次addDictButton
    addDictButton = new DictButton("+");
    //设置UI和连接信号槽
    setupUI();
    connectSignals();

    // 隐藏测试界面的pushButton，避免影响窗口缩放
    // tmp();
}

LearnWidget::~LearnWidget()
{
    delete ui;
}
// void LearnWidget::tmp()
// {
//     // 隐藏测试界面的pushButton，避免影响窗口缩放
//     for (int i = 0; i < 4; ++i) {
//         QPushButton* btn = nullptr;
//         switch (i) {
//         case 0: btn = ui->pushButton_0; break;
//         case 1: btn = ui->pushButton_1; break;
//         case 2: btn = ui->pushButton_2; break;
//         case 3: btn = ui->pushButton_3; break;
//         }
//         btn->hide(); // 用hide替换setVisible(false)
//         btn->setMinimumSize(0, 0);
//         btn->setMaximumSize(0, 0); // 强制最大最小都为0
//         btn->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
//     }
// }

void LearnWidget::setupUI()
{
    //设置初始界面
    ui->stackedWidget->setCurrentIndex(0);
    //设置添加词库按钮
    // addDictButton = new DictButton("+"); // 删除此行


    // 先清空defaultBox原有布局和控件
    QLayout* oldLayout = ui->defaultBox->layout();
    if (oldLayout) {
        QLayoutItem* item;
        while ((item = oldLayout->takeAt(0)) != nullptr) {
            if (QWidget* w = item->widget()) w->deleteLater();
            delete item;
        }
        delete oldLayout;
    }

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
    // 不再重复connect/disconnect addDictButton
    // ...existing code...

    defaultContainer->setLayout(defaultGrid);
    QScrollArea* defaultScroll = new QScrollArea;
    defaultScroll->setWidgetResizable(true);
    defaultScroll->setWidget(defaultContainer);
    // 为defaultBox新建布局
    QVBoxLayout* defaultBoxLayout = new QVBoxLayout();
    defaultBoxLayout->addWidget(defaultScroll);
    ui->defaultBox->setLayout(defaultBoxLayout);


    
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
        ui->stackedWidget->setCurrentIndex(0);
        // tmp();
    });
    connect(ui->backButton_2, &QToolButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(1);
        initDictWidget();
        // tmp();
    });
    connect(ui->backButton_3, &QToolButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(2);
        initWordsWidget();
        // tmp();
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
    // tmp();
    

    // 词库名
    ui->dictName->setText(dictName);

    // 清空showWidget布局
    QLayout* oldLayout = ui->showWidget->layout();
    if (oldLayout) {
        QLayoutItem* item;
        while ((item = oldLayout->takeAt(0)) != nullptr) {
            if (QWidget* w = item->widget()) w->deleteLater();
            delete item;
        }
        delete oldLayout;
    }

    // 简约化样式
    QString chartStyle = "QChartView { background: transparent; border: none; }";

    // --- 柱状图（学习数） ---
    QVector<int> dailyCounts = DBptr->getDailyLearningCountInDays(14);
    QBarSet* set = new QBarSet("学习数");
    for (int v : dailyCounts) *set << v;
    set->setLabelColor(Qt::black);
    set->setColor(QColor("#f5f5f5"));
    set->setBorderColor(QColor("#cccccc"));

    QBarSeries* barSeries = new QBarSeries();
    barSeries->append(set);
    barSeries->setLabelsVisible(true);

    QChart* barChart = new QChart();
    barChart->addSeries(barSeries);
    barChart->setTitle("");
    barChart->setBackgroundVisible(false);
    barChart->legend()->hide();
    barChart->setMargins(QMargins(0,0,0,0));
    barChart->setAnimationOptions(QChart::SeriesAnimations);

    // 横坐标：近14天（含今天），从小到大
    QStringList categories;
    QDate today = QDate::currentDate();
    for (int i = 0; i < dailyCounts.size(); ++i) {
        QDate d = today.addDays(-(dailyCounts.size() - 1 - i));
        categories << d.toString("M-d");
    }
    QBarCategoryAxis* axisX = new QBarCategoryAxis();
    axisX->append(categories);
    barChart->addAxis(axisX, Qt::AlignBottom);
    barSeries->attachAxis(axisX);

    // 取消纵坐标

    QChartView* barChartView = new QChartView(barChart);
    barChartView->setRenderHint(QPainter::Antialiasing);
    barChartView->setMinimumHeight(140);
    barChartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    barChartView->setStyleSheet(chartStyle);

    // --- 进度条 ---
    int learned = DBptr->learnednum();
    int total = DBptr->getTotalWordCount();
    QProgressBar* progressBar = new QProgressBar(ui->showWidget);
    progressBar->setMinimum(0);
    progressBar->setMaximum(total > 0 ? total : 1);
    progressBar->setValue(learned);
    double percent = total > 0 ? (double)learned / total * 100.0 : 0.0;
    progressBar->setFormat(QString("%1/%2 已学 (%3%)").arg(learned).arg(total).arg(QString::number(percent, 'f', 1)));
    progressBar->setAlignment(Qt::AlignCenter);
    progressBar->setMinimumHeight(28);
    progressBar->setStyleSheet(
        "QProgressBar {"
        " border: 1px solid #bbb; border-radius: 8px; background: #f5f5f5; text-align: center; color:rgb(77, 77, 77); }"
        "QProgressBar::chunk {"
        " background-color:rgb(95, 211, 99); border-radius: 8px; }"
    );
    progressBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // --- 纵向布局，宽度自适应 ---
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(barChartView);
    mainLayout->addWidget(progressBar);
    mainLayout->setSpacing(12);
    mainLayout->setContentsMargins(8, 8, 8, 8);
    ui->showWidget->setLayout(mainLayout);
}

void LearnWidget::initWordsWidget()
{
    // tmp();

    // 清空并设置表头
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
        // 设置自动换行
        defItem->setData(Qt::TextWrapAnywhere, true);
        defItem->setFlags(defItem->flags() | Qt::ItemIsEditable); // 允许wrap属性生效
        ui->wordsListWidget->setItem(i, 1, defItem);
    }
    // 自动调整列宽和行高，使内容自适应
    ui->wordsListWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->wordsListWidget->horizontalHeader()->setStretchLastSection(true);
    ui->wordsListWidget->resizeRowsToContents();

    // 设置表格支持自动换行（全局）
    ui->wordsListWidget->setWordWrap(true);
}

void LearnWidget::initCheckout()
{
    // tmp();
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
        // 设置文本颜色为黑色
        wordItem->setForeground(QBrush(Qt::black));
        defItem->setForeground(QBrush(Qt::black));

        ui->wordsListWidget->setItem(i, 0, wordItem);
        ui->wordsListWidget->setItem(i, 1, defItem);
    }
    // 自动调整列宽和行高，使内容自适应
    ui->wordsListWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->wordsListWidget->horizontalHeader()->setStretchLastSection(true);
    ui->wordsListWidget->resizeRowsToContents();

    // 设置表格支持自动换行（全局）
    ui->wordsListWidget->setWordWrap(true);

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

    // 确保 optionLabels 有 4 个元素且全部已初始化
    optionLabels.resize(4);
    for (int i = 0; i < 4; ++i)
    {
        QLabel* lbl = nullptr;
        switch (i) {
        case 0: lbl = ui->label_0; break;
        case 1: lbl = ui->label_1; break;
        case 2: lbl = ui->label_2; break;
        case 3: lbl = ui->label_3; break;
        }
        optionLabels[i] = lbl;
        lbl->setStyleSheet(kLabelNormalStyle);
        lbl->setCursor(Qt::PointingHandCursor);
        lbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        lbl->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred); // 关键：自动延展
        lbl->disconnect();
        lbl->installEventFilter(this);
    }


    // 连接确定按钮
    disconnect(ui->testConfirmButton, nullptr, nullptr, nullptr);
    connect(ui->testConfirmButton, &QToolButton::clicked, this, [=]() {
        if (currentSelected == -1) return; // 未选择
        int wordId = wordsList[currentTestIndex].id;
        bool correct = (optionLabels[currentSelected]->text() == correctAnswer);
        testResults[currentTestIndex] = correct;
        DBptr->updateWordLearningInfo(wordId, correct, -int(correct));

        // 显示正误反馈
        for (int i = 0; i < 4; i++) {
            if (optionLabels[i]->text() == correctAnswer) {
                optionLabels[i]->setStyleSheet(kLabelCorrectStyle);
            } else if (i == currentSelected) {
                optionLabels[i]->setStyleSheet(kLabelWrongStyle);
            } else {
                optionLabels[i]->setStyleSheet(kLabelNormalStyle);
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

// 事件过滤器实现label点击选择
bool LearnWidget::eventFilter(QObject* watched, QEvent* event)
{
    for (int i = 0; i < 4; ++i) {
        if (watched == optionLabels[i] && event->type() == QEvent::MouseButtonRelease) {
            currentSelected = i;
            for (int j = 0; j < 4; ++j) {
                if (j == i) {
                    optionLabels[j]->setStyleSheet(kLabelSelectedStyle);
                } else {
                    optionLabels[j]->setStyleSheet(kLabelNormalStyle);
                }
            }
            return true;
        }
    }
    return QWidget::eventFilter(watched, event);
}

void LearnWidget::showTestForWord(int idx)
{
    if (idx < 0 || idx >= wordsList.size()) return;
    currentSelected = -1;
    ui->testWordLabel->setText(wordsList[idx].word);

    // 获取四个释义选项
    options = DBptr->FourmeaningtoChoice(wordsList[idx].id);
    if (options.size() < 4) {
        while (options.size() < 4) options << "";
    }
    correctAnswer = options[0];

    QVector<QString> shuffledOptions = options;
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(shuffledOptions.begin(), shuffledOptions.end(), g);

    for (int i = 0; i < 4; ++i) {
        optionLabels[i]->setText(shuffledOptions[i]);
        optionLabels[i]->setStyleSheet(kLabelNormalStyle);
        optionLabels[i]->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        optionLabels[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred); // 关键：自动延展
    }
}

void LearnWidget::on_addDictButton_clicked()
{
    // 打开文件选择对话框，选择txt文件
    QString txtFilePath = QFileDialog::getOpenFileName(this, "选择TXT词库文件", "", "文本文件 (*.txt)");
    if (txtFilePath.isEmpty()) {
        this->setFocus();
        return;
    }

    // 输入新词库名称，名称必填
    bool ok = false;
    QString dbName;
    while (true) {
        dbName = QInputDialog::getText(this, "新建词库", "请输入新词库名称（必填）：", QLineEdit::Normal, "", &ok);
        if (!ok) return;
        if (!dbName.trimmed().isEmpty()) break;
        QMessageBox::warning(this, "提示", "词库名称不能为空，请输入名称。");
    }

    // 选择本地牛津数据库名（可选，假设为"oxford"）
    QString search_dbname = "oxford_9";

    // 弹出导入中信息框
    QProgressDialog progress("正在导入词库，请稍候...", QString(), 0, 0, this);
    progress.setWindowModality(Qt::ApplicationModal);
    progress.setCancelButton(nullptr);
    progress.setMinimumDuration(0);
    progress.show();
    QApplication::processEvents();

    Wordloader loader;
    bool success = loader.importWordFromTXT(txtFilePath, dbName, search_dbname, true);

    progress.close();

    if (success) {
        defaultDictNames = DBptr->getlist();
        setupUI();
        QMessageBox::information(this, "导入成功", "新词库已成功导入！", QMessageBox::Ok);
        this->setFocus();
    } else {
        QMessageBox::warning(this, "导入失败", "导入词库失败，请检查文件格式或数据库权限。", QMessageBox::Ok);
        this->setFocus();
    }
}
void LearnWidget::on_dictButton_clicked()
{
    dictName = qobject_cast<DictButton*>(sender())->text();
    //跳转到词库信息界面
    ui->stackedWidget->setCurrentIndex(1);
    DBptr->closeCurrentDatabase();
    DBptr->initDatabase(dictName);
    //初始化界面
    initDictWidget();
}
void LearnWidget::on_reviewButton_clicked()
{
    //跳转到words界面
    ui->stackedWidget->setCurrentIndex(2);
    ui->testButton->setText("开始测试");
    wordsList.clear();
    wordsList = DBptr->getWordsToReview(10);

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
    wordsList = DBptr->getRandomWords(10);

    disconnect(ui->refreshButton, nullptr, nullptr, nullptr);
    connect(ui->refreshButton, &QToolButton::clicked, this, &LearnWidget::on_refreshButton_clicked_1);

    // 初始化单词列表界面
    initWordsWidget();

    // 成就
    emit sendId(2);
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
    wordsList = DBptr->getRandomWords(10);

    initWordsWidget();
}
void LearnWidget::on_refreshButton_clicked_2()
{
    ui->testButton->setText("开始测试");
    //重新获取wordsList
    wordsList.clear();
    wordsList = DBptr->getWordsToReview(10);

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




void LearnWidget::on_resetButton_clicked()
{
    DBptr->resetLearningRecords();
    initDictWidget();
}

