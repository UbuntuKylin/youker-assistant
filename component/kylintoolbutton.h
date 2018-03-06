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

#ifndef KYLINTOOlBUTTON_H
#define KYLINTOOlBUTTON_H

#include <QToolButton>
#include <QMouseEvent>
#include <QPainter>

class KylinToolButton : public QToolButton
{

public:
    explicit KylinToolButton(const QString &pic_name, const QString &text , QWidget *parent = 0);
    ~KylinToolButton();
    void setMousePress(bool is_press);
    void setMouseHover();
    bool pressed;

protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
	void mousePressEvent(QMouseEvent *event);

public:
	bool mouse_over; //鼠标是否移过
	bool m_mousePressed; //鼠标是否按下
    QIcon normal_icon;
    QIcon hover_icon;
    QIcon press_icon;
};

#endif //KYLINTOOlBUTTON_H
