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

#include "youkersessiondbus.h"
#include <QDebug>

SessionDispatcher::SessionDispatcher(QObject *parent)
    : QObject(parent)
{
    sessioniface = new QDBusInterface("com.kylin.assistant.sessiondaemon",
                               "/com/kylin/assistant/sessiondaemon",
                               "com.kylin.assistant.sessiondaemon",
                               QDBusConnection::sessionBus());
    qDebug() << "Starting SessionDispatcher";
//    QObject::connect(sessioniface, SIGNAL(autostartmanage_data_signal(QVariantMap)), this, SLOT(handlerAutoManageData(QVariantMap)));

    QObject::connect(sessioniface, SIGNAL(autostartmanage_data_signal(QStringList)), this, SLOT(handlerAutoManageData(QStringList)));
    QObject::connect(sessioniface, SIGNAL(autostartmanage_status_signal(QString)), this, SLOT(handlerAutoManageStatus(QString)));
    QObject::connect(sessioniface, SIGNAL(autostartmanage_error_signal(QString)), this, SLOT(handlerAutoManageError(QString)));

    QObject::connect(sessioniface, SIGNAL(subpage_data_signal(QStringList)), this, SLOT(handlerScanCleanerData(QStringList)));
    QObject::connect(sessioniface, SIGNAL(subpage_status_signal(QString)), this, SLOT(handlerScanCleanerStatus(QString)));
    QObject::connect(sessioniface, SIGNAL(subpage_error_signal(QString)), this, SLOT(handlerScanCleanerError(QString)));

//    thread = new KThread(this);

/*
    //kobe
    check_thread = new KThread(this);
    scan_thread = new KThread(this);
    onekey_scan_thread = new KThread(this);
*/

    QObject::connect(sessioniface, SIGNAL(display_scan_process(QString)), this, SLOT(handler_scan_process(QString)));
    QObject::connect(sessioniface, SIGNAL(scan_complete(QString)), this, SLOT(handler_scan_complete(QString)));
    QObject::connect(sessioniface, SIGNAL(total_data_transmit(QString, QString)), this, SLOT(handler_total_data_transmit(QString,QString)));
    QObject::connect(sessioniface, SIGNAL(youkerid_whoami_signal(QString, QString)), this, SLOT(handlerYoukerID(QString, QString)));
    QObject::connect(sessioniface, SIGNAL(youkerid_logout_signal()), this, SLOT(handlerLogoutSuccess()));
    QObject::connect(sessioniface, SIGNAL(youkerid_login_fail_signal()), this, SLOT(handlerLoginFail()));


    QObject::connect(sessioniface, SIGNAL(notify_boolean(QString, bool)), this, SLOT(handler_notify_boolean(QString, bool)));
    QObject::connect(sessioniface, SIGNAL(notify_int(QString, int)), this, SLOT(handler_notify_int(QString, int)));
    QObject::connect(sessioniface, SIGNAL(notify_double(QString, double)), this, SLOT(handler_notify_double(QString, double)));
    QObject::connect(sessioniface, SIGNAL(notify_string(QString, QString)), this, SLOT(handler_notify_string(QString, QString)));

    QObject::connect(sessioniface, SIGNAL(check_source_list_signal(bool)), this, SIGNAL(receive_source_list_signal(bool)));

    //pingback
    this->submit_uk_pingback();
}

SessionDispatcher::~SessionDispatcher() {
    /*check_thread->terminate();
    check_thread->wait();
    if(check_thread != NULL) {
        delete check_thread;
        check_thread = NULL;
    }
    scan_thread->terminate();
    scan_thread->wait();
    if(scan_thread != NULL) {
        delete scan_thread;
        scan_thread = NULL;
    }
    onekey_scan_thread->terminate();
    onekey_scan_thread->wait();
    if(onekey_scan_thread != NULL) {
        delete onekey_scan_thread;
        onekey_scan_thread = NULL;
    }*/


//    thread->terminate();
//    thread->wait();
//    if(thread != NULL) {
//        delete thread;
//        thread = NULL;
//    }
    this->exit_qt();
    if (sessioniface != NULL) {
        delete sessioniface;
        sessioniface = NULL;
    }
}

//dbus服务退出
void SessionDispatcher::exit_qt()
{
    sessioniface->call("exit");
}

QString SessionDispatcher::get_os_release_qt()
{
    QDBusReply<QString> reply = sessioniface->call("get_os_release");
    return reply.value();
}

bool SessionDispatcher::submit_uk_pingback()
{
    QDBusReply<bool> reply = sessioniface->call("submit_uk_pingback", qApp->applicationVersion());
    return reply.value();
}

QStringList SessionDispatcher::checkNewVersion()
{
    QDBusReply<QStringList> reply = sessioniface->call("currently_installed_version");
    return reply.value();
}

void SessionDispatcher::start_check_source_useable_qt()
{
    sessioniface->call("start_check_source_useable");

    /*if (check_thread->isRunning()) {
        qDebug() << "check_thread is running......";
    }
    else {
        QMap<QString, QVariant> data;
        QStringList tmplist;
        check_thread->initValues(data, tmplist, sessioniface, "start_check_source_useable");
        check_thread->start();
//        qDebug() << "check_thread is ready to run......";
    }
    return true;*/
}

void SessionDispatcher::runApp(QString pkgname)
{
    sessioniface->call("run_selected_app", pkgname);
}

void SessionDispatcher::handlerAutoManageData(QStringList data)
//void SessionDispatcher::handlerAutoManageData(const QVariantMap &data)
{
    emit this->tellAutoModel(data);
}

void SessionDispatcher::handlerAutoManageStatus(QString status)
{
    emit this->showAutoModel();
}

void SessionDispatcher::handlerAutoManageError(QString status)
{

}

void SessionDispatcher::getAutoStartAppStatus()
{
    sessioniface->call("get_current_autostart_status");
}

