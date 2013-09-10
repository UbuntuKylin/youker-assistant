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
//#include "progressdialog.h"
#include <QMap>
#include "KThread.h"
//extern QString passwd;

SudoDispatcher::SudoDispatcher(QObject *parent) :
    QObject(parent)
{
    sudoiface = new QDBusInterface("com.ubuntukylin.Ihu",
                               "/",
                               "com.ubuntukylin.Ihu",
                               QDBusConnection::systemBus());
    progressdialog = new ProgressDialog;
//    QObject::connect(sudoiface,SIGNAL(clean_complete(QString)),this,SLOT(handler_clear_rubbish(QString)));
//    QObject::connect(sudoiface,SIGNAL(clean_error(QString)),this,SLOT(handler_clear_rubbish_error(QString)));
}

SudoDispatcher::~SudoDispatcher()
{
    if (authdialog)
        delete authdialog;
    if(progressdialog)
        delete progressdialog;
}

void SudoDispatcher::exit_qt()
{
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
}

QString SudoDispatcher::get_sudo_daemon_qt() {
    QDBusReply<QString> reply = sudoiface->call("get_sudo_daemon");
    return reply.value();
}

void SudoDispatcher::handler_clear_rubbish(QString msg)
{
     emit finishCleanWork(msg);
}

void SudoDispatcher::handler_clear_rubbish_error(QString msg)
{
     emit finishCleanWorkError(msg);
}

void SudoDispatcher::handler_software_fetch_signal(QString type, QString msg)
{
    qDebug() << "get software_fetch_signal.....";
    qDebug() << type;
    qDebug() << msg;
    if(!type.isEmpty()) {
        emit getValue(type, msg);
    }
//    emit finishSoftwareFetch(type, msg);
}

void SudoDispatcher::handler_software_apt_signal(QString type, QString msg)
{
    qDebug() << "get software_apt_signal.....";
    qDebug() << type;
    qDebug() << msg;
    if(!type.isEmpty()) {
        emit getValue(type, msg);
    }
//    emit finishSoftwareApt(type, msg);
}

//void SudoDispatcher::handler_software_check_status_signal(QMap<QString, QVariant> statusDict)
void SudoDispatcher::handler_software_check_status_signal(QStringList statusDict)
{
//    qDebug() << "get software_check_status_signal.....";
    qDebug() << statusDict;
//    status_dict = statusDict;
//    emit finishSoftwareCheckStatus(statusDict);
}

void SudoDispatcher::show_passwd_dialog() {
    authdialog = new AuthDialog("提示：请输入当前用户登录密码，保证优客助手的正常使用。");
    authdialog->exec();
}

void SudoDispatcher::show_progress_dialog() {
//    ProgressDialog progressdialog;
//    progressdialog.exec();
//    ProgressDialog progressdialog("正在下载...");
//    progressdialog->exec();
    progressdialog->show();
}

void SudoDispatcher::clean_package_cruft_qt(QStringList strlist) {
    sudoiface->call("clean_package_cruft", strlist);
}

QStringList SudoDispatcher::get_args() {
    QStringList pkgNameList;
    pkgNameList << "qtcreator" << "qtcreator-plugin-ubuntu"<< "ubiquity";
    return pkgNameList;
}

// -------------------------software-center-------------------------
void SudoDispatcher::install_pkg_qt(QString pkgName) {
    qDebug() << "start to install";
    qDebug() << pkgName;
    QStringList strlist;
    strlist << "Kobe" << "Lee";
    KThread *thread = new KThread(sudoiface, "install_pkg", strlist, pkgName);
    thread->start();
//    sudoiface->call("install_pkg", pkgName);
}
void SudoDispatcher::uninstall_pkg_qt(QString pkgName) {

//    sudoiface->call("uninstall_pkg", pkgName);
    QStringList strlist;
    strlist << "Kobe" << "Lee";
    KThread *thread = new KThread(sudoiface, "uninstall_pkg", strlist, pkgName);
    thread->start();
}
void SudoDispatcher::update_pkg_qt(QString pkgName) {
    QStringList strlist;
    strlist << "Kobe" << "Lee";
    KThread *thread = new KThread(sudoiface, "update_pkg", strlist, pkgName);
    thread->start();
//    sudoiface->call("update_pkg", pkgName);
}
void SudoDispatcher::check_pkgs_status_qt(QStringList pkgNameList) {
//    pkgNameList << "qtcreator" << "qtcreator-plugin-ubuntu";
    sudoiface->call("check_pkgs_status", pkgNameList);
//    QDBusReply<QMap<QString, QVariant> > reply = sudoiface->call("check_pkgs_status", pkgNameList);
//    qDebug() << "lllll->";
//    qDebug() << reply.value();
    //QMap(("qtcreator", QVariant(QString, "i") ) ( "qtcreator-plugin-ubuntu" ,  QVariant(QString, "n") ) )
}

QString SudoDispatcher::check_pkg_status_qt(QString pkgName) {
    QDBusReply<QString> reply = sudoiface->call("check_pkg_status", pkgName);
    return reply.value();
}

void SudoDispatcher::apt_get_update_qt() {
    sudoiface->call("apt_get_update");
}
