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

//qdbusxml2cpp -v -c SystemInterface -p systeminterface.h:systeminterface.cpp com.kylin.assistant.qsystemdbus.xml

#include <QCoreApplication>
#include <QDBusConnection>
#include <QDBusError>
#include <QDebug>

#include "systemservice.h"
#include "customdata.h"
#include "customdatalist.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setOrganizationName("kylin");
    app.setApplicationName("kylin-assistant-qsystemdbus-service");

    registerCustomDataMetaType();
    registerCustomDataListMetaType();

    SystemService service;
    auto connection = QDBusConnection::systemBus();
    if (!connection.registerService("com.kylin.assistant.qsystemdbus")) {
        qCritical() << "QDbus register service failed reason:" << connection.lastError();
        exit(1);
    }

    if (!connection.registerObject("/com/kylin/assistant/qsystemdbus",
                                  &service,
                                  QDBusConnection::ExportAllSlots |
                                  QDBusConnection::ExportAllSignals)) {
        qCritical() << "QDbus register object failed reason:" << connection.lastError();
        exit(2);
    }

    return app.exec();
}
