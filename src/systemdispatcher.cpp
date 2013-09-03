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
#include "systemdispatcher.h"
#include <QDebug>
#include <QVariant>
#include <QProcessEnvironment>
#include <QtDBus>
#include <QObject>
#include <QString>
#include <QFileDialog>
#include <QDir>

#include <QFile>
#include <QDataStream>
#include <iostream>
#include "authdialog.h"
#include "KThread.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>

#include <errno.h>
#include <sys/wait.h>
extern QString passwd;
extern QString music_path;

SystemDispatcher::SystemDispatcher(QObject *parent) :
    QObject(parent)
{
    systemiface = new QDBusInterface("com.ubuntukylin_tools.daemon",
                               "/",
                               "com.ubuntukylin_tools.daemon",
                               QDBusConnection::systemBus());
    //绑定到底层清理完毕后发送到信号函数clear_browser
    QObject::connect(systemiface,SIGNAL(clean_complete(QString)),this,SLOT(handler_clear_rubbish(QString)));
    QObject::connect(systemiface,SIGNAL(clean_complete_main(QString)),this,SLOT(handler_clear_rubbish_main_onekey(QString)));
    QObject::connect(systemiface,SIGNAL(clean_error_main(QString)),this,SLOT(handler_clear_rubbish_main_error(QString)));
    QObject::connect(systemiface,SIGNAL(clean_complete_second(QString)),this,SLOT(handler_clear_rubbish_second_onekey(QString)));
    QObject::connect(systemiface,SIGNAL(clean_error_second(QString)),this,SLOT(handler_clear_rubbish_second_error(QString)));
    QObject::connect(systemiface,SIGNAL(get_speed(QStringList)),this,SLOT(handler_network_speed(QStringList)));

    history_flag = true;
    onekey_args << "cache" << "history" << "cookies" << "unneed";
    onekey_args2 << "cache" << "history" << "cookies" << "unneed";
}

void SystemDispatcher::handler_clear_rubbish_second_error(QString msg)
{
     emit finishCleanWorkSecondError(msg);
}

void SystemDispatcher::exit_qt()
{
    systemiface->call("exit");
}

QString SystemDispatcher::get_system_daemon_qt() {
    QDBusReply<QString> reply = systemiface->call("get_system_daemon");
    return reply.value();
}

QString SystemDispatcher::get_system_daemon_qt_default() {
    QDBusReply<QString> reply = systemiface->call("get_system_daemon");
    return reply.value();
}

void SystemDispatcher::get_music_path(QString musicpath) {
    music_path = musicpath;
}

void SystemDispatcher::set_homedir_qt() {
    QString homedir = QDir::homePath();
    systemiface->call("set_homedir", homedir);
}

void SystemDispatcher::set_user_homedir_qt() {
    QString homedir = QDir::homePath();
    systemiface->call("set_user_homedir", homedir);
}


void SystemDispatcher::set_history_flag(bool flag) {
    history_flag = flag;
}

bool SystemDispatcher::get_history_flag() {
    return history_flag;
}

int SystemDispatcher::get_add_value()
{
    QDBusReply<int> reply = systemiface->call("test_add", 3, 4);
    int tt = reply.value();
    return tt;
}

void SystemDispatcher::handler_clear_rubbish(QString msg)
{
     emit finishCleanWork(msg);
}

void SystemDispatcher::handler_clear_rubbish_main_onekey(QString msg)
{
     emit finishCleanWorkMain(msg);
}

void SystemDispatcher::handler_clear_rubbish_main_error(QString msg)
{
     emit finishCleanWorkMainError(msg);
}
void SystemDispatcher::handler_clear_rubbish_second_onekey(QString msg)
{
     emit finishCleanWorkSecond(msg);
}

void SystemDispatcher::handler_network_speed(QStringList speed) {
    emit finishGetNetworkSpeed(speed);
}

void SystemDispatcher::send_btn_msg(QString str)
{
    systemiface->call("test_fastclear", str);
}

void SystemDispatcher::check_screen_break_point() {
    systemiface->call("check_screen");
}


//-----------------------sound------------------------
QStringList SystemDispatcher::get_sound_themes_qt() {
    QDBusReply<QStringList> reply = systemiface->call("get_sound_themes");
    return reply.value();
}
QStringList SystemDispatcher::get_sounds_qt() {
    QDBusReply<QStringList> reply = systemiface->call("get_sounds");
    return reply.value();
}
void SystemDispatcher::replace_sound_file_qt(QString origfile, QString targetfile) {
    systemiface->call("replace_sound_file", origfile, targetfile);
}
void SystemDispatcher::restore_sound_file_qt(QString targetfile) {
    systemiface->call("restore_sound_file", targetfile);
}
void SystemDispatcher::restore_all_sound_file_qt(QString soundtheme) {
    systemiface->call("restore_all_sound_file", soundtheme);
}

