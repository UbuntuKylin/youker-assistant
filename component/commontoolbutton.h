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

#ifndef COMMONOOlBUTTON_H
#define COMMONOOlBUTTON_H

#include <QToolButton>
#include <QMouseEvent>

class CommonToolButton : public QToolButton
{

public:
    explicit CommonToolButton(const QString &pic_name, const QString &text , QWidget *parent = 0);
    ~CommonToolButton();
    void setMousePress(bool is_press);

protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
	void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

public:
	bool mouse_over; //鼠标是否移过
	bool mouse_press; //鼠标是否按下
    QIcon normal_icon;
    QIcon hover_icon;
    QIcon press_icon;
};

#endif //COMMONOOlBUTTON_H
