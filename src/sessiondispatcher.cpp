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

    skin_widget = new SkinsWidget();
    connect(skin_widget, SIGNAL(skinSignalToQML(QString)), this, SLOT(handler_change_skin(QString)));
}

SessionDispatcher::~SessionDispatcher() {
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
    QString homepath = QDir::homePath();
    Util::writeInit(QString(homepath + "/youker.ini"), QString("skin"), skinName);
    //发送开始更换QML界面皮肤的信号
    emit startChangeQMLSkin(skinName);
}

QString SessionDispatcher::setSkin() {
    QString homepath = QDir::homePath();
    QString skinName;
    bool is_read = Util::readInit(QString(homepath + "/youker.ini"), QString("skin"), skinName);
    if(is_read) {
        if(skinName.isEmpty()) {
            skinName = QString("0_bg");
        }
    }
    else {
        skinName = QString("0_bg");
    }
    return skinName;
}

void SessionDispatcher::showSkinWidget(int window_x, int window_y) {
    this->alert_x = window_x + (mainwindow_width / 2) - (alert_width  / 2);
    this->alert_y = window_y + mainwindow_height - 400;
    skin_widget->move(this->alert_x, this->alert_y);
    skin_widget->show();
}

/*-------------------weather forecast-------------------*/
//QMap(("city", QVariant(QString, "长沙") )
//     ( "date_y" ,  QVariant(QString, "2013年10月17日") )
//     ( "fchh" ,  QVariant(QString, "11") )
//     ( "fl1" ,  QVariant(QString, "小于3级") )
//     ( "fl2" ,  QVariant(QString, "小于3级") )
//     ( "fl3" ,  QVariant(QString, "小于3级") )
//     ( "fl4" ,  QVariant(QString, "小于3级") )
//     ( "fl5" ,  QVariant(QString, "小于3级") )
//     ( "fl6" ,  QVariant(QString, "小于3级") )
//     ( "fx1" ,  QVariant(QString, "微风") )
//     ( "fx2" ,  QVariant(QString, "微风") )
//     ( "img1" ,  QVariant(QString, "7") )
//     ( "img10" ,  QVariant(QString, "99") )
//     ( "img11" ,  QVariant(QString, "1") )
//     ( "img12" ,  QVariant(QString, "99") )
//     ( "img2" ,  QVariant(QString, "2") )
//     ( "img3" ,  QVariant(QString, "7") )
//     ( "img4" ,  QVariant(QString, "2") )
//     ( "img5" ,  QVariant(QString, "2") )
//     ( "img6" ,  QVariant(QString, "1") )
//     ( "img7" ,  QVariant(QString, "2") )
//     ( "img8" ,  QVariant(QString, "1") )
//     ( "img9" ,  QVariant(QString, "2") )
//     ( "img_single" ,  QVariant(QString, "7") )
//     ( "img_title1" ,  QVariant(QString, "小雨") )
//     ( "img_title10" ,  QVariant(QString, "阴") )
//     ( "img_title11" ,  QVariant(QString, "多云") )
//     ( "img_title12" ,  QVariant(QString, "多云") )
//     ( "img_title2" ,  QVariant(QString, "阴") )
//     ( "img_title3" ,  QVariant(QString, "小雨") )
//     ( "img_title4" ,  QVariant(QString, "阴") )
//     ( "img_title5" ,  QVariant(QString, "阴") )
//     ( "img_title6" ,  QVariant(QString, "多云") )
//     ( "img_title7" ,  QVariant(QString, "阴") )
//     ( "img_title8" ,  QVariant(QString, "多云") )
//     ( "img_title9" ,  QVariant(QString, "阴") )
//     ( "img_title_single" ,  QVariant(QString, "小雨") )
//     ( "index" ,  QVariant(QString, "较舒适") )
//     ( "index48" ,  QVariant(QString, "较舒适") )
//     ( "index48_d" ,  QVariant(QString, "建议着薄外套、开衫牛仔衫裤等服装。年老体弱者应适当添加衣物，宜着夹克衫、薄毛衣等。") )
//     ( "index_ag" ,  QVariant(QString, "易发") )
//     ( "index_cl" ,  QVariant(QString, "较不宜") )
//     ( "index_co" ,  QVariant(QString, "舒适") )
//     ( "index_d" ,  QVariant(QString, "建议着薄外套、开衫牛仔衫裤等服装。年老体弱者应适当添加衣物，宜着夹克衫、薄毛衣等。") )
//     ( "index_ls" ,  QVariant(QString, "不宜") )
//     ( "index_tr" ,  QVariant(QString, "适宜") )
//     ( "index_uv" ,  QVariant(QString, "最弱") )
//     ( "index_xc" ,  QVariant(QString, "不宜") )
//     ( "temp1" ,  QVariant(QString, "18℃~13℃") )
//     ( "temp2" ,  QVariant(QString, "19℃~14℃") )
//     ( "temp3" ,  QVariant(QString, "22℃~15℃") )
//     ( "temp4" ,  QVariant(QString, "24℃~16℃") )
//     ( "temp5" ,  QVariant(QString, "24℃~16℃") )
//     ( "temp6" ,  QVariant(QString, "24℃~15℃") )
//     ( "weather1" ,  QVariant(QString, "小雨转阴") )
//     ( "weather2" ,  QVariant(QString, "小雨转阴") )
//     ( "weather3" ,  QVariant(QString, "阴转多云") )
//     ( "weather4" ,  QVariant(QString, "阴转多云") )
//     ( "weather5" ,  QVariant(QString, "阴") )
//     ( "weather6" ,  QVariant(QString, "多云") )
//     ( "wind1" ,  QVariant(QString, "微风") )
//     ( "wind2" ,  QVariant(QString, "微风") )
//     ( "wind3" ,  QVariant(QString, "微风") )
//     ( "wind4" ,  QVariant(QString, "北风小于3级") )
//     ( "wind5" ,  QVariant(QString, "北风小于3级") )
//     ( "wind6" ,  QVariant(QString, "北风小于3级") ) )
void SessionDispatcher::get_forecast_weahter_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = sessioniface->call("get_forecast_weahter");
    forecastInfo = reply.value();


