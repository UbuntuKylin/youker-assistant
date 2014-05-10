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

#include "icontext.h"
#include <QDebug>
IconText::IconText(int index, QWidget *parent) :
    QWidget(parent)
{
    mouseEnter = false;
    mousePress = false;
    btnIcon = new QLabel(this);
    cur_index = index;
}

IconText::~IconText()
{
    delete btnIcon;
}

void IconText::setIcon(const QPixmap &pixmap)
{
    btnIcon->setPixmap(pixmap.scaled(QSize(14, 14), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void IconText::setMouseEnterFlag(bool flag)
{
    mouseEnter = flag;
    this->update();
}

void IconText::setMousePressFlag(bool flag)
{
    mousePress = flag;
    this->update();
}

void IconText::enterEvent(QEvent *)
{
    if(!mousePress)
    {
        setMouseEnterFlag(true);
    }
    this->setCursor(Qt::PointingHandCursor);
}

void IconText::leaveEvent(QEvent *)
{
    setMouseEnterFlag(false);
}

void IconText::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        setMousePressFlag(true);
//        emit ukclicked(this);
        emit ukclicked(this->cur_index);

    }
}

void IconText::paintEvent(QPaintEvent *e)
{
    if(mouseEnter) {//鼠标放上去的时候
        paintChangePic(true);
    }
    else if(mousePress) {//鼠标点击选中
        paintChangePic(true);
    }
    else if(!mousePress) {//鼠标没有选中
        paintChangePic(false);
    }
    QWidget::paintEvent(e);
}

void IconText::paintChangePic(bool flag)
{
    QPixmap pixmap;
    if(flag) {
        pixmap = QPixmap(QString(":/pixmap/image/dot_active"));
    }
    else {
        pixmap = QPixmap(QString(":/pixmap/image/dot_normal"));
    }
    btnIcon->setPixmap(pixmap.scaled(QSize(14, 14), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
