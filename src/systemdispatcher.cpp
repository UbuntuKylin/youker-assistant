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
#include "systemdispatcher.h"
#include <QDebug>
#include <QVariant>
#include <QProcessEnvironment>
#include <QtDBus>
#include <QObject>
#include <QString>
#include <QFileDialog>
#include <QMap>
#include <QMessageBox>
#include "kthread.h"

extern QString music_path;

SystemDispatcher::SystemDispatcher(QObject *parent) :
    QObject(parent)
{
    systemiface = new QDBusInterface("com.ubuntukylin.youker",
                               "/",
                               "com.ubuntukylin.youker",
                               QDBusConnection::systemBus());
    history_flag = true;
    onekey_args << "cache" << "history" << "cookies";
    tmplist << "Kobe" << "Lee";
    this->mainwindow_width = 850;
    this->mainwindow_height = 600;
    this->alert_width = 292;
    this->alert_width_bg = 329;
    this->alert_height = 54;
    ratio_sus = 0;

    //绑定到底层清理完毕后发送到信号函数clear_browser
    QObject::connect(systemiface,SIGNAL(clean_single_complete(QString)),this,SLOT(handler_clear_single_rubbish(QString)));
    QObject::connect(systemiface,SIGNAL(clean_single_error(QString)),this,SLOT(handler_clear_single_rubbish_error(QString)));
    QObject::connect(systemiface,SIGNAL(clean_complete(QString)),this,SLOT(handler_clear_rubbish(QString)));
    QObject::connect(systemiface,SIGNAL(quit_clean(QString)),this,SLOT(handler_quit_clean(QString)));
    QObject::connect(systemiface,SIGNAL(clean_error(QString)),this,SLOT(handler_clear_rubbish_error(QString)));
    QObject::connect(systemiface,SIGNAL(clean_complete_onekey(QString)),this,SLOT(handler_clear_rubbish_main_onekey(QString)));
    QObject::connect(systemiface,SIGNAL(clean_error_onekey(QString)),this,SLOT(handler_clear_rubbish_main_error(QString)));
    QObject::connect(systemiface,SIGNAL(status_for_quick_clean(QString,QString)),this,SLOT(handler_status_for_quick_clean(QString,QString)));

    QObject::connect(systemiface,SIGNAL(finish_clean(QString)),this,SLOT(handlerClearDeb(QString)));
    QObject::connect(systemiface,SIGNAL(sudo_clean_error(QString)),this,SLOT(handlerClearDebError(QString)));
    //多余包和内核包删除过程信号绑定
    QObject::connect(systemiface,SIGNAL(status_remove_packages(QString,QString)),this,SLOT(handlerRemoveProgress(QString,QString)));
}

SystemDispatcher::~SystemDispatcher() {
    this->exit_qt();
}

void SystemDispatcher::kill_root_process_qt(QString pid) {
    systemiface->call("kill_root_process", pid);
}

bool SystemDispatcher::set_cursor_theme_with_root_qt(QString theme) {
    QDBusReply<bool> reply = systemiface->call("set_cursor_theme_with_root", theme);
    return reply.value();
}

void SystemDispatcher::get_computer_info_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("get_computer_info");
    if (reply.isValid()) {
        QMap<QString, QVariant> value = reply.value();
        computerInfo = value;
    }
    else {
        qDebug() << "get computer info failed!";
    }
}

void SystemDispatcher::get_cpu_info_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("get_cpu_info");
    if (reply.isValid()) {
        QMap<QString, QVariant> value = reply.value();
        cpuInfo = value;
    }
    else {
        qDebug() << "get cpu info failed!";
    }
}

void SystemDispatcher::get_memory_info_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("get_memory_info");
    if (reply.isValid()) {
        QMap<QString, QVariant> value = reply.value();
        memoryInfo = value;
//        qDebug() << memoryInfo;
    }
    else {
        qDebug() << "get memory info failed!";
    }
}

void SystemDispatcher::get_board_info_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("get_board_info");
    if (reply.isValid()) {
        QMap<QString, QVariant> value = reply.value();
        boardInfo = value;
    }
    else {
        qDebug() << "get board info failed!";
    }
}

void SystemDispatcher::get_harddisk_info_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("get_harddisk_info");
    if (reply.isValid()) {
        QMap<QString, QVariant> value = reply.value();
        harddiskInfo = value;
    }
    else {
        qDebug() << "get harddisk info failed!";
    }
}

