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

#include "boardwidget.h"

BoardWidget::BoardWidget(QWidget *parent, SystemDispatcher *proxy) :
    QWidget(parent),
    systemproxy(proxy)
{
    this->setStyleSheet("QWidget{border: none;background-color: #ffffff;}");
    setFixedSize(750, 403);
    scroll_widget = new ScrollWidget(this);
    scroll_widget->setGeometry(0, 0, 750, 403);
    dataOK = false;
}

bool BoardWidget::getStatus()
{
    return this->dataOK;
}

void BoardWidget::initData()
{
    QMap<QString, QVariant> tmpMap = systemproxy->get_board_info_qt();
    QMap<QString,QVariant>::iterator it;
    for ( it = tmpMap.begin(); it != tmpMap.end(); ++it ) {
        if (it.value().toString().length() > 0) {
            board_info_map.insert(it.key(), it.value());
        }
    }
    if(board_info_map.count() == 1 && board_info_map.contains("kylinkobe"))
    {
        page = NULL;
    }
    else {
        page = new ComputerPage(scroll_widget->zone, tr("Board Info"));
        page->setMap(board_info_map, board_info_map.value("BoaVendor").toString().toUpper());
        page->initUI();
        scroll_widget->addScrollWidget(page);
    }
    dataOK = true;
}
