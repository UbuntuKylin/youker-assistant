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
#include "systemdispatcher.h"
#include <QDebug>
#include <QVariant>
#include <QProcessEnvironment>
#include <QtDBus>
#include <QObject>
#include <QString>
SystemDispatcher::SystemDispatcher(QObject *parent) :
    QObject(parent)
{
    systemiface = new QDBusInterface("com.ubuntukylin.Ihu",
                               "/",
                               "com.ubuntukylin.Ihu",
                               QDBusConnection::systemBus());

    //绑定到底层清理完毕后发送到信号函数clear_browser
    QObject::connect(systemiface,SIGNAL(clear_browser(QString)),this,SLOT(handler_clear_rubbish(QString)));
    QObject::connect(systemiface,SIGNAL(pc_msg(QString)),this,SLOT(show_signal(QString)));

    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("pc_message");

    notify_str = "";

    if (reply.isValid()) {
        QMap<QString, QVariant> value = reply.value();
        myinfo = value;
        qDebug() << myinfo;
    }
    else {
        qDebug() << "get pc_message failed!";
    }
}


QString SystemDispatcher::get_value(QString key)
{
    QVariant tt = myinfo.value(key);
    return tt.toString();
}

int SystemDispatcher::get_add_value()
{
    QDBusReply<int> reply = systemiface->call("test_add", 3, 4);
    int tt = reply.value();
    return tt;
}

void SystemDispatcher::handler_clear_rubbish(QString msg)
{
    emit finishCleanWork(msg);
//    emit myStringChanged("Kobe test for fastclear button and dbus communication");
}


QString SystemDispatcher::show_signal(QString msg) {
    qDebug() << "pspspspspps***********";
    qDebug() << msg;
    return msg;
}

void SystemDispatcher::send_btn_msg(QString str)
{
    QDBusReply<void> reply = systemiface->call("test_fastclear", str);
}

//QString SystemDispatcher::getMyString()
//{
//    m_string="Called from the Q_INVOKABLE function";
//    return m_string;
//}

//void SystemDispatcher::setmyString(QString aString)
//{
//    if(aString==m_string)
//    {
//        return;
//    }
//    m_string=aString;
//    emit myStringChanged();
//}

//QString SystemDispatcher::myString()
//{
//    m_string="Called from the PROPERTY";
//    return m_string;
//}


void SystemDispatcher::check_screen_break_point() {
    QDBusReply<void> reply = systemiface->call("check_screen");
}

void SystemDispatcher::custom_plymouth_bg(QString imagepath) {
    QDBusReply<void> reply = systemiface->call("custom_plymouth", imagepath);
}


//QMap<QString, QStringList> SystemDispatcher::search_the_same_file(QString path) {
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

int SystemDispatcher::get_the_record_qt(QString mode) {
    QDBusReply<int> reply = systemiface->call("get_the_record", mode);
    if (reply.isValid()) {
        int value = reply.value();
//        qDebug() << "value start";
//        qDebug() << value;
//        qDebug() << "value end";
        return value;
    }
    else {
        qDebug() << "get record number failed!";
        return 0;
    }
}


void SystemDispatcher::clean_the_browser_qt(QString mode) {
    QDBusReply<void> reply = systemiface->call("clean_the_browser", mode);
}

QMap<QString, QVariant> SystemDispatcher::search_same_files(QString path) {
    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("search_the_same", path);
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

QStringList SystemDispatcher::search_largest_file(QString path) {
    QDBusReply<QStringList> reply = systemiface->call("search_the_large", path);
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

void SystemDispatcher::set_str(QString str)
{
    notify_str = str;
}
QString SystemDispatcher::get_str()
{
    return notify_str;
}