bool SessionDispatcher::getSingleAutoStartStatus(QString abs_path)
{
    QDBusReply<bool> reply = sessioniface->call("get_current_single_autostart_status", abs_path);
    return reply.value();
}


void SessionDispatcher::changeAutoStartAppStatus(QString appName)
{
    sessioniface->call("change_autostart_status", appName);
}

void SessionDispatcher::handlerScanCleanerData(QStringList data)
{
    emit this->tellCleanerDetailData(data);
}

void SessionDispatcher::handlerScanCleanerStatus(QString status)
{
    emit this->tellCleanerDetailStatus(status);
}

void SessionDispatcher::handlerScanCleanerError(QString status)
{
    emit this->tellCleanerDetailError(status);
}

//bool SessionDispatcher::judge_camera_qt() {
//    QDBusReply<bool> reply = sessioniface->call("judge_camera");
//    return reply.value();
//}

//void SessionDispatcher::call_camera_qt() {
//    sessioniface->call("call_camera");
////    if (thread->isRunning()) {
////        qDebug() << "camera_thread is running......";
////    }
////    else {
////        qDebug() << "camera_thread is ready to run......";
////        QStringList tmp;
////        QMap<QString, QVariant> data;
////        thread->initValues(data, tmp, sessioniface, "call_camera");
////        thread->start();
////    }
//}

bool SessionDispatcher::judge_power_is_exists_qt()
{
    QDBusReply<bool> reply = sessioniface->call("judge_power_is_exists");
    return reply.value();
}

QMap<QString, QVariant> SessionDispatcher::read_battery_info_qt()
{
    QMap<QString, QVariant> value;
    QDBusReply<QMap<QString, QVariant> > reply = sessioniface->call("read_battery_info");
    if (reply.isValid()) {
        value = reply.value();
        if (value.contains("POWER_SUPPLY_VOLTAGE_NOW")) {
            value["POWER_SUPPLY_VOLTAGE_NOW"] =  QString::number(value["POWER_SUPPLY_VOLTAGE_NOW"].toDouble()/1000000, 'f', 1) + "V";
        }
        if (value.contains("POWER_SUPPLY_ENERGY_FULL_DESIGN")) {
            value["POWER_SUPPLY_ENERGY_FULL_DESIGN"] =  QString::number(value["POWER_SUPPLY_ENERGY_FULL_DESIGN"].toDouble()/1000000, 'f', 1) + "Wh";
        }
        if (value.contains("POWER_SUPPLY_ENERGY_FULL")) {
            value["POWER_SUPPLY_ENERGY_FULL"] =  QString::number(value["POWER_SUPPLY_ENERGY_FULL"].toDouble()/1000000, 'f', 1) + "Wh";
        }
        if (value.contains("POWER_SUPPLY_ENERGY_NOW")) {
            value["POWER_SUPPLY_ENERGY_NOW"] =  QString::number(value["POWER_SUPPLY_ENERGY_NOW"].toDouble()/1000000, 'f', 1) + "Wh";
        }
        return value;
    }
    else {
        qDebug() << "get battery_message failed!";
//        QMap<QString, QVariant> value;
//        value.insert("kylinkobe", "kylinkobe");
        return value;
    }
}

void SessionDispatcher::open_folder_qt(QString path)
{
    sessioniface->call("open_folder", path);
}

void SessionDispatcher::check_user_qt()
{
//    sessioniface->call("check_user");
}

//弹出登录框
void SessionDispatcher::popup_login_dialog()
{
    //add ubuntukylin sso
//    sessioniface->call("slot_do_login_account");
}

void SessionDispatcher::popup_register_dialog()
{
    //add ubuntukylin sso
//    sessioniface->call("slot_do_register");
}

//退出登录
void SessionDispatcher::logout_ubuntukylin_account()
{
    //add ubuntukylin sso
//    sessioniface->call("slot_do_logout");
}

void SessionDispatcher::handlerYoukerID(QString displayName, QString emailAddress)
{
    emit this->ssoSuccessSignal(displayName, emailAddress);
}

void SessionDispatcher::handlerLogoutSuccess()
{
    emit this->ssoLoginLogoutSignal(true);
}

void SessionDispatcher::handlerLoginFail()
{
    emit this->ssoLoginLogoutSignal(false);
}

void SessionDispatcher::handler_scan_complete(QString msg)
{
    emit finishScanWork(msg);
}

void SessionDispatcher::handler_scan_process(QString msg)
{
    emit isScanning(msg);
}

void SessionDispatcher::handler_total_data_transmit(QString flag, QString msg)
{
    emit tellScanResult(flag, msg);
}

//QString SessionDispatcher::get_locale_version() {
//    QString locale = QLocale::system().name();
//    return locale;
//}

//一键扫描
void SessionDispatcher::onekey_scan_function_qt(QStringList selectedList)
{
//    QMap<QString, QVariant> data;
//    thread->initValues(data, selectedList, sessioniface, "onekey_scan_function");
//    thread->start();


    sessioniface->call("onekey_scan_function", selectedList);


    /*if (scan_thread->isRunning()) {
        qDebug() << "onekey_scan_thread is running......";
    }
    else {
//        qDebug() << "onekey_scan_thread is ready to run......";
        QMap<QString, QVariant> data;
        onekey_scan_thread->initValues(data, selectedList, sessioniface, "onekey_scan_function");
        onekey_scan_thread->start();
    }*/
}

//系统扫描
void SessionDispatcher::scanSystemCleanerItems(QMap<QString, QVariant> data)
{
    sessioniface->call("get_scan_result", data);

    /*if (scan_thread->isRunning()) {
        qDebug() << "scan_thread is running......";
    }
    else {
//        if (scan_thread == NULL)
//            qDebug() << "scan_thread is null, ready to run......";
//        else
//            qDebug() << "scan_thread is not null, ready to run......";
        QStringList tmp;
        scan_thread->initValues(data, tmp, sessioniface, "get_scan_result");
        scan_thread->start();
//        QElapsedTimer et;
//        et.start();
//        while(et.elapsed()<300)
//            QCoreApplication::processEvents();
    }*/
}

