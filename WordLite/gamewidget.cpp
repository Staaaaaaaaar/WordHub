#include "gamewidget.h"
#include "ui_gamewidget.h"
#include "guess_according_to_description_h/guess_word.h"

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameWidget)
{
    ui->setupUi(this);
}

GameWidget::~GameWidget()
{
    delete ui;
}

void GameWidget::on_guessButton_clicked()
{
    guess_word g;
    g.processingPython();
}

