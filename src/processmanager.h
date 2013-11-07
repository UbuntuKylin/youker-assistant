/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
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

#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <QObject>
#include <QDebug>
#include <QProcess>
#include "yprocess.h"
#include "util.h"
#include <QMap>
#include <QFile>

class QSettings;
class ProcessManager : public QObject
{
    Q_OBJECT
public:
    explicit ProcessManager(QObject *parent = 0);
    ~ProcessManager();

    QMap<QString,QString> *memos;
    void readMemoFile();
//    Q_INVOKABLE QList<YProcess> getProcess();
    //得到当前登录用户的所有进程列表
    Q_INVOKABLE QStringList getProcess();
    //根据进程号杀掉进程
    Q_INVOKABLE bool killProcess(QString pid);
    //清空进程序号和进程号组合的map
    Q_INVOKABLE void clearMap();
    //更新进程序号和进程号组合的map
    Q_INVOKABLE void updateMap(QString num, QString id);
    //从map中得到进程号
    Q_INVOKABLE QString getProcessId(QString currentIndex);
signals:

public slots:
private:
    QSettings * mSettings;
    QMap<QString, QString> processMap;
    
};

#endif // PROCESSMANAGER_H
