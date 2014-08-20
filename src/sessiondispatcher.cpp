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

#include "sessiondispatcher.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QFontDialog>
#include <QFileDialog>
#include "warningdialog.h"
#include "kthread.h"
#include "util.h"
#include "kfontdialog.h"
#include "logindialog.h"
#include "messengerproxy.h"

QString selectedFont;
extern QPoint widgetPosition;

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

    httpauth = new HttpAuth();
    mSettings = new QSettings(YOUKER_COMPANY_SETTING, YOUKER_SETTING_FILE_NAME_SETTING);
    mSettings->setIniCodec("UTF-8");

    default_Settings = new QSettings(DEFAULT_UBUNTUKYLIN_SETTING, QSettings::IniFormat);
    default_Settings->setIniCodec("UTF-8");

    //初始化QSetting配置文件
    initConfigFile();

    slidershow = new NewCharacter();

    //超时计时器
    timer = new QTimer(this);
    loginOK = false;

    updatetimer = new QTimer(this);

    //handler_change_titlebar_position
    QObject::connect(sessioniface, SIGNAL(change_titlebar_position(QString)), this, SLOT(handler_change_titlebar_position(QString)));
    QObject::connect(sessioniface, SIGNAL(display_scan_process(QString)), this, SLOT(handler_scan_process(QString)));
    QObject::connect(sessioniface, SIGNAL(scan_complete(QString)), this, SLOT(handler_scan_complete(QString)));
    QObject::connect(sessioniface, SIGNAL(access_weather(QString, QString)), this, SLOT(accord_flag_access_weather(QString, QString)));
    QObject::connect(sessioniface, SIGNAL(total_data_transmit(QString, QString)), this, SLOT(handler_total_data_transmit(QString,QString)));

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

    //login
    QObject::connect(httpauth, SIGNAL(response(/*QString,*/QString,QString,QString)), this, SLOT(handle_data_after_login_success(/*QString,*/QString,QString,QString)));
    QObject::connect(httpauth, SIGNAL(refresh(/*QString,*/QString)), this, SLOT(handle_data_after_search_success(/*QString,*/QString)));
    QObject::connect(httpauth, SIGNAL(error(int)), this, SLOT(handle_data_when_login_failed(int)));
    QObject::connect(httpauth, SIGNAL(failedCommunicate()), this, SLOT(resetTimerStatus()));
    QObject::connect(httpauth, SIGNAL(successCommunicate()), this, SLOT(searchCurrentInfo()));

    QObject::connect(sessioniface, SIGNAL(get_history_number(QString, int)), this, SLOT(handlerHistoryNumber(QString, int)));
    QObject::connect(sessioniface, SIGNAL(get_largefile_list(QStringList)), this, SLOT(handlerLargeFileList(QStringList)));

    QObject::connect(MessengerProxy::get_instance_object(), SIGNAL(getHomeBackIndex(int)), this, SLOT(handlerBackToHomePage(int)));
    selectDialog = new SelectDialog(mSettings, 0);
    connect(selectDialog, SIGNAL(readyToUpdateWeatherForWizard()), this, SLOT(handler_change_city()));

    connect(updatetimer,SIGNAL(timeout()),this,SLOT(get_current_weather_qt()));
    updatetimer->start(60000*15);

    this->get_distrowatch_url_qt("http://distrowatch.com/");
    qDebug() << this->get_distrowatch_info_qt();
}

SessionDispatcher::~SessionDispatcher() {
    if(loginOK) {
        //退出
        mSettings->beginGroup("user");
        int id = mSettings->value("id").toInt();
        mSettings->endGroup();
        mSettings->sync();
        QString requestData = QString("http://www.ubuntukylin.com/boxbeta/find_get.php?pp[type]=logout&pp[table]=yk_member&pp[id]=%1").arg(id);
        QUrl url(requestData);
        httpauth->sendGetRequest(url);
    }
    if (httpauth != NULL) {
        delete httpauth;
    }
    waitTime = 0;
    disconnect(timer,SIGNAL(timeout()),this,SLOT(connectHttpServer()));
    if(timer->isActive()) {
        timer->stop();
    }
    if (timer != NULL) {
        delete timer;
    }

    disconnect(updatetimer,SIGNAL(timeout()),this,SLOT(get_current_weather_qt()));
    if(updatetimer->isActive()) {
        updatetimer->stop();
    }
    if (updatetimer != NULL) {
        delete updatetimer;
    }


    this->exit_qt();
    if (sessioniface != NULL) {
        delete sessioniface;
    }
    mSettings->sync();
    if (mSettings != NULL) {
        delete mSettings;
    }

    default_Settings->sync();
    if (default_Settings != NULL) {
        delete default_Settings;
    }

    if (slidershow != NULL) {
        delete slidershow;
    }

    if (selectDialog != NULL) {
        delete selectDialog;
    }
}

//dbus服务退出
void SessionDispatcher::exit_qt() {
    sessioniface->call("exit");
}

bool SessionDispatcher::judge_camera_qt() {
    QDBusReply<bool> reply = sessioniface->call("judge_camera");
    return reply.value();
}

void SessionDispatcher::call_camera_qt() {
    QStringList tmp;
    KThread *thread = new KThread(tmp, sessioniface, "call_camera");
    thread->start();
}

bool SessionDispatcher::judge_power_is_exists_qt() {
    QDBusReply<bool> reply = sessioniface->call("judge_power_is_exists");
    return reply.value();
}

