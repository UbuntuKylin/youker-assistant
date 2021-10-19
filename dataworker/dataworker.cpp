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

#include "dataworker.h"

#include <QDBusMessage>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>
#include <QProcess>
#include <QFile>
#include <QTextStream>

#include <QDebug>

#define DBUSPATH_CPUFM "/com/kylin/assistant/cpufm"
#define DBUSPATH_DEVMONITOR "/com/kylin/assistant/devmonitor"
#define DBUSPATH_HARDWAREINFO "/com/kylin/assistant/systemdaemon"

#define DBUSPATH_SESSIONDBUS "/com/kylin/assistant/sessiondbus"

DataWorker* DataWorker::m_instance = nullptr;
QMutex DataWorker::m_mutex;

DataWorker::DataWorker(QObject *parent)
    : QObject(parent)
{

}

DataWorker::~DataWorker()
{
    if (m_dbusCpuFM) {
        delete m_dbusCpuFM;
        m_dbusCpuFM = nullptr;
    }
    if (m_dbusDevMonitor) {
        delete m_dbusDevMonitor;
        m_dbusDevMonitor = nullptr;
    }
}

DataWorker* DataWorker::getInstance()
{
    m_mutex.lock();
    if (!m_instance) {
        m_instance = new DataWorker();
    }
    m_mutex.unlock();
    return m_instance;
}

void DataWorker::initDbusInterface(QDBusInterface **interface, QString strPath)
{
    if (*interface) {
        return;
    }
    *interface = new QDBusInterface("com.kylin.assistant.systemdaemon",
                                   strPath,
                                   "com.kylin.assistant.systemdaemon",
                                   QDBusConnection::systemBus());
}

void DataWorker::initDbusSession(QDBusInterface **interface, QString strPath)
{
    if (*interface) {
        return;
    }
    *interface = new QDBusInterface("com.kylin.assistant.sessiondbus",
                                   strPath,
                                   "com.kylin.assistant.systemdaemon",
                                   QDBusConnection::sessionBus());
}

void DataWorker::getCpuFMInfo()
{
    initDbusInterface(&m_dbusCpuFM, DBUSPATH_CPUFM);
    if (m_dbusCpuFM && m_dbusCpuFM->isValid()) {
        QDBusPendingCall asyncCall = m_dbusCpuFM->asyncCall("readCpuFMInfo");
        if (!asyncCall.isError()) {
            // 创建异步调用监视器
            QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(asyncCall, this);
            // 连接监视器信号
            connect(watcher, SIGNAL(finished(QDBusPendingCallWatcher*)),
                             this, SLOT(onAsyncGetCpuFMInfo(QDBusPendingCallWatcher*)));
        }
    } else {
        qWarning()<<"call cpufm dbus failed!!";
    }
}

void DataWorker::onAsyncGetCpuFMInfo(QDBusPendingCallWatcher* callWatcher)
{
    QDBusPendingReply<QString> reply = *callWatcher;
    if (!reply.isError()) {
        QString strInfoJson = reply.value();
        Q_EMIT updateCpuFMInfo(1, strInfoJson);
    }
    callWatcher->deleteLater();
}

void DataWorker::setCpuFMInfo(QString strInfoJson)
{
    initDbusInterface(&m_dbusCpuFM, DBUSPATH_CPUFM);
    if (m_dbusCpuFM && m_dbusCpuFM->isValid()) {
        QDBusReply<QString> reply = m_dbusCpuFM->call("adjust_cpufreq_scaling_governer", strInfoJson);
        if (reply.isValid()) {
            QString strResult = reply.value();
            qInfo()<<"adjust fm Info:"<<strResult;
        }
    } else {
        qWarning()<<"call cpufm dbus failed!!";
    }
}

void DataWorker::connectCpuFMInfoSignal(bool bConnect)
{
    initDbusInterface(&m_dbusCpuFM, DBUSPATH_CPUFM);
    if (m_dbusCpuFM && m_dbusCpuFM->isValid()) {
        if (bConnect) {
            connect(m_dbusCpuFM, SIGNAL(signalUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateCpuFMInfo(unsigned,QString)));
        } else {
            disconnect(m_dbusCpuFM, SIGNAL(signalUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateCpuFMInfo(unsigned,QString)));
        }
    } else {
        qWarning()<<"call cpufm dbus failed!!";
    }
}

