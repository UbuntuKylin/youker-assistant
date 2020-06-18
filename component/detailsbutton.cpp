#include "detailsbutton.h"
#include <QMouseEvent>

DetailsButton::DetailsButton(QString text, QWidget *parent)
    :QPushButton(parent)
{
    this->setAutoFillBackground(true);
    buttonText = text;
}

DetailsButton::~DetailsButton()
{

}

void DetailsButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); //反锯齿
    painter.setPen(Qt::transparent);

    if(hover)
        painter.setBrush(QBrush(QColor(64,64,64,80)));
    else
        painter.setBrush(QBrush(QColor(64,64,64,30)));

    painter.drawRoundedRect(0,0,this->width(),this->height(),18,18);
    painter.setPen(QColor(0,0,0,185));
    painter.drawText(QPoint(25,23),buttonText);

    painter.setBrush(QBrush(QColor(64,64,64)));
    static const QPointF points[3] = {
        QPointF(95.0, 15.0),
        QPointF(95.0, 25.0),
        QPointF(85.0, 25.0)
    };
    painter.drawConvexPolygon(points,3);

    painter.end();  //画完了

    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);


    QWidget::paintEvent(event);
}

void DetailsButton::mousePressEvent(QMouseEvent *event)
{

}

void DetailsButton::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit this->clicked();
    }
}

void DetailsButton::enterEvent(QEvent *event)
{
    hover = true;
    this->repaint();
}

void DetailsButton::leaveEvent(QEvent *event)
{
    hover = false;
    this->repaint();
}
