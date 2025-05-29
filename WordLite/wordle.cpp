#include "wordle.h"
#include "ui_wordle.h"

Wordle::Wordle(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Wordle)
{
    ui->setupUi(this);
}

Wordle::~Wordle()
{
    delete ui;
}

void Wordle::initGameBoard()
{
    letterGrid.resize(MAX_ATTEMPTS);
    for (int row=0;row<MAX_ATTEMPTS;++row)
    {
        letterGrid[row].resize(WORD_LENGTH);
        for (int col=0;col<WORD_LENGTH;++col)
        {
            QLabel *label=new QLabel("",this);
            label->setAlignment(Qt::AlignCenter);
            label->setStyleSheet("border: 2px solid #d3d6da; border-radius: 3px;"
                                 "font-size: 32px; font-weight: bold;"
                                 "min-width: 60px; min-height: 60px;");
            letterGrid[row][col]=label;
            boardLayout->addWidget(label,row,col);
        }
    }
}

void Wordle::selectRandomWord()
{

}
