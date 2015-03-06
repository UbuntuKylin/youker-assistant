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
    setFixedSize(750, 403);
    scroll_widget = new ScrollWidget(this);
    scroll_widget->setGeometry(0, 0, 750, 403);

    diskNum = this->initData();

    if(diskNum == 1)
    {
        ComputerPage *page = new ComputerPage(scroll_widget->zone, tr("HardWare Info"));
        hd_info_map.remove("DiskNum");
        page->setMap(hd_info_map, hd_info_map.value("DiskVendor").toString().toUpper());
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
                if(itbegin.key() != "DiskNum")
                    tmp_info_map.insert(itbegin.key(), itbegin.value().toString().split("<1_1>").at(i));
            }
            page->setMap(tmp_info_map, tmp_info_map.value("DiskVendor").toString().toUpper());
            page->initUI();
            scroll_widget->addScrollWidget(page);
        }
    }



}

int HDWidget::initData()
{
    hd_info_map.clear();
    hd_info_map = systemproxy->get_harddisk_info_qt();
    QMap<QString, QVariant>::iterator iter = hd_info_map.find("DiskNum");
    if (iter == hd_info_map.end())
    {
        return 0;
    }
    else{
        return iter.value().toInt();
    }
}
