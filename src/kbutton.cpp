/*
 * Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd.
 * Author: Kobe Lee
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "kbutton.h"

KButton::KButton(QWidget *parent)
    :QPushButton(parent)
{
    status = NORMAL;
    mouse_press = false;
}

KButton::~KButton()
{

}

void KButton::setPicName(QString pic_name)
{
    this->pic_name = pic_name;
    setFixedSize(QPixmap(pic_name).size());
}

void KButton::enterEvent(QEvent *)
{
    status = ENTER;
    update();
}

void KButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        mouse_press = true;
        status = PRESS;
        update();
    }
}

void KButton::mouseReleaseEvent(QMouseEvent *event)
{
    if(mouse_press  && this->rect().contains(event->pos())) {
        mouse_press = false;
        status = ENTER;
        update();
        emit clicked();
    }
}

void KButton::leaveEvent(QEvent *)
{
    status = NORMAL;
    update();
}

void KButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pixmap;
    switch(status) {
        case NORMAL:
            pixmap.load(pic_name);
            break;
        case ENTER:
            pixmap.load(pic_name + QString("_hover"));
            break;
        case PRESS:
            pixmap.load(pic_name + QString("_hover"));
            break;
        case NOSTATUS:
            pixmap.load(pic_name);
            break;
        default:
            pixmap.load(pic_name);
    }
    painter.drawPixmap(rect(), pixmap);
}