void DataWorker::getDevMonitorInfo()
{
    initDbusInterface(&m_dbusDevMonitor, DBUSPATH_DEVMONITOR);
    if (m_dbusDevMonitor && m_dbusDevMonitor->isValid()) {
        QDBusPendingCall asyncCall = m_dbusDevMonitor->asyncCall("readDevMonitorInfo");
        if (!asyncCall.isError()) {
            // 创建异步调用监视器
            QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(asyncCall, this);
            // 连接监视器信号
            connect(watcher, SIGNAL(finished(QDBusPendingCallWatcher*)),
                             this, SLOT(onAsyncDevMonitorInfo(QDBusPendingCallWatcher*)));
        }
    } else {
        qWarning()<<"call devmonitor dbus failed!!";
    }
}

void DataWorker::onAsyncDevMonitorInfo(QDBusPendingCallWatcher* callWatcher)
{
    QDBusPendingReply<QString> reply = *callWatcher;
    if (!reply.isError()) {
        QString strInfoJson = reply.value();
        Q_EMIT updateDevMonitorInfo(1, strInfoJson);
    }
    callWatcher->deleteLater();
}

void DataWorker::connectDevMonitorInfoSignal(bool bConnect)
{
    initDbusInterface(&m_dbusDevMonitor, DBUSPATH_DEVMONITOR);
    if (m_dbusDevMonitor && m_dbusDevMonitor->isValid()) {
        if (bConnect) {
            connect(m_dbusDevMonitor, SIGNAL(signalUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateDevMonitorInfo(unsigned,QString)));
        } else {
            disconnect(m_dbusDevMonitor, SIGNAL(signalUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateDevMonitorInfo(unsigned,QString)));
        }
    } else {
        qWarning()<<"call devMonitor dbus failed!!";
    }
}

void DataWorker::getHardwareInfo()
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        genMonitorInfoDataFile(true);
        QDBusPendingCall asyncCall = m_dbusHardwareInfo->asyncCall("readHardwareInfo");
        if (!asyncCall.isError()) {
            // 创建异步调用监视器
            QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(asyncCall, this);
            // 连接监视器信号
            connect(watcher, SIGNAL(finished(QDBusPendingCallWatcher*)),
                             this, SLOT(onAsyncHardwareInfo(QDBusPendingCallWatcher*)));
        }
    } else {
        qWarning()<<"call hardwareinfo dbus failed!!";
    }
}

void DataWorker::onAsyncHardwareInfo(QDBusPendingCallWatcher* callWatcher)
{
    QDBusPendingReply<QString> reply = *callWatcher;
    if (!reply.isError()) {
        QString strInfoJson = reply.value();
        Q_EMIT updateHardwareInfo(1, strInfoJson);
    }
    callWatcher->deleteLater();
}

void DataWorker::connectHardwareInfoSignal(bool bConnect)
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        if (bConnect) {
            connect(m_dbusHardwareInfo, SIGNAL(signalHardwareUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateHardwareInfo(unsigned,QString)));
        } else {
            disconnect(m_dbusHardwareInfo, SIGNAL(signalHardwareUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateHardwareInfo(unsigned,QString)));
        }
    } else {
        qWarning()<<"call hardwareinfo dbus failed!!";
    }
}

void DataWorker::getHardDiskInfo()
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        QDBusPendingCall asyncCall = m_dbusHardwareInfo->asyncCall("readHDInfo");
        if (!asyncCall.isError()) {
            // 创建异步调用监视器
            QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(asyncCall, this);
            // 连接监视器信号
            connect(watcher, SIGNAL(finished(QDBusPendingCallWatcher*)),
                             this, SLOT(onAsyncHardDiskInfo(QDBusPendingCallWatcher*)));
        }
    } else {
        qWarning()<<"call hardwareinfo dbus failed!!";
    }
}

void DataWorker::onAsyncHardDiskInfo(QDBusPendingCallWatcher* callWatcher)
{
    QDBusPendingReply<QString> reply = *callWatcher;
    if (!reply.isError()) {
        QString strInfoJson = reply.value();
        Q_EMIT updateHardDiskInfo(1, strInfoJson);
    }
    callWatcher->deleteLater();
}

