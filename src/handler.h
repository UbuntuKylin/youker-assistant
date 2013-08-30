/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
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

#ifndef HANDLER_H
#define HANDLER_H

#include <QObject>
#include <QVariant>
class Handler : public QObject
{
    Q_OBJECT
public slots:
    void signalHandler() {
        emit trans_signal_between_qml();
    }
    void getData(double value, QString up, QString down) {
        emit send_data(QVariant(value), QVariant(up), QVariant(down));
    }

signals:
    void trans_signal_between_qml();
    void send_data(QVariant value, QVariant up, QVariant down);
};

#endif // HANDLER_H
