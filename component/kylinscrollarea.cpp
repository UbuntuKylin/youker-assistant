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

#include "kylinscrollarea.h"
#include <QDebug>
#include "autogroup.h"


KylinScrollArea::KylinScrollArea(QWidget *parent/*, int width, int height, int spacing*/) :
    QWidget(parent)
{
    cardcount = 0;
    number_per_row = -1;
    this->setWindowFlags(Qt::FramelessWindowHint);
    itemwidth = 400;//width;
    itemheight = 50;//height;
    cardspacing = 6;//spacing;
    scroll_area = new QScrollArea(this);
    cardPanel = new QWidget();
    scroll_area->setWidget(cardPanel);
    scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
}

void KylinScrollArea::calculate_data()
{
   scroll_area->setGeometry(-1, -1, this->width() + 2, this->height() + 2);
   cardPanel->setGeometry(0, 0, this->width(), this->height());
   number_per_row = (this->width() + this->cardspacing) / (this->itemwidth + this->cardspacing);
}

void KylinScrollArea::add_card(AutoGroup *card)
{
    int x = int(cardcount % number_per_row) * (itemwidth + cardspacing);
    int y = int(cardcount / number_per_row) * (itemheight + cardspacing);

    int nowHeight = y + itemheight;
    if(nowHeight >= cardPanel->height())
        cardPanel->resize(cardPanel->width(), nowHeight);

    card->move(x, y);
    cardcount = cardcount + 1;
}
