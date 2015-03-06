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

#include "systemtray.h"

SystemTray::SystemTray(QWidget *parent)
    : QSystemTrayIcon(parent)
{
    this->initTrayActions();
    this->setLanguage();
}

SystemTray::~SystemTray()
{
}

void SystemTray::setLanguage()
{
    this->setToolTip(tr("Youker Assistant"));
    action_open->setText(tr("open"));
    action_open->setIcon(QIcon("://res/icon.png"));
    action_logout->setText(tr("logout"));
}

void SystemTray::initTrayActions()
{
    this->setIcon(QIcon("://res/icon.png"));
    tray_menu = new QMenu();
//    tray_menu->setObjectName("mainmenu");
    action_open = new QAction(this);
    action_logout = new QAction(this);

    tray_menu->setFixedWidth(250);

    connect(action_open, SIGNAL(triggered()), this, SIGNAL(showWidget()));
    connect(action_logout, SIGNAL(triggered()), qApp, SLOT(quit()));

    this->setContextMenu(tray_menu);

    tray_menu->addAction(action_open);
    tray_menu->addSeparator();
    tray_menu->addAction(action_logout);
}
