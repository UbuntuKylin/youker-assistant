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

#include "processorinfo.h"
#include "dataworker.h"

#include <QDebug>
#include <QTimer>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>

ProcessorInfo::ProcessorInfo(QWidget *parent)
    : KABaseInfoPage(parent)
{
    m_strInfoJson = "";
    initUI();
    initConnections();
}

void ProcessorInfo::initUI()
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

void ProcessorInfo::onUpdateInfo(QString strInfoJson)
{
    m_strInfoJson = strInfoJson;
    qInfo()<<"processorinfo Info:"<<m_strInfoJson;
    QTimer::singleShot(0, this, [&, this, strInfoJson](){
        this->updateInfoItems(strInfoJson);
    });
}

void ProcessorInfo::initConnections()
{
    connect(DataWorker::getInstance(), SIGNAL(updateProcessorInfo(uint,QString)), this, SLOT(onUpdateInfo(uint,QString)));
}

void ProcessorInfo::clearInfoItems()
{
    QMap<unsigned, KInfoListItem*>::iterator itInfoItem = m_mapItem.begin();
    for (; itInfoItem != m_mapItem.end(); itInfoItem++) {
        if (itInfoItem.value()) {
            delete itInfoItem.value();
        }
    }
    m_mapItem.clear();
}

void ProcessorInfo::addInfoItems(unsigned uId, QString strTitle, QString strContent)
{
    if (strContent.isEmpty())
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

void ProcessorInfo::updateInfoItems(QString strInfoJson)
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
         QJsonValue valJson = rootObj.value(PSI_PROCESSOR);
         if (valJson.isString()) {
             addInfoItems(PROCESSORINFO_PROCESSOR, tr("Processor"), valJson.toString());
         }
         valJson = rootObj.value(PSI_MANUFACTURER);
         if (valJson.isString()) {
             addInfoItems(PROCESSORINFO_MANUFACTURER, tr("Manufacturer"), valJson.toString());
         }
         valJson = rootObj.value(PSI_ARCH);
         if (valJson.isString()) {
             addInfoItems(PROCESSORINFO_ARCH, tr("Architecture"), valJson.toString());
         }
         valJson = rootObj.value(PSI_CORESNUM);
         if (valJson.isString()) {
             addInfoItems(PROCESSORINFO_CORESNUM, tr("Core Num"), valJson.toString());
         }
         valJson = rootObj.value(PSI_CORESONLINE);
         if (valJson.isString()) {
             addInfoItems(PROCESSORINFO_CORESONLINE, tr("Core Online Num"), valJson.toString());
         }
         valJson = rootObj.value(PSI_THREADSNUM);
         if (valJson.isString()) {
             addInfoItems(PROCESSORINFO_THREADSNUM, tr("Thread"), valJson.toString());
         }
         valJson = rootObj.value(PSI_SLOT);
         if (valJson.isString()) {
             addInfoItems(PROCESSORINFO_SLOT, tr("Slot"), valJson.toString());
         }
         valJson = rootObj.value(PSI_FREQ_MAX);
         if (valJson.isString()) {
             addInfoItems(PROCESSORINFO_FREQMAX, tr("Max Frequency"), valJson.toString());
         }
         valJson = rootObj.value(PSI_FREQ);
         if (valJson.isString()) {
             addInfoItems(PROCESSORINFO_FREQ, tr("Frequency"), valJson.toString());
         }
         valJson = rootObj.value(PSI_L1CACHE);
         if (valJson.isString()) {
             addInfoItems(PROCESSORINFO_L1CACHE, tr("L1 Cache"), valJson.toString());
         }
         valJson = rootObj.value(PSI_L1DCACHE);
         if (valJson.isString()) {
             addInfoItems(PROCESSORINFO_L1DCACHE, tr("L1d Cache"), valJson.toString());
         }
         valJson = rootObj.value(PSI_L1ICACHE);
         if (valJson.isString()) {
             addInfoItems(PROCESSORINFO_L1ICACHE, tr("L1i Cache"), valJson.toString());
         }
         valJson = rootObj.value(PSI_L2CACHE);
         if (valJson.isString()) {
             addInfoItems(PROCESSORINFO_L2CACHE, tr("L2 Cache"), valJson.toString());
         }
         valJson = rootObj.value(PSI_L3CACHE);
         if (valJson.isString()) {
             addInfoItems(PROCESSORINFO_L3CACHE, tr("L3 Cache"), valJson.toString());
         }
         valJson = rootObj.value(PSI_INSTSET);
         if (valJson.isString()) {
             addInfoItems(PROCESSORINFO_INSTSET, tr("Instruction Set"), valJson.toString());
         }
         valJson = rootObj.value(PSI_EXTINSTSET);
         if (valJson.isString()) {
             addInfoItems(PROCESSORINFO_EXTINSTSET, tr("EXT Instruction Set"), valJson.toString());
         }
         valJson = rootObj.value(PSI_USED);
         if (valJson.isString()) {
             addInfoItems(PROCESSORINFO_USED, tr("Used"), valJson.toString());
         }
    }
}

void ProcessorInfo::onRefreshInfo()
{
    DataWorker::getInstance()->getProcessorInfo();
}
