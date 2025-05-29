#ifndef WORDWIDGET_H
#define WORDWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QMenu>
#include <QActionGroup>
#include <QAction>
#include <QInputDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <./back_head/database.h>

namespace Ui {
class WordWidget;
}

class WordWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WordWidget(QString word, WordDatabase* ptr, QWidget *parent = nullptr);
    ~WordWidget();

    QString word;
    WordDatabase* DBptr;

    // 设置UI和连接信号槽
    void setupUI(QVector<Word> wordList);
    void connectSignals();

private:
    Ui::WordWidget *ui;

};

#endif // WORDWIDGET_H
