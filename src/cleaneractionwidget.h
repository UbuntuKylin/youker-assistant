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

#ifndef CLEANERACTIONWIDGET_H
#define CLEANERACTIONWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QSignalMapper>
#include <QVBoxLayout>
#include "../component/kylinbutton.h"
#include "../component/systembutton.h"
#include "../component/loadinglabel.h"

class SessionDispatcher;
class SystemDispatcher;

class CleanerActionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CleanerActionWidget(QWidget *parent = 0);
    ~CleanerActionWidget();
    void setSessionDbusProxy(SessionDispatcher* dispatcher) { sessionProxy = dispatcher;}
    void setSystemDbusProxy(SystemDispatcher* dispatcher) { systemProxy = dispatcher;}
    void initConnect();
    void setLanguage();

public slots:
    void onStartButtonClicked();
    void onCleanButtonClicked();
    void onBackButtonClicked();
    void showCleanReciveStatus(const QString &status);
    void showCleanReciveError(const QString &status);
    void showCleanOverStatus();
    void showCleanerData(const QStringList &data);
    void showCleanerStatus(const QString &status, const QString &domain);
    void showCleanerError(const QString &status);
    void displayOrgPage();
    void displayAnimation();
//    void displayCleanAnimation();
    void receivePolicyKitSignal(bool status);
    void accordScanOverStatusToChange(bool status);

signals:
    void showDetailData();
    void showMainData();
    void sendCleanSignal();
    void sendScanSignal();

private:
    bool is_move;
    LoadingLabel *loading_label;
    QLabel *suggest_label;
    QLabel *doing_label;
    QPushButton *scan_button;
    QPushButton *clean_button;
    QPushButton *back_button;

    SystemDispatcher *systemProxy;
    SessionDispatcher *sessionProxy;
};

#endif // CLEANERACTIONWIDGET_H
