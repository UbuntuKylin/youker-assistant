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

#include "startupmanager.h"

#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
#include <QStackedLayout>


//#sudo apt-get install rcconf
//root 下运行: #sudo rcconf
//功能更全的工具：sysv-rc-conf
//#sudo apt-get update
//#sudo apt-get install sysv-rc-conf
//运行：#sudo sysv-rc-conf

//gnome-session-properties(gnome-session-bin/gnome-session)


StartupManager::StartupManager(QObject *parent)
    : QObject(parent)
{
    startup_dialog = new StartupWidget;
}

StartupManager::~StartupManager()
{
    if (startup_dialog) {
        delete startup_dialog;
        startup_dialog = nullptr;
    }
}

QString StartupManager::getGuid()
{
    return "UBUNTU-KYLIN-STARTUP";
}

 QString StartupManager::getName()
{
    return tr("Startup Manager");
}

QString StartupManager::getDescribe()
{
    return tr("Help user to manager application startup items");
}

QString StartupManager::getPicture()
{
    return "startupmanager.png";
}

void StartupManager::doAction()
{
    startup_dialog->show();
    startup_dialog->raise();
    startup_dialog->setFocus();
}

QWidget *StartupManager::centralWidget()
{
    return startup_dialog;
}


#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
Q_EXPORT_PLUGIN2(StartupManager, StartupManager)
#endif
