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

#include "motherboardinfo.h"
#include "dataworker.h"

#include <QDebug>
#include <QTimer>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>

MotherBoardInfo::MotherBoardInfo(QWidget *parent)
    : KABaseInfoPage(parent)
{
    m_strInfoJson = "";
    initUI();
    initConnections();
}

void MotherBoardInfo::initUI()
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

void MotherBoardInfo::onUpdateInfo(QString strInfoJson)
{
    m_strInfoJson = strInfoJson;
    qInfo()<<"MotherBoardInfo Info:"<<m_strInfoJson;
    QTimer::singleShot(0, this, [&, this, strInfoJson](){
        this->updateInfoItems(strInfoJson);
        this->chkNoDevice();
    });
}

void MotherBoardInfo::initConnections()
{
    connect(DataWorker::getInstance(), SIGNAL(updateMotherBoardInfo(uint,QString)), this, SLOT(onUpdateInfo(uint,QString)));
}

void MotherBoardInfo::clearInfoItems()
{
    QMap<unsigned, KInfoListItem*>::iterator itInfoItem = m_mapItem.begin();
    for (; itInfoItem != m_mapItem.end(); itInfoItem++) {
        if (itInfoItem.value()) {
            delete itInfoItem.value();
        }
    }
    m_mapItem.clear();
}

void MotherBoardInfo::addInfoItems(unsigned uId, QString strTitle, QString strContent)
{
    if(strContent.isEmpty())
        return;
    if (m_mapItem.contains(uId)) {
        m_mapItem[uId]->updateDetailInfo(strContent);
    } else {
        KInfoListItem *listItem = new KInfoListItem(strTitle, "", strContent, m_mapItem.size()%2);
        listItem->setMinimumHeight(40);
        listItem->setFixedWidth(666);
        m_listLayout->addWidget(listItem);
        m_mapItem[uId] = listItem;
    }
}

void MotherBoardInfo::updateInfoItems(QString strInfoJson)
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
         clearInfoItems();
         QJsonValue valJson = rootObj.value(MBI_NAME);
         if (valJson.isString()) {
             addInfoItems(MOTHERBOARDINFO_NAME, tr("Name"), valJson.toString());
         }
         valJson = rootObj.value(MBI_MANUFACTURER);
         if (valJson.isString()) {
             addInfoItems(MOTHERBOARDINFO_MANUFACTURER, tr("Manufacturer"), valJson.toString());
         }
         valJson = rootObj.value(MBI_VERSION);
         if (valJson.isString()) {
             addInfoItems(MOTHERBOARDINFO_VERSION, tr("Version"), valJson.toString());
         }
         valJson = rootObj.value(MBI_CHIPSET);
         if (valJson.isString()) {
             addInfoItems(MOTHERBOARDINFO_CHIPSET, tr("Chipset"), valJson.toString());
         }
         valJson = rootObj.value(MBI_SERIALNUM);
         if (valJson.isString()) {
             addInfoItems(MOTHERBOARDINFO_SERIALNUM, tr("Serial Num"), valJson.toString());
         }
         valJson = rootObj.value(MBI_PUBDATE);
         if (valJson.isString()) {
             addInfoItems(MOTHERBOARDINFO_PUBDATE, tr("Publish Date"), valJson.toString());
         }
         valJson = rootObj.value(MBI_BIOSMANUFACTURER);
         if (valJson.isString()) {
             addInfoItems(MOTHERBOARDINFO_BIOSMANUFACTURER, tr("BIOS Manufacturer"), valJson.toString());
         }
         valJson = rootObj.value(MBI_BIOSVERSION);
         if (valJson.isString()) {
             addInfoItems(MOTHERBOARDINFO_BIOSVERSION, tr("BIOS Version"), valJson.toString());
         }
    }
}

void MotherBoardInfo::onRefreshInfo()
{
    DataWorker::getInstance()->getMotherBoardInfo();
}

void MotherBoardInfo::chkNoDevice()
{
    if (m_mapItem.size() == 0) {
        addInfoItems(MOTHERBOARDINFO_INVALID, "", tr("Device not exitst or Get Device is Empty"));
    }
}
