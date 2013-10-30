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
//    QObject::connect(sessioniface,SIGNAL(scan_complete(QString)),this,SLOT(handler_scan_rubbish(QString)));
//    QObject::connect(sessioniface,SIGNAL(get_speed(QStringList)),this,SLOT(handler_network_speed(QStringList)));
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

//    initWeatherIcons();
}

SessionDispatcher::~SessionDispatcher() {
    mSettings->sync();
    if (mSettings != NULL)
        delete mSettings;

    this->exit_qt();
}

//void SessionDispatcher::handler_network_speed(QStringList speed) {
//    emit finishGetNetworkSpeed(speed);
//    qDebug() << "get speed";
//}

//void SessionDispatcher::handler_scan_rubbish(QString msg) {
//    emit finishScanWork(msg);
//}

void SessionDispatcher::exit_qt() {
    sessioniface->call("exit");
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
    }
    else {
        qDebug() << "get pc_message failed!";
    }
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
    QString dir = QFileDialog::getExistingDirectory(0, tr("选择文件夹"), QDir::homePath(),
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

void SessionDispatcher::get_network_flow_qt() {
    QStringList tmplist;
    tmplist << "Kobe" << "Lee";
    KThread *thread = new KThread(tmplist, sessioniface, "get_network_flow");
    thread->start();
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

void SessionDispatcher::showSkinWidget(/*int window_x, int window_y*/) {
//    this->alert_x = window_x + (mainwindow_width / 2) - (alert_width  / 2);
//    this->alert_y = window_y + mainwindow_height - 400;
//    skin_widget->move(this->alert_x, this->alert_y);
    skin_widget->show();
}

/*-------------------weather forecast-------------------*/
//void SessionDispatcher::initWeatherIcons() {
//    //"../img/weather/d0.gif"
//    weatherIcon.insert("d0.gif", "../img/weather/day/sunny.png");
//    weatherIcon.insert("d1.gif", "../img/weather/day/fewclouds.png");
//    weatherIcon.insert("d2.gif", "../img/weather/day/fewclouds.png");
//    weatherIcon.insert("d3.gif", "../img/weather/day/heavyrain.png");
//    weatherIcon.insert("d4.gif", "../img/weather/day/heavyrain.png");
//    weatherIcon.insert("d5.gif", "../img/weather/day/heavyrain.png");
//    weatherIcon.insert("d6.gif", "../img/weather/day/bigsnow.png");
//    weatherIcon.insert("d7.gif", "../img/weather/day/heavyrain.png");
//    weatherIcon.insert("d8.gif", "../img/weather/day/heavyrain.png");
//    weatherIcon.insert("d9.gif", "../img/weather/day/heavyrain.png");
//    weatherIcon.insert("d10.gif", "../img/weather/day/heavyrain.png");
//    weatherIcon.insert("d11.gif", "../img/weather/day/heavyrain.png");
//    weatherIcon.insert("d12.gif", "../img/weather/day/heavyrain.png");
//    weatherIcon.insert("d13.gif", "../img/weather/day/bigsnow.png");
//    weatherIcon.insert("d14.gif", "../img/weather/day/bigsnow.png");
//    weatherIcon.insert("d15.gif", "../img/weather/day/bigsnow.png");
//    weatherIcon.insert("d16.gif", "../img/weather/day/bigsnow.png");
//    weatherIcon.insert("d17.gif", "../img/weather/day/bigsnow.png");
//    weatherIcon.insert("d18.gif", "../img/weather/day/fog.png");
//    weatherIcon.insert("d19.gif", "../img/weather/day/bigsnow.png");
//    weatherIcon.insert("d20.gif", "../img/weather/day/fog.png");
//    weatherIcon.insert("d21.gif", "../img/weather/day/heavyrain.png");
//    weatherIcon.insert("d22.gif", "../img/weather/day/heavyrain.png");
//    weatherIcon.insert("d23.gif", "../img/weather/day/heavyrain.png");
//    weatherIcon.insert("d24.gif", "../img/weather/day/heavyrain.png");
//    weatherIcon.insert("d25.gif", "../img/weather/day/heavyrain.png");
//    weatherIcon.insert("d26.gif", "../img/weather/day/bigsnow.png");
//    weatherIcon.insert("d27.gif", "../img/weather/day/bigsnow.png");
//    weatherIcon.insert("d28.gif", "../img/weather/day/bigsnow.png");
//    weatherIcon.insert("d29.gif", "../img/weather/day/fog.png");
//    weatherIcon.insert("d30.gif", "../img/weather/day/fog.png");
//    weatherIcon.insert("d31.gif", "../img/weather/day/fog.png");
//    weatherIcon.insert("d53.gif", "../img/weather/day/fog.png");

//    weatherIcon.insert("n0.gif", "../img/weather/night/sunny.png");
//    weatherIcon.insert("n1.gif", "../img/weather/night/fewclouds.png");
//    weatherIcon.insert("n2.gif", "../img/weather/night/fewclouds.png");
//    weatherIcon.insert("n3.gif", "../img/weather/night/heavyrain.png");
//    weatherIcon.insert("n4.gif", "../img/weather/night/heavyrain.png");
//    weatherIcon.insert("n5.gif", "../img/weather/night/heavyrain.png");
//    weatherIcon.insert("n6.gif", "../img/weather/night/bigsnow.png");
//    weatherIcon.insert("n7.gif", "../img/weather/night/heavyrain.png");
//    weatherIcon.insert("n8.gif", "../img/weather/night/heavyrain.png");
//    weatherIcon.insert("n9.gif", "../img/weather/night/heavyrain.png");
//    weatherIcon.insert("n10.gif", "../img/weather/night/heavyrain.png");
//    weatherIcon.insert("n11.gif", "../img/weather/night/heavyrain.png");
//    weatherIcon.insert("n12.gif", "../img/weather/night/heavyrain.png");
//    weatherIcon.insert("n13.gif", "../img/weather/night/bigsnow.png");
//    weatherIcon.insert("n14.gif", "../img/weather/night/bigsnow.png");
//    weatherIcon.insert("n15.gif", "../img/weather/night/bigsnow.png");
//    weatherIcon.insert("n16.gif", "../img/weather/night/bigsnow.png");
//    weatherIcon.insert("n17.gif", "../img/weather/night/bigsnow.png");
//    weatherIcon.insert("n18.gif", "../img/weather/night/fog.png");
//    weatherIcon.insert("n19.gif", "../img/weather/night/bigsnow.png");
//    weatherIcon.insert("n20.gif", "../img/weather/night/fog.png");
//    weatherIcon.insert("n21.gif", "../img/weather/night/heavyrain.png");
//    weatherIcon.insert("n22.gif", "../img/weather/night/heavyrain.png");
//    weatherIcon.insert("n23.gif", "../img/weather/night/heavyrain.png");
//    weatherIcon.insert("n24.gif", "../img/weather/night/heavyrain.png");
//    weatherIcon.insert("n25.gif", "../img/weather/night/heavyrain.png");
//    weatherIcon.insert("n26.gif", "../img/weather/night/bigsnow.png");
//    weatherIcon.insert("n27.gif", "../img/weather/night/bigsnow.png");
//    weatherIcon.insert("n28.gif", "../img/weather/night/bigsnow.png");
//    weatherIcon.insert("n29.gif", "../img/weather/night/fog.png");
//    weatherIcon.insert("n30.gif", "../img/weather/night/fog.png");
//    weatherIcon.insert("n31.gif", "../img/weather/night/fog.png");
//    weatherIcon.insert("n53.gif", "../img/weather/night/fog.png");
//}

void SessionDispatcher::get_forecast_weahter_qt() {
    getCityIdInfo();
    QDBusReply<QMap<QString, QVariant> > reply = sessioniface->call("get_forecast_weahter", initCityId);
    forecastInfo = reply.value();
}

//QMap(("SD", QVariant(QString, "59%") ) ( "WD" ,  QVariant(QString, "南风") ) ( "WS" ,  QVariant(QString, "1级") )
//     ( "city" ,  QVariant(QString, "长沙") ) ( "img1" ,  QVariant(QString, "d1.gif") )
//     ( "img2" ,  QVariant(QString, "n2.gif") ) ( "ptime" ,  QVariant(QString, "08:00") )
//     ( "temp" ,  QVariant(QString, "14") ) ( "temp1" ,  QVariant(QString, "25℃") )
//     ( "temp2" ,  QVariant(QString, "15℃") ) ( "time" ,  QVariant(QString, "08:00") )
//     ( "weather" ,  QVariant(QString, "多云转阴") ) )
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
//    QString rateStr = mSettings->value("rate").toString();
//    if(rateStr.isEmpty()) {
//        mSettings->setValue("rate", "60");
//    }
//    else {
//        rate = rateStr.toInt();
//    }
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
//        info = weatherIcon.value(key);
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

bool SessionDispatcher::showChangeCityDialog(/*int window_x, int window_y*/) {
    ChangeCityDialog *cityDialog = new ChangeCityDialog(mSettings);
    cityDialog-> QWidget::setAttribute(Qt::WA_DeleteOnClose);
    connect(cityDialog, SIGNAL(readyToUpdateWeather()), this, SLOT(handler_change_city()));
//    this->alert_x = window_x + (mainwindow_width / 2) - (alert_width  / 2);
//    this->alert_y = window_y + mainwindow_height - 400;
//    cityDialog->move(this->alert_x, this->alert_y);
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
