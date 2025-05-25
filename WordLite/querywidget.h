#ifndef QUERYWIDGET_H
#define QUERYWIDGET_H

#include <QWidget>
#include <wordwidget.h>

namespace Ui {
class QueryWidget;
}

class QueryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QueryWidget(QWidget *parent = nullptr);
    ~QueryWidget();

private slots:
    void on_searchEdit_returnPressed();

    void on_tabWidget_tabCloseRequested(int index);

private:
    Ui::QueryWidget *ui;
};

#endif // QUERYWIDGET_H
