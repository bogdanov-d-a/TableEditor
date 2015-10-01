#include "plotwidget.h"
#include <QPainter>

PlotWidget::PlotWidget(QWidget *parent) : QWidget(parent)
{}

void PlotWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);

    painter.drawRect(0, 0, size().width() - 1, size().height() - 1);
}
