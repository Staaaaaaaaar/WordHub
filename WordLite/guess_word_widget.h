#ifndef GUESS_WORD_WIDGET_H
#define GUESS_WORD_WIDGET_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class guess_word_widget;
}

class guess_word_widget : public QWidget
{
    Q_OBJECT

public:
    explicit guess_word_widget(QWidget *parent = nullptr);
    ~guess_word_widget();
    void connectSignals();
    void onExitButtonClicked();
    void onRuleButtonClicked();
    void onBeginButtonClicked();
    void onAnswerButtonClicked();
    void onCommitButtonClicked();
    QString word;
    QString translation;
    QString description;
    QString wordInput;
    QMessageBox *dialog;

signals:
    void exitRequested();
    void ruleRequested();
    void beginRequested();
    void answerRequested();
    void commitRequested();

private:
    Ui::guess_word_widget *ui;
};

#endif // GUESS_WORD_WIDGET_H
