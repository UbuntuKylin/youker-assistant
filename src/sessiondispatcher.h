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

    Q_PROPERTY(QNOTIFY finishSetFont)
public:
    explicit SessionDispatcher(QObject *parent = 0);

    QDBusInterface *sessioniface;
    Q_INVOKABLE QString get_session_daemon_qt();

    Q_INVOKABLE void send_message_dialog();
    void create_messagedialog();

    Q_INVOKABLE void send_checkscreen_dialog();
    void create_checkscreendialog();

//    void create_dialog(QString mode);
    Q_INVOKABLE void send_warningdialog_msg(QString title, QString content);
    void create_warningdialog(QString title, QString content);


    Q_INVOKABLE void set_page_num(int num);
    Q_INVOKABLE int get_page_num();
    int page_num;

    Q_INVOKABLE QString get_home_path();

    Q_INVOKABLE void set_str(QString str);
    Q_INVOKABLE void del_str(QString str);
    Q_INVOKABLE QString get_str();
    QString notify_str;

    //----get system message
    QMap<QString, QVariant> myinfo;
    Q_INVOKABLE void get_system_message_qt();
    Q_INVOKABLE QString get_value(QString);

    Q_INVOKABLE bool set_launcher(bool);
    Q_INVOKABLE QStringList get_themes();
    Q_INVOKABLE void set_theme(QString theme);
    Q_INVOKABLE void new_object_test();

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
//    Q_INVOKABLE QString get_font_qt();
//    Q_INVOKABLE bool set_font_qt(QString font);
//    Q_INVOKABLE QString get_desktop_font_qt();
//    Q_INVOKABLE bool set_desktop_font_qt(QString font);
//    Q_INVOKABLE QString get_document_font_qt();
//    Q_INVOKABLE bool set_document_font_qt(QString font);
//    Q_INVOKABLE QString get_monospace_font_qt();
//    Q_INVOKABLE bool set_monospace_font_qt(QString font);
//    Q_INVOKABLE QString get_window_title_font_qt();
//    Q_INVOKABLE bool set_window_title_font_qt(QString font);
//    Q_INVOKABLE double get_font_zoom_qt();
//    Q_INVOKABLE bool set_font_zoom_qt(double zoom);

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
public slots:
    QString show_signal(QString msg);
private:
//    QUIBO *qtui;
};

#endif // SESSIONDISPATCHER_H
/*
a 	ARRAY 数组
b 	BOOLEAN 布尔值
d 	DOUBLE IEEE 754双精度浮点数
g 	SIGNATURE 类型签名
i 	INT32 32位有符号整数
n 	INT16 16位有符号整数
o 	OBJECT_PATH 对象路径
q 	UINT16 16位无符号整数
s 	STRING 零结尾的UTF-8字符串
t 	UINT64 64位无符号整数
u 	UINT32 32位无符号整数
v 	VARIANT 可以放任意数据类型的容器，数据中包含类型信息。例如glib中的GValue。
x 	INT64 64位有符号整数
y 	BYTE 8位无符号整数
() 	定义结构时使用。例如"(i(ii))"
{} 	定义键－值对时使用。例如"a{us}"

a表示数组，数组元素的类型由a后面的标记决定。例如：
    "as"是字符串数组。
    数组"a(i(ii))"的元素是一个结构。用括号将成员的类型括起来就表示结构了，结构可以嵌套。
    数组"a{sv}"的元素是一个键－值对。"{sv}"表示键类型是字符串，值类型是VARIANT。
*/
