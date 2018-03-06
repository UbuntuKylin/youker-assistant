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

#include "kylinswitcher.h"
#include <QDebug>

KylinSwitcher::KylinSwitcher(QWidget *parent) :
    QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    switchedOn = false;
    m_mousePressed = false;
    pixmap_on.load("://res/switch-on.png");
    pixmap_off.load("://res/switch-off.png");
    this->setFixedSize(pixmap_on.width(), pixmap_on.height());
    this->setCursor(Qt::PointingHandCursor);
}

void KylinSwitcher::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_mousePressed = true;
    }
}

void KylinSwitcher::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_mousePressed && this->rect().contains(event->pos())) {
        m_mousePressed = false;
        switchedOn = !switchedOn;
        emit clicked();
    }
    update();
}

//void KylinSwitcher::enterEvent(QEvent *)
//{
//    if(this->isEnabled()) {
//        update();
//    }
//}

void KylinSwitcher::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(QPoint(0,0), pixmap_on);
    QPoint off_point;
    if (switchedOn)
    {
        off_point = rect().topRight();
    }
    else
    {
        off_point = QPoint(this->width() - pixmap_off.width(), this->rect().top());
    }
    painter.drawPixmap(off_point, pixmap_off);

    if(switchedOn)
    {
        QRect rectON;
//        rectON.setTopLeft(rect().topLeft());
        rectON.setTopLeft(QPoint(rect().topLeft().x() + 10, rect().topLeft().y()));
        rectON.setBottomRight(QPoint(pixmap_off.width(), pixmap_off.height()));
        this->setStyleSheet("QWidget{color:#ffffff;font-size:12px;}");
        painter.drawText(rectON, Qt::AlignLeft | Qt::AlignVCenter, tr("ON"));
    }
    else
    {
        QRect rectOFF;
        rectOFF.setTopLeft(rect().topLeft());
//        rectOFF.setBottomRight(QPoint(pixmap_off.width(), pixmap_off.height()));
        rectOFF.setBottomRight(QPoint(pixmap_off.width() - 10, pixmap_off.height()));
        this->setStyleSheet("QWidget{color:#7c8487;font-size:12px;}");
        painter.drawText(rectOFF, Qt::AlignRight|Qt::AlignVCenter, tr("OFF"));
    }
}