void DataWorker::connectHDInfoSignal(bool bConnect)
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        if (bConnect) {
            connect(m_dbusHardwareInfo, SIGNAL(signalHDUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateHardDiskInfo(unsigned,QString)));
        } else {
            disconnect(m_dbusHardwareInfo, SIGNAL(signalHDUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateHardDiskInfo(unsigned,QString)));
        }
    } else {
        qWarning()<<"call hardwareinfo dbus failed!!";
    }
}

void DataWorker::getMemoryInfo()
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        QDBusPendingCall asyncCall = m_dbusHardwareInfo->asyncCall("readMemInfo");
        if (!asyncCall.isError()) {
            // 创建异步调用监视器
            QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(asyncCall, this);
            // 连接监视器信号
            connect(watcher, SIGNAL(finished(QDBusPendingCallWatcher*)),
                             this, SLOT(onAsyncMemoryInfo(QDBusPendingCallWatcher*)));
        }
    } else {
        qWarning()<<"call hardwareinfo dbus failed!!";
    }
}

void DataWorker::onAsyncMemoryInfo(QDBusPendingCallWatcher* callWatcher)
{
    QDBusPendingReply<QString> reply = *callWatcher;
    if (!reply.isError()) {
        QString strInfoJson = reply.value();
        Q_EMIT updateMemoryInfo(1, strInfoJson);
    }
    callWatcher->deleteLater();
}

void DataWorker::connectMemInfoSignal(bool bConnect)
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        if (bConnect) {
            connect(m_dbusHardwareInfo, SIGNAL(signalMemUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateMemoryInfo(unsigned,QString)));
        } else {
            disconnect(m_dbusHardwareInfo, SIGNAL(signalMemUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateMemoryInfo(unsigned,QString)));
        }
    } else {
        qWarning()<<"call hardwareinfo dbus failed!!";
    }
}

void DataWorker::getProcessorInfo()
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        QDBusPendingCall asyncCall = m_dbusHardwareInfo->asyncCall("readProcInfo");
        if (!asyncCall.isError()) {
            // 创建异步调用监视器
            QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(asyncCall, this);
            // 连接监视器信号
            connect(watcher, SIGNAL(finished(QDBusPendingCallWatcher*)),
                             this, SLOT(onAsyncProcessorInfo(QDBusPendingCallWatcher*)));
        }
    } else {
        qWarning()<<"call hardwareinfo dbus failed!!";
    }
}

void DataWorker::onAsyncProcessorInfo(QDBusPendingCallWatcher* callWatcher)
{
    QDBusPendingReply<QString> reply = *callWatcher;
    if (!reply.isError()) {
        QString strInfoJson = reply.value();
        Q_EMIT updateProcessorInfo(1, strInfoJson);
    }
    callWatcher->deleteLater();
}

void DataWorker::connectProcInfoSignal(bool bConnect)
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        if (bConnect) {
            connect(m_dbusHardwareInfo, SIGNAL(signalProcUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateProcessorInfo(unsigned,QString)));
        } else {
            disconnect(m_dbusHardwareInfo, SIGNAL(signalProcUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateProcessorInfo(unsigned,QString)));
        }
    } else {
        qWarning()<<"call hardwareinfo dbus failed!!";
    }
}

void DataWorker::getMotherBoardInfo()
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        QDBusPendingCall asyncCall = m_dbusHardwareInfo->asyncCall("readMBInfo");
        if (!asyncCall.isError()) {
            // 创建异步调用监视器
            QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(asyncCall, this);
            // 连接监视器信号
            connect(watcher, SIGNAL(finished(QDBusPendingCallWatcher*)),
                             this, SLOT(onAsyncMotherBoard(QDBusPendingCallWatcher*)));
        }
    } else {
        qWarning()<<"call hardwareinfo dbus failed!!";
    }
}

void DataWorker::onAsyncMotherBoard(QDBusPendingCallWatcher* callWatcher)
{
    QDBusPendingReply<QString> reply = *callWatcher;
    if (!reply.isError()) {
        QString strInfoJson = reply.value();
        Q_EMIT updateMotherBoardInfo(1, strInfoJson);
    }
    callWatcher->deleteLater();
}

void DataWorker::connectMBInfoSignal(bool bConnect)
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        if (bConnect) {
            connect(m_dbusHardwareInfo, SIGNAL(signalMBUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateMotherBoardInfo(unsigned,QString)));
        } else {
            disconnect(m_dbusHardwareInfo, SIGNAL(signalMBUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateMotherBoardInfo(unsigned,QString)));
        }
    } else {
        qWarning()<<"call hardwareinfo dbus failed!!";
    }
}

