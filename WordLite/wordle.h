#ifndef WORDLE_H
#define WORDLE_H

#include <QWidget>
#include <QVector>
#include <QSet>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

namespace Ui {
class Wordle;
}

class Wordle : public QWidget
{
    Q_OBJECT

public:
    explicit Wordle(QWidget *parent = nullptr);
    ~Wordle();
    static const int MAX_ATTEMPTS=6;
    static const int WORD_LENGTH=5;

    QString target_word;
    int currentRow;
    int currentCol;
    int attempts;
    bool game_over;

    QVector<QVector<QLabel*> > letterGrid;
    QVector<QPushButton*> keyBoardButtons;
    QGridLayout *boardLayout;
    QGridLayout *keyboardLayout;

    void initUI();
    void initGameBoard();
    void selectRandomWord();

    void submitGuess();
    void evaluateGuess();
    void updateKeyBoardColors();
    void endGame(bool isWin);

    bool isValidWord(const QString & word);
    void updateStatusMessage(const QString & message);
    void setLetterColor(int row,int col,const QColor & color);


private:
    Ui::Wordle *ui;
};

#endif // WORDLE_H
