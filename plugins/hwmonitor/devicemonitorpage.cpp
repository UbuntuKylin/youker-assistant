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

#include "devicemonitorpage.h"

#include "../../src/commondef.h"
#include "../../src/kajsondef.h"
#include "dataworker.h"

#include <QDebug>
#include <QTimer>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

DeviceMonitorPage::DeviceMonitorPage(QWidget *parent)
    : QWidget(parent)
{
    initUI();
    initConnections();
}

DeviceMonitorPage::~DeviceMonitorPage()
{
    clearInfoItems();
}

void DeviceMonitorPage::initUI()
{
    m_listStatus << tr("The equipment is normal and the heat dissipation is good")
                 << tr("Equipment temperature is high, please pay attention to heat dissipation")
                 << tr("Equipment temperature is abnormal, please pay attention to heat dissipation");
    m_mainLayout = new QVBoxLayout();
    m_mainLayout->setContentsMargins(0,0,0,0);
    m_mainLayout->setSpacing(0);
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_tempLayout = new QVBoxLayout();
    m_tempLayout->setContentsMargins(0,0,0,0);
    m_tempLayout->setSpacing(0);
    m_tempLayout->setAlignment(Qt::AlignTop);
    m_usageLayout = new QVBoxLayout();
    m_usageLayout->setContentsMargins(0,0,0,0);
    m_usageLayout->setSpacing(0);
    m_usageLayout->setAlignment(Qt::AlignTop);

    m_scrollLayout = new QVBoxLayout();
    m_scrollLayout->setContentsMargins(0,0,0,0);
    m_scrollLayout->setSpacing(0);
    m_scrollLayout->setAlignment(Qt::AlignTop);
    m_scrollWidget = new QFrame();
    m_scrollWidget->setLayout(m_scrollLayout);
    m_scrollFrame = new QScrollArea();
    m_scrollFrame->setContentsMargins(0, 0, 0, 0);
    m_scrollFrame->setBackgroundRole(QPalette::Base);
    m_scrollFrame->setAutoFillBackground(true);
    m_scrollFrame->setFrameStyle(0);
    m_scrollFrame->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollFrame->setWidgetResizable(true);
    m_scrollFrame->setWidget(m_scrollWidget);

    m_tempTitle = new QLabel();
    m_tempTitle->setFixedWidth(666);
    m_tempTitle->setWordWrap(true);
    m_tempTitle->setText(m_listStatus[0]);
    m_tempTitleLayout = new QHBoxLayout();
    m_tempTitleLayout->setContentsMargins(0,0,0,0);
    m_tempTitleLayout->setSpacing(0);
    m_tempTitleLayout->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    m_tempTitleLayout->addWidget(m_tempTitle);
    m_tempContentLayout = new QHBoxLayout();
    m_tempContentLayout->setContentsMargins(0,0,16,0);
    m_tempContentLayout->setSpacing(16);
    m_tempContentLayout->setAlignment(Qt::AlignLeft|Qt::AlignTop);

    m_tempLayout->addLayout(m_tempTitleLayout);
    m_tempLayout->addSpacing(16);
    m_tempLayout->addLayout(m_tempContentLayout);

    m_usageLayout->setSpacing(32);

    m_scrollLayout->addSpacing(32);
    m_scrollLayout->addLayout(m_tempLayout);
    m_scrollLayout->addSpacing(32);
    m_scrollLayout->addLayout(m_usageLayout);
    m_scrollLayout->addStretch();
    m_mainLayout->addWidget(m_scrollFrame);
    this->setLayout(m_mainLayout);
    initStyleTheme();
}

void DeviceMonitorPage::initStyleTheme()
{
    const QByteArray idd(THEME_QT_SCHEMA);
    if(QGSettings::isSchemaInstalled(idd)) {
        m_styleSettings = new QGSettings(idd);
    }
    if (m_styleSettings) {
        connect(m_styleSettings, &QGSettings::changed, this, [=](const QString &key) {
            if (key == "systemFontSize" || key == "systemFont") {
                qDebug()<<"style font changed";
                auto styleFontSizeValue = m_styleSettings->get("systemFontSize");
                if (styleFontSizeValue.isValid()) {
                    float fFontSize = styleFontSizeValue.toFloat();
                    QFont font = m_tempTitle->font();
                    font.setPointSize(fFontSize+2);
                    m_tempTitle->setFont(font);
                }
            }
        });
        auto styleFontSizeValue = m_styleSettings->get("systemFontSize");
        if (styleFontSizeValue.isValid()) {
            float fFontSize = styleFontSizeValue.toFloat();
            QFont font = m_tempTitle->font();
            font.setPointSize(fFontSize+2);
            m_tempTitle->setFont(font);
        }
    }
}

