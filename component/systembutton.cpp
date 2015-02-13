#include "systembutton.h"
#include <QDebug>

SystemButton::SystemButton(QWidget *parent) :
    QPushButton(parent)
{
    status = NORMAL;
    mouse_press = false;
}


void SystemButton::loadPixmap(QString pic_name)
{
    pixmap = QPixmap(pic_name);
    btn_width = pixmap.width()/3;
    btn_height = pixmap.height();
    this->setFixedSize(btn_width, btn_height);
}

void SystemButton::enterEvent(QEvent *)
{
    status = ENTER;
    update();
}

void SystemButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        mouse_press = true;
        status = PRESS;
        update();
    }
}

void SystemButton::mouseReleaseEvent(QMouseEvent *event)
{
    if(mouse_press  && this->rect().contains(event->pos()))
    {
        mouse_press = false;
        status = ENTER;
        update();
        emit clicked();
    }
}

void SystemButton::leaveEvent(QEvent *)
{
    status = NORMAL;
    update();
}

void SystemButton::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);
    painter.drawPixmap(this->rect(), pixmap.copy(btn_width * status, 0, btn_width, btn_height));
    painter.end();
}
