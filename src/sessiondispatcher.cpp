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
#include "modelessdialog.h"
#include "warningdialog.h"
#include <QDesktopWidget>
#include <QDeclarativeContext>
#include <QFontDialog>
#include <QColorDialog>
#include <QColor>
SessionDispatcher::SessionDispatcher(QObject *parent) :
    QObject(parent)
{
    sessioniface = new QDBusInterface("com.ubuntukylin.IhuSession",
                               "/",
                               "com.ubuntukylin.IhuSession",
                               QDBusConnection::sessionBus());

    QObject::connect(sessioniface,SIGNAL(pc_msg(QString)),this,SLOT(show_signal(QString)));
//    QObject::connect(sessioniface,SIGNAL(receive_dialog_msg()), this, SLOT(create_dialog()));
//    QDBusReply<QStringList> reply = sessioniface->call("get_themes");
//    if (reply.isValid()) {
//        QStringList value = reply.value();

//        qDebug() << value;
//    }
//    else {
//        qDebug() << "get thems msg failed!";
//    }


    QDBusReply<QMap<QString, QVariant> > reply = sessioniface->call("get_system_message");
    if (reply.isValid()) {
        QMap<QString, QVariant> value = reply.value();
        myinfo = value;
//        qDebug() << myinfo;
    }
    else {
        qDebug() << "get pc_message failed!";
    }

    notify_str = "";



//    QDBusReply<QString> reply1 = sessioniface->call("get_theme");
//    qDebug() << "12345677654321";
//    qDebug() << reply1.value();
//    qDebug() << "7654321";

}


void SessionDispatcher::send_dialog_msg(QString mode) {
    qDebug() << "3333333333333333";
//    emit receive_dialog_msg();
    create_dialog(mode);
    qDebug() << "44444444444444444";
}

void SessionDispatcher::send_warningdialog_msg(QString msg) {
    create_warningdialog(msg);
}

void SessionDispatcher::set_str(QString str)
{
    notify_str += str;
}

void SessionDispatcher::del_str(QString str)
{
    notify_str.replace(QString(str), QString(""));
}

QString SessionDispatcher::get_str()
{
    return notify_str;
}


QString SessionDispatcher::get_value(QString key)
{
    QVariant tt = myinfo.value(key);
    return tt.toString();
}

QString SessionDispatcher::show_signal(QString msg) {
    qDebug() << "*****signal******";
    qDebug() << msg;
    return msg;
}

void SessionDispatcher::create_dialog(QString mode) {
    if (mode == "modal") {
//        qDebug() << "555555555555";
        ModalDialog *dialog = new ModalDialog;
//        qDebug() << "6666666666666";
//        qDebug() << "77777777777";
        dialog->setModal(true);
        dialog->show();
//        qDebug() << "888888888888888";
    }
    else if (mode == "modeless") {
//        qDebug() << "555555555555";
        ModelessDialog *dialog = new ModelessDialog;
        dialog->show();
        dialog->move ((QApplication::desktop()->width() - dialog->width())/2,(QApplication::desktop()->height() - dialog->height())/2);
//        qDebug() << "6666666666666";
    }

}

void SessionDispatcher::create_warningdialog(QString msg) {

    WarningDialog *dialog = new WarningDialog(msg);
//    qDebug() << "77777777777";
    dialog->exec();
//    dialog->setModal(true);
//    dialog->show();
//    qDebug() << "888888888888888";

}


bool SessionDispatcher::set_launcher(bool flag) {
    QDBusReply<bool> reply = sessioniface->call("set_launcher_autohide", flag);
    return true;
}

QStringList SessionDispatcher::get_themes() {
    QDBusReply<QStringList> reply = sessioniface->call("get_sys_themes");
    if (reply.isValid()) {
        QStringList value = reply.value();
//        myinfo = value;
        qDebug() << value;
        return reply.value();
    }
    else {
        qDebug() << "get thems msg1 failed!";
    }
}


