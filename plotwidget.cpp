#include "plotwidget.h"
#include <QPainter>
#include "mytablemodel.h"

PlotWidget::PlotWidget(MyTableModel *table, QWidget *parent)
    :QWidget(parent)
    ,m_table(table)
{}

const QVector<QColor> colors = {
    "orange",
    "yellow",
    "green",
    "blue",
    "violet",
    "pink"
};

void PlotWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHints(painter.renderHints() | QPainter::Antialiasing);
    //painter.drawRect(0, 0, size().width() - 1, size().height() - 1);

    int sum = 0;
    for (int row = 0; row < m_table->getSize(); ++row)
        sum += m_table->getNumber(row);

    if (sum == 0)
        return;

    int start = 0;
    for (int row = 0; row < m_table->getSize(); ++row)
    {
        int curSize = 360 * 16 * m_table->getNumber(row) / sum;

        if (row == 0)
            painter.setBrush(QBrush("red"));
        else
            painter.setBrush(QBrush(colors[(row - 1) % colors.size()]));

        painter.drawPie(0, 0,
                        size().width(), size().height(),
                        start, curSize);

        start += curSize;
    }
}
