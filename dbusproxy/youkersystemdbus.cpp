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

#include "youkersystemdbus.h"
#include <QDebug>
#include <QtDBus>
#include <QFileDialog>
#include <QMap>
#include <QMessageBox>

SystemDispatcher::SystemDispatcher(QObject *parent)
//    QObject(parent)
{
    systemiface = new QDBusInterface("com.ubuntukylin.youker",
                               "/",
                               "com.ubuntukylin.youker",
                               QDBusConnection::systemBus());
    thread = new KThread(this);
//    onekey_args << "cache" << "history" << "cookies";
//    tmplist << "Kobe" << "Lee";
//    this->mainwindow_width = 850;
//    this->mainwindow_height = 600;
//    ratio_sus = 0;
//    //绑定到底层清理完毕后发送到信号函数clear_browser
//    QObject::connect(systemiface,SIGNAL(clean_single_complete(QString)),this,SLOT(handler_clear_single_rubbish(QString)));
//    QObject::connect(systemiface,SIGNAL(clean_single_error(QString)),this,SLOT(handler_clear_single_rubbish_error(QString)));
//    QObject::connect(systemiface,SIGNAL(clean_complete(QString)),this,SLOT(handler_clear_rubbish(QString)));
    QObject::connect(systemiface,SIGNAL(quit_clean(/*QString*/)),this,SLOT(handler_quit_clean(/*QString*/)));
//    QObject::connect(systemiface,SIGNAL(clean_error(QString)),this,SLOT(handler_clear_rubbish_error(QString)));
    QObject::connect(systemiface,SIGNAL(clean_complete_onekey(QString)),this,SLOT(handler_clear_rubbish_main_onekey(QString)));
    QObject::connect(systemiface,SIGNAL(clean_error_onekey(QString)),this,SLOT(handler_clear_rubbish_main_error(QString)));
    QObject::connect(systemiface,SIGNAL(status_for_quick_clean(QString,QString)),this,SLOT(handler_status_for_quick_clean(QString,QString)));


    QObject::connect(systemiface,SIGNAL(subpage_data_signal(QStringList)),this,SLOT(handlerCleanerSubPageDataSignal(QStringList)));
    QObject::connect(systemiface,SIGNAL(subpage_status_signal(QString, QString)),this,SLOT(handlerCleanerSubPageStatusSignal(QString, QString)));
    QObject::connect(systemiface,SIGNAL(subpage_error_signal(QString)),this,SLOT(handlerCleanerSubPageErrorSignal(QString)));

//    QObject::connect(systemiface,SIGNAL(finish_clean(QString)),this,SLOT(handlerClearDeb(QString)));
//    QObject::connect(systemiface,SIGNAL(sudo_clean_error(QString)),this,SLOT(handlerClearDebError(QString)));
//    //多余包和内核包删除过程信号绑定
//    QObject::connect(systemiface,SIGNAL(status_remove_packages(QString,QString)),this,SLOT(handlerRemoveProgress(QString,QString)));

}

SystemDispatcher::~SystemDispatcher() {
    this->exit_qt();
    if (systemiface != NULL) {
        delete systemiface;
        systemiface = NULL;
    }
//    if (thread != NULL) {
//        delete thread;
//        thread = NULL;
//    }
}

void SystemDispatcher::cleanAllSelectItems(QMap<QString, QVariant> selectMap)
{
    QStringList tmp;
    thread->initValues(selectMap, tmp, systemiface, "remove_select_items");
    thread->start();
}

//void SystemDispatcher::removeFile(QString fileName)
//{
//    qDebug() << "start to remove file->" << fileName;
//    systemiface->call("remove_file", fileName);
//}

//void SystemDispatcher::removePackage(QString packageName)
//{
//    systemiface->call("remove_package", packageName);
//}

//void SystemDispatcher::removeFirefoxHistory()
//{
//    systemiface->call("remove_firefox_history");
//}

//void SystemDispatcher::removeChromiumHistory()
//{
//    systemiface->call("remove_chromium_history");
//}

//void SystemDispatcher::removeFirefoxCookie(QString cookieName)
//{
//    systemiface->call("remove_firefox_cookies", cookieName);
//}

//void SystemDispatcher::removeChromiumCookie(QString cookieName)
//{
//    systemiface->call("remove_chromium_cookies", cookieName);
//}

