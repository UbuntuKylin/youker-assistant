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

#include <QApplication>
#include "ShredAdaptor.h"
#include "serverimplementation.h"

//qdbusxml2cpp shredInterfaceServer.xml -a ShredAdaptor

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ServerImplementation* demo = new ServerImplementation;
    new UkshredAdaptor(demo);
    QDBusConnection connection = QDBusConnection::systemBus();
    bool ret = connection.registerService("org.freedesktop.ukshred");
    ret = connection.registerObject("/", demo);
    return a.exec();
}
