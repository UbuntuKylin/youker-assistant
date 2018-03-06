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

#ifndef KTHREAD_H
#define KTHREAD_H

#include <QThread>
#include <QObject>
#include <QApplication>
#include <QString>

#include <QtDBus>
#include <QDBusInterface>
#include <QDBusConnection>
#include <QMap>

class KThread : public QThread
{
    Q_OBJECT
public:
    explicit KThread(QObject *parent);
//    explicit KThread(QStringList &arglist, QDBusInterface *systemiface=0,/* QObject *parent = 0, */QString method="", QString flag="", int size=0);
    ~KThread();
    void stop();
    void initValues(QMap<QString, QVariant> data, QStringList &arglist, QDBusInterface *systemiface=0,QString method="");
//signals:
//  void msgSignal(const int result);//用于向主线程传递
protected:
    void run();
private:
    //Dbus接口
    QDBusInterface *iface;
    QMap<QString, QVariant> mapData;
    QStringList list;
    QString methodName;
//    QString fileFlag;
};
#endif // KTHREAD_H