//void SystemDispatcher::kill_root_process_qt(QString pid) {
//    systemiface->call("kill_root_process", pid);
//}

bool SystemDispatcher::set_cursor_theme_with_root_qt(QString theme) {
    QDBusReply<bool> reply = systemiface->call("set_cursor_theme_with_root", theme);
    return reply.value();
}

QMap<QString, QVariant> SystemDispatcher::get_computer_info_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("get_computer_info");
    if (reply.isValid()) {
        QMap<QString, QVariant> value = reply.value();
        return value;
//        computerInfo.clear();
//        computerInfo = value;
    }
    else {
        qDebug() << "get computer info failed!";
    }
}

QMap<QString, QVariant> SystemDispatcher::get_cpu_info_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("get_cpu_info");
    if (reply.isValid()) {
        QMap<QString, QVariant> value = reply.value();
        return value;
//        cpuInfo.clear();
//        cpuInfo = value;
    }
    else {
        qDebug() << "get cpu info failed!";
    }
}

QMap<QString, QVariant> SystemDispatcher::get_memory_info_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("get_memory_info");
    if (reply.isValid()) {
        QMap<QString, QVariant> value = reply.value();
//        memoryInfo.clear();
//        memoryInfo = value;
        return value;
//        qDebug() << memoryInfo;
    }
    else {
        qDebug() << "get memory info failed!";
    }
}

QMap<QString, QVariant> SystemDispatcher::get_board_info_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("get_board_info");
    if (reply.isValid()) {
        QMap<QString, QVariant> value = reply.value();
        return value;
//        boardInfo.clear();
//        boardInfo = value;
    }
    else {
        qDebug() << "get board info failed!";
    }
}

QMap<QString, QVariant> SystemDispatcher::get_harddisk_info_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("get_harddisk_info");
    if (reply.isValid()) {
        QMap<QString, QVariant> value = reply.value();
        return value;
//        harddiskInfo.clear();
//        harddiskInfo = value;
    }
    else {
        qDebug() << "get harddisk info failed!";
    }
}

QMap<QString, QVariant> SystemDispatcher::get_networkcard_info_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("get_networkcard_info");
    if (reply.isValid()) {
        QMap<QString, QVariant> value = reply.value();
        return value;
//        networkcardInfo.clear();
//        networkcardInfo = value;
    }
    else {
        qDebug() << "get networkcard info failed!";
    }
}

QMap<QString, QVariant> SystemDispatcher::get_monitor_info_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("get_monitor_info");
    if (reply.isValid()) {
        QMap<QString, QVariant> value = reply.value();
        return value;
//        monitorInfo.clear();
//        monitorInfo = value;
    }
    else {
        qDebug() << "get monitor info failed!";
    }
}

QMap<QString, QVariant> SystemDispatcher::get_cdrom_info_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("get_cdrom_info");
    if (reply.isValid()) {
        QMap<QString, QVariant> value = reply.value();
        return value;
//        cdromInfo.clear();
//        cdromInfo = value;
    }
    else {
        qDebug() << "get cdrom info failed!";
    }
}

