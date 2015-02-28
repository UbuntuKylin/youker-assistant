#include "switchmenu.h"

#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

SwitchMenu::SwitchMenu(QWidget *parent) :
    QWidget(parent)
{
//    setWindowFlags(Qt::FramelessWindowHint);

    m_bOn = false;

    m_bLBtnDown = false;

    m_pixmapBk.load(":/background/res/on.png");
    m_pixmapFore.load(":/background/res/off.png");

    setGeometry(0, 0, m_pixmapBk.width(), m_pixmapBk.height());
}

void SwitchMenu::paintEvent(QPaintEvent *)
{
    qDebug() << "1111111111";
    QPainter painter(this);

    painter.drawPixmap(QPoint(0,0), m_pixmapBk);

    QPoint ptFore;
    if (m_bOn) {
        ptFore = rect().topLeft();
    } else {
        ptFore = QPoint(this->width() - m_pixmapFore.width(),
                        this->rect().top());
    }
    painter.drawPixmap(ptFore, m_pixmapFore);

    QRect rcOn;
    rcOn.setTopLeft(rect().topLeft());
    rcOn.setBottomRight(QPoint(m_pixmapFore.width(), m_pixmapFore.height()));
    painter.drawText(rcOn, Qt::AlignCenter, "ON");

    QRect rcOff;
    rcOff.setTopLeft(QPoint(rect().width() - m_pixmapFore.width(), rect().top()));
    rcOff.setBottomRight(rect().bottomRight());
    painter.drawText(rcOff, Qt::AlignCenter, "Off");
}

void SwitchMenu::mousePressEvent(QMouseEvent *)
{
    qDebug() << "333333333";
    m_bLBtnDown = true;
}

void SwitchMenu::mouseReleaseEvent(QMouseEvent *e)
{
    qDebug() << "222222222";
    if (m_bLBtnDown) {
        m_bOn = !m_bOn;

        m_bLBtnDown = false;
    }

    update();
}

void SwitchMenu::leaveEvent(QEvent *)
{
//    status = NORMAL;
    update();
}

void SwitchMenu::enterEvent(QEvent *)
{
//    status = ENTER;
    update();
}








//void SystemButton::paintEvent(QPaintEvent *)
//{
//    QPainter painter;
//    painter.begin(this);
//    painter.drawPixmap(this->rect(), pixmap.copy(btn_width * status, 0, btn_width, btn_height));
//    painter.end();
//}
