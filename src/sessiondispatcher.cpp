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
#include "sessiondispatcher.h"
#include <QDebug>
#include <QVariant>
#include <QProcessEnvironment>
#include <QtDBus>
#include <QObject>
#include <QString>
#include "messagedialog.h"
#include "warningdialog.h"
#include <QDesktopWidget>
#include <QDeclarativeContext>
#include <QFontDialog>
#include <QFileDialog>
#include "KThread.h"
#include "wizarddialog.h"
#include "changecitydialog.h"
#include "util.h"
#include "kfontdialog.h"
#include "logindialog.h"

QString selectedFont;
QString selectedFcitxFont;
SessionDispatcher::SessionDispatcher(QObject *parent) :
    QObject(parent)
{
    sessioniface = new QDBusInterface("com.ubuntukylin.session",
                               "/",
                               "com.ubuntukylin.session",
                               QDBusConnection::sessionBus());
    page_num = 0;
    this->mainwindow_width = 850;
    this->mainwindow_height = 600;
    this->alert_width_bg = 329;
    this->alert_width = 329;
    this->alert_height = 195;

    httpauth = new HttpAuth();
    mSettings = new QSettings(YOUKER_COMPANY_SETTING, YOUKER_SETTING_FILE_NAME_SETTING);
    mSettings->setIniCodec("UTF-8");

    //初始化QSetting配置文件
    initConfigFile();

    skin_widget = new SkinsWidget(mSettings);
//    skinCenter = new SkinCenter();
//    connect(skin_widget, SIGNAL(skinSignalToQML(QString)), this, SLOT(handler_change_skin(QString)));

    QObject::connect(sessioniface,SIGNAL(display_scan_process(QString)),this,SLOT(handler_scan_process(QString)));
    QObject::connect(sessioniface,SIGNAL(scan_complete(QString)),this,SLOT(handler_scan_complete(QString)));
    QObject::connect(sessioniface, SIGNAL(access_weather(QString, QString)), this, SLOT(handler_access_forecast_weather(QString, QString)));
    QObject::connect(sessioniface,SIGNAL(total_data_transmit(QString, QString)),this,SLOT(handler_total_data_transmit(QString,QString)));

    //Apt and Soft center cache
    QObject::connect(sessioniface, SIGNAL(data_transmit_by_cache(QString, QString, QString, QString)), this, SLOT(handler_append_cache_data_to_model(QString,QString,QString,QString)));
    QObject::connect(sessioniface, SIGNAL(cache_transmit_complete(QString)), this, SLOT(handler_cache_scan_over(QString)));

    //Uninstall unneed package and old kernel package
    QObject::connect(sessioniface, SIGNAL(data_transmit_by_package(QString, QString, QString, QString)), this, SLOT(handler_append_package_data_to_model(QString,QString,QString,QString)));
    QObject::connect(sessioniface, SIGNAL(package_transmit_complete()), this, SLOT(handler_package_scan_over()));

    //Largest file
//    QObject::connect(sessioniface, SIGNAL(data_transmit_by_large(QString, QString)), this, SLOT(handler_append_largest_file_to_model(QString,QString)));
//    QObject::connect(sessioniface, SIGNAL(large_transmit_complete()), this, SLOT(handler_largest_scan_over()));

    //cookies
    QObject::connect(sessioniface, SIGNAL(data_transmit_by_cookies(QString, QString, QString)), this, SLOT(handler_append_cookies_to_model(QString,QString,QString)));
    QObject::connect(sessioniface, SIGNAL(cookies_transmit_complete(QString)), this, SLOT(handler_cookies_scan_over(QString)));

    QObject::connect(httpauth, SIGNAL(response(/*QString,QString,*/QString)), this, SLOT(handler_access_login_success_info(/*QString,QString,*/QString)));
    QObject::connect(httpauth, SIGNAL(error(int)), this, SLOT(handler_access_login_failed_info(int)));
    QObject::connect(httpauth, SIGNAL(insertDataToServer(QString)), this, SLOT(handler_insert_data_to_server(QString)));
    QObject::connect(httpauth, SIGNAL(updateServerData(QString)), this, SLOT(handler_update_server_data(QString)));
}

SessionDispatcher::~SessionDispatcher() {
    mSettings->sync();
    if (mSettings != NULL)
        delete mSettings;
    this->exit_qt();
}

void SessionDispatcher::exit_qt() {
    sessioniface->call("exit");
}

void SessionDispatcher::show_slider_qt() {
    sessioniface->call("display_slide_show");
}

QString SessionDispatcher::get_currrent_date_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_currrent_date");
    return reply.value();
}

QString SessionDispatcher::get_current_time_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_current_time");
    return reply.value();
}

int SessionDispatcher::login_in_forum_account_qt() {
    //得到是否是当天第一次启动的标记
    mSettings->beginGroup("account");
    bool flag = mSettings->value("firststart").toBool();
    //得到配置文件中的日期
    QString org_date = mSettings->value("date").toString();
    mSettings->endGroup();
    mSettings->sync();
    qDebug() << "confile data->";
//    qDebug() << flag;
    qDebug() << org_date;
    QDBusReply<int> reply = sessioniface->call("login_in_forum_account", flag, org_date);
    qDebug() << "my login score->";
    qDebug() << reply.value();
    return reply.value();
}

