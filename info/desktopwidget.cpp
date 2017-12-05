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
    this->setStyleSheet("QWidget{border: none;background-color: #ffffff;}");
    dataOK = false;
    page = NULL;
    setFixedSize(750, 403);
    scroll_widget = new ScrollWidget(this);
    scroll_widget->setGeometry(0, 0, 750, 403);
}

DesktopWidget::~DesktopWidget()
{
    this->clear_page_list();
    if (scroll_widget != NULL) {
        delete scroll_widget;
        scroll_widget = NULL;
    }
}

void DesktopWidget::clear_page_list()
{
    if (page != NULL) {
        delete page;
        page = NULL;
    }
    if (scroll_widget)
        scroll_widget->resetWidget();
}

bool DesktopWidget::displaySwitch()
{
    QMap<QString, QVariant> tmpMap = sessionProxy->get_system_message_qt();
//    if (tmpMap.isEmpty() || tmpMap.count() <= 0)
//    {
//        return false;
//    }
//    else
//    {
//        QMap<QString,QVariant>::iterator it;
//        for ( it = tmpMap.begin(); it != tmpMap.end(); ++it ) {
//            if (it.value().toString().length() > 0) {
//                desktop_info_map.insert(it.key(), it.value());
//            }
//        }
//        return true;
//    }
    QMap<QString,QVariant>::iterator it;
    bool sflag = false;
    for ( it = tmpMap.begin(); it != tmpMap.end(); ++it )
    {
        if (it.value().toString().length() > 0)
        {
            desktop_info_map.insert(it.key(), it.value());
            sflag = true;
        }
    }
    if (sflag)
        return true;
    else
        return false;
}

bool DesktopWidget::getStatus()
{
    return this->dataOK;
}


void DesktopWidget::initData()
{
    this->clear_page_list();

    page = new ComputerPage(scroll_widget->zone, tr("Desktop Info"));
    page->setMap(desktop_info_map, "");
    page->initUI(false);
    scroll_widget->addScrollWidget(page);
    /*QMap<QString,QVariant>::iterator it;
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
    }*/
//    dataOK = true;
}
