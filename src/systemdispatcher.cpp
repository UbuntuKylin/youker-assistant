/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
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
#include "KThread.h"
#include "sourcedialog.h"

extern QString music_path;

SystemDispatcher::SystemDispatcher(QObject *parent) :
    QObject(parent)
{
    systemiface = new QDBusInterface("com.ubuntukylin.youker",
                               "/",
                               "com.ubuntukylin.youker",
                               QDBusConnection::systemBus());
    updatedialog = new UpdateDialog;
    history_flag = true;
    onekey_args << "cache" << "history" << "cookies";
    tmplist << "Kobe" << "Lee";
    this->mainwindow_width = 850;
    this->mainwindow_height = 600;
    this->alert_width = 292;
    this->alert_width_bg = 329;
    this->alert_height = 54;

    config = new QSettings(APP_LIST_FILE, QSettings::IniFormat);
    config->setIniCodec("UTF-8");
    progressFlag = false;
    ratio_sus = 0;

    //绑定到底层清理完毕后发送到信号函数clear_browser
    QObject::connect(systemiface,SIGNAL(clean_single_complete(QString)),this,SLOT(handler_clear_single_rubbish(QString)));
    QObject::connect(systemiface,SIGNAL(clean_single_error(QString)),this,SLOT(handler_clear_single_rubbish_error(QString)));
    QObject::connect(systemiface,SIGNAL(clean_complete(QString)),this,SLOT(handler_clear_rubbish(QString)));
    QObject::connect(systemiface,SIGNAL(quit_clean(QString)),this,SLOT(handler_quit_clean(QString)));
    QObject::connect(systemiface,SIGNAL(clean_error(QString)),this,SLOT(handler_clear_rubbish_error(QString)));
//    QObject::connect(systemiface,SIGNAL(clean_complete_main(QString)),this,SLOT(handler_clear_rubbish_main_onekey(QString)));
//    QObject::connect(systemiface,SIGNAL(clean_error_main(QString)),this,SLOT(handler_clear_rubbish_main_error(QString)));
    QObject::connect(systemiface,SIGNAL(clean_complete_onekey(QString)),this,SLOT(handler_clear_rubbish_main_onekey(QString)));
    QObject::connect(systemiface,SIGNAL(clean_error_onekey(QString)),this,SLOT(handler_clear_rubbish_main_error(QString)));
    QObject::connect(systemiface,SIGNAL(clean_complete_second(QString)),this,SLOT(handler_clear_rubbish_second_onekey(QString)));
    QObject::connect(systemiface,SIGNAL(clean_error_second(QString)),this,SLOT(handler_clear_rubbish_second_error(QString)));
    QObject::connect(systemiface,SIGNAL(clean_data_main(QString,QString)),this,SLOT(handler_clean_data_main(QString, QString)));
    QObject::connect(systemiface,SIGNAL(clean_data_second(QString,QString)),this,SLOT(handler_clean_data_second(QString,QString)));
    QObject::connect(systemiface,SIGNAL(status_for_quick_clean(QString,QString)),this,SLOT(handler_status_for_quick_clean(QString,QString)));

    QObject::connect(systemiface,SIGNAL(sudo_finish_clean(QString)),this,SLOT(handlerClearDeb(QString)));
    QObject::connect(systemiface,SIGNAL(sudo_clean_error(QString)),this,SLOT(handlerClearDebError(QString)));
    QObject::connect(systemiface,SIGNAL(software_fetch_signal(QString,QString)),this,SLOT(handlerSoftwareFetch(QString,QString)));
    QObject::connect(systemiface,SIGNAL(software_apt_signal(QString,QString)),this,SLOT(handlerSoftwareApt(QString,QString)));
    QObject::connect(systemiface,SIGNAL(software_check_status_signal(QStringList)),this,SLOT(handlerGetSoftwareListStatus(QStringList)));
    QObject::connect(updatedialog,SIGNAL(call_update()),this, SLOT(startUpdateSoftwareSource()));
    //多余包和内核包删除过程信号绑定
    QObject::connect(systemiface,SIGNAL(status_remove_packages(QString,QString)),this,SLOT(handlerRemoveProgress(QString,QString)));
}