//-----------------------------------------------

//-----------------------monitorball------------------------
double SystemDispatcher::get_cpu_percent_qt() {
    QDBusReply<double> reply = systemiface->call("get_cpu_percent");
    return reply.value();
}
QString SystemDispatcher::get_total_memory_qt() {
    QDBusReply<QString> reply = systemiface->call("get_total_memory");
    return reply.value();
}
QString SystemDispatcher::get_used_memory_qt() {
    QDBusReply<QString> reply = systemiface->call("get_used_memory");
    return reply.value();
}
QString SystemDispatcher::get_free_memory_qt() {
    QDBusReply<QString> reply = systemiface->call("get_free_memory");
    return reply.value();
}

void SystemDispatcher::get_network_flow_qt() {
//    systemiface->call("get_network_flow");
    KThread *thread = new KThread(systemiface, "get_network_flow");
    thread->start();
}

QStringList SystemDispatcher::get_network_flow_total_qt() {
    QDBusReply<QStringList> reply = systemiface->call("get_network_flow_total");
    return reply.value();
}

void SystemDispatcher::cleanup_memory_qt() {
    systemiface->call("cleanup_memory");
}
//-----------------------------------------------

//-----------------------------------------------

//-----------------------others------------------------
void SystemDispatcher::custom_plymouth_bg_qt(QString plymouthName) {
    systemiface->call("custom_plymouth_bg", plymouthName);
}
void SystemDispatcher::add_new_plymouth_qt(QString customBG, QString plymouthName) {
    systemiface->call("add_new_plymouth", customBG, plymouthName);
}
void SystemDispatcher::send_boot_signal() {
    emit addBootImage();
}

QStringList SystemDispatcher::get_existing_plymouth_list_qt() {
    QDBusReply<QStringList> reply = systemiface->call("get_existing_plymouth_list");
    return reply.value();
}
void SystemDispatcher::plymouth_init_check_qt() {
    systemiface->call("plymouth_init_check");
}

//-----------------------------------------------


QString SystemDispatcher::show_file_dialog(QString flag) {
    if (flag == "bootanimation") {
        QString bootfileName = QFileDialog::getOpenFileName(0, tr("选择开机动画"), "", tr("Image Files (*.png)"));
        return bootfileName;
    }
    else if (flag == "soundeffects") {
        QString musicfileName = QFileDialog::getOpenFileName(0, tr("选择音乐"), "", tr("Music Files (*.ogg *.wav *.mp3 *.wma)"));
        return musicfileName;
    }
    else
        return "/ubuntukylin";
}

void SystemDispatcher::clean_history_records_qt() {
//    systemiface->call("clean_history_records");

    KThread *thread = new KThread(systemiface, "clean_history_records");
    thread->start();
}

void SystemDispatcher::clean_cookies_records_qt(QStringList strlist) {
//    systemiface->call("clean_cookies_records", strlist);

    KThread *thread = new KThread(systemiface, "clean_cookies_records", strlist);
    thread->start();
}

void SystemDispatcher::clean_package_cruft_qt(QStringList strlist) {
//    systemiface->call("clean_package_cruft", strlist);

    KThread *thread = new KThread(systemiface, "clean_package_cruft", strlist);
    thread->start();
}
void SystemDispatcher::clean_file_cruft_qt(QStringList strlist, QString str) {
//    systemiface->call("clean_file_cruft", strlist, str);
    KThread *thread = new KThread(systemiface, "clean_file_cruft", strlist, str);
    thread->start();
}

QStringList SystemDispatcher::get_apt_data()
{
    return apt_center["apt"].toStringList();
}
QStringList SystemDispatcher::get_center_data() {
    return apt_center["softwarecenter"].toStringList();
}

void SystemDispatcher::clean_by_main_one_key_qt(QStringList strlist) {
//    systemiface->call("clean_by_main_one_key", strlist);
    KThread *thread = new KThread(systemiface, "clean_by_main_one_key", strlist);
//    qDebug() << KThread::currentThreadId();
    thread->start();
}
void SystemDispatcher::clean_by_second_one_key_qt(QStringList strlist) {
//    systemiface->call("clean_by_second_one_key", strlist);

    KThread *thread = new KThread(systemiface, "clean_by_second_one_key", strlist);
    thread->start();
}
//------------------------------------------------------


//--------------------
void SystemDispatcher::set_apt_args(QString str) {
    apt_args.append(str);
}
void SystemDispatcher::del_apt_args(QString str) {
    QStringList bake;
    int len = apt_args.length();
    for (int i=0; i< len; i++) {
        if (apt_args[i] != str)
            bake.append(apt_args[i]);
    }
    apt_args.clear();
    apt_args = bake;
}
void SystemDispatcher::clear_apt_args() {
    apt_args.clear();
}
QStringList SystemDispatcher::get_apt_args() {
    return apt_args;
}

