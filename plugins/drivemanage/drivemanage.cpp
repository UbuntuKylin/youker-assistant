/*
 * Copyright (C) 2021 KylinSoft Co., Ltd.
 *
 * Authors:
 *  Yang Min yangmin@kylinos.cn
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stdio.h"
#include "drivemanage.h"
#include "../../src/commondef.h"
#include "../../src/kajsondef.h"

#include <QLabel>
#include <QIcon>
#include <QDebug>
#include <QDBusMessage>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>
#include <QTimer>
#include <QFile>
#include <QProcess>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

DriveManage::DriveManage()
{
    m_pluginName = tr("DriveManager");
    m_pluginType = DRIVER_MANAGER;
    mFirstLoad = true;
}

DriveManage::~DriveManage()
{

}

QString DriveManage::getPluginName()
{
    return m_pluginName;
}

int DriveManage::getPluginType()
{
    return m_pluginType;
}

QWidget* DriveManage::getPluginMainWnd()
{
    if (mFirstLoad) {
        mFirstLoad = false;
        initUI();
        initConnections();
    }
    return m_pluginWidget;
}

void DriveManage::pluginDelayControl()
{
    // 首次获取驱动信息
    getDriveInfo(true);
}

const QString DriveManage::name() const
{
    return QStringLiteral("drivemanager");
}

void DriveManage::updatePluginContent()
{
    qInfo()<<"";
    getDriveInfo(true);
}

void DriveManage::initUI()
{
    m_pluginWidget = new QWidget();
    m_pluginWidget->setFixedSize(RIGHT_PANEL_WIDTH, RIGHT_PANEL_HEIGHT);
    m_pluginWidget->setAttribute(Qt::WA_DeleteOnClose);

    m_mainLayout = new QHBoxLayout();
    m_mainLayout->setContentsMargins(0,0,0,0);
    m_mainLayout->setSpacing(0);

    m_stackedWidget = new QStackedWidget();
    // add widget
    m_loadingWidget = new LoadingWidget();
    m_stackedWidget->addWidget(m_loadingWidget);
    // add driveInfo widget
    m_driveInfoPage = new DriveInfoPage();
    m_stackedWidget->addWidget(m_driveInfoPage);

    m_mainLayout->addWidget(m_stackedWidget);

    m_pluginWidget->setLayout(m_mainLayout);
}

void DriveManage::initConnections()
{
}

void DriveManage::getDriveInfo(bool bReScan)
{
    Q_UNUSED(bReScan);
    QString strInfoJson = getDriveInfoJson();
    onUpdateInfo(1, strInfoJson);
}

void DriveManage::onUpdateInfo(unsigned uStatus, QString strInfoJson)
{
    qInfo()<<"updateInfo:"<<uStatus<<","<<strInfoJson;
    if (uStatus == 0) {
        m_stackedWidget->setCurrentIndex(0);
    } else {
        if (m_driveInfoPage) {
            m_driveInfoPage->onUpdateInfo(strInfoJson);
            m_stackedWidget->setCurrentIndex(1);
        }
    }
}

bool DriveManage::isHW990() {
    QFile file("/proc/cpuinfo");
    bool isHW990 = false;
    bool ret = file.open(QIODevice::ReadOnly|QIODevice::Text);
    if (ret){
        QString all = file.readAll();
        if(all.contains("HUAWEI Kirin 990") || all.contains("kirin990") || all.contains("HUAWEI Kirin 9006C") || all.contains("Kirin990")){
            isHW990 = true;
        }
    }
    return isHW990;
}

QStringList DriveManage::getDeviceDriveInfo()
{
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
        if(str.startsWith("\t") == false){
            if(tmps != ""){
                deviceMsgList.append(tmps);
            }
            tmps = str.mid(str.indexOf(" "));
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

QString DriveManage::getDriveInfoJson()
{
    QJsonObject rootObj;
    QJsonArray driveArray;
    QStringList list = getDeviceDriveInfo();
    for (int i=0 ; i < list.length() ; i++) {
        QString strDriveName;
        QString strDriveType;
        QStringList splitlist = list.at(i).split(";");
        if(splitlist.length() == 1) {
            //QStringList name = splitlist.at(0).split(":");
        } else if(splitlist.length() == 2) {
            QStringList name1 = splitlist.at(0).split(":");
            QStringList name2 = splitlist.at(1).split(":");
            strDriveType = name1.at(0).trimmed();
            strDriveName = name2.at(1);
        } else if(splitlist.length() == 3) {
            QStringList name3 = splitlist[0].split(":");
            QStringList name4 = splitlist[1].split(":");
            //QStringList name5 = splitlist[2].split(":");
            strDriveType = name3.at(0).trimmed();
            strDriveName = name4.at(1);
        }
        if (!strDriveType.isEmpty()) {
            QJsonObject oneElement;
            oneElement.insert(DRIVE_INFO_TYPE, strDriveType);
            oneElement.insert(DRIVE_INFO_NAME, strDriveName);
            //oneElement.insert(DRIVE_INFO_VERSION, strDriveName);
            driveArray.append(oneElement);
        }
    }
    rootObj.insert(DRIVE_INFO, driveArray);
    QJsonDocument rootDoc;
    rootDoc.setObject(rootObj);
    return QString(rootDoc.toJson(QJsonDocument::Compact));  //紧凑格式;
}