bool SessionDispatcher::read_battery_info_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = sessioniface->call("read_battery_info");
    if (reply.isValid()) {
        QMap<QString, QVariant> value = reply.value();
        batteryInfo.clear();
        batteryInfo = value;
        if (batteryInfo.contains("POWER_SUPPLY_VOLTAGE_NOW")) {
            batteryInfo["POWER_SUPPLY_VOLTAGE_NOW"] =  QString::number(batteryInfo["POWER_SUPPLY_VOLTAGE_NOW"].toDouble()/1000000, 'f', 1) + "V";
        }
        if (batteryInfo.contains("POWER_SUPPLY_ENERGY_FULL_DESIGN")) {
            batteryInfo["POWER_SUPPLY_ENERGY_FULL_DESIGN"] =  QString::number(batteryInfo["POWER_SUPPLY_ENERGY_FULL_DESIGN"].toDouble()/1000000, 'f', 1) + "Wh";
        }
        if (batteryInfo.contains("POWER_SUPPLY_ENERGY_FULL")) {
            batteryInfo["POWER_SUPPLY_ENERGY_FULL"] =  QString::number(batteryInfo["POWER_SUPPLY_ENERGY_FULL"].toDouble()/1000000, 'f', 1) + "Wh";
        }
        if (batteryInfo.contains("POWER_SUPPLY_ENERGY_NOW")) {
            batteryInfo["POWER_SUPPLY_ENERGY_NOW"] =  QString::number(batteryInfo["POWER_SUPPLY_ENERGY_NOW"].toDouble()/1000000, 'f', 1) + "Wh";
        }
        return true;
    }
    else {
        qDebug() << "get battery_message failed!";
        return false;
    }
}

void SessionDispatcher::let_detail_info_page_to_update_data(QString infoFlag) {
    emit this->tellDetailPageUpdateData(infoFlag);
}

void SessionDispatcher::handlerHistoryNumber(QString flag, int num) {
    emit this->tellQMLHistoryNumber(flag, num);
}

void SessionDispatcher::handlerLargeFileList(QStringList filelist) {
    emit this->tellQMLLargeFileList(filelist);
}

void SessionDispatcher::open_folder_qt(QString path) {
    sessioniface->call("open_folder", path);
}

//distrowatch rank
void SessionDispatcher::get_distrowatch_url_qt(QString url) {
    sessioniface->call("get_distrowatch_url", url);
}

QStringList SessionDispatcher::get_distrowatch_info_qt() {
    QDBusReply<QStringList> reply = sessioniface->call("get_distrowatch_info");
    qDebug() << "get_distrowatch_info_qt->";
    qDebug() << reply.value();
    return reply.value();
}


//准发发送信号告诉优客助手自己去改变自身的标题栏控制按钮位置
void SessionDispatcher::handler_change_titlebar_position(QString position) {
    emit this->startChangeControlBtnPosition(position);
}

//每30minutes连接服务器beat一次
void SessionDispatcher::connectHttpServer(){
    mSettings->beginGroup("user");
    int id = mSettings->value("id").toInt();
    mSettings->endGroup();
    mSettings->sync();
    //心跳
    QString requestData = QString("http://www.ubuntukylin.com/boxbeta/find_get.php?pp[type]=beat&pp[table]=yk_member&pp[id]=%1").arg(id);
    QUrl url(requestData);
    httpauth->sendGetRequest(url);
}

//beat失败处理，beat不成功，界面的用户信息消失，改为登录界面，提示网络出错
void SessionDispatcher::resetTimerStatus() {
    //主动查询
    QString requestData = QString("http://www.ubuntukylin.com/boxbeta/find_get.php?pp[type]=network");
    QUrl url(requestData);
    httpauth->sendGetRequest(url);
}

//查询当前的积分、等级....
void SessionDispatcher::searchCurrentInfo() {
    waitTime = 0;
    mSettings->beginGroup("user");
    int id = mSettings->value("id").toInt();
    mSettings->endGroup();
    mSettings->sync();
    QString requestData = QString("http://www.ubuntukylin.com/boxbeta/find_get.php?pp[type]=getall&pp[table]=yk_member&pp[id]=%1").arg(id);
    QUrl url(requestData);
    httpauth->sendGetRequest(url);
}

//显示SliderShow
void SessionDispatcher::show_slider_qt() {
    sessioniface->call("display_slide_show");
}

//程序正常关闭之前，关闭定时器，获取id后发送退出信号给服务端
void SessionDispatcher::ready_exit_normally() {
    //关闭定时器
    waitTime = 0;
    disconnect(timer,SIGNAL(timeout()),this,SLOT(connectHttpServer()));
    if(timer->isActive()) {
        timer->stop();
    }
    //退出
    mSettings->beginGroup("user");
    int id = mSettings->value("id").toInt();
    mSettings->endGroup();
    mSettings->sync();
    QString requestData = QString("http://www.ubuntukylin.com/boxbeta/find_get.php?pp[type]=logout&pp[table]=yk_member&pp[id]=%1").arg(id);
    QUrl url(requestData);
    httpauth->sendGetRequest(url);
}

//点击登录框的确定按钮后，开始发送数据给服务端进行登录验证
void SessionDispatcher::verify_user_and_password(QString user, QString pwd) {
    //显示登录动态图
    emit showLoginAnimatedImage();
    //发送数据给服务端进行登录验证
    QString requestData = QString("http://www.ubuntukylin.com/boxbeta/find_get.php?pp[type]=login&pp[table]=yk_member&name=%1&password=%2").arg(user).arg(pwd);
    QUrl url(requestData);
    httpauth->sendGetRequest(url);
}

//弹出登录框
void SessionDispatcher::popup_login_dialog() {
    //LoginDialog width:397; LoginDialog height:282
    LoginDialog *logindialog = new LoginDialog();
    QObject::connect(logindialog, SIGNAL(translate_user_password(QString,QString)),this, SLOT(verify_user_and_password(QString,QString)));
    int w_x = widgetPosition.x() + (this->mainwindow_width / 2) - (397  / 2);
    int w_y = widgetPosition.y() + (this->mainwindow_height /2) - (282  / 2);
    logindialog->move(w_x, w_y);
    logindialog->exec();
}

//退出登录
void SessionDispatcher::logout_ubuntukylin_account() {
    this->ready_exit_normally();
}

//用户登录成功后处理数据：显示界面、id写入本地配置、开启定时器
void SessionDispatcher::handle_data_after_login_success(QString id,/* QString level, */QString name, QString score) {
    loginOK = true;
    //登录成功后将用户信息显示在界面上
    bool ok;
    QString level = score_count_level(score.toInt(&ok, 10));
    emit updateLoginStatus(name, level, score);

    //将当前用户id写入本地配置文件中
    mSettings->beginGroup("user");
    mSettings->setValue("id", id);
    mSettings->endGroup();
    mSettings->sync();

    //绑定和初始化定时器，每隔30minutes连接服务器一次
    waitTime = 0;
    connect(timer,SIGNAL(timeout()),this,SLOT(connectHttpServer()));
    timer->start(60000*30);//5000
}