void SessionDispatcher::handler_write_user_info_when_exit() {//更新数据库数据和本地配置文件
    //更新本地配置文件
    mSettings->beginGroup("account");
    QString org_date = mSettings->value("date").toString();
    QString current_date = this->get_currrent_date_qt();
    mSettings->setValue("date", current_date);
    if(org_date == current_date) {
        mSettings->setValue("firststart", "false");
    }
    mSettings->endGroup();
    mSettings->sync();
    //更新数据库数据
//    int num = 1;
//    int myscore = this->login_in_forum_account_qt();
//    QString requestData = QString("http://210.209.123.136/yk/find_get.php?pp[type]=update&pp[table]=yk_member&pp[dnumber]=%1&pp[id]=%2&pp[0]=score&score=%3").arg(num).arg(id).arg(myscore);
//    QUrl url(requestData);
//    qDebug () << requestData;
//    httpauth->sendGetRequest(url);
    qDebug() << "kobe222";
    emit this->ready_to_exit();
}

void SessionDispatcher::handler_access_user_password(QString user, QString pwd) {
    username = user;
    //显示登录动态图
    emit showLoginAnimatedImage();
    //发送数据给服务端进行登录验证
    QString requestData = QString("%1%2%3%4").arg("name=").arg(user).arg("&password=").arg(pwd);
    QUrl url("http://210.209.123.136/box/find.php");
    QByteArray postData;
    postData.append(requestData);
    httpauth->sendPostRequest(url, postData);


//    QString requestData = QString("%1%2%3%4%5").arg("username=").arg(user).arg("&password=").arg(pwd).arg("&hiddenFields=ifAny");
//    QUrl url("http://210.209.123.136/box/find.php");
//    QByteArray postData;
//    postData.append(requestData);
//    httpauth->sendPostRequest(url, postData);
}

void SessionDispatcher::login_ubuntukylin_account(int window_x, int window_y) {
    LoginDialog *logindialog = new LoginDialog();
    QObject::connect(logindialog, SIGNAL(translate_user_password(QString,QString)),this, SLOT(handler_access_user_password(QString,QString)));
    this->alert_x = window_x + (mainwindow_width / 2) - (alert_width_bg  / 2);
    this->alert_y = window_y + mainwindow_height - 400;
    logindialog->move(this->alert_x, this->alert_y);
    logindialog->show();
}

void SessionDispatcher::handler_access_login_success_info(/*QString username, QString password, */QString score) {
    //登录成功后将用户信息显示在界面上
    emit updateLoginStatus(username, /*password, */score);
//    QString data_type;
//    int num = 0;
//    num = 8;//3;
//    data_type= "insert";
//    int id = 24;
//    QString logo = "lixiang-kobe";
//    int level = 2;
//    int myscore = 3000;//2000;
//    bool isfirststart = true;//false;
//    int lastlogintime = 200;
//    int lastlogouttime = 400;
//    int holdtime = 200;

    //post
//    QString requestData = QString("pp[type]=%1&pp[table]=yk_member&pp[dnumber]=%2&pp[id]=%3&pp[logo]=%4&pp[level]=%5&pp[score]=%6&pp[isfirststart]=%7&pp[lastlogintime]=%8&pp[lastlogouttime]=%9&pp[holdtime]=%10").arg(data_type).arg(num).arg(id).arg(logo).arg(level).arg(myscore).arg(isfirststart).arg(lastlogintime).arg(lastlogouttime).arg(holdtime);
//    QUrl url("http://210.209.123.136/yk/find_post.php");
//    qDebug () << requestData;
//    QByteArray postData;
//    postData.append(requestData);
//    httpauth->sendPostRequest(url, postData);

    //get
    //search
    QString requestData = QString("http://210.209.123.136/yk/find_get.php?pp[type]=find&pp[table]=yk_member&pp[id]=2");
//    QString requestData = QString("http://210.209.123.136/yk/find_get.php?pp[type]=find&pp[table]=yk_member&pp[id]=%1").arg(id);
    //insert
//    QString requestData = QString("http://210.209.123.136/yk/find_get.php?pp[type]=%1&pp[table]=yk_member&pp[dnumber]=%2&pp[id]=%3&pp[logo]=\"%4\"&pp[level]=%5&pp[score]=%6&pp[isfirststart]=%7&pp[lastlogintime]=%8&pp[lastlogouttime]=%9&pp[holdtime]=%10").arg(data_type).arg(num).arg(id).arg(logo).arg(level).arg(myscore).arg(isfirststart).arg(lastlogintime).arg(lastlogouttime).arg(holdtime);
    //update
    //    QString requestData = QString("http://210.209.123.136/yk/find_get.php?pp[type]=%1&pp[table]=yk_member&pp[dnumber]=%2&pp[id]=%3&pp[0]=logo&pp[1]=score&pp[2]=isfirststart&logo=\"%4\"&score=%5&isfirststart=%6").arg("update").arg(num).arg(id).arg(logo).arg(myscore).arg(isfirststart);
    QUrl url(requestData);
//    qDebug () << requestData;
    httpauth->sendGetRequest(url);
}

void SessionDispatcher::handler_access_login_failed_info(int status) {
    emit loginFailedStatus(status);
}

