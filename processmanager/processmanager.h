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

#include <QObject>
#include <QString>
#include "../component/plugininterface.h"
#include "processdialog.h"

//插件入口
class ProcessManager : public QObject , PluginInterface
{
  Q_OBJECT
  Q_INTERFACES(PluginInterface)

public:
    ProcessManager(QObject* parent = 0);
    virtual ~ProcessManager();

public slots:

public:
    virtual QString getGuid();
    virtual QString getName();
    virtual QString getDescribe();
    virtual QString getPicture();
    virtual void doAction();

private:
    ProcessDialog process_dialog;
};
