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

//qdbusxml2cpp -a sessionadaptor -c SessionAdaptor -l SessionAdaptor com.kylin.assistant.qsessiondbus.xml
//qdbusxml2cpp com.kylin.assistant.qsessiondbus.xml -a sessionadaptor -c SessionAdaptor

#include <QCoreApplication>
#include <QDBusConnection>
#include <QDBusError>
#include <QDebug>

#include "sessionservice.h"
#include "./data/sessionadaptor.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setOrganizationName("kylin");
    app.setApplicationName("kylin-assistant-qsessiondbus-service");

    SessionService service;
//    SessionService *service = new SessionService();
    new SessionAdaptor(&service);
    auto connection = QDBusConnection::sessionBus();
    if (!connection.registerService("com.kylin.assistant.qsessiondbus")) {
        qCritical() << "QDbus register service failed reason:" << connection.lastError();
        exit(1);
    }//QDBusConnection::sessionBus().unregisterService("com.kylin.assistant.qsessiondbus");

    if (!connection.registerObject("/com/kylin/assistant/qsessiondbus",
                                  &service,
                                  QDBusConnection::ExportAllSlots |
                                  QDBusConnection::ExportAllSignals)) {
        qCritical() << "QDbus register object failed reason:" << connection.lastError();
        exit(2);
    }

    return app.exec();
}