void SessionDispatcher::handler_insert_data_to_server(QString data) {//插入数据到服务端数据库
    qDebug() << "insert->";
    qDebug() << data;
    //insert
//    int id = 24;
//    QString logo = "lixiang-kobe";
//    int level = 2;
//    int myscore = 3000;//2000;
//    bool isfirststart = true;//false;
//    int lastlogintime = 200;
//    int lastlogouttime = 400;
//    int holdtime = 200;
//    QString requestData = QString("http://210.209.123.136/yk/find_get.php?pp[type]=insert&pp[table]=yk_member&pp[dnumber]=8&pp[id]=%1&pp[logo]=\"%2\"&pp[level]=%3&pp[score]=%4&pp[isfirststart]=%5&pp[lastlogintime]=%6&pp[lastlogouttime]=%7&pp[holdtime]=%8").arg(id).arg(logo).arg(level).arg(myscore).arg(isfirststart).arg(lastlogintime).arg(lastlogouttime).arg(holdtime);
//    QUrl url(requestData);
////    qDebug () << requestData;
//    httpauth->sendGetRequest(url);
}

void SessionDispatcher::handler_update_server_data(QString data) {//更系服务端数据库的数据
    qDebug() << "update->";
    qDebug() << data;//"id=2,logo=lixiang-kobe,level=3,score=3000,isfirststart=0,lastlogintime=0000-00-00 00:00:00,lastlogouttime=0000-00-00 00:00:00,holdtime=8"
    //update
    QStringList updateData = data.split(",");
    QStringList idData = updateData.at(0).split("=");
    int id = idData.at(1).toInt();
    QStringList scoreData = updateData.at(3).split("=");
//    QString logo = "lixiang-kobe";
    int login_score = this->login_in_forum_account_qt();
    bool isfirststart = false;
    if(login_score == 5) {//是当天的第一次登录
        isfirststart = true;
    }
    QString tmp_time = this->get_current_time_qt();
    qDebug() << "-------------------";
    qDebug() << tmp_time;
    int myscore = login_score + scoreData.at(1).toInt();
//    QString requestData = QString("http://210.209.123.136/yk/find_get.php?pp[type]=update&pp[table]=yk_member&pp[dnumber]=3&pp[id]=%1&pp[0]=logo&pp[1]=score&pp[2]=isfirststart&logo=\"%2\"&score=%3&isfirststart=%4").arg(id).arg(logo).arg(myscore).arg(isfirststart);
    QString requestData = QString("http://210.209.123.136/yk/find_get.php?pp[type]=update&pp[table]=yk_member&pp[dnumber]=3&pp[id]=%1&pp[0]=score&pp[1]=isfirststart&pp[2]=lastlogintime&score=%2&isfirststart=%3&lastlogintime=%4").arg(id).arg(myscore).arg(isfirststart).arg(tmp_time);
    QUrl url(requestData);
////    qDebug () << requestData;
    httpauth->sendGetRequest(url);
}

QStringList SessionDispatcher::search_city_names_qt(QString search_name) {
    QDBusReply<QStringList> reply = sessioniface->call("search_city_names", search_name);
    return reply.value();
}

QStringList SessionDispatcher::get_geonameid_list_qt() {
    QDBusReply<QStringList> reply = sessioniface->call("get_geonameid_list");
    return reply.value();
}

QStringList SessionDispatcher::get_longitude_list_qt() {
    QDBusReply<QStringList> reply = sessioniface->call("get_longitude_list");
    return reply.value();
}

QStringList SessionDispatcher::get_latitude_list_qt() {
    QDBusReply<QStringList> reply = sessioniface->call("get_latitude_list");
    return reply.value();
}

QString SessionDispatcher::get_yahoo_city_id_qt(QString geonameid) {
    QDBusReply<QString> reply = sessioniface->call("get_yahoo_city_id", geonameid);
//    qDebug() << "new id->";
//    qDebug() << reply.value();
    return reply.value();
}

void SessionDispatcher::handler_access_forecast_weather(QString key, QString value) {
    if(key == "forecast" && value == "kobe") {
        get_forecast_dict_qt();
        emit startUpdateForecastWeahter("forecast");
    }
    else if(key == "weather" && value == "kobe") {
        get_current_weather_dict_qt();
        emit startUpdateForecastWeahter("weather");
    }
    else if(key == "pm25" && value == "kobe") {
        get_pm25_str_qt();
        emit startUpdateForecastWeahter("pm25");
    }
    else if(key == "yahoo" && value == "kobe") {
        get_current_yahoo_weather_dict_qt();
        emit startUpdateForecastWeahter("yahoo");
    }
}

void SessionDispatcher::handler_append_cache_data_to_model(QString flag, QString path, QString fileFlag, QString sizeValue) {
    emit appendContentToCacheModel(flag, path, fileFlag, sizeValue);
}

void SessionDispatcher::handler_cache_scan_over(QString flag) {
    emit tellQMLCaheOver(flag);
}

void SessionDispatcher::handler_append_package_data_to_model(QString flag, QString pkgName, QString description, QString sizeValue) {
    emit appendPackageContentToCacheModel(flag, pkgName, description, sizeValue);
}

void SessionDispatcher::handler_package_scan_over() {
    emit tellQMLPackageOver();
}

void SessionDispatcher::handler_append_largest_file_to_model(QString sizeValue, QString path) {
    emit appendLargestContentToModel(sizeValue, path);
}

void SessionDispatcher::handler_largest_scan_over() {
    emit tellQMLLargestOver();
}

