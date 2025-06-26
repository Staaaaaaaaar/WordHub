#include "guess_word_widget.h"
#include "ui_guess_word_widget.h"
#include <QtConcurrent> // 引入 Qt 并发框架

guess_word_widget::guess_word_widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::guess_word_widget)
{
    ui->setupUi(this);
    // 注意：m_guesser 不能有父对象，因为它将被移动到另一个线程
    m_guesser = new guess_word();
    m_watcher = new QFutureWatcher<std::map<QString, QString>>(this);

    // 当监视器发现任务完成时，调用 handleProcessingFinished 槽函数
    connect(m_watcher, &QFutureWatcher<std::map<QString, QString>>::finished, this, &guess_word_widget::handleProcessingFinished);

    // 假设您的UI里有一个名为 "startButton" 的按钮
    // connect(ui->startButton, &QPushButton::clicked, this, &guess_word_widget::onStartButtonClicked);
    // 您需要将上面这行代码中的 startButton 替换为您UI中实际的按钮名称
}

guess_word_widget::~guess_word_widget()
{
    // m_guesser 会在后台任务结束后自动被 QtConcurrent 清理
    delete ui;
}

// 当点击开始按钮时
void guess_word_widget::onStartButtonClicked()
{
    // 可以在这里禁用按钮，防止用户重复点击
    // ui->startButton->setEnabled(false);
    // ui->descriptionLabel->setText("正在向AI请求题目，请稍候..."); // 给用户一个提示

    // 使用 QtConcurrent::run 在后台线程执行耗时的 processingPython 函数
    // 这行代码会立即返回，不会阻塞UI
    QFuture<std::map<QString, QString>> future = QtConcurrent::run([this]() -> std::map<QString, QString> {
        return m_guesser->processingPython();
    });

    m_watcher->setFuture(future);
}

// 当后台任务完成时，此函数会被自动调用
void guess_word_widget::handleProcessingFinished()
{
    // 可以在这里恢复按钮
    // ui->startButton->setEnabled(true);

    // 从监视器获取后台函数的返回结果
    std::map<QString, QString> result = m_watcher->result();

    if (result.count("error")) {
        // 如果结果中包含 "error" 键，说明出错了
        // ui->descriptionLabel->setText("获取题目失败: " + result["error"]);
    } else {
        // 成功获取数据，更新UI
        // ui->descriptionLabel->setText(result["description"]);
        // ui->translationLabel->setText(result["translation"]);
        m_correctWord = result["word"]; // 保存正确答案
    }
}
