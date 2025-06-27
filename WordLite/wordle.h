#ifndef WORDLE_H
#define WORDLE_H

#include <QWidget>
#include <vector>
#include <set>

// Forward declarations
class QLabel;
class QFont;

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

signals:
    void exitSignals();
    void sendId(int id);

private slots:
    // 恢复为独立的槽函数
    void game();
    void restart();
    void getText();
    void displayWord();
    void onExitButtonClicked();

private:
    // 内部辅助函数
    void setColor();
    void loadWord();
    void selectRandomWord();

    Ui::Wordle *ui;
    std::vector<QString> wordbase;
    std::vector<std::vector<QLabel*>> letterGrid;
    QString target_word;
    QString text;
    std::set<QChar> letters;
    int currentCol;
    int attempts;
    bool game_over;
    QFont *font;
};

#endif // WORDLE_H
