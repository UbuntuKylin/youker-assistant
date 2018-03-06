/*
 * Copyright (C) 2013 ~ 2015 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  Kobe Lee    xiangli@ubuntukylin.com/kobe24_lixiang@126.com
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

#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QtCore/QtPlugin>
#include <QString>

class PluginInterface
{
public:
    virtual ~PluginInterface() {}
    virtual QString getGuid()  = 0;
    virtual QString getName() = 0;
    virtual QString getDescribe() = 0;
    virtual QString getPicture() = 0;
    virtual void doAction() = 0;
    virtual QWidget *centralWidget() = 0;
};

//Q_DECLARE_INTERFACE定义在在qobject.h中，用来告诉Qt meta-object system 这个接口名称
Q_DECLARE_INTERFACE(PluginInterface, "com.kylin.Plugin.PluginInterface")

#endif // PLUGININTERFACE_H