//用户查询成功后处理数据：界面刷新数据
void SessionDispatcher::handle_data_after_search_success(/*QString level, */QString score) {
    //查询成功后将用户信息更新在界面上
    bool ok;
    QString level = score_count_level(score.toInt(&ok, 10));
    emit refreshUserInfo(level, score);
    waitTime = 0;
}

//登录失败时或者测试网络失败，通知QML界面
void SessionDispatcher::handle_data_when_login_failed(int status) {
    if(status == 99) {
        waitTime++;
        if(waitTime >= 4){
            waitTime = 0;
            disconnect(timer, SIGNAL(timeout()), this, SLOT(connectHttpServer()));
            if(timer->isActive()) {
                timer->stop();
            }
            emit loginFailedStatus(99); //超时次数到，向主界面发送网络出现错误的信号
            qDebug()<<"connect fail...";
        }else{
            qDebug() << "continue connect...";
            QString requestData = QString("http://www.ubuntukylin.com/boxbeta/find_get.php?pp[type]=network");
            QUrl url(requestData);
            httpauth->sendGetRequest(url);
        }
    }
    else {
        loginOK = false;
        emit loginFailedStatus(status);
    }
}

//根据积分计算用户等级
QString SessionDispatcher::score_count_level(int score) {
    return QString::number(qFloor(sqrt((score - 5) / 30 )));
}

