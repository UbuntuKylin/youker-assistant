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


#ifndef FILESYSTEMDATA_H
#define FILESYSTEMDATA_H

#include <QObject>
#include <QString>

class FileSystemData : public QObject
{
    Q_OBJECT

public:
    explicit FileSystemData(QObject *parent = 0);

    const QString deviceName() const;
    void setDevName(const QString &name);

    const QString mountDir() const;
    const QString diskType() const;
    const QString totalCapacity() const;
    const QString freeCapacity() const;
    const QString availCapacity() const;
    const QString usedCapactiy() const;
    const int usedPercentage();

    void updateDiskInfo(QString mountDir, QString diskType, QString totalCapacity, QString freeCapacity, QString availCapacity, QString usedCapactiy, int percentage);

private:
    QString m_devName;
    QString m_mountDir;
    QString m_diskType;
    QString m_totalCapacity;
    QString m_freeCapacity;
    QString m_availCapacity;
    QString m_usedCapactiy;
    int m_percentage;
};

#endif // FILESYSTEMDATA_H

