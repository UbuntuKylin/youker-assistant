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

#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>
#include <QDebug>
#include <QProcess>
#include <QMap>
#include <QFile>

class DeviceManager : public QObject
{
    Q_OBJECT
public:
    explicit DeviceManager(QObject *parent = 0);

    //得到硬件设备及其驱动信息
    Q_INVOKABLE QStringList getDeviceMsg();
    
signals:
    
public slots:
    
};

#endif // DEVICEMANAGER_H
