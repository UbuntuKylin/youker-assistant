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

#include "util.h"
#include <QFileDialog>

QString Util::get_id_from_cityname(QString cityName) {
    QString cityId = "";
    QFile locationFile("/usr/lib/python2.7/dist-packages/youker-assistant-daemon/src/weather/location.txt");
    if(locationFile.exists() && locationFile.open(QFile::ReadOnly)) {
        QTextStream in(&locationFile);
        QString line;
        QString location;
        while(!in.atEnd())
        {
           line = in.readLine();
           location = line.split(':')[0];
           if (cityName == location) {
               cityId = line.split(':')[1];
               break;
           }
        }
        locationFile.close();

    }
    return cityId;
}

bool Util::id_exists_in_location_file(QString id) {
    QFile locationFile("/usr/lib/python2.7/dist-packages/youker-assistant-daemon/src/weather/location.txt");
    if(locationFile.exists() && locationFile.open(QFile::ReadOnly)) {
        QTextStream in(&locationFile);
        QString line;
        QString tmpId;
        while(!in.atEnd())
        {
           line = in.readLine();
           tmpId = line.split(':')[1];
           if (tmpId == id) {
               locationFile.close();
               return true;
           }
        }
        locationFile.close();
    }
    return false;
}