void SystemDispatcher::set_software_args(QString str) {
    software_args.append(str);
}
void SystemDispatcher::del_software_args(QString str) {
    QStringList bake;
    int len = software_args.length();
    for (int i=0; i< len; i++) {
        if (software_args[i] != str)
            bake.append(software_args[i]);
    }
    software_args.clear();
    software_args = bake;
}
void SystemDispatcher::clear_software_args() {
    software_args.clear();
}
QStringList SystemDispatcher::get_software_args() {
    return software_args;
}

void SystemDispatcher::set_cookies_args(QString str) {
    cookies_args.append(str);
}
void SystemDispatcher::del_cookies_args(QString str) {
    QStringList bake;
    int len = cookies_args.length();
    for (int i=0; i< len; i++) {
        if (cookies_args[i] != str)
            bake.append(cookies_args[i]);
    }
    cookies_args.clear();
    cookies_args = bake;
}
void SystemDispatcher::clear_cookies_args() {
    cookies_args.clear();
}
QStringList SystemDispatcher::get_cookies_args() {
    return cookies_args;
}

void SystemDispatcher::set_package_args(QString str) {
    package_args.append(str);
}
void SystemDispatcher::del_package_args(QString str) {
    QStringList bake;
    int len = package_args.length();
    for (int i=0; i< len; i++) {
        if (package_args[i] != str)
            bake.append(package_args[i]);
    }
    package_args.clear();
    package_args = bake;
//    package_args.replaceInStrings(QString(str), QString(""));
}
void SystemDispatcher::clear_package_args() {
    package_args.clear();
}
QStringList SystemDispatcher::get_package_args() {
    return package_args;
}

void SystemDispatcher::set_onekey_args(QString str) {
    onekey_args.append(str);
}
void SystemDispatcher::del_onekey_args(QString str) {
    QStringList bake;
    int len = onekey_args.length();
    for (int i=0; i< len; i++) {
        if (onekey_args[i] != str)
            bake.append(onekey_args[i]);
    }
    onekey_args.clear();
    onekey_args = bake;
//    package_args.replaceInStrings(QString(str), QString(""));
}
void SystemDispatcher::clear_onekey_args() {
    onekey_args.clear();
}
QStringList SystemDispatcher::get_onekey_args() {
    return onekey_args;
}

void SystemDispatcher::set_onekey_args2(QString str) {
    onekey_args2.append(str);
}
void SystemDispatcher::del_onekey_args2(QString str) {
    QStringList bake;
    int len = onekey_args2.length();
    for (int i=0; i< len; i++) {
        if (onekey_args2[i] != str)
            bake.append(onekey_args2[i]);
    }
    onekey_args2.clear();
    onekey_args2 = bake;
//    package_args.replaceInStrings(QString(str), QString(""));
}
void SystemDispatcher::clear_onekey_args2() {
    onekey_args2.clear();
}
QStringList SystemDispatcher::get_onekey_args2() {
    return onekey_args2;
}

void SystemDispatcher::set_largestfile_args(QString str) {
    largestfile_args.append(str);
}
void SystemDispatcher::del_largestfile_args(QString str) {
    QStringList bake;
    int len = largestfile_args.length();
    for (int i=0; i< len; i++) {
        if (largestfile_args[i] != str)
            bake.append(largestfile_args[i]);
    }
    largestfile_args.clear();
    largestfile_args = bake;
//    package_args.replaceInStrings(QString(str), QString(""));
}
void SystemDispatcher::clear_largestfile_args() {
    largestfile_args.clear();
}
QStringList SystemDispatcher::get_largestfile_args() {
    return largestfile_args;
}

int SystemDispatcher::get_the_record_qt(QString mode) {
    QDBusReply<int> reply = systemiface->call("get_the_record", mode);
    int value = reply.value();
    return value;
}


void SystemDispatcher::clean_the_browser_qt(QString mode) {
    systemiface->call("clean_the_browser", mode);
}

QMap<QString, QVariant> SystemDispatcher::search_same_files(QString path) {
    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("search_the_same", path);
    return reply.value();
}

QStringList SystemDispatcher::search_largest_file(QString path) {
    QDBusReply<QStringList> reply = systemiface->call("search_the_large", path);
    return reply.value();
}

QMap<QString, QVariant> SystemDispatcher::scan_by_one_key_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("scan_by_one_key");
    return reply.value();
}


void SystemDispatcher::show_passwd_dialog() {
    AuthDialog *dialog = new AuthDialog;
    dialog->exec();
}
