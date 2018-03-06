/*
 * Copyright (C) 2013 ~ 2015 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  Kobe Lee    xiangli@ubuntukylin.com/kobe24_lixiang@126.com
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

#include "systembutton.h"
#include <QDebug>

SystemButton::SystemButton(QWidget *parent) :
    QPushButton(parent)
{
    status = NORMAL;
    m_mousePressed = false;
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
        m_mousePressed = true;
        status = PRESS;
        update();
    }
}

void SystemButton::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_mousePressed  && this->rect().contains(event->pos()))
    {
        m_mousePressed = false;
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