void DataWorker::getNetworkCardInfo()
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        QDBusPendingCall asyncCall = m_dbusHardwareInfo->asyncCall("readNWInfo");
        if (!asyncCall.isError()) {
            // 创建异步调用监视器
            QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(asyncCall, this);
            // 连接监视器信号
            connect(watcher, SIGNAL(finished(QDBusPendingCallWatcher*)),
                             this, SLOT(onAsyncNetworkCard(QDBusPendingCallWatcher*)));
        }
    } else {
        qWarning()<<"call hardwareinfo dbus failed!!";
    }
}

void DataWorker::onAsyncNetworkCard(QDBusPendingCallWatcher* callWatcher)
{
    QDBusPendingReply<QString> reply = *callWatcher;
    if (!reply.isError()) {
        QString strInfoJson = reply.value();
        Q_EMIT updateNetworkCardInfo(1, strInfoJson);
    }
    callWatcher->deleteLater();
}

void DataWorker::connectNWInfoSignal(bool bConnect)
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        if (bConnect) {
            connect(m_dbusHardwareInfo, SIGNAL(signalNWUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateNetworkCardInfo(unsigned,QString)));
        } else {
            disconnect(m_dbusHardwareInfo, SIGNAL(signalNWUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateNetworkCardInfo(unsigned,QString)));
        }
    } else {
        qWarning()<<"call hardwareinfo dbus failed!!";
    }
}

void DataWorker::getVoiceCardInfo()
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        QDBusPendingCall asyncCall = m_dbusHardwareInfo->asyncCall("readVCInfo");
        if (!asyncCall.isError()) {
            // 创建异步调用监视器
            QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(asyncCall, this);
            // 连接监视器信号
            connect(watcher, SIGNAL(finished(QDBusPendingCallWatcher*)),
                             this, SLOT(onAsyncVoiceCard(QDBusPendingCallWatcher*)));
        }
    } else {
        qWarning()<<"call hardwareinfo dbus failed!!";
    }
}

void DataWorker::onAsyncVoiceCard(QDBusPendingCallWatcher* callWatcher)
{
    QDBusPendingReply<QString> reply = *callWatcher;
    if (!reply.isError()) {
        QString strInfoJson = reply.value();
        Q_EMIT updateVoiceCardInfo(1, strInfoJson);
    }
    callWatcher->deleteLater();
}

void DataWorker::connectVCInfoSignal(bool bConnect)
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        if (bConnect) {
            connect(m_dbusHardwareInfo, SIGNAL(signalVCUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateVoiceCardInfo(unsigned,QString)));
        } else {
            disconnect(m_dbusHardwareInfo, SIGNAL(signalVCUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateVoiceCardInfo(unsigned,QString)));
        }
    } else {
        qWarning()<<"call hardwareinfo dbus failed!!";
    }
}

void DataWorker::getGraphicsCardInfo()
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        QDBusPendingCall asyncCall = m_dbusHardwareInfo->asyncCall("readGSInfo");
        if (!asyncCall.isError()) {
            // 创建异步调用监视器
            QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(asyncCall, this);
            // 连接监视器信号
            connect(watcher, SIGNAL(finished(QDBusPendingCallWatcher*)),
                             this, SLOT(onAsyncGraphicsCard(QDBusPendingCallWatcher*)));
        }
    } else {
        qWarning()<<"call hardwareinfo dbus failed!!";
    }
}

void DataWorker::onAsyncGraphicsCard(QDBusPendingCallWatcher* callWatcher)
{
    QDBusPendingReply<QString> reply = *callWatcher;
    if (!reply.isError()) {
        QString strInfoJson = reply.value();
        Q_EMIT updateGraphicsCardInfo(1, strInfoJson);
    }
    callWatcher->deleteLater();
}

void DataWorker::connectGSInfoSignal(bool bConnect)
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        if (bConnect) {
            connect(m_dbusHardwareInfo, SIGNAL(signalGSUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateGraphicsCardInfo(uint,QString)));
        } else {
            disconnect(m_dbusHardwareInfo, SIGNAL(signalGSUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateGraphicsCardInfo(unsigned,QString)));
        }
    } else {
        qWarning()<<"call hardwareinfo dbus failed!!";
    }
}

