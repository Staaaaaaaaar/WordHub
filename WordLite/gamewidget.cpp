#include "gamewidget.h"
#include "ui_gamewidget.h"
#include <QDebug>
#include "wordle.h"

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameWidget)
{
    ui->setupUi(this);
    setupUI();
    connectSignals();
}

GameWidget::~GameWidget()
{
    delete ui;
}

void GameWidget::setupUI()
{
    guessWordWidget=new guess_word_widget(this);
    wordle=new Wordle(this);
    ui->stackedWidget->addWidget(guessWordWidget);
    ui->stackedWidget->addWidget(wordle);

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

    // 清空原有布局内容
    QLayoutItem* item;
    while ((item = ui->gameLayout->takeAt(0)) != nullptr) {
        if (item->widget()) item->widget()->setParent(nullptr);
        delete item;
    }

    // 设置按钮为三列排列，每行不延展
    ui->gameLayout->setSpacing(30);
    ui->gameLayout->setContentsMargins(40, 40, 40, 40);
    ui->gameLayout->addWidget(ui->guessButton, 0, 0, 1, 1, Qt::AlignLeft | Qt::AlignTop);
    ui->gameLayout->addWidget(ui->wordleButton, 0, 1, 1, 1, Qt::AlignLeft | Qt::AlignTop);
    // 预留第三列位置
    QWidget* placeholder = new QWidget(this);
    placeholder->setFixedSize(1, 1);
    ui->gameLayout->addWidget(placeholder, 0, 2, 1, 1);
}

void GameWidget::connectSignals()
{
    connect(ui->guessButton, &QToolButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentWidget(guessWordWidget);
    });
    connect(ui->wordleButton, &QToolButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentWidget(wordle);
    });
    connect(guessWordWidget, &guess_word_widget::exitRequested, this, &GameWidget::onGuessWordWidgetExit);
    connect(wordle,&Wordle::exitSignals,this,&GameWidget::onGuessWordWidgetExit);
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
