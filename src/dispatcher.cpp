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
    QObject::connect(iface,SIGNAL(clear_browser(QString)),this,SLOT(show_progress_clear_rubbish(QString)));
    QObject::connect(iface,SIGNAL(pc_msg(QString)),this,SLOT(show_signal(QString)));
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

    QDBusReply<QMap<QString, QVariant> > reply2 = iface->call("search_the_same", "/home/kobe/a/");
    if (reply2.isValid()) {
        qDebug() << "aaaaaaaaaaaaa";
        qDebug() << reply2.value();
    }
    else {
        qDebug() << "search_the_same failed!";
//        return "search_the_same has error";
    }


    QDBusReply<QStringList> reply3 = iface->call("search_the_large", "/home/kobe/a/");
    if (reply3.isValid()) {
        QStringList value = reply3.value();
        qDebug() << value;
    }
    else {
        qDebug() << "search_the_large failed!";
    }


}

QString DispatcherQml::get_value(QString key)
{
    QVariant tt = myinfo.value(key);
    return tt.toString();
}

int DispatcherQml::get_add_value()
{
    QDBusReply<int> reply = iface->call("test_add", 3, 4);
    int tt = reply.value();
    return tt;
}

QString DispatcherQml::show_progress_clear_rubbish(QString msg)
{
    qDebug() << "kobekoeb***********";
    qDebug() << msg;
//    emit myStringChanged("Kobe test for fastclear button and dbus communication");
    return msg;
}

QString DispatcherQml::show_signal(QString msg) {
    qDebug() << "pspspspspps***********";
    qDebug() << msg;
    return msg;
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

//QMap<QString, QStringList> search_the_same_file(QString imagepath);

//QMap<QString, QStringList> DispatcherQml::search_the_same_file(QString path) {
//    QDBusReply<QMap<QString, QStringList> > reply = iface->call("search_the_same", path);
////    if (reply.isValid()) {
////        QMap<QString, QStringList> value = reply.value();
//////        myinfo = value;
////        qDebug() << value;
////    }
////    else {
////        qDebug() << "get same file failed!";
////    }
//}

int DispatcherQml::get_record_number(QString mode) {
    QDBusReply<int> reply = iface->call("get_the_record", mode);
    if (reply.isValid()) {
        int value = reply.value();
        qDebug() << "value start";
        qDebug() << value;
        qDebug() << "value end";
        return value;
    }
    else {
        qDebug() << "get record number failed!";
        return 0;
    }
}


void DispatcherQml::clean_browser_record(QString mode) {
    QDBusReply<void> reply = iface->call("clean_the_browser", mode);
}

QMap<QString, QVariant> DispatcherQml::search_same_files(QString path) {
    QDBusReply<QMap<QString, QVariant> > reply = iface->call("search_the_same", path);
    if (reply.isValid()) {
        qDebug() << "aaaaaaaaaaaaa";
        qDebug() << reply.value();
        return reply.value();
    }
    else {
        qDebug() << "search_the_same failed!";
//        return "search_the_same has error";
    }
}

QStringList DispatcherQml::search_largest_file(QString path) {
    QDBusReply<QStringList> reply = iface->call("search_the_large", path);
    if (reply.isValid()) {
        QStringList value = reply.value();
        qDebug() << value;
        return reply.value();
    }
    else {
        qDebug() << "search_the_large failed!";
//        return "search_the_large has error";
    }
}

void DispatcherQml::set_str(QString str)
{
    notify_str = str;
}
QString DispatcherQml::get_str()
{
    return notify_str;
}
