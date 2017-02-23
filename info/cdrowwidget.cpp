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

#include "cdrowwidget.h"
#include "computerpage.h"

CDRowWidget::CDRowWidget(QWidget *parent, SystemDispatcher *proxy) :
    QWidget(parent),
    systemproxy(proxy)
{
    this->setStyleSheet("QWidget{border: none;background-color: #ffffff;}");
    setFixedSize(750, 403);
    scroll_widget = new ScrollWidget(this);
    scroll_widget->setGeometry(0, 0, 750, 403);
    dataOK = false;
}

bool CDRowWidget::getStatus()
{
    return this->dataOK;
}

void CDRowWidget::initData()
{
    cdrom_info_map.clear();
    cdrom_info_map = systemproxy->get_cdrom_info_qt();
    int cdNum = 0;
    if (cdrom_info_map.isEmpty() || cdrom_info_map.count() <= 0) {
        cdNum = 0;
    }
    else {
        QMap<QString, QVariant>::iterator iter = cdrom_info_map.find("Dvdnum");
        if (iter == cdrom_info_map.end()) {
            cdNum = 0;
        }
        else {
            cdNum = iter.value().toInt();
            if(cdNum == 1)
            {
                ComputerPage *page = new ComputerPage(scroll_widget->zone, tr("CDROM Info"));
                cdrom_info_map.remove("Dvdnum");
                QMap<QString, QVariant> tmpMap;
                QMap<QString,QVariant>::iterator it;
                for ( it = cdrom_info_map.begin(); it != cdrom_info_map.end(); ++it ) {
                    if (it.value().toString().length() > 0) {
                        tmpMap.insert(it.key(), it.value());
                    }
                }
                page->setMap(tmpMap, cdrom_info_map.value("DvdVendor").toString().toUpper());
                page->initUI();
                scroll_widget->addScrollWidget(page);
            }
            else if(cdNum > 1)
            {
                for(int i=0;i<cdNum;i++)
                {
                    ComputerPage *page = new ComputerPage(scroll_widget->zone, tr("CDROM Info %1").arg(i+1));
                    tmp_info_map.clear();
                    QMap<QString, QVariant>::iterator itbegin = cdrom_info_map.begin();
                    QMap<QString, QVariant>::iterator  itend = cdrom_info_map.end();
                    for (;itbegin != itend; ++itbegin)
                    {
                        if(itbegin.key() != "Dvdnum" && itbegin.value().toString().contains("<1_1>")) {
                            QString result = itbegin.value().toString().split("<1_1>").at(i);
                            if (result.length() > 0) {
                                tmp_info_map.insert(itbegin.key(), result);
                            }
                        }
                    }
                    page->setMap(tmp_info_map, tmp_info_map.value("DvdVendor").toString().toUpper());
                    page->initUI();
                    scroll_widget->addScrollWidget(page);
                }
            }
        }
    }
    /*if(cdrom_info_map.count() == 1 && cdrom_info_map.contains("kylinkobe"))
    {
    }
    else {
        if(cdNum == 1)
        {
            ComputerPage *page = new ComputerPage(scroll_widget->zone, tr("CDROM Info"));
            cdrom_info_map.remove("Dvdnum");
            QMap<QString, QVariant> tmpMap;
            QMap<QString,QVariant>::iterator it;
            for ( it = cdrom_info_map.begin(); it != cdrom_info_map.end(); ++it ) {
                if (it.value().toString().length() > 0) {
                    tmpMap.insert(it.key(), it.value());
                }
            }
            page->setMap(tmpMap, cdrom_info_map.value("DvdVendor").toString().toUpper());
            page->initUI();
            scroll_widget->addScrollWidget(page);
        }
        else if(cdNum > 1)
        {
            for(int i=0;i<cdNum;i++)
            {
                ComputerPage *page = new ComputerPage(scroll_widget->zone, tr("CDROM Info %1").arg(i+1));
                tmp_info_map.clear();
                QMap<QString, QVariant>::iterator itbegin = cdrom_info_map.begin();
                QMap<QString, QVariant>::iterator  itend = cdrom_info_map.end();
                for (;itbegin != itend; ++itbegin)
                {
                    if(itbegin.key() != "Dvdnum" && itbegin.value().toString().contains("<1_1>")) {
                        QString result = itbegin.value().toString().split("<1_1>").at(i);
                        if (result.length() > 0) {
                            tmp_info_map.insert(itbegin.key(), result);
                        }
                    }
                }
                page->setMap(tmp_info_map, tmp_info_map.value("DvdVendor").toString().toUpper());
                page->initUI();
                scroll_widget->addScrollWidget(page);
            }
        }
    }*/
    dataOK = true;
}
