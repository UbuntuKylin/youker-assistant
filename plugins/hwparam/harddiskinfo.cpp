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

#include "harddiskinfo.h"
#include "dataworker.h"

#include <QDebug>
#include <QTimer>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

HardDiskInfo::HardDiskInfo(QWidget *parent)
    : KABaseInfoPage(parent)
{
    m_strInfoJson = "";
    initUI();
    initConnections();
}

void HardDiskInfo::initUI()
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

void HardDiskInfo::onUpdateInfo(QString strInfoJson)
{
    m_strInfoJson = strInfoJson;
    qInfo()<<"HardDisk Info:"<<m_strInfoJson;
    QTimer::singleShot(0, this, [&, this, strInfoJson](){
        this->updateInfoItems(strInfoJson);
        this->chkNoDevice();
    });
}

void HardDiskInfo::initConnections()
{
    connect(DataWorker::getInstance(), SIGNAL(updateHardDiskInfo(unsigned, QString)), this, SLOT(onUpdateInfo(unsigned, QString)));
}

void HardDiskInfo::clearInfoItems()
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

void HardDiskInfo::addInfoItems(unsigned uGroup, unsigned uId, QString strTitle, QString strContent, bool bMulti)
{
    if (strContent.isEmpty())
        return;
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
            KAInfoTitle *infoTitle = new KAInfoTitle(QString("%1%2").arg(tr("Hard Disk Info")).arg(m_mapInfoItems.size()+1));
            infoTitle->setMinimumHeight(40);
            infoTitle->setFixedWidth(666);
            m_listLayout->addWidget(infoTitle);
            mapItems[HARDDISKINFO_TITLE] = infoTitle;
        }
        KInfoListItem *listItem = new KInfoListItem(strTitle, "", strContent, 0);
        listItem->setMinimumHeight(40);
        listItem->setFixedWidth(666);
        m_listLayout->addWidget(listItem);
        mapItems[uId] = listItem;
        m_mapInfoItems[uGroup] = mapItems;
    }
}

void HardDiskInfo::updateInfoItems(QString strInfoJson)
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
                    QJsonValue subItemValue = subItemObj.value(HDI_MANUFACTURER);
                    if (subItemValue.isString()) {
                        addInfoItems(n, HARDDISKINFO_MANUFACTURER, tr("Manufacturer"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(HDI_NAME);
                    if (subItemValue.isString()) {
                        addInfoItems(n, HARDDISKINFO_NAME, tr("Name"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(HDI_CAPACITY);
                    if (subItemValue.isString()) {
                        addInfoItems(n, HARDDISKINFO_CAPACITY, tr("Capacity"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(HDI_USEDTIMES);
                    if (subItemValue.isString()) {
                        addInfoItems(n, HARDDISKINFO_USEDTIMES, tr("Used Times"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(HDI_INTERFACE);
                    if (subItemValue.isString()) {
                        addInfoItems(n, HARDDISKINFO_INTERFACE, tr("Interface"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(HDI_ISMAINDISK);
                    if (subItemValue.isString()) {
                        QString strYesOrNo = "";
                        if (subItemValue.toString() == "1") {
                            strYesOrNo = tr("Yes");
                        } else {
                            strYesOrNo = tr("No");
                        }
                        addInfoItems(n, HARDDISKINFO_ISMAINDISK, tr("Main Disk"), strYesOrNo, bMulti);
                    }
                    subItemValue = subItemObj.value(HDI_ISSSD);
                    if (subItemValue.isString()) {
                        QString strSsd = "";
                        if (subItemValue.toString() == "1") {
                            strSsd = tr("SSD");
                        } else {
                            strSsd = tr("HDD");
                        }
                        addInfoItems(n, HARDDISKINFO_ISSSD, tr("Type"), strSsd, bMulti);
                    }
                    subItemValue = subItemObj.value(HDI_SERIALNUM);
                    if (subItemValue.isString()) {
                        addInfoItems(n, HARDDISKINFO_SERIALNUM, tr("Serial Num"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(HDI_MODEL);
                    if (subItemValue.isString()) {
                        addInfoItems(n, HARDDISKINFO_MODEL, tr("Model"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(HDI_TRANSRATE);
                    if (subItemValue.isString()) {
                        addInfoItems(n, HARDDISKINFO_TRANSRATE, tr("Transfer Rate"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(HDI_READSPEED);
                    if (subItemValue.isString()) {
                        addInfoItems(n, HARDDISKINFO_READSPEED, tr("Read Speed"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(HDI_WRITESPEED);
                    if (subItemValue.isString()) {
                        addInfoItems(n, HARDDISKINFO_WRITESPEED, tr("Write Speed"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(HDI_FIRMWAREVER);
                    if (subItemValue.isString()) {
                        addInfoItems(n, HARDDISKINFO_FIRMWAREVER, tr("Firmware Version"), subItemValue.toString(), bMulti);
                    }
                }
            }
         }
    }
}

void HardDiskInfo::onRefreshInfo()
{
    DataWorker::getInstance()->getHardDiskInfo();
}

void HardDiskInfo::chkNoDevice()
{
    unsigned infoSize = 0;
    QMap<unsigned,QMap<unsigned, QWidget*>>::iterator itMapInfoItems = m_mapInfoItems.begin();
    for (;itMapInfoItems != m_mapInfoItems.end(); itMapInfoItems++) {
        infoSize += itMapInfoItems.value().size();
    }
    if (infoSize == 0) {
        addInfoItems(0, HARDDISKINFO_INVALID, "", tr("Device not exitst or Get Device is Empty"), false);
    }
}
