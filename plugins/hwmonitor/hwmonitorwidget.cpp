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

#include "hwmonitorwidget.h"

#include <QDebug>
#include <QDBusMessage>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>
#include <QTimer>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

#include "../../src/commondef.h"
#include "../../src/kajsondef.h"

HWMonitorWidget::HWMonitorWidget(QWidget *parent)
    : QWidget(parent)
{
    initUI();
    initConnections();
}

HWMonitorWidget::~HWMonitorWidget()
{
    if (m_refreshInfoTimer) {
        m_refreshInfoTimer->stop();
    }
    if (m_styleSettings) {
        delete m_styleSettings;
        m_styleSettings = nullptr;
    }
}

void HWMonitorWidget::initUI()
{
    m_mainLayout = new QVBoxLayout();
    m_mainLayout->setContentsMargins(32,16,0,16);
    m_mainLayout->setSpacing(0);
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_topLayout = new QHBoxLayout();
    m_topLayout->setContentsMargins(0,0,0,0);
    m_topLayout->setSpacing(1);

    // button group
    m_btnGroup = new QButtonGroup();
    m_btnGroup->setExclusive(true);
    //dev monitor button
    m_btnDevMonitor = new KAGroupButton();
    m_btnDevMonitor->setText(tr("Device Monitor"));
    m_btnDevMonitor->setMinimumWidth(180);
    m_btnDevMonitor->setMinimumHeight(40);
    m_btnDevMonitor->setCheckable(true);
    m_btnDevMonitor->setAutoExclusive(true);
    m_btnDevMonitor->setChecked(true);
    m_btnDevMonitor->setPosition(KAButtonStyleOption::Begin);
    // freq adjust button
    m_btnFreqAdjust = new KAGroupButton();
    m_btnFreqAdjust->setText(tr("CPU FM"));
    m_btnFreqAdjust->setMinimumWidth(180);
    m_btnFreqAdjust->setMinimumHeight(40);
    m_btnFreqAdjust->setCheckable(true);
    m_btnFreqAdjust->setAutoExclusive(true);
    m_btnFreqAdjust->setChecked(false);
    m_btnFreqAdjust->setPosition(KAButtonStyleOption::End);
    m_topLayout->setAlignment(Qt::AlignLeft);
    m_topLayout->addWidget(m_btnDevMonitor);
    m_btnGroup->addButton(m_btnDevMonitor);
    m_topLayout->addWidget(m_btnFreqAdjust);
    m_btnGroup->addButton(m_btnFreqAdjust);
    // init stacked widget
    m_stackedWidget = new QStackedWidget();
    m_stackedWidget->setContentsMargins(0,0,0,0);
    m_deviceMonitor = new DeviceMonitorPage();
    m_stackedWidget->addWidget(m_deviceMonitor);
    m_cpuFM = new CpuFMPage();
    m_stackedWidget->addWidget(m_cpuFM);

    m_mainLayout->addLayout(m_topLayout);
    m_mainLayout->addWidget(m_stackedWidget);
    this->setLayout(m_mainLayout);
    initStyleTheme();
    m_refreshInfoTimer = new QTimer(this);
}

void HWMonitorWidget::initConnections()
{
    connect(this, &HWMonitorWidget::refreshInfo, this, &HWMonitorWidget::onRefreshInfo);
    connect(m_btnDevMonitor, &KAGroupButton::clicked, this, &HWMonitorWidget::onSwitchWidget);
    connect(m_btnFreqAdjust, &KAGroupButton::clicked, this, &HWMonitorWidget::onSwitchWidget);
    connect(m_refreshInfoTimer, &QTimer::timeout, this, &HWMonitorWidget::onTimerRefreshInfo);
    m_refreshInfoTimer->start(1000);
}

void HWMonitorWidget::onSwitchWidget()
{
    KAGroupButton *button = qobject_cast<KAGroupButton *>(sender());
    if (button == m_btnDevMonitor) {
        if (m_stackedWidget->currentIndex() != 0) {
            m_stackedWidget->setCurrentIndex(0);
        }
    } else if (button == m_btnFreqAdjust) {
        if (m_stackedWidget->currentIndex() != 1) {
            m_stackedWidget->setCurrentIndex(1);
        }
    }
}

void HWMonitorWidget::onUpdateInfo(unsigned uStatus, QString strInfoJson)
{
    Q_UNUSED(uStatus);
    Q_UNUSED(strInfoJson);
}

void HWMonitorWidget::initStyleTheme()
{
    const QByteArray idd(THEME_QT_SCHEMA);
    if(QGSettings::isSchemaInstalled(idd)) {
        m_styleSettings = new QGSettings(idd);
    }
    if (m_styleSettings) {
        connect(m_styleSettings, &QGSettings::changed, this, [=](const QString &key) {
            if (key == "styleName") {
                qDebug()<<"style name changed";
                auto styleName = m_styleSettings->get("styleName").toString();

                if (styleName == "ukui-default" || styleName == "ukui-dark" || styleName == "ukui-white"
                        || styleName == "ukui-black" || styleName == "ukui-light" || styleName == "ukui") {
                    if (styleName == "ukui")
                        styleName = "ukui-default";
                    else if (styleName == "ukui-black")
                        styleName = "ukui-dark";
                    else if (styleName == "ukui-white")
                        styleName = "ukui-light";

                    m_strStyleName = styleName;
                    auto listBtn = m_btnGroup->buttons();
                    for (auto btn : listBtn) {
                        btn->setStyle(new KAButtonProxyStyle(m_strStyleName));
                    }
                }
            }
        });
        auto styleName = m_styleSettings->get("styleName").toString();
        if (styleName == "ukui-default" || styleName == "ukui-dark" || styleName == "ukui-white"
                || styleName == "ukui-black" || styleName == "ukui-light" || styleName == "ukui") {
            if (styleName == "ukui")
                styleName = "ukui-default";
            else if (styleName == "ukui-black")
                styleName = "ukui-dark";
            else if (styleName == "ukui-white")
                styleName = "ukui-light";

            m_strStyleName = styleName;
            auto listBtn = m_btnGroup->buttons();
            for (auto btn : listBtn) {
                btn->setStyle(new KAButtonProxyStyle(m_strStyleName));
            }
        }
    }
}

void HWMonitorWidget::onRefreshInfo()
{
    if (m_deviceMonitor) {
        m_deviceMonitor->refreshInfo();
    }
    if (m_cpuFM) {
        m_cpuFM->refreshInfo();
    }
}

void HWMonitorWidget::onTimerRefreshInfo()
{
    static int cpuFmUpdateDelay = 0;
    if (m_deviceMonitor) {
        m_deviceMonitor->refreshInfo();
    }
    if (cpuFmUpdateDelay >= 2) {
        cpuFmUpdateDelay = 0;
        if (m_cpuFM) {
            m_cpuFM->refreshInfo();
        }
    } else {
        cpuFmUpdateDelay ++;
    }
}
