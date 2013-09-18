#ifndef KTHREAD_H
#define KTHREAD_H
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
#include <QThread>
#include <QObject>
#include <QApplication>
#include <QString>

#include <QtDBus>
#include <QDBusInterface>
#include <QDBusConnection>

class KThread : public QThread
{
public:
    KThread(QStringList &arglist, QDBusInterface *systemiface=0, QString method="", QString flag="");
    ~KThread();
    void stop();
protected:
    void run();
private:
    QDBusInterface *iface;
    QStringList list;
    QString method_name;
    QString file_flag;
};
#endif // KTHREAD_H
