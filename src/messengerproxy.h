/*
 * Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd.
 * Author: Kobe Lee
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

#ifndef MESSENGERPROXY_H
#define MESSENGERPROXY_H

#include <QObject>

class MessengerProxy : public QObject
{
    Q_OBJECT
public:
    static MessengerProxy *get_instance_object();
    ~MessengerProxy();

private:
    explicit MessengerProxy(QObject *parent = 0);
    static MessengerProxy *proxy;

signals:
    void getHomeBackIndex(int index);

public slots:
    void accessCurrentHomeIndex(int index);
};

#endif // MESSENGERPROXY_H
