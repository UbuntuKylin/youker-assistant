/*
 * Copyright (C) 2013 ~ 2015 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  Kobe Lee    xiangli@ubuntukylin.com/kobe24_lixiang@126.com
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
#include <QtDBus>
#include <QDBusInterface>
#include <QDBusConnection>
//#include "kthread.h"

class SessionDispatcher : public QObject
{
    Q_OBJECT
public:
    explicit SessionDispatcher(QObject *parent = 0);
    ~SessionDispatcher();
    void getAutoStartAppStatus();
    bool getSingleAutoStartStatus(QString abs_path);
    void changeAutoStartAppStatus(QString appName);
    QStringList checkNewVersion();
    void runApp(QString pkgname);
    void scanSystemCleanerItems(QMap<QString, QVariant> data);
    void check_user_qt();
    //打开文件夹
    void open_folder_qt(QString path);
//    bool judge_camera_qt();
//    void call_camera_qt();
    QMap<QString, QVariant> batteryInfo;
    bool judge_power_is_exists_qt();
    QMap<QString, QVariant> read_battery_info_qt();

    QString get_os_release_qt();

    bool submit_uk_pingback();

    //弹出登录框
    void popup_login_dialog();
    void popup_register_dialog();
    //退出登录
    void logout_ubuntukylin_account();

    //得到SessionDbus的验证值，可以通过其判断该服务是否正在运行
//    QString get_session_daemon_qt();

    //退出sessiondubs服务
    void exit_qt();
    //得到安装操作系统的语言版本
//    QString get_locale_version();
//    //得到当前登录用户的主目录
    QString getHomePath();

    //----get system message
    //存放当前系统和桌面信息
    QMap<QString, QVariant> systemInfo;
    //得到当前系统和桌面信息
    QMap<QString, QVariant>  get_system_message_qt();

//    void set_default_launcher_have_showdesktopicon_qt();

//    /*-------------------desktop of beauty-------------------*/
    bool set_show_desktop_icons_qt(bool flag);
    bool get_show_desktop_icons_qt();
    bool set_show_computer_qt(bool flag);
    bool get_show_computer_qt();
    bool set_show_homefolder_qt(bool flag);
    bool get_show_homefolder_qt();
    bool set_show_network_qt(bool flag);
    bool get_show_network_qt();
    bool set_show_trash_qt(bool flag);
    bool get_show_trash_qt();
    bool set_show_devices_qt(bool flag);
    bool get_show_devices_qt();

    void start_check_source_useable_qt();
//    Q_INVOKABLE bool get_show_cinnamon_desktop_icons_qt();
//    Q_INVOKABLE bool set_show_cinnamon_desktop_icons_qt(bool flag);
//    Q_INVOKABLE bool get_show_cinnamon_computer_qt();
//    Q_INVOKABLE bool set_show_cinnamon_computer_qt(bool flag);
//    Q_INVOKABLE bool get_show_cinnamon_homefolder_qt();
//    Q_INVOKABLE bool set_show_cinnamon_homefolder_qt(bool flag);
//    Q_INVOKABLE bool get_show_cinnamon_network_qt();
//    Q_INVOKABLE bool set_show_cinnamon_network_qt(bool flag);
//    Q_INVOKABLE bool get_show_cinnamon_trash_qt();
//    Q_INVOKABLE bool set_show_cinnamon_trash_qt(bool flag);
//    Q_INVOKABLE bool get_show_cinnamon_devices_qt();
//    Q_INVOKABLE bool set_show_cinnamon_devices_qt(bool flag);

    /*-------------------unity of beauty-------------------*/
    bool set_launcher_autohide_qt(bool flag);
    bool get_launcher_autohide_qt();
    bool set_launcher_icon_size_qt(int num);
    int get_launcher_icon_size_qt();
    bool set_launcher_have_showdesktopicon_qt(bool flag);
    bool get_launcher_have_showdesktopicon_qt();
    //-----------------mate of beauty--------------------*/
    bool set_mate_panel_autohide_qt(QString positon, bool flag);
    bool get_mate_panel_autohide_qt(QString positon);
    bool set_mate_panel_icon_size_qt(QString positon, int num);
    int get_mate_panel_icon_size_qt(QString positon);

    //透明度
    double get_launcher_transparency_qt();
    bool set_launcher_transparency_qt(double opacity);
    //图标背景
    QStringList get_all_launcher_icon_colourings_qt();
    int get_launcher_icon_colouring_qt();
    bool set_launcher_icon_colouring_qt(int colouring);
    //Launcher position
    QString get_current_launcher_position_qt();
    QStringList get_all_launcher_position_qt();
    bool set_launcher_position_qt(QString position);
    //Dash背景模糊类型
    int get_dash_blur_experimental_qt();
    bool set_dash_blur_experimental_qt(int blur);
    //面板菜单透明度
    double get_panel_transparency_qt();
    bool set_panel_transparency_qt(double opacity);
    //日期时间格式
    QStringList get_all_time_format_qt();
    QString get_time_format_qt();
    bool set_time_format_qt(QString format);
    bool get_show_seconds_qt();
    bool set_show_seconds_qt(bool flag);
    bool get_show_week_qt();
    bool set_show_week_qt(bool flag);
    bool get_show_date_qt();
    bool set_show_date_qt(bool flag);
    //电源
    QStringList get_all_power_icon_policy_qt();
    QString get_power_icon_policy_qt();
    bool set_power_icon_policy_qt(QString flag);
    bool get_show_power_time_qt();
    bool set_show_power_time_qt(bool flag);
    bool get_show_power_percentage_qt();
    bool set_show_power_percentage_qt(bool flag);


    bool get_show_apps_qt();
    bool set_show_apps_qt(bool flag);
    bool get_show_desktop_qt();
    bool set_show_desktop_qt(bool flag);
    bool get_show_icon_qt();
    bool set_show_icon_qt(bool flag);
    bool get_show_places_qt();
    bool set_show_places_qt(bool flag);

    /*-------------------theme of beauty-------------------*/
    QStringList get_themes_qt();
    QString get_theme_qt();
    void set_theme_qt(QString theme);
    QStringList get_icon_themes_qt();
    QString get_icon_theme_qt();
    void set_icon_theme_qt(QString theme);
    QStringList get_cursor_themes_qt();
    QString get_cursor_theme_qt();
    void set_cursor_theme_qt(QString theme);
    int get_cursor_size_qt();
    void set_cursor_size_qt(int size);
    //window theme