void DataWorker::getBluetoothInfo()
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        QDBusPendingCall asyncCall = m_dbusHardwareInfo->asyncCall("readBLInfo");
        if (!asyncCall.isError()) {
            // 创建异步调用监视器
            QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(asyncCall, this);
            // 连接监视器信号
            connect(watcher, SIGNAL(finished(QDBusPendingCallWatcher*)),
                             this, SLOT(onAsyncBluetooth(QDBusPendingCallWatcher*)));
        }
    } else {
        qWarning()<<"call hardwareinfo dbus failed!!";
    }
}

void DataWorker::onAsyncBluetooth(QDBusPendingCallWatcher* callWatcher)
{
    QDBusPendingReply<QString> reply = *callWatcher;
    if (!reply.isError()) {
        QString strInfoJson = reply.value();
        Q_EMIT updateBluetoothInfo(1, strInfoJson);
    }
    callWatcher->deleteLater();
}

void DataWorker::connectBLInfoSignal(bool bConnect)
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        if (bConnect) {
            connect(m_dbusHardwareInfo, SIGNAL(signalBLUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateBluetoothInfo(uint,QString)));
        } else {
            disconnect(m_dbusHardwareInfo, SIGNAL(signalBLUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateBluetoothInfo(unsigned,QString)));
        }
    } else {
        qWarning()<<"call hardwareinfo dbus failed!!";
    }
}

void DataWorker::getKeyboardInfo()
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        QDBusPendingCall asyncCall = m_dbusHardwareInfo->asyncCall("readKBInfo");
        if (!asyncCall.isError()) {
            // 创建异步调用监视器
            QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(asyncCall, this);
            // 连接监视器信号
            connect(watcher, SIGNAL(finished(QDBusPendingCallWatcher*)),
                             this, SLOT(onAsyncKeyboard(QDBusPendingCallWatcher*)));
        }
    } else {
        qWarning()<<"call hardwareinfo dbus failed!!";
    }
}

void DataWorker::onAsyncKeyboard(QDBusPendingCallWatcher* callWatcher)
{
    QDBusPendingReply<QString> reply = *callWatcher;
    if (!reply.isError()) {
        QString strInfoJson = reply.value();
        Q_EMIT updateKeyboardInfo(1, strInfoJson);
    }
    callWatcher->deleteLater();
}

void DataWorker::connectKBInfoSignal(bool bConnect)
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        if (bConnect) {
            connect(m_dbusHardwareInfo, SIGNAL(signalKBUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateKeyboardInfo(uint,QString)));
        } else {
            disconnect(m_dbusHardwareInfo, SIGNAL(signalKBUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateKeyboardInfo(unsigned,QString)));
        }
    } else {
        qWarning()<<"call hardwareinfo dbus failed!!";
    }
}

void DataWorker::getMouseInfo()
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        QDBusPendingCall asyncCall = m_dbusHardwareInfo->asyncCall("readMSInfo");
        if (!asyncCall.isError()) {
            // 创建异步调用监视器
            QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(asyncCall, this);
            // 连接监视器信号
            connect(watcher, SIGNAL(finished(QDBusPendingCallWatcher*)),
                             this, SLOT(onAsyncMouse(QDBusPendingCallWatcher*)));
        }
    } else {
        qWarning()<<"call hardwareinfo dbus failed!!";
    }
}

void DataWorker::onAsyncMouse(QDBusPendingCallWatcher* callWatcher)
{
    QDBusPendingReply<QString> reply = *callWatcher;
    if (!reply.isError()) {
        QString strInfoJson = reply.value();
        Q_EMIT updateMouseInfo(1, strInfoJson);
    }
    callWatcher->deleteLater();
}

void DataWorker::connectMSInfoSignal(bool bConnect)
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        if (bConnect) {
            connect(m_dbusHardwareInfo, SIGNAL(signalMSUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateMouseInfo(uint,QString)));
        } else {
            disconnect(m_dbusHardwareInfo, SIGNAL(signalMSUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateMouseInfo(unsigned,QString)));
        }
    } else {
        qWarning()<<"call hardwareinfo dbus failed!!";
    }
}

