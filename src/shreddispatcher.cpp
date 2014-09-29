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

#include "shreddispatcher.h"
#include <QDebug>

ShredDispatcher::ShredDispatcher(QObject *parent) :
    QObject(parent)
{
    shrediface = new QDBusInterface("org.freedesktop.ukshred",
                               "/",
                               "org.freedesktop.ukshred",
                               QDBusConnection::systemBus());
}

ShredDispatcher::~ShredDispatcher() {
    this->exit_qt();
    if (shrediface != NULL) {
        delete shrediface;
    }
}

void ShredDispatcher::exit_qt() {
    shrediface->call("exitDbus", "ubuntukylin");
}

int ShredDispatcher::shred_file_qt(const QString &data) {
    QDBusReply<int> reply = shrediface->call("shredFile", data);
    return reply.value();
}
