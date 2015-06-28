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

#include "processmanager.h"
#include <QDebug>

ProcessManager::ProcessManager(QObject *parent)
:QObject(parent), process_dialog(this)
{

}

ProcessManager::~ProcessManager()
{
}

QString ProcessManager::getGuid()
{
    return "UBUNTU-KYLIN-PROCESS";
}

 QString ProcessManager::getName()
{
    return tr("Process Manager");
}

QString ProcessManager::getDescribe()
{
    return tr("Help user to kill process");//方便用户杀掉进程
}

QString ProcessManager::getPicture()
{
    return "processmanager.png";
}

void  ProcessManager::doAction()
{
    int windowWidth = QApplication::desktop()->width();
    int windowHeight = QApplication::desktop()->height();
    process_dialog.resetSkin();
    process_dialog.move((windowWidth - 850) / 2,(windowHeight - 476) / 2);
    process_dialog.show();
    process_dialog.raise();
}

Q_EXPORT_PLUGIN2(ProcessManager, ProcessManager)
