/*
 * Copyright (C) 2013 ~ 2018 National University of Defense Technology(NUDT) & Tianjin Kylin Ltd.
 *
 * Authors:
 *  Kobe Lee    xiangli@ubuntukylin.com/kobe24_lixiang@126.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef INFOWIDGET_H
#define INFOWIDGET_H

#include <QWidget>
#include <QSplitter>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QPen>
#include <QHBoxLayout>
#include <QEvent>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QList>
#include <QStackedWidget>
#include <QScrollArea>

#include <QDBusMessage>
#include <QDBusConnection>

class TestWidget;
class InfoGui;

class InfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InfoWidget(QString machine = "", QWidget *parent = 0);
    ~InfoWidget();

    void initInfoUI(bool has_battery, bool has_sensor);
    void resetInfoLeftListUI(QStringList keys);

public slots:
    void changeInfoPage(QListWidgetItem* item,QListWidgetItem* item1);

    void onSendSystemInfo(QMap<QString, QVariant> tmpMap);
//    void onSendSystemRunnedTime(int time_value);
    void onSendDesktopInfo(QMap<QString, QVariant> tmpMap);
    void onSendCpuInfo(QMap<QString, QVariant> tmpMap);
    void onSendMemoryInfo(QMap<QString, QVariant> tmpMap);
    void onSendBoardInfo(QMap<QString, QVariant> tmpMap);
    void onSendHDInfo(QMap<QString, QVariant> tmpMap);
    void onSendNicInfo(QMap<QString, QVariant> tmpMap);
    void onSendMonitorInfo(QMap<QString, QVariant> tmpMap);
    void onSendAudioInfo(QMap<QString, QVariant> tmpMap);
    void onSendBatteryInfo(QMap<QString, QVariant> tmpMap);
    void onSendSensorInfo(QMap<QString, QVariant> tmpMap);
    void onSendCDROMInfo(QMap<QString, QVariant> tmpMap);
    void onSendInputInfo(QDBusMessage msg);
    void onSendMultimediaInfo(QDBusMessage msg);
    void onSendCommunicationInfo(QDBusMessage msg);
    void onSendDisplayInfo(QDBusMessage msg);
//    void updateTimeValue();
    void paintEvent(QPaintEvent *);
    void onUDevHotPluginAdd(QString strUdevSubName, QString strUdevType);
    void onUDevHotPluginRemove(QString strUdevSubName, QString strUdevType);

signals:
    void emit_network_info(QMap<QString, QVariant> info);

    //system info
    void requestupdateSystemRunnedTime();
    void requestRefreshSystemInfo();
//    void sendSystemRunnedTime(int time_value);
//    void sendSystemInfo(QMap<QString, QVariant> tmpMap);

    //desktop info
    void requestDesktopInfo();
//    void sendDesktopInfo(QMap<QString, QVariant> tmpMap);

    //cpu info
    void requestCpuInfo();
//    void sendCpuInfo(QMap<QString, QVariant> tmpMap);

    //memory info
    void requestMemoryInfo();
//    void sendMemoryInfo(QMap<QString, QVariant> tmpMap);

    //board info
    void requestBoardInfo();
//    void sendBoardInfo(QMap<QString, QVariant> tmpMap);

    //hd info
    void requestHDInfo();
//    void sendHDInfo(QMap<QString, QVariant> tmpMap);

    //nic info
    void requestNicInfo();
//    void sendNicInfo(QMap<QString, QVariant> tmpMap);

    //monitor info
    void requestMonitorInfo();
//    void sendMonitorInfo(QMap<QString, QVariant> tmpMap);

    //audio info
    void requestAudioInfo();
//    void sendAudioInfo(QMap<QString, QVariant> tmpMap);

    //battery info
    void requestBatteryInfo();
//    void sendBatteryInfo(QMap<QString, QVariant> tmpMap);

    //sensor info
    void requestSensorInfo();
//    void sendSensorInfo(QMap<QString, QVariant> tmpMap);

    //sensor info
    void requestCDROMInfo();

    //driver info

    //input info
    void requestInputInfo();

    //communication info
    void requestCommunicationInfo();
    
private:
    QSplitter *splitter = nullptr;
    QListWidget *category_widget = nullptr;
    QListWidget *category_widget1 = nullptr;
    QListWidgetItem *default_listitem = nullptr;
    QListWidget *default_widget = nullptr;

    QStringList type_list;
    QStringList icon_list;
    QStackedWidget *stacked_widget = nullptr;

    InfoGui *system_widget = nullptr;
//    QList<InfoGui *> m_pageList;

//    InfoGui *desktop_widget = nullptr;
//    InfoGui *cpu_widget = nullptr;
//    InfoGui *memory_widget = nullptr;
//    InfoGui *board_widget = nullptr;
//    InfoGui *hd_widget = nullptr;
//    InfoGui *nic_widget = nullptr;
//    InfoGui *monitor_widget = nullptr;
//    InfoGui *audio_widget = nullptr;
//    InfoGui *battery_widget = nullptr;
//    InfoGui *driver_widget = nullptr;
//    InfoGui *sensor_widget = nullptr;
//    InfoGui *m_testWidget = nullptr;

    QString current_tip;
    QString arch;

    bool firstLoadInputDev;
    bool firstLoadMultiMediaDev;
    bool firstLoadCommunicationDev;
    bool firstLoadDisplayDev;
};

#endif // INFOWIDGET_H