void DataWorker::genMonitorInfoDataFile(bool bUpdate)
{
    QString strMonitorInfoFile = "/tmp/youker-assistant-monitorinfo.dat";
    QFile tmpFile(strMonitorInfoFile);
    if (!bUpdate && tmpFile.exists())
        return;
    QString cmd = "xrandr --prop";
    QProcess *p = new QProcess();
    p->start(cmd);
    p->waitForFinished();
    // 将monitor信息写入临时文件
    if (!tmpFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream tsFile(&tmpFile);
    while(p->canReadLine()){
        QString str = p->readLine();
        str = str.left(str.length() - 1);
        tsFile<<str<<endl;  //写入文件
    }
    tmpFile.close();
    delete p;
}

void DataWorker::getMonitorInfo(bool bUpdate)
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        genMonitorInfoDataFile(bUpdate);
        QDBusPendingCall asyncCall = m_dbusHardwareInfo->asyncCall("readMNInfo");
        if (!asyncCall.isError()) {
            // 创建异步调用监视器
            QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(asyncCall, this);
            // 连接监视器信号
            connect(watcher, SIGNAL(finished(QDBusPendingCallWatcher*)),
                             this, SLOT(onAsyncMonitor(QDBusPendingCallWatcher*)));
        }
    } else {
        qWarning()<<"call hardwareinfo dbus failed!!";
    }
}

void DataWorker::onAsyncMonitor(QDBusPendingCallWatcher* callWatcher)
{
    QDBusPendingReply<QString> reply = *callWatcher;
    if (!reply.isError()) {
        QString strInfoJson = reply.value();
        Q_EMIT updateMonitorInfo(1, strInfoJson);
    }
    callWatcher->deleteLater();
}

void DataWorker::connectMNInfoSignal(bool bConnect)
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        if (bConnect) {
            connect(m_dbusHardwareInfo, SIGNAL(signalMNUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateMonitorInfo(uint,QString)));
        } else {
            disconnect(m_dbusHardwareInfo, SIGNAL(signalMNUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateMonitorInfo(unsigned,QString)));
        }
    } else {
        qWarning()<<"call hardwareinfo dbus failed!!";
    }
}

void DataWorker::getCDDriveInfo()
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        QDBusPendingCall asyncCall = m_dbusHardwareInfo->asyncCall("readCDInfo");
        if (!asyncCall.isError()) {
            // 创建异步调用监视器
            QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(asyncCall, this);
            // 连接监视器信号
            connect(watcher, SIGNAL(finished(QDBusPendingCallWatcher*)),
                             this, SLOT(onAsyncCDDrive(QDBusPendingCallWatcher*)));
        }
    } else {
        qWarning()<<"call hardwareinfo dbus failed!!";
    }
}

void DataWorker::onAsyncCDDrive(QDBusPendingCallWatcher* callWatcher)
{
    QDBusPendingReply<QString> reply = *callWatcher;
    if (!reply.isError()) {
        QString strInfoJson = reply.value();
        Q_EMIT updateCDDriveInfo(1, strInfoJson);
    }
    callWatcher->deleteLater();
}

void DataWorker::connectCDInfoSignal(bool bConnect)
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        if (bConnect) {
            connect(m_dbusHardwareInfo, SIGNAL(signalCDUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateCDDriveInfo(uint,QString)));
        } else {
            disconnect(m_dbusHardwareInfo, SIGNAL(signalCDUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateCDDriveInfo(unsigned,QString)));
        }
    } else {
        qWarning()<<"call hardwareinfo dbus failed!!";
    }
}

void DataWorker::getBatteryInfo()
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        QDBusPendingCall asyncCall = m_dbusHardwareInfo->asyncCall("readBTInfo");
        if (!asyncCall.isError()) {
            // 创建异步调用监视器
            QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(asyncCall, this);
            // 连接监视器信号
            connect(watcher, SIGNAL(finished(QDBusPendingCallWatcher*)),
                             this, SLOT(onAsyncBattery(QDBusPendingCallWatcher*)));
        }
    } else {
        qWarning()<<"call hardwareinfo dbus failed!!";
    }
}

void DataWorker::onAsyncBattery(QDBusPendingCallWatcher* callWatcher)
{
    QDBusPendingReply<QString> reply = *callWatcher;
    if (!reply.isError()) {
        QString strInfoJson = reply.value();
        Q_EMIT updateBatteryInfo(1, strInfoJson);
    }
    callWatcher->deleteLater();
}

