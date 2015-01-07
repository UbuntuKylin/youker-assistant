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
#ifndef ACCELERATEDISPATCHER_H
#define ACCELERATEDISPATCHER_H

#include <QObject>
#include <QDBusInterface>
#include <QDBusConnection>

class AccelerateDispatcher : public QObject
{
    Q_OBJECT
public:
    explicit AccelerateDispatcher(QObject *parent = 0);
    ~AccelerateDispatcher();

    Q_INVOKABLE void exit_qt();
    //一键加速
    Q_INVOKABLE void cleanup_memory_qt();

private:
    QDBusInterface *speediface;
};

#endif // ACCELERATEDISPATCHER_H
