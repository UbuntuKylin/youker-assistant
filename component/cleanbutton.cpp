/* Authors:
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

#include "cleanbutton.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

CleanButton::CleanButton(QWidget *parent) :
    QWidget(parent)
{
    hoverPixmap.load("://res/shadow_hover");
    grayhoverPixmap.load("://res/shadow_gray_hover");
    this->setFixedSize(hoverPixmap.size());
    QPixmap pixMap("://res/checkbox-two.png");
    int width = pixMap.width();
    int height = pixMap.height();//20
    int num = 6;//6*20=120
    for(int i=0; i != num; i++)
    {
        checkboxList.append(pixMap.copy(i*(width/num), 0, width/num, height));
    }
    //设置checkbox的显示位置:x(62), y(53)
    checkboxRect.setX(60);
    checkboxRect.setY(53);
    checkboxRect.setSize(checkboxList.at(0).size());
}

void CleanButton::setIconPath(const QString &icon)
{
    checkPixmap.load(icon + "_check");
    uncheckPixmap.load(icon + "_uncheck");
}

void CleanButton::setCleanButtonStatus(BUTTONSTATUS status)
{
    buttonStatus = status;
    update();
}

void CleanButton::setCheckboxStatus(int status)
{
    tristateStatus = status;
    setCleanButtonStatus(BUTTON_LEAVE);
}

void CleanButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    switch (buttonStatus) {
    case BUTTON_LEAVE:
        if(tristateStatus == 2)
        {
            painter.drawPixmap(rect(), checkPixmap);
            painter.drawPixmap(checkboxRect, checkboxList.at(2));
        }
        else if(tristateStatus == 1)
        {
            painter.drawPixmap(rect(), checkPixmap);
            painter.drawPixmap(checkboxRect, checkboxList.at(4));
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
            painter.drawPixmap(rect(), hoverPixmap);
            painter.drawPixmap(rect(), checkPixmap);
            painter.drawPixmap(checkboxRect, checkboxList.at(2));
        }
        else if(tristateStatus == 1)
        {
            painter.drawPixmap(rect(), hoverPixmap);
            painter.drawPixmap(rect(), checkPixmap);
            painter.drawPixmap(checkboxRect, checkboxList.at(4));
        }
        else if(tristateStatus == 0)
        {
            painter.drawPixmap(rect(), grayhoverPixmap);
            painter.drawPixmap(rect(), uncheckPixmap);
            painter.drawPixmap(checkboxRect, checkboxList.at(0));
        }
        break;
    case BUTTON_PRESSED:
        if(tristateStatus == 2)
        {
            painter.drawPixmap(rect(), hoverPixmap);
            painter.drawPixmap(rect(), checkPixmap);
            painter.drawPixmap(checkboxRect, checkboxList.at(2));
        }
        else if(tristateStatus == 1)
        {
            painter.drawPixmap(rect(), hoverPixmap);
            painter.drawPixmap(rect(), checkPixmap);
            painter.drawPixmap(checkboxRect, checkboxList.at(4));
        }
        else if(tristateStatus == 0)
        {
            painter.drawPixmap(rect(), grayhoverPixmap);
            painter.drawPixmap(rect(), uncheckPixmap);
            painter.drawPixmap(checkboxRect, checkboxList.at(0));
        }
        break;
    default:
        break;
    }
}

void CleanButton::enterEvent(QEvent *)
{
    setCleanButtonStatus(BUTTON_ENTER);
}

void CleanButton::leaveEvent(QEvent *)
{
    setCleanButtonStatus(BUTTON_LEAVE);
}

void CleanButton::mousePressEvent(QMouseEvent *event)
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

void CleanButton::mouseReleaseEvent(QMouseEvent *event)
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
