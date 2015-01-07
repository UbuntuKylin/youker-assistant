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

#include "clounddispatcher.h"
#include "warningdialog.h"

CloundDispatcher::CloundDispatcher(QObject *parent) :
    QObject(parent)
{
    cloundiface = new QDBusInterface("com.ubuntukylin.session",
                               "/",
                               "com.ubuntukylin.session",
                               QDBusConnection::sessionBus());
    QObject::connect(cloundiface, SIGNAL(access_weather(QString, QString)), this, SLOT(accord_flag_ip(QString, QString)));
}

CloundDispatcher::~CloundDispatcher() {
    this->exit_qt();
    if (cloundiface != NULL) {
        delete cloundiface;
    }
}

//dbus服务退出
void CloundDispatcher::exit_qt() {
    cloundiface->call("exit");
}

void CloundDispatcher::get_ip_address_qt() {
    //then get ip
    cloundiface->call("get_ip_address");
}

QString CloundDispatcher::show_ip_address_qt() {
    QDBusReply<QString> reply = cloundiface->call("show_ip_address");
    return reply.value();
}

void CloundDispatcher::accord_flag_ip(QString key, QString value) {
    if(key == "ip_addr" && value == "kobe") {
        QString ip_addr = this->show_ip_address_qt();
        emit startShowIPAddress(ip_addr);
    }
}