QString SessionDispatcher::getHomePath()
{
    QString homepath = QDir::homePath();
    return homepath;
}

//QString SessionDispatcher::get_session_daemon_qt() {
//    QDBusReply<QString> reply = sessioniface->call("get_session_daemon");
//    return reply.value();
//}

QMap<QString, QVariant>  SessionDispatcher::get_system_message_qt()
{
    QMap<QString, QVariant> value;
    QDBusReply<QMap<QString, QVariant> > reply = sessioniface->call("get_system_message");
    if (reply.isValid()) {
        value = reply.value();
        return value;
//        systemInfo.clear();
//        systemInfo = value;
        //把当前登录的用户名存放到QSetting配置文件中，方便任务管理器使用
//        mSettings->beginGroup("user");
//        mSettings->setValue("currentName", systemInfo["currrent_user"].toString());
//        mSettings->endGroup();
//        mSettings->sync();
    }
    else {
        qDebug() << "get pc_message failed!";
//        QMap<QString, QVariant> value;
//        value.insert("kylinkobe", "kylinkobe");
        return value;
    }
}

/*-----------------------------desktop of beauty-----------------------------*/
bool SessionDispatcher::set_show_desktop_icons_qt(bool flag)
{
    QDBusReply<bool> reply = sessioniface->call("set_show_desktop_icons", flag);
    return reply.value();
}

bool SessionDispatcher::get_show_desktop_icons_qt()
{
    QDBusReply<bool> reply = sessioniface->call("get_show_desktop_icons");
    return reply.value();
}

bool SessionDispatcher::set_show_computer_qt(bool flag)
{
    QDBusReply<bool> reply = sessioniface->call("set_show_computer", flag);
    return reply.value();
}

bool SessionDispatcher::get_show_computer_qt()
{
    QDBusReply<bool> reply = sessioniface->call("get_show_computer");
    return reply.value();
}

bool SessionDispatcher::set_show_homefolder_qt(bool flag)
{
    QDBusReply<bool> reply = sessioniface->call("set_show_homefolder", flag);
    return reply.value();
}

bool SessionDispatcher::get_show_homefolder_qt()
{
    QDBusReply<bool> reply = sessioniface->call("get_show_homefolder");
    return reply.value();
}

bool SessionDispatcher::set_show_network_qt(bool flag)
{
    QDBusReply<bool> reply = sessioniface->call("set_show_network", flag);
    return reply.value();
}

bool SessionDispatcher::get_show_network_qt()
{
    QDBusReply<bool> reply = sessioniface->call("get_show_network");
    return reply.value();
}

bool SessionDispatcher::set_show_trash_qt(bool flag)
{
    QDBusReply<bool> reply = sessioniface->call("set_show_trash", flag);
    return reply.value();
}

bool SessionDispatcher::get_show_trash_qt()
{
    QDBusReply<bool> reply = sessioniface->call("get_show_trash");
    return reply.value();
}

bool SessionDispatcher::set_show_devices_qt(bool flag)
{
    QDBusReply<bool> reply = sessioniface->call("set_show_devices", flag);
    return reply.value();
}

bool SessionDispatcher::get_show_devices_qt()
{
    QDBusReply<bool> reply = sessioniface->call("get_show_devices");
    return reply.value();
}

//bool SessionDispatcher::get_show_cinnamon_desktop_icons_qt() {
//    QDBusReply<bool> reply = sessioniface->call("get_show_cinnamon_desktop_icons");
//    return reply.value();
//}

//bool SessionDispatcher::set_show_cinnamon_desktop_icons_qt(bool flag) {
//    QDBusReply<bool> reply = sessioniface->call("set_show_cinnamon_desktop_icons", flag);
//    return reply.value();
//}

//bool SessionDispatcher::get_show_cinnamon_computer_qt() {
//    QDBusReply<bool> reply = sessioniface->call("get_show_cinnamon_computer");
//    return reply.value();
//}

//bool SessionDispatcher::set_show_cinnamon_computer_qt(bool flag) {
//    QDBusReply<bool> reply = sessioniface->call("set_show_cinnamon_computer", flag);
//    return reply.value();
//}

//bool SessionDispatcher::get_show_cinnamon_homefolder_qt() {
//    QDBusReply<bool> reply = sessioniface->call("get_show_cinnamon_homefolder");
//    return reply.value();
//}

//bool SessionDispatcher::set_show_cinnamon_homefolder_qt(bool flag) {
//    QDBusReply<bool> reply = sessioniface->call("set_show_cinnamon_homefolder", flag);
//    return reply.value();
//}

//bool SessionDispatcher::get_show_cinnamon_network_qt() {
//    QDBusReply<bool> reply = sessioniface->call("get_show_cinnamon_network");
//    return reply.value();
//}

//bool SessionDispatcher::set_show_cinnamon_network_qt(bool flag) {
//    QDBusReply<bool> reply = sessioniface->call("set_show_cinnamon_network", flag);
//    return reply.value();
//}

//bool SessionDispatcher::get_show_cinnamon_trash_qt() {
//    QDBusReply<bool> reply = sessioniface->call("get_show_cinnamon_trash");
//    return reply.value();
//}

//bool SessionDispatcher::set_show_cinnamon_trash_qt(bool flag) {
//    QDBusReply<bool> reply = sessioniface->call("set_show_cinnamon_trash", flag);
//    return reply.value();
//}

