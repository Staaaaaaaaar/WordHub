#ifndef WORDWIDGET_H
#define WORDWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <./back_head/database.h>

namespace Ui {
class WordWidget;
}

class WordWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WordWidget(QString word, QWidget *parent = nullptr);
    ~WordWidget();

    QString word;

    // 设置UI和连接信号槽
    void setupUI(QVector<Word> wordList);
    void connectSignals();

private:
    Ui::WordWidget *ui;

};

#endif // WORDWIDGET_H
