#include "guess_word_widget.h"
#include "ui_guess_word_widget.h"
#include <QtConcurrent> // 引入 Qt 并发框架
#include <QMessageBox>
#include <QTextOption>

guess_word_widget::guess_word_widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::guess_word_widget)
{
    ui->setupUi(this);

    // --- 异步处理部分初始化 ---
    // m_guesser 不能有父对象，因为它将被移动到另一个线程
    m_guesser = new guess_word();
    m_watcher = new QFutureWatcher<std::map<QString, QString>>(this);
    // 当监视器发现任务完成时，调用 handleProcessingFinished 槽函数
    connect(m_watcher, &QFutureWatcher<std::map<QString, QString>>::finished, this, &guess_word_widget::handleProcessingFinished);

    // --- 成员变量和UI初始化 (来自旧代码) ---
    m_word = "";
    m_translation = "";
    m_description = "";
    m_dialog = new QMessageBox(this); // 创建消息对话框

    ui->displayTextEdit->setStyleSheet(
        "QTextEdit {"
        "   font-family: '微软雅黑';"
        "   font-size: 10pt;"
        "}"
    );
    ui->displayTextEdit->setLineWrapMode(QTextEdit::WidgetWidth);
    ui->displayTextEdit->setWordWrapMode(QTextOption::WordWrap);

    // --- 信号与槽连接 (来自旧代码) ---
    // 注意：这里假设您的UI文件中按钮的 objectName 分别是：
    // exitButton, ruleButton, beginButton, answerButton, commitButton
    connect(ui->exitButton, &QPushButton::clicked, this, &guess_word_widget::on_exitButton_clicked);
    connect(ui->ruleButton, &QPushButton::clicked, this, &guess_word_widget::onRuleButtonClicked);
    connect(ui->startButton, &QPushButton::clicked, this, &guess_word_widget::onBeginButtonClicked);
    connect(ui->answerButton, &QPushButton::clicked, this, &guess_word_widget::onAnswerButtonClicked);
    connect(ui->commitButton, &QPushButton::clicked, this, &guess_word_widget::onCommitButtonClicked);
}

guess_word_widget::~guess_word_widget()
{
    // m_guesser 由 QtConcurrent 管理，不需要手动 delete
    delete ui;
}

// “开始游戏”按钮的槽函数 (替换了旧的 onBeginButtonClicked 的前半部分)
void guess_word_widget::onBeginButtonClicked()
{
    // 禁用按钮，防止用户在请求期间重复点击
    ui->startButton->setEnabled(false);
    ui->displayTextEdit->setText("正在向AI请求题目，请稍候..."); // 给用户一个提示

    // --- 新增代码 ---
    emit sendId(4); 

    // 使用 QtConcurrent::run 在后台线程执行耗时的 processingPython 函数
    // 这行代码会立即返回，不会阻塞UI
    QFuture<std::map<QString, QString>> future = QtConcurrent::run([this]() -> std::map<QString, QString> {
        return m_guesser->processingPython();
    });

    m_watcher->setFuture(future);
}

// 当后台任务完成时，此函数会被自动调用 (替换了旧的 onBeginButtonClicked 的后半部分)
void guess_word_widget::handleProcessingFinished()
{
    // 恢复按钮
    ui->startButton->setEnabled(true);

    // 从监视器获取后台函数的返回结果
    std::map<QString, QString> result = m_watcher->result();

    if (result.count("error")) {
        // 如果结果中包含 "error" 键，说明出错了
        ui->displayTextEdit->setText("获取题目失败: " + result["error"]);
        m_word = ""; // 清空单词，防止后续逻辑出错
    } else {
        // 成功获取数据，更新成员变量
        m_word = result["word"];
        m_translation = result["translation"];
        m_description = result["description"];

        // 更新UI，显示题目和提示
        if (!m_word.isEmpty() && m_word.length() >= 2) {
            ui->displayTextEdit->setText(m_description + "\n\n请在下方输入你的答案" + "\n提示：这是开头的两个字母: " + m_word.left(2));
        } else {
            ui->displayTextEdit->setText("获取的单词数据不完整，请重试。");
            m_word = "";
        }
    }
}

// --- 以下是直接从旧代码迁移过来的槽函数 ---

void guess_word_widget::on_exitButton_clicked()
{
    emit exitRequested();
}

void guess_word_widget::onRuleButtonClicked()
{
    QString rule = "本游戏由DEEPSEEK-V3对从词库中随机抽取的单词生成描述，请你根据描述猜出是哪个词，如果查看答案会显示英文单词，deepseek生成解释的翻译以及里面重点词的意思，有以下文件夹可供选择："
                   "四六级词汇合集，四级词汇，六级词汇，GRE词汇，牛津词典词汇，小学英语词汇，中考英语词汇";
    ui->displayTextEdit->setText(rule);
}

void guess_word_widget::onAnswerButtonClicked()
{
    if (m_word.isEmpty()) {
        ui->displayTextEdit->setText("请先点击“开始游戏”获取题目。");
        return;
    }
    ui->displayTextEdit->setText(m_word + "\n\n" + m_translation);
}

void guess_word_widget::onCommitButtonClicked()
{
    QString text = ui->answerLineEdit->text();
    if (text.isEmpty() || m_word.isEmpty()) {
        m_dialog->setWindowTitle("错误信息");
        m_dialog->setText("后端未运行或用户未输入！");
        m_dialog->exec();
    } else {
        if (text.toLower() == m_word.toLower()) { // 比较时忽略大小写
            ui->displayTextEdit->setText("You Win!");
            m_word = ""; // 猜对后清空，防止重复提交
        } else {
            ui->displayTextEdit->setText("I am sorry. Please try again.");
        }
        ui->answerLineEdit->clear(); // 提交后清空输入框
    }
}

