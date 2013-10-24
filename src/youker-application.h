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

#ifndef SYSTEMAPPLICATION_H
#define SYSTEMAPPLICATION_H
#include <QDeclarativeView>
#include <QApplication>
#include <QMouseEvent>
#include "QPoint"
#include "tray.h"
#include "alertdialog.h"
#include <QDBusInterface>
#include <QDBusConnection>
#include <QtGui>

//const QString SOURCE_LIST = "/etc/apt/sources1.list";
//const QString LSB_RELEASE = "/etc/lsb-release";

class IhuApplication : public QApplication
{
    Q_OBJECT
public:
    IhuApplication(int &argc, char **argv);
    virtual ~IhuApplication();
    bool setup();
private:
    //关联QML界面
    QDeclarativeView *viewer;
    //系统托盘
    Tray *tray;
public slots:
    //主界面显示和隐藏
    void showOrHideMainPage();
};
#endif // SYSTEMAPPLICATION_H