//    QStringList get_window_themes_qt();
//    QString get_current_window_theme_qt();
//    void set_window_theme_qt(QString theme);

//    /*-------------------fonts of beauty-------------------*/
    QString get_default_font_string_qt(QString schema, QString key);
    bool set_default_font_string_qt(QString schema, QString key, QString type);

    QString get_font_qt();
//    Q_INVOKABLE bool set_font_qt_default(QString font);
    bool set_font_qt(QString font);
    QString get_desktop_font_qt();
    bool set_desktop_font_qt_default();//when is null ,we set a default value
    bool set_desktop_font_qt(QString font);
    QString get_document_font_qt();
//    Q_INVOKABLE bool set_document_font_qt_default(QString font);
    bool set_document_font_qt(QString font);
    QString get_monospace_font_qt();
//    Q_INVOKABLE bool set_monospace_font_qt_default(QString font);
    bool set_monospace_font_qt(QString font);
    QString get_window_title_font_qt();
//    Q_INVOKABLE bool set_window_title_font_qt_default(QString font);
    bool set_window_title_font_qt(QString font);
    double get_font_zoom_qt();
    bool set_font_zoom_qt(double zoom);

    QStringList get_smooth_style_list_qt();
    QString get_smooth_style_qt();
    bool set_smooth_style_qt(QString style);
    QStringList get_antialiasing_style_list_qt();
    QString get_antialiasing_style_qt();
    bool set_antialiasing_style_qt(QString style);

    /*-------------------scrollbars of beauty-------------------*/
    bool set_scrollbars_mode_overlay_qt();
    bool set_scrollbars_mode_legacy_qt();
    QString get_scrollbars_mode_qt();

    /*-------------------touchpad of beauty-------------------*/
    bool set_touchpad_enable_qt(bool flag);
    bool get_touchpad_enable_qt();
    bool set_touchscrolling_mode_disabled_qt();
    bool set_touchscrolling_mode_edge_qt();
    bool set_touchscrolling_mode_twofinger_qt();
    QString get_touchscrolling_mode_qt();
    bool set_touchscrolling_use_horizontal_qt(bool flag);
    bool get_touchscrolling_use_horizontal_qt();

    int get_mate_touchscrolling_mode_qt();
    bool set_mate_touchscrolling_mode_qt(int value);

    /*-------------------window of beauty-------------------*/
    void set_window_button_align_left_qt();
    void set_window_button_align_right_qt();
    QString get_window_button_align_qt();
    bool set_menus_have_icons_qt(bool flag);
    bool get_menus_have_icons_qt();
    QStringList get_titlebar_wheel_qt();
    QString get_current_titlebar_wheel_qt();
    void set_titlebar_wheel_qt(QString value);
    QStringList get_titlebar_options_qt();
    QString get_current_titlebar_double_qt();
    void set_titlebar_double_qt(QString value);
//    QStringList get_titlebar_middle_qt();
    QString get_current_titlebar_middle_qt();
    void set_titlebar_middle_qt(QString value);
