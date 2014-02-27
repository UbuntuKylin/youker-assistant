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

#ifndef UTIL_H
#define UTIL_H
#include <QtGui>
#include <QMap>
const QString YOUKER_COMPANY_SETTING = "ubuntukylin/youker-assistant";
const QString YOUKER_SETTING_FILE_NAME_SETTING = "youker-assistant";
const QString LSB_RELEASE = "/etc/lsb-release";

class Util
{

public:
    static QString get_id_from_cityname(QString cityName);
    static bool id_exists_in_location_file(QString id);
};

#endif // UTIL_H