void SystemDispatcher::get_networkcard_info_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("get_networkcard_info");
    if (reply.isValid()) {
        QMap<QString, QVariant> value = reply.value();
        networkcardInfo = value;
    }
    else {
        qDebug() << "get networkcard info failed!";
    }
}

void SystemDispatcher::get_monitor_info_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("get_monitor_info");
    if (reply.isValid()) {
        QMap<QString, QVariant> value = reply.value();
        monitorInfo = value;
    }
    else {
        qDebug() << "get monitor info failed!";
    }
}

void SystemDispatcher::get_cdrom_info_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("get_cdrom_info");
    if (reply.isValid()) {
        QMap<QString, QVariant> value = reply.value();
        cdromInfo = value;
    }
    else {
        qDebug() << "get cdrom info failed!";
    }
}

void SystemDispatcher::get_audiocard_info_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("get_audiocard_info");
    if (reply.isValid()) {
        QMap<QString, QVariant> value = reply.value();
        audiocardInfo = value;
    }
    else {
        qDebug() << "get audiocard info failed!";
    }
}

QString SystemDispatcher::get_time_value_qt() {
    QDBusReply<QString> reply = systemiface->call("get_time_value");
    return reply.value();
}

QString SystemDispatcher::getHWSingleInfo(QString key, QString flag) {
    QVariant info;
    if(flag == "computer") {
        info = computerInfo.value(key);
    }
    else if(flag == "cpu") {
        info = cpuInfo.value(key);
    }
    else if(flag == "memory") {
        info = memoryInfo.value(key);
    }
    else if(flag == "board") {
        info = boardInfo.value(key);
    }
    else if(flag == "harddisk") {
        info = harddiskInfo.value(key);
    }
    else if(flag == "networkcard") {
        info = networkcardInfo.value(key);
    }
    else if(flag == "monitor") {
        info = monitorInfo.value(key);
    }
    else if(flag == "cdrom") {
        info = cdromInfo.value(key);
    }
    else if(flag == "audiocard") {
        info = audiocardInfo.value(key);
    }
    return info.toString();
}

void SystemDispatcher::handler_clear_rubbish_error(QString msg) {
     emit finishCleanWorkError(msg);
}

void SystemDispatcher::exit_qt() {
    systemiface->call("exit");
}

QString SystemDispatcher::get_system_daemon_qt() {
    QDBusReply<QString> reply = systemiface->call("get_system_daemon");
    return reply.value();
}

