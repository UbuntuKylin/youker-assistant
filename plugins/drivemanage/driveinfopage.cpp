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

#include "driveinfopage.h"

#include <QPixmap>
#include <QLabel>
#include <QDBusMessage>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>
#include <QDebug>
#include <QTimer>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

DriveInfoPage::DriveInfoPage(QWidget *parent)
    : QWidget(parent)
{
    m_strInfoJson = "";
    initUI();
    initConnections();
}

void DriveInfoPage::initUI()
{
    m_mainLayout = new QHBoxLayout();
    m_mainLayout->setContentsMargins(0,0,0,0);
    m_mainLayout->setSpacing(0);
    m_listLayout = new QVBoxLayout();
    m_listLayout->setContentsMargins(32,0,0,0);
    m_listLayout->setSpacing(0);
    m_listLayout->setAlignment(Qt::AlignTop);
    m_listFrame = new QFrame();
    m_listFrame->setLayout(m_listLayout);
    m_scrollFrame = new QScrollArea();
    m_scrollFrame->setContentsMargins(0, 0, 0, 0);
    m_scrollFrame->setBackgroundRole(QPalette::Base);
    m_scrollFrame->setAutoFillBackground(true);
    m_scrollFrame->setFrameStyle(0);
    m_scrollFrame->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollFrame->setWidgetResizable(true);
    m_scrollFrame->setWidget(m_listFrame);

    m_mainLayout->addWidget(m_scrollFrame);
    this->setLayout(m_mainLayout);
}

void DriveInfoPage::clearInfoItems()
{
    QMap<unsigned, QList<KDriveInfoItem*>>::iterator itDriveInfoItems = m_mapItems.begin();
    for (; itDriveInfoItems != m_mapItems.end(); itDriveInfoItems++) {
        for (int n = 0; n < itDriveInfoItems.value().size(); n++) {
            if (itDriveInfoItems.value().at(n)) {
                delete itDriveInfoItems.value().at(n);
            }
        }
        itDriveInfoItems.value().clear();
    }
    m_mapItems.clear();
    m_mapDriveInfo.clear();
}

void DriveInfoPage::refreshInfoItems()
{
    QMap<DI_TYPE, QList<DriveInfo>>::iterator itDriveInfo = m_mapDriveInfo.begin();
    int nCurIndex = 0;
    qInfo()<<"Info Count:"<<m_mapDriveInfo.size();
    for (; itDriveInfo != m_mapDriveInfo.end(); itDriveInfo++) {
         qInfo()<<"Info Type:"<<itDriveInfo.key();
        for (int n = 0; n < itDriveInfo.value().size(); n++) {
            QString itemIcon = "";
            QString itemName = "";
            unsigned uType = DRIVEINFOTYPE_OTHER;
            DriveInfo driveInfo = itDriveInfo.value().at(n);
            if (driveInfo.strType == "Host bridge" ||
                driveInfo.strType == "Signal processing controller" ||
                driveInfo.strType == "USB controller" ||
                driveInfo.strType == "PCI bridge" ||
                driveInfo.strType == "SA bridge") { // 主板
                itemIcon = ":/imgres/img_res/mother-board.svg";
                itemName = tr("Motherboard");
                uType = DRIVEINFOTYPE_MOTHERBOCARD;
            } else if (driveInfo.strType == "VGA compatible controller") { // 显卡
                itemIcon = ":/imgres/img_res/graphics-card.svg";
                itemName = tr("Graphics Card");
                uType = DRIVEINFOTYPE_GRPHICS;
            } else if (driveInfo.strType == "Ethernet controller") {    // 网卡
                itemIcon = ":/imgres/img_res/wired.svg";
                itemName = tr("Wired Network Card");
                uType = DRIVEINFOTYPE_NETWORK;
            } else if (driveInfo.strType == "Audio device") {   // 声卡
                itemIcon = ":/imgres/img_res/soundcard.svg";
                itemName = tr("Sound Card");
                uType = DRIVEINFOTYPE_AUDIO;
            } else if (driveInfo.strType == "Network controller") { //无线网卡
                itemIcon = ":/imgres/img_res/wireless.svg";
                itemName = tr("Wireless Network Card");
                uType = DRIVEINFOTYPE_WIFI;
            } else if (driveInfo.strType == "RAM memory" ||
                      driveInfo.strType == "SATA controller" ||
                       driveInfo.strType == "SMBus") { // 其他
                itemIcon = ":/imgres/img_res/monitor.svg";
                itemName = tr("Other");
                uType = DRIVEINFOTYPE_OTHER;
            } else {
                itemIcon = ":/imgres/img_res/monitor.svg";
                itemName = tr("Other");
                uType = DRIVEINFOTYPE_OTHER;
            }
            KDriveInfoItem *infoItem = new KDriveInfoItem(itemName, itemIcon, driveInfo.strName, driveInfo.strVersion, nCurIndex%2);
            infoItem->setMinimumHeight(40);
            infoItem->setFixedWidth(666);
            m_listLayout->addWidget(infoItem);
            if (m_mapItems.contains(uType)) {
                m_mapItems[uType].append(infoItem);
            } else {
                QList<KDriveInfoItem*> listItems;
                listItems.append(infoItem);
                m_mapItems[uType] = listItems;
            }
            nCurIndex++;
        }
    }
}

