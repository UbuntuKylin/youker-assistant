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

#include "memorywidget.h"
#include "computerpage.h"
#include "../dbusproxy/youkersystemdbus.h"
#include <QDebug>

MemoryWidget::MemoryWidget(QWidget *parent, SystemDispatcher *proxy) :
    QWidget(parent),
    systemproxy(proxy)
{
//    this->setStyleSheet("QWidget{border: none}");
    this->setStyleSheet("QWidget{background-color: #ffffff}");
    setFixedSize(750, 403);
    scroll_widget = new ScrollWidget(this);
    scroll_widget->setGeometry(0, 0, 750, 403);
    dataOK = false;
//    memoryNum = this->initData();
}

bool MemoryWidget::getStatus()
{
    return this->dataOK;
}

void MemoryWidget::initData()
{
    memory_info_map.clear();
    memory_info_map = systemproxy->get_memory_info_qt();
    QMap<QString, QVariant>::iterator iter = memory_info_map.find("Memnum");
    int memoryNum = 0;
    if (iter == memory_info_map.end())
    {
        memoryNum = 0;
    }
    else{
        memoryNum = iter.value().toInt();
    }
    if(memory_info_map.count() == 1 && memory_info_map.contains("kylinkobe"))
    {
    }
    else {
        if(memoryNum == 1)
        {
            ComputerPage *page = new ComputerPage(scroll_widget->zone, tr("Memory Info"));
            memory_info_map.remove("Memnum");
            QMap<QString, QVariant> tmpMap;
            QMap<QString,QVariant>::iterator it;
            for ( it = memory_info_map.begin(); it != memory_info_map.end(); ++it ) {
                if (it.value().toString().length() > 0) {
                    tmpMap.insert(it.key(), it.value());
                }
            }
            page->setMap(tmpMap, "INTEL");
            page->initUI();
            scroll_widget->addScrollWidget(page);
        }
        else if(memoryNum > 1)
        {
            for(int i=0;i<memoryNum;i++)
            {
                ComputerPage *page = new ComputerPage(scroll_widget->zone, tr("Memory Info %1").arg(i+1));
                tmp_info_map.clear();
                QMap<QString, QVariant>::iterator itbegin = memory_info_map.begin();
                QMap<QString, QVariant>::iterator  itend = memory_info_map.end();
                for (;itbegin != itend; ++itbegin)
                {
                    if(itbegin.key() != "Memnum") {
                        QString result = itbegin.value().toString().split("<1_1>").at(i);
                        if (result.length() > 0) {
                            tmp_info_map.insert(itbegin.key(), result);
                        }
                    }
                }
                page->setMap(tmp_info_map, tmp_info_map.value("MemVendor").toString().toUpper());
                page->initUI();
                scroll_widget->addScrollWidget(page);
            }
        }
    }
    dataOK = true;
}