void DataWorker::connectBTInfoSignal(bool bConnect)
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        if (bConnect) {
            connect(m_dbusHardwareInfo, SIGNAL(signalBTUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateBatteryInfo(uint,QString)));
        } else {
            disconnect(m_dbusHardwareInfo, SIGNAL(signalBTUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateBatteryInfo(unsigned,QString)));
        }
    } else {
        qWarning()<<"call hardwareinfo dbus failed!!";
    }
}

void DataWorker::getFanInfo()
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        QDBusPendingCall asyncCall = m_dbusHardwareInfo->asyncCall("readFAInfo");
        if (!asyncCall.isError()) {
            // 创建异步调用监视器
            QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(asyncCall, this);
            // 连接监视器信号
            connect(watcher, SIGNAL(finished(QDBusPendingCallWatcher*)),
                             this, SLOT(onAsyncFan(QDBusPendingCallWatcher*)));
        }
    } else {
        qWarning()<<"call hardwareinfo dbus failed!!";
    }
}

void DataWorker::onAsyncFan(QDBusPendingCallWatcher* callWatcher)
{
    QDBusPendingReply<QString> reply = *callWatcher;
    if (!reply.isError()) {
        QString strInfoJson = reply.value();
        Q_EMIT updateFanInfo(1, strInfoJson);
    }
    callWatcher->deleteLater();
}

void DataWorker::connectFAInfoSignal(bool bConnect)
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        if (bConnect) {
            connect(m_dbusHardwareInfo, SIGNAL(signalFAUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateFanInfo(uint,QString)));
        } else {
            disconnect(m_dbusHardwareInfo, SIGNAL(signalFAUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateFanInfo(unsigned,QString)));
        }
    } else {
        qWarning()<<"call hardwareinfo dbus failed!!";
    }
}

void DataWorker::getCameraInfo()
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        QDBusPendingCall asyncCall = m_dbusHardwareInfo->asyncCall("readCAInfo");
        if (!asyncCall.isError()) {
            // 创建异步调用监视器
            QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(asyncCall, this);
            // 连接监视器信号
            connect(watcher, SIGNAL(finished(QDBusPendingCallWatcher*)),
                             this, SLOT(onAsyncCamera(QDBusPendingCallWatcher*)));
        }
    } else {
        qWarning()<<"call hardwareinfo dbus failed!!";
    }
}

void DataWorker::onAsyncCamera(QDBusPendingCallWatcher* callWatcher)
{
    QDBusPendingReply<QString> reply = *callWatcher;
    if (!reply.isError()) {
        QString strInfoJson = reply.value();
        Q_EMIT updateCameraInfo(1, strInfoJson);
    }
    callWatcher->deleteLater();
}

void DataWorker::connectCAInfoSignal(bool bConnect)
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        if (bConnect) {
            connect(m_dbusHardwareInfo, SIGNAL(signalCAUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateCameraInfo(uint,QString)));
        } else {
            disconnect(m_dbusHardwareInfo, SIGNAL(signalCAUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateCameraInfo(unsigned,QString)));
        }
    } else {
        qWarning()<<"call hardwareinfo dbus failed!!";
    }
}

/**
 * @brief DataWorker::getOutline
 */
void DataWorker::getOutline()
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        genMonitorInfoDataFile(false);
        QDBusPendingCall asyncCall = m_dbusHardwareInfo->asyncCall("readOutline");
        if (!asyncCall.isError()) {
            // 创建异步调用监视器
            QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(asyncCall, this);
            // 连接监视器信号
            connect(watcher, SIGNAL(finished(QDBusPendingCallWatcher*)),
                             this, SLOT(onAsyncOutline(QDBusPendingCallWatcher*)));
        }
    } else {
        qWarning()<<"call hardwareinfo dbus failed!!";
    }
}

void DataWorker::onAsyncOutline(QDBusPendingCallWatcher* callWatcher)
{
    QDBusPendingReply<QString> reply = *callWatcher;
    if (!reply.isError()) {
        QString strInfoJson = reply.value();
        Q_EMIT updateOutline(1, strInfoJson);
    }
    callWatcher->deleteLater();
}

void DataWorker::connectOutlineSignal(bool bConnect)
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        if (bConnect) {
            connect(m_dbusHardwareInfo, SIGNAL(signalOutlineUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateOutline(uint,QString)));
        } else {
            disconnect(m_dbusHardwareInfo, SIGNAL(signalOutlineUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateOutline(unsigned,QString)));
        }
    } else {
        qWarning()<<"call hardwareinfo dbus failed!!";
    }
}

