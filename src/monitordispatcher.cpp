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

#include "monitordispatcher.h"

MonitorDispatcher::MonitorDispatcher(QObject *parent) :
    QObject(parent)
{

    monitoriface = new QDBusInterface("com.ubuntukylin.session",
                               "/",
                               "com.ubuntukylin.session",
                               QDBusConnection::sessionBus());
}

MonitorDispatcher::~MonitorDispatcher() {
    this->exit_qt();
    if (monitoriface != NULL) {
        delete monitoriface;
    }
}

//dbus服务退出
void MonitorDispatcher::exit_qt() {
    monitoriface->call("exit");
}

//-----------------------monitorball------------------------
double MonitorDispatcher::get_cpu_percent_qt() {
    QDBusReply<double> reply = monitoriface->call("get_cpu_percent");
    return reply.value();
}

QString MonitorDispatcher::get_total_memory_qt() {
    QDBusReply<QString> reply = monitoriface->call("get_total_memory");
    return reply.value();
}

QString MonitorDispatcher::get_used_memory_qt() {
    QDBusReply<QString> reply = monitoriface->call("get_used_memory");
    return reply.value();
}

QString MonitorDispatcher::get_free_memory_qt() {
    QDBusReply<QString> reply = monitoriface->call("get_free_memory");
    return reply.value();
}

QStringList MonitorDispatcher::get_network_flow_total_qt() {
    QDBusReply<QStringList> reply = monitoriface->call("get_network_flow_total");
    return reply.value();
}
