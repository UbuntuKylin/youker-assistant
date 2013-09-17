/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  Kobe Lee    kobe24_lixiang@126.com
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
#ifndef SUDODISPATCHER_H
#define SUDODISPATCHER_H

#include <QObject>
#include <QDBusInterface>
#include <QDBusConnection>
#include <QApplication>
#include <QString>
#include <QDeclarativeView>
#include "authdialog.h"
#include "progressdialog.h"
#include "updatedialog.h"
class SudoDispatcher : public QObject
{
    Q_OBJECT
public:
    explicit SudoDispatcher(QObject *parent = 0);
    ~SudoDispatcher();
    Q_INVOKABLE void exit_qt();
    Q_INVOKABLE void show_passwd_dialog(int window_x, int window_y);
    Q_INVOKABLE void show_progress_dialog(int window_x, int window_y);
    Q_INVOKABLE void show_update_dialog(int window_x, int window_y);
    Q_INVOKABLE QString get_sudo_daemon_qt();
    Q_INVOKABLE void clean_package_cruft_qt(QStringList strlist);
    Q_INVOKABLE void bind_signals_after_dbus_start();
    QDBusInterface *sudoiface;
    AuthDialog *authdialog;
    ProgressDialog *progressdialog;
    UpdateDialog *updatedialog;

    QMap<QString, QString> status_dict;
    Q_INVOKABLE QString get_value(QString);
    Q_INVOKABLE QStringList getUKSoftwareList();
    Q_INVOKABLE void send_software_current_status(QString current_status);


    // -------------------------software-center-------------------------
    Q_INVOKABLE void install_pkg_qt(QString pkgName);
    Q_INVOKABLE void uninstall_pkg_qt(QString pkgName);
    Q_INVOKABLE void update_pkg_qt(QString pkgName);
    Q_INVOKABLE void check_pkgs_status_qt(QStringList pkgNameList);
    Q_INVOKABLE QString check_pkg_status_qt(QString pkgName);
    Q_INVOKABLE void apt_get_update_qt();
    Q_INVOKABLE QStringList get_args();
signals:
    void finishCleanWork(QString msg);//绑定到QML的Handler：onFinishCleanWork
    void finishCleanWorkError(QString msg);
    void finishSoftwareFetch(QString type, QString msg);
    void finishSoftwareApt(QString type);
    void finishSoftwareCheckStatus(QStringList statusDict);
    void finishSoftwareStatus(QString current_status);

    void getValue(QString type, QString msg);
    void finishGetSourceStatus(QString cur_status);
    void callMasklayer();

public slots:
    void handler_clear_rubbish(QString msg);
    void handler_clear_rubbish_error(QString msg);
    void handler_software_fetch_signal(QString type, QString msg);
    void handler_software_apt_signal(QString type, QString msg);
    void handler_software_check_status_signal(QStringList statusDict);
    void start_to_update();
    void get_software_source_progress(QString cur_status);
private:
    QStringList strlist;
    int mainwindow_width;
    int mainwindow_height;
    int alert_width;
    int alert_height;
    int alert_width_bg;
    //本次alert的x坐标
    int alert_x;
    //保额次alert的y坐标
    int alert_y;
};

#endif // SUDODISPATCHER_H