DI_TYPE DriveInfoPage::getDriveType(QString strType)
{
    if (strType == "Host bridge" ||
        strType == "Signal processing controller" ||
        strType == "USB controller" ||
        strType == "PCI bridge" ||
        strType == "SA bridge") { // 主板
        return DRIVEINFOTYPE_MOTHERBOCARD;
    } else if (strType == "VGA compatible controller") { // 显卡
        return DRIVEINFOTYPE_GRPHICS;
    } else if (strType == "Ethernet controller") {    // 网卡
        return DRIVEINFOTYPE_NETWORK;
    } else if (strType == "Audio device") {   // 声卡
        return DRIVEINFOTYPE_AUDIO;
    } else if (strType == "Network controller") { //无线网卡
        return DRIVEINFOTYPE_WIFI;
    } else if (strType == "RAM memory" ||
              strType == "SATA controller" ||
               strType == "SMBus") { // 其他
        return DRIVEINFOTYPE_OTHER;
    } else {
        return DRIVEINFOTYPE_OTHER;
    }
}

void DriveInfoPage::onUpdateInfo(QString strInfoJson)
{
    m_strInfoJson = strInfoJson;
    qInfo()<<"Drive Info:"<<m_strInfoJson;
    QTimer::singleShot(0, this, [&, this, strInfoJson](){
        this->updateInfoItems(strInfoJson);
    });
}

void DriveInfoPage::initConnections()
{
}

void DriveInfoPage::updateInfoItems(QString strInfoJson)
{
    if (strInfoJson.isEmpty())
        return;
    qInfo()<<"Cur info:"<<strInfoJson;
    QJsonParseError jsonParseErr;
    QJsonDocument  rootDoc = QJsonDocument::fromJson(strInfoJson.toUtf8(), &jsonParseErr);//字符串格式化为JSON
    if (jsonParseErr.error != QJsonParseError::NoError) {
        qWarning() << "JSON格式错误";
        return;
    } else {
         QJsonObject rootObj = rootDoc.object();
         if (rootObj.isEmpty()) {
             qWarning() << "JSON串为空";
             return;
         }
         QJsonValue valJson = rootObj.value(DRIVE_INFO);
         if (valJson.isArray()) {
             QJsonArray arrayJson = valJson.toArray();
             clearInfoItems();
             for (int n = 0; n < arrayJson.size(); n++) {
                 if (arrayJson.at(n).isObject()) {
                     QJsonObject subItemObj = arrayJson.at(n).toObject();
                     QJsonValue subItemValue = subItemObj.value(DRIVE_INFO_TYPE);
                     DriveInfo driveInfo;
                     if (subItemValue.isString()) {
                         driveInfo.strType = subItemValue.toString();
                     }
                     subItemValue = subItemObj.value(DRIVE_INFO_NAME);
                     if (subItemValue.isString()) {
                         driveInfo.strName = subItemValue.toString();
                     }
                     subItemValue = subItemObj.value(DRIVE_INFO_VERSION);
                     if (subItemValue.isString()) {
                         driveInfo.strVersion = subItemValue.toString();
                     }
                     DI_TYPE diType = getDriveType(driveInfo.strType);
                     if (m_mapDriveInfo.contains(diType)) {
                         bool isSameInfo = false;
                         for (int n = 0; n < m_mapDriveInfo[diType].size(); n++) {
                             if (m_mapDriveInfo[diType].at(n).strName == driveInfo.strName) {
                                 isSameInfo = true;
                                 break;
                             }
                         }
                         if (isSameInfo) {
                             continue;
                         }
                         m_mapDriveInfo[diType].append(driveInfo);
                     } else {
                         QList<DriveInfo> listDriveInfo;
                         listDriveInfo.append(driveInfo);
                         m_mapDriveInfo[diType] = listDriveInfo;
                     }
                 }
             }
             refreshInfoItems();
         }
    }
}
