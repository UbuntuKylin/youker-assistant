/*
 * This file is part of the chinese-calendar project
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * This project is developed by "UbuntuKylin Members" team,
 * see <https://launchpad.net/~ubuntukylin~members>
 * Authors: Abel Liu <guiltyritter@gmail.com>
 *                 Shine Huang <hostc@163.com>
 */

#ifndef TRAY_H
#define TRAY_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QtGui>
#include <QAction>
#include "ui_tray.h"
#include "suspensionframe.h"

#include "systemdispatcher.h"

class Tray: public QWidget, private Ui::Tray
{
    Q_OBJECT
public:
    explicit Tray(QWidget *parent = 0);
    virtual ~Tray();
    QIcon icon;
    void createTray();

    QSystemTrayIcon *trayIcon;
    QMenu *trayMenu;
    QAction *actionShow, *actionQuit;
private:
    QPoint dragPos;
    SuspensionFrame *frame;
    SystemDispatcher *dispather;

    QString cpu_value;
    QString up_speed;
    QString down_speed;
    double used_memory;
    QString free_memory;
    int memory_size;
    double total_size;
    QString ratio;
    QStringList speed;
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

public slots:
    void handle_trayIcon_activated(QSystemTrayIcon::ActivationReason reason);
    void showOrHide();
    void obtain_network_speed(QStringList speed);
    void updateData();
    void start_to_accelerate();
signals:
    void showFloat();
    void sysc_data(QStringList speed, QString ratio, int used_memory, QString free_memory, QString cpu_ratio);
};

#endif