//bool SessionDispatcher::get_show_cinnamon_devices_qt() {
//    QDBusReply<bool> reply = sessioniface->call("get_show_cinnamon_devices");
//    return reply.value();
//}
//bool SessionDispatcher::set_show_cinnamon_devices_qt(bool flag) {
//    QDBusReply<bool> reply = sessioniface->call("set_show_cinnamon_devices", flag);
//    return reply.value();
//}

/*-----------------------------unity of beauty-----------------------------*/
//void SessionDispatcher::set_default_launcher_have_showdesktopicon_qt() {
//    sessioniface->call("set_default_launcher_have_showdesktopicon");
//}

bool SessionDispatcher::set_launcher_autohide_qt(bool flag)
{
    QDBusReply<bool> reply = sessioniface->call("set_launcher_autohide", flag);
    return reply.value();
//    return true;
}

bool SessionDispatcher::get_launcher_autohide_qt()
{
    QDBusReply<bool> reply = sessioniface->call("get_launcher_autohide");
    return reply.value();
//    return true;
}

bool SessionDispatcher::set_launcher_icon_size_qt(int num)
{
    QDBusReply<bool> reply = sessioniface->call("set_launcher_icon_size", num);
    return reply.value();
}

int SessionDispatcher::get_launcher_icon_size_qt()
{
    QDBusReply<int> reply = sessioniface->call("get_launcher_icon_size");
    return reply.value();
//    return 32;
}
bool SessionDispatcher::set_launcher_have_showdesktopicon_qt(bool flag)
{
    QDBusReply<bool> reply = sessioniface->call("set_launcher_have_showdesktopicon", flag);
    return reply.value();
//    return true;
}

bool SessionDispatcher::get_launcher_have_showdesktopicon_qt()
{
    QDBusReply<bool> reply = sessioniface->call("get_launcher_have_showdesktopicon");
    return reply.value();
//    return true;
}

//-----------------------------------------------mate----------------------------------------------
bool SessionDispatcher::set_mate_panel_autohide_qt(QString positon, bool flag)
{
    QDBusReply<bool> reply = sessioniface->call("set_mate_panel_autohide", positon, flag);
    return reply.value();
}

bool SessionDispatcher::get_mate_panel_autohide_qt(QString positon)
{
    QDBusReply<bool> reply = sessioniface->call("get_mate_panel_autohide", positon);
    return reply.value();
}

bool SessionDispatcher::set_mate_panel_icon_size_qt(QString positon, int num)
{
    QDBusReply<bool> reply = sessioniface->call("set_mate_panel_icon_size", positon, num);
    return reply.value();
}

int SessionDispatcher::get_mate_panel_icon_size_qt(QString positon)
{
    QDBusReply<int> reply = sessioniface->call("get_mate_panel_icon_size", positon);
    return reply.value();
}

//透明度
double SessionDispatcher::get_launcher_transparency_qt() {
    QDBusReply<double> reply = sessioniface->call("get_launcher_transparency");
    return reply.value();
//    return 0.0;
}

bool SessionDispatcher::set_launcher_transparency_qt(double opacity) {
    QDBusReply<bool> reply = sessioniface->call("set_launcher_transparency", opacity);
    return reply.value();
}

//图标背景
QStringList SessionDispatcher::get_all_launcher_icon_colourings_qt() {
    QDBusReply<QStringList> reply = sessioniface->call("get_all_launcher_icon_colourings");
    return reply.value();
//    return QStringList();
}

int SessionDispatcher::get_launcher_icon_colouring_qt() {
    QDBusReply<int> reply = sessioniface->call("get_launcher_icon_colouring");
    return reply.value();
//    return 0;
}

bool SessionDispatcher::set_launcher_icon_colouring_qt(int colouring)
{
    QDBusReply<bool> reply = sessioniface->call("set_launcher_icon_colouring", colouring);
    return reply.value();
}

//Dash背景模糊类型
int SessionDispatcher::get_dash_blur_experimental_qt() {
    QDBusReply<int> reply = sessioniface->call("get_dash_blur_experimental");
    return reply.value();
}

bool SessionDispatcher::set_dash_blur_experimental_qt(int blur) {
    QDBusReply<bool> reply = sessioniface->call("set_dash_blur_experimental", blur);
    return reply.value();
}

//面板菜单透明度
double SessionDispatcher::get_panel_transparency_qt() {
    QDBusReply<double> reply = sessioniface->call("get_panel_transparency");
    return reply.value();
}

bool SessionDispatcher::set_panel_transparency_qt(double opacity) {
    QDBusReply<bool> reply = sessioniface->call("set_panel_transparency", opacity);
    return reply.value();
}

//日期时间格式
QStringList SessionDispatcher::get_all_time_format_qt() {
    QDBusReply<QStringList> reply = sessioniface->call("get_all_time_format");
    return reply.value();
}

QString SessionDispatcher::get_time_format_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_time_format");
    return reply.value();
}

bool SessionDispatcher::set_time_format_qt(QString format) {
    QDBusReply<bool> reply = sessioniface->call("set_time_format", format);
    return reply.value();
}

bool SessionDispatcher::get_show_seconds_qt() {
    QDBusReply<bool> reply = sessioniface->call("get_show_seconds");
    return reply.value();
}

bool SessionDispatcher::set_show_seconds_qt(bool flag) {
    QDBusReply<bool> reply = sessioniface->call("set_show_seconds", flag);
    return reply.value();
}

bool SessionDispatcher::get_show_week_qt() {
    QDBusReply<bool> reply = sessioniface->call("get_show_week");
    return reply.value();
}

bool SessionDispatcher::set_show_week_qt(bool flag) {
    QDBusReply<bool> reply = sessioniface->call("set_show_week", flag);
    return reply.value();
}

bool SessionDispatcher::get_show_date_qt() {
    QDBusReply<bool> reply = sessioniface->call("get_show_date");
    return reply.value();
}

bool SessionDispatcher::set_show_date_qt(bool flag) {
    QDBusReply<bool> reply = sessioniface->call("set_show_date", flag);
    return reply.value();
}