SystemDispatcher::~SystemDispatcher() {
    config->sync();
    if (config != NULL) {
        delete config;
    }
    if(updatedialog) {
        delete updatedialog;
    }
    this->exit_qt();
}

void SystemDispatcher::kill_root_process_qt(QString pid) {
    systemiface->call("kill_root_process", pid);
}

//void SystemDispatcher::write_source_to_qsetting() {
//    mSettings->beginGroup("sourcelist");
//    mSettings->setValue("ubuntukylin", true);
//    mSettings->endGroup();
//    mSettings->sync();
//}

//bool SystemDispatcher::read_source_from_qsetting() {
//    mSettings->beginGroup("sourcelist");
//    bool flag = mSettings->value("ubuntukylin").toBool();
//    mSettings->endGroup();
//    mSettings->sync();
//    return flag;
//}

//void SystemDispatcher::get_detail_system_message_qt() {
//    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("get_detail_system_message");
//    if (reply.isValid()) {
//        QMap<QString, QVariant> value = reply.value();
//        systemInfo = value;
////        qDebug() << systemInfo;
//    }
//    else {
//        qDebug() << "get pc_detail_message failed!";
//    }
//}

void SystemDispatcher::get_computer_info_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("get_computer_info");
    if (reply.isValid()) {
        QMap<QString, QVariant> value = reply.value();
        computerInfo = value;
//        qDebug() << computerInfo;
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

bool SystemDispatcher::judge_source_ubuntukylin_qt() {
    QDBusReply<bool> reply = systemiface->call("judge_source_ubuntukylin");
    return reply.value();
}

QString SystemDispatcher::readOSVersion() {
    QFile lsbFile(LSB_RELEASE);
    if(lsbFile.exists() && lsbFile.open(QFile::ReadOnly)) {
        QTextStream in(&lsbFile);
        QString line;
        QString version;
        while(!in.atEnd())
        {
           line = in.readLine();
           if(line.contains("DISTRIB_CODENAME")) {
               version = line.split("=").at(1);
               lsbFile.close();
               return version;
           }
        }
        lsbFile.close();
    }
    return "raring";
}

void SystemDispatcher::add_source_ubuntukylin_qt() {
    QString version = readOSVersion();
    systemiface->call("add_source_ubuntukylin", version);
}

void SystemDispatcher::showAddSourceList(int window_x, int window_y) {
    //弹出添加软件源的对话框
    SourceDialog *sourceDialog = new SourceDialog;
    connect(sourceDialog, SIGNAL(addList()), this, SLOT(add_source_ubuntukylin_qt()));
    this->alert_x = window_x + (mainwindow_width / 2) - (alert_width_bg  / 2);
    this->alert_y = window_y + mainwindow_height - 400;
    sourceDialog->move(this->alert_x, this->alert_y);
    sourceDialog->exec();
}

void SystemDispatcher::handler_clear_rubbish_error(QString msg) {
     emit finishCleanWorkError(msg);
}

void SystemDispatcher::handler_clear_rubbish_second_error(QString msg) {
     emit finishCleanWorkSecondError(msg);
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

void SystemDispatcher::handler_clear_rubbish_second_onekey(QString msg) {
     emit finishCleanWorkSecond(msg);
}

void SystemDispatcher::handler_clean_data_main(QString type, QString msg) {
    emit finishCleanDataMain(type, msg);
}

void SystemDispatcher::handler_clean_data_second(QString type, QString msg) {
    emit finishCleanDataSecond(type, msg);
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

void SystemDispatcher::clean_dash_history_qt() {
    KThread *thread = new KThread(tmplist, systemiface, "clean_dash_history");
    thread->start();
}

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

void SystemDispatcher::clean_by_main_one_key_qt(/*QStringList strlist*/bool garbageFlag, bool traceFlag, bool cookiesFlag) {
//    KThread *thread = new KThread(strlist, systemiface, "onekey_clean_crufts_function");
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

//void SystemDispatcher::set_cookies_args(QString str) {
//    cookies_args.append(str);
//}

//void SystemDispatcher::del_cookies_args(QString str) {
//    QStringList bake;
//    int len = cookies_args.length();
//    for (int i=0; i< len; i++) {
//        if (cookies_args[i] != str) {
//            bake.append(cookies_args[i]);
//        }
//    }
//    cookies_args.clear();
//    cookies_args = bake;
//}

//void SystemDispatcher::clear_cookies_args() {
//    cookies_args.clear();
//}

//QStringList SystemDispatcher::get_cookies_args() {
//    return cookies_args;
//}

//void SystemDispatcher::set_chromium_cookies_args(QString str) {
//    chromium_cookies_args.append(str);
//}

//void SystemDispatcher::del_chromium_cookies_args(QString str) {
//    QStringList bake;
//    int len = chromium_cookies_args.length();
//    for (int i=0; i< len; i++) {
//        if (chromium_cookies_args[i] != str) {
//            bake.append(chromium_cookies_args[i]);
//        }
//    }
//    chromium_cookies_args.clear();
//    chromium_cookies_args = bake;
//}

//void SystemDispatcher::clear_chromium_cookies_args() {
//    chromium_cookies_args.clear();
//}

//QStringList SystemDispatcher::get_chromium_cookies_args() {
//    return chromium_cookies_args;
//}

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
                    if(progressFlag) {//更新软件源的下载
                        QString download_items = process_value.at(2).split(":").at(1);
                        QString total_items = process_value.at(3).split(":").at(1);
                        emit notifySourceStatusToQML(download_items, total_items);
                    }
                }
            }
        }
    }
    else if(type == "down_stop") {
        //软件源更新下载完毕后，把progressFlag置为false
        if(progressFlag) {
            progressFlag = false;
        }
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

//下载
void SystemDispatcher::handlerSoftwareFetch(QString type, QString msg) {
    if(!type.isEmpty()) {
        QString info = dealProgressData(type, msg);
        //下载过程中把数据给进度条
        emit sendDynamicSoftwareProgressQML(type, info, ratio_sus);
        //下载完成
        if(type == "down_stop") {
            emit finishSoftwareFetch(type, msg);
        }
    }
}

//apt操作
void SystemDispatcher::handlerSoftwareApt(QString type, QString msg) {
    if(!type.isEmpty()) {
        QString info = dealProgressData(type, msg);
        //操作过程中把数据给进度条
        emit sendDynamicSoftwareProgressQML(type, info, ratio_sus);
        //操作完成
        if (type == "apt_stop") {
            emit finishSoftwareApt(type);
        }
    }
}

//得到所有软件的状态
void SystemDispatcher::handlerGetSoftwareListStatus(QStringList statusDict) {
    status_dict.clear();
    for(int i=0; i< statusDict.size(); i++) {
        QStringList value = statusDict[i].split(":");
        status_dict.insert(value[0], value[1]);
    }
//    qDebug() << status_dict;
}

//void SystemDispatcher::showPasswdDialog(int window_x, int window_y) {
//    //弹出输入密码的对话框
//    AuthDialog *authdialog = new AuthDialog(tr("Tip: please input password of current user to start server, make it work normally."));//提示：请输入当前用户登录密码启动服务，保证优客助手的正常使用。
//    this->alert_x = window_x + (mainwindow_width / 2) - (alert_width_bg  / 2);
//    this->alert_y = window_y + mainwindow_height - 400;
//    authdialog->move(this->alert_x, this->alert_y);
//    authdialog->exec();
//}

void SystemDispatcher::showUpdateSourceDialog(int window_x, int window_y) {
    progressFlag = true;//此时让qt的进度条隐藏
    this->alert_x = window_x + (mainwindow_width / 2) - (alert_width  / 2);
    this->alert_y = window_y + mainwindow_height - 400;
    updatedialog->move(this->alert_x, this->alert_y);
    updatedialog->show();
}

void SystemDispatcher::clean_package_cruft_qt(QStringList strlist, QString flag) {
    KThread *thread = new KThread(strlist, systemiface, "clean_package_cruft", flag);
    thread->start();
}

//从状态列表中得到指定的某个软件的状态
QString SystemDispatcher::getSoftwareStatus(QString key) {
    QVariant tt = status_dict.value(key);
    return tt.toString();
}

// -------------------------software-center-------------------------
void SystemDispatcher::install_pkg_qt(QString pkgName) {
    KThread *thread = new KThread(tmplist, systemiface, "install_pkg", pkgName);
    thread->start();
}

void SystemDispatcher::uninstall_pkg_qt(QString pkgName) {
    KThread *thread = new KThread(tmplist, systemiface, "uninstall_pkg", pkgName);
    thread->start();
}

void SystemDispatcher::update_pkg_qt(QString pkgName) {
    KThread *thread = new KThread(tmplist, systemiface, "update_pkg", pkgName);
    thread->start();
}

void SystemDispatcher::check_pkgs_status_qt(QStringList pkgNameList) {
    KThread *thread = new KThread(pkgNameList, systemiface, "check_pkgs_status");
    thread->start();
}

QString SystemDispatcher::check_pkg_status_qt(QString pkgName) {
    QDBusReply<QString> reply = systemiface->call("check_pkg_status", pkgName);
    return reply.value();
}

void SystemDispatcher::apt_get_update_qt() {
    KThread *thread = new KThread(tmplist, systemiface, "apt_get_update");
    thread->start();
}

void SystemDispatcher::ready_show_app_page(QString flag) {
    emit sendAppInfo(flag);
}

QString SystemDispatcher::getSingleInfo(QString key) {
    QString info = appInfo.value(key);
    return info;
}

//获取所有软件的的可执行程序的名字列表，此名字对应着源里面的安装程序的名字，用该名字可以获取软件状态
QStringList SystemDispatcher::getAllSoftwareExecNameList() {
    QStringList execNameList = config->value(QString("app-list/AllExecList")).toStringList();
    config->sync();
    return execNameList;

}

//得到所有app的列表，根据列表的名字可以显示所有软件机器logo到推荐界面上
void SystemDispatcher::getAppListForDisPlay() {
    QFile appFile(APP_LIST_FILE);
    if(appFile.exists()) {
        appList = config->value(QString("app-list/AppList")).toStringList();
        config->sync();
        emit sendAppListToQML(appList);
    }
    else {
        //警告：   没有找到软件列表文件！
        QMessageBox::warning(NULL,
                             tr("Warning:"),
                             tr("No find the softlist file!"),
                             QMessageBox::Ok);
    }
}

void SystemDispatcher::getAppInfo(QString flag) {
    QFile appFile(APP_LIST_FILE);
    if(appFile.exists()) {
        appInfo["name"] = config->value(flag + QString("/name")).toString();
        appInfo["title"] = config->value(flag + QString("/title")).toString();
        appInfo["logo"] = config->value(flag + QString("/logo")).toString();
        appInfo["description"] = config->value(flag + QString("/description")).toString();
        appInfo["image1"] = config->value(flag + QString("/image1")).toString();
        appInfo["image2"] = config->value(flag + QString("/image2")).toString();
        config->sync();
    }
    else {
        //警告：   没有找到软件列表文件！
        QMessageBox::warning(NULL,
                             tr("Warning:"),
                             tr("No find the softlist file!"),
                             QMessageBox::Ok);
    }
}

void SystemDispatcher::startUpdateSoftwareSource() {
    emit callMasklayer();
    apt_get_update_qt();
}
