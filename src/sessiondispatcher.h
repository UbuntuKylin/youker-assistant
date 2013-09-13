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
#ifndef SESSIONDISPATCHER_H
#define SESSIONDISPATCHER_H

#include <QObject>
#include <QDBusInterface>
#include <QDBusConnection>
#include <QApplication>
#include <QString>
#include <QDeclarativeView>
#include "quibo.h"
#include "modaldialog.h"

class SessionDispatcher : public QObject
{
    Q_OBJECT
//    Q_PROPERTY(QNOTIFY finishSetFont)
//    Q_PROPERTY(QNOTIFY finishScanWork)
public:
    explicit SessionDispatcher(QObject *parent = 0);
    ~SessionDispatcher();
    QDBusInterface *sessioniface;
    Q_INVOKABLE QString get_session_daemon_qt();

    Q_INVOKABLE int scan_history_records_qt();
    Q_INVOKABLE int scan_system_history_qt();
    Q_INVOKABLE int scan_dash_history_qt();
    Q_INVOKABLE QStringList scan_of_same_qt(QString abspath);
    Q_INVOKABLE QStringList scan_of_large_qt(int size, QString abspath);
    Q_INVOKABLE QStringList scan_cookies_records_qt();
    Q_INVOKABLE QStringList scan_unneed_packages_qt();
    Q_INVOKABLE QStringList scan_apt_cruft_qt();
    Q_INVOKABLE QStringList scan_softwarecenter_cruft_qt();
    Q_INVOKABLE void exit_qt();

    Q_INVOKABLE void send_message_dialog(int window_x, int window_y);
    void create_messagedialog(int window_x, int window_y);

    Q_INVOKABLE void send_checkscreen_dialog(int window_x, int window_y);
    void create_checkscreendialog(int window_x, int window_y);

    Q_INVOKABLE void send_warningdialog_msg(QString title, QString content, int window_x, int window_y);
    void create_warningdialog(QString title, QString content, int window_x, int window_y);


    Q_INVOKABLE void set_page_num(int num);
    Q_INVOKABLE int get_page_num();
    int page_num;

    Q_INVOKABLE void setsize_for_large_qt(int size);
    Q_INVOKABLE QString get_home_path();

    //----get system message
    QMap<QString, QVariant> myinfo;
    Q_INVOKABLE void get_system_message_qt();
    Q_INVOKABLE QString get_value(QString);

    Q_INVOKABLE bool set_launcher(bool);
    Q_INVOKABLE QStringList get_themes();
    Q_INVOKABLE void set_theme(QString theme);

    /*-------------------desktop of beauty-------------------*/
    Q_INVOKABLE bool set_show_desktop_icons_qt(bool flag);
    Q_INVOKABLE bool get_show_desktop_icons_qt();
    Q_INVOKABLE bool set_show_homefolder_qt(bool flag);
    Q_INVOKABLE bool get_show_homefolder_qt();
    Q_INVOKABLE bool set_show_network_qt(bool flag);
    Q_INVOKABLE bool get_show_network_qt();
    Q_INVOKABLE bool set_show_trash_qt(bool flag);
    Q_INVOKABLE bool get_show_trash_qt();
    Q_INVOKABLE bool set_show_devices_qt(bool flag);
    Q_INVOKABLE bool get_show_devices_qt();

    /*-------------------unity of beauty-------------------*/
    Q_INVOKABLE bool set_launcher_autohide_qt(bool flag);
    Q_INVOKABLE bool get_launcher_autohide_qt();
    Q_INVOKABLE bool set_launcher_icon_size_qt(int num);
    Q_INVOKABLE int get_launcher_icon_size_qt();
    Q_INVOKABLE bool set_launcher_have_showdesktopicon_qt(bool flag);
    Q_INVOKABLE bool get_launcher_have_showdesktopicon_qt();