void DeviceMonitorPage::initConnections()
{
    // 连接dbus信号
    DataWorker::getInstance()->connectDevMonitorInfoSignal();
    connect(DataWorker::getInstance(), SIGNAL(updateDevMonitorInfo(unsigned, QString)), this, SLOT(onUpdateInfo(unsigned, QString)));
}

void DeviceMonitorPage::refreshInfo()
{
    DataWorker::getInstance()->getDevMonitorInfo();
    checkTempStatus();
}

void DeviceMonitorPage::clearInfoItems()
{
    QMap<QString, QWidget*>::iterator itSubWidget = m_mapSubWidgets.begin();
    for (; itSubWidget != m_mapSubWidgets.end(); itSubWidget++) {
        if (itSubWidget.value()) {
            delete itSubWidget.value();
            itSubWidget.value() = nullptr;
        }
    }
    m_mapSubWidgets.clear();
}

void DeviceMonitorPage::addInfoItems(int nType, QString strTitle, qreal rHigh, qreal rVHigh, qreal newValue)
{
    switch(nType) {
    case 0: // temp
    {
        QString strItemKey = "TEMP_"+strTitle;
        if (m_mapSubWidgets.contains(strItemKey)) {
            ((KATempItem*)m_mapSubWidgets[strItemKey])->setThresholdValue(rHigh, rVHigh);
            ((KATempItem*)m_mapSubWidgets[strItemKey])->onUpdateTemperature(newValue);
        } else {
            if (strTitle.startsWith("CPU")) {
                KATempItem *tempCpu = new KATempItem(tr("CPU Temp"));
                tempCpu->setThresholdValue(rHigh, rVHigh);
                tempCpu->onUpdateTemperature(newValue);
                m_tempContentLayout->addWidget(tempCpu);
                m_mapSubWidgets[strItemKey] = tempCpu;
            } else if (strTitle.startsWith("HARDDISK")) {
                KATempItem *tempHd = new KATempItem(tr("HARDDISK Temp"));
                tempHd->setThresholdValue(rHigh, rVHigh);
                tempHd->onUpdateTemperature(newValue);
                m_tempContentLayout->addWidget(tempHd);
                m_mapSubWidgets[strItemKey] = tempHd;
            } else if (strTitle.startsWith("GPU")) {
                KATempItem *tempGpu = new KATempItem(tr("GPU Temp"));
                tempGpu->setThresholdValue(rHigh, rVHigh);
                tempGpu->onUpdateTemperature(newValue);
                m_tempContentLayout->addWidget(tempGpu);
                m_mapSubWidgets[strItemKey] = tempGpu;
            }else {
                KATempItem *tempDev = new KATempItem(tr("DEV Temp"));
                tempDev->setThresholdValue(rHigh, rVHigh);
                tempDev->onUpdateTemperature(newValue);
                m_tempContentLayout->addWidget(tempDev);
                m_mapSubWidgets[strItemKey] = tempDev;
            }
        }
    }
        break;
    case 1: // usage
    {
        QString strItemKey = "USAGE_"+strTitle;
        if (m_mapSubWidgets.contains(strItemKey)) {
            ((KAUsageItem*)m_mapSubWidgets[strItemKey])->setThresholdValue(rHigh, rVHigh);
            ((KAUsageItem*)m_mapSubWidgets[strItemKey])->onUpdateValue(newValue);
        } else {
            if (strTitle.startsWith("CPU")) {
                KAUsageItem *usageItem = new KAUsageItem(tr("CPU Usage"));
                usageItem->setThresholdValue(rHigh, rVHigh);
                usageItem->onUpdateValue(newValue);
                m_usageLayout->addWidget(usageItem);
                m_mapSubWidgets[strItemKey] = usageItem;
            } else if (strTitle.startsWith("MEM")) {
                KAUsageItem *usageItem = new KAUsageItem(tr("Memory Usage"));
                usageItem->setThresholdValue(rHigh, rVHigh);
                usageItem->onUpdateValue(newValue);
                m_usageLayout->addWidget(usageItem);
                m_mapSubWidgets[strItemKey] = usageItem;
            } else {
                KAUsageItem *usageItem = new KAUsageItem(tr("DEV Usage"));
                usageItem->setThresholdValue(rHigh, rVHigh);
                usageItem->onUpdateValue(newValue);
                m_usageLayout->addWidget(usageItem);
                m_mapSubWidgets[strItemKey] = usageItem;
            }
        }
    }
        break;
    default:
        break;
    }
}

/*
 * {\"device_monitor\": {\"device_temps\": [{\"device_temp\": \"41.3\", \"device_temp_high\": \"84.0\", \"device_temp_crit\": \"100.0\", \"device_name\": \"CPU\"}],
 * \"device_usage\": [{\"device_name\": \"CPU\", \"device_usage_used\": \"1.2\", \"device_usage_total\": \"100\"},
 * {\"device_name\": \"MEM\", \"device_usage_used\": \"60.6\", \"device_usage_total\": \"100\"}]}}
 **/
