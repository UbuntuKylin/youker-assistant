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

#include "processmanager.h"

#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
#include <QStackedLayout>

ProcessManager::ProcessManager(QObject *parent)
    : QObject(parent)
{
    process_dialog = new SystemMonitor;
}

ProcessManager::~ProcessManager()
{
    if (process_dialog) {
        delete process_dialog;
        process_dialog = nullptr;
    }
}

QString ProcessManager::getGuid()
{
    return "UBUNTU-KYLIN-PROCESS";
}

 QString ProcessManager::getName()
{
    return tr("System Monitor");
}

QString ProcessManager::getDescribe()
{
    return tr("Help user to kill process");//方便用户杀掉进程
}

QString ProcessManager::getPicture()
{
    return "processmanager.png";
}

void ProcessManager::doAction()
{
//    int windowWidth = QApplication::desktop()->width();
//    int windowHeight = QApplication::desktop()->height();
//    process_dialog->resetSkin();
//    process_dialog->move((windowWidth - 850) / 2,(windowHeight - 476) / 2);
    process_dialog->show();
    process_dialog->raise();
    process_dialog->setFocus();
}

QWidget *ProcessManager::centralWidget()
{
    return process_dialog;
}


#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
Q_EXPORT_PLUGIN2(ProcessManager, ProcessManager)
#endif
