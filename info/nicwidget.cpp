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

#include "nicwidget.h"

NicWidget::NicWidget(QWidget *parent, SystemDispatcher *proxy) :
    QWidget(parent),
    systemproxy(proxy)
{
    setFixedSize(750, 403);
    scroll_widget = new ScrollWidget(this);
    scroll_widget->setGeometry(0, 0, 750, 403);
    this->initData();
    if(wireless_info_map.count() == 0)
    {
        page = NULL;
    }
    else {
        page = new ComputerPage(scroll_widget->zone, tr("NIC Info"));
        page->setMap(wire_info_map, wire_info_map.value("NetVendor").toString().toUpper());
        page->initUI();
        scroll_widget->addScrollWidget(page);
    }
    if(wireless_info_map.count() == 0)
    {
        page2 = NULL;
    }
    else {
        page2 = new ComputerPage(scroll_widget->zone, tr("WireLess NIC Info"));
        page2->setMap(wireless_info_map, wireless_info_map.value("WlanVendor").toString().toUpper());
        page2->initUI();
        scroll_widget->addScrollWidget(page2);
    }
}

void NicWidget::initData()
{
    QMap<QString, QVariant> tmpMap = systemproxy->get_networkcard_info_qt();
    QMap<QString,QVariant>::iterator it; //遍历map
    for ( it = tmpMap.begin(); it != tmpMap.end(); ++it ) {
        if(it.key().startsWith("Wlan"))
        {
            wireless_info_map.insert(it.key(), it.value());
        }
        else
        {
            wire_info_map.insert(it.key(), it.value());
        }
    }
}
