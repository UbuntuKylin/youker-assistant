/*
 * Copyright (C) 2013 ~ 2015 National University of Defense Technology(NUDT) & Kylin Ltd.
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
#include <QToolButton>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QPainter>
#include <QPen>
#include <QHBoxLayout>
#include <QEvent>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QList>
#include <QStackedWidget>
//#include "infotype.h"
#include "../info/systemwidget.h"
#include "../info/desktopwidget.h"
#include "../info/cpuwidget.h"
#include "../info/memorywidget.h"
#include "../info/boardwidget.h"
#include "../info/hdwidget.h"
#include "../info/nicwidget.h"
#include "../info/monitorwidget.h"
#include "../info/audiowidget.h"
#include "../info/cdrowwidget.h"
#include "../info/batterywidget.h"
#include "../info/driverwidget.h"

#include <QScrollArea>
//#include "../dbusproxy/youkersystemdbus.h"
class SessionDispatcher;
class SystemDispatcher;


class InfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InfoWidget(QWidget *parent = 0);
    ~InfoWidget();
    void setSessionDbusProxy(SessionDispatcher *dispatcher) { sessionProxy = dispatcher;}
    void setSystemDbusProxy(SystemDispatcher *dispatcher) { systemProxy = dispatcher;}
    void initUI();

signals:

public slots:
    void changeInfoPage(QListWidgetItem* item);

//    void change_box_index(int index);
private:
    QSplitter *splitter;
    QListWidget *category_widget;
    QStringList type_list;
    QStringList icon_list;
    QStackedWidget *stacked_widget;
    SystemWidget *system_widget;
    DesktopWidget *desktop_widget;
    CpuWidget *cpu_widget;
    MemoryWidget *memory_widget;
    BoardWidget *board_widget;
    HDWidget *hd_widget;
    NicWidget *nic_widget;
    MonitorWidget *monitor_widget;
    AudioWidget *audio_widget;
    CDRowWidget *cdrom_widget;
    BatteryWidget *battery_widget;
    DriverWidget *driver_widget;
    QWidget *right_widget;
    QString current_tip;
//    QList<InfoType> *categoryList;


//    QWidget *device_content;
//    QWidget *logo_view;
//    SystemDispatcher systemproxy;
    SessionDispatcher *sessionProxy;
    SystemDispatcher *systemProxy;
};

#endif // INFOWIDGET_H
