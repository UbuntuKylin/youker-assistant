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

#ifndef MAINTOPWIDGET_H
#define MAINTOPWIDGET_H

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

class MainTopWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainTopWidget(bool isMain = false, QSettings *mSettings = 0, QWidget *parent = 0);
    ~MainTopWidget();
    void setParentWindow(MainWindow* window) { p_mainwindow = window;}
    void initConnect();
    void setLanguage();
    void writeFixCleanDate();
    QString getFixCleanDate();
    QString getCurrentDateTime();
    void writeSafeScanDate();
    QString getSafeScanDate();
    QString getOneKeyFlag();

    void setDoingLabelText(const QString &description, int defaultWidth = 700);

    void initTitlebarLeftContent();
    void initTitlebarRightContent();
    void initContentLeftContent();
    void initActionRightContent();
    void initWidgets();

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


    //clean page
    void showCleanReciveStatus(const QString &status);
    void showCleanReciveError(const QString &status);
    void showCleanOverStatus();
    void showCleanerData(const QStringList &data);
    void showCleanerStatus(const QString &status, const QString &domain);
    void showCleanerError(const QString &status);
    void displayOrgPage();
    void displayAnimation();
    void receivePolicyKitSignal(bool status);
    void accordScanOverStatusToChange(bool status);

signals:
    void startOneKeyScan(const QStringList &categorys);
    void startOneKeyClean();

    //clean page
    void showDetailData();
    void showMainData();
    void sendCleanSignal();
    void sendScanSignal();

    void showMenu();
    void showSkinCenter();
    void showMin();
    void closeApp();

private:
    LoadingLabel *loading_label = nullptr;
    QLabel *suggest_label = nullptr;
    QLabel *scan_result_label = nullptr;
    QLabel *result_label = nullptr;
    QLabel *doing_label = nullptr;
    QPushButton *scan_button = nullptr;
    QPushButton *clean_button = nullptr;
    QPushButton *back_button = nullptr;

    QString trace;
    QString cookies;
    QString garbage;
    QSettings *pSettings;
    QString dateStr;
    QString workFlag;
    QString scanFinishTime;

    QVBoxLayout *m_layout = nullptr;
    QHBoxLayout *m_topLayout = nullptr;
    QHBoxLayout *m_titleRightLayout = nullptr;
    QHBoxLayout *m_bottomLayout = nullptr;
    QHBoxLayout *m_titleLeftLayout = nullptr;
    QHBoxLayout *m_toolLeftLayout = nullptr;
    QHBoxLayout *m_toolRightLayout = nullptr;

    MainWindow *p_mainwindow = nullptr;

    bool m_isMain;
};

#endif // MAINTOPWIDGET_H
