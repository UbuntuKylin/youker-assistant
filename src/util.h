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
#ifndef UTIL_H
#define UTIL_H
#include <QtGui>
//const QString YOUKER_COMPANY_SETTING = "Ubuntukylin";
//const QString YOUKER_SETTING_FILE_NAME_SETTING = "youker-assistant";
class Util
{

public:

//    static bool writeInit(QString path, QString user_key, QString user_value);
//    static bool readInit(QString path, QString user_key, QString &user_value);
    static QString get_id_from_cityname(QString cityName);

};

#endif // UTIL_H
