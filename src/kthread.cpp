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

#include <QDebug>
#include "kthread.h"

//Thread::Thread(QString message, QObject *parent) :
//    stopped(false)
//  , QThread(parent)
//  , message(message)
//{
//}

//Thread *thread = new Thread(name, this);


KThread::KThread(QObject *parent):QThread(parent)
{

}

void KThread::initValues(QMap<QString, QVariant> data, QStringList &arglist, QDBusInterface *systemiface, QString method) {
    iface = systemiface;
    mapData = data;
    methodName = method;
    list = arglist;
}

KThread::~KThread() {
    stop();
}

void KThread::run() {
    //清理
    if(methodName == "onekey_clean_crufts_function") {
        iface->call("onekey_clean_crufts_function", list);
    }
    //扫描
    else if(methodName == "onekey_scan_function") {
        iface->call("onekey_scan_function", list);
    }
    else if(methodName == "get_scan_result") {
        iface->call("get_scan_result", mapData);
    }
    else if(methodName == "remove_select_items") {
        iface->call("remove_select_items", mapData);
    }
    else if(methodName == "call_camera") {
        iface->call("call_camera");
    }
    else if(methodName == "install") {
        iface->call("install", "kylin-assistant");
    }
    else if(methodName == "update") {
        iface->call("update");
    }
    else if(methodName == "start_check_source_useable") {
        iface->call("start_check_source_useable");
    }
    //sso
//    else if(methodName == "slot_do_login_account") {
//        iface->call("slot_do_login_account");
//    }
//    else if(methodName == "check_user") {
//       iface->call("check_user");
//    }
//    else if(methodName == "shredFile") {
//        QDBusReply<int> reply = iface->call("shredFile", fileFlag);
//        emit msgSignal(reply.value());
//    }
}
void KThread::stop() {
    wait();
}
