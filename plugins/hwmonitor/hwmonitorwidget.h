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

#ifndef HWMONITORWIDGET_H
#define HWMONITORWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QButtonGroup>
#include <qgsettings.h>
#include <QTimer>

#include "kagroupbutton.h"
#include "devicemonitorpage.h"
#include "cpufmpage.h"

class HWMonitorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HWMonitorWidget(QWidget *parent = nullptr);
    virtual ~HWMonitorWidget();

    void initUI();

    void initConnections();

public slots:
    void onUpdateInfo(unsigned uStatus, QString strInfoJson);
    void onSwitchWidget();
    void onTimerRefreshInfo();
    void onRefreshInfo();

signals:
    void refreshInfo();

private:
    void initStyleTheme();

private:
    QVBoxLayout *m_mainLayout = nullptr;
    QHBoxLayout *m_topLayout = nullptr;
    KAGroupButton *m_btnDevMonitor = nullptr;
    KAGroupButton *m_btnFreqAdjust = nullptr;
    QButtonGroup *m_btnGroup = nullptr;
    QStackedWidget *m_stackedWidget = nullptr;
    QGSettings *m_styleSettings = nullptr;

    DeviceMonitorPage *m_deviceMonitor = nullptr;
    CpuFMPage *m_cpuFM = nullptr;

    QString m_strStyleName;
    QTimer *m_refreshInfoTimer = nullptr;
};

#endif // HWMONITORWIDGET_H
