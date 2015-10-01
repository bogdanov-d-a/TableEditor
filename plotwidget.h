#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>

class PlotWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlotWidget(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // PLOTWIDGET_H
