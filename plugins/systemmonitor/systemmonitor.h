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

#ifndef SYSTEMMONITOR_H
#define SYSTEMMONITOR_H

#include "monitortitlewidget.h"
#include "processdialog.h"
#include "resourcesdialog.h"
#include "filesystemdialog.h"

#include <QFrame>
#include <QStackedWidget>
#include <QLabel>
#include <QSettings>

class SystemMonitor : public QFrame
{
    Q_OBJECT

public:
    SystemMonitor(QWidget *parent = 0);
    ~SystemMonitor();

    void initTitleWidget();
    void initPanelStack();
    void initConnections();

    QList<bool> getReadyDisplayProcessColumns();
    bool isSortOrNot();
    int getCurrentSortColumnIndex();

    QList<bool> getReadyDisplayFileSysColumns();

    void moveCenter();

public slots:
    void recordProcessVisibleColumn(int, bool, QList<bool> columnVisible);
    void recordSortStatus(int index, bool isSort);
    void recordFileSysVisibleColumn(int, bool, QList<bool> columnVisible);
    void onChangePage(int index);

protected:
    void resizeEvent(QResizeEvent *e) override;
//    void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent *event);
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    QStackedWidget  *m_sysMonitorStack = nullptr;
    MonitorTitleWidget  *m_titleWidget = nullptr;
//    ToolBar *m_toolBar = nullptr;
    ProcessDialog *process_dialog = nullptr;
    ResouresDialog *resources_dialog = nullptr;
    FileSystemDialog *filesystem_dialog = nullptr;
    QSettings *proSettings;

    QPoint dragPosition;
    bool mousePressed;
};

#endif // SYSTEMMONITOR_H