void SessionDispatcher::handler_append_cookies_to_model(QString flag, QString domain, QString num) {
    emit appendCookiesContentToModel(flag, domain, num);
}

void SessionDispatcher::handler_cookies_scan_over(QString cookiesFlag) {
    emit tellQMLCookiesOver(cookiesFlag);
}

void SessionDispatcher::handler_scan_complete(QString msg) {
    emit finishScanWork(msg);
}

void SessionDispatcher::handler_scan_process(QString msg) {
    emit isScanning(msg);
}

void SessionDispatcher::handler_total_data_transmit(QString flag, QString msg) {
    emit tellScanResultToQML(flag, msg);
}

QString SessionDispatcher::get_locale_version() {
    QString locale = QLocale::system().name();
    return locale;
}

void SessionDispatcher::onekey_scan_function_qt(QStringList selectedList) {
    sessioniface->call("onekey_scan_function", selectedList);
}


int SessionDispatcher::scan_history_records_qt(QString flag) {
    QDBusReply<int> reply = sessioniface->call("history_scan_funciton", flag);
    return reply.value();
}

int SessionDispatcher::scan_system_history_qt() {
    QDBusReply<int> reply = sessioniface->call("scan_system_history");
    return reply.value();
}

int SessionDispatcher::scan_dash_history_qt() {
    QDBusReply<int> reply = sessioniface->call("scan_dash_history");
    return reply.value();
}

QStringList SessionDispatcher::scan_of_same_qt(QString abspath) {
    QDBusReply<QStringList> reply = sessioniface->call("scan_of_same", abspath);
    return reply.value();
}

QStringList SessionDispatcher::scan_of_large_qt(int size, QString abspath) {
    QDBusReply<QStringList> reply = sessioniface->call("scan_of_large", size, abspath);//large_scan_function
    return reply.value();
}

QStringList SessionDispatcher::scan_cookies_records_qt() {
    QDBusReply<QStringList> reply = sessioniface->call("scan_cookies_records");
    return reply.value();
}

void SessionDispatcher::cookies_scan_function_qt(QString flag) {
//    QDBusReply<QStringList> reply = sessioniface->call("scan_cookies_function", flag);//cookies_scan_function
//    return reply.value();
    sessioniface->call("scan_cookies_function", flag);
}

QStringList SessionDispatcher::scan_unneed_packages_qt() {
    QDBusReply<QStringList> reply = sessioniface->call("scan_unneed_packages");
    return reply.value();
}

QStringList SessionDispatcher::scan_apt_cruft_qt() {
    QDBusReply<QStringList> reply = sessioniface->call("scan_apt_cruft");
    return reply.value();
}

QStringList SessionDispatcher::scan_softwarecenter_cruft_qt() {
    QDBusReply<QStringList> reply = sessioniface->call("scan_softwarecenter_cruft");
    return reply.value();
}

QStringList SessionDispatcher::get_cache_arglist(int i) {
    QStringList tmp;
    if(i == 0) {
        tmp << "apt" << "software-center" << "thumbnails";
    }
    else if(i == 4) {
        tmp << "apt" << "software-center";
    }
    else if(i == 5) {
        tmp << "apt" << "thumbnails";
    }
    else if(i == 6) {
        tmp << "software-center" << "thumbnails";
    }
    return tmp;
}

QStringList SessionDispatcher::get_browser_cache_arglist() {
    QStringList tmp;
    tmp << "firefox" << "chromium";
    return tmp;
}

QStringList SessionDispatcher::get_package_arglist(int i) {
    QStringList tmp;
    if(i == 0) {
        tmp << "unneed" << "oldkernel" << "configfile";
    }
    else if(i == 4) {
        tmp << "unneed" << "oldkernel";
    }
    else if(i == 5) {
        tmp << "unneed" << "configfile";
    }
    else if(i == 6) {
        tmp << "oldkernel" << "configfile";
    }
//    tmp << "unneed" << "oldkernel";
    return tmp;
}

void SessionDispatcher::cache_scan_function_qt(QStringList argList, QString flag) {
    sessioniface->call("cache_scan_function", argList, flag);
}

void SessionDispatcher::package_scan_function_qt(QStringList argList) {
    sessioniface->call("package_scan_function", argList);
}

QStringList SessionDispatcher::scan_oldkernel_packages_qt() {
    QDBusReply<QStringList> reply = sessioniface->call("oldkernel_scan_function");
    return reply.value();
}

QString SessionDispatcher::getHomePath() {
    QString homepath = QDir::homePath();
    return homepath;
}

void SessionDispatcher::set_page_num(int num) {
    page_num = num;
}

int SessionDispatcher::get_page_num() {
    return page_num;
}

QString SessionDispatcher::get_session_daemon_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_session_daemon");
    return reply.value();
}

void SessionDispatcher::get_system_message_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = sessioniface->call("get_system_message");
    if (reply.isValid()) {
        QMap<QString, QVariant> value = reply.value();
        systemInfo = value;
        //把当前登录的用户名存放到QSetting配置文件中，方便任务管理器使用
        mSettings->beginGroup("user");
        mSettings->setValue("currentName", systemInfo["currrent_user"].toString());
        mSettings->endGroup();
        mSettings->sync();
    }
    else {
        qDebug() << "get pc_message failed!";
    }
}

