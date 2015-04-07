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

#include "systemwidget.h"
#include <QScrollBar>
#include <QPushButton>

#include <QMap>

SystemWidget::SystemWidget(QWidget *parent, SystemDispatcher *proxy) :
    QWidget(parent),
    systemproxy(proxy)
{
    this->setStyleSheet("QWidget{border: none}");
    setFixedSize(750, 403);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimeValue()));
    scroll_widget = new ScrollWidget(this);
    scroll_widget->setGeometry(0, 0, 750, 403);
    this->initData();
    if(sys_info_map.count() == 1 && sys_info_map.contains("kylinkobe"))
    {
        page = NULL;
    }
    else {
        page = new ComputerPage(scroll_widget->zone, tr("Computer Base Info"));
        page->setMap(sys_info_map, sys_info_map.value("ComVendor").toString().toUpper());
        page->initUI();
        scroll_widget->addScrollWidget(page);
        timer->start(1000*4);
    }
}

SystemWidget::~SystemWidget()
{
    disconnect(timer,SIGNAL(timeout()),this,SLOT(updateTimeValue()));
    if(timer->isActive()) {
        timer->stop();
    }
    if (timer != NULL) {
        delete timer;
        timer = NULL;
    }
}

void SystemWidget::updateTimeValue()
{
    QString result;
    int time_value = systemproxy->get_time_value_qt().toInt();
    int hour_value = time_value/60;
    int minutes_value =time_value%60;
    if(hour_value < 1)
    {
        result = QString::number(minutes_value) + tr(" Minutes");//分钟
    }
    else
    {
        result = QString::number(hour_value) + tr(" Hours ") + QString::number(minutes_value) + tr(" Minutes");//小时 分钟
    }
    page->resetTimeValue(result);
}

void SystemWidget::initData()
{
    QMap<QString, QVariant> tmpMap = systemproxy->get_computer_info_qt();
    QMap<QString,QVariant>::iterator it;
    for ( it = tmpMap.begin(); it != tmpMap.end(); ++it ) {
        if (it.value().toString().length() > 0) {
            sys_info_map.insert(it.key(), it.value());
        }
    }
}
