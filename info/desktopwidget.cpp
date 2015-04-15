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

#include "desktopwidget.h"

DesktopWidget::DesktopWidget(QWidget *parent, SessionDispatcher *proxy) :
    QWidget(parent),
    sessionProxy(proxy)
{
//    this->setStyleSheet("QWidget{border: none}");
    this->setStyleSheet("QWidget{background-color: #ffffff}");
    dataOK = false;
    setFixedSize(750, 403);
    scroll_widget = new ScrollWidget(this);
    scroll_widget->setGeometry(0, 0, 750, 403);
//    this->initData();
}

bool DesktopWidget::getStatus()
{
    return this->dataOK;
}

void DesktopWidget::initData()
{
    QMap<QString, QVariant> tmpMap = sessionProxy->get_system_message_qt();
    QMap<QString,QVariant>::iterator it;
    for ( it = tmpMap.begin(); it != tmpMap.end(); ++it ) {
        if (it.value().toString().length() > 0) {
            desktop_info_map.insert(it.key(), it.value());
        }
    }
    if(desktop_info_map.count() == 1 && desktop_info_map.contains("kylinkobe"))
    {
        page = NULL;
    }
    else {
        page = new ComputerPage(scroll_widget->zone, tr("Desktop Info"));
        page->setMap(desktop_info_map, "UBUNTUKYLIN");
        page->initUI();
        scroll_widget->addScrollWidget(page);
    }
    dataOK = true;
}
