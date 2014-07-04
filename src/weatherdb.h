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

#ifndef WEATHERDB_H
#define WEATHERDB_H

#include <QObject>
#include <QDBusInterface>
#include <QDBusConnection>
#include <QtDBus>
#include <QDeclarativeView>
#include <QDesktopWidget>
#include <QDeclarativeContext>

class WeatherDB : public QObject
{
    Q_OBJECT
public:
    explicit WeatherDB(QObject *parent = 0);
    ~WeatherDB();
    QDBusInterface *weatheriface;
    //退出sessiondubs服务
    void exit_qt();
    //weather sqlite database
    QStringList get_province_list_qt();
    QStringList search_counties_qt(QString province, QString city);
    QString search_id_qt(QString province, QString city, QString county);
    QStringList search_city_table_qt(QString province);

    //得到yahoo城市列表
    QStringList search_city_names_qt(QString search_name);
    //得到对应yahoo城市列表的geonameid列表
    QStringList get_geonameid_list_qt();
    //得到经度
    QStringList get_longitude_list_qt();
    //得到纬度
    QStringList get_latitude_list_qt();
    //得到可以获取天气数据的id
    QString get_yahoo_city_id_qt(QString geonameid);
};

#endif // WEATHERDB_H
