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

#ifndef HWPARAM_H
#define HWPARAM_H

#include <QObject>
#include <QWidget>
#include <QtPlugin>
#include <QHBoxLayout>
#include <QStackedWidget>

#include "../../src/interface.h"
#include "loadingwidget.h"
#include "maininfopage.h"

class HWParam : public QObject, PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PluginInterfaceIID)
    Q_INTERFACES(PluginInterface)

public:
    explicit HWParam();

    QString getPluginName() Q_DECL_OVERRIDE;
    int getPluginType() Q_DECL_OVERRIDE;
    QWidget* getPluginMainWnd() Q_DECL_OVERRIDE;
    void pluginDelayControl() Q_DECL_OVERRIDE;
    const QString name() const Q_DECL_OVERRIDE;
    void updatePluginContent() Q_DECL_OVERRIDE;

    void initUI();
    void initConnections();
    void getHardwareParam(bool bReScan = false);

public slots:
    void onUpdateInfo(unsigned uStatus);

private:
    QString m_pluginName;
    int m_pluginType;
    QWidget *m_pluginWidget = nullptr;
    bool mFirstLoad;

    LoadingWidget *m_loadingWidget = nullptr;
    MainInfoPage *m_mainInfoPage = nullptr;
    QHBoxLayout *m_mainLayout = nullptr;
    QStackedWidget *m_stackedWidget = nullptr;
};

#endif // HWPARAM_H