    /*-------------------theme of beauty-------------------*/
    Q_INVOKABLE QStringList get_themes_qt();
    Q_INVOKABLE QString get_theme_qt();
    Q_INVOKABLE void set_theme_qt(QString theme);
    Q_INVOKABLE QStringList get_icon_themes_qt();
    Q_INVOKABLE QString get_icon_theme_qt();
    Q_INVOKABLE void set_icon_theme_qt(QString theme);
    Q_INVOKABLE QStringList get_cursor_themes_qt();
    Q_INVOKABLE QString get_cursor_theme_qt();
    Q_INVOKABLE void set_cursor_theme_qt(QString theme);
    Q_INVOKABLE int get_cursor_size_qt();
    Q_INVOKABLE void set_cursor_size_qt(int size);

    /*-------------------fonts of beauty-------------------*/
    Q_INVOKABLE void restore_default_font_signal(QString flag);
    Q_INVOKABLE void show_font_dialog(QString flag);
    Q_INVOKABLE void show_color_dialog();
    Q_INVOKABLE QString show_folder_dialog();


    Q_INVOKABLE QString get_font_qt();
    Q_INVOKABLE bool set_font_qt_default(QString font);
    bool set_font_qt(QString font);
    Q_INVOKABLE QString get_desktop_font_qt();
    Q_INVOKABLE bool set_desktop_font_qt_default();//when is null ,we set a default value
    bool set_desktop_font_qt(QString font);
    Q_INVOKABLE QString get_document_font_qt();
    Q_INVOKABLE bool set_document_font_qt_default(QString font);
    bool set_document_font_qt(QString font);
    Q_INVOKABLE QString get_monospace_font_qt();
    Q_INVOKABLE bool set_monospace_font_qt_default(QString font);
    bool set_monospace_font_qt(QString font);
    Q_INVOKABLE QString get_window_title_font_qt();
    Q_INVOKABLE bool set_window_title_font_qt_default(QString font);
    bool set_window_title_font_qt(QString font);
    Q_INVOKABLE double get_font_zoom_qt();
    Q_INVOKABLE bool set_font_zoom_qt(double zoom);

    /*-------------------scrollbars of beauty-------------------*/
    Q_INVOKABLE bool set_scrollbars_mode_overlay_qt();
    Q_INVOKABLE bool set_scrollbars_mode_legacy_qt();
    Q_INVOKABLE QString get_scrollbars_mode_qt();

    /*-------------------touchpad of beauty-------------------*/
    Q_INVOKABLE bool set_touchpad_enable_qt(bool flag);
    Q_INVOKABLE bool get_touchpad_enable_qt();
    Q_INVOKABLE bool set_touchscrolling_mode_edge_qt();
    Q_INVOKABLE bool set_touchscrolling_mode_twofinger_qt();
    Q_INVOKABLE QString get_touchscrolling_mode_qt();
    Q_INVOKABLE bool set_touchscrolling_use_horizontal_qt(bool flag);
    Q_INVOKABLE bool get_touchscrolling_use_horizontal_qt();

    /*-------------------window of beauty-------------------*/
    Q_INVOKABLE bool set_window_button_align_left_qt();
    Q_INVOKABLE bool set_window_button_align_right_qt();
    Q_INVOKABLE QString get_window_button_align_qt();
    Q_INVOKABLE bool set_menus_have_icons_qt(bool flag);
    Q_INVOKABLE bool get_menus_have_icons_qt();

    /*-------------------sound of beauty-------------------*/
    Q_INVOKABLE void set_login_music_enable_qt(bool flag);
    Q_INVOKABLE bool get_login_music_enable_qt();
    Q_INVOKABLE QString get_sound_theme_qt();
    Q_INVOKABLE void set_sound_theme_qt(QString theme);
    
signals:
    void finishSetFont(QString font_style);//绑定到QML的Handler：onFinishSetFont
    void finishScanWork(QString msg);//绑定到QML的Handler：onFinishScanWork
public slots:
    QString show_signal(QString msg);
//    QString show_signal(QStringList msg);
    void handler_scan_rubbish(QString msg);
private:
    int mainwindow_width;
    int mainwindow_height;
    int alert_width;
    int alert_height;
    //本次alert的x坐标
    int alert_x;
    //保额次alert的y坐标
    int alert_y;
};

#endif // SESSIONDISPATCHER_H
