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
#ifndef KTHREAD_H
#define KTHREAD_H

#include <QThread>
#include <QObject>
#include <QApplication>
#include <QString>

#include <QtDBus>
#include <QDBusInterface>
#include <QDBusConnection>

class KThread : public QThread
{
    Q_OBJECT
public:
    explicit KThread(QStringList &arglist, QDBusInterface *systemiface=0,/* QObject *parent = 0, */QString method="", QString flag="", int size=0);
    ~KThread();
    void stop();
protected:
    void run();
private:
    //Dbus接口
    QDBusInterface *iface;
    QStringList list;
    QString methodName;
    QString fileFlag;
    int fileSize;
};
#endif // KTHREAD_H
