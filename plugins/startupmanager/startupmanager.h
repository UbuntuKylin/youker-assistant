/*
 * Copyright (C) 2013 ~ 2018 National University of Defense Technology(NUDT) & Tianjin Kylin Ltd.
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

#ifndef STARTUPMANAGER_H
#define STARTUPMANAGER_H

#include <QObject>
#include <QString>
#include "../../component/plugininterface.h"
#include "startupwidget.h"

//插件入口
class StartupManager : public QObject , PluginInterface
{
  Q_OBJECT
  Q_INTERFACES(PluginInterface)

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    Q_PLUGIN_METADATA(IID "com.kylin.Plugin.PluginInterface" FILE "startupmanager.json")//指定IID和.json文件
#endif

public:
    explicit StartupManager(QObject* parent = 0);
    virtual ~StartupManager();
    QWidget *centralWidget();

public:
    virtual QString getGuid();
    virtual QString getName();
    virtual QString getDescribe();
    virtual QString getPicture();
    virtual void doAction();

private:
    StartupWidget *startup_dialog = nullptr;
};

#endif // STARTUPMANAGER_H
