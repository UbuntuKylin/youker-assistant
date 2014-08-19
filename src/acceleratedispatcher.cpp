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
#include "acceleratedispatcher.h"

AccelerateDispatcher::AccelerateDispatcher(QObject *parent) :
    QObject(parent)
{
    speediface = new QDBusInterface("com.ubuntukylin.youker",
                               "/",
                               "com.ubuntukylin.youker",
                               QDBusConnection::systemBus());
}

AccelerateDispatcher::~AccelerateDispatcher() {
    this->exit_qt();
    if (speediface != NULL) {
        delete speediface;
    }
}

void AccelerateDispatcher::exit_qt() {
    speediface->call("exit");
}

void AccelerateDispatcher::cleanup_memory_qt() {
    speediface->call("cleanup_memory");
}
