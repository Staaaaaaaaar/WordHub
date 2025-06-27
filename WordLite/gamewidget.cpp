#include "gamewidget.h"
#include "ui_gamewidget.h"
#include <QDebug>
#include "wordle.h"

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameWidget)
{
    ui->setupUi(this);
    guessWordWidget = new guess_word_widget(this);
    
    // 错误：不再在这里创建 Wordle 实例
    // wordle = new Wordle(this); 
    // 正确：将指针初始化为空
    wordle = nullptr;

    ui->stackedWidget->addWidget(guessWordWidget);
    // 不再在这里添加 wordle
    // ui->stackedWidget->addWidget(wordle);
    
    setupUI();
    connectSignals();
}

GameWidget::~GameWidget()
{
    delete ui;
}

void GameWidget::setupUI()
{
    // 设置按钮样式
    // QString btnStyle =
    //     "QToolButton {"
    //     "  background-color: #f0f0f0;"
    //     "  border: 2px solid #8f8f91;"
    //     "  border-radius: 12px;"
    //     "  font-size: 20px;"
    //     "  padding: 18px 36px;"
    //     "  color: #333;"
    //     "  margin: 12px;"
    //     "}"
    //     "QToolButton:hover {"
    //     "  background-color: #e0eaff;"
    //     "  border: 2px solid #5b9bd5;"
    //     "  color: #1a237e;"
    //     "}"
    //     "QToolButton:pressed {"
    //     "  background-color: #bbdefb;"
    //     "}";

    // ui->guessButton->setStyleSheet(btnStyle);
    // ui->wordleButton->setStyleSheet(btnStyle);

    ui->stackedWidget->setCurrentIndex(0);
}

void GameWidget::connectSignals()
{
    connect(ui->guessButton, &QToolButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentWidget(guessWordWidget);
    });

    // 错误：这个连接是无效的，因为 wordle 此时是 nullptr
    // connect(ui->wordleButton, &QToolButton::clicked, this, [=](){
    //     ui->stackedWidget->setCurrentWidget(wordle);
    // });
    // 正确：将按钮的点击信号连接到我们新创建的槽函数
    connect(ui->wordleButton, &QToolButton::clicked, this, &GameWidget::onWordleButtonClicked);

    connect(guessWordWidget, &guess_word_widget::exitRequested, this, &GameWidget::onGuessWordWidgetExit);
    
    // 错误：这些连接应该在 wordle 实例被创建之后进行
    // connect(wordle,&Wordle::exitSignals,this,&GameWidget::onGuessWordWidgetExit);
    // connect(wordle, &Wordle::sendId, this, &GameWidget::sendId);

    connect(guessWordWidget, &guess_word_widget::sendId, this, &GameWidget::sendId);
}

void GameWidget::onGuessWordWidgetExit()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void GameWidget::onBeginSignalCome()
{

}

void GameWidget::onAnswerSignalCome()
{

}

// 假设这是您 UI 中“进入Wordle游戏”按钮的槽函数
void GameWidget::onWordleButtonClicked() 
{
    // 1. 如果当前存在一个 Wordle 实例，则彻底删除它
    if (wordle != nullptr) {
        ui->stackedWidget->removeWidget(wordle); // 从布局中移除
        delete wordle;                           // 删除对象
        wordle = nullptr;                        // 指针置空，防止悬挂
    }

    // 2. 创建一个全新的 Wordle 实例
    wordle = new Wordle(this); // 'this' 确保了父子关系，有助于内存管理

    // 3. 将新实例的信号连接到处理函数上
    connect(wordle, &Wordle::exitSignals, this, &GameWidget::returnToGameMenu);
    connect(wordle, &Wordle::sendId, this, &GameWidget::sendId); // <--- 将信号连接移到这里

    // 4. 将新实例添加到 QStackedWidget 并切换到它
    ui->stackedWidget->addWidget(wordle);
    ui->stackedWidget->setCurrentWidget(wordle);
}

void GameWidget::returnToGameMenu()
{
    // 假设您的游戏选择界面是一个名为 gameSelectionPage 的 QWidget
    // 您需要将其替换为您UI中实际的页面名称
    // ui->stackedWidget->setCurrentWidget(ui->gameSelectionPage); 
    
    // 如果没有单独的页面，可以切换回第一个页面（通常是选择页）
    ui->stackedWidget->setCurrentIndex(0); 
}
