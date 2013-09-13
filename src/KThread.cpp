/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
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
#include <QDebug>
#include "KThread.h"

KThread::KThread(QDBusInterface *systemiface, QString method, QStringList arglist, QString flag):QThread()
{
    iface = systemiface;
    method_name = method;
    list = arglist;
    file_flag = flag;
}

KThread::~KThread()
{
    stop();
}
void KThread::run()
{
    if(method_name == "get_network_flow") {
        iface->call("get_network_flow");
    }
    else if(method_name == "clean_by_main_one_key") {
//        qDebug() << KThread::currentThreadId();
        iface->call("clean_by_main_one_key", list);
//        QThread::sleep(10);
    }
    else if(method_name == "clean_by_second_one_key") {
        iface->call("clean_by_second_one_key", list);
    }
    else if(method_name == "clean_history_records") {
        qDebug() << "11111111";
//        qDebug() << list;
        iface->call("clean_history_records");
    }
    else if(method_name == "clean_system_history") {
        qDebug() << "2222222222";
        iface->call("clean_system_history");
    }
    else if(method_name == "clean_cookies_records") {
        iface->call("clean_cookies_records", list);
    }
    else if(method_name == "clean_package_cruft") {
        iface->call("clean_package_cruft", list);
    }
    else if(method_name == "clean_file_cruft") {
        iface->call("clean_file_cruft", list, file_flag);
    }
    else if(method_name == "install_pkg") {
        iface->call("install_pkg", file_flag);
    }
    else if(method_name == "uninstall_pkg") {
        iface->call("uninstall_pkg", file_flag);
    }
    else if(method_name == "update_pkg") {
        iface->call("update_pkg", file_flag);
    }
    else if(method_name == "apt_get_update") {
        iface->call("apt_get_update");
    }
}
void KThread::stop()
{
    wait();
}
