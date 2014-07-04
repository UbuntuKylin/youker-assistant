/*
 * Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd.
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
#include "sessiondispatcher.h"
#include "aboutdialog.h"

class Tray: public QWidget, private Ui::Tray
{
    Q_OBJECT
public:
    explicit Tray(QWidget *parent = 0);
    virtual ~Tray();
    QIcon icon;
    //创建托盘
    void createTray();
    QSystemTrayIcon *trayIcon;
    QMenu *trayMenu;
    //监控球、QML、关于、退出程序四个托盘菜单
    QAction *actionShow, *actionQml, *actionAbout, *actionQuit;

    virtual QSize sizeHint() const;
private:
    QPoint dragPos;
    SuspensionFrame *frame;
    SystemDispatcher *dispather;
    SessionDispatcher *sedispather;
    QString cpu_value;
    QString up_speed;
    QString down_speed;
    double used_memory;
    QString free_memory;
    int memory_size;
    double total_size;
    QString ratio;
    QStringList speed;
    QStringList total_speed;
    QSize initSize;
    QImage wheel;
    QPixmap blister;
    int ratio_sus;
    AboutDialog *aboutDlg;
    QTimer *timer;
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *event);

public slots:
    void handle_trayIcon_activated(QSystemTrayIcon::ActivationReason reason);
    //显示/隐藏监控球
    void showOrHide();
    //显示/隐藏QML主界面
    void showOrHideQml();
    //小监控球数据更新
    void updateData();
    //开始整理内存，一键加速
    void startMemoryAccelerate();
    //弹出关于本软件的对话框
    void showAboutWidget();
    //快捷键退出
    void exit();
signals:
    //显示/隐藏QML主界面的信号
    void showOrHideQmlSignal();
    //将小监控球实时更新的数据同步到大监控球
    void sysc_data(QString upspeed, QString downspeed, QString ratio, int used_memory, QString free_memory, QString cpu_ratio);
};

#endif