//电源
QStringList SessionDispatcher::get_all_power_icon_policy_qt() {
    QDBusReply<QStringList> reply = sessioniface->call("get_all_power_icon_policy");
    return reply.value();
}

QString SessionDispatcher::get_power_icon_policy_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_power_icon_policy");
    return reply.value();
}

bool SessionDispatcher::set_power_icon_policy_qt(QString format) {
    QDBusReply<bool> reply = sessioniface->call("set_power_icon_policy", format);
    return reply.value();
}

bool SessionDispatcher::get_show_power_time_qt() {
    QDBusReply<bool> reply = sessioniface->call("get_show_power_time");
    return reply.value();
}

bool SessionDispatcher::set_show_power_time_qt(bool flag) {
    QDBusReply<bool> reply = sessioniface->call("set_show_power_time", flag);
    return reply.value();
}

bool SessionDispatcher::get_show_power_percentage_qt() {
    QDBusReply<bool> reply = sessioniface->call("get_show_power_percentage");
    return reply.value();
}

bool SessionDispatcher::set_show_power_percentage_qt(bool flag) {
    QDBusReply<bool> reply = sessioniface->call("set_show_power_percentage", flag);
    return reply.value();
}

//--------------------------mate--------------------
bool SessionDispatcher::get_show_apps_qt() {
    QDBusReply<bool> reply = sessioniface->call("get_show_apps");
    return reply.value();
}

bool SessionDispatcher::set_show_apps_qt(bool flag) {
    QDBusReply<bool> reply = sessioniface->call("set_show_apps", flag);
    return reply.value();
}

bool SessionDispatcher::get_show_desktop_qt() {
    QDBusReply<bool> reply = sessioniface->call("get_show_desktop");
    return reply.value();
}

bool SessionDispatcher::set_show_desktop_qt(bool flag) {
    QDBusReply<bool> reply = sessioniface->call("set_show_desktop", flag);
    return reply.value();
}

bool SessionDispatcher::get_show_icon_qt() {
    QDBusReply<bool> reply = sessioniface->call("get_show_icon");
    return reply.value();
}

bool SessionDispatcher::set_show_icon_qt(bool flag) {
    QDBusReply<bool> reply = sessioniface->call("set_show_icon", flag);
    return reply.value();
}

bool SessionDispatcher::get_show_places_qt() {
    QDBusReply<bool> reply = sessioniface->call("get_show_places");
    return reply.value();
}

bool SessionDispatcher::set_show_places_qt(bool flag) {
    QDBusReply<bool> reply = sessioniface->call("set_show_places", flag);
    return reply.value();
}


/*-----------------------------theme of beauty-----------------------------*/
QStringList SessionDispatcher::get_themes_qt() {
    QDBusReply<QStringList> reply = sessioniface->call("get_themes");
    return reply.value();
}

QString SessionDispatcher::get_theme_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_theme");
    return reply.value();
}

void SessionDispatcher::set_theme_qt(QString theme) {
    sessioniface->call("set_theme", theme);
}

QStringList SessionDispatcher::get_icon_themes_qt() {
    QDBusReply<QStringList> reply = sessioniface->call("get_icon_themes");
    return reply.value();
}

QString SessionDispatcher::get_icon_theme_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_icon_theme");
    return reply.value();
}

void SessionDispatcher::set_icon_theme_qt(QString theme) {
    sessioniface->call("set_icon_theme", theme);
}

QStringList SessionDispatcher::get_cursor_themes_qt() {
    QDBusReply<QStringList> reply = sessioniface->call("get_cursor_themes");
    return reply.value();
}

QString SessionDispatcher::get_cursor_theme_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_cursor_theme");
    return reply.value();
}

void SessionDispatcher::set_cursor_theme_qt(QString theme) {
    sessioniface->call("set_cursor_theme", theme);
}

int SessionDispatcher::get_cursor_size_qt() {
    QDBusReply<int> reply = sessioniface->call("get_cursor_size");
    return reply.value();
}
void SessionDispatcher::set_cursor_size_qt(int size) {
    sessioniface->call("set_cursor_size", size);
}

//window theme
//QStringList SessionDispatcher::get_window_themes_qt() {
//    QDBusReply<QStringList> reply = sessioniface->call("get_window_themes");
//    return reply.value();
//}

//QString SessionDispatcher::get_current_window_theme_qt() {
//    QDBusReply<QString> reply = sessioniface->call("get_current_window_theme");
//    return reply.value();
//}

//void SessionDispatcher::set_window_theme_qt(QString theme) {
//    sessioniface->call("set_window_theme", theme);
//}

QString SessionDispatcher::get_default_font_string_qt(QString schema, QString key)
{
    QDBusReply<QString> reply = sessioniface->call("get_default_font_string", schema, key);
    return reply.value();
}

bool SessionDispatcher::set_default_font_string_qt(QString schema, QString key, QString type)
{
    QDBusReply<bool> reply = sessioniface->call("set_default_font", schema, key, type);
    return reply.value();
}

QString SessionDispatcher::get_font_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_font");
    return reply.value();
}

//bool SessionDispatcher::set_font_qt_default(QString font) {
//    QDBusReply<bool> reply = sessioniface->call("set_font", font);
//    return reply.value();
//}

bool SessionDispatcher::set_font_qt(QString font) {
    QDBusReply<bool> reply = sessioniface->call("set_font", font);
    return reply.value();
}

QString SessionDispatcher::get_desktop_font_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_desktop_font");
    return reply.value();
}

bool SessionDispatcher::set_desktop_font_qt(QString font) {
    QDBusReply<bool> reply = sessioniface->call("set_desktop_font", font);
    return reply.value();
}

bool SessionDispatcher::set_desktop_font_qt_default() {
    QDBusReply<bool> reply = sessioniface->call("set_desktop_font", "Ubuntu 11");
    return reply.value();
}