//    qDebug() << forecastInfo;
}

//QMap(("SD", QVariant(QString, "83%") )
//     ( "WD" ,  QVariant(QString, "西北风") )
//     ( "WS" ,  QVariant(QString, "2级") )
//     ( "city" ,  QVariant(QString, "长沙") )
//     ( "img1" ,  QVariant(QString, "d7.gif") )
//     ( "img2" ,  QVariant(QString, "n2.gif") )
//     ( "ptime" ,  QVariant(QString, "11:00") )
//     ( "temp" ,  QVariant(QString, "12") )
//     ( "temp1" ,  QVariant(QString, "18℃") )
//     ( "temp2" ,  QVariant(QString, "13℃") )
//     ( "time" ,  QVariant(QString, "17:00") )
//     ( "weather" ,  QVariant(QString, "小雨转阴") ) )
void SessionDispatcher::get_current_weather_qt() {
    QDBusReply<QMap<QString, QVariant> > reply = sessioniface->call("get_current_weather");
    currentInfo = reply.value();
}

//QMap(("error", QVariant(QString, "Sorry，您这个小时内的API请求次数用完了，休息一下吧！") ) )
//{u'pm2_5': 84, u'area': u'\u957f\u6c99', u'quality': u'\u8f7b\u5ea6\u6c61\u67d3',
//u'station_code': None, u'time_point': #u'2013-10-18T09:00:00Z',
//    u'pm2_5_24h': 0, u'position_name': None, u'aqi': 122, u'primary_pollutant': None}
QString SessionDispatcher::get_current_pm25_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_current_pm25");
    return reply.value();
}

bool SessionDispatcher::update_weather_data_qt() {
    QDBusReply<bool> reply = sessioniface->call("update_weather_data");
    return reply.value();
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
    return info.toString();
}
