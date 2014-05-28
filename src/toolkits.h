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
#ifndef TOOLKITS_H
#define TOOLKITS_H

#include <QObject>
#include <QtGui>
#include <QDebug>
#include "alertdialog.h"

class Toolkits : public QObject
{
    Q_OBJECT
public:
    explicit Toolkits(QObject *parent = 0);
    //启动alert提示
    Q_INVOKABLE void alertMSG(const QString &alertText);
private:
    int mainwindow_width;
    int mainwindow_height;
    int alert_width;
    int alert_height;
    //本次alert的x坐标
    int alert_x;
    //保额次alert的y坐标
    int alert_y;

    //alert message提示框
    AlertDialog *alertBG;
    //alert提示框timer
    QTimer *alertTimer;
    //alert提示框隐藏timer
    QTimer *alertDelayTimer;
    //alert提示框GOE
    QGraphicsOpacityEffect *alertGOE;
    //alert提示框透明度
    float ao;
    //alert提示框y坐标
    int ay;
private slots:
    //alert提示步处理
    void updateAlert();
    //隐藏alert提示框
    void hideAlert();
};

#endif // TOOLKITS_H
