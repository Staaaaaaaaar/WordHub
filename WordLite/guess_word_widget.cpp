#include "guess_word_widget.h"
#include "ui_guess_word_widget.h"

guess_word_widget::guess_word_widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::guess_word_widget)
{
    ui->setupUi(this);
}

guess_word_widget::~guess_word_widget()
{
    delete ui;
}
