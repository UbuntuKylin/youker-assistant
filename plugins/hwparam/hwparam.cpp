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

#include "hwparam.h"

#include "../../src/commondef.h"

#include <QDBusMessage>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>
#include <QDebug>
#include <QTimer>

HWParam::HWParam()
{
    m_pluginName = tr("HardwareParam");
    m_pluginType = HARDWARE_PARAMETERS;
    mFirstLoad = true;
}

QString HWParam::getPluginName()
{
    return m_pluginName;
}

int HWParam::getPluginType()
{
    return m_pluginType;
}

QWidget* HWParam::getPluginMainWnd()
{
    if (mFirstLoad) {
        mFirstLoad = false;
        initUI();
        initConnections();
    }
    return m_pluginWidget;
}

void HWParam::pluginDelayControl()
{
    if (m_mainInfoPage)
        m_mainInfoPage->refreshInfo();
}

const QString HWParam::name() const
{
    return QStringLiteral("hardwareparam");
}

void HWParam::updatePluginContent()
{
//    if (m_mainInfoPage)
//        m_mainInfoPage->refreshInfo();
}

void HWParam::initUI()
{
    m_pluginWidget = new QWidget();
    m_pluginWidget->setFixedSize(RIGHT_PANEL_WIDTH, RIGHT_PANEL_HEIGHT);
    m_pluginWidget->setAttribute(Qt::WA_DeleteOnClose);

    m_mainLayout = new QHBoxLayout();
    m_mainLayout->setContentsMargins(0,0,0,0);
    m_mainLayout->setSpacing(0);

    m_stackedWidget = new QStackedWidget();

    m_loadingWidget = new LoadingWidget();
    m_stackedWidget->addWidget(m_loadingWidget);
    m_mainInfoPage = new MainInfoPage();
    m_stackedWidget->addWidget(m_mainInfoPage);
    m_mainLayout->addWidget(m_stackedWidget);

    m_pluginWidget->setLayout(m_mainLayout);
}

void HWParam::initConnections()
{
    // 连接dbus信号
    if (m_mainInfoPage)
        connect(m_mainInfoPage, &MainInfoPage::updateInfo, this, &HWParam::onUpdateInfo);
}


void HWParam::onUpdateInfo(unsigned uStatus)
{
    qInfo()<<"updateInfo:"<<uStatus;
    if (uStatus == 0) {
        m_stackedWidget->setCurrentIndex(0);
    } else {
        m_stackedWidget->setCurrentIndex(1);
    }
}

