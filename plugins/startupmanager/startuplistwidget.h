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

#ifndef STARTUPLISTWIDGET_H
#define STARTUPLISTWIDGET_H

#include "startupitem.h"
#include "startupworker.h"
#include "util.h"

#include <QListWidget>

class QFileSystemWatcher;
class StartupData;

class StartupListWidget : public QListWidget
{
    Q_OBJECT

public:
    StartupListWidget(QWidget *parent=0);
    ~StartupListWidget();

    void displayAutoStartupItems();
    void clearUI();
    void loadItem(StartupData info);
    void loadItems(QStringList items, int scrollValue);
    void listAllDesktopFileInDirectory(MonitorData monitorData);
    void setAppAutoStartup(const QString &exec, bool enabled);
    void removeItemByName(const QString &appName);

public slots:
    void onChangeStartup(const QString &exec, bool active);
    void onMouseEnter();
    void onRefreshUI();

private:
    StartupWorker *m_startupWorker = nullptr;
//    QList <QFileSystemWatcher*> m_watcherList;//QList<QFileSystemWatcher*> *m_watcherList;
//    QMap<QString, QFileSystemWatcher*> m_watcherMap;
};

#endif // STARTUPLISTWIDGET_H
