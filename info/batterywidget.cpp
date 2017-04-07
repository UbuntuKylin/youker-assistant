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

BatteryWidget::BatteryWidget(QWidget *parent, SessionDispatcher *proxy) :
    QWidget(parent),
    sessionproxy(proxy)
{
    this->setStyleSheet("QWidget{border: none;background-color: #ffffff;}");
    setFixedSize(750, 403);
    page = NULL;
    scroll_widget = new ScrollWidget(this);
    scroll_widget->setGeometry(0, 0, 750, 403);
    dataOK = false;
}

BatteryWidget::~BatteryWidget()
{
    this->clear_page_list();
    if (scroll_widget != NULL) {
        delete scroll_widget;
        scroll_widget = NULL;
    }
}

void BatteryWidget::clear_page_list()
{
    if (page != NULL) {
        delete page;
        page = NULL;
    }
    if (scroll_widget)
        scroll_widget->resetWidget();
}

bool BatteryWidget::getStatus()
{
    return this->dataOK;
}

void BatteryWidget::initData()
{
    this->clear_page_list();
    QMap<QString, QVariant> tmpMap = sessionproxy->read_battery_info_qt();
    if (tmpMap.isEmpty() || tmpMap.count() <= 0) {
        page = NULL;
    }
    else {
        QMap<QString,QVariant>::iterator it; //遍历map
        QStringList powerlist;
        powerlist << "POWER_SUPPLY_NAME" << "POWER_SUPPLY_MANUFACTURER" << "POWER_SUPPLY_MODEL_NAME" << "POWER_SUPPLY_TECHNOLOGY" << "POWER_SUPPLY_VOLTAGE_NOW" << "POWER_SUPPLY_ENERGY_FULL_DESIGN" << "POWER_SUPPLY_ENERGY_FULL" << "POWER_SUPPLY_ENERGY_NOW" << "POWER_SUPPLY_SERIAL_NUMBER";
        for ( it = tmpMap.begin(); it != tmpMap.end(); ++it ) {
            QList<QString>::Iterator itstart = powerlist.begin(), itend = powerlist.end();
            for(;itstart !=itend;itstart++)
            {
                if(*itstart == it.key())
                {
                    if (it.key() == "POWER_SUPPLY_SERIAL_NUMBER")
                    {
                        if (it.value().toString().replace(" " ,"").length() > 0)
                            battery_info_map.insert(it.key(), it.value());
                    }
                    else {
                        if (it.value().toString().length() > 0)
                            battery_info_map.insert(it.key(), it.value());
                    }
                    break;
                }
            }
        }
        if(battery_info_map.isEmpty() || battery_info_map.count() <= 0) {
            page = NULL;
        }
        else {
            page = new ComputerPage(scroll_widget->zone, tr("Battery Info"));
            page->setMap(battery_info_map, battery_info_map.value("POWER_SUPPLY_MANUFACTURER").toString().toUpper());
            page->initUI(false);
            scroll_widget->addScrollWidget(page);
        }
    }
    /*QMap<QString,QVariant>::iterator it; //遍历map
    QStringList powerlist;
    powerlist << "POWER_SUPPLY_NAME" << "POWER_SUPPLY_MANUFACTURER" << "POWER_SUPPLY_MODEL_NAME" << "POWER_SUPPLY_TECHNOLOGY" << "POWER_SUPPLY_VOLTAGE_NOW" << "POWER_SUPPLY_ENERGY_FULL_DESIGN" << "POWER_SUPPLY_ENERGY_FULL" << "POWER_SUPPLY_ENERGY_NOW" << "POWER_SUPPLY_SERIAL_NUMBER";
    for ( it = tmpMap.begin(); it != tmpMap.end(); ++it ) {
        QList<QString>::Iterator itstart = powerlist.begin(), itend = powerlist.end();
        for(;itstart !=itend;itstart++)
        {
            if(*itstart == it.key())
            {
                if (it.key() == "POWER_SUPPLY_SERIAL_NUMBER")
                {
                    if (it.value().toString().replace(" " ,"").length() > 0)
                        battery_info_map.insert(it.key(), it.value());
                }
                else {
                    if (it.value().toString().length() > 0)
                        battery_info_map.insert(it.key(), it.value());
                }
                break;
            }
        }
//        if(it.key() != "POWER_SUPPLY_CAPACITY" && it.key() != "POWER_SUPPLY_CYCLE_COUNT" && it.key() != "POWER_SUPPLY_POWER_NOW" && it.key() != "POWER_SUPPLY_PRESENT" && it.key() != "POWER_SUPPLY_STATUS" && it.key() != "POWER_SUPPLY_VOLTAGE_MIN_DESIGN" )
//        {
//            if (it.value().toString().length() > 0)
//                battery_info_map.insert(it.key(), it.value());
//        }
    }
    if(battery_info_map.count() == 1 && battery_info_map.contains("kylinkobe")) {
        page = NULL;
    }
    else {
        page = new ComputerPage(scroll_widget->zone, tr("Battery Info"));
        page->setMap(battery_info_map, battery_info_map.value("POWER_SUPPLY_MANUFACTURER").toString().toUpper());
        page->initUI();
        scroll_widget->addScrollWidget(page);
    }*/
//    dataOK = true;
}

