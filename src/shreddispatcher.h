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

#ifndef SHREDDISPATCHER_H
#define SHREDDISPATCHER_H

#include <QObject>
#include <QDBusInterface>
#include <QDBusConnection>
#include <QStringList>
#include <QProcess>
#include <QProcessEnvironment>
#include <QtDBus>
#include <QFileDialog>
#include <QMap>
#include <QMessageBox>

class ShredDispatcher : public QObject
{
    Q_OBJECT
public:
    explicit ShredDispatcher(QObject *parent = 0);
    ~ShredDispatcher();
    QString call_dbus_method(QString context);
    void exit_qt();
    Q_INVOKABLE int shred_file_qt(const QString &data);

private:
    QDBusInterface *shrediface;
};

#endif // SHREDDISPATCHER_H
