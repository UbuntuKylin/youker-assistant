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

#include "commontoolbutton.h"

CommonToolButton::CommonToolButton(const QString &pic_name, const QString &text, QWidget *parent)
    :QToolButton(parent)
{
    setDown(false);
    setFocusPolicy(Qt::NoFocus);

    this->setText(text);

//	QPalette text_palette = palette();
//	text_palette.setColor(QPalette::ButtonText, QColor(230, 230, 230));
//	setPalette(text_palette);

    setToolButtonStyle( Qt::ToolButtonTextUnderIcon);
    setPopupMode(QToolButton::InstantPopup);

    QPixmap pixmap(pic_name);
    normal_icon = QIcon(pic_name);

    setIcon(pixmap);
    setIconSize(pixmap.size());

//    setFixedSize(pixmap.width(), pixmap.height() + 10);
	setAutoRaise(true);
    this->setObjectName("commonToolButton");
	mouse_over = false;
	mouse_press = false;
}

CommonToolButton::~CommonToolButton()
{

}

void CommonToolButton::enterEvent(QEvent *event)
{
    if(isEnabled())
    {
        mouse_over = true;
    }
}

void CommonToolButton::leaveEvent(QEvent *event)
{
    if(isEnabled())
    {
        mouse_over = false;
    }
}

void CommonToolButton::mousePressEvent(QMouseEvent *event)
{
    if(isEnabled() && event->button() == Qt::LeftButton)
    {
        emit clicked();
    }
    QToolButton::mousePressEvent(event);
}

void CommonToolButton::setMousePress(bool is_press)
{
    this->mouse_press = is_press;
	update();
}

void CommonToolButton::paintEvent(QPaintEvent *event)
{
    if(this->mouse_over)
    {
        this->setIcon(QIcon(press_icon));
    }
    else
    {
        if(this->mouse_press)
        {
            this->setIcon(QIcon(hover_icon));
        }
        else
        {
            this->setIcon(QIcon(normal_icon));
        }
    }

    QToolButton::paintEvent(event);
}
