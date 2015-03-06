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

#include "cleansubbutton.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

CleanSubButton::CleanSubButton(QWidget *parent) :
    QWidget(parent)
{
//    hoverPixmap.load("://res/shadow_hover");
//    grayhoverPixmap.load("://res/shadow_gray_hover");
//    this->setFixedSize(hoverPixmap.size());
    this->setFixedSize(48, 48);
    QPixmap pixMap("://res/checkbox-tristate.png");
    int width = pixMap.width();
    int height = pixMap.height();
    int num = 9;//9*12=108
    for(int i=0; i != num; i++)
    {
        checkboxList.append(pixMap.copy(i*(width/num), 0, width/num, height));
    }
    //设置checkbox的显示位置:x(36), y(34)
    checkboxRect.setX(36);
    checkboxRect.setY(34);
    checkboxRect.setSize(checkboxList.at(0).size());
}

void CleanSubButton::setIconPath(const QString &icon)
{
    checkPixmap.load(icon + "_check");
//    midcheckPixmap.load(icon + "_midcheck");
    uncheckPixmap.load(icon + "_uncheck");
}

void CleanSubButton::setCleanButtonStatus(BUTTONSTATUS status)
{
    buttonStatus = status;
    update();
}

void CleanSubButton::setCheckboxStatus(int status)
{
    tristateStatus = status;
    setCleanButtonStatus(BUTTON_LEAVE);
}

void CleanSubButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    switch (buttonStatus) {
    case BUTTON_LEAVE:
        if(tristateStatus == 2)
        {
            painter.drawPixmap(rect(), checkPixmap);
            painter.drawPixmap(checkboxRect, checkboxList.at(3));
        }
        else if(tristateStatus == 1)
        {
            painter.drawPixmap(rect(), checkPixmap);
            painter.drawPixmap(checkboxRect, checkboxList.at(6));
        }
        else if(tristateStatus == 0)
        {
            painter.drawPixmap(rect(), uncheckPixmap);
            painter.drawPixmap(checkboxRect, checkboxList.at(0));
        }
        break;
    case BUTTON_ENTER:
        if(tristateStatus == 2)
        {
//            painter.drawPixmap(rect(), hoverPixmap);
            painter.drawPixmap(rect(), checkPixmap);
            painter.drawPixmap(checkboxRect, checkboxList.at(4));
        }
        else if(tristateStatus == 1)
        {
//            painter.drawPixmap(rect(), hoverPixmap);
            painter.drawPixmap(rect(), checkPixmap);
            painter.drawPixmap(checkboxRect, checkboxList.at(7));
        }
        else if(tristateStatus == 0)
        {
//            painter.drawPixmap(rect(), grayhoverPixmap);
            painter.drawPixmap(rect(), uncheckPixmap);
            painter.drawPixmap(checkboxRect, checkboxList.at(1));
        }
        break;
    case BUTTON_PRESSED:
        if(tristateStatus == 2)
        {
//            painter.drawPixmap(rect(), hoverPixmap);
            painter.drawPixmap(rect(), checkPixmap);
            painter.drawPixmap(checkboxRect, checkboxList.at(4));
        }
        else if(tristateStatus == 1)
        {
//            painter.drawPixmap(rect(), hoverPixmap);
            painter.drawPixmap(rect(), checkPixmap);
            painter.drawPixmap(checkboxRect, checkboxList.at(7));
        }
        else if(tristateStatus == 0)
        {
//            painter.drawPixmap(rect(), grayhoverPixmap);
            painter.drawPixmap(rect(), uncheckPixmap);
            painter.drawPixmap(checkboxRect, checkboxList.at(1));
        }
        break;
    default:
        break;
    }
}

void CleanSubButton::enterEvent(QEvent *)
{
    setCleanButtonStatus(BUTTON_ENTER);
}

void CleanSubButton::leaveEvent(QEvent *)
{
    setCleanButtonStatus(BUTTON_LEAVE);
}

void CleanSubButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        setCleanButtonStatus(BUTTON_PRESSED);
    }
    else
    {
        event->ignore();
    }
}

void CleanSubButton::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if(rect().contains(event->pos()))
        {
            setCleanButtonStatus(BUTTON_ENTER);
            emit this->clicked();
        }else
        {
            setCleanButtonStatus(BUTTON_LEAVE);
        }
    }
    else
    {
        event->ignore();
    }
}