QString SessionDispatcher::get_document_font_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_document_font");
    return reply.value();
}

//bool SessionDispatcher::set_document_font_qt_default(QString font) {
//    QDBusReply<bool> reply = sessioniface->call("set_document_font", font);
//    return reply.value();
//}

bool SessionDispatcher::set_document_font_qt(QString font) {
    QDBusReply<bool> reply = sessioniface->call("set_document_font", font);
    return reply.value();
}

QString SessionDispatcher::get_monospace_font_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_monospace_font");
    return reply.value();
}

//bool SessionDispatcher::set_monospace_font_qt_default(QString font) {
//    QDBusReply<bool> reply = sessioniface->call("set_monospace_font", font);
//    return reply.value();
//}

bool SessionDispatcher::set_monospace_font_qt(QString font) {
    QDBusReply<bool> reply = sessioniface->call("set_monospace_font", font);
    return reply.value();
}

QString SessionDispatcher::get_window_title_font_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_window_title_font");
    return reply.value();
}

//bool SessionDispatcher::set_window_title_font_qt_default(QString font) {
//    QDBusReply<bool> reply = sessioniface->call("set_window_title_font", font);
//    return reply.value();
//}

bool SessionDispatcher::set_window_title_font_qt(QString font) {
    QDBusReply<bool> reply = sessioniface->call("set_window_title_font", font);
    return reply.value();
}

double SessionDispatcher::get_font_zoom_qt() {
    QDBusReply<double> reply = sessioniface->call("get_font_zoom");
    return reply.value();
}

bool SessionDispatcher::set_font_zoom_qt(double zoom) {
    QDBusReply<bool> reply = sessioniface->call("set_font_zoom", zoom);
    return reply.value();
}

QStringList SessionDispatcher::get_smooth_style_list_qt() {
    QDBusReply<QStringList> reply = sessioniface->call("get_smooth_style_list");
    return reply.value();
}

QString SessionDispatcher::get_smooth_style_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_smooth_style");
    return reply.value();
}

bool SessionDispatcher::set_smooth_style_qt(QString style) {
    QDBusReply<bool> reply = sessioniface->call("set_smooth_style", style);
    return reply.value();
}

QStringList SessionDispatcher::get_antialiasing_style_list_qt() {
    QDBusReply<QStringList> reply = sessioniface->call("get_antialiasing_style_list");
    return reply.value();
}

QString SessionDispatcher::get_antialiasing_style_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_antialiasing_style");
    return reply.value();
}

bool SessionDispatcher::set_antialiasing_style_qt(QString style) {
    QDBusReply<bool> reply = sessioniface->call("set_antialiasing_style", style);
    return reply.value();
}

/*-----------------------------scrollbars of beauty-----------------------------*/
bool SessionDispatcher::set_scrollbars_mode_overlay_qt() {
    QDBusReply<bool> reply = sessioniface->call("set_scrollbars_mode_overlay");
    return reply.value();
}

bool SessionDispatcher::set_scrollbars_mode_legacy_qt() {
    QDBusReply<bool> reply = sessioniface->call("set_scrollbars_mode_legacy");
    return reply.value();
}

QString SessionDispatcher::get_scrollbars_mode_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_scrollbars_mode");
    return reply.value();
}

/*-----------------------------touchpad of beauty-----------------------------*/
bool SessionDispatcher::set_touchpad_enable_qt(bool flag) {
    QDBusReply<bool> reply = sessioniface->call("set_touchpad_enable", flag);
    return reply.value();
}

bool SessionDispatcher::get_touchpad_enable_qt() {
    QDBusReply<bool> reply = sessioniface->call("get_touchpad_enable");
    return reply.value();
}

bool SessionDispatcher::set_touchscrolling_mode_disabled_qt() {
    QDBusReply<bool> reply = sessioniface->call("set_touchscrolling_mode_disabled");
    return reply.value();
}

bool SessionDispatcher::set_touchscrolling_mode_edge_qt() {
    QDBusReply<bool> reply = sessioniface->call("set_touchscrolling_mode_edge");
    return reply.value();
}

bool SessionDispatcher::set_touchscrolling_mode_twofinger_qt() {
    QDBusReply<bool> reply = sessioniface->call("set_touchscrolling_mode_twofinger");
    return reply.value();
}

QString SessionDispatcher::get_touchscrolling_mode_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_touchscrolling_mode");
    return reply.value();
}

bool SessionDispatcher::set_touchscrolling_use_horizontal_qt(bool flag) {
    QDBusReply<bool> reply = sessioniface->call("set_touchscrolling_use_horizontal", flag);
    return reply.value();
}

bool SessionDispatcher::get_touchscrolling_use_horizontal_qt() {
    QDBusReply<bool> reply = sessioniface->call("get_touchscrolling_use_horizontal");
    return reply.value();
}

int SessionDispatcher::get_mate_touchscrolling_mode_qt()
{
    QDBusReply<int> reply = sessioniface->call("get_mate_touchscrolling_mode");
    return reply.value();
}

bool SessionDispatcher::set_mate_touchscrolling_mode_qt(int value)
{
    QDBusReply<bool> reply = sessioniface->call("set_mate_touchscrolling_mode", value);
    return reply.value();
}

/*-----------------------------window of beauty-----------------------------*/
void SessionDispatcher::set_window_button_align_left_qt() {
    sessioniface->call("set_window_button_align_left");
}

void SessionDispatcher::set_window_button_align_right_qt() {
    sessioniface->call("set_window_button_align_right");
}

QString SessionDispatcher::get_window_button_align_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_window_button_align");
    return reply.value();
}

bool SessionDispatcher::set_menus_have_icons_qt(bool flag) {
    QDBusReply<bool> reply = sessioniface->call("set_menus_have_icons", flag);
    return reply.value();
}

