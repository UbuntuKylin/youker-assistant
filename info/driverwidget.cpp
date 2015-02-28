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

#include "driverwidget.h"
#include "devicemanager.h"
#include <QDebug>

DriverWidget::DriverWidget(QWidget *parent/*, SystemDispatcher *proxy*/) :
    QWidget(parent)
//    systemproxy(proxy)
{
    setFixedSize(750, 403);
    scroll_widget = new ScrollWidget(this);
    scroll_widget->setGeometry(0, 0, 750, 403);
    this->initData();
    page = new ComputerPage(scroll_widget->zone, tr("Driver Info"));
    page->setMap(driver_info_map,"");
    page->initUI();
    scroll_widget->addScrollWidget(page);
}

void DriverWidget::initData()
{
    DeviceManager manager;
    QStringList list = manager.getDeviceMsg();
    for (int i=0 ; i < list.length() ; i++) {
        QStringList splitlist = list.at(i).split(";");
        if(splitlist.length() == 1) {
            QStringList name = splitlist.at(0).split(":");
            driver_info_map.insert(name.at(0).trimmed(), name.at(1));
//            driver_info_map.insert("deviceName", name.at(0));
//            driver_info_map.insert("deviceNameText", name.at(1));
        }
        else if(splitlist.length() == 2) {
            QStringList name1 = splitlist.at(0).split(":");
            QStringList name2 = splitlist.at(1).split(":");
            driver_info_map.insert(name1.at(0).trimmed(), name1.at(1));
            driver_info_map.insert(name2.at(0).trimmed(), name2.at(1));
//            driver_info_map.insert("deviceName", name1.at(0));
//            driver_info_map.insert("deviceNameText", name1.at(1));
//            driver_info_map.insert("inUseName", name2.at(0));
//            driver_info_map.insert("inUseNameText", name2.at(1));
        }
        else if(splitlist.length() == 3) {
            QStringList name3 = splitlist[0].split(":");
            QStringList name4 = splitlist[1].split(":");
            QStringList name5 = splitlist[2].split(":");
            driver_info_map.insert(name3.at(0).trimmed(), name3.at(1));
            driver_info_map.insert(name4.at(0).trimmed(), name4.at(1));
            driver_info_map.insert(name5.at(0).trimmed(), name5.at(1));
//            driver_info_map.insert("deviceName", name3.at(0));
//            driver_info_map.insert("deviceNameText", name3.at(1));
//            driver_info_map.insert("inUseName", name4.at(0));
//            driver_info_map.insert("inUseNameText", name4.at(1));
//            driver_info_map.insert("existName", name5.at(0));
//            driver_info_map.insert("existNameText", name5.at(1));
        }
    }
}
