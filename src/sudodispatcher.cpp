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
#include "progressdialog.h"
#include <QMap>
//extern QString passwd;

SudoDispatcher::SudoDispatcher(QObject *parent) :
    QObject(parent)
{
    sudoiface = new QDBusInterface("com.ubuntukylin.Ihu",
                               "/",
                               "com.ubuntukylin.Ihu",
                               QDBusConnection::systemBus());
//    QObject::connect(sudoiface,SIGNAL(clean_complete(QString)),this,SLOT(handler_clear_rubbish(QString)));
//    QObject::connect(sudoiface,SIGNAL(clean_error(QString)),this,SLOT(handler_clear_rubbish_error(QString)));
}

SudoDispatcher::~SudoDispatcher()
{
    if (authdialog)
        delete authdialog;
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
//    QObject::connect(sudoiface,SIGNAL(software_check_status_signal(QMap<QString, QVariant>)),this,SLOT(handler_software_check_status_signal(QMap<QString, QVariant>)));
    QObject::connect(sudoiface,SIGNAL(software_check_status_signal(QStringList)),this,SLOT(handler_software_check_status_signal(QStringList)));
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
    emit finishSoftwareFetch(type, msg);
}

void SudoDispatcher::handler_software_apt_signal(QString type, QString msg)
{
    qDebug() << "get software_apt_signal.....";
    qDebug() << type;
    qDebug() << msg;
    emit finishSoftwareApt(type, msg);
}

//void SudoDispatcher::handler_software_check_status_signal(QMap<QString, QVariant> statusDict)
void SudoDispatcher::handler_software_check_status_signal(QStringList statusDict)
{
    qDebug() << "get software_check_status_signal.....";
    qDebug() << statusDict;
    emit finishSoftwareCheckStatus(statusDict);
}
//bool SudoDispatcher::trans_password(QString flagstr, QString pwd) {
//    QString cmd1 = "echo " + pwd + " | sudo -S touch /usr/bin/youker.txt";
//    QByteArray ba1 = cmd1.toLatin1();
//    const char *transpd = ba1.data();
//    int bb = system(transpd);
//    qDebug() << bb;
//    if (bb == 0) {
//        qDebug() << "yes";
//        QString cmd2 = "echo " + pwd + " | sudo -S rm /usr/bin/youker.txt";
//        QByteArray ba2 = cmd2.toLatin1();
//        const char *transpd2 = ba2.data();
//        int bb1 = system(transpd2);
//        qDebug() << bb1;
//        QProcess *process = new QProcess;
//        process->start("/usr/bin/" + flagstr + " " + pwd);
//        return true;
//    }
//    else {
//        qDebug() << "no";
//    }
//    return false;
//}

void SudoDispatcher::show_passwd_dialog() {
    authdialog = new AuthDialog("提示：请输入当前用户登录密码，保证优客助手的正常使用。");
    authdialog->exec();
//    bool value = trans_password("youkersudo", passwd);
//    return value;
}

void SudoDispatcher::show_progress_dialog() {
//    ProgressDialog progressdialog;
//    progressdialog.exec();
    ProgressDialog progressdialog("正在下载...");
    progressdialog.exec();
}

void SudoDispatcher::clean_package_cruft_qt(QStringList strlist) {
    sudoiface->call("clean_package_cruft", strlist);
}

QStringList SudoDispatcher::get_args() {
    QStringList pkgNameList;
    pkgNameList << "qtcreator" << "qtcreator-plugin-ubuntu";
    return pkgNameList;
}

// -------------------------software-center-------------------------
void SudoDispatcher::install_pkg_qt(QString pkgName) {
    sudoiface->call("install_pkg", pkgName);
}
void SudoDispatcher::uninstall_pkg_qt(QString pkgName) {
    sudoiface->call("uninstall_pkg", pkgName);
}
void SudoDispatcher::update_pkg_qt(QString pkgName) {
    sudoiface->call("update_pkg", pkgName);
}
void SudoDispatcher::check_pkgs_status_qt(QStringList pkgNameList) {
//    pkgNameList << "qtcreator" << "qtcreator-plugin-ubuntu";
    sudoiface->call("check_pkgs_status", pkgNameList);
//    QDBusReply<QMap<QString, QVariant> > reply = sudoiface->call("check_pkgs_status", pkgNameList);
//    qDebug() << "lllll->";
//    qDebug() << reply.value();
    //QMap(("qtcreator", QVariant(QString, "i") ) ( "qtcreator-plugin-ubuntu" ,  QVariant(QString, "n") ) )
}