//    QStringList get_titlebar_right_qt();
    QString get_current_titlebar_right_qt();
    void set_titlebar_right_qt(QString value);

    /*-------------------sound of beauty-------------------*/
    void set_sound_event_enable_qt(bool flag);
    bool get_sound_event_enable_qt();
    void set_input_feedback_sounds_enable_qt(bool flag);
    bool get_input_feedback_sounds_enable_qt();
    void set_login_music_enable_qt(bool flag);
    bool get_login_music_enable_qt();
    QString get_sound_theme_qt();
    void set_sound_theme_qt(QString theme);

    /*-------------------filemanager of beauty-------------------*/
    void set_location_replace_pathbar_qt(bool flag);
    bool get_location_replace_pathbar_qt();
    void set_auto_mount_media_qt(bool flag);
    bool get_auto_mount_media_qt();
    void set_auto_open_folder_qt(bool flag);
    bool get_auto_open_folder_qt();
    void set_prompt_autorun_programs_qt(bool flag);
    bool get_prompt_autorun_programs_qt();
    void set_thumbnail_icon_size_qt(int size);
    int get_thumbnail_icon_size_qt();
    void set_thumbnail_cache_time_qt(int value);
    int get_thumbnail_cache_time_qt();
    void set_thumbnail_cache_size_qt(int size);
    int get_thumbnail_cache_size_qt();
    QString access_current_desktop_qt();
    QString access_current_machine_qt();
//    Q_INVOKABLE QString judge_desktop_is_unity_qt();
//    Q_INVOKABLE QString judge_desktop_is_cinnamon_qt();
    //一键清理扫描
    void onekey_scan_function_qt(QStringList selectedList);

    //-------------------conserve energe----------------
    void adjust_screen_gamma_qt(double gamma);
    double get_screen_gamma_qt();
    QStringList get_idle_delay_list_qt();
    QString get_current_idle_delay_qt();
    void set_current_idle_delay_qt(int value);
    bool get_lock_enabled_qt();
    void set_lock_enabled_qt(bool value);
    QStringList get_lock_delay_list_qt();
    QString get_current_lock_delay_qt();
    void set_current_lock_delay_qt(int value);

    QStringList get_sleep_timeout_list_qt();
    QString get_current_critical_low_qt();
    void set_current_critical_low_qt(QString value);
    QString get_current_lid_battery_qt();
    void set_current_lid_battery_qt(QString value);
    QString get_current_lid_ac_qt();
    void set_current_lid_ac_qt(QString value);
    QString get_current_sleep_timeout_display_battery_qt();
    void set_current_sleep_timeout_display_battery_qt(int value);
    QString get_current_sleep_timeout_display_ac_qt();
    void set_current_sleep_timeout_display_ac_qt(int value);
    QString get_current_sleep_timeout_battery_qt();
    void set_current_sleep_timeout_battery_qt(int value);
    QString get_current_sleep_timeout_ac_qt();
    void set_current_sleep_timeout_ac_qt(int value);


signals:
    void tellAutoModel(const QStringList &data);
    void showAutoModel();
    void finishScanWork(QString msg);
    void isScanning(QString msg);
    void tellCleanerDetailData(const QStringList &data);
    void tellCleanerDetailStatus(const QString &status);
    void tellCleanerDetailError(const QString &status);
    void tellScanResult(QString flag, QString msg);
    void ssoSuccessSignal(QString displayName, QString emailAddress);
    void ssoLoginLogoutSignal(bool loginFlag);

    void bool_value_notify(QString key, bool value);
    void int_value_notify(QString key, int value);
    void double_value_notify(QString key, double value);
    void string_value_notify(QString key, QString value);

    void receive_source_list_signal(bool result);

public slots:
    void handlerAutoManageData(QStringList data);
//    void handlerAutoManageData(const QVariantMap &data);

    void handlerAutoManageStatus(QString status);
    void handlerAutoManageError(QString status);

    void handlerScanCleanerData(QStringList data);
    void handlerScanCleanerStatus(QString status);
    void handlerScanCleanerError(QString status);

    //扫描完成槽函数
    void handler_scan_complete(QString msg);
    //扫描过程的函数
    void handler_scan_process(QString msg);
    //扫描的总数
    void handler_total_data_transmit(QString flag, QString msg);
    void handlerYoukerID(QString displayName, QString emailAddress);
    void handlerLogoutSuccess();
    void handlerLoginFail();

    // notify changes
    void handler_notify_boolean(QString key, bool value);
    void handler_notify_int(QString key, int value);
    void handler_notify_double(QString key, double value);
    void handler_notify_string(QString key, QString value);

private:
    QDBusInterface *sessioniface;
    /*KThread *check_thread;
    KThread *scan_thread;
    KThread *onekey_scan_thread;*/
};

#endif // SESSIONDISPATCHER_H
