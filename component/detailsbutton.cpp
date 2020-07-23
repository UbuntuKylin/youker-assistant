/*
 * Copyright (C) 2013 ~ 2015 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  tang guang   tangguang@kylinos.cn
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
    painter.setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing); //反锯齿
    painter.setPen(Qt::transparent);

    if(hover)
        painter.setBrush(QBrush(QColor(64,64,64,80)));
    else
        painter.setBrush(QBrush(QColor(64,64,64,30)));

    painter.drawRoundedRect(0,0,this->width(),this->height(),18,18);
    painter.setPen(QColor(0,0,0,185));
    painter.drawText(QPoint(20,23),buttonText);

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