//把优客助手运行时，系统的默认配置写到配置文件
void SessionDispatcher::write_default_configure_to_qsetting_file(QString key, QString name, QString value) {
    mSettings->beginGroup(key);
    mSettings->setValue(name, value);
    mSettings->endGroup();
    mSettings->sync();
}

//从Qsetting配置文件中读取系统启动时的默认配置
QString SessionDispatcher::read_default_configure_from_qsetting_file(QString key, QString name) {
    QString result;
    mSettings->beginGroup(key);
    result = mSettings->value(name).toString();
    mSettings->endGroup();
    mSettings->sync();
    return result;
}

//----------------message dialog--------------------
void SessionDispatcher::showFeatureDialog(int window_x, int window_y) {
    MessageDialog *dialog = new MessageDialog();
    this->alert_x = window_x + (mainwindow_width / 2) - (alert_width  / 2);
    this->alert_y = window_y + mainwindow_height - 400;
    dialog->move(this->alert_x, this->alert_y);
//    dialog->move ((QApplication::desktop()->width() - dialog->width())/2,(QApplication::desktop()->height() - dialog->height())/2);
    dialog->show();
}

//----------------checkscreen dialog--------------------
void SessionDispatcher::showCheckscreenDialog(int window_x, int window_y) {
    ModalDialog *dialog = new ModalDialog;
    this->alert_x = window_x + (mainwindow_width / 2) - (alert_width  / 2);
    this->alert_y = window_y + mainwindow_height - 400;
    dialog->move(this->alert_x, this->alert_y);
    dialog->setModal(true);
    dialog->show();
}

void SessionDispatcher::showWarningDialog(QString title, QString content, int window_x, int window_y) {
    WarningDialog *dialog = new WarningDialog(title, content);
    this->alert_x = window_x + (mainwindow_width / 2) - (alert_width  / 2);
    this->alert_y = window_y + mainwindow_height - 400;
    dialog->move(this->alert_x, this->alert_y);
    dialog->exec();
//    dialog->setModal(true);
//    dialog->show();
}

QString SessionDispatcher::getSingleInfo(QString key) {
    QVariant info = systemInfo.value(key);
    return info.toString();
}

/*-----------------------------desktop of beauty-----------------------------*/
bool SessionDispatcher::set_show_desktop_icons_qt(bool flag) {
    QDBusReply<bool> reply = sessioniface->call("set_show_desktop_icons", flag);
    return reply.value();
}

bool SessionDispatcher::get_show_desktop_icons_qt() {
    QDBusReply<bool> reply = sessioniface->call("get_show_desktop_icons");
    return reply.value();
}

bool SessionDispatcher::set_show_homefolder_qt(bool flag) {
    QDBusReply<bool> reply = sessioniface->call("set_show_homefolder", flag);
    return reply.value();
}

bool SessionDispatcher::get_show_homefolder_qt() {
    QDBusReply<bool> reply = sessioniface->call("get_show_homefolder");
    return reply.value();
}
bool SessionDispatcher::set_show_network_qt(bool flag) {
    QDBusReply<bool> reply = sessioniface->call("set_show_network", flag);
    return reply.value();
}

bool SessionDispatcher::get_show_network_qt() {
    QDBusReply<bool> reply = sessioniface->call("get_show_network");
    return reply.value();
}
bool SessionDispatcher::set_show_trash_qt(bool flag) {
    QDBusReply<bool> reply = sessioniface->call("set_show_trash", flag);
    return reply.value();
}

bool SessionDispatcher::get_show_trash_qt() {
    QDBusReply<bool> reply = sessioniface->call("get_show_trash");
    return reply.value();
}
bool SessionDispatcher::set_show_devices_qt(bool flag) {
    QDBusReply<bool> reply = sessioniface->call("set_show_devices", flag);
    return reply.value();
}

bool SessionDispatcher::get_show_devices_qt() {
    QDBusReply<bool> reply = sessioniface->call("get_show_devices");
    return reply.value();
}

/*-----------------------------unity of beauty-----------------------------*/
bool SessionDispatcher::set_launcher_autohide_qt(bool flag) {
    QDBusReply<bool> reply = sessioniface->call("set_launcher_autohide", flag);
    return reply.value();
}

bool SessionDispatcher::get_launcher_autohide_qt() {
    QDBusReply<bool> reply = sessioniface->call("get_launcher_autohide");
    return reply.value();
}

bool SessionDispatcher::set_launcher_icon_size_qt(int num) {
    QDBusReply<bool> reply = sessioniface->call("set_launcher_icon_size", num);
    return reply.value();
}

int SessionDispatcher::get_launcher_icon_size_qt() {
    QDBusReply<int> reply = sessioniface->call("get_launcher_icon_size");
    return reply.value();
}
bool SessionDispatcher::set_launcher_have_showdesktopicon_qt(bool flag) {
    QDBusReply<bool> reply = sessioniface->call("set_launcher_have_showdesktopicon", flag);
    return reply.value();
}

bool SessionDispatcher::get_launcher_have_showdesktopicon_qt() {
    QDBusReply<bool> reply = sessioniface->call("get_launcher_have_showdesktopicon");
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

/*-----------------------------font of beauty-----------------------------*/
QString SessionDispatcher::get_font_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_font");
    return reply.value();
}

bool SessionDispatcher::set_font_qt_default(QString font) {
    QDBusReply<bool> reply = sessioniface->call("set_font", font);
    return reply.value();
}

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

