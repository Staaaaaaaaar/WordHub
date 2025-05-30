#ifndef LEARNWIDGET_H
#define LEARNWIDGET_H

#include "qpushbutton.h"
#include "qtoolbutton.h"
#include <QWidget>
#include <QGridLayout>
#include <QList>
#include <QScrollArea>
#include <QTimer>
#include <back_head/database.h>

namespace Ui {
class LearnWidget;
class DictButton;
class AutoGridLayout;
}

class DictButton : public QToolButton
{
    Q_OBJECT

public:
    explicit DictButton(QString text="词库名"); //附加一个字典指针
    ~DictButton();

private:

};



class LearnWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LearnWidget(QWidget *parent = nullptr);
    ~LearnWidget();

    WordDatabase* DBptr;
    QVector<QString> defaultDictNames;

    Word* wordptr;
    QVector<Word> wordsList;
    QVector<bool> testResults;
    QVector<QString> options;
    QVector<QPushButton*> optionButtons;
    QString correctAnswer;

    int currentTestIndex;
    int currentSelected;

    void addButtonsToGrid(QGridLayout *grid, const QList<DictButton*> &buttons, int columns = 3);
    void initDictWidget();
    void initTestWidget();
    void initWordsWidget();
    void initCheckout();
    void showTestForWord(int idx);

    // 设置UI和连接信号槽
    void setupUI();
    void connectSignals();

private slots:
    void on_dictButton_clicked();
    void on_testButton_clicked();
    void on_addDictButton_clicked();

    void on_reviewButton_clicked();

    void on_learnButton_clicked();

    void on_refreshButton_clicked();

private:
    Ui::LearnWidget *ui;
    QList<DictButton*> defaultButtons;
    QList<DictButton*> customizeButtons;
    DictButton* addDictButton;
};




#endif // LEARNWIDGET_H
