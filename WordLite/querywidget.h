#ifndef QUERYWIDGET_H
#define QUERYWIDGET_H

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
#include <QToolButton>
#include <QWidgetAction>
#include <QCheckBox>
#include <./back_head/database.h>
#include <./API/dictionaryapi.h>

namespace Ui {
class QueryWidget;
class WordWidget;
}

class WordWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WordWidget(QString word, WordDatabase* ptr, bool& useapi, QWidget *parent = nullptr);
    ~WordWidget();

    QString word;
    bool useAPI = false;
    WordDatabase* DBptr;

    // 设置UI和连接信号槽
    void setupUI(QVector<Word> wordList);
    void connectSignals();

private: signals:
    void sendMes(QString message, int timeout=0);
    void clearMes();
private:
};



class QueryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QueryWidget(QWidget *parent = nullptr);
    ~QueryWidget();

    WordWidget* wordWidget;
    WordDatabase* wordDataBase;
    DictionaryAPI* dictionaryAPI;
    bool useAPI = false;
    QString defaultWordDB;
    QVector<QString> wordDBList;

    void setupUI();
    void connectSignals();

private slots:
    void on_searchEdit_returnPressed();

    void on_tabWidget_tabCloseRequested(int index);

    void on_comboBox_currentTextChanged(const QString &arg1);

    void sendMess(QString message, int timeout);
    void clearMess();



private: signals:
    void sendMes(QString message, int timeout=0);
    void clearMes();

    void sendId(int id);


private:
    Ui::QueryWidget *ui;
};






#endif // QUERYWIDGET_H
