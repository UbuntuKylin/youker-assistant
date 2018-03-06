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

#include "kylinbutton.h"

KylinButton::KylinButton(QWidget *parent)
	:QPushButton(parent)
{	
	status = NORMAL;
	m_mousePressed = false;
}

KylinButton::~KylinButton()
{

}

void KylinButton::setPicName(QString pic_name)
{
	this->pic_name = pic_name;
	setFixedSize(QPixmap(pic_name).size());
}

void KylinButton::enterEvent(QEvent *)
{
	status = ENTER;
	update();
}

void KylinButton::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		m_mousePressed = true;
		status = PRESS;
		update();
	}
}

void KylinButton::mouseReleaseEvent(QMouseEvent *event)
{
	if(m_mousePressed  && this->rect().contains(event->pos()))
	{
		m_mousePressed = false;
		status = ENTER;
		update();
		emit clicked();
	}
}

void KylinButton::leaveEvent(QEvent *)
{
	status = NORMAL;
	update();
}

void KylinButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pixmap;
    switch(status)
    {
    case NORMAL:
        {
            pixmap.load(pic_name);
            break;
        }
    case ENTER:
        {
            pixmap.load(pic_name + QString("_hover"));
            break;
        }
    case PRESS:
        {
            pixmap.load(pic_name + QString("_pressed"));
            break;
        }
    case NOSTATUS:
        {
            pixmap.load(pic_name);
            break;
        }
    default:
        pixmap.load(pic_name);
    }
	
    painter.drawPixmap(rect(), pixmap);
}
