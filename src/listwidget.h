#ifndef INFOLISTWIDGET_H
#define INFOLISTWIDGET_H

#include <QWidget>
#include <QString>
#include <QStackedWidget>
#include <QStringList>
#include <QListView>
#include <QListWidget>
#include <QSplitter>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>

#include <QDBusMessage>

class InfoWidget;
class InfoGui;

class MListwidget : public QWidget
{
    Q_OBJECT
public:
    explicit MListwidget(QWidget *parent = nullptr);
    void InitListUI();
    void InitInfowidgetUI();
    void setBatteryAndSensor(bool battery,bool sensor,QMap<QString,bool> info);
signals:
    void m_requestRefreshSystemInfo();

    //desktop info
    void List_requestDesktopInfo();
    void requestDesktopInfo_send(QMap<QString, QVariant> tmpMap);

    //cpu info
    void List_requestCpuInfo();
    void requestCpuInfo_send(QMap<QString, QVariant> tmpMap);

    //memory info
    void List_requestMemoryInfo();
    void requestMemoryInfo_send(QMap<QString, QVariant> tmpMap);

    //board info
    void List_requestBoardInfo();
    void requestBoardInfo_send(QMap<QString, QVariant> tmpMap);

    //hd info
    void List_requestHDInfo();
    void requestHDInfo_send(QMap<QString, QVariant> tmpMap);

    //nic info
    void List_requestNicInfo();
    void requestNicInfo_send(QMap<QString, QVariant> tmpMap);

    //monitor info
    void List_requestMonitorInfo();
    void requestMonitorInfo_send(QMap<QString, QVariant> tmpMap);

    //audio info
    void List_requestAudioInfo();
    void requestAudioInfo_send(QMap<QString, QVariant> tmpMap);

    //battery info
    void List_requestBatteryInfo();
    void requestBatteryInfo_send(QMap<QString, QVariant> tmpMap);

    //sensor info
    void List_requestSensorInfo();
    void requestSensorInfo_send(QMap<QString, QVariant> tmpMap);

public slots:
    void changeListwidgetpage(QListWidgetItem* item);

    void onSendSystemInfo(QMap<QString, QVariant> tmpMap);

    void onSendDesktopInfo_next(QMap<QString, QVariant> tmpMap);
    void onSendDesktopInfo_signal();

    void onSendCpuInfo_next(QMap<QString, QVariant> tmpMap);
    void onSendCpuInfo_signal();

    void onSendMemoryInfo_next(QMap<QString, QVariant> tmpMap);
    void onSendMemoryInfo_signal();

    void onSendBoardInfo_next(QMap<QString, QVariant> tmpMap);
    void onSendBoardInfo_signal();

    void onSendHDInfo_next(QMap<QString, QVariant> tmpMap);
    void onSendHDInfo_signal();

    void onSendNicInfo_next(QMap<QString, QVariant> tmpMap);
    void onSendNicInfo_signal();

    void onSendMonitorInfo_next(QMap<QString, QVariant> tmpMap);
    void onSendMonitorInfo_signal();

    void onSendAudioInfo_next(QMap<QString, QVariant> tmpMap);
    void onSendAudioInfo_signal();

    void onSendBatteryInfo_next(QMap<QString, QVariant> tmpMap);
    void onSendBatteryInfo_signal();

    void onSendSensorInfo_next(QMap<QString, QVariant> tmpMap);
    void onSendSensorInfo_signal();

private:
    QSplitter *splitter = nullptr;
    QStackedWidget *stackedwidget = nullptr;
    QListWidget *listview = nullptr;
    InfoWidget *info_widget = nullptr;
    InfoGui *system_widget = nullptr;
    QStringList stringlist;
    bool has_Battery = false;
    bool has_Sensor = false;
    QMap<QString,bool> all_info;
};

#endif // INFOLISTWIDGET_H