void SystemDispatcher::getMusicFileAbsolutePath(QString musicpath) {
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

void SystemDispatcher::handler_clear_rubbish(QString msg) {
     emit finishCleanWork(msg);
}

void SystemDispatcher::handler_quit_clean(QString msg) {
    emit quitCleanWork(msg);
}

void SystemDispatcher::handler_clear_single_rubbish(QString msg) {
    emit finishCleanSingleWork(msg);
}

void SystemDispatcher::handler_clear_single_rubbish_error(QString msg) {
    emit finishCleanSingleWorkError(msg);
}

void SystemDispatcher::handler_clear_rubbish_main_onekey(QString msg) {
     emit finishCleanWorkMain(msg);
}

void SystemDispatcher::handler_clear_rubbish_main_error(QString msg) {
     emit finishCleanWorkMainError(msg);
}

void SystemDispatcher::handler_status_for_quick_clean(QString type, QString status) {
    emit quickCleanProcess(type, status);
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
void SystemDispatcher::cleanup_memory_qt() {
    systemiface->call("cleanup_memory");
}

//-----------------------------------------------

//-----------------------others------------------------
void SystemDispatcher::custom_plymouth_bg_qt(QString plymouthName) {
    systemiface->call("custom_plymouth_bg", plymouthName);
}

void SystemDispatcher::add_new_plymouth_qt(QString customBG, QString plymouthName) {
    systemiface->call("add_new_plymouth", customBG, plymouthName);
}

void SystemDispatcher::readyAddBootImageToList() {
    emit finishAddBootImage();
}

QStringList SystemDispatcher::get_existing_plymouth_list_qt() {
    QDBusReply<QStringList> reply = systemiface->call("get_existing_plymouth_list");
    return reply.value();
}

void SystemDispatcher::plymouth_init_check_qt() {
    systemiface->call("plymouth_init_check");
}

QString SystemDispatcher::get_image_path_qt(QString name) {
    QDBusReply<QString> reply = systemiface->call("get_image_path", name);
    return reply.value();
}

bool SystemDispatcher::delete_plymouth_qt(QString plymouthName) {
    QDBusReply<bool> reply = systemiface->call("delete_plymouth", plymouthName);
    return reply.value();
}

//-----------------------------------------------
QString SystemDispatcher::showSelectFileDialog(QString flag) {
    if (flag == "bootanimation") {
        //选择开机动画            图像文件  (*.png *.jpg *.gif)
        QString bootfileName = QFileDialog::getOpenFileName(0, tr("Select the boot animation"), "", tr("Image Files (*.png *.jpg *.gif)"));
        return bootfileName;
    }
    else if (flag == "soundeffects") {
        //选择音乐      音频文件 (*.ogg *.wav *.mp3 *.wma)
        QString musicfileName = QFileDialog::getOpenFileName(0, tr("Select music"), "", tr("Audio Files (*.ogg *.wav *.mp3 *.wma)"));
        return musicfileName;
    }
    else {
        return "/ubuntukylin";
    }
}

void SystemDispatcher::clean_history_records_qt(QString flag) {
    KThread *thread = new KThread(tmplist, systemiface, "history_clean_records_function", flag);
    thread->start();
}

void SystemDispatcher::clean_system_history_qt() {
    KThread *thread = new KThread(tmplist, systemiface, "clean_system_history");
    thread->start();
}

//void SystemDispatcher::clean_dash_history_qt() {
//    KThread *thread = new KThread(tmplist, systemiface, "clean_dash_history");
//    thread->start();
//}

void SystemDispatcher::cookies_clean_record_function_qt(QString flag, QString website) {
    QStringList strlist;
    strlist << flag << website;
    KThread *thread = new KThread(strlist, systemiface, "cookies_clean_record_function");
    thread->start();
}

void SystemDispatcher::cookies_clean_records_function_qt(QString flag) {
    KThread *thread = new KThread(tmplist, systemiface, "cookies_clean_records_function", flag);
    thread->start();
}

void SystemDispatcher::clean_file_cruft_qt(QStringList strlist, QString str) {
    KThread *thread = new KThread(strlist, systemiface, "clean_file_cruft", str);
    thread->start();
}

void SystemDispatcher::clean_by_main_one_key_qt(bool garbageFlag, bool traceFlag, bool cookiesFlag) {
    QStringList argList;
    if(garbageFlag) {
        argList << "1";
    }
    else {
        argList << "0";
    }
    if(traceFlag) {
        argList << "1";
    }
    else {
        argList << "0";
    }
    if(cookiesFlag) {
        argList << "1";
    }
    else {
        argList << "0";
    }
    KThread *thread = new KThread(argList, systemiface, "onekey_clean_crufts_function");
    thread->start();
}

//------------------------------------------------------
void SystemDispatcher::set_cache_args(QString str) {
    cache_args.append(str);
}

void SystemDispatcher::del_cache_args(QString str) {
    QStringList bake;
    int len = cache_args.length();
    for (int i=0; i< len; i++) {
        if (cache_args[i] != str) {
            bake.append(cache_args[i]);
        }
    }
    cache_args.clear();
    cache_args = bake;
}

void SystemDispatcher::clear_cache_args() {
    cache_args.clear();
}

QStringList SystemDispatcher::get_cache_args() {
    return cache_args;
}

void SystemDispatcher::set_apt_args(QString str) {
    apt_args.append(str);
}

void SystemDispatcher::del_apt_args(QString str) {
    QStringList bake;
    int len = apt_args.length();
    for (int i=0; i< len; i++) {
        if (apt_args[i] != str) {
            bake.append(apt_args[i]);
        }
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
        if (software_args[i] != str) {
            bake.append(software_args[i]);
        }
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

void SystemDispatcher::set_package_args(QString str) {
    package_args.append(str);
}

void SystemDispatcher::del_package_args(QString str) {
    QStringList bake;
    int len = package_args.length();
    for (int i=0; i< len; i++) {
        if (package_args[i] != str) {
            bake.append(package_args[i]);
        }
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

void SystemDispatcher::set_browser_args(QString str) {
    browser_args.append(str);
}

void SystemDispatcher::del_browser_args(QString str) {
    QStringList bake;
    int len = browser_args.length();
    for (int i=0; i< len; i++) {
        if (browser_args[i] != str) {
            bake.append(browser_args[i]);
        }
    }
    browser_args.clear();
    browser_args = bake;
//    browser_args.replaceInStrings(QString(str), QString(""));
}

void SystemDispatcher::clear_browser_args() {
    browser_args.clear();
}

QStringList SystemDispatcher::get_browser_args() {
    return browser_args;
}

void SystemDispatcher::set_kernel_args(QString str) {
    kernel_args.append(str);
}

void SystemDispatcher::del_kernel_args(QString str) {
    QStringList bake;
    int len = kernel_args.length();
    for (int i=0; i< len; i++) {
        if (kernel_args[i] != str) {
            bake.append(kernel_args[i]);
        }
    }
    kernel_args.clear();
    kernel_args = bake;
//    kernel_args.replaceInStrings(QString(str), QString(""));
}

void SystemDispatcher::clear_kernel_args() {
    kernel_args.clear();
}

QStringList SystemDispatcher::get_kernel_args() {
    return kernel_args;
}

void SystemDispatcher::set_onekey_args(QString str) {
    onekey_args.append(str);
}

void SystemDispatcher::del_onekey_args(QString str) {
    QStringList bake;
    int len = onekey_args.length();
    for (int i=0; i< len; i++) {
        if (onekey_args[i] != str) {
            bake.append(onekey_args[i]);
        }
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

void SystemDispatcher::set_largestfile_args(QString str) {
    largestfile_args.append(str);
}

void SystemDispatcher::del_largestfile_args(QString str) {
    QStringList bake;
    int len = largestfile_args.length();
    for (int i=0; i< len; i++) {
        if (largestfile_args[i] != str) {
            bake.append(largestfile_args[i]);
        }
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


//------------------------------
void SystemDispatcher::handlerClearDeb(QString msg) {
     emit finishCleanDeb(msg);
}

void SystemDispatcher::handlerClearDebError(QString msg) {
     emit finishCleanDebError(msg);
}

//得到下载或者是操作过程中发送过来的数据，在显示在进度条上之前处理优化下
QString SystemDispatcher::dealProgressData(QString type, QString msg) {
    QString info = "";
    if(type == "down_start") {
        ratio_sus = 0;
    }
    else if(type == "down_pulse"){
        if(!msg.isEmpty()) {
            if(msg.contains("download_bytes") && msg.contains("total_bytes")) {
                QStringList process_value = msg.split(",");
                if (process_value.size() == 4) {
                    QStringList download_bytes = process_value.at(0).split(":");
                    double download_bytes_value = download_bytes.at(1).toDouble();
                    QStringList total_bytes = process_value.at(1).split(":");
                    double total_bytes_value = total_bytes.at(1).toDouble();
                    double percent = download_bytes_value / total_bytes_value;
                    QString cur_status = QString::number(percent, 'f', 2);
                    double trans = cur_status.toDouble() * 100;
                    cur_status = QString::number(trans,'f',0);
                    ratio_sus = cur_status.toInt();
                }
            }
        }
    }
    else if(type == "down_stop") {
        ratio_sus = 100;
    }
    else if(type == "apt_start"){
        ratio_sus = 0;
    }
    else if(type == "apt_pulse"){
        if(!msg.isEmpty()) {
            if(msg.contains(",")) {
                QStringList process_value = msg.split(",");
                if (process_value.size() == 2) {
                    QStringList status_value = process_value.at(0).split(":");
                    int value = status_value.at(1).toInt();
                    QStringList action_value = process_value.at(1).split(":");
                    info = action_value.at(1);
                    ratio_sus = value;
                }
            }
        }
    }
    else if(type == "apt_stop") {
        ratio_sus = 100;
    }
    return info;
}

void SystemDispatcher::handlerRemoveProgress(QString type, QString msg) {//remove package or old kernel
    if(!type.isEmpty()) {
        QString info = dealProgressData(type, msg);
        //操作过程中把数据给进度条
        emit sendProgressToQML(type, info, ratio_sus);
    }
}

void SystemDispatcher::clean_package_cruft_qt(QStringList strlist, QString flag) {
    KThread *thread = new KThread(strlist, systemiface, "clean_package_cruft", flag);
    thread->start();
}
