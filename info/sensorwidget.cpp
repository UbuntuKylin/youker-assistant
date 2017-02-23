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

#include "sensorwidget.h"
#include "computerpage.h"

SensorWieget::SensorWieget(QWidget *parent, SystemDispatcher *proxy) :
    QWidget(parent),
    systemproxy(proxy)
{
    this->setStyleSheet("QWidget{border: none;background-color: #ffffff;}");
    setFixedSize(750, 403);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimeValue()));
    scroll_widget = new ScrollWidget(this);
    scroll_widget->setGeometry(0, 0, 750, 403);
    this->initData();
}

SensorWieget::~SensorWieget()
{
    if (timer != NULL) {
        disconnect(timer,SIGNAL(timeout()),this,SLOT(updateTimeValue()));
        if(timer->isActive()) {
            timer->stop();
        }
        delete timer;
        timer = NULL;
    }
}

void SensorWieget::updateTimeValue()
{
    QMap<QString, QVariant> tmpMap = systemproxy->get_sensor_info_qt();
    if (tmpMap.isEmpty() || tmpMap.count() <= 0) {

    }
    else {
        sensor_info_map.clear();
        QMap<QString,QVariant>::iterator it;
        for (it = tmpMap.begin(); it != tmpMap.end(); ++it) {
            if (it.value().toString().length() > 0) {
                sensor_info_map.insert(it.key(), it.value());
            }
        }
        if (!sensor_info_map.isEmpty() && sensor_info_map.count() > 0) {
            page->resetSensor(sensor_info_map);
        }
    }
}

void SensorWieget::initData()
{
    QMap<QString, QVariant> tmpMap = systemproxy->get_sensor_info_qt();
    if (tmpMap.isEmpty() || tmpMap.count() <= 0) {
        page = NULL;
    }
    else {
        QMap<QString,QVariant>::iterator it;
        for ( it = tmpMap.begin(); it != tmpMap.end(); ++it ) {
            if (it.value().toString().length() > 0) {
                sensor_info_map.insert(it.key(), it.value());
            }
        }
        if (sensor_info_map.isEmpty() || sensor_info_map.count() <= 0) {
            page = NULL;
        }
        else {
            page = new ComputerPage(scroll_widget->zone, tr("Hardware sensor information"));
            page->setMap(sensor_info_map, "");
            page->setsensor(true);
            page->initUI();
            scroll_widget->addScrollWidget(page);
            timer->start(1000*4);
        }
    }
    /*QMap<QString,QVariant>::iterator it;
    for ( it = tmpMap.begin(); it != tmpMap.end(); ++it ) {
        if (it.value().toString().length() > 0) {
            sensor_info_map.insert(it.key(), it.value());
        }
    }
    if(sensor_info_map.count() == 0)
    {
        page = NULL;
    }
    else {
        page = new ComputerPage(scroll_widget->zone, tr("Hardware sensor information"));
        page->setMap(sensor_info_map, "");
        page->setsensor(true);
        page->initUI();
        scroll_widget->addScrollWidget(page);
        timer->start(1000*4);
    }*/
}
