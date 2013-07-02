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


#include "dispatcher.h"
#include <QDebug>
#include <QVariant>
#include <QProcessEnvironment>
#include <QtDBus>
#include <QObject>
#include <QString>

DispatcherQml::DispatcherQml(QObject *parent) :
    QObject(parent)
{
    iface = new QDBusInterface("com.ubuntukylin.Ihu",
                               "/",
                               "com.ubuntukylin.Ihu",
                               QDBusConnection::systemBus());
//                               QDBusConnection::sessionBus());

    iface1 = new QDBusInterface("com.ubuntukylin.IhuSession",
                               "/",
                               "com.ubuntukylin.IhuSession",
                               QDBusConnection::sessionBus());
//    QObject::connect(iface,SIGNAL(clear_rubbish(QString)),this,SLOT(show_progress_clear_rubbish(QString)));
    //呼叫远程的pc_message，参数为num
    //QDBusReply<int> reply = iface.call("pc_message", num);
    QDBusReply<QMap<QString, QVariant> > reply = iface->call("pc_message");

    notify_str = "";
    if (reply.isValid()) {
        QMap<QString, QVariant> value = reply.value();
        myinfo = value;
        qDebug() << myinfo;
    }
    else {
        qDebug() << "get pc_message failed!";
    }


    QDBusReply<QStringList> reply1 = iface1->call("get_sys_themes");
    if (reply1.isValid()) {
        QStringList value1 = reply1.value();
//        myinfo = value;
        qDebug() << value1;
    }
    else {
        qDebug() << "get thems msg failed!";
    }


}

QString DispatcherQml::get_value(QString key)
{
    QVariant tt = myinfo.value(key);
    return tt.toString();
//    return "aa";
}

int DispatcherQml::get_add_value()
{
    QDBusReply<int> reply = iface->call("test_add", 3, 4);
    int tt = reply.value();
    return tt;
}

QString DispatcherQml::show_progress_clear_rubbish(QString str)
{
    qDebug() << str;
    emit myStringChanged("Kobe test for fastclear button and dbus communication");
    return str;
}

void DispatcherQml::send_btn_msg(QString str)
{
    QDBusReply<void> reply = iface->call("test_fastclear", str);
}

//QString DispatcherQml::getMyString()
//{
//    m_string="Called from the Q_INVOKABLE function";
//    return m_string;
//}

//void DispatcherQml::setmyString(QString aString)
//{
//    if(aString==m_string)
//    {
//        return;
//    }
//    m_string=aString;
//    emit myStringChanged();
//}

//QString DispatcherQml::myString()
//{
//    m_string="Called from the PROPERTY";
//    return m_string;
//}

bool DispatcherQml::set_launcher(bool flag) {
    QDBusReply<bool> reply = iface1->call("set_launcher_autohide", flag);
    return true;
}

QStringList DispatcherQml::get_themes() {
    QDBusReply<QStringList> reply = iface1->call("get_sys_themes");
    if (reply.isValid()) {
        QStringList value = reply.value();
//        myinfo = value;
        qDebug() << value;
        return reply.value();
    }
    else {
        qDebug() << "get thems msg1 failed!";
    }
}


void DispatcherQml::set_theme(QString theme) {
    QDBusReply<void> reply = iface1->call("set_sys_theme", theme);
}

void DispatcherQml::check_screen_break_point() {
    QDBusReply<void> reply = iface->call("check_screen");
}

void DispatcherQml::custom_plymouth_bg(QString imagepath) {
    QDBusReply<void> reply = iface->call("custom_plymouth", imagepath);
}

void DispatcherQml::set_str(QString str)
{
    notify_str = str;
}
QString DispatcherQml::get_str()
{
    return notify_str;
}