bool SessionDispatcher::get_menus_have_icons_qt() {
    QDBusReply<bool> reply = sessioniface->call("get_menus_have_icons");
    return reply.value();
}

QStringList SessionDispatcher::get_titlebar_wheel_qt() {
    QDBusReply<QStringList> reply = sessioniface->call("get_titlebar_wheel");
    return reply.value();
}

QString SessionDispatcher::get_current_titlebar_wheel_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_current_titlebar_wheel");
    return reply.value();
}

void SessionDispatcher::set_titlebar_wheel_qt(QString value) {
    sessioniface->call("set_titlebar_wheel", value);
}

QStringList SessionDispatcher::get_titlebar_options_qt() {
    QDBusReply<QStringList> reply = sessioniface->call("get_titlebar_options");
    return reply.value();
}

QString SessionDispatcher::get_current_titlebar_double_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_current_titlebar_double");
    return reply.value();
}

void SessionDispatcher::set_titlebar_double_qt(QString value) {
    sessioniface->call("set_titlebar_double", value);
}

//QStringList SessionDispatcher::get_titlebar_middle_qt() {
//    QDBusReply<QStringList> reply = sessioniface->call("get_titlebar_middle");
//    return reply.value();
//}

QString SessionDispatcher::get_current_titlebar_middle_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_current_titlebar_middle");
    return reply.value();
}

void SessionDispatcher::set_titlebar_middle_qt(QString value) {
    sessioniface->call("set_titlebar_middle", value);
}

//QStringList SessionDispatcher::get_titlebar_right_qt() {
//    QDBusReply<QStringList> reply = sessioniface->call("get_titlebar_right");
//    return reply.value();
//}

QString SessionDispatcher::get_current_titlebar_right_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_current_titlebar_right");
    return reply.value();
}

void SessionDispatcher::set_titlebar_right_qt(QString value) {
    sessioniface->call("set_titlebar_right", value);
}

/*-----------------------------sound of beauty-----------------------------*/
bool SessionDispatcher::get_sound_event_enable_qt() {
    QDBusReply<bool> reply = sessioniface->call("get_sound_event_enable");
    return reply.value();
}

void SessionDispatcher::set_sound_event_enable_qt(bool flag) {
    sessioniface->call("set_sound_event_enable", flag);
}

bool SessionDispatcher::get_input_feedback_sounds_enable_qt() {
    QDBusReply<bool> reply = sessioniface->call("get_input_feedback_sounds_enable");
    return reply.value();
}

void SessionDispatcher::set_input_feedback_sounds_enable_qt(bool flag) {
    sessioniface->call("set_input_feedback_sounds_enable", flag);
}

void SessionDispatcher::set_login_music_enable_qt(bool flag) {
    sessioniface->call("set_login_music_enable", flag);
}

bool SessionDispatcher::get_login_music_enable_qt() {
    QDBusReply<bool> reply = sessioniface->call("get_login_music_enable");
    return reply.value();
}

QString SessionDispatcher::get_sound_theme_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_sound_theme");
    return reply.value();
}

void SessionDispatcher::set_sound_theme_qt(QString theme) {
    sessioniface->call("set_sound_theme", theme);
}

void SessionDispatcher::set_location_replace_pathbar_qt(bool flag) {
    sessioniface->call("set_location_replace_pathbar", flag);
}

bool SessionDispatcher::get_location_replace_pathbar_qt() {
    QDBusReply<bool> reply = sessioniface->call("get_location_replace_pathbar");
    return reply.value();
}

void SessionDispatcher::set_auto_mount_media_qt(bool flag) {
    sessioniface->call("set_auto_mount_media", flag);
}

bool SessionDispatcher::get_auto_mount_media_qt() {
    QDBusReply<bool> reply = sessioniface->call("get_auto_mount_media");
    return reply.value();
}

void SessionDispatcher::set_auto_open_folder_qt(bool flag) {
    sessioniface->call("set_auto_open_folder", flag);
}

bool SessionDispatcher::get_auto_open_folder_qt() {
    QDBusReply<bool> reply = sessioniface->call("get_auto_open_folder");
    return reply.value();
}

void SessionDispatcher::set_prompt_autorun_programs_qt(bool flag) {
    sessioniface->call("set_prompt_autorun_programs", flag);
}

bool SessionDispatcher::get_prompt_autorun_programs_qt() {
    QDBusReply<bool> reply = sessioniface->call("get_prompt_autorun_programs");
    return reply.value();
}

void SessionDispatcher::set_thumbnail_icon_size_qt(int size) {
    sessioniface->call("set_thumbnail_icon_size", size);
}

int SessionDispatcher::get_thumbnail_icon_size_qt() {
    QDBusReply<int> reply = sessioniface->call("get_thumbnail_icon_size");
    return reply.value();
}

void SessionDispatcher::set_thumbnail_cache_time_qt(int value) {
    sessioniface->call("set_thumbnail_cache_time", value);
}

int SessionDispatcher::get_thumbnail_cache_time_qt() {
    QDBusReply<int> reply = sessioniface->call("get_thumbnail_cache_time");
    return reply.value();
}

void SessionDispatcher::set_thumbnail_cache_size_qt(int size) {
    sessioniface->call("set_thumbnail_cache_size", size);
}

int SessionDispatcher::get_thumbnail_cache_size_qt() {
    QDBusReply<int> reply = sessioniface->call("get_thumbnail_cache_size");
    return reply.value();
}

QString SessionDispatcher::access_current_desktop_qt() {
    QDBusReply<QString> reply = sessioniface->call("access_current_desktop");
    return reply.value();
}

QString SessionDispatcher::access_current_machine_qt() {
    QDBusReply<QString> reply = sessioniface->call("access_current_machine");
    return reply.value();
}