//更加相应的标记去获取需要的天气数据
void SessionDispatcher::accord_flag_access_weather(QString key, QString value) {
    if(key == "weather" && value == "kobe") {
        get_current_weather_dict_qt();
        emit startUpdateForecastWeahter("weather");
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
//    sessioniface->call("onekey_scan_function", selectedList);
    KThread *thread = new KThread(selectedList, sessioniface, "onekey_scan_function");
    thread->start();
}

void SessionDispatcher::scan_history_records_qt(QString flag) {
//    QDBusReply<int> reply = sessioniface->call("scan_history_records", flag);
//    return reply.value();

    QStringList tmp;
    KThread *thread = new KThread(tmp, sessioniface, "scan_history_records", flag);
    thread->start();
}


void SessionDispatcher::scan_system_history_qt() {
//    QDBusReply<int> reply = sessioniface->call("scan_system_history");
//    return reply.value();

    QStringList tmp;
    KThread *thread = new KThread(tmp, sessioniface, "scan_system_history");
    thread->start();
}

//int SessionDispatcher::scan_dash_history_qt() {
//    QDBusReply<int> reply = sessioniface->call("scan_dash_history");
//    return reply.value();
//}

//QStringList SessionDispatcher::scan_of_same_qt(QString abspath) {
//    QDBusReply<QStringList> reply = sessioniface->call("scan_of_same", abspath);
//    return reply.value();
//}

void SessionDispatcher::scan_of_large_qt(QString abspath, int size) {
    QStringList tmp;
    KThread *thread = new KThread(tmp, sessioniface, "scan_of_large", abspath, size);
    thread->start();
}

void SessionDispatcher::cookies_scan_function_qt(QString flag) {
    QStringList tmp;
    KThread *thread = new KThread(tmp, sessioniface, "cookies_scan_function", flag);
    thread->start();
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
    return tmp;
}

void SessionDispatcher::cache_scan_function_qt(QStringList argList, QString flag) {
    KThread *thread = new KThread(argList, sessioniface, "cache_scan_function", flag);
    thread->start();
}

void SessionDispatcher::package_scan_function_qt(QStringList argList) {
    KThread *thread = new KThread(argList, sessioniface, "package_scan_function");
    thread->start();
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
        systemInfo.clear();
        systemInfo = value;
//        qDebug() << systemInfo;
//        QMap(("cpu", QVariant(QString, " Pentium(R) Dual-Core  CPU      E5500  @ 2.80GHz") ) ( "currrent_user" ,  QVariant(QString, "trusty") ) ( "desktopenvironment" ,  QVariant(QString, "Unity") ) ( "distribution" ,  QVariant(QString, "Ubuntu Kylin-14.04-trusty") ) ( "home_path" ,  QVariant(QString, "/home/trusty") ) ( "hostname" ,  QVariant(QString, "trusty-lenovo") ) ( "language" ,  QVariant(QString, "zh_CN.UTF-8") ) ( "platform" ,  QVariant(QString, "x86_64") ) ( "ram" ,  QVariant(QString, "2.0 GB") ) ( "shell" ,  QVariant(QString, "/bin/bash") ) )
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

//----------------message dialog--------------------
void SessionDispatcher::showFeatureDialog() {
    //slider width:680; slider height:372
    int w_x = widgetPosition.x() + (this->mainwindow_width / 2) - (680  / 2);
    int w_y = widgetPosition.y() + (this->mainwindow_height /2) - (372  / 2);
    slidershow->move(w_x, w_y);
    slidershow->showSlider();
}

//----------------checkscreen dialog--------------------
void SessionDispatcher::showCheckscreenDialog() {
    //ModalDialog width:329; ModalDialog height:195
    ModalDialog *dialog = new ModalDialog;
    int w_x = widgetPosition.x() + (this->mainwindow_width / 2) - (329  / 2);
    int w_y = widgetPosition.y() + (this->mainwindow_height /2) - (195  / 2);
    dialog->move(w_x, w_y);
    dialog->setModal(true);
    dialog->show();
}

void SessionDispatcher::showWarningDialog(QString title, QString content) {
    //WarningDialog width:329; WarningDialog height:195
    WarningDialog *dialog = new WarningDialog(title, content);
    int w_x = widgetPosition.x() + (this->mainwindow_width / 2) - (329  / 2);
    int w_y = widgetPosition.y() + (this->mainwindow_height /2) - (195  / 2);
    dialog->move(w_x, w_y);
    dialog->exec();
}

bool SessionDispatcher::showConfirmDialog(QString title, QString content) {
    //WarningDialog width:329; WarningDialog height:195
    WarningDialog *dialog = new WarningDialog(title, content);
    int w_x = widgetPosition.x() + (this->mainwindow_width / 2) - (329  / 2);
    int w_y = widgetPosition.y() + (this->mainwindow_height /2) - (195  / 2);
    dialog->move(w_x, w_y);
    dialog-> QWidget::setAttribute(Qt::WA_DeleteOnClose);
    if(dialog->exec()==QDialog::Rejected) {
        return false;
    }
    else {
        return true;
    }
}

QString SessionDispatcher::getSingleInfo(QString key) {
    QVariant info = systemInfo.value(key);
    return info.toString();
}

QString SessionDispatcher::getBatterySingleInfo(QString key) {
    QVariant info = batteryInfo.value(key);
    return info.toString();
}

//-------------------------------------ubuntukylin default settings-------------------------------------
QString SessionDispatcher::get_uk_default_setting_string(QString key, QString name) {
    QString result;
    default_Settings->beginGroup(key);
    if (key == "window" && name == "button-layout") {
        result = default_Settings->value(name).toString().replace("-", ",");
    }
    else {
        result = default_Settings->value(name).toString();
    }
    default_Settings->endGroup();
    default_Settings->sync();
    return result;
}

double SessionDispatcher::get_uk_default_setting_double(QString key, QString name) {
    default_Settings->beginGroup(key);
    double result = default_Settings->value(name).toDouble();
    default_Settings->endGroup();
    default_Settings->sync();
    return result;
}

int SessionDispatcher::get_uk_default_setting_int(QString key, QString name) {
    default_Settings->beginGroup(key);
    int result = default_Settings->value(name).toInt();
    default_Settings->endGroup();
    default_Settings->sync();
    return result;
}

bool SessionDispatcher::get_uk_default_setting_bool(QString key, QString name) {
    default_Settings->beginGroup(key);
    bool result = default_Settings->value(name).toBool();
    default_Settings->endGroup();
    default_Settings->sync();
    return result;
}

void SessionDispatcher::restore_uk_default_setting(QString key, QString name) {
    default_Settings->beginGroup(key);
    //-------------------字体-------------------
    if (key == "font") {
        if(name == "font-name") {//"Ubuntu 11"
            sessioniface->call("set_ubuntukylin_default_setting_str", "org.gnome.desktop.interface", "font", "font-name", "string", default_Settings->value(name).toString());
        }
        else if(name == "font") {//"Ubuntu 11"
            sessioniface->call("set_ubuntukylin_default_setting_str", "org.gnome.nautilus.desktop", "font", "font", "string", default_Settings->value(name).toString());
        }
        else if(name == "monospace-font-name") {//"Ubuntu Mono 13"
            sessioniface->call("set_ubuntukylin_default_setting_str", "org.gnome.desktop.interface", "font", "monospace-font-name", "string", default_Settings->value(name).toString());
        }
        else if(name == "document-font-name") {//"Sans 11"
            sessioniface->call("set_ubuntukylin_default_setting_str", "org.gnome.desktop.interface", "font", "document-font-name", "string", default_Settings->value(name).toString());
        }
        else if(name == "titlebar-font") {//"Ubuntu Bold 11"
            sessioniface->call("set_ubuntukylin_default_setting_str", "org.gnome.desktop.wm.preferences", "font", "titlebar-font", "string", default_Settings->value(name).toString());
        }
        else if(name == "text-scaling-factor") {//1
            sessioniface->call("set_ubuntukylin_default_setting_double", "org.gnome.desktop.interface", "font", "text-scaling-factor", "double", default_Settings->value(name).toDouble());
        }
        else if(name == "hinting") {//"slight"
            sessioniface->call("set_ubuntukylin_default_setting_str", "org.gnome.settings-daemon.plugins.xsettings", "font", "hinting", "string", default_Settings->value(name).toString());
        }
        else if(name == "antialiasing") {//"rgba"
            sessioniface->call("set_ubuntukylin_default_setting_str", "org.gnome.settings-daemon.plugins.xsettings", "font", "antialiasing", "string", default_Settings->value(name).toString());
        }
    }
    else if (key == "icon") {
        if(name == "icon-theme") {//"ubuntukylin-icon-theme"
             sessioniface->call("set_ubuntukylin_default_setting_str", "org.gnome.desktop.interface", "icon", "icon-theme", "string", default_Settings->value(name).toString());
        }
        else if(name == "show-desktop-icons") {//显示桌面图标
             sessioniface->call("set_ubuntukylin_default_setting_bool", "org.gnome.desktop.background", "icon", "show-desktop-icons", "boolean", default_Settings->value(name).toBool());
        }
        else if(name == "home-icon-visible") {//显示主文件夹
             sessioniface->call("set_ubuntukylin_default_setting_bool", "org.gnome.nautilus.desktop", "icon", "home-icon-visible", "boolean", default_Settings->value(name).toBool());
        }
        else if(name == "network-icon-visible") {//显示网络
             sessioniface->call("set_ubuntukylin_default_setting_bool", "org.gnome.nautilus.desktop", "icon", "network-icon-visible", "boolean", default_Settings->value(name).toBool());
        }
        else if(name == "trash-icon-visible") {//显示回收站
             sessioniface->call("set_ubuntukylin_default_setting_bool", "org.gnome.nautilus.desktop", "icon", "trash-icon-visible", "boolean", default_Settings->value(name).toBool());
        }
        else if(name == "volumes-visible") {//显示挂载卷标
             sessioniface->call("set_ubuntukylin_default_setting_bool", "org.gnome.nautilus.desktop", "icon", "volumes-visible", "boolean", default_Settings->value(name).toBool());
        }
    }
    else if (key == "file") {
        if(name == "always-use-location-entry") {//路径输入框取代路径栏
            sessioniface->call("set_ubuntukylin_default_setting_bool", "org.gnome.nautilus.preferences", "file", "always-use-location-entry", "boolean", default_Settings->value(name).toBool());
        }
        else if(name == "automount") {//自动挂载媒体
            sessioniface->call("set_ubuntukylin_default_setting_bool", "org.gnome.desktop.media-handling", "file", "automount", "boolean", default_Settings->value(name).toBool());
        }
        else if(name == "automount-open") {//自动打开文件夹
            sessioniface->call("set_ubuntukylin_default_setting_bool", "org.gnome.desktop.media-handling", "file", "automount-open", "boolean", default_Settings->value(name).toBool());
        }
        else if(name == "autorun-never") {//提示自动运行的程序
            sessioniface->call("set_ubuntukylin_default_setting_bool", "org.gnome.desktop.media-handling", "file", "autorun-never", "boolean", default_Settings->value(name).toBool());
        }
        else if(name == "thumbnail-size") {//缩略图图标尺寸（像素）
            sessioniface->call("set_ubuntukylin_default_setting_int", "org.gnome.nautilus.icon-view", "file", "thumbnail-size", "int", default_Settings->value(name).toInt());
        }
        else if(name == "maximum-age") {//缩略图缓存时间（天数）
            sessioniface->call("set_ubuntukylin_default_setting_int", "org.gnome.desktop.thumbnail-cache", "file", "maximum-age", "int", default_Settings->value(name).toInt());
        }
        else if(name == "maximum-size") {//最大缩略图缓存尺寸（MB）
            sessioniface->call("set_ubuntukylin_default_setting_int", "org.gnome.desktop.thumbnail-cache", "file", "maximum-size", "int", default_Settings->value(name).toInt());
        }
    }
    else if (key == "unity") {
        if(name == "icon-size") {//launcher图标大小
            sessioniface->call("set_ubuntukylin_default_setting_int", "org.compiz.unityshell", "unity", "icon-size", "int", default_Settings->value(name).toInt());
        }
        else if(name == "launcher-hide-mode") {//launcher自动隐藏
            sessioniface->call("set_ubuntukylin_default_setting_int", "org.compiz.unityshell", "unity", "launcher-hide-mode", "int", default_Settings->value(name).toInt());
        }
        else if(name == "launcher-opacity") {//透明度
            sessioniface->call("set_ubuntukylin_default_setting_double", "org.compiz.unityshell", "unity", "launcher-opacity", "double", default_Settings->value(name).toDouble());
        }
        else if(name == "backlight-mode") {//图标背景模式
            sessioniface->call("set_ubuntukylin_default_setting_int", "org.compiz.unityshell", "unity", "backlight-mode", "int", default_Settings->value(name).toInt());
        }

        else if(name == "dash-blur-experimental") {//Dash背景模糊类型
            sessioniface->call("set_ubuntukylin_default_setting_int", "org.compiz.unityshell", "unity", "dash-blur-experimental", "int", default_Settings->value(name).toInt());
        }
        else if(name == "panel-opacity") {//面板菜单透明度
            sessioniface->call("set_ubuntukylin_default_setting_double", "org.compiz.unityshell", "unity", "panel-opacity", "double", default_Settings->value(name).toDouble());
        }
    }
    else if (key == "mouse") {
        if(name == "cursor-size") {
            sessioniface->call("set_ubuntukylin_default_setting_int", "org.gnome.desktop.interface", "mouse", "cursor-size", "int", default_Settings->value(name).toInt());
        }
    }
    else if (key == "touchpad") {
        if(name == "touchpad-enabled") {
            sessioniface->call("set_ubuntukylin_default_setting_bool", "org.gnome.settings-daemon.peripherals.touchpad", "touchpad", "touchpad-enabled", "boolean", default_Settings->value(name).toBool());
        }
        else if(name == "horiz-scroll-enabled") {
            sessioniface->call("set_ubuntukylin_default_setting_bool", "org.gnome.settings-daemon.peripherals.touchpad", "touchpad", "horiz-scroll-enabled", "boolean", default_Settings->value(name).toBool());
        }
        else if(name == "scrollbar-mode") {
            sessioniface->call("set_ubuntukylin_default_setting_str", "com.canonical.desktop.interface", "touchpad", "scrollbar-mode", "string", default_Settings->value(name).toString());
        }
        else if(name == "scroll-method") {
            sessioniface->call("set_ubuntukylin_default_setting_str", "org.gnome.settings-daemon.peripherals.touchpad", "touchpad", "scroll-method", "string", default_Settings->value(name).toString());
        }
    }
    else if (key == "window") {
        if(name == "button-layout") {
            sessioniface->call("set_ubuntukylin_default_setting_str", "org.gnome.desktop.wm.preferences", "window", "button-layout", "string", default_Settings->value(name).toString().replace("-", ","));
        }
        else if(name == "menus-have-icons") {
            sessioniface->call("set_ubuntukylin_default_setting_bool", "org.gnome.desktop.interface", "window", "menus-have-icons", "boolean", default_Settings->value(name).toBool());
        }
        else if(name == "mouse-wheel-action") {
            sessioniface->call("set_ubuntukylin_default_setting_str", "org.compiz.gwd", "window", "mouse-wheel-action", "string", default_Settings->value(name).toString());
        }
        else if(name == "action-double-click-titlebar") {
            sessioniface->call("set_ubuntukylin_default_setting_str", "org.gnome.desktop.wm.preferences", "window", "action-double-click-titlebar", "string", default_Settings->value(name).toString());
        }
        else if(name == "action-middle-click-titlebar") {
            sessioniface->call("set_ubuntukylin_default_setting_str", "org.gnome.desktop.wm.preferences", "window", "action-middle-click-titlebar", "string", default_Settings->value(name).toString());
        }
        else if(name == "action-right-click-titlebar") {
            sessioniface->call("set_ubuntukylin_default_setting_str", "org.gnome.desktop.wm.preferences", "window", "action-right-click-titlebar", "string", default_Settings->value(name).toString());
        }
    }
    else if (key == "datetime") {
        if(name == "time-format") {//日期时间格式
            sessioniface->call("set_ubuntukylin_default_setting_str", "com.canonical.indicator.datetime", "datetime", "time-format", "string", default_Settings->value(name).toString());
        }
        else if(name == "show-seconds") {//秒
            sessioniface->call("set_ubuntukylin_default_setting_bool", "com.canonical.indicator.datetime", "datetime", "show-seconds", "boolean", default_Settings->value(name).toBool());
        }
        else if(name == "show-day") {//星期
            sessioniface->call("set_ubuntukylin_default_setting_bool", "com.canonical.indicator.datetime", "datetime", "show-day", "boolean", default_Settings->value(name).toBool());
        }
        else if(name == "show-date") {//日期
            sessioniface->call("set_ubuntukylin_default_setting_bool", "com.canonical.indicator.datetime", "datetime", "show-date", "boolean", default_Settings->value(name).toBool());
        }
    }
    else if (key == "power") {
        if(name == "time-format") {//日期时间格式
            sessioniface->call("set_ubuntukylin_default_setting_str", "com.canonical.indicator.power", "power", "icon-policy", "string", default_Settings->value(name).toString());
        }
        else if(name == "show-percentage") {//电源百分比
            sessioniface->call("set_ubuntukylin_default_setting_bool", "com.canonical.indicator.power", "power", "show-percentage", "boolean", default_Settings->value(name).toBool());
        }
        else if(name == "show-time") {//电源时间
            sessioniface->call("set_ubuntukylin_default_setting_bool", "com.canonical.indicator.power", "power", "show-time", "boolean", default_Settings->value(name).toBool());
        }
    }

    default_Settings->endGroup();
    default_Settings->sync();
}
//-------------------------------------uk end-------------------------------------


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

int SessionDispatcher::get_default_unity_qt(QString name, QString key) {
    QDBusReply<int> reply = sessioniface->call("get_default_unity", name, key);
    return reply.value();
}

void SessionDispatcher::set_default_unity_qt(QString flag, int value) {
    if(flag == "launchersize") {//launcher图标大小
        sessioniface->call("set_default_unity", "icon-size", "int", value);
    }
    else if(flag == "launcherhide") {//launcher自动隐藏
        sessioniface->call("set_default_unity", "launcher-hide-mode", "int", value);
    }
}

void SessionDispatcher::set_default_launcher_have_showdesktopicon_qt() {
    sessioniface->call("set_default_launcher_have_showdesktopicon");
}

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

// for v1.1.0
//透明度
double SessionDispatcher::get_launcher_transparency_qt() {
    QDBusReply<double> reply = sessioniface->call("get_launcher_transparency");
    return reply.value();
}

bool SessionDispatcher::set_launcher_transparency_qt(double opacity) {
    QDBusReply<bool> reply = sessioniface->call("set_launcher_transparency", opacity);
    return reply.value();
}

//图标背景
QStringList SessionDispatcher::get_all_launcher_icon_colourings_qt() {
    QDBusReply<QStringList> reply = sessioniface->call("get_all_launcher_icon_colourings");
    return reply.value();
}

int SessionDispatcher::get_launcher_icon_colouring_qt() {
    QDBusReply<int> reply = sessioniface->call("get_launcher_icon_colouring");
    return reply.value();
}

bool SessionDispatcher::set_launcher_icon_colouring_qt(int colouring) {
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
QStringList SessionDispatcher::get_window_themes_qt() {
    QDBusReply<QStringList> reply = sessioniface->call("get_window_themes");
    return reply.value();
}

QString SessionDispatcher::get_current_window_theme_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_current_window_theme");
    return reply.value();
}

void SessionDispatcher::set_window_theme_qt(QString theme) {
    sessioniface->call("set_window_theme", theme);
}

/*-----------------------------font of beauty-----------------------------*/
QString SessionDispatcher::get_default_theme_sring_qt(QString flag/*QString schema, QString key*/) {
    if(flag == "icontheme") {
        QDBusReply<QString> reply = sessioniface->call("get_default_font_sring", "org.gnome.desktop.interface", "icon-theme");
        return reply.value();
    }
    else if(flag == "windowtheme") {
        QDBusReply<QString> reply = sessioniface->call("get_default_font_sring", "org.gnome.desktop.wm.preferences", "theme");
        return reply.value();
    }
    else if(flag == "mousetheme") {
        QDBusReply<QString> reply = sessioniface->call("get_default_font_sring", "org.gnome.desktop.interface", "cursor-theme");
        return reply.value();
    }
    else if(flag == "smoothstyle") {
        QDBusReply<QString> reply = sessioniface->call("get_default_font_sring", "org.gnome.settings-daemon.plugins.xsettings", "hinting");
        return reply.value();
    }
    else if(flag == "antialiasingstyle") {
        QDBusReply<QString> reply = sessioniface->call("get_default_font_sring", "org.gnome.settings-daemon.plugins.xsettings", "antialiasing");
        return reply.value();
    }
    return flag;
}

double SessionDispatcher::get_default_theme_double_qt(QString schema, QString key) {
    QDBusReply<double> reply = sessioniface->call("get_default_font_double", schema, key);
    return reply.value();
}

void SessionDispatcher::set_default_theme_qt(QString flag/*QString schema, QString key, QString type*/) {
    //-------------------字体-------------------
    if(flag == "defaultfont") {
        sessioniface->call("set_default_font", "org.gnome.desktop.interface", "font-name", "string");
    }
    else if(flag == "desktopfont") {
        sessioniface->call("set_default_font", "org.gnome.nautilus.desktop", "font", "string");
    }
    else if(flag == "monospacefont") {
        sessioniface->call("set_default_font", "org.gnome.desktop.interface", "monospace-font-name", "string");
    }
    else if(flag == "globalfontscaling") {
        sessioniface->call("set_default_font", "org.gnome.desktop.interface", "text-scaling-factor", "double");
    }
    else if(flag == "documentfont") {
        sessioniface->call("set_default_font", "org.gnome.desktop.interface", "document-font-name", "string");
    }
    else if(flag == "titlebarfont") {
        sessioniface->call("set_default_font", "org.gnome.desktop.wm.preferences", "titlebar-font", "string");
    }
    else if(flag == "smoothstyle") {
        sessioniface->call("set_default_font", "org.gnome.settings-daemon.plugins.xsettings", "hinting", "string");
    }
    else if(flag == "antialiasingstyle") {
        sessioniface->call("set_default_font", "org.gnome.settings-daemon.plugins.xsettings", "antialiasing", "string");
    }

    else if(flag == "icontheme") {//图标主题
        sessioniface->call("set_default_font", "org.gnome.desktop.interface", "icon-theme", "string");
    }
    else if(flag == "windowtheme") {//窗口主题
        sessioniface->call("set_default_font", "org.gnome.desktop.wm.preferences", "theme", "string");
    }
    else if(flag == "mousetheme") {//鼠标指针主题
        sessioniface->call("set_default_font", "org.gnome.desktop.interface", "cursor-theme", "string");
    }
    else if(flag == "cursorsize") {//光标大小
        sessioniface->call("set_default_font", "org.gnome.desktop.interface", "cursor-size", "int");
    }
}

bool SessionDispatcher::get_default_desktop_bool_qt(QString schema, QString key) {
    QDBusReply<bool> reply = sessioniface->call("get_default_desktop_bool", schema, key);
    return reply.value();
}

void SessionDispatcher::set_default_desktop_qt(QString flag) {
    if(flag == "showdesktopicons") {//显示桌面图标
        sessioniface->call("set_default_desktop", "org.gnome.desktop.background", "show-desktop-icons", "boolean");
    }
    else if(flag == "homeiconvisible") {//显示主文件夹
        sessioniface->call("set_default_desktop", "org.gnome.nautilus.desktop", "home-icon-visible", "boolean");
    }
    else if(flag == "networkiconvisible") {//显示网络
        sessioniface->call("set_default_desktop", "org.gnome.nautilus.desktop", "network-icon-visible", "boolean");
    }
    else if(flag == "trashiconvisible") {//显示回收站
        sessioniface->call("set_default_desktop", "org.gnome.nautilus.desktop", "trash-icon-visible", "boolean");
    }
    else if(flag == "volumesvisible") {//显示挂载卷标
        sessioniface->call("set_default_desktop", "org.gnome.nautilus.desktop", "volumes-visible", "boolean");
    }
}


QString SessionDispatcher::get_default_sound_string_qt(QString flag/*QString schema, QString key*/) {
    if(flag == "soundtheme") {
        QDBusReply<QString> reply = sessioniface->call("get_default_sound_string", "org.gnome.desktop.sound", "theme-name");
        return reply.value();
    }
    return flag;
}

void SessionDispatcher::set_default_sound_qt(QString flag) {
    if(flag == "soundtheme") {//声音主题
        sessioniface->call("set_default_sound", "org.gnome.desktop.sound", "theme-name", "string");
    }
}


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


void SessionDispatcher::restore_default_font_signal(QString flag) {
    emit notifyFontStyleToQML(flag); //font_style
}

void SessionDispatcher::show_font_dialog(QString flag, QString current_font) {
    KFontDialog *fontDialog = new KFontDialog(mSettings, flag, current_font, 0);
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
        else if(flag == "fcitxfont") {

        }
        selectedFont.clear();
        emit notifyFontStyleToQML(flag); //font_style
    }
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
QString SessionDispatcher::get_default_system_sring_qt(QString flag) {
    if(flag == "wheel-action") {//菜单项旁显示图标
        QDBusReply<QString> reply = sessioniface->call("get_default_system_sring", "org.compiz.gwd", "mouse-wheel-action");
        return reply.value();
    }
    else if(flag == "double-click") {//标题栏双击动作
        QDBusReply<QString> reply = sessioniface->call("get_default_system_sring", "org.gnome.desktop.wm.preferences", "action-double-click-titlebar");
        return reply.value();
    }
    else if(flag == "middle-click") {//标题栏中键动作
        QDBusReply<QString> reply = sessioniface->call("get_default_system_sring", "org.gnome.desktop.wm.preferences", "action-middle-click-titlebar");
        return reply.value();
    }
    else if(flag == "right-click") {//标题栏右键动作
        QDBusReply<QString> reply = sessioniface->call("get_default_system_sring", "org.gnome.desktop.wm.preferences", "action-right-click-titlebar");
        return reply.value();
    }
    return flag;
}

bool SessionDispatcher::get_default_system_bool_qt(QString schema, QString key) {
    QDBusReply<bool> reply = sessioniface->call("get_default_system_bool", schema, key);
    return reply.value();
}

void SessionDispatcher::set_default_system_qt(QString flag) {
    if(flag == "touchpad-enabled") {//启用禁用触摸板
        sessioniface->call("set_default_system", "org.gnome.settings-daemon.peripherals.touchpad", "touchpad-enabled", "boolean");
    }
    else if(flag == "scrollbar-mode") {//滚动条类型
        sessioniface->call("set_default_system", "com.canonical.desktop.interface", "scrollbar-mode", "string");
    }
    else if(flag == "scroll-method") {//触摸板滚动条触发方式
        sessioniface->call("set_default_system", "org.gnome.settings-daemon.peripherals.touchpad", "scroll-method", "string");
    }
    else if(flag == "horiz-scroll-enabled") {//触摸板横向滚动
        sessioniface->call("set_default_system", "org.gnome.settings-daemon.peripherals.touchpad", "horiz-scroll-enabled", "boolean");
    }
    else if(flag == "control-button-position") {//窗口控制按钮位置
        sessioniface->call("set_default_system", "org.gnome.desktop.wm.preferences", "button-layout", "string");
    }
    else if(flag == "menu-with-icons") {//菜单项旁显示图标
        sessioniface->call("set_default_system", "org.gnome.desktop.interface", "menus-have-icons", "boolean");
    }
    else if(flag == "wheel-action") {//标题栏鼠标滚轮动作
        sessioniface->call("set_default_system", "org.compiz.gwd", "mouse-wheel-action", "string");
    }
    else if(flag == "double-click") {//标题栏双击动作
        sessioniface->call("set_default_system", "org.gnome.desktop.wm.preferences", "action-double-click-titlebar", "string");
    }
    else if(flag == "middle-click") {//标题栏中键动作
        sessioniface->call("set_default_system", "org.gnome.desktop.wm.preferences", "action-middle-click-titlebar", "string");
    }
    else if(flag == "right-click") {//标题栏右键动作
        sessioniface->call("set_default_system", "org.gnome.desktop.wm.preferences", "action-right-click-titlebar", "string");
    }
}



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

QStringList SessionDispatcher::get_titlebar_double_qt() {
    QDBusReply<QStringList> reply = sessioniface->call("get_titlebar_double");
    return reply.value();
}

QString SessionDispatcher::get_current_titlebar_double_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_current_titlebar_double");
    return reply.value();
}

void SessionDispatcher::set_titlebar_double_qt(QString value) {
    sessioniface->call("set_titlebar_double", value);
}

QStringList SessionDispatcher::get_titlebar_middle_qt() {
    QDBusReply<QStringList> reply = sessioniface->call("get_titlebar_middle");
    return reply.value();
}

QString SessionDispatcher::get_current_titlebar_middle_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_current_titlebar_middle");
    return reply.value();
}

