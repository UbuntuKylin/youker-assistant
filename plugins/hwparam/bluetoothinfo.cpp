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

#include "bluetoothinfo.h"
#include "dataworker.h"

#include <QDebug>
#include <QTimer>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

BluetoothInfo::BluetoothInfo(QWidget *parent)
    : KABaseInfoPage(parent)
{
    m_strInfoJson = "";
    initUI();
    initConnections();
}

void BluetoothInfo::initUI()
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

void BluetoothInfo::onUpdateInfo(QString strInfoJson)
{
    m_strInfoJson = strInfoJson;
    qInfo()<<"Bluetooth Info:"<<m_strInfoJson;
    QTimer::singleShot(0, this, [&, this, strInfoJson](){
        this->updateInfoItems(strInfoJson);
        this->chkNoDevice();
    });
}

void BluetoothInfo::initConnections()
{
    connect(DataWorker::getInstance(), SIGNAL(updateBluetoothInfo(uint,QString)), this, SLOT(onUpdateInfo(uint,QString)));
}

void BluetoothInfo::clearInfoItems()
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

void BluetoothInfo::addInfoItems(unsigned uGroup, unsigned uId, QString strTitle, QString strContent, bool bMulti)
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
            KAInfoTitle *infoTitle = new KAInfoTitle(QString("%1%2").arg(tr("Bluetooth")).arg(m_mapInfoItems.size()+1));
            infoTitle->setMinimumHeight(40);
            infoTitle->setFixedWidth(666);
            m_listLayout->addWidget(infoTitle);
            mapItems[BLUETOOTHINFO_TITLE] = infoTitle;
        }
        KInfoListItem *listItem = new KInfoListItem(strTitle, "", strContent, 0);
        listItem->setMinimumHeight(40);
        listItem->setFixedWidth(666);
        m_listLayout->addWidget(listItem);
        mapItems[uId] = listItem;
        m_mapInfoItems[uGroup] = mapItems;
    }
}

void BluetoothInfo::updateInfoItems(QString strInfoJson)
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
                    QJsonValue subItemValue = subItemObj.value(BLI_BUSADDR);
                    if (subItemValue.isString()) {
                        addInfoItems(n, BLUETOOTHINFO_BUSADDR, tr("Bus Address"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(BLI_FUNCTION);
                    if (subItemValue.isString()) {
                        addInfoItems(n, BLUETOOTHINFO_FUNCTION, tr("Function"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(BLI_FREQ);
                    if (subItemValue.isString()) {
                        addInfoItems(n, BLUETOOTHINFO_FREQ, tr("Frequency"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(BLI_CONF);
                    if (subItemValue.isString()) {
                        addInfoItems(n, BLUETOOTHINFO_CONF, tr("Configuration"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(BLI_DEVTYPE);
                    if (subItemValue.isString()) {
                        addInfoItems(n, BLUETOOTHINFO_DEVTYPE, tr("Type"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(BLI_ID);
                    if (subItemValue.isString()) {
                        addInfoItems(n, BLUETOOTHINFO_ID, tr("ID"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(BLI_DEVMODEL);
                    if (subItemValue.isString()) {
                        addInfoItems(n, BLUETOOTHINFO_DEVMODEL, tr("Model"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(BLI_RESOURCE);
                    if (subItemValue.isString()) {
                        addInfoItems(n, BLUETOOTHINFO_RESOURCE, tr("Resource"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(BLI_MANUFACTURER);
                    if (subItemValue.isString()) {
                        addInfoItems(n, BLUETOOTHINFO_MANUFACTURER, tr("Manufacturer"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(BLI_DEVVERSION);
                    if (subItemValue.isString()) {
                        addInfoItems(n, BLUETOOTHINFO_DEVVERSION, tr("Version"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(BLI_DATAWIDTH);
                    if (subItemValue.isString()) {
                        addInfoItems(n, BLUETOOTHINFO_DATAWIDTH, tr("Data Width"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(BLI_NAME);
                    if (subItemValue.isString()) {
                        addInfoItems(n, BLUETOOTHINFO_NAME, tr("Name"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(BLI_DRIVER);
                    if (subItemValue.isString()) {
                        addInfoItems(n, BLUETOOTHINFO_DRIVER, tr("Driver"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(BLI_SPEED);
                    if (subItemValue.isString()) {
                        addInfoItems(n, BLUETOOTHINFO_SPEED, tr("Speed"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(BLI_SERIALNUM);
                    if (subItemValue.isString()) {
                        addInfoItems(n, BLUETOOTHINFO_SERIALNUM, tr("Serial Number"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(BLI_ADDRESS);
                    if (subItemValue.isString()) {
                        addInfoItems(n, BLUETOOTHINFO_ADDRESS, tr("Address"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(BLI_LINKMODE);
                    if (subItemValue.isString()) {
                        addInfoItems(n, BLUETOOTHINFO_LINKMODE, tr("Link Mode"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(BLI_LINKPOLICY);
                    if (subItemValue.isString()) {
                        addInfoItems(n, BLUETOOTHINFO_LINKPOLICY, tr("Link Policy"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(BLI_CAPABILITIES);
                    if (subItemValue.isString()) {
                        addInfoItems(n, BLUETOOTHINFO_CAPABILITIES, tr("Capabilities"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(BLI_BUS);
                    if (subItemValue.isString()) {
                        addInfoItems(n, BLUETOOTHINFO_BUS, tr("Bus"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(BLI_SCOMTU);
                    if (subItemValue.isString()) {
                        addInfoItems(n, BLUETOOTHINFO_SCOMTU, tr("SCO MTU"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(BLI_ALCMTU);
                    if (subItemValue.isString()) {
                        addInfoItems(n, BLUETOOTHINFO_ALCMTU, tr("ALC MTU"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(BLI_PACKETTYPE);
                    if (subItemValue.isString()) {
                        addInfoItems(n, BLUETOOTHINFO_PACKETTYPE, tr("Packet Type"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(BLI_FEATURES);
                    if (subItemValue.isString()) {
                        addInfoItems(n, BLUETOOTHINFO_FEATURES, tr("Features"), subItemValue.toString(), bMulti);
                    }
                }
            }
         }
    }
}

void BluetoothInfo::onRefreshInfo()
{
    DataWorker::getInstance()->getBluetoothInfo();
}

void BluetoothInfo::chkNoDevice()
{
    unsigned infoSize = 0;
    QMap<unsigned,QMap<unsigned, QWidget*>>::iterator itMapInfoItems = m_mapInfoItems.begin();
    for (;itMapInfoItems != m_mapInfoItems.end(); itMapInfoItems++) {
        infoSize += itMapInfoItems.value().size();
    }
    if (infoSize == 0) {
        addInfoItems(0, BLUETOOTHINFO_INVALID, "", tr("Device not exitst or Get Device is Empty"), false);
    }
}
