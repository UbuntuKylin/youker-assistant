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

#include "infopage.h"
#include "dataworker.h"

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

InfoPage::InfoPage(QWidget *parent)
    : QWidget(parent)
{
    m_strInfoJson = "";
    initUI();
    initConnections();
}

void InfoPage::initUI()
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

void InfoPage::onUpdateInfo(QString strInfoJson)
{
    m_strInfoJson = strInfoJson;
    qInfo()<<"Machine Info11:"<<m_strInfoJson;
    QTimer::singleShot(0, this, [&, this, strInfoJson](){
        this->updateInfoItems(strInfoJson);
    });
}

void InfoPage::onUpdateInfo(unsigned uStatus, QString strInfoJson)
{
    if (strInfoJson.isEmpty()) {
        uStatus = 0;
    }
    if (uStatus == 1) {
        onUpdateInfo(strInfoJson);
    }
    Q_EMIT updateInfo(uStatus, strInfoJson);
}

void InfoPage::initConnections()
{
    // 连接更新信息信号
    connect(DataWorker::getInstance(), SIGNAL(updateOutline(uint,QString)), this, SLOT(onUpdateInfo(uint,QString)));
    DataWorker::getInstance()->connectOutlineSignal(true);
}

void InfoPage::addInfoItems(unsigned uId, QString strTitle, QString strIcon, QString strContent)
{
    if (strContent.isEmpty()) {
        return ;
    }
    if (m_mapItem.contains(uId)) {
        m_mapItem[uId]->updateDetailInfo(strContent);
    } else {
        KInfoListItem *listItem = new KInfoListItem(strTitle,
                                                    strIcon,
                                                    strContent, m_mapItem.size()%2);
        listItem->setMinimumHeight(40);
        listItem->setFixedWidth(666);
        m_listLayout->addWidget(listItem);
        m_mapItem[uId] = listItem;
    }
}

void InfoPage::clearInfoItems()
{
    QMap<unsigned, KInfoListItem*>::iterator itInfoItem = m_mapItem.begin();
    for (; itInfoItem != m_mapItem.end(); itInfoItem++) {
        if (itInfoItem.value()) {
            delete itInfoItem.value();
        }
    }
    m_mapItem.clear();
}

void InfoPage::updateInfoItems(QString strInfoJson)
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
         QJsonValue valJson = rootObj.value(MI_MANUFACTURER);
         if (valJson.isString()) {
             addInfoItems(MACHINEINFO_MANUFACTURER, tr("Manufacturer"),
                          ":/imgres/img_res/manufacturer.svg",
                          valJson.toString());
         }
         valJson = rootObj.value(MI_MACHINEMODEL);
         if (valJson.isString()) {
             addInfoItems(MACHINEINFO_MACHINEMODEL, tr("Machine Model"),
                          ":/imgres/img_res/Machine-model.svg",
                          valJson.toString());
         }
         valJson = rootObj.value(MI_SERIALNUM);
         if (valJson.isString()) {
             addInfoItems(MACHINEINFO_SERIALNUM, tr("Serial Number"),
                          ":/imgres/img_res/SN.svg",
                          valJson.toString());
         }
         valJson = rootObj.value(MI_SYSTEMBITS);
         if (valJson.isString()) {
             addInfoItems(MACHINEINFO_SYSTEMBITS, tr("System Bits"),
                          ":/imgres/img_res/system-bits.svg",
                          valJson.toString());
         }
         valJson = rootObj.value(MI_KERNELARCH);
         if (valJson.isString()) {
             addInfoItems(MACHINEINFO_KERNELARCH, tr("Kernel Arch"),
                          ":/imgres/img_res/kernel-architecture.svg",
                          valJson.toString());
         }
         valJson = rootObj.value(MI_HOSTNAME);
         if (valJson.isString()) {
             addInfoItems(MACHINEINFO_HOSTNAME, tr("Host Name"),
                          ":/imgres/img_res/host.svg",
                          valJson.toString());
         }
         valJson = rootObj.value(MI_OSVERSION);
         if (valJson.isString()) {
             addInfoItems(MACHINEINFO_OSVERSION, tr("OS Version"),
                          ":/imgres/img_res/osversion.svg",
                          valJson.toString());
         }
         valJson = rootObj.value(MI_KERNELVERSION);
         if (valJson.isString()) {
             addInfoItems(MACHINEINFO_KERNELVERSION, tr("Kernel Version"),
                          ":/imgres/img_res/kernel-version.svg",
                          valJson.toString());
         }
         valJson = rootObj.value(MI_PROCESSOR);
         if (valJson.isString()) {
             addInfoItems(MACHINEINFO_PROCESSOR, tr("Processor"),
                          ":/imgres/img_res/processor.svg",
                          valJson.toString());
         }
         valJson = rootObj.value(MI_MEMORY);
         if (valJson.isString()) {
             addInfoItems(MACHINEINFO_MEMORY, tr("Memory"),
                          ":/imgres/img_res/memory.svg",
                          valJson.toString());
         }
         valJson = rootObj.value(MI_MAINBOARD);
         if (valJson.isString()) {
             addInfoItems(MACHINEINFO_MAINBOARD, tr("Mother Board"),
                          ":/imgres/img_res/mother-board.svg",
                          valJson.toString());
         }
         valJson = rootObj.value(MI_HARDDISK);
         if (valJson.isString()) {
             addInfoItems(MACHINEINFO_HARDDISK, tr("Hard Disk"),
                          ":/imgres/img_res/hard-disk.svg",
                          valJson.toString());
         }
         valJson = rootObj.value(MI_GRAPHICSCARD);
         if (valJson.isString()) {
             addInfoItems(MACHINEINFO_GRAPHICSCARD, tr("Graphics Card"),
                          ":/imgres/img_res/graphics-card.svg",
                          valJson.toString());
         }
         valJson = rootObj.value(MI_MONITOR);
         if (valJson.isString()) {
             addInfoItems(MACHINEINFO_MONITOR, tr("Monitor"),
                          ":/imgres/img_res/monitor.svg",
                          valJson.toString());
         }
         valJson = rootObj.value(MI_NETWORKCARD);
         if (valJson.isString()) {
             addInfoItems(MACHINEINFO_NETWORKCARD, tr("Network Card"),
                          ":/imgres/img_res/network-card.svg",
                          valJson.toString());
         }
         valJson = rootObj.value(MI_SOUNDCARD);
         if (valJson.isString()) {
             addInfoItems(MACHINEINFO_SOUNDCARD, tr("Sound Card"),
                          ":/imgres/img_res/soundcard.svg",
                          valJson.toString());
         }
    }
}

void InfoPage::onRefreshInfo()
{
    DataWorker::getInstance()->getOutline();
}