bool SessionDispatcher::set_document_font_qt_default(QString font) {
    QDBusReply<bool> reply = sessioniface->call("set_document_font", font);
    return reply.value();
}

bool SessionDispatcher::set_document_font_qt(QString font) {
    QDBusReply<bool> reply = sessioniface->call("set_document_font", font);
    return reply.value();
}

QString SessionDispatcher::get_monospace_font_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_monospace_font");
    return reply.value();
}

bool SessionDispatcher::set_monospace_font_qt_default(QString font) {
    QDBusReply<bool> reply = sessioniface->call("set_monospace_font", font);
    return reply.value();
}

bool SessionDispatcher::set_monospace_font_qt(QString font) {
    QDBusReply<bool> reply = sessioniface->call("set_monospace_font", font);
    return reply.value();
}

QString SessionDispatcher::get_window_title_font_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_window_title_font");
    return reply.value();
}

bool SessionDispatcher::set_window_title_font_qt_default(QString font) {
    QDBusReply<bool> reply = sessioniface->call("set_window_title_font", font);
    return reply.value();
}

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

void SessionDispatcher::restore_default_font_signal(QString flag) {
    emit notifyFontStyleToQML(flag); //font_style
}

QString SessionDispatcher::getSelectedFcitxFont() {
     return selectedFcitxFont;//
}

void SessionDispatcher::show_font_dialog(QString flag) {
    KFontDialog *fontDialog = new KFontDialog(mSettings, flag, 0);
    fontDialog->exec();
    if(!selectedFont.isEmpty()) {
        if(flag == "font") {
            set_font_qt(selectedFont);//set font
        }
        else if(flag == "desktopfont") {
            set_desktop_font_qt(selectedFont);//set desktopfont
        }
        else if(flag == "monospacefont") {
            set_monospace_font_qt(selectedFont);//set monospacefont
        }
        else if(flag == "documentfont") {
            set_document_font_qt(selectedFont);//set documentfont
        }
        else if(flag == "titlebarfont") {
            set_window_title_font_qt(selectedFont);//set titlebarfont
        }
        else if(flag == "fcitxfont")
        {

        }
        selectedFont.clear();
        emit notifyFontStyleToQML(flag); //font_style
    }
//    bool ok;
//    const QFont& font = QFontDialog::getFont(&ok, 0);
//    if(ok) {
//        QString fontsize = QString("%1").arg(font.pointSize());
//        QString fontstyle = font.family() + " " +  font.styleName() + " " + fontsize;
//        if(flag == "font")
//            set_font_qt(fontstyle);//set font
//        else if(flag == "desktopfont")
//            set_desktop_font_qt(fontstyle);//set desktopfont
//        else if(flag == "monospacefont")
//            set_monospace_font_qt(fontstyle);//set monospacefont
//        else if(flag == "documentfont")
//            set_document_font_qt(fontstyle);//set documentfont
//        else if(flag == "titlebarfont")
//            set_window_title_font_qt(fontstyle);//set titlebarfont
//        emit notifyFontStyleToQML(flag); //font_style
//    }
}

QString SessionDispatcher::show_folder_dialog() {
    //选择文件夹
    QString dir = QFileDialog::getExistingDirectory(0, tr("Select folder"), QDir::homePath(),
                                                    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    return dir;
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

/*-----------------------------window of beauty-----------------------------*/
bool SessionDispatcher::set_window_button_align_left_qt() {
    QDBusReply<bool> reply = sessioniface->call("set_window_button_align_left");
    return reply.value();
}

bool SessionDispatcher::set_window_button_align_right_qt() {
    QDBusReply<bool> reply = sessioniface->call("set_window_button_align_right");
    return reply.value();
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

/*-----------------------------sound of beauty-----------------------------*/
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

//-----------------------monitorball------------------------
double SessionDispatcher::get_cpu_percent_qt() {
    QDBusReply<double> reply = sessioniface->call("get_cpu_percent");
    return reply.value();
}

QString SessionDispatcher::get_total_memory_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_total_memory");
    return reply.value();
}

QString SessionDispatcher::get_used_memory_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_used_memory");
    return reply.value();
}

QString SessionDispatcher::get_free_memory_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_free_memory");
    return reply.value();
}

QStringList SessionDispatcher::get_network_flow_total_qt() {
    QDBusReply<QStringList> reply = sessioniface->call("get_network_flow_total");
    return reply.value();
}

//-----------------------change skin------------------------
void SessionDispatcher::handler_change_skin(QString skinName) {
    //将得到的更换皮肤名字写入配置文件中
    mSettings->setValue("skin/background", skinName);
    mSettings->sync();
//    //发送开始更换QML界面皮肤的信号
    emit startChangeQMLSkin(skinName);
}

QString SessionDispatcher::setSkin() {
    QString skinName;
    mSettings->beginGroup("skin");
    skinName = mSettings->value("background").toString();
    if(skinName.isEmpty()) {
        skinName = QString("0_bg");
        mSettings->setValue("background", skinName);
    }
    mSettings->endGroup();
    mSettings->sync();
    return skinName;
}

void SessionDispatcher::showSkinWidget() {
    skin_widget->show();
}

//void SessionDispatcher::showSkinCenter() {
//    skinCenter->show();
//}

