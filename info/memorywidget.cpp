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
    this->setStyleSheet("QWidget{border: none;background-color: #ffffff;}");
    setFixedSize(750, 403);
    scroll_widget = new ScrollWidget(this);
    scroll_widget->setGeometry(0, 0, 750, 403);
    dataOK = false;
}

MemoryWidget::~MemoryWidget()
{
    this->clear_page_list();
    if (scroll_widget != NULL) {
        delete scroll_widget;
        scroll_widget = NULL;
    }
}

void MemoryWidget::clear_page_list()
{
    for(int i=0; i<page_list.count(); i++)
    {
        ComputerPage *page = page_list.at(i);
        delete page;
        page = NULL;
    }
    page_list.clear();
    if (scroll_widget)
        scroll_widget->resetWidget();
}

bool MemoryWidget::displaySwitch()
{
    memory_info_map.clear();
    memory_info_map = systemproxy->get_memory_info_qt();
    if (memory_info_map.isEmpty() || memory_info_map.count() <= 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool MemoryWidget::getStatus()
{
    return this->dataOK;
}

void MemoryWidget::initData()
{
    this->clear_page_list();
    memory_info_map = systemproxy->get_memory_info_qt();//？硬盘，显卡，声卡，内存界面需要重新调用?为何其他界面不需要重新调用
    QMap<QString, QVariant>::iterator iter = memory_info_map.find("Memnum");
    int memoryNum = 0;
    if (iter == memory_info_map.end()) {
        memoryNum = 0;
    }
    else{
        memoryNum = iter.value().toInt();
    }
    if(memoryNum == 0) {
    }
    else {
        if(memoryNum == 1) {
            ComputerPage *page = new ComputerPage(scroll_widget->zone, tr("Memory Info"));
            page_list.append(page);
            memory_info_map.remove("Memnum");
            QMap<QString, QVariant> tmpMap;
            QMap<QString,QVariant>::iterator it;
            for ( it = memory_info_map.begin(); it != memory_info_map.end(); ++it ) {
                if (it.value().toString().length() > 0) {
                    tmpMap.insert(it.key(), it.value());
                }
            }
            page->setMap(tmpMap, "UBUNTUKYLIN");
            page->initUI(false);
            scroll_widget->addScrollWidget(page);
        }
        else if(memoryNum > 1) {
            for(int i=0;i<memoryNum;i++) {
                ComputerPage *page = new ComputerPage(scroll_widget->zone, tr("Memory Info %1").arg(i+1));
                page_list.append(page);
                tmp_info_map.clear();
                QMap<QString, QVariant>::iterator itbegin = memory_info_map.begin();
                QMap<QString, QVariant>::iterator  itend = memory_info_map.end();
                for (;itbegin != itend; ++itbegin) {
                    if(itbegin.key() != "Memnum" && itbegin.value().toString().contains("<1_1>")) {
                        QString result = itbegin.value().toString().split("<1_1>").at(i);
                        if (result.length() > 0) {
                            tmp_info_map.insert(itbegin.key(), result);
                        }
                    }
                }
                page->setMap(tmp_info_map, tmp_info_map.value("MemVendor").toString().toUpper());
                page->initUI(false);
                scroll_widget->addScrollWidget(page);
            }
        }
    }

    /*QMap<QString, QVariant>::iterator iter = memory_info_map.find("Memnum");
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
            page->setMap(tmpMap, "UBUNTUKYLIN");
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
                    if(itbegin.key() != "Memnum" && itbegin.value().toString().contains("<1_1>")) {
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
    }*/
//    dataOK = true;
}