//QString SessionDispatcher::judge_desktop_is_unity_qt() {
//    QDBusReply<QString> reply = sessioniface->call("judge_desktop_is_unity");
//    return reply.value();
//}

//QString SessionDispatcher::judge_desktop_is_cinnamon_qt() {
//    QDBusReply<QString> reply = sessioniface->call("judge_desktop_is_cinnamon");
//    return reply.value();
//}
void SessionDispatcher::adjust_screen_gamma_qt(double gamma)
{
    sessioniface->call("adjust_screen_gamma", gamma);
}

double SessionDispatcher::get_screen_gamma_qt()
{
    QDBusReply<double> reply = sessioniface->call("get_screen_gamma");
    return reply.value();
}

QStringList SessionDispatcher::get_idle_delay_list_qt()
{
    QDBusReply<QStringList> reply = sessioniface->call("get_idle_delay_list");
    return reply.value();
}

QString SessionDispatcher::get_current_idle_delay_qt()
{
    QDBusReply<int> reply = sessioniface->call("get_current_idle_delay");
    return QString::number(reply.value());
}

void SessionDispatcher::set_current_idle_delay_qt(int value)
{
    sessioniface->call("set_current_idle_delay", value);
}

bool SessionDispatcher::get_lock_enabled_qt()
{
    QDBusReply<bool> reply = sessioniface->call("get_lock_enabled");
    return reply.value();
}

void SessionDispatcher::set_lock_enabled_qt(bool value)
{
    sessioniface->call("set_lock_enabled", value);
}

QStringList SessionDispatcher::get_lock_delay_list_qt()
{
    QDBusReply<QStringList> reply = sessioniface->call("get_lock_delay_list");
    return reply.value();
}

QString SessionDispatcher::get_current_lock_delay_qt()
{
    QDBusReply<int> reply = sessioniface->call("get_current_lock_delay");
    return QString::number(reply.value());
}

void SessionDispatcher::set_current_lock_delay_qt(int value)
{
    sessioniface->call("set_current_lock_delay", value);
}

QStringList SessionDispatcher::get_sleep_timeout_list_qt()
{
    QDBusReply<QStringList> reply = sessioniface->call("get_sleep_timeout_list");
    return reply.value();
}

QString SessionDispatcher::get_current_critical_low_qt()
{
    QDBusReply<QString> reply = sessioniface->call("get_current_critical_low");
    return reply.value();
}

void SessionDispatcher::set_current_critical_low_qt(QString value)
{
    sessioniface->call("set_current_critical_low", value);
}


QString SessionDispatcher::get_current_lid_battery_qt()
{
    QDBusReply<QString> reply = sessioniface->call("get_current_lid_battery");
    return reply.value();
}

void SessionDispatcher::set_current_lid_battery_qt(QString value)
{
    sessioniface->call("set_current_lid_battery", value);
}

QString SessionDispatcher::get_current_lid_ac_qt()
{
    QDBusReply<QString> reply = sessioniface->call("get_current_lid_ac");
    return reply.value();
}

void SessionDispatcher::set_current_lid_ac_qt(QString value)
{
    sessioniface->call("set_current_lid_ac", value);
}

QString SessionDispatcher::get_current_sleep_timeout_display_battery_qt()
{
    QDBusReply<int> reply = sessioniface->call("get_current_sleep_timeout_display_battery");
    return QString::number(reply.value());
}

void SessionDispatcher::set_current_sleep_timeout_display_battery_qt(int value)
{
    sessioniface->call("set_current_sleep_timeout_display_battery", value);
}

QString SessionDispatcher::get_current_sleep_timeout_display_ac_qt()
{
    QDBusReply<int> reply = sessioniface->call("get_current_sleep_timeout_display_ac");
    return QString::number(reply.value());
}

void SessionDispatcher::set_current_sleep_timeout_display_ac_qt(int value)
{
    sessioniface->call("set_current_sleep_timeout_display_ac", value);
}

QString SessionDispatcher::get_current_sleep_timeout_battery_qt()
{
    QDBusReply<int> reply = sessioniface->call("get_current_sleep_timeout_battery");
    return QString::number(reply.value());
}

void SessionDispatcher::set_current_sleep_timeout_battery_qt(int value)
{
    sessioniface->call("set_current_sleep_timeout_battery", value);
}

QString SessionDispatcher::get_current_sleep_timeout_ac_qt()
{
    QDBusReply<int> reply = sessioniface->call("get_current_sleep_timeout_ac");
    return QString::number(reply.value());
}

void SessionDispatcher::set_current_sleep_timeout_ac_qt(int value)
{
    sessioniface->call("set_current_sleep_timeout_ac", value);
}

QString SessionDispatcher::get_current_launcher_position_qt()
{
    QDBusReply<QString> reply = sessioniface->call("get_current_launcher_position");
    return reply.value();
//    return QString();
}

QStringList SessionDispatcher::get_all_launcher_position_qt()
{
    QDBusReply<QStringList> reply = sessioniface->call("get_all_launcher_position");
    return reply.value();
//    return QStringList();
}

bool SessionDispatcher::set_launcher_position_qt(QString position)
{
    QDBusReply<bool> reply = sessioniface->call("set_launcher_position", position);
    return reply.value();
}

// notify changes
void SessionDispatcher::handler_notify_boolean(QString key, bool value)
{
//    if (key == "home-icon-visible")
//    {
//        qDebug() << "home-icon-visible->" << value;
//    }
//     qDebug() << key;
//     qDebug() << value;
    emit bool_value_notify(key, value);
}

void SessionDispatcher::handler_notify_int(QString key, int value)
{
    emit int_value_notify(key, value);
}

void SessionDispatcher::handler_notify_double(QString key, double value)
{
    emit double_value_notify(key, value);
}

void SessionDispatcher::handler_notify_string(QString key, QString value)
{
//    if (key == "gtk-theme")
//    {
//    }
    emit string_value_notify(key, value);
}

