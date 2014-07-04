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

#include "weatherdb.h"
#include <QDebug>

WeatherDB::WeatherDB(QObject *parent) :
    QObject(parent)
{
    weatheriface = new QDBusInterface("com.ubuntukylin.weather",
                               "/",
                               "com.ubuntukylin.weather",
                               QDBusConnection::sessionBus());
}

WeatherDB::~WeatherDB() {
    this->exit_qt();
    if (weatheriface != NULL) {
        delete weatheriface;
    }
}

//dbus服务退出
void WeatherDB::exit_qt() {
    weatheriface->call("exit");
}

QStringList WeatherDB::search_city_names_qt(QString search_name) {
    QDBusReply<QStringList> reply = weatheriface->call("search_city_names", search_name);
    return reply.value();
}

QStringList WeatherDB::get_geonameid_list_qt() {
    QDBusReply<QStringList> reply = weatheriface->call("get_geonameid_list");
    return reply.value();
}

QStringList WeatherDB::get_longitude_list_qt() {
    QDBusReply<QStringList> reply = weatheriface->call("get_longitude_list");
    return reply.value();
}

QStringList WeatherDB::get_latitude_list_qt() {
    QDBusReply<QStringList> reply = weatheriface->call("get_latitude_list");
    return reply.value();
}

QString WeatherDB::get_yahoo_city_id_qt(QString geonameid) {
    QDBusReply<QString> reply = weatheriface->call("get_yahoo_city_id", geonameid);
    return reply.value();
}
//-------------------------



//weather sqlite database
QStringList WeatherDB::get_province_list_qt() {
    QDBusReply<QStringList> reply = weatheriface->call("get_province_list");
    return reply.value();
}

QStringList WeatherDB::search_counties_qt(QString province, QString city) {
    QDBusReply<QStringList> reply = weatheriface->call("search_counties", province, city);
    return reply.value();
}

QString WeatherDB::search_id_qt(QString province, QString city, QString county) {
    QDBusReply<QString> reply = weatheriface->call("search_id", province, city, county);
    return reply.value();
}

QStringList WeatherDB::search_city_table_qt(QString province) {
    QDBusReply<QStringList> reply = weatheriface->call("search_city_table", province);
    return reply.value();
}
