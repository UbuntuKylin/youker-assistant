#include "pushbutton.h"

PushButton::PushButton(QWidget *parent)
    :QPushButton(parent)
{
    status = NORMAL;
    mouse_press = false;
}

PushButton::~PushButton() {
}

void PushButton::loadPixmap(QString pic_name) {
    pixmap.load(pic_name);
    btn_width = pixmap.width()/4;
    btn_height = pixmap.height();
    setFixedSize(btn_width, btn_height);
}

void PushButton::enterEvent(QEvent *) {
    status = ENTER;
    update();
}

void PushButton::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        mouse_press = true;
        status = PRESS;
        update();
    }
}

void PushButton::mouseReleaseEvent(QMouseEvent *) {
    if(mouse_press) {
        mouse_press = false;
        status = ENTER;
        update();
        emit clicked();
    }
}

void PushButton::leaveEvent(QEvent *) {
    status = NORMAL;
    update();
}

void PushButton::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawPixmap(rect(), pixmap.copy(btn_width * status, 0, btn_width, btn_height));
}
