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

#include "netcardinfo.h"
#include "dataworker.h"

#include <QDebug>
#include <QTimer>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

NetCardInfo::NetCardInfo(QWidget *parent)
    : KABaseInfoPage(parent)
{
    m_strInfoJson = "";
    initUI();
    initConnections();
}

void NetCardInfo::initUI()
{
    m_mainLayout = new QVBoxLayout();
    m_mainLayout->setContentsMargins(0,0,0,0);
    m_mainLayout->setSpacing(0);
    m_listLayout = new QVBoxLayout();
    m_listLayout->setContentsMargins(0,0,0,0);
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

void NetCardInfo::onUpdateInfo(QString strInfoJson)
{
    m_strInfoJson = strInfoJson;
    qInfo()<<"NetCardInfo Info:"<<m_strInfoJson;
    QTimer::singleShot(0, this, [&, this, strInfoJson](){
        this->updateInfoItems(strInfoJson);
        this->chkNoDevice();
    });
}

void NetCardInfo::initConnections()
{
    connect(DataWorker::getInstance(), SIGNAL(updateNetworkCardInfo(uint,QString)), this, SLOT(onUpdateInfo(uint,QString)));
}

void NetCardInfo::clearInfoItems()
{
    QMap<unsigned,QMap<unsigned, QWidget*>>::iterator itMapInfoItems = m_mapInfoItems.begin();
    for (;itMapInfoItems != m_mapInfoItems.end(); itMapInfoItems++) {
        QMap<unsigned, QWidget*>::iterator itInfoItems = itMapInfoItems.value().begin();
        for (;itInfoItems != itMapInfoItems.value().end(); itInfoItems++) {
            if (itInfoItems.value()) {
                delete itInfoItems.value();
            }
        }
        itMapInfoItems.value().clear();
    }
    m_mapInfoItems.clear();
}

void NetCardInfo::addInfoItems(unsigned uGroup, unsigned uId, QString strTitle, QString strContent, bool bMulti)
{
    if (m_mapInfoItems.contains(uGroup)) {
        QMap<unsigned,QMap<unsigned, QWidget*>>::iterator itMapInfoItems = m_mapInfoItems.find(uGroup);
        if (itMapInfoItems != m_mapInfoItems.end()) {
            if (itMapInfoItems.value().contains(uId)) {
                KInfoListItem *listItem = qobject_cast<KInfoListItem *>(itMapInfoItems.value()[uId]);
                if (listItem) {
                    listItem->updateDetailInfo(strContent);
                }
            } else {
                bool isSigleLine = true;
                if (bMulti) {
                    isSigleLine = (itMapInfoItems.value().size()-1)%2;
                } else {
                    isSigleLine = itMapInfoItems.value().size()%2;
                }
                KInfoListItem *listItem = new KInfoListItem(strTitle, "", strContent, isSigleLine);
                listItem->setMinimumHeight(40);
                listItem->setFixedWidth(666);
                m_listLayout->addWidget(listItem);
                itMapInfoItems.value()[uId] = listItem;
            }
        }
    } else {
        QMap<unsigned, QWidget*> mapItems;
        if (bMulti) {
            KAInfoTitle *infoTitle = new KAInfoTitle(QString("%1%2").arg(tr("Network Card")).arg(m_mapInfoItems.size()+1));
            infoTitle->setMinimumHeight(40);
            infoTitle->setFixedWidth(666);
            m_listLayout->addWidget(infoTitle);
            mapItems[NETCARDINFO_TITLE] = infoTitle;
        }
        KInfoListItem *listItem = new KInfoListItem(strTitle, "", strContent, 0);
        listItem->setMinimumHeight(40);
        listItem->setFixedWidth(666);
        m_listLayout->addWidget(listItem);
        mapItems[uId] = listItem;
        m_mapInfoItems[uGroup] = mapItems;
    }
}

void NetCardInfo::updateInfoItems(QString strInfoJson)
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
         QJsonValue valJson = rootObj.value("list");
         if (valJson.isArray()) {
            QJsonArray arrayJson = valJson.toArray();
            clearInfoItems();
            bool bMulti = false;
            if (arrayJson.size() > 1) {
                bMulti = true;
            }
            for (int n = 0; n < arrayJson.size(); n++) {
                if (arrayJson.at(n).isObject()) {
                    QJsonObject subItemObj = arrayJson.at(n).toObject();
                    QJsonValue subItemValue = subItemObj.value(NWI_NAME);
                    if (subItemValue.isString()) {
                        addInfoItems(n, NETCARDINFO_NAME, tr("Name"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(NWI_TYPE);
                    if (subItemValue.isString()) {
                        QString strType = subItemValue.toString();
                        if (strType.contains("Ethernet", Qt::CaseInsensitive)) {
                            addInfoItems(n, NETCARDINFO_ISWIFI, tr("Type"), tr("Wired"), bMulti);
                        } else if (strType.contains("Wireless", Qt::CaseInsensitive)) {
                            addInfoItems(n, NETCARDINFO_ISWIFI, tr("Type"), tr("Wireless"), bMulti);
                        } else {
                            addInfoItems(n, NETCARDINFO_ISWIFI, tr("Type"), strType, bMulti);
                        }
                    }
                    subItemValue = subItemObj.value(NWI_MANUFACTURER);
                    if (subItemValue.isString()) {
                        addInfoItems(n, NETCARDINFO_MANUFACTURER, tr("Manufacturer"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(NWI_BUSADDR);
                    if (subItemValue.isString()) {
                        addInfoItems(n, NETCARDINFO_BUSADDR, tr("Bus Address"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(NWI_MACADDR);
                    if (subItemValue.isString()) {
                        addInfoItems(n, NETCARDINFO_MACADDR, tr("MAC"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(NWI_DRIVER);
                    if (subItemValue.isString()) {
                        addInfoItems(n, NETCARDINFO_DRIVER, tr("Driver"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(NWI_CONNSPEED);
                    if (subItemValue.isString()) {
                        addInfoItems(n, NETCARDINFO_CONNSPEED, tr("Link Speed"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(NWI_MTU);
                    if (subItemValue.isString()) {
                        addInfoItems(n, NETCARDINFO_MTU, tr("MTU"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(NWI_IPADDR);
                    if (subItemValue.isString()) {
                        addInfoItems(n, NETCARDINFO_IPADDR, tr("IP"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(NWI_MODEL);
                    if (subItemValue.isString()) {
                        addInfoItems(n, NETCARDINFO_MODEL, tr("Model"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(NWI_SUBNETMASK);
                    if (subItemValue.isString()) {
                        addInfoItems(n, NETCARDINFO_SUBNETMASK, tr("Subnet Mask"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(NWI_GATEWAY);
                    if (subItemValue.isString()) {
                        addInfoItems(n, NETCARDINFO_GATEWAY, tr("Gateway"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(NWI_DNSSERVER);
                    if (subItemValue.isString()) {
                        addInfoItems(n, NETCARDINFO_DNSSERVER, tr("DNS Server"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(NWI_RECVBYTES);
                    if (subItemValue.isString()) {
                        addInfoItems(n, NETCARDINFO_RECVBYTES, tr("Bytes Received"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(NWI_SENDBYTES);
                    if (subItemValue.isString()) {
                        addInfoItems(n, NETCARDINFO_SENDBYTES, tr("Bytes Sent"), subItemValue.toString(), bMulti);
                    }
                }
            }
         }
    }
}

void NetCardInfo::onRefreshInfo()
{
    DataWorker::getInstance()->getNetworkCardInfo();
}

void NetCardInfo::chkNoDevice()
{
    unsigned infoSize = 0;
    QMap<unsigned,QMap<unsigned, QWidget*>>::iterator itMapInfoItems = m_mapInfoItems.begin();
    for (;itMapInfoItems != m_mapInfoItems.end(); itMapInfoItems++) {
        infoSize += itMapInfoItems.value().size();
    }
    if (infoSize == 0) {
        addInfoItems(0, NETCARDINFO_INVALID, "", tr("Device not exitst or Get Device is Empty"), false);
    }
}
