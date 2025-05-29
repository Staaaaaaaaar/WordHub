#include "gamewidget.h"
#include "ui_gamewidget.h"
#include <QDebug>

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
    ui->stackedWidget->addWidget(guessWordWidget);
}

void GameWidget::connectSignals()
{
    connect(ui->guessButton, &QToolButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentWidget(guessWordWidget);
    });
    connect(guessWordWidget, &guess_word_widget::exitRequested, this, &GameWidget::onGuessWordWidgetExit);
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
