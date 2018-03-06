#ifndef MEMORYCIRCLE_H
#define MEMORYCIRCLE_H

#include <QWidget>
#include <QPainter>
#include <glibtop/mem.h>
#include <glibtop/swap.h>

typedef struct MemoryInfo
{
    float total;
    float free;
    float cached;
    float used;
    float user;
    float percent;

    float swaptotal;
    float swapfree;
    float swapcached;
    float swapused;
    float swappercent;

}Meminfo;

class MemoryCircle : public QWidget
{
    Q_OBJECT

public:
    MemoryCircle(QWidget *parent = 0);
    ~MemoryCircle();

    void drawCircle(QPainter &painter, bool isSwap = false);
    void drawColorPie(QPainter &painter, bool isSwap = false);
    void drawTextInfo(QPainter &painter);

public slots:
    void onUpdateMemoryStatus();

signals:
    void rebackMemoryInfo(const QString &info, double percent);

protected:
    void paintEvent(QPaintEvent * event);

private:
    qreal circleRadius;
    qreal rectWidth;
    qreal rectHeight;
    qreal colorPieRadius;
    QPointF center;
    QPointF swapcenter;
    QRectF pieRect;
    QRectF swappieRect;
    Meminfo mi;
};

#endif // MEMORYCIRCLE_H
