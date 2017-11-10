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

#include "monitorwidget.h"
#include "computerpage.h"

MonitorWidget::MonitorWidget(QWidget *parent, SystemDispatcher *proxy) :
    QWidget(parent),
    systemproxy(proxy)
{
    this->setStyleSheet("QWidget{border: none;background-color: #ffffff;}");
    setFixedSize(750, 403);
    scroll_widget = new ScrollWidget(this);
    scroll_widget->setGeometry(0, 0, 750, 403);
    dataOK = false;
}

MonitorWidget::~MonitorWidget()
{
    this->clear_page_list();
    if (scroll_widget != NULL) {
        delete scroll_widget;
        scroll_widget = NULL;
    }
}

void MonitorWidget::clear_page_list()
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

bool MonitorWidget::displaySwitch()
{
    monitor_info_map.clear();
    monitor_info_map = systemproxy->get_monitor_info_qt();
    if (monitor_info_map.isEmpty() || monitor_info_map.count() <= 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool MonitorWidget::getStatus()
{
    return this->dataOK;
}

void MonitorWidget::initData()
{
    this->clear_page_list();


    //0711
//    monitor_info_map.insert("Mon_chip", "Intel(R) HD Graphics 4400");
//    monitor_info_map.insert("Vga_Drive", "i915<1_1>nouveau");
//    monitor_info_map.insert("Vga_businfo", "pci@0000:00:02.0 <1_1>pci@0000:04:00.0");
//    monitor_info_map.insert("Vga_num", "2");
//    monitor_info_map.insert("Vga_product", "Intel Corporation Haswell-ULT Integrated Graphics Controller (rev 09) (prog-if 00 [VGA controller])<1_1>NVIDIA Corporation GF117M [GeForce 610M/710M/810M/820M / GT 620M/625M/630M/720M] (rev a1) (prog-if 00 [VGA controller]");
//    monitor_info_map.insert("Vga_vendor", "Intel<1_1>Nvidia");
    monitor_info_map = systemproxy->get_monitor_info_qt();//？硬盘，显卡，声卡，内存界面需要重新调用?为何其他界面不需要重新调用
    QMap<QString, QVariant>::iterator iter = monitor_info_map.find("Vga_num");
    int vgaNum = 0;
    if (iter == monitor_info_map.end()) {
        vgaNum = 0;
    }
    else {
        vgaNum = iter.value().toInt();
    }
    if(vgaNum == 0) {
    }
    else {
        if(vgaNum == 1) {
            ComputerPage *page = new ComputerPage(scroll_widget->zone, tr("Monitor Info"));
            page_list.append(page);
            monitor_info_map.remove("Vga_num");
            QMap<QString, QVariant> tmpMap;
            QMap<QString,QVariant>::iterator it;
            for ( it = monitor_info_map.begin(); it != monitor_info_map.end(); ++it ) {
                if (it.value().toString().length() > 0) {
                    tmpMap.insert(it.key(), it.value());
                }
            }
            page->setMap(tmpMap, monitor_info_map.value("Vga_vendor").toString().toUpper());
            page->initUI(false);
            scroll_widget->addScrollWidget(page);
        }
        else if(vgaNum > 1) {
            for(int i=0;i<vgaNum;i++) {
                ComputerPage *page = new ComputerPage(scroll_widget->zone, tr("Monitor Info %1").arg(i+1));
                page_list.append(page);
                tmp_info_map.clear();
                QMap<QString, QVariant>::iterator itbegin = monitor_info_map.begin();
                QMap<QString, QVariant>::iterator  itend = monitor_info_map.end();
                for (;itbegin != itend; ++itbegin) {
                    if(itbegin.key() != "Vga_num" && itbegin.value().toString().contains("<1_1>")) {
                        QString result = itbegin.value().toString().split("<1_1>").at(i);
                        if (result.length() > 0) {
                            tmp_info_map.insert(itbegin.key(), result);
                        }
                    }
                }
                page->setMap(tmp_info_map, tmp_info_map.value("Vga_vendor").toString().toUpper());
                page->initUI(false);
                scroll_widget->addScrollWidget(page);
            }
        }
    }

    /*QMap<QString, QVariant>::iterator iter = monitor_info_map.find("Vga_num");
    int vgaNum = 0;
    if (iter == monitor_info_map.end())
    {
        vgaNum = 0;
    }
    else{
        vgaNum = iter.value().toInt();
    }
    if(monitor_info_map.count() == 1 && monitor_info_map.contains("kylinkobe"))
    {
    }
    else {
        if(vgaNum == 1)
        {
            ComputerPage *page = new ComputerPage(scroll_widget->zone, tr("Monitor Info"));
            monitor_info_map.remove("Vga_num");
            QMap<QString, QVariant> tmpMap;
            QMap<QString,QVariant>::iterator it;
            for ( it = monitor_info_map.begin(); it != monitor_info_map.end(); ++it ) {
                if (it.value().toString().length() > 0) {
                    tmpMap.insert(it.key(), it.value());
                }
            }
            page->setMap(tmpMap, monitor_info_map.value("Vga_vendor").toString().toUpper());
            page->initUI();
            scroll_widget->addScrollWidget(page);
        }
        else if(vgaNum > 1)
        {
            for(int i=0;i<vgaNum;i++)
            {
                ComputerPage *page = new ComputerPage(scroll_widget->zone, tr("Monitor Info %1").arg(i+1));
                tmp_info_map.clear();
                QMap<QString, QVariant>::iterator itbegin = monitor_info_map.begin();
                QMap<QString, QVariant>::iterator  itend = monitor_info_map.end();
                for (;itbegin != itend; ++itbegin)
                {
                    if(itbegin.key() != "Vga_num" && itbegin.value().toString().contains("<1_1>")) {
                        QString result = itbegin.value().toString().split("<1_1>").at(i);
                        if (result.length() > 0) {
                            tmp_info_map.insert(itbegin.key(), result);
                        }
                    }
                }
                page->setMap(tmp_info_map, tmp_info_map.value("Vga_vendor").toString().toUpper());
                page->initUI();
                scroll_widget->addScrollWidget(page);
            }
        }
    }*/
//    dataOK = true;
}
