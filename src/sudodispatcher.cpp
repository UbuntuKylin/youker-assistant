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
#include "sudodispatcher.h"
#include <QDebug>
#include <QProcessEnvironment>
#include <QtDBus>
#include <QMap>
#include "KThread.h"
bool progress_flag;

SudoDispatcher::SudoDispatcher(QObject *parent) :
    QObject(parent)
{
    sudoiface = new QDBusInterface("com.ubuntukylin.Ihu",
                               "/",
                               "com.ubuntukylin.Ihu",
                               QDBusConnection::systemBus());
    progressdialog = new ProgressDialog;
    updatedialog = new UpdateDialog;
    strlist << "Kobe" << "Lee";

    this->mainwindow_width = 850;
    this->mainwindow_height = 600;
    this->alert_width = 292;
    this->alert_width_bg = 329;
    this->alert_height = 54;
//    QObject::connect(sudoiface,SIGNAL(clean_complete(QString)),this,SLOT(handler_clear_rubbish(QString)));
//    QObject::connect(sudoiface,SIGNAL(clean_error(QString)),this,SLOT(handler_clear_rubbish_error(QString)));
}

SudoDispatcher::~SudoDispatcher() {
    this->exit_qt();
    if (authdialog) {
        delete authdialog;
    }
    if(progressdialog) {
        delete progressdialog;
    }
    if(updatedialog) {
        delete updatedialog;
    }
}

void SudoDispatcher::exit_qt() {
    sudoiface->call("exit");
}

void SudoDispatcher::bind_signals_after_dbus_start() {
    sudoiface = new QDBusInterface("com.ubuntukylin.Ihu",
                               "/",
                               "com.ubuntukylin.Ihu",
                               QDBusConnection::systemBus());
    QObject::connect(sudoiface,SIGNAL(clean_complete(QString)),this,SLOT(handler_clear_rubbish(QString)));
    QObject::connect(sudoiface,SIGNAL(clean_error(QString)),this,SLOT(handler_clear_rubbish_error(QString)));
    QObject::connect(sudoiface,SIGNAL(software_fetch_signal(QString,QString)),this,SLOT(handler_software_fetch_signal(QString,QString)));
    QObject::connect(sudoiface,SIGNAL(software_apt_signal(QString,QString)),this,SLOT(handler_software_apt_signal(QString,QString)));
    QObject::connect(sudoiface,SIGNAL(software_check_status_signal(QStringList)),this,SLOT(handler_software_check_status_signal(QStringList)));
    QObject::connect(this,SIGNAL(getValue(QString,QString)),progressdialog, SLOT(setValue(QString,QString)));
    QObject::connect(updatedialog,SIGNAL(call_update()),this, SLOT(start_to_update()));
    QObject::connect(progressdialog,SIGNAL(update_software_progress(QString)),this, SLOT(get_software_source_progress(QString)));
}

QString SudoDispatcher::get_sudo_daemon_qt() {
    QDBusReply<QString> reply = sudoiface->call("get_sudo_daemon");
    return reply.value();
}

void SudoDispatcher::get_software_source_progress(QString cur_status) {
    emit finishGetSourceStatus(cur_status);
}

void SudoDispatcher::handler_clear_rubbish(QString msg) {
     emit finishCleanWork(msg);
}

void SudoDispatcher::handler_clear_rubbish_error(QString msg) {
     emit finishCleanWorkError(msg);
}

void SudoDispatcher::handler_software_fetch_signal(QString type, QString msg) {
    if(!type.isEmpty()) {
        emit getValue(type, msg);
        if(type == "down_stop") {
            emit finishSoftwareFetch(type, msg);
        }
    }
//    emit finishSoftwareFetch(type, msg);
}

void SudoDispatcher::handler_software_apt_signal(QString type, QString msg) {
    if(!type.isEmpty()) {
        emit getValue(type, msg);
        if (type == "apt_stop") {
            emit finishSoftwareApt(type);
        }
    } 
}

