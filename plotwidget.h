#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>

class MyTableModel;
class QTimer;

class PlotWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlotWidget(MyTableModel *table, QWidget *parent = 0);
    ~PlotWidget();

public slots:
    void setAngle(int angle);

protected:
    void paintEvent(QPaintEvent *event);

private:
    MyTableModel *m_table;
    double m_shift, m_angle;
    QTimer *m_timer;

private slots:
    void onTimer();
};

#endif // PLOTWIDGET_H