void DataWorker::getSysInfo()
{
    initDbusSession(&m_dbusSession, DBUSPATH_SESSIONDBUS);
    if (m_dbusSession && m_dbusSession->isValid()) {
        QDBusPendingCall asyncCall = m_dbusSession->asyncCall("readSysInfo");
        if (!asyncCall.isError()) {
            // 创建异步调用监视器
            QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(asyncCall, this);
            // 连接监视器信号
            connect(watcher, SIGNAL(finished(QDBusPendingCallWatcher*)),
                             this, SLOT(onAsyncSysInfo(QDBusPendingCallWatcher*)));
        }
    } else {
        qWarning()<<"call session dbus failed!!";
    }
}

void DataWorker::onAsyncSysInfo(QDBusPendingCallWatcher* callWatcher)
{
    QDBusPendingReply<QString> reply = *callWatcher;
    if (!reply.isError()) {
        QString strInfoJson = reply.value();
        Q_EMIT updateSysInfo(1, strInfoJson);
    }
    callWatcher->deleteLater();
}

void DataWorker::connectSysInfoSignal(bool bConnect)
{
    initDbusSession(&m_dbusSession, DBUSPATH_SESSIONDBUS);
    if (m_dbusSession && m_dbusSession->isValid()) {
        if (bConnect) {
            connect(m_dbusSession, SIGNAL(signalSysInfoUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateSysInfo(uint,QString)));
        } else {
            disconnect(m_dbusSession, SIGNAL(signalSysInfoUpdateInfo(unsigned,QString)),
                    this, SIGNAL(updateSysInfo(unsigned,QString)));
        }
    } else {
        qWarning()<<"call session dbus failed!!";
    }
}

bool DataWorker::getCpuTempEnable()
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        QDBusReply<bool> reply = m_dbusHardwareInfo->call("hide_temperature_page");
        if (reply.value()) {
            return true;
        }
    }
    return false;
}

bool DataWorker::getCpuFanEnable()
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        QDBusReply<bool> reply = m_dbusHardwareInfo->call("hide_fan_page");
        if (reply.value()) {
            return true;
        }
    }
    return false;
}

bool DataWorker::getCpuFMEnable()
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        QDBusReply<bool> reply = m_dbusHardwareInfo->call("hide_cpufm_page");
        if (reply.value()) {
            return true;
        }
    }
    return false;
}

bool DataWorker::updateLshwInfo(bool bForceUpdate)
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        QDBusPendingCall asyncCall = m_dbusHardwareInfo->asyncCall("reloadLshwInfo", bForceUpdate);
        if (!asyncCall.isError()) {
            // 创建异步调用监视器
            QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(asyncCall, this);
            // 连接监视器信号
            connect(watcher, SIGNAL(finished(QDBusPendingCallWatcher*)),
                             this, SLOT(onAsyncLshwInfo(QDBusPendingCallWatcher*)));
            return true;
        }
    } else {
        qWarning()<<"call hardwareinfo dbus failed!!";
    }
    return false;
}

void DataWorker::onAsyncLshwInfo(QDBusPendingCallWatcher* callWatcher)
{
    QDBusPendingReply<bool> reply = *callWatcher;
    if (!reply.isError()) {
        //bool bResult = reply.value();
        //Q_EMIT updateLshwFinished();
    }
    callWatcher->deleteLater();
}

void DataWorker::connectLshwInfoSignal(bool bConnect)
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        if (bConnect) {
            connect(m_dbusHardwareInfo, SIGNAL(signalLshwUpdateFinished()),
                    this, SIGNAL(updateLshwFinished()));
        } else {
            disconnect(m_dbusHardwareInfo, SIGNAL(signalLshwUpdateFinished()),
                    this, SIGNAL(updateLshwFinished()));
        }
    } else {
        qWarning()<<"call hardwareinfo dbus failed!!";
    }
}

bool DataWorker::exitDaemonDbus()
{
    initDbusInterface(&m_dbusHardwareInfo, DBUSPATH_HARDWAREINFO);
    if (m_dbusHardwareInfo && m_dbusHardwareInfo->isValid()) {
        m_dbusHardwareInfo->call("exit");
        return true;
    }
    return false;
}
