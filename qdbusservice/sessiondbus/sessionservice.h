/*
 * Copyright (C) 2013 ~ 2018 National University of Defense Technology(NUDT) & Tianjin Kylin Ltd.
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

#ifndef SESSIONSERVICE_H
#define SESSIONSERVICE_H

#include <QObject>
#include <QDBusContext>
#include <QScopedPointer>

class SessionService : public QObject, protected QDBusContext
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.kylin.assistant.qsessiondbus")

public:
    explicit SessionService(QObject *parent = 0);
    virtual ~SessionService();

public slots:
    Q_SCRIPTABLE QString demoInfo();
    Q_SCRIPTABLE void exitService();

};

#endif // SESSIONSERVICE_H