QMap<QString, QVariant> SystemDispatcher::get_audiocard_info_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("get_audiocard_info");
    if (reply.isValid()) {
        QMap<QString, QVariant> value = reply.value();
        return value;
//        audiocardInfo.clear();
//        audiocardInfo = value;
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

//void SystemDispatcher::handler_clear_rubbish_error(QString msg) {
//     emit finishCleanWorkError(msg);
//}

void SystemDispatcher::exit_qt() {
//    qDebug() << "start exit system dbus daemon....";
    systemiface->call("exit");
}

QString SystemDispatcher::get_system_daemon_qt() {
    QDBusReply<QString> reply = systemiface->call("get_system_daemon");
    return reply.value();
}

//void SystemDispatcher::listen_music(QString path) {
//    if (QSound::isAvailable()) {
//        QSound player(path);
//        player.play();
//        if (player.isFinished() == true) {
//            player.stop();
//        }
//    }
//}

//void SystemDispatcher::set_homedir_qt() {
//    QString homedir = QDir::homePath();
//    systemiface->call("set_homedir", homedir);
//}

void SystemDispatcher::set_user_homedir_qt() {
    QString homedir = QDir::homePath();
    systemiface->call("set_user_homedir", homedir);
}

//void SystemDispatcher::handler_clear_rubbish(QString msg) {
//     emit finishCleanWork(msg);
//}

void SystemDispatcher::handler_quit_clean(/*QString msg*/) {
    emit quitCleanWork(/*msg*/);//dengting
}

//void SystemDispatcher::handler_clear_single_rubbish(QString msg) {
//    emit finishCleanSingleWork(msg);
//}

//void SystemDispatcher::handler_clear_single_rubbish_error(QString msg) {
//    emit finishCleanSingleWorkError(msg);
//}

void SystemDispatcher::handler_clear_rubbish_main_onekey(QString msg/*, QString flag*/) {
     emit finishCleanWorkMain(msg/*, flag*/);
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


void SystemDispatcher::handlerCleanerSubPageDataSignal(QStringList data)
{
//    qDebug() << "lixiang clean data----" << data;
    emit this->tellCleanerMainData(data);
//    lixiang clean data---- ("Path:/home/trusty64/.cache/software-center/rnrclient", "Size:0.00 B")
    //lixiang clean data---- ("Pkg:testapp", "Percent:50%", "Status:removing")
}

void SystemDispatcher::handlerCleanerSubPageStatusSignal(QString status, QString domain)
{
//    qDebug() << "lixiang clean status----" << status << "--------domain--------" << domain;

//    lixiang clean status---- "Complete:Cookies.firefox" --------domain-------- "10010.com"
//    lixiang clean status---- "Complete:Cookies.firefox" --------domain-------- "10086.cn"
    if(status == "Complete:All" && domain == "finish")
    {
        emit sendCleanOverSignal();
    }
    else {
        emit this->tellCleanerMainStatus(status, domain);
    }
}

void SystemDispatcher::handlerCleanerSubPageErrorSignal(QString status)
{
//    qDebug() << "lixiang clean error----" << status;
    emit sendCleanErrorSignal(status);
    //system.subpage_error_signal('Non-existent:%s' % filepath)
    //system.subpage_error_signal('Working:Chromium')
    //system.subpage_error_signal('Non-existent:%s' % pkgname)
}

//QStringList SystemDispatcher::get_sounds_qt() {
//    QDBusReply<QStringList> reply = systemiface->call("get_sounds");
//    return reply.value();
//}

//void SystemDispatcher::replace_sound_file_qt(QString origfile, QString targetfile) {
//    systemiface->call("replace_sound_file", origfile, targetfile);
//}
//void SystemDispatcher::restore_sound_file_qt(QString targetfile) {
//    systemiface->call("restore_sound_file", targetfile);
//}

//void SystemDispatcher::restore_all_sound_file_qt(QString soundtheme) {
//    systemiface->call("restore_all_sound_file", soundtheme);
//}

////-----------------------others------------------------
void SystemDispatcher::custom_plymouth_bg_qt(QString plymouthName) {
    systemiface->call("custom_plymouth_bg", plymouthName);
}

void SystemDispatcher::add_new_plymouth_qt(QString customBG, QString plymouthName) {
    systemiface->call("add_new_plymouth", customBG, plymouthName);
}

//void SystemDispatcher::readyAddBootImageToList() {
//    emit finishAddBootImage();
//}

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

QString SystemDispatcher::delete_plymouth_qt(QString plymouthName) {
    QDBusReply<QString> reply = systemiface->call("delete_plymouth", plymouthName);
    return reply.value();
}

////-----------------------------------------------
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

//void SystemDispatcher::clean_history_records_qt(QString flag) {
//    thread->initValues(tmplist, systemiface, "history_clean_records_function", flag);
//    thread->start();
//}

//void SystemDispatcher::clean_system_history_qt() {
//    thread->initValues(tmplist, systemiface, "clean_system_history");
//    thread->start();
//}

//void SystemDispatcher::clean_dash_history_qt() {
//    thread->initValues(tmplist, systemiface, "clean_dash_history");
//    thread->start();
//}

//void SystemDispatcher::cookies_clean_record_function_qt(QString flag, QString website) {
//    QStringList strlist;
//    strlist << flag << website;
//    thread->initValues(strlist, systemiface, "cookies_clean_record_function");
//    thread->start();
//}

//void SystemDispatcher::cookies_clean_records_function_qt(QString flag) {
//    thread->initValues(tmplist, systemiface, "cookies_clean_records_function", flag);
//    thread->start();
//}

//void SystemDispatcher::clean_file_cruft_qt(QStringList strlist, QString str) {
//    thread->initValues(strlist, systemiface, "clean_file_cruft", str);
//    thread->start();
//}

void SystemDispatcher::clean_by_main_one_key_qt() {
    QStringList argList;
    argList << "1" << "1" << "1";
    QMap<QString, QVariant> data;
    thread->initValues(data, argList, systemiface, "onekey_clean_crufts_function");
    thread->start();
}

//void SystemDispatcher::set_onekey_args(QString str) {
//    onekey_args.append(str);
//}

//void SystemDispatcher::del_onekey_args(QString str) {
//    QStringList bake;
//    int len = onekey_args.length();
//    for (int i=0; i< len; i++) {
//        if (onekey_args[i] != str) {
//            bake.append(onekey_args[i]);
//        }
//    }
//    onekey_args.clear();
//    onekey_args = bake;
////    package_args.replaceInStrings(QString(str), QString(""));
//}

//void SystemDispatcher::clear_onekey_args() {
//    onekey_args.clear();
//}

//QStringList SystemDispatcher::get_onekey_args() {
//    return onekey_args;
//}

//int SystemDispatcher::get_the_record_qt(QString mode) {
//    QDBusReply<int> reply = systemiface->call("get_the_record", mode);
//    int value = reply.value();
//    return value;
//}

//void SystemDispatcher::clean_the_browser_qt(QString mode) {
//    systemiface->call("clean_the_browser", mode);
//}

//QMap<QString, QVariant> SystemDispatcher::search_same_files(QString path) {
//    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("search_the_same", path);
//    return reply.value();
//}

//QStringList SystemDispatcher::search_largest_file(QString path) {
//    QDBusReply<QStringList> reply = systemiface->call("search_the_large", path);
//    return reply.value();
//}


////------------------------------
//void SystemDispatcher::handlerClearDeb(QString msg) {
//     emit finishCleanDeb(msg);
//}

//void SystemDispatcher::handlerClearDebError(QString msg) {
//     emit finishCleanDebError(msg);
//}

//得到下载或者是操作过程中发送过来的数据，在显示在进度条上之前处理优化下
//QString SystemDispatcher::dealProgressData(QString type, QString msg) {
//    QString info = "";
//    if(type == "down_start") {
//        ratio_sus = 0;
//    }
//    else if(type == "down_pulse"){
//        if(!msg.isEmpty()) {
//            if(msg.contains("download_bytes") && msg.contains("total_bytes")) {
//                QStringList process_value = msg.split(",");
//                if (process_value.size() == 4) {
//                    QStringList download_bytes = process_value.at(0).split(":");
//                    double download_bytes_value = download_bytes.at(1).toDouble();
//                    QStringList total_bytes = process_value.at(1).split(":");
//                    double total_bytes_value = total_bytes.at(1).toDouble();
//                    double percent = download_bytes_value / total_bytes_value;
//                    QString cur_status = QString::number(percent, 'f', 2);
//                    double trans = cur_status.toDouble() * 100;
//                    cur_status = QString::number(trans,'f',0);
//                    ratio_sus = cur_status.toInt();
//                }
//            }
//        }
//    }
//    else if(type == "down_stop") {
//        ratio_sus = 100;
//    }
//    else if(type == "apt_start"){
//        ratio_sus = 0;
//    }
//    else if(type == "apt_pulse"){
//        if(!msg.isEmpty()) {
//            if(msg.contains(",")) {
//                QStringList process_value = msg.split(",");
//                if (process_value.size() == 2) {
//                    QStringList status_value = process_value.at(0).split(":");
//                    int value = status_value.at(1).toInt();
//                    QStringList action_value = process_value.at(1).split(":");
//                    info = action_value.at(1);
//                    ratio_sus = value;
//                }
//            }
//        }
//    }
//    else if(type == "apt_stop") {
//        ratio_sus = 100;
//    }
//    return info;
//}

//void SystemDispatcher::handlerRemoveProgress(QString type, QString msg) {//remove package or old kernel
//    if(!type.isEmpty()) {
//        QString info = dealProgressData(type, msg);
//        //操作过程中把数据给进度条
//        emit sendProgressToQML(type, info, ratio_sus);
//    }
//}

//void SystemDispatcher::clean_package_cruft_qt(QStringList strlist, QString flag) {
//    thread->initValues(strlist, systemiface, "clean_package_cruft", flag);
//    thread->start();
//}