void SessionDispatcher::set_titlebar_middle_qt(QString value) {
    sessioniface->call("set_titlebar_middle", value);
}

QStringList SessionDispatcher::get_titlebar_right_qt() {
    QDBusReply<QStringList> reply = sessioniface->call("get_titlebar_right");
    return reply.value();
}

QString SessionDispatcher::get_current_titlebar_right_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_current_titlebar_right");
    return reply.value();
}

void SessionDispatcher::set_titlebar_right_qt(QString value) {
    sessioniface->call("set_titlebar_right", value);
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

void SessionDispatcher::set_default_filemanager_qt(QString flag) {
    if(flag == "pathbar") {//路径输入框取代路径栏
        sessioniface->call("set_default_filemanager", "org.gnome.nautilus.preferences", "always-use-location-entry", "boolean");
    }
    else if(flag == "media") {//自动挂载媒体
        sessioniface->call("set_default_filemanager", "org.gnome.desktop.media-handling", "automount", "boolean");
    }
    else if(flag == "folder") {//自动打开文件夹
        sessioniface->call("set_default_filemanager", "org.gnome.desktop.media-handling", "automount-open", "boolean");
    }
    else if(flag == "programs") {//提示自动运行的程序
        sessioniface->call("set_default_filemanager", "org.gnome.desktop.media-handling", "autorun-never", "boolean");
    }
    else if(flag == "iconsize") {//缩略图图标尺寸（像素）
        sessioniface->call("set_default_filemanager", "org.gnome.nautilus.icon-view", "thumbnail-size", "int");
    }
    else if(flag == "cachetime") {//缩略图缓存时间（天数）
        sessioniface->call("set_default_filemanager", "org.gnome.desktop.thumbnail-cache", "maximum-age", "int");
    }
    else if(flag == "maxsize") {//最大缩略图缓存尺寸（MB）
        sessioniface->call("set_default_filemanager", "org.gnome.desktop.thumbnail-cache", "maximum-size", "int");
    }
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

QString SessionDispatcher::judge_desktop_is_unity_qt() {
    QDBusReply<QString> reply = sessioniface->call("judge_desktop_is_unity");
    return reply.value();
}

bool SessionDispatcher::submit_uk_pingback() {
    QDBusReply<bool> reply = sessioniface->call("submit_uk_pingback");
    return reply.value();
}

bool SessionDispatcher::access_server_pingback() {
    QDBusReply<bool> reply = sessioniface->call("access_server_pingback");
    return reply.value();
}

void SessionDispatcher::get_current_weather_qt() {
    bool result = this->access_server_pingback();
    if(result) {
        qDebug() << "link weather server success....";
        QString initCityId = this->getCityIdInfo();
        bool flag = Util::id_exists_in_location_file(initCityId);
        if(flag) {//获取中国气象局数据
            QStringList tmplist;
            KThread *thread = new KThread(tmplist, sessioniface, "get_current_weather", initCityId);
            thread->start();
        }
        else {//获取雅虎气象数据
            QStringList latlon = this->getLatandLon();
            KThread *thread = new KThread(latlon, sessioniface, "get_current_yahoo_weather", initCityId);
            thread->start();
        }
        this->submit_uk_pingback();
    }
    else {
        qDebug() << "link weather server failed....";
    }
}

void SessionDispatcher::get_current_weather_dict_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = sessioniface->call("get_current_weather_dict");
    currentInfo.clear();
    currentInfo = reply.value();
}

void SessionDispatcher::get_current_yahoo_weather_dict_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = sessioniface->call("get_current_yahoo_weather_dict");
    yahoocurrentInfo.clear();
    yahoocurrentInfo = reply.value();
}


