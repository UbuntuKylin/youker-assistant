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


#ifndef FILESYSTEMWORKER_H
#define FILESYSTEMWORKER_H

#include <QObject>
#include <QMap>

#include "filesystemdata.h"

class FileSystemWorker : public QObject
{
    Q_OBJECT

public:
    explicit FileSystemWorker(QObject *parent = 0);
    ~FileSystemWorker();

    void removeDiskItem(const QString &devname);

    FileSystemData *getDiskInfo(const QString &devname);
    QList<FileSystemData *> diskInfoList() const;
    void addDiskInfo(const QString &devname, FileSystemData *info);
    void removeDiskInfo(const QString &devname);
    bool isDeviceContains(const QString &devname);

public slots:
    void onFileSystemListChanged();

private:
    QMap<QString, FileSystemData *> m_diskInfoList;
};

#endif // FILESYSTEMWORKER_H