void SudoDispatcher::handler_software_check_status_signal(QStringList statusDict) {
    status_dict.clear();
    for(int i=0; i< statusDict.size(); i++) {
        QStringList value = statusDict[i].split(":");
        status_dict.insert(value[0], value[1]);
    }
//    qDebug() << status_dict;
//    emit finishSoftwareCheckStatus(statusDict);
}

void SudoDispatcher::show_passwd_dialog(int window_x, int window_y) {
    authdialog = new AuthDialog("提示：请输入当前用户登录密码启动服务，保证优客助手的正常使用。");
    this->alert_x = window_x + (mainwindow_width / 2) - (alert_width_bg  / 2);
    this->alert_y = window_y + mainwindow_height - 400;
    authdialog->move(this->alert_x, this->alert_y);
    authdialog->exec();
}

void SudoDispatcher::show_update_dialog(int window_x, int window_y) {
    progress_flag = true;
    this->alert_x = window_x + (mainwindow_width / 2) - (alert_width  / 2);
    this->alert_y = window_y + mainwindow_height - 400;
    updatedialog->move(this->alert_x, this->alert_y);
    updatedialog->show();
}

void SudoDispatcher::show_progress_dialog(int window_x, int window_y) {
//    ProgressDialog progressdialog;
//    progressdialog.exec();
//    progressdialog = new ProgressDialog (window_x, window_y);
//    progressdialog->exec();
    progress_flag = false;
    this->alert_x = window_x + (mainwindow_width / 2) - (alert_width  / 2);
    this->alert_y = window_y + mainwindow_height - 400;
    progressdialog->move(this->alert_x, this->alert_y);
    progressdialog->show();
}

void SudoDispatcher::clean_package_cruft_qt(QStringList strlist) {
    KThread *thread = new KThread(sudoiface, "clean_package_cruft", strlist);
    thread->start();
}

QStringList SudoDispatcher::get_args() {
    QStringList pkgNameList;
    pkgNameList << "eclipse" << "qtcreator"<< "wps-office" << "wine-qq2012-longeneteam" << \
                   "flashplugin-installer" <<  "lotus" << "kuaipan4UK" <<"vlc" << \
                   "chromium-bsu" << "kugou" << "ppstream" << "qbittorrent" << \
                   "virtualbox" << "stardict" << "xchat" << "wine-thunder";
    return pkgNameList;
}

QString SudoDispatcher::get_value(QString key) {
    QVariant tt = status_dict.value(key);
    return tt.toString();
}

// -------------------------software-center-------------------------
void SudoDispatcher::install_pkg_qt(QString pkgName) {
    KThread *thread = new KThread(sudoiface, "install_pkg", strlist, pkgName);
    thread->start();
}

void SudoDispatcher::uninstall_pkg_qt(QString pkgName) {
    KThread *thread = new KThread(sudoiface, "uninstall_pkg", strlist, pkgName);
    thread->start();
}

void SudoDispatcher::update_pkg_qt(QString pkgName) {
    KThread *thread = new KThread(sudoiface, "update_pkg", strlist, pkgName);
    thread->start();
}

void SudoDispatcher::check_pkgs_status_qt(QStringList pkgNameList) {
    sudoiface->call("check_pkgs_status", pkgNameList);
}

QString SudoDispatcher::check_pkg_status_qt(QString pkgName) {
    QDBusReply<QString> reply = sudoiface->call("check_pkg_status", pkgName);
    return reply.value();
}

void SudoDispatcher::send_software_current_status(QString current_status) {
    emit finishSoftwareStatus(current_status);
}

void SudoDispatcher::apt_get_update_qt() {
    QStringList tmplist;
    tmplist << "Kobe" << "Lee";
    KThread *thread = new KThread(sudoiface, "apt_get_update", tmplist);
    thread->start();
}

void SudoDispatcher::start_to_update() {
    progressdialog->hide();
    emit callMasklayer();
    apt_get_update_qt();
}
