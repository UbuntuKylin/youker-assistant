#include "memorycircle.h"
#include "util.h"

#include <QDebug>
#include <QObject>

inline QString formatMemory(guint64 size)
{
    enum {
        K_INDEX,
        M_INDEX,
        G_INDEX,
        T_INDEX
    };

    QList<guint64> factorList;
    factorList.append(G_GUINT64_CONSTANT(1) << 10);//KiB
    factorList.append(G_GUINT64_CONSTANT(1) << 20);//MiB
    factorList.append(G_GUINT64_CONSTANT(1) << 30);//GiB
    factorList.append(G_GUINT64_CONSTANT(1) << 40);//TiB

    if (size < factorList.at(K_INDEX)) {
        if ((guint) size > 1) {
            return QString("%1 %2").arg((guint) size).arg(QObject::tr("byte"));
        }
        else {
            return QString("%1 %2").arg((guint) size).arg(QObject::tr("bytes"));
        }
    } else {
        guint64 factor;
        QString format;
        if (size < factorList.at(M_INDEX)) {
            factor = factorList.at(K_INDEX);
                format = QObject::tr("KiB");
        }else if (size < factorList.at(G_INDEX)) {
            factor = factorList.at(M_INDEX);
                format = QObject::tr("MiB");
        } else if (size < factorList.at(T_INDEX)) {
            factor = factorList.at(G_INDEX);
                format = QObject::tr("GiB");
        } else {
            factor = factorList.at(T_INDEX);
                format = QObject::tr("TiB");
        }
        std::string formatted_result(make_string(g_strdup_printf("%.1f", size / (double)factor)));
        return QString::fromStdString(formatted_result) + format;
    }
}

MemoryCircle::MemoryCircle(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize(400, 300);

    circleRadius = 128/2; //半径
    rectWidth = 100; //文本框宽
    rectHeight = 20; // 文本框高
    center = rect().center();
    center.setX(center.x()/2);
    center.setY(center.y()/2);
    swapcenter = rect().center();
    swapcenter.setX(swapcenter.x()*3/2);
    swapcenter.setY(swapcenter.y()/2);
}

MemoryCircle::~MemoryCircle()
{

}

void MemoryCircle::drawCircle(QPainter &painter, bool isSwap)
{
    //渐变效果设置
    /*QRadialGradient circleGradient(center, circleRadius, center);
    circleGradient.setColorAt(0.0, QColor(220, 220, 220));
    circleGradient.setColorAt(0.2, QColor(220, 220, 220));
    circleGradient.setColorAt(0.4, QColor(240, 240, 240));
    circleGradient.setColorAt(1.0, QColor(220, 220, 220));*/

    QPen pen;
    if (isSwap)
        pen.setColor(QColor("#fc7416"));
    else
        pen.setColor(QColor("#9528b4"));
    pen.setWidth(1);
    painter.setPen(pen);
//    painter.setBrush(circleGradient);
    painter.setBrush(QBrush(QColor("#ffffff")));

    if (isSwap)
        painter.drawEllipse(swapcenter, circleRadius, circleRadius);
    else
        painter.drawEllipse(center, circleRadius, circleRadius);
}

void MemoryCircle::drawColorPie(QPainter &painter, bool isSwap)
{
    //内存矩形，绘制扇形需要的参数，圆在矩形内且与矩形相切
    QPointF pieRectLeftTop(center.x()-circleRadius, center.y()-circleRadius);
    QPointF pieRectRightBottom(center.x()+circleRadius, center.y()+circleRadius);
    pieRect = QRectF(pieRectLeftTop, pieRectRightBottom);
    //SWAP矩形范围，，绘制扇形需要的参数，圆在矩形内且与矩形相切
    QPointF swapRectLeftTop(swapcenter.x()-circleRadius, swapcenter.y()-circleRadius);
    QPointF swapRectRightBottom(swapcenter.x()+circleRadius, swapcenter.y()+circleRadius);
    swappieRect = QRectF(swapRectLeftTop, swapRectRightBottom);


    if (isSwap) {
        if (mi.swappercent == 0)
            painter.setPen(Qt::NoPen);
        else {
            QPen pen;
            pen.setColor(QColor("#fc7416"));
            pen.setWidth(1);
            painter.setPen(pen);
        }
        painter.setBrush(QBrush(QColor("#fef5f1")));
        float swapcurrentPie = - (360 * (mi.swappercent/100)); //负数顺时针
        painter.drawPie(swappieRect, 90*16, swapcurrentPie*16);//绘制扇形，90*16为初始，12点钟位置
    }
    else {
        if (mi.percent == 0)
            painter.setPen(Qt::NoPen);
        else {
            QPen pen;
            pen.setColor(QColor("#9528b4"));
            pen.setWidth(1);
            painter.setPen(pen);
        }
        painter.setBrush(QBrush(QColor("#f4e9f7")));
        float currentPie = - (360 * (mi.percent/100)); //负数顺时针，0*16为3点钟位置
        painter.drawPie(pieRect, 90*16, currentPie*16); //绘制扇形，90*16为初始，12点钟位置
    }
}

