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


#ifndef STARTUPDATA_H
#define STARTUPDATA_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QSharedPointer>
#include <QFileSystemWatcher>
#include <glib.h>

/*typedef struct {
    QString dir;
    int index;
    QFileSystemWatcher *watcher;
    QStringList fileList;
} MonitorData;*/

class MonitorData
{
public:
    QString dir;//监控目录
    int index;
    QFileSystemWatcher *watcher;//监控器
    QStringList fileList;//监控目录下的文件列表
};


class StartupData/* : public QObject*/
{
//    Q_OBJECT
//public:
//    explicit StartupData(QObject *parent = 0);

public:
    bool hidden;
    bool no_display;
    bool enabled;
    bool shown;

    QString path;
    QString basename;
    QString name;
    QString exec;
    QString comment;
    QString icon;
    QString description;

    /* position of the directory in the XDG environment variable */
    unsigned int  xdg_position = G_MAXUINT;
    /* position of the first system directory in the XDG env var containing
     * this autostart app too (G_MAXUINT means none) */
    unsigned int  xdg_system_position = G_MAXUINT;
    /* mask of what has changed */
    unsigned int save_mask = 0;
    /* path that contains the original file that needs to be saved */
    QString old_system_path;

public:
    void setEnabled(bool b) { this->enabled = b; }
};


typedef QSharedPointer<StartupData>  StartupDataPtr;
typedef QList<StartupDataPtr>  StartupDataPtrList;

Q_DECLARE_METATYPE(StartupData)
Q_DECLARE_METATYPE(StartupDataPtr)
Q_DECLARE_METATYPE(StartupDataPtrList)

#endif // STARTUPDATA_H