void SessionDispatcher::get_forecast_weahter_qt() {
    getCityIdInfo();

//    QStringList tmplist;
//    tmplist << "Kobe" << "Lee";
//    KThread *thread = new KThread(tmplist, sessioniface, "get_forecast_weahter", initCityId);
//    thread->start();

    bool flag = Util::id_exists_in_location_file(initCityId);
    if(flag) {//获取中国气象局数据
        QStringList tmplist;
        tmplist << "Kobe" << "Lee";
        KThread *thread = new KThread(tmplist, sessioniface, "get_forecast_weahter", initCityId);
        thread->start();
    }
    else {
        get_yahoo_forecast_dict_qt();
        emit startUpdateForecastWeahter("yahooforecast");
    }

//    QDBusReply<QMap<QString, QVariant> > reply = sessioniface->call("get_forecast_weahter", initCityId);
//    forecastInfo = reply.value();
}

void SessionDispatcher::get_forecast_dict_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = sessioniface->call("get_forecast_dict");
    forecastInfo = reply.value();
}

void SessionDispatcher::get_yahoo_forecast_dict_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = sessioniface->call("get_yahoo_forecast_dict");
    yahooforecastInfo = reply.value();
}

/*bool*/void SessionDispatcher::get_current_weather_qt() {
    getCityIdInfo();
//    qDebug() << initCityId;
    QStringList tmplist;
    tmplist << "Kobe" << "Lee";
//0.3.3
    bool flag = Util::id_exists_in_location_file(initCityId);
    if(flag) {//获取中国气象局数据
//        sessioniface->call("get_current_weather", initCityId);
//        qDebug() << initCityId;
        KThread *thread = new KThread(tmplist, sessioniface, "get_current_weather", initCityId);
        thread->start();
    }
    else {//获取雅虎气象数据
        QStringList latlon = this->getLatandLon(initCityId);
//        qDebug() << latlon;
//        qDebug() << initCityId;
//        sessioniface->call("get_current_yahoo_weather", latlon, initCityId);
        KThread *thread = new KThread(latlon, sessioniface, "get_current_yahoo_weather", initCityId);
        thread->start();
    }

//    QDBusReply<QMap<QString, QVariant> > reply = sessioniface->call("get_current_weather", initCityId);
//    currentInfo = reply.value();
//    if(currentInfo.isEmpty()) {
//        return false;
//    }
//    else {
//        return true;
//    }
}

void SessionDispatcher::get_current_weather_dict_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = sessioniface->call("get_current_weather_dict");
    currentInfo = reply.value();
}

void SessionDispatcher::get_current_yahoo_weather_dict_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = sessioniface->call("get_current_yahoo_weather_dict");
    yahoocurrentInfo = reply.value();
//    qDebug() << "yahoo data->";
//    qDebug() << yahoocurrentInfo;
}

//QString SessionDispatcher::get_current_pm25_qt() {
//    getCityIdInfo();
//    QDBusReply<QString> reply = sessioniface->call("get_current_pm25", initCityId);
//    return reply.value();
//}

void SessionDispatcher::get_current_pm25_qt() {
    getCityIdInfo();
    QStringList tmplist;
    tmplist << "Kobe" << "Lee";
    KThread *thread = new KThread(tmplist, sessioniface, "get_current_pm25", initCityId);
    thread->start();

//    QDBusReply<QString> reply = sessioniface->call("get_current_pm25", initCityId);
//    return reply.value();
}

void SessionDispatcher::get_pm25_str_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_pm25_str");
    pm25Info = reply.value();
}

QString SessionDispatcher::access_pm25_str_qt() {
    return pm25Info;
}

int SessionDispatcher::get_current_rate() {
    mSettings->beginGroup("weather");
    int rate = 60;
    rate = mSettings->value("rate").toInt();
    mSettings->endGroup();
    mSettings->sync();
    return rate;
}

bool SessionDispatcher::update_weather_data_qt() {
    getCityIdInfo();
    bool flag = Util::id_exists_in_location_file(initCityId);
    if(flag) {//获取中国气象局数据
        QDBusReply<bool> reply = sessioniface->call("update_weather_data", initCityId);
        return reply.value();
    }
    else {
        QStringList latlon = this->getLatandLon(initCityId);
        KThread *thread = new KThread(latlon, sessioniface, "get_current_yahoo_weather", initCityId);
        thread->start();
        return false;
    }

//    QDBusReply<bool> reply = sessioniface->call("update_weather_data", initCityId);
//    return reply.value();
}

void SessionDispatcher::update_forecast_weather() {
//    emit startUpdateForecastWeahter();
}

void SessionDispatcher::change_select_city_name_qt(QString cityName) {
    sessioniface->call("change_select_city_name", cityName);
}

QString SessionDispatcher::getSingleWeatherInfo(QString key, QString flag) {
    QVariant info = "";
    if(flag == "forecast") {
        info = forecastInfo.value(key);
    }
    else if(flag == "current") {
        info = currentInfo.value(key);
    }
    else if(flag == "weathericon") {
        info = "../../img/weather/" + key;
    }
    else if(flag == "yahoo") {
        info = yahoocurrentInfo.value(key);
    }
    else if(flag == "yahooforecast") {
        info = yahooforecastInfo.value(key);
    }
    return info.toString();
}