void MemoryCircle::drawTextInfo(QPainter &painter)
{
    setFontSize(painter, 20);
    painter.setPen(QPen(QColor("#000000")));
    painter.drawText(QRect(center.x()-circleRadius, center.y() + circleRadius + 10, circleRadius*2, 30), Qt::AlignCenter, tr("Memory"));
    painter.drawText(QRect(swapcenter.x()-circleRadius, swapcenter.y() + circleRadius + 10, circleRadius*2, 30), Qt::AlignCenter, tr("Swap"));

    //draw title
    setFontSize(painter, 12);
    painter.setPen(QPen(QColor("#999999")));
    painter.drawText(QRect(center.x()-circleRadius, center.y() + circleRadius + 40, circleRadius*2, 30), Qt::AlignLeft |Qt::AlignVCenter, tr("Used(Percent)"));
    painter.drawText(QRect(swapcenter.x()-circleRadius, swapcenter.y() + circleRadius + 40, circleRadius*2, 30), Qt::AlignLeft |Qt::AlignVCenter, tr("Used(Percent)"));
    painter.drawText(QRect(center.x()-circleRadius, center.y() + circleRadius + 100, circleRadius*2, 30), Qt::AlignLeft |Qt::AlignVCenter, tr("Total"));
    painter.drawText(QRect(swapcenter.x()-circleRadius, swapcenter.y() + circleRadius + 100, circleRadius*2, 30), Qt::AlignLeft |Qt::AlignVCenter, tr("Total"));

    //draw text data
    setFontSize(painter, 20);
    QFontMetrics fm = painter.fontMetrics();
    painter.setPen(QPen(QColor("#000000")));
    const QString memeryUsed = tr("%1(%2%)").arg(formatMemory(mi.user)).arg(QString::number(mi.percent, 'f', 1));
    const QString swapUsed = tr("%1(%2%)").arg(formatMemory(mi.swapused)).arg(QString::number(mi.swappercent, 'f', 1));
    painter.drawText(QRect(center.x()-circleRadius, center.y() + circleRadius + 70, fm.width(memeryUsed), 30), Qt::AlignLeft |Qt::AlignVCenter, memeryUsed);
    painter.drawText(QRect(swapcenter.x()-circleRadius, swapcenter.y() + circleRadius + 70, fm.width(swapUsed), 30), Qt::AlignLeft |Qt::AlignVCenter, swapUsed);
    painter.drawText(QRect(center.x()-circleRadius, center.y() + circleRadius + 130, circleRadius*2, 30), Qt::AlignLeft |Qt::AlignVCenter, formatMemory(mi.total));
    painter.drawText(QRect(swapcenter.x()-circleRadius, swapcenter.y() + circleRadius + 130, circleRadius*2, 30), Qt::AlignLeft |Qt::AlignVCenter, formatMemory(mi.swaptotal));
}

void MemoryCircle::onUpdateMemoryStatus()
{
    glibtop_mem mem;
    glibtop_swap swap;

    glibtop_get_mem(&mem);
    glibtop_get_swap(&swap);

    float swappercent = (swap.total ? (float)swap.used / (float)swap.total : 0.0f);
    float mempercent  = (float)mem.user  / (float)mem.total;

    mi.percent = mempercent * 100;
    mi.swappercent = swappercent * 100;

    //初始单位为字节，需要修正
    mi.user = mem.user;
    mi.total = mem.total;

    mi.swapused = swap.used;
    mi.swaptotal = swap.total;

    const QString info = QString("%1/%2(%3%)").arg(formatMemory(mi.user)).arg(formatMemory(mi.total)).arg(QString::number(mi.percent, 'f', 1));
    emit rebackMemoryInfo(info, mi.percent);

    repaint();//this->update();
}

void MemoryCircle::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);//反走样,绘制出来的线条会出现锯齿

    //draw memory circle
    drawCircle(painter);
    drawColorPie(painter);

    //draw swap circle
    drawCircle(painter, true);
    drawColorPie(painter, true);

    painter.setRenderHint(QPainter::Antialiasing, false);
    drawTextInfo(painter);
}
