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

#ifndef DATAWORKER_H
#define DATAWORKER_H

#include <QObject>
#include <QMutex>
#include <QDBusInterface>
#include <QDBusPendingCallWatcher>

class DataWorker : public QObject
{
    Q_OBJECT
public:
    virtual ~DataWorker();
    static DataWorker* getInstance();

    // 连接被动更新信号
    void connectCpuFMInfoSignal(bool bConnect = true);  //CPU调频
    void connectDevMonitorInfoSignal(bool bConnect = true); //设备监测
    void connectHDInfoSignal(bool bConnect = true);     //硬盘
    void connectMemInfoSignal(bool bConnect = true);    //内存
    void connectProcInfoSignal(bool bConnect = true);   //处理器
    void connectMBInfoSignal(bool bConnect = true);     //主板
    void connectNWInfoSignal(bool bConnect = true);     //网卡
    void connectVCInfoSignal(bool bConnect = true);     //声卡
    void connectGSInfoSignal(bool bConnect = true);     //显卡
    void connectBLInfoSignal(bool bConnect = true);     //蓝牙
    void connectKBInfoSignal(bool bConnect = true);     //键盘
    void connectMSInfoSignal(bool bConnect = true);     //鼠标
    void connectMNInfoSignal(bool bConnect = true);     //显示
    void connectCDInfoSignal(bool bConnect = true);     //光驱
    void connectBTInfoSignal(bool bConnect = true);     //电池
    void connectFAInfoSignal(bool bConnect = true);     //风扇
    void connectCAInfoSignal(bool bConnect = true);     //摄像头
    void connectOutlineSignal(bool bConnect = true);    //整机概要信息
    void connectSysInfoSignal(bool bConnect = true);    //系统概要信息
    void connectHardwareInfoSignal(bool bConnect = true); //硬件参数信息
    void connectLshwInfoSignal(bool bConnect = true); //刷新lshw信息

    bool getCpuTempEnable();
    bool getCpuFanEnable();
    bool getCpuFMEnable();
    bool updateLshwInfo(bool bForceUpdate = true); //更新lshw信息
    bool exitDaemonDbus(); //退出dbus

public slots:
    // 异步获取接口
    void getCpuFMInfo();
    void onAsyncGetCpuFMInfo(QDBusPendingCallWatcher* callWatcher);
    void setCpuFMInfo(QString strInfoJson);
    void getDevMonitorInfo();
    void onAsyncDevMonitorInfo(QDBusPendingCallWatcher* callWatcher);
    void getHardwareInfo();
    void onAsyncHardwareInfo(QDBusPendingCallWatcher* callWatcher);
    void getHardDiskInfo();
    void onAsyncHardDiskInfo(QDBusPendingCallWatcher* callWatcher);
    void getMemoryInfo();
    void onAsyncMemoryInfo(QDBusPendingCallWatcher* callWatcher);
    void getProcessorInfo();
    void onAsyncProcessorInfo(QDBusPendingCallWatcher* callWatcher);
    void getMotherBoardInfo();
    void onAsyncMotherBoard(QDBusPendingCallWatcher* callWatcher);
    void getNetworkCardInfo();
    void onAsyncNetworkCard(QDBusPendingCallWatcher* callWatcher);
    void getVoiceCardInfo();
    void onAsyncVoiceCard(QDBusPendingCallWatcher* callWatcher);
    void getGraphicsCardInfo();
    void onAsyncGraphicsCard(QDBusPendingCallWatcher* callWatcher);
    void getBluetoothInfo();
    void onAsyncBluetooth(QDBusPendingCallWatcher* callWatcher);
    void getKeyboardInfo();
    void onAsyncKeyboard(QDBusPendingCallWatcher* callWatcher);
    void getMouseInfo();
    void onAsyncMouse(QDBusPendingCallWatcher* callWatcher);
    void getMonitorInfo(bool bUpdate = true);
    void onAsyncMonitor(QDBusPendingCallWatcher* callWatcher);
    void getCDDriveInfo();
    void onAsyncCDDrive(QDBusPendingCallWatcher* callWatcher);
    void getBatteryInfo();
    void onAsyncBattery(QDBusPendingCallWatcher* callWatcher);
    void getFanInfo();
    void onAsyncFan(QDBusPendingCallWatcher* callWatcher);
    void getCameraInfo();
    void onAsyncCamera(QDBusPendingCallWatcher* callWatcher);
    void getOutline();
    void onAsyncOutline(QDBusPendingCallWatcher* callWatcher);
    void getSysInfo();
    void onAsyncSysInfo(QDBusPendingCallWatcher* callWatcher);
    void onAsyncLshwInfo(QDBusPendingCallWatcher* callWatcher);

signals:
    //异步获取返回信息信号
    void updateCpuFMInfo(unsigned uStatus, QString strInfoJson);
    void updateDevMonitorInfo(unsigned uStatus, QString strInfoJson);
    void updateHardwareInfo(unsigned uStatus, QString strInfoJson);
    void updateHardDiskInfo(unsigned uStatus, QString strInfoJson);
    void updateMemoryInfo(unsigned uStatus, QString strInfoJson);
    void updateProcessorInfo(unsigned uStatus, QString strInfoJson);
    void updateMotherBoardInfo(unsigned uStatus, QString strInfoJson);
    void updateNetworkCardInfo(unsigned uStatus, QString strInfoJson);
    void updateVoiceCardInfo(unsigned uStatus, QString strInfoJson);
    void updateGraphicsCardInfo(unsigned uStatus, QString strInfoJson);
    void updateBluetoothInfo(unsigned uStatus, QString strInfoJson);
    void updateKeyboardInfo(unsigned uStatus, QString strInfoJson);
    void updateMouseInfo(unsigned uStatus, QString strInfoJson);
    void updateMonitorInfo(unsigned uStatus, QString strInfoJson);
    void updateCDDriveInfo(unsigned uStatus, QString strInfoJson);
    void updateBatteryInfo(unsigned uStatus, QString strInfoJson);
    void updateFanInfo(unsigned uStatus, QString strInfoJson);
    void updateCameraInfo(unsigned uStatus, QString strInfoJson);
    void updateOutline(unsigned uStatus, QString strInfoJson);
    void updateSysInfo(unsigned uStatus, QString strInfoJson);
    void updateLshwFinished();

private:
    explicit DataWorker(QObject *parent = nullptr);
    void initDbusInterface(QDBusInterface **interface, QString strPath);
    void initDbusSession(QDBusInterface **interface, QString strPath);
    void genMonitorInfoDataFile(bool bUpdate = true);

public:
    static QMutex m_mutex;
    static DataWorker *m_instance;

private:
    QDBusInterface *m_dbusCpuFM = nullptr;
    QDBusInterface *m_dbusDevMonitor = nullptr;
    QDBusInterface *m_dbusHardwareInfo = nullptr;
    QDBusInterface *m_dbusSession = nullptr;
};

#endif // DATAWORKER_H