bool SessionDispatcher::showWizardController() {
    WizardDialog *wizardDialog = new WizardDialog(mSettings, 0);
    connect(wizardDialog, SIGNAL(readyToUpdateRateTime(int)), this, SLOT(handler_change_rate(int)));
    connect(wizardDialog, SIGNAL(readyToUpdateWeatherForWizard()), this, SLOT(handler_change_city()));
    wizardDialog-> QWidget::setAttribute(Qt::WA_DeleteOnClose);
    if(wizardDialog->exec()==QDialog::Rejected) {
        return false;
    }
    else {
        return true;
    }
}

void SessionDispatcher::handler_change_rate(int rate) {
    emit startUpdateRateTime(rate);
}

bool SessionDispatcher::showChangeCityDialog() {
    ChangeCityDialog *cityDialog = new ChangeCityDialog(mSettings);
    cityDialog-> QWidget::setAttribute(Qt::WA_DeleteOnClose);
    connect(cityDialog, SIGNAL(readyToUpdateWeather()), this, SLOT(handler_change_city()));
    if(cityDialog->exec()==QDialog::Rejected) {
        return false;
    }
    else {
        return true;
    }
}

void SessionDispatcher::handler_change_city() {
    emit startChangeQMLCity();
}

int SessionDispatcher::getLengthOfCityList() {
    mSettings->beginGroup("weather");
    QStringList cityList = mSettings->value("places").toStringList();
    mSettings->endGroup();
    mSettings->sync();
    return cityList.size();
}

void SessionDispatcher::initConfigFile() {
    mSettings->beginGroup("account");
    QString firststart = mSettings->value("firststart").toString();
//    qDebug() << "--------------";

    if(firststart.isEmpty()) {
//        qDebug() << "11111";
        firststart = "true";
        mSettings->setValue("firststart", firststart);
    }
//    else {
//        qDebug() << "2222222";
//        qDebug() << firststart;
//    }
    QString current_date = mSettings->value("date").toString();
    if(current_date.isEmpty()) {
        current_date = this->get_currrent_date_qt();
        mSettings->setValue("date", current_date);
    }
    mSettings->endGroup();
    mSettings->sync();

    mSettings->beginGroup("weather");
    QString cityId = mSettings->value("cityId").toString();
    //cityId为空时，赋默认值为：101250101
    if(cityId.isEmpty()) {
        cityId = QString("101250101");
        mSettings->setValue("cityId", cityId);
    }
    QStringList idList = mSettings->value("idList").toStringList();
    if(idList.isEmpty()) {
        idList.append("101250101");
        idList.append("101010100");
        idList.append("101020100");
        mSettings->setValue("idList", idList);
    }
    QStringList places = mSettings->value("places").toStringList();
    //places为空时，赋默认值为：湖南,长沙,长沙
    if(places.isEmpty()) {
//        places = QStringList("湖南,长沙,长沙");
        places.append("湖南,长沙,长沙");
        places.append("北京,北京,北京");
        places.append("上海,上海,上海");
        mSettings->setValue("places", places);
    }
    //纬度
    QStringList latitude = mSettings->value("latitude").toStringList();
    if(latitude.isEmpty()) {
        latitude.append("NA");
        latitude.append("NA");
        latitude.append("NA");
        mSettings->setValue("latitude", latitude);
    }
    //经度
    QStringList longitude = mSettings->value("longitude").toStringList();
    if(longitude.isEmpty()) {
        longitude.append("NA");
        longitude.append("NA");
        longitude.append("NA");
        mSettings->setValue("longitude", longitude);
    }
    QString rate = mSettings->value("rate").toString();
    //rate为空时，赋默认值为：60
    if(rate.isEmpty()) {
        rate = QString("60");
        mSettings->setValue("rate", rate);
    }
    mSettings->endGroup();

    mSettings->beginGroup("skin");
    QString backGround = mSettings->value("background").toString();
    //backGround为空时，赋默认值为：0_bg
    if(backGround.isEmpty() || backGround != "0_bg") {
        backGround = QString("0_bg");
        mSettings->setValue("background", backGround);
    }
    mSettings->endGroup();
    mSettings->sync();
}

void SessionDispatcher::getCityIdInfo() {
    mSettings->beginGroup("weather");
    initCityId = mSettings->value("cityId").toString();
    mSettings->endGroup();
    mSettings->sync();
}

QStringList SessionDispatcher::getLatandLon(QString id) {
//    QStringList tmp;
//    mSettings->beginGroup("weather");
//    tmp << mSettings->value("latitude").toString();
//    tmp << mSettings->value("longitude").toString();
//    mSettings->endGroup();
//    mSettings->sync();
//    return tmp;

    QStringList tmp;
    bool flag = false;
    mSettings->beginGroup("weather");
    QStringList idList = mSettings->value("idList").toStringList();
    QStringList latitude = mSettings->value("latitude").toStringList();
    QStringList longitude = mSettings->value("longitude").toStringList();
    mSettings->endGroup();
    mSettings->sync();

    int j = 0;
    for (int i=0; i< idList.length(); i++) {
        if(id == idList[i]) {
            flag = true;
            break;
        }
        j += 1;
    }
    if(flag) {
        flag = false;
        tmp << latitude[j];
        tmp << longitude[j];
    }
    return tmp;
}

void SessionDispatcher::change_maincheckbox_status(QString status) {
    emit startChangeMaincheckboxStatus(status);
}
