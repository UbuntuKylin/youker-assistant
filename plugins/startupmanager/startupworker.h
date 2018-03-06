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


#ifndef STARTUPWORKER_H
#define STARTUPWORKER_H

#include "startupdata.h"

#include <QObject>
#include <QMap>
#include <QFileSystemWatcher>

class StartupWorker : public QObject
{
    Q_OBJECT

public:
    explicit StartupWorker(QObject *parent = 0);
    ~StartupWorker();

    void newStartupInfo(const QString &desktopFile, unsigned int xdg_position);
    bool isExecContains(const QString &exec);
    QList<StartupData> getStartupInfoList() const;
    StartupData getStartupInfo(const QString &exec);
    StartupData getStartupInfoAccordDestkopFile(const QString &desktopFile);

    QFileSystemWatcher *createFileSystemMonitor(const QString &path);
    void updateGspXdgDir(const QString &dir, QStringList fileList);
    QString getStringValueAccordKeyFromDesktopFile(const gchar *key, const QString &desktopFile, bool isLocale = false);

    void updateEnable(const QString &exec, bool enabled);
    void updateSaveMask(const QString &exec, unsigned int save_mask);
    void updateXdgPosition(const QString &exec, unsigned int xdg_position);
    void updateXdgSystemPosition(const QString &exec, unsigned int xdg_system_position);
    void updateOldSystemPath(const QString &exec, QString old_system_path);
    void updatePath(const QString &exec, QString path);

    void appendMonitorXdgDirData(MonitorData monitorData);
    int getDirIndex(QString dir);
    QString getMonitorDirectoryAccordXdgSystemPosition(unsigned int index);
    QList<MonitorData> getAllDirs() { /*return m_monitorList;*/ return this->m_xdgMap.values(); }

    void ensureUserAutostartupDirExists(void);
    void changeSaveFlagsWhenDoneSuccess (StartupData info);
//    bool isDesktopFileInUserAndSystemConfiguDir (StartupData info, QString &system_path, QString locale);//Qt
    bool isDesktopFileInUserAndSystemConfiguDir (StartupData info, char **system_path);//glibc
    bool saveAppDesktopInfo(StartupData info);
    void readySaveDesktopInfo(StartupData info);
    StartupData getAppStartupDataAccrodDesktopFileName(QString &basename);

signals:
    void refreshUI();

private:
    QMap<QString, StartupData> m_startupInfoList;
    QMap<QString, MonitorData> m_xdgMap;//QList<MonitorData> m_monitorList;
};

#endif // STARTUPWORKER_H

