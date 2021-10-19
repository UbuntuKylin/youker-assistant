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

#ifndef MAININFOPAGE_H
#define MAININFOPAGE_H

#include <QWidget>
#include <katabbar.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QMap>

#include "processorinfo.h"
#include "memoryinfo.h"
#include "graphicscardinfo.h"
#include "motherboardinfo.h"
#include "netcardinfo.h"
#include "harddiskinfo.h"
#include "monitorinfo.h"
#include "voicecardinfo.h"
#include "keyboardinfo.h"
#include "mouseinfo.h"
#include "batteryinfo.h"
#include "cdrominfo.h"
#include "camerainfo.h"
#include "bluetoothinfo.h"
#include "faninfo.h"
#include "udevhotplugin.h"

enum {
    HWINFO_PROCESSOR,
    HWINFO_MEMORY,
    HWINFO_GRAPHICSCARD,
    HWINFO_MOTHERBOARD,
    HWINFO_NETCARD,
    HWINFO_HARDDISK,
    HWINFO_MONITOR,
    HWINFO_VOICECARD,
    HWINFO_KEYBOARD,
    HWINFO_MOUSE,
    HWINFO_BATTERY,
    HWINFO_CDROM,
    HWINFO_CAMERA,
    HWINFO_BLUETOOTH,
    HWINFO_FAN,
};

class MainInfoPage : public QWidget
{
    Q_OBJECT
public:
    explicit MainInfoPage(QWidget *parent = nullptr);
    virtual ~MainInfoPage();

    void refreshInfo();

public slots:
    void onUpdateInfo(QString strAllInfo);
    void onUpdateInfo(unsigned uStatus, QString strAllInfo);
    void onChangeInfoPage(int nPage);
    void startUDevHotPlugin();
    void stopUDevHotPlugin();
    void onUDevHotPluginAdd(QString strUdevSubName, QString strUdevType);
    void onUDevHotPluginRemove(QString strUdevSubName, QString strUdevType);
    void onLshwInfoUpdateFinished();

signals:
    void updateInfo(unsigned uStatus);

protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *e) override;

private:
    void initUI();
    void initConnections();
    void switchWidgetAnimation(int nOldIndex, int nNewIndex);

private:
    KATabBar *m_tabbar = nullptr;
    QStackedWidget *m_stackedInfoPage = nullptr;
    QVBoxLayout *m_mainLayout = nullptr;
    QHBoxLayout *m_tabbarLayout = nullptr;

    QPropertyAnimation *m_anmWidgetLeft = nullptr;
    QPropertyAnimation *m_anmWidgetRight = nullptr;
    QParallelAnimationGroup *m_anmgWidget = nullptr;

    ProcessorInfo *m_processorInfo = nullptr;
    MemoryInfo *m_memoryInfo = nullptr;
    GraphicsCardInfo *m_graphicsCardInfo = nullptr;
    MotherBoardInfo *m_motherBoardInfo = nullptr;
    NetCardInfo *m_netcardInfo = nullptr;
    HardDiskInfo *m_harddiskInfo = nullptr;
    MonitorInfo *m_monitorInfo = nullptr;
    VoiceCardInfo *m_voicecardInfo = nullptr;
    KeyboardInfo *m_keyboardInfo = nullptr;
    MouseInfo *m_mouseInfo = nullptr;
    BatteryInfo *m_batteryInfo = nullptr;
    CDRomInfo *m_cdromInfo = nullptr;
    CameraInfo *m_cameraInfo = nullptr;
    BluetoothInfo *m_bluetoothInfo = nullptr;
    FanInfo *m_fanInfo = nullptr;
    UDevHotPlugin *m_udevHotPlugin = nullptr;

    QMap<unsigned, QWidget*> m_mapWidget;
};

#endif // MAININFOPAGE_H