void DeviceMonitorPage::onUpdateInfo(unsigned uStatus, QString strInfoJson)
{
    if (strInfoJson.isEmpty())
        return;
    //qInfo()<<"Cur info:"<<strInfoJson;
    Q_EMIT updateInfo(uStatus, strInfoJson);
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
         QJsonValue valJson = rootObj.value(DEVMONITOR_ROOT);
         if (valJson.isObject()) {
             QJsonObject objMonitor = valJson.toObject();
             QJsonValue valTemps = objMonitor.value(DEVMONITOR_DEVTEMP);
             if (valTemps.isArray()) {
                 QJsonArray arrayJson = valTemps.toArray();
                 for (int n = 0; n < arrayJson.size(); n++) {
                     if (arrayJson.at(n).isObject()) {
                         QJsonObject subItemObj = arrayJson.at(n).toObject();
                         QJsonValue subItemValue = subItemObj.value(DEVMONITOR_DEVTEMP_NAME);
                         QString strTempName;
                         qreal rHigh = 80.0;
                         qreal rVHigh = 90.0;
                         qreal rNewValue = 0.0;
                         if (subItemValue.isString()) {
                             strTempName = subItemValue.toString();
                         }
                         subItemValue = subItemObj.value(DEVMONITOR_DEVTEMP_VALUE);
                         if (subItemValue.isString()) {
                             rNewValue = subItemValue.toString().toDouble();
                         }
                         subItemValue = subItemObj.value(DEVMONITOR_DEVTEMP_HIGH);
                         if (subItemValue.isString()) {
                             rHigh = subItemValue.toString().toDouble();
                         }
                         subItemValue = subItemObj.value(DEVMONITOR_DEVTEMP_CRIT);
                         if (subItemValue.isString()) {
                             rVHigh = subItemValue.toString().toDouble();
                         }
                         if (!strTempName.isEmpty()) {
                             addInfoItems(0, strTempName, 80.0/*rHigh*/, 90.0/*rVHigh*/, rNewValue);
                         }
                     }
                 }
             }

             QJsonValue valUsages = objMonitor.value(DEVMONITOR_DEVUSAGE);
             if (valUsages.isArray()) {
                 QJsonArray arrayJson = valUsages.toArray();
                 for (int n = 0; n < arrayJson.size(); n++) {
                     if (arrayJson.at(n).isObject()) {
                         QJsonObject subItemObj = arrayJson.at(n).toObject();
                         QJsonValue subItemValue = subItemObj.value(DEVMONITOR_DEVUSAGE_NAME);
                         QString strUsageName;
                         qreal rHigh = 80.0;
                         qreal rVHigh = 90.0;
                         qreal rUsed = 0.0, rTotal = 0.0;
                         if (subItemValue.isString()) {
                             strUsageName = subItemValue.toString();
                         }
                         subItemValue = subItemObj.value(DEVMONITOR_DEVUSAGE_USED);
                         if (subItemValue.isString()) {
                             rUsed = subItemValue.toString().toDouble();
                         }
                         subItemValue = subItemObj.value(DEVMONITOR_DEVUSAGE_TOTAL);
                         if (subItemValue.isString()) {
                             rTotal = subItemValue.toString().toDouble();
                         }
                         if (!strUsageName.isEmpty()) {
                             addInfoItems(1, strUsageName, rHigh, rVHigh, rUsed);
                         }
                     }
                 }
             }
         }
    }
}

void DeviceMonitorPage::checkTempStatus()
{
    bool bHavVHigh = false;
    bool bHavHigh = false;
    unsigned uTempCount = 0;
    QMap<QString, QWidget*>::iterator itSubWidget = m_mapSubWidgets.begin();
    for (; itSubWidget != m_mapSubWidgets.end(); itSubWidget ++) {
        if (itSubWidget.key().startsWith("TEMP_")) {
            KATempItem *tempItem = qobject_cast<KATempItem *>(itSubWidget.value());
            if (tempItem) {
                if (tempItem->getCurStatus() == KATempItem::STATUS_VHIGH) {
                    bHavVHigh = true;
                } else if(tempItem->getCurStatus() == KATempItem::STATUS_HIGH) {
                    bHavHigh = true;
                }
                uTempCount ++;
            }
        }
    }
    if (uTempCount == 0) {
        m_tempTitle->hide();
    } else {
        if (bHavVHigh) {
            m_tempTitle->setText(m_listStatus[2]);
        } else if (bHavHigh) {
            m_tempTitle->setText(m_listStatus[1]);
        } else {
            m_tempTitle->setText(m_listStatus[0]);
        }
        m_tempTitle->show();
    }
}
