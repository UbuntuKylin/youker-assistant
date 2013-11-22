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

SessionDispatcher::SessionDispatcher(QObject *parent) :
    QObject(parent)
{
    sessioniface = new QDBusInterface("com.ubuntukylin.IhuSession",
                               "/",
                               "com.ubuntukylin.IhuSession",
                               QDBusConnection::sessionBus());
    page_num = 0;
    this->mainwindow_width = 850;
    this->mainwindow_height = 600;
    this->alert_width = 329;
    this->alert_height = 195;

    mSettings = new QSettings(YOUKER_COMPANY_SETTING, YOUKER_SETTING_FILE_NAME_SETTING);
    mSettings->setIniCodec("UTF-8");

    //初始化QSetting配置文件
    initConfigFile();

    skin_widget = new SkinsWidget(mSettings);
    connect(skin_widget, SIGNAL(skinSignalToQML(QString)), this, SLOT(handler_change_skin(QString)));


    QObject::connect(sessioniface,SIGNAL(scan_complete(QString)),this,SLOT(handler_scan_complete(QString)));
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

void SessionDispatcher::handler_scan_complete(QString msg) {
    emit finishScanWork(msg);
}

int SessionDispatcher::scan_history_records_qt() {
    QDBusReply<int> reply = sessioniface->call("scan_history_records");
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
    QDBusReply<QStringList> reply = sessioniface->call("scan_of_large", size, abspath);
    return reply.value();
}

QStringList SessionDispatcher::scan_cookies_records_qt() {
    QDBusReply<QStringList> reply = sessioniface->call("scan_cookies_records");
    return reply.value();
}

QStringList SessionDispatcher::cookies_scan_function_qt(QString flag) {
    QDBusReply<QStringList> reply = sessioniface->call("cookies_scan_function", flag);
    return reply.value();
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

void SessionDispatcher::show_font_dialog(QString flag) {
    bool ok;
    const QFont& font = QFontDialog::getFont(&ok, 0);
    if(ok) {
        QString fontsize = QString("%1").arg(font.pointSize());
        QString fontstyle = font.family() + " " +  font.styleName() + " " + fontsize;
        if(flag == "font")
            set_font_qt(fontstyle);//set font
        else if(flag == "desktopfont")
            set_desktop_font_qt(fontstyle);//set desktopfont
        else if(flag == "monospacefont")
            set_monospace_font_qt(fontstyle);//set monospacefont
        else if(flag == "documentfont")
            set_document_font_qt(fontstyle);//set documentfont
        else if(flag == "titlebarfont")
            set_window_title_font_qt(fontstyle);//set titlebarfont
        emit notifyFontStyleToQML(flag); //font_style
    }
}

QString SessionDispatcher::show_folder_dialog() {
    //选择文件夹
    QString dir = QFileDialog::getExistingDirectory(0, tr("choose folder"), QDir::homePath(),
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

void SessionDispatcher::get_forecast_weahter_qt() {
    getCityIdInfo();
    QDBusReply<QMap<QString, QVariant> > reply = sessioniface->call("get_forecast_weahter", initCityId);
    forecastInfo = reply.value();
}

bool SessionDispatcher::get_current_weather_qt() {
    getCityIdInfo();
    QDBusReply<QMap<QString, QVariant> > reply = sessioniface->call("get_current_weather", initCityId);
    currentInfo = reply.value();
    if(currentInfo.isEmpty()) {
        return false;
    }
    else {
        return true;
    }
}

QString SessionDispatcher::get_current_pm25_qt() {
    getCityIdInfo();
    QDBusReply<QString> reply = sessioniface->call("get_current_pm25", initCityId);
    return reply.value();
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
    QDBusReply<bool> reply = sessioniface->call("update_weather_data", initCityId);
    return reply.value();
}

void SessionDispatcher::update_forecast_weather() {
    emit startUpdateForecastWeahter();
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
        info = "../img/weather/" + key;
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
    mSettings->beginGroup("weather");
    QString cityId = mSettings->value("cityId").toString();
    //cityId为空时，赋默认值为：101250101
    if(cityId.isEmpty()) {
        cityId = QString("101250101");
        mSettings->setValue("cityId", cityId);
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
    if(backGround.isEmpty()) {
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


void SessionDispatcher::change_maincheckbox_status(QString status) {
    emit startChangeMaincheckboxStatus(status);
}


//void SessionDispatcher::tellNullToListTitle(QString emptyFlag, bool status) {
//    emit getNullFlag(emptyFlag, status);
//}


////浏览器判断firefox
//void SessionDispatcher::handler_deb_exists_firefox(QString flag) {
//    emit judge_deb_exists_firefox(flag);
//}

////浏览器判断chromium
//void SessionDispatcher::handler_deb_exists_chromium(QString flag) {
//    emit judge_deb_exists_chromium(flag);
//}