void SessionDispatcher::set_theme(QString theme) {
    QDBusReply<void> reply = sessioniface->call("set_sys_theme", theme);
}


void SessionDispatcher::new_object_test() {
//    delete this->qtui;
//    this->qtui = new QUIBO();
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
//    qDebug() << "1234567890";
//    qDebug() << reply.value();
    return reply.value();
}

QString SessionDispatcher::get_theme_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_theme");
    return reply.value();
}
void SessionDispatcher::set_theme_qt(QString theme) {
    QDBusReply<void> reply = sessioniface->call("set_theme", theme);
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
    QDBusReply<void> reply = sessioniface->call("set_icon_theme", theme);
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
    QDBusReply<void> reply = sessioniface->call("set_cursor_theme", theme);
}
int SessionDispatcher::get_cursor_size_qt() {
    QDBusReply<int> reply = sessioniface->call("get_cursor_size");
    return reply.value();
}
void SessionDispatcher::set_cursor_size_qt(int size) {
    QDBusReply<void> reply = sessioniface->call("set_cursor_size", size);
}


/*-----------------------------font of beauty-----------------------------*/
QString SessionDispatcher::get_font_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_font");
    return reply.value();
}
bool SessionDispatcher::set_font_qt(QString font) {
    QDBusReply<bool> reply = sessioniface->call("set_font", font);
    return reply.value();
}
QString SessionDispatcher::get_desktop_font_qt() {
    QDBusReply<void> reply = sessioniface->call("get_desktop_font");
}
bool SessionDispatcher::set_desktop_font_qt(QString font) {
    QDBusReply<bool> reply = sessioniface->call("set_desktop_font", font);
    return reply.value();
}
QString SessionDispatcher::get_document_font_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_document_font");
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
bool SessionDispatcher::set_monospace_font_qt(QString font) {
    QDBusReply<bool> reply = sessioniface->call("set_monospace_font", font);
    return reply.value();
}
QString SessionDispatcher::get_window_title_font_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_window_title_font");
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


void SessionDispatcher::show_font_dialog(QString flag) {
//    QFontDialog *dialog = new QFontDialog;
//    bool ok;
//    QFont font = QFontDialog::getFont(&ok, QFont("Times", 12),dialog);
//    dialog->setFont(font);
//    qDebug()<<font.key();
//    dialog->show();


    bool ok;
//    const QFont& font = QFontDialog::getFont(&ok, get_font_qt());
    const QFont& font = QFontDialog::getFont(&ok, 0);
    if(ok)
    {
        qDebug() << "OK-----------";
        qDebug() << font.family();
        set_font_qt(font.family());//set font
//        displayTextEdit->setFont(font);
    }
    else
        qDebug() << "Quit-----------";

}

void SessionDispatcher::show_color_dialog() {
//    QColorDialog *dialog = new QColorDialog;
//    QColor color;
//    color = QColorDialog::getColor(Qt::green, dialog, "Select Color", QColorDialog::DontUseNativeDialog);
//    dialog->setPalette(QPalette(color));
//    dialog->show();


//    QPalette palette = displayTextEdit->palette();
//    const QColor& color = QColorDialog::getColor(palette.color(QPalette::Base), this);
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
    QDBusReply<bool> reply = sessioniface->call("set_login_music_enable", flag);
}
bool SessionDispatcher::get_login_music_enable_qt() {
    QDBusReply<bool> reply = sessioniface->call("get_login_music_enable");
    return reply.value();
}
QStringList SessionDispatcher::get_sound_themes_qt() {
    QDBusReply<QStringList> reply = sessioniface->call("get_sound_themes");
    return reply.value();
}

QString SessionDispatcher::get_sound_theme_qt() {
    QDBusReply<QString> reply = sessioniface->call("get_sound_theme");
    return reply.value();
}
void SessionDispatcher::set_sound_theme_qt(QString theme) {
    QDBusReply<bool> reply = sessioniface->call("set_sound_theme", theme);
}
