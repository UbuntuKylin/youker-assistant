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

#ifndef SENSORWIDGET_H
#define SENSORWIDGET_H

#include <QWidget>
#include "../component/scrollwidget.h"
#include <QMap>
#include <QVariant>
#include <QTimer>

class SystemDispatcher;

class SensorWieget : public QWidget
{
    Q_OBJECT
public:
    explicit SensorWieget(QWidget *parent = 0, SystemDispatcher *proxy = 0);
    ~SensorWieget();
    void initData();

signals:

public slots:
    void updateTimeValue();

private:
    ScrollWidget *scroll_widget;
    QMap<QString, QVariant> sensor_info_map;
    ComputerPage *page;
    SystemDispatcher *systemproxy;
    QTimer *timer;
};

#endif // SENSORWIDGET_H
