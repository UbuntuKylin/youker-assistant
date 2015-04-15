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

#include "hdwidget.h"
#include "computerpage.h"

HDWidget::HDWidget(QWidget *parent, SystemDispatcher *proxy) :
    QWidget(parent),
    systemproxy(proxy)
{
//    this->setStyleSheet("QWidget{border: none}");
    this->setStyleSheet("QWidget{background-color: #ffffff}");
    setFixedSize(750, 403);
    scroll_widget = new ScrollWidget(this);
    scroll_widget->setGeometry(0, 0, 750, 403);
    dataOK = false;
//    diskNum = this->initData();
}

bool HDWidget::getStatus()
{
    return this->dataOK;
}

void HDWidget::initData()
{
    hd_info_map.clear();
    hd_info_map = systemproxy->get_harddisk_info_qt();
    QMap<QString, QVariant>::iterator iter = hd_info_map.find("DiskNum");
    int diskNum = 0;
    if (iter == hd_info_map.end())
    {
        diskNum = 0;
    }
    else{
        diskNum = iter.value().toInt();
    }
    if(hd_info_map.count() == 1 && hd_info_map.contains("kylinkobe"))
    {
    }
    else {
        if(diskNum == 1)
        {
            ComputerPage *page = new ComputerPage(scroll_widget->zone, tr("HardWare Info"));
            hd_info_map.remove("DiskNum");
            QMap<QString, QVariant> tmpMap;
            QMap<QString,QVariant>::iterator it;
            for ( it = hd_info_map.begin(); it != hd_info_map.end(); ++it ) {
                if (it.value().toString().length() > 0) {
                    tmpMap.insert(it.key(), it.value());
                }
            }
            page->setMap(tmpMap, hd_info_map.value("DiskVendor").toString().toUpper());
            page->initUI();
            scroll_widget->addScrollWidget(page);
        }
        else if(diskNum > 1)
        {
            for(int i=0;i<diskNum;i++)
            {
                ComputerPage *page = new ComputerPage(scroll_widget->zone, tr("HardWare Info %1").arg(i+1));
                tmp_info_map.clear();
                QMap<QString, QVariant>::iterator itbegin = hd_info_map.begin();
                QMap<QString, QVariant>::iterator  itend = hd_info_map.end();
                for (;itbegin != itend; ++itbegin)
                {
                    if(itbegin.key() != "DiskNum") {
                        QString result = itbegin.value().toString().split("<1_1>").at(i);
                        if (result.length() > 0) {
                            tmp_info_map.insert(itbegin.key(), result);
                        }
                    }
                }
                page->setMap(tmp_info_map, tmp_info_map.value("DiskVendor").toString().toUpper());
                page->initUI();
                scroll_widget->addScrollWidget(page);
            }
        }
    }
    dataOK = true;
}
