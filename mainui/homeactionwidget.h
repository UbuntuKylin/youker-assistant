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

#ifndef HOMEACTIONWIDGET_H
#define HOMEACTIONWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QSignalMapper>
#include <QVBoxLayout>
#include <QSettings>
#include "../component/kylinbutton.h"
#include "../component/systembutton.h"
#include "../component/loadinglabel.h"

class MainWindow;
class SessionDispatcher;
class SystemDispatcher;

class HomeActionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HomeActionWidget(QWidget *parent = 0, QSettings *mSettings = 0);
    ~HomeActionWidget();
    void setParentWindow(MainWindow* window) { p_mainwindow = window;}
    void setSessionDbusProxy(SessionDispatcher* dispatcher) { sessionProxy = dispatcher;}
    void setSystemDbusProxy(SystemDispatcher* dispatcher) { systemProxy = dispatcher;}
    void initConnect();
    void setLanguage();
    void writeFixCleanDate();
    QString getFixCleanDate();
    QString getCurrentDateTime();
    void writeSafeScanDate();
    QString getSafeScanDate();
    QString getOneKeyFlag();

    void enableSanButton();

public slots:
    void onStartButtonClicked();
    void onCleanButtonClicked();
    void onEndButtonClicked();
    void getScanResult(QString msg);
    void finishScanResult(QString msg);
    void getScanAllResult(QString flag, QString msg);
    void getCleanResult(QString msg/*, QString flag*/);
    void finishCleanError(QString msg);
    void getCleaningMessage(QString type, QString status);

private:
    QPoint press_point;//鼠标按下去的点
    bool is_move;
    LoadingLabel *loading_label;
    QLabel *suggest_label;
    QLabel *scan_result_label;
    QLabel *result_label;
    QLabel *doing_label;
    QPushButton *scan_button;
    QPushButton *clean_button;
    QPushButton *back_button;

    MainWindow *p_mainwindow;
    SystemDispatcher *systemProxy;
    SessionDispatcher *sessionProxy;
    QString trace;
    QString cookies;
    QString garbage;
    QSettings *pSettings;
    QString dateStr;
    QString workFlag;
    QString scanFinishTime;
};

#endif // HOMEACTIONWIDGET_H
