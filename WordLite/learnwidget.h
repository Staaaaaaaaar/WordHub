#ifndef LEARNWIDGET_H
#define LEARNWIDGET_H

#include "qtoolbutton.h"
#include <QWidget>
#include <QGridLayout>
#include <QList>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QTimer>
#include <random>
#include <QProgressBar>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <back_head/database.h>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include "back_head/loadword.h"

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
    QString dictName;

    int currentTestIndex;
    int currentSelected;

    void addButtonsToGrid(QGridLayout *grid, const QList<DictButton*> &buttons, int columns = 3);
    void initDictWidget();
    void initTestWidget();
    void initWordsWidget();
    void initCheckout();
    void showTestForWord(int idx);
    void tmp();

    // 设置UI和连接信号槽
    void setupUI();
    void connectSignals();

private slots:
    void on_dictButton_clicked();
    void on_testButton_clicked();
    void on_addDictButton_clicked();

    void on_reviewButton_clicked();

    void on_learnButton_clicked();

    void on_refreshButton_clicked_1();
    void on_refreshButton_clicked_2();

    void on_resetButton_clicked();

private:
    Ui::LearnWidget *ui;
    QList<DictButton*> defaultButtons;
    QList<DictButton*> customizeButtons;
    DictButton* addDictButton;
};




#endif // LEARNWIDGET_H
