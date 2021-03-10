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

#include "devicemanager.h"

DeviceManager::DeviceManager(QObject *parent) :
    QObject(parent)
{
}

QStringList DeviceManager::getDeviceMsg(){
    QString cmd = "lspci -k";

    QProcess *p = new QProcess();
    p->start(cmd);
    p->waitForFinished();

    QStringList tmpList;
    while(p->canReadLine()){
        QString str = p->readLine();
        str = str.left(str.length() - 1);
        tmpList.append(str);
    }

    QString tmps;
    QStringList deviceMsgList;
    for (int i = 0;i < tmpList.size();i ++) {
        QString str = tmpList.at(i);
//        qDebug() << str;
        if(str.startsWith("\t") == false){
            if(tmps != ""){
                deviceMsgList.append(tmps);
            }
            tmps = str.mid(str.indexOf(" "));
//            qDebug() << tmps;
        }else{
            QStringList tmparr = str.split(":");
            if(tmparr.at(0).indexOf("Kernel driver in use") != -1){
                tmps += ";";
                tmps += "driver in use:";   //"使用中的驱动:"
                tmps += tmparr.at(1);
            }
            if(tmparr.at(0).indexOf("Kernel modules") != -1){
                tmps += ";";
                tmps += "existing drivers:";  //"可选择的驱动:"
                tmps += tmparr.at(1);
            }
        }
    }
    if(tmps != ""){
        deviceMsgList.append(tmps);
    }
    if(isHW990()){
        //add graphics & sound
        deviceMsgList.append("VGA compatible controller: Mali-G76;driver in use:mali");
        deviceMsgList.append("Audio device:da_combine_v5;driver in use:hi3xxx_DA_combine_v5");
    }
    qDebug() << deviceMsgList;
    return deviceMsgList;
}

bool DeviceManager::isHW990(){
    QFile file("/proc/cpuinfo");
    bool isHW990 = false;
    bool ret = file.open(QIODevice::ReadOnly|QIODevice::Text);
    if (ret){
        QString all = file.readAll();
        if(all.contains("HUAWEI Kirin 990")){
            isHW990 = true;
        }
    }
    return isHW990;
}
