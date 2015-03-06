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

#include "batterywidget.h"
//#include <QDebug>

BatteryWidget::BatteryWidget(QWidget *parent, SessionDispatcher *proxy) :
    QWidget(parent),
    sessionproxy(proxy)
{
    setFixedSize(750, 403);

    scroll_widget = new ScrollWidget(this);
    scroll_widget->setGeometry(0, 0, 750, 403);
    this->initData();
    page = new ComputerPage(scroll_widget->zone, tr("Battery Info"));
    page->setMap(battery_info_map, battery_info_map.value("POWER_SUPPLY_MANUFACTURER").toString().toUpper());
    page->initUI();
    scroll_widget->addScrollWidget(page);
}

void BatteryWidget::initData()
{
    QMap<QString, QVariant> tmpMap = sessionproxy->read_battery_info_qt();
    QMap<QString,QVariant>::iterator it; //遍历map
    for ( it = tmpMap.begin(); it != tmpMap.end(); ++it ) {
        if(it.key() != "POWER_SUPPLY_CAPACITY" && it.key() != "POWER_SUPPLY_CYCLE_COUNT" && it.key() != "POWER_SUPPLY_POWER_NOW" && it.key() != "POWER_SUPPLY_PRESENT" && it.key() != "POWER_SUPPLY_STATUS" && it.key() != "POWER_SUPPLY_VOLTAGE_MIN_DESIGN" )
        {
            battery_info_map.insert(it.key(), it.value());
        }
    }
}

