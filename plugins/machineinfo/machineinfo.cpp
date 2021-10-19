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
#include "machineinfo.h"
#include "../../src/commondef.h"

#include <QLabel>
#include <QIcon>
#include <QDebug>
#include <QDBusMessage>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>
#include <QTimer>

MachineInfo::MachineInfo()
{
    m_pluginName = tr("MachineInfo");
    m_pluginType = MACHINE_INFO;
    mFirstLoad = true;
}

MachineInfo::~MachineInfo()
{

}

QString MachineInfo::getPluginName()
{
    return m_pluginName;
}

int MachineInfo::getPluginType()
{
    return m_pluginType;
}

QWidget* MachineInfo::getPluginMainWnd()
{
    if (mFirstLoad) {
        mFirstLoad = false;
        initUI();
        initConnections();
    }
    return m_pluginWidget;
}

void MachineInfo::pluginDelayControl()
{
    // 首次获取整机信息
    if (m_infoPage)
        m_infoPage->onRefreshInfo();
}

const QString MachineInfo::name() const
{
    return QStringLiteral("machineinfo");
}

void MachineInfo::updatePluginContent()
{
    qInfo()<<"";
}

void MachineInfo::initUI()
{
    m_pluginWidget = new QWidget();
    m_pluginWidget->setFixedSize(RIGHT_PANEL_WIDTH, RIGHT_PANEL_HEIGHT);
    m_pluginWidget->setAttribute(Qt::WA_DeleteOnClose);

    m_mainLayout = new QHBoxLayout();
    m_mainLayout->setContentsMargins(0,0,0,0);
    m_mainLayout->setSpacing(0);

    m_stackedWidget = new QStackedWidget();

    m_loadingWidget = new LoadingWidget();
    m_infoPage = new InfoPage();
    m_stackedWidget->addWidget(m_loadingWidget);
    m_stackedWidget->addWidget(m_infoPage);
    m_mainLayout->addWidget(m_stackedWidget);

    m_pluginWidget->setLayout(m_mainLayout);
}

void MachineInfo::initConnections()
{
    connect(m_infoPage, &InfoPage::updateInfo, this, &MachineInfo::onUpdateInfo);
}

void MachineInfo::onUpdateInfo(unsigned uStatus, QString strInfoJson)
{
    Q_UNUSED(strInfoJson);
    qDebug()<<"updateInfo:"<<uStatus;
    if (uStatus == 0) {
        m_stackedWidget->setCurrentIndex(0);
    } else {
        m_stackedWidget->setCurrentIndex(1);
    }
}
