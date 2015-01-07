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
    thread = new KThread(this);
    connect(thread, SIGNAL(msgSignal(const int)),this, SLOT(OnMsgSignal(const int)));//此处connect的第五个参数默认变成Qt::QueuedConnection
}

ShredDispatcher::~ShredDispatcher() {
    this->exit_qt();
    if (shrediface != NULL) {
        delete shrediface;
        shrediface = NULL;
    }
    if (thread != NULL) {
        delete thread;
        thread = NULL;
    }
}

void ShredDispatcher::exit_qt() {
    shrediface->call("exitDbus", "ubuntukylin");
}

void ShredDispatcher::shred_file_qt(const QString &data) {
    QStringList tmp;
    thread->initValues(tmp, shrediface, "shredFile", data);
    thread->start();
}

void ShredDispatcher::OnMsgSignal(const int result)
{
    emit this->finishDeleteWork(result);
}
