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
#include <QColorDialog>
#include <QColor>
#include <QFileDialog>
SessionDispatcher::SessionDispatcher(QObject *parent) :
    QObject(parent)
{
    sessioniface = new QDBusInterface("com.ubuntukylin.IhuSession",
                               "/",
                               "com.ubuntukylin.IhuSession",
                               QDBusConnection::sessionBus());
    QObject::connect(sessioniface,SIGNAL(pc_msg(QString)),this,SLOT(show_signal(QString)));
//    QObject::connect(sessioniface,SIGNAL(pc_msg(QStringList)),this,SLOT(show_signal(QStringList)));
    QObject::connect(sessioniface,SIGNAL(scan_complete(QString)),this,SLOT(handler_scan_rubbish(QString)));
    page_num = 0;

    this->mainwindow_width = 850;
    this->mainwindow_height = 600;
    this->alert_width = 329;
    this->alert_height = 195;
}

SessionDispatcher::~SessionDispatcher()
{
    this->exit_qt();
}

void SessionDispatcher::handler_scan_rubbish(QString msg)
{
    emit finishScanWork(msg);
}
void SessionDispatcher::exit_qt()
{
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

QString SessionDispatcher::get_home_path() {
    QString homepath = QDir::homePath();
    return homepath;
}

void SessionDispatcher::setsize_for_large_qt(int size) {
    sessioniface->call("setsize_for_large", size);
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
        myinfo = value;
    }
    else {
        qDebug() << "get pc_message failed!";
    }
}

//----------------message dialog--------------------
void SessionDispatcher::send_message_dialog(int window_x, int window_y) {
    create_messagedialog(window_x, window_y);
}
void SessionDispatcher::create_messagedialog(int window_x, int window_y) {
    MessageDialog *dialog = new MessageDialog();
    this->alert_x = window_x + (mainwindow_width / 2) - (alert_width  / 2);
    this->alert_y = window_y + mainwindow_height - 400;
    dialog->move(this->alert_x, this->alert_y);
//    dialog->move ((QApplication::desktop()->width() - dialog->width())/2,(QApplication::desktop()->height() - dialog->height())/2);
    dialog->show();
}
//------------------------------------

//----------------checkscreen dialog--------------------
void SessionDispatcher::send_checkscreen_dialog(int window_x, int window_y)
{
    create_checkscreendialog(window_x, window_y);
}
void SessionDispatcher::create_checkscreendialog(int window_x, int window_y) {
    ModalDialog *dialog = new ModalDialog;
    this->alert_x = window_x + (mainwindow_width / 2) - (alert_width  / 2);
    this->alert_y = window_y + mainwindow_height - 400;
    dialog->move(this->alert_x, this->alert_y);
    dialog->setModal(true);
    dialog->show();
}
//------------------------------------

void SessionDispatcher::send_warningdialog_msg(QString title, QString content, int window_x, int window_y) {
    create_warningdialog(title, content, window_x, window_y);
}
void SessionDispatcher::create_warningdialog(QString title, QString content, int window_x, int window_y) {

    WarningDialog *dialog = new WarningDialog(title, content);
    this->alert_x = window_x + (mainwindow_width / 2) - (alert_width  / 2);
    this->alert_y = window_y + mainwindow_height - 400;
    dialog->move(this->alert_x, this->alert_y);
    dialog->exec();
//    dialog->setModal(true);
//    dialog->show();
}
//------------------------------------

QString SessionDispatcher::get_value(QString key)
{
    QVariant tt = myinfo.value(key);
    return tt.toString();
}

QString SessionDispatcher::show_signal(QString msg) {
    return msg;
}

bool SessionDispatcher::set_launcher(bool flag) {
    QDBusReply<bool> reply = sessioniface->call("set_launcher_autohide", flag);
    return true;
}

QStringList SessionDispatcher::get_themes() {
    QDBusReply<QStringList> reply = sessioniface->call("get_sys_themes");
    return reply.value();
//    if (reply.isValid()) {
//        QStringList value = reply.value();
//        return reply.value();
//    }
//    else {
//        qDebug() << "get thems msg1 failed!";
//    }
}


void SessionDispatcher::set_theme(QString theme) {
    sessioniface->call("set_sys_theme", theme);
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
    emit finishSetFont(flag); //font_style
}

void SessionDispatcher::show_font_dialog(QString flag) {
    bool ok;
    const QFont& font = QFontDialog::getFont(&ok, 0);
    if(ok)
    {
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

        emit finishSetFont(flag); //font_style
    }
}

void SessionDispatcher::show_color_dialog() {
    const QColor& color = QColorDialog::getColor(Qt::white, 0);
    if(color.isValid())
    {
        qDebug() << "OK-----------";
//        palette.setColor(QPalette::Base, color);
//        displayTextEdit->setPalette(palette);
    }
    else
        qDebug() << "Quit-----------";

}


QString SessionDispatcher::show_folder_dialog() {
    QString dir = QFileDialog::getExistingDirectory(0, tr("打开文件夹"), "/home",
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
