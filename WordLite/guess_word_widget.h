#ifndef GUESS_WORD_WIDGET_H
#define GUESS_WORD_WIDGET_H

#include <QWidget>

namespace Ui {
class guess_word_widget;
}

class guess_word_widget : public QWidget
{
    Q_OBJECT

public:
    explicit guess_word_widget(QWidget *parent = nullptr);
    ~guess_word_widget();

private:
    Ui::guess_word_widget *ui;
};

#endif // GUESS_WORD_WIDGET_H
