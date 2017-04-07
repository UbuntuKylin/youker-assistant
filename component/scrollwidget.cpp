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

#include "scrollwidget.h"
#include "../info/computerpage.h"
#include <QDebug>
#include "../component/utils.h"

ScrollWidget::ScrollWidget(QWidget *parent) :
    QWidget(parent)
{
//    this->setStyleSheet("QWidget{border: none;background-color: #ffffff;}");
    this->setWindowFlags(Qt::FramelessWindowHint);
    widget_count = 0;
    zone_height = 403;
    scroll_area = new QScrollArea();
    zone = new QWidget();

    //set white background color
    zone->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    zone->setPalette(palette);

    scroll_area->setGeometry(-1, -1, 750+2, 403);
    zone->setGeometry(0,0,750,403);
    zone->setWindowFlags(Qt::FramelessWindowHint);
    scroll_area->setWidget(zone);
    scroll_area->horizontalScrollBar()->hide();
//    scroll_area->setBackgroundRole(QPalette::Dark);
    scroll_area->setAlignment(Qt::AlignLeft);
    scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

   QVBoxLayout *v_layout = new QVBoxLayout();
   v_layout->addWidget(scroll_area);
   v_layout->setSpacing(0);//设置间隔
   v_layout->setMargin(0);//设置总的外围边框
//   v_layout->setContentsMargins(5, 5, 5, 5);

   setLayout(v_layout);
}

ScrollWidget::~ScrollWidget() {
    if(zone != NULL) {
        delete zone;
        zone = NULL;
    }
    if(scroll_area != NULL) {
        delete scroll_area;
        scroll_area = NULL;
    }
}

void ScrollWidget::addScrollWidget(ComputerPage *widget)
{
    if (widget_count == 0) {
        widget->move(0,0);
//        if(widget->page_height > zone->height()) {
//            zone_height = widget->page_height;
//            this->zone->resize(750, zone_height);
//        }
//        else {
//            this->zone->resize(750, 403-3);
//        }
        zone_height = widget->page_height;
        this->zone->resize(750, zone_height);
    }
    else {
        int y = zone_height/* + PAGESPACE*/;
        zone_height += widget->page_height/* + PAGESPACE*/;
        if(zone_height > zone->height()) {
            this->zone->resize(750, zone_height);
        }
        widget->move(0, y);
    }
    widget_count ++;
}

void ScrollWidget::resetWidget()
{
    widget_count = 0;
    zone_height = 403;
}
