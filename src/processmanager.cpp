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

#include "processmanager.h"
#include "util.h"
#include <QDebug>

ProcessManager::ProcessManager(QObject *parent) :
    QObject(parent)
{
    mSettings = new QSettings(YOUKER_COMPANY_SETTING, YOUKER_SETTING_FILE_NAME_SETTING);
    mSettings->setIniCodec("UTF-8");
}

ProcessManager::~ProcessManager() {
    mSettings->sync();
    if (mSettings != NULL)
        delete mSettings;
}

//QList<YProcess> ProcessManager::getProcess(){


//    mSettings->beginGroup("user");
//    QString currrentName = mSettings->value("currentName").toString();
//    if(currrentName.isEmpty()) {
//        currrentName = QString("root");
//    }
//    mSettings->endGroup();
//    mSettings->sync();

//    QString cmd = tr("ps -u %1 -o user,pid,%cpu,%mem,start,command").arg(currrentName);

//    QProcess *p = new QProcess();
////    p->start("ps -u lixiang -o user,pid,%cpu,%mem,start,command");
//    p->start(cmd);
//    p->waitForFinished();

//    QList<YProcess> *yplist = new QList<YProcess>();
//    p->readLine();  //throw the first line
//    qDebug() << "-----------------access process list-------------------";
//    QStringList processList;
//    QString str;
//    while(p->canReadLine()){
//        str.clear();
//        YProcess *yp = new YProcess();
//        QString tmps = p->readLine();

//        int spaceIndex = tmps.indexOf(" ");
//        yp->user = tmps.mid(0, spaceIndex);
//        tmps.remove(0, spaceIndex);
//        tmps = tmps.trimmed();

//        spaceIndex = tmps.indexOf(" ");
//        yp->pid = tmps.mid(0, spaceIndex);
//        tmps.remove(0, spaceIndex);
//        tmps = tmps.trimmed();

//        spaceIndex = tmps.indexOf(" ");
//        yp->pcpu = tmps.mid(0, spaceIndex);
//        tmps.remove(0, spaceIndex);
//        tmps = tmps.trimmed();

//        spaceIndex = tmps.indexOf(" ");
//        yp->pmem = tmps.mid(0, spaceIndex);
//        tmps.remove(0, spaceIndex);
//        tmps = tmps.trimmed();

//        spaceIndex = tmps.indexOf(" ");
//        yp->started = tmps.mid(0, spaceIndex);
//        tmps.remove(0, spaceIndex);
//        tmps = tmps.trimmed();

//        yp->command = tmps;

//        yplist->append(*yp);
//        str = tr("%1;%2;%3;%4;%5;%6").arg(yp->user).arg(yp->pid).arg(yp->pcpu).arg(yp->pmem).arg(yp->started).arg(yp->command);
//        processList.append(str);
////        qDebug() << yp->user;
////        qDebug() << yp->pcpu;
////        qDebug() << yp->pmem;
////        qDebug() << yp->started;
////        qDebug() << yp->command;
//    }
//    return *yplist;
//}


QStringList ProcessManager::getProcess(){


    mSettings->beginGroup("user");
    QString currrentName = mSettings->value("currentName").toString();
    if(currrentName.isEmpty()) {
        currrentName = QString("root");
    }
    mSettings->endGroup();
    mSettings->sync();

    QString cmd = tr("ps -u %1 -o user,pid,%cpu,%mem,start,command").arg(currrentName);

    QProcess *p = new QProcess();
    p->start(cmd);
    p->waitForFinished();

    p->readLine();  //throw the first line
    QStringList processList;
    QString str;
    while(p->canReadLine()){
        str.clear();
        YProcess *yp = new YProcess();
        QString tmps = p->readLine();

        int spaceIndex = tmps.indexOf(" ");
        yp->user = tmps.mid(0, spaceIndex);
        tmps.remove(0, spaceIndex);
        tmps = tmps.trimmed();

        spaceIndex = tmps.indexOf(" ");
        yp->pid = tmps.mid(0, spaceIndex);
        tmps.remove(0, spaceIndex);
        tmps = tmps.trimmed();

        spaceIndex = tmps.indexOf(" ");
        yp->pcpu = tmps.mid(0, spaceIndex);
        tmps.remove(0, spaceIndex);
        tmps = tmps.trimmed();

        spaceIndex = tmps.indexOf(" ");
        yp->pmem = tmps.mid(0, spaceIndex);
        tmps.remove(0, spaceIndex);
        tmps = tmps.trimmed();

        spaceIndex = tmps.indexOf(" ");
        yp->started = tmps.mid(0, spaceIndex);
        tmps.remove(0, spaceIndex);
        tmps = tmps.trimmed();

        yp->command = tmps;
        str = tr("%1;%2;%3;%4;%5;%6").arg(yp->user).arg(yp->pid).arg(yp->pcpu).arg(yp->pmem).arg(yp->started).arg(yp->command);
        processList.append(str);
    }
    return processList;
}


bool ProcessManager::killProcess(QString pid){
    QProcess *p = new QProcess();
    p->start("kill -9 " + pid);
    return p->waitForFinished();
}

void ProcessManager::clearMap() {
    processMap.clear();
}

void ProcessManager::updateMap(QString num, QString id) {
    processMap.insert(num, id);
}

QString ProcessManager::getProcessId(QString currentIndex) {
    QString currentId;
    if(processMap.contains(currentIndex)) {
        currentId = processMap.value(currentIndex);
    }
    return currentId;
}
