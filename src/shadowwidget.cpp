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

#include "shadowwidget.h"
#include <QPainter>
#include <QtMath>
#include <QPen>

ShadowWidget::ShadowWidget(QWidget *parent) :
    QWidget(parent)
    ,widget_color(QColor("#fca71d"))
{
    widget_opacity = 1;
}

void ShadowWidget::setOpacity(qreal opacity)
{
    widget_opacity = opacity;
    update();
}

void ShadowWidget::mousePressEvent(QMouseEvent *event)
{
//    if(event->button() == Qt::LeftButton)
//    {
//        m_mousePressed = true;
//        m_dragPosition = event->globalPos() - this->frameGeometry().topLeft();
//        event->accept();
//    }
    if(event->button() == Qt::LeftButton)
    {
        m_mousePressed = true;
        m_dragPosition = event->globalPos() - pos();
    }
}

void ShadowWidget::mouseReleaseEvent(QMouseEvent *)
{
    m_mousePressed = false;
    setWindowOpacity(1);
}

void ShadowWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_mousePressed)
    {
        QPoint move_pos = event->globalPos();
        move(move_pos - m_dragPosition);
        setWindowOpacity(0.9);
//        event->accept();
    }
}

void ShadowWidget::paintEvent(QPaintEvent *)
{
//    QPainter painter(this);
//    painter.setOpacity(widget_opacity);
//    painter.setBrush(widget_color);
//    painter.setPen(Qt::NoPen);
//    painter.drawRect(rect());

    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(10,10,this->width()-20,this->height()-20);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.fillPath(path,QBrush(Qt::white));
//    QColor color(0,0,0,50);
    QColor color(widget_color);
    for(int i = 0 ; i < 10 ; ++i)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(10-i,10-i,this->width()-(10-i)*2,this->height()-(10-i)*2);
        color.setAlpha(150 - qSqrt(i)*50);
        painter.setPen(color);
        painter.drawPath(path);
    }
}
