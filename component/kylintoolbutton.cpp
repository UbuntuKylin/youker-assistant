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

#include "kylintoolbutton.h"
#include <QDebug>

KylinToolButton::KylinToolButton(const QString &pic_name, const QString &text, QWidget *parent)
    :QToolButton(parent)
{
    setDown(false);
    setFocusPolicy(Qt::NoFocus);

    this->setText(text);

//	QPalette text_palette = palette();
//	text_palette.setColor(QPalette::ButtonText, QColor(230, 230, 230));
//	setPalette(text_palette);

//	QFont &text_font = const_cast<QFont &>(font());
//	text_font.setWeight(QFont::Bold);

    setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
//    setToolButtonStyle( Qt::ToolButtonTextUnderIcon);
    setPopupMode(QToolButton::InstantPopup);

    QPixmap pixmap(pic_name);
    normal_icon = QIcon(pic_name);
    hover_icon = QIcon(pic_name + "-hover");
    press_icon = QIcon(pic_name + "-press");
    setIcon(pixmap);
    setIconSize(pixmap.size());

//    setFixedSize(pixmap.width(), pixmap.height() + 10);
	setAutoRaise(true);
    this->setObjectName("transparentToolButton");
	mouse_over = false;
	m_mousePressed = false;
    pressed = false;
}

KylinToolButton::~KylinToolButton()
{

}

void KylinToolButton::enterEvent(QEvent *event)
{
    if(isEnabled())
    {
        mouse_over = true;
        this->setMouseHover();
    }
}

void KylinToolButton::leaveEvent(QEvent *event)
{
    if(isEnabled())
    {
        mouse_over = false;
        this->setMouseHover();
    }
}

void KylinToolButton::mousePressEvent(QMouseEvent *event)
{
    if(isEnabled() && event->button() == Qt::LeftButton)
    {
        //kobe: don't emit, it will emit by click it self.
//        emit clicked();
    }
    QToolButton::mousePressEvent(event);
}

void KylinToolButton::setMouseHover()
{
    if(this->mouse_over)
    {
        this->setIcon(QIcon(hover_icon));
    }
    else {
        if(pressed)
            this->setIcon(QIcon(press_icon));
        else
            this->setIcon(QIcon(normal_icon));
    }
}

void KylinToolButton::setMousePress(bool is_press)
{
    this->m_mousePressed = is_press;

    if(this->m_mousePressed)
    {
        this->setIcon(QIcon(press_icon));
        pressed = true;
    }
    else
    {
        this->setIcon(QIcon(normal_icon));
        pressed = false;
    }

//    if(this->mouse_over)
//    {
//        this->setIcon(QIcon(hover_icon));
//    }
//    else
//    {
//        if(this->m_mousePressed)
//        {
//            this->setIcon(QIcon(press_icon));
//        }
//        else
//        {
//            this->setIcon(QIcon(normal_icon));
//        }
//    }
}
