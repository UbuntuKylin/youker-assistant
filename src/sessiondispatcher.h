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
#include "skinswidget.h"

class QSettings;

class SessionDispatcher : public QObject
{
    Q_OBJECT
public:
    explicit SessionDispatcher(QObject *parent = 0);
    ~SessionDispatcher();
    QDBusInterface *sessioniface;
    //得到SessionDbus的验证值，可以通过其判断该服务是否正在运行
    Q_INVOKABLE QString get_session_daemon_qt();
    //扫描浏览器历史记录
    Q_INVOKABLE int scan_history_records_qt();
    //扫描系统最近打开文件的历史记录
    Q_INVOKABLE int scan_system_history_qt();
    //扫描Dash历史记录
    Q_INVOKABLE int scan_dash_history_qt();
    //扫描同名文件
    Q_INVOKABLE QStringList scan_of_same_qt(QString abspath);
    //扫描大文件
    Q_INVOKABLE QStringList scan_of_large_qt(int size, QString abspath);
    //扫描cookies
    Q_INVOKABLE QStringList scan_cookies_records_qt();
    //扫描不需要的deb包
    Q_INVOKABLE QStringList scan_unneed_packages_qt();
    //扫描apt缓存
    Q_INVOKABLE QStringList scan_apt_cruft_qt();
    //扫描软件中心缓存
    Q_INVOKABLE QStringList scan_softwarecenter_cruft_qt();
    //退出sessiondubs服务
    Q_INVOKABLE void exit_qt();
    //弹出新特性对话框
    Q_INVOKABLE void showFeatureDialog(int window_x, int window_y);
    //弹出屏幕坏点检测对话框
    Q_INVOKABLE void showCheckscreenDialog(int window_x, int window_y);
    //弹出警告提示对话框
    Q_INVOKABLE void showWarningDialog(QString title, QString content, int window_x, int window_y);

    Q_INVOKABLE void set_page_num(int num);
    Q_INVOKABLE int get_page_num();
    int page_num;

    //得到当前登录用户的主目录
    Q_INVOKABLE QString getHomePath();

    //----get system message
    //存放当前系统和桌面信息
    QMap<QString, QVariant> systemInfo;
    //得到当前系统和桌面信息
    Q_INVOKABLE void get_system_message_qt();
    //通过键得到对应的单个信息的值
    Q_INVOKABLE QString getSingleInfo(QString key);

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

    /*-------------------monitorball-------------------*/
    Q_INVOKABLE double get_cpu_percent_qt();
    Q_INVOKABLE QString get_total_memory_qt();
    Q_INVOKABLE QString get_used_memory_qt();
    Q_INVOKABLE QString get_free_memory_qt();
    Q_INVOKABLE QStringList get_network_flow_total_qt();
    Q_INVOKABLE void get_network_flow_qt();
    
    /*-------------------change skin-------------------*/
    Q_INVOKABLE QString setSkin();
    //皮肤对话框
    Q_INVOKABLE void showSkinWidget(int window_x, int window_y);

    /*-------------------weather forecast-------------------*/
    Q_INVOKABLE void get_forecast_weahter_qt();
    Q_INVOKABLE void get_current_weather_qt();
    Q_INVOKABLE QString get_current_pm25_qt();
    Q_INVOKABLE bool update_weather_data_qt();
    Q_INVOKABLE void change_select_city_name_qt(QString cityName);
    QMap<QString, QVariant> forecastInfo;
    QMap<QString, QVariant> currentInfo;
    //通过键得到对应的单个信息的值,flag= forecast/current
    Q_INVOKABLE QString getSingleWeatherInfo(QString key, QString flag);

    //读取天气配置文件
//    QMap<QString, QVariant> confData;
//    Q_INVOKABLE void read_conf_data_qt();

    //列出城市名字
//    Q_INVOKABLE QStringList list_city_names_qt(QString cityName);
    //显示wizard
    Q_INVOKABLE bool showWizardController();

    void initFilterConfigFile();
    void updateStorageInfo();
signals:
    //告知QML那种某种类型的字体样式
//    void finishSetFont(QString font_style);//绑定到QML的Handler：onFinishSetFont
    void notifyFontStyleToQML(QString font_style);
    //扫描完成后发送信号
//    void finishScanWork(QString msg);
//    void finishGetNetworkSpeed(QStringList speed);
    void startChangeQMLSkin(QString skinName);//发送开始更换QML界面皮肤的信号
public slots:
//    QString show_signal(QString msg);
    //扫描完成后触发finishScanWork信号
//    void handler_scan_rubbish(QString msg);
//    void handler_network_speed(QStringList speed);
    void handler_change_skin(QString skinName);
    //设置天气配置文件
//    void write_conf_data_qt(QString key, QString value);
private:
    int mainwindow_width;
    int mainwindow_height;
    int alert_width;
    int alert_height;
    //本次alert的x坐标
    int alert_x;
    //保额次alert的y坐标
    int alert_y;

    //皮肤对话框对象
    SkinsWidget *skin_widget;

    QSettings * mSettings;
    QString initCityId;
};

#endif // SESSIONDISPATCHER_H