QString SessionDispatcher::getSingleWeatherInfo(QString key, QString flag) {
    QVariant info = "";
    if(flag == "current") {
        info = currentInfo.value(key);
    }
    else if(flag == "weathericon") {
        info = "../../img/weather/" + key;
    }
    else if(flag == "yahoo") {
        info = yahoocurrentInfo.value(key);
    }
    return info.toString();
}

void SessionDispatcher::showWizardController() {
    //selectDialog width:531; selectDialog height:210
    int w_x = widgetPosition.x() + (this->mainwindow_width / 2) - (531  / 2);
    int w_y = widgetPosition.y() + (this->mainwindow_height /2) - (210  / 2);
    selectDialog->move(w_x, w_y);
    selectDialog->showCityDialog();
}

void SessionDispatcher::handler_change_city() {
    emit startChangeQMLCity();
}

void SessionDispatcher::initConfigFile() {
    mSettings->beginGroup("user");
    QString id = mSettings->value("id").toString();
    if(id.isEmpty()) {
        mSettings->setValue("id", "0");
    }
    mSettings->endGroup();

    mSettings->beginGroup("weather");
    QString cityId = mSettings->value("cityId").toString();
    //cityId为空时，赋默认值为：101250101
    if(cityId.isEmpty()) {
        cityId = QString("101250101");
        mSettings->setValue("cityId", cityId);
    }
    QString cityName = mSettings->value("cityName").toString();
    if(cityName.isEmpty()) {
        cityName = QString("湖南,长沙,长沙");
        mSettings->setValue("cityName", cityName);
    }
    QStringList lat_lon = mSettings->value("latLon").toStringList();
    if(lat_lon.isEmpty()) {
        lat_lon.append("NA");
        lat_lon.append("NA");
        mSettings->setValue("latLon", lat_lon);
    }
    mSettings->endGroup();
    mSettings->sync();
}

QString SessionDispatcher::getCityIdInfo() {
    mSettings->beginGroup("weather");
    QString initCityId = mSettings->value("cityId").toString();
    mSettings->endGroup();
    mSettings->sync();
    return initCityId;
}

QStringList SessionDispatcher::getLatandLon() {
    QStringList lat_lon;
    mSettings->beginGroup("weather");
    lat_lon = mSettings->value("latLon").toStringList();
    mSettings->endGroup();
    mSettings->sync();
    return lat_lon;
}

void SessionDispatcher::change_maincheckbox_status(QString status) {
    emit startChangeMaincheckboxStatus(status);
}

//0412
void SessionDispatcher::handlerBackToHomePage(int index) {
    emit backToHomePage(index);
    this->set_page_num(index);
}
