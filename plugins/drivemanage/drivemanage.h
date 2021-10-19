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

#ifndef DRIVEMANAGE_H
#define DRIVEMANAGE_H

#include <QObject>
#include <QtPlugin>
#include <QWidget>
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QStringList>

#include "../../src/interface.h"
#include "loadingwidget.h"
#include "driveinfopage.h"

class DriveManage : public QObject, PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PluginInterfaceIID)
    Q_INTERFACES(PluginInterface)

public:
    DriveManage();
    virtual ~DriveManage();

    QString getPluginName() Q_DECL_OVERRIDE;
    int getPluginType() Q_DECL_OVERRIDE;
    QWidget* getPluginMainWnd() Q_DECL_OVERRIDE;
    void pluginDelayControl() Q_DECL_OVERRIDE;
    const QString name() const Q_DECL_OVERRIDE;
    void updatePluginContent() Q_DECL_OVERRIDE;

    void initUI();
    void initConnections();
    void getDriveInfo(bool bReScan = false);

    bool isHW990();
    QStringList getDeviceDriveInfo();
    QString getDriveInfoJson();

public slots:
    void onUpdateInfo(unsigned uStatus, QString strInfoJson);

private:
    QString m_pluginName;
    int m_pluginType;
    QWidget *m_pluginWidget = nullptr;
    bool mFirstLoad;

    QHBoxLayout *m_mainLayout = nullptr;
    LoadingWidget *m_loadingWidget = nullptr;
    DriveInfoPage *m_driveInfoPage = nullptr;
    QStackedWidget *m_stackedWidget = nullptr;
};

#endif // DRIVEMANAGE_H
