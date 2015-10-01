#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>

class MyTableModel;

class PlotWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlotWidget(MyTableModel *table, QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);

private:
    MyTableModel *m_table;
};

#endif // PLOTWIDGET_H
