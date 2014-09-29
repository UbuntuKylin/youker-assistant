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

#ifndef SERVERIMPLEMENTATION_H
#define SERVERIMPLEMENTATION_H

#include <QApplication>
#include <QDebug>
#include "filewipe.h"
#include <QObject>
#include "ShredAdaptor.h"

class ServerImplementation : public QObject
{
    Q_OBJECT
public:
    explicit ServerImplementation(QObject *parent = 0);

public slots:
    int shredFile(const QString &data);
    void exitDbus(const QString &data);
signals:
    void responseFromServer(const QString &data);
};

#endif // SERVERIMPLEMENTATION_H
