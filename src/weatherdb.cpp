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
    QObject::connect(weatheriface, SIGNAL(trans_yahoo_city_id(QString)), this, SLOT(handler_access_yahoo_city_id(QString)));
    QObject::connect(weatheriface, SIGNAL(trans_yahoo_cities(QStringList)), this, SLOT(handler_access_yahoo_cities(QStringList)));
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

void WeatherDB::search_city_names_qt(QString search_name) {
    weatheriface->call("search_city_names", search_name);
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

void WeatherDB::get_yahoo_city_id_qt(QString geonameid) {
    weatheriface->call("get_yahoo_city_id", geonameid);
}

void WeatherDB::handler_access_yahoo_city_id(QString cityId) {
    if (cityId == "error" || cityId.isEmpty()) {
        emit this->send_yahoo_city_id("");
    }
    else {
        emit this->send_yahoo_city_id(cityId);
    }
}

void WeatherDB::handler_access_yahoo_cities(QStringList cities) {
    emit this->ready_to_get_cities_info(cities);
}

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
