#ifndef WORDLE_H
#define WORDLE_H

#include <QWidget>
#include <QVector>
#include <QSet>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <vector>
#include <QFont>
using namespace std;

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
    QString text;
    int currentCol;
    int attempts;
    bool game_over;
    vector<vector<QLabel*> > letterGrid;

    vector<QString> wordbase;
    QSet<QString> letters;

    void selectRandomWord();
    void loadWord();
    void game();
    void onExitButtonClicked();
    void getText();
    void setColor();
    void restart();
    void displayWord();
    QFont *font;

signals:
    void exitSignals();
private:
    Ui::Wordle *ui;
};

#endif // WORDLE_H
