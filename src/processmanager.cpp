/*
 * Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd.
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

ProcessManager::ProcessManager(QObject *parent) :
    QObject(parent)
{
    mSettings = new QSettings(YOUKER_COMPANY_SETTING, YOUKER_SETTING_FILE_NAME_SETTING);
    mSettings->setIniCodec("UTF-8");

    memos = new QMap<QString,QString>();
    readMemoFile();
}

ProcessManager::~ProcessManager(){
    mSettings->sync();
    if (mSettings != NULL) {
        delete mSettings;
    }
    if (memos != NULL) {
        delete memos;
    }
}

void ProcessManager::readMemoFile(){
    QFile *memoFile = new QFile("/var/lib/youker-assistant-daemon/processmanager/processmemo");
    if(memoFile->open(QIODevice::ReadOnly)){
        memos->clear();
        QTextStream in(memoFile);
        while(!in.atEnd()){
            QString line = in.readLine();
            QStringList tmp = line.split(":");
            memos->insert(tmp.at(0), tmp.at(1));
        }
        memoFile->close();
    }
}

QString ProcessManager::getCasualUser() {
    QString currrentName;
    mSettings->beginGroup("user");
    currrentName = mSettings->value("currentName").toString();
    mSettings->endGroup();
    mSettings->sync();
    return currrentName;
}

QStringList ProcessManager::getProcess(){
    mSettings->beginGroup("user");
    QString currrentName = mSettings->value("currentName").toString();
    if(currrentName.isEmpty()){
        currrentName = QString("root");
    }
    mSettings->endGroup();
    mSettings->sync();

    QString cmd = tr("ps -u %1 -o user,pid,%cpu,%mem,start,ucmd,command").arg(currrentName);

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

        spaceIndex = tmps.indexOf(" ");
        yp->cmd = tmps.mid(0, spaceIndex);
        tmps.remove(0, spaceIndex);
        tmps = tmps.trimmed();

        yp->command = tmps;

        foreach (QString key, memos->keys()){
            if(yp->command.indexOf(key) != -1){
                yp->memo = memos->value(key);
            }
        }

        str = tr("%1;%2;%3;%4;%5;%6;%7").arg(yp->user).arg(yp->pid).arg(yp->pcpu).arg(yp->pmem).arg(yp->started).arg(yp->memo).arg(yp->command);
        processList.append(str);
    }
    return processList;
}

QStringList ProcessManager::getProcessAdvance(){
    QString cmd = "ps ax -o user,pid,%cpu,%mem,start,ucmd,command";

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

        spaceIndex = tmps.indexOf(" ");
        yp->cmd = tmps.mid(0, spaceIndex);
        tmps.remove(0, spaceIndex);
        tmps = tmps.trimmed();

        yp->command = tmps;

        foreach (QString key, memos->keys()){
            if(yp->command.indexOf(key) != -1){
                yp->memo = memos->value(key);
            }
        }

        str = tr("%1;%2;%3;%4;%5;%6;%7").arg(yp->user).arg(yp->pid).arg(yp->pcpu).arg(yp->pmem).arg(yp->started).arg(yp->memo).arg(yp->command);
        processList.append(str);
    }
    return processList;
}

bool ProcessManager::killProcess(QString pid){
    QProcess *p = new QProcess();
//    qDebug() << pid;
    p->start("kill -9 " + pid);
    bool aa = p->waitForFinished();
//    qDebug() << QString("%1").arg(aa);
    return aa;
//    return p->waitForFinished();
}

void ProcessManager::clearMap(){
    processMap.clear();
}

void ProcessManager::updateMap(QString num, QString id){
    processMap.insert(num, id);
}

QString ProcessManager::getProcessId(QString currentIndex){
    QString currentId;
    if(processMap.contains(currentIndex)){
        currentId = processMap.value(currentIndex);
    }
    return currentId;
}

int ProcessManager::getProcessIndex(QString currentId){
    int currentIndex;
    currentIndex = processMap.key(currentId).toInt();
//    qDebug() << QString("%1").arg(currentIndex);
    return currentIndex;
}

void ProcessManager::clearUserMap(){
    userMap.clear();
}

void ProcessManager::updateUserMap(QString id, QString user){
    userMap.insert(id, user);
}

QString ProcessManager::getProcessUser(QString currentId){
    QString currentUser;
    if(userMap.contains(currentId)){
        currentUser = userMap.value(currentId);
    }
    return currentUser;
}
