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
    this->setStyleSheet("QWidget{border: none;background-color: #ffffff;}");
    setFixedSize(750, 403);
    scroll_widget = new ScrollWidget(this);
    scroll_widget->setGeometry(0, 0, 750, 403);
    dataOK = false;
}

bool HDWidget::getStatus()
{
    return this->dataOK;
}

void HDWidget::initData()
{
    hd_info_map.clear();
    hd_info_map = systemproxy->get_harddisk_info_qt();

    //0711
//    hd_info_map.insert("DiskCapacity", "465.8 GiB, 500107862016 bytes<1_1>14.9 GiB, 16013942784 bytes");
//    hd_info_map.insert("DiskFw", "0002LIM1<1_1>U21B001");
//    hd_info_map.insert("DiskName", "/dev/sda<1_1>/dev/sdb");
//    hd_info_map.insert("DiskNum", "2");
//    hd_info_map.insert("DiskProduct", "ST500LM021-1KJ152<1_1>SanDisk SSD U110 16GB");
//    hd_info_map.insert("DiskSerial", "W6227R7B<1_1>144116411501");
//    hd_info_map.insert("DiskVendor", "Seagate<1_1>Seagate");

    if (hd_info_map.isEmpty() || hd_info_map.count() <= 0) {

    }
    else {
        QMap<QString, QVariant>::iterator iter = hd_info_map.find("DiskNum");
        int diskNum = 0;
        if (iter == hd_info_map.end()) {
            diskNum = 0;
        }
        else{
            diskNum = iter.value().toInt();
        }
        if(diskNum == 0) {
        }
        else {
            if(diskNum == 1) {
                ComputerPage *page = new ComputerPage(scroll_widget->zone, tr("HardWare Info"));
                hd_info_map.remove("DiskNum");
                QMap<QString, QVariant> tmpMap;
                QMap<QString,QVariant>::iterator it;
                for ( it = hd_info_map.begin(); it != hd_info_map.end(); ++it ) {
                    if (it.value().toString().length() > 0) {
                        if (QString::compare(it.value().toString(), "$", Qt::CaseInsensitive) != 0)//20161228
                            tmpMap.insert(it.key(), it.value());
                    }
                }
                page->setMap(tmpMap, hd_info_map.value("DiskVendor").toString().toUpper());
                page->initUI();
                scroll_widget->addScrollWidget(page);
            }
            else if(diskNum > 1) {
                for(int i=0;i<diskNum;i++) {
                    ComputerPage *page = new ComputerPage(scroll_widget->zone, tr("HardWare Info %1").arg(i+1));
                    tmp_info_map.clear();
                    QMap<QString, QVariant>::iterator itbegin = hd_info_map.begin();
                    QMap<QString, QVariant>::iterator  itend = hd_info_map.end();
                    for (;itbegin != itend; ++itbegin) {
                        if(itbegin.key() != "DiskNum" && itbegin.value().toString().contains("<1_1>")) {
                            QString result = itbegin.value().toString().split("<1_1>").at(i);
                            if (result.length() > 0) {
                                if (QString::compare(result, "$", Qt::CaseInsensitive) != 0)//20161228
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
    }
    /*QMap<QString, QVariant>::iterator iter = hd_info_map.find("DiskNum");
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
                    if (QString::compare(it.value().toString(), "$", Qt::CaseInsensitive) != 0)//20161228
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
                    if(itbegin.key() != "DiskNum" && itbegin.value().toString().contains("<1_1>")) {
                        QString result = itbegin.value().toString().split("<1_1>").at(i);
                        if (result.length() > 0) {
                            if (QString::compare(result, "$", Qt::CaseInsensitive) != 0)//20161228
                                tmp_info_map.insert(itbegin.key(), result);
                        }
                    }
                }
                page->setMap(tmp_info_map, tmp_info_map.value("DiskVendor").toString().toUpper());
                page->initUI();
                scroll_widget->addScrollWidget(page);
            }
        }
    }*/
    dataOK = true;
}
