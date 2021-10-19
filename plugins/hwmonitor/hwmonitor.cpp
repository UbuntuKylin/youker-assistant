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
#include "hwmonitor.h"
#include "../../src/commondef.h"

#include <QLabel>
#include <QIcon>
#include <QDebug>
#include <QTimer>

HWMonitorInfo::HWMonitorInfo()
{
    m_pluginName = tr("HardwareMonitor");
    m_pluginType = HARDWARE_MONITOR;
    mFirstLoad = true;
}

HWMonitorInfo::~HWMonitorInfo()
{

}

QString HWMonitorInfo::getPluginName()
{
    return m_pluginName;
}

int HWMonitorInfo::getPluginType()
{
    return m_pluginType;
}

QWidget* HWMonitorInfo::getPluginMainWnd()
{
    if (mFirstLoad) {
        mFirstLoad = false;
        initUI();
        initConnections();
    }
    return m_pluginWidget;
}

void HWMonitorInfo::pluginDelayControl()
{
    if (m_hwMonitorWidget) {
        Q_EMIT m_hwMonitorWidget->refreshInfo();
    }
}

const QString HWMonitorInfo::name() const
{
    return QStringLiteral("hardwaremonitor");
}

void HWMonitorInfo::updatePluginContent()
{
    if (m_hwMonitorWidget) {
        Q_EMIT m_hwMonitorWidget->refreshInfo();
    }
}

void HWMonitorInfo::initUI()
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
    // add monitor widget
    m_hwMonitorWidget = new HWMonitorWidget();
    m_stackedWidget->addWidget(m_hwMonitorWidget);
    m_stackedWidget->setCurrentIndex(1);
    m_mainLayout->addWidget(m_stackedWidget);

    m_pluginWidget->setLayout(m_mainLayout);
}

void HWMonitorInfo::initConnections()
{
}

void HWMonitorInfo::onUpdateInfo(unsigned uStatus, QString strInfoJson)
{
    qInfo()<<"updateInfo:"<<uStatus<<","<<strInfoJson;
    if (uStatus == 0) {
        m_stackedWidget->setCurrentIndex(0);
    } else {
        m_stackedWidget->setCurrentIndex(1);
    }
}
