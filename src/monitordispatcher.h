/*
 * Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd.
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
#ifndef MONITORDISPATCHER_H
#define MONITORDISPATCHER_H

#include <QObject>
#include <QtDBus>
#include <QDBusInterface>
#include <QDBusConnection>

class MonitorDispatcher : public QObject
{
    Q_OBJECT
public:
    explicit MonitorDispatcher(QObject *parent = 0);
    ~MonitorDispatcher();
    QDBusInterface *monitoriface;
    //退出sessiondubs服务
    Q_INVOKABLE void exit_qt();
    Q_INVOKABLE double get_cpu_percent_qt();
    Q_INVOKABLE QString get_total_memory_qt();
    Q_INVOKABLE QString get_used_memory_qt();
    Q_INVOKABLE QString get_free_memory_qt();
    Q_INVOKABLE QStringList get_network_flow_total_qt();
};

#endif // MONITORDISPATCHER_H
