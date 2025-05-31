#include "gamewidget.h"
#include "ui_gamewidget.h"
#include <QDebug>
#include "wordle.h"

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameWidget)
{
    ui->setupUi(this);
    guessWordWidget=new guess_word_widget(this);
    wordle=new Wordle(this);
    ui->stackedWidget->addWidget(guessWordWidget);
    ui->stackedWidget->addWidget(wordle);
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
    connect(ui->wordleButton, &QToolButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentWidget(wordle);
    });
    connect(guessWordWidget, &guess_word_widget::exitRequested, this, &GameWidget::onGuessWordWidgetExit);
    connect(wordle,&Wordle::exitSignals,this,&GameWidget::onGuessWordWidgetExit);


    connect(wordle, &Wordle::sendId, this, &GameWidget::sendId);
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
