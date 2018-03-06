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

#include "systemservice.h"

#include <QCoreApplication>
#include <QDBusContext>
#include <QDBusConnection>
#include <QDBusConnectionInterface>
#include <QDebug>

SystemService::SystemService(QObject *parent) :
    QObject(parent)
{

}

SystemService::~SystemService()
{
    this->exitService();
}

bool SystemService::userIsActive(const QString &user, bool active)
{
    return true;
}

QString SystemService::demoInfo()
{
    emit this->reportAlert(0, "demo");

    auto callerPid = static_cast<int>(this->connection().interface()->servicePid(this->message().service()).value());
    qDebug() << "callerPid="<<callerPid;
    return QString::number(callerPid);
}

CustomData SystemService::getCustomData()
{
    CustomData message;
    message.hash = "01234567890";
    message.name = "lixiang";
    message.description = "Engineer";
    message.index = 8;
    message.valid = true;

    return message;
}

void SystemService::sendCustomData(const CustomData &message)
{
    qDebug() << message.hash;
}

void SystemService::exitService()
{
    qDebug() << "ready to exit service";
    qApp->exit(0);
}
