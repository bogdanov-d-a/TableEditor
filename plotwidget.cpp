#include "plotwidget.h"
#include <QPainter>
#include "mytablemodel.h"
#include <QtMath>

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

double DegAngleToRadAngle(double deg)
{
    return (deg / 180 * M_PI);
}

double RadAngleToDegAngle(double rad)
{
    return (rad / M_PI * 180);
}

QPolygonF GenerateSidePolygon(QVector<QPointF> const& line, QPointF const& shift)
{
    Q_ASSERT(!line.empty());
    QPolygonF result;

    for (auto &point : line)
        result << point;

    for (int i = line.size() - 1; i >= 0; --i)
        result << line[i] + shift;

    return result;
}

QPointF GetEllipsePoint(QRectF const& rect, double angle)
{
    return rect.center() + QPointF(
        rect.width() / 2 * cos(angle),
        rect.height() / 2 * sin(angle)
    );
}

int RadAngleToPieAngle(double angle)
{
    return RadAngleToDegAngle(angle) * 16;
}

void DrawPieHelper(QPainter &painter, QRectF const& rect, double astart, double aend)
{
    double alen = aend - astart;
    painter.drawPie(rect, RadAngleToPieAngle(-aend), RadAngleToPieAngle(alen));
}

double ConstrainAngle(double x)
{
    x = fmod(x, 2 * M_PI);
    if (x < 0)
        x += 2 * M_PI;
    return x;
}

double SmallestAngleDifference(double a, double b)
{
    double r = ConstrainAngle(a - b);
    if (r > M_PI)
        r -= 2 * M_PI;
    if (r < -M_PI)
        r += 2 * M_PI;
    return fabs(r);
}

void DrawPie(QPainter &painter, QRectF const& rect, QPointF const& shift, double astart, double aend)
{
    {
        double first, second;
        if (SmallestAngleDifference(astart, 3 * M_PI / 2) <
            SmallestAngleDifference(aend, 3 * M_PI / 2))
        {
            first = astart;
            second = aend;
        }
        else
        {
            first = aend;
            second = astart;
        }

        painter.drawPolygon(GenerateSidePolygon(
            { rect.center(), GetEllipsePoint(rect, first) },
            shift
        ));
        painter.drawPolygon(GenerateSidePolygon(
            { rect.center(), GetEllipsePoint(rect, second) },
            shift
        ));
    }

    {
        QVector<QPointF> arc;

        for (double angle = astart; angle <= aend; angle += 0.01)
        {
            if (ConstrainAngle(angle) <= M_PI)
                arc.push_back(GetEllipsePoint(rect, angle));
        }

        if (!arc.empty())
            painter.drawPolygon(GenerateSidePolygon(arc, shift));
    }

    DrawPieHelper(painter, rect, astart, aend);
}

struct PieInfo
{
    double astart;
    double alen;
    int number;

    PieInfo()
        :astart(0)
        ,alen(0)
        ,number(0)
    {}

    PieInfo(double astart, double alen, int number)
        :astart(astart)
        ,alen(alen)
        ,number(number)
    {}

    double Key() const
    {
        return SmallestAngleDifference(astart + alen / 2, 3 * M_PI / 2);
    }

    bool operator<(PieInfo const& other) const
    {
        return Key() < other.Key();
    }
};

void PlotWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHints(painter.renderHints() | QPainter::Antialiasing);
    painter.drawRect(0, 0, size().width(), size().height());

    const int HGAP = 10;
    double heightScale = 0.6;
    double thicknessScale = 0.05;
    double vgap = size().height() * (1 - heightScale) / 2;
    QRectF rect(HGAP, vgap, size().width() - 2 * HGAP, size().height() * heightScale);
    QPointF shift(0, size().height() * thicknessScale);

    int sum = 0;
    for (int row = 0; row < m_table->getSize(); ++row)
        sum += m_table->getNumber(row);

    if (sum == 0)
        return;

    QVector<PieInfo> pies;
    {
        double start = 0;
        for (int row = 0; row < m_table->getSize(); ++row)
        {
            double curSize = 2 * M_PI * m_table->getNumber(row) / sum;
            pies.push_back(PieInfo(start, curSize, row));
            start += curSize;
        }
    }
    qSort(pies);

    for (int pieId = 0; pieId < pies.size(); ++pieId)
    {
        PieInfo &pie = pies[pieId];

        if (pie.number == 0)
            painter.setBrush(QBrush("red"));
        else
            painter.setBrush(QBrush(colors[(pie.number - 1) % colors.size()]));

        DrawPie(painter, rect, shift, pie.astart, pie.astart + pie.alen);
    }
}
