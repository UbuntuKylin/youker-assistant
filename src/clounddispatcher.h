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
#ifndef CLOUNDDISPATCHER_H
#define CLOUNDDISPATCHER_H

#include <QObject>
#include <QtDBus>
#include <QDBusInterface>
#include <QDBusConnection>

class CloundDispatcher : public QObject
{
    Q_OBJECT
public:
    explicit CloundDispatcher(QObject *parent = 0);
    ~CloundDispatcher();
    QDBusInterface *cloundiface;
    Q_INVOKABLE void get_ip_address_qt();
    Q_INVOKABLE QString show_ip_address_qt();
    Q_INVOKABLE void exit_qt();

signals:
    void startShowIPAddress(QString ip_addr);

public slots:
    void accord_flag_ip(QString key, QString value);
};

#endif // CLOUNDDISPATCHER_H
