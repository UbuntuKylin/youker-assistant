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
//#include "quibo.h"
//#include "modaldialog.h"
//#include "newcharacter.h"
//#include "selectdialog.h"
//#include "httpdownload.h"
#include "kthread.h"

class QSettings;

class SessionDispatcher : public QObject
{
    Q_OBJECT
public:
    explicit SessionDispatcher(QObject *parent = 0);
    ~SessionDispatcher();
    QDBusInterface *sessioniface;
    void getAutoStartAppStatus();
    void changeAutoStartAppStatus(QString appName);
    QString checkNewVersion();

    //new scan method
    void scanSystemCleanerItems(QMap<QString, QVariant> data);


//    Q_INVOKABLE void show_slider_qt();
    /*Q_INVOKABLE*/ void check_user_qt();
//    void http_get_img_resource();
//    //打开文件夹
    /*Q_INVOKABLE*/ void open_folder_qt(QString path);
//    Q_INVOKABLE void get_distrowatch_url_qt();
//    Q_INVOKABLE QStringList get_distrowatch_info_qt();
//    QMap<QString, QVariant> distrowatchInfo;
//    Q_INVOKABLE void get_ubuntukylin_distrowatch_info_qt();
//    Q_INVOKABLE QString getDistrowatchSingleInfo(QString key);
//    Q_INVOKABLE QStringList get_default_all_distrowatch();
//    Q_INVOKABLE void get_default_ubuntukylin_distrowatch();
//    void set_default_all_distrowatch(QString key, QString value);
//    void set_default_ubuntukylin_distrowatch(QString key, QString value);

    /*Q_INVOKABLE*/ bool judge_camera_qt();
    /*Q_INVOKABLE*/ void call_camera_qt();
    QMap<QString, QVariant> batteryInfo;
    /*Q_INVOKABLE */bool judge_power_is_exists_qt();
    /*Q_INVOKABLE */QMap<QString, QVariant> read_battery_info_qt();

//    //弹出登录框
    /*Q_INVOKABLE*/ void popup_login_dialog();
    /*Q_INVOKABLE*/ void popup_register_dialog();
//    //退出登录
    /*Q_INVOKABLE*/ void logout_ubuntukylin_account();

//    //得到SessionDbus的验证值，可以通过其判断该服务是否正在运行
//    Q_INVOKABLE QString get_session_daemon_qt();
//    //扫描浏览器历史记录
//    Q_INVOKABLE void scan_history_records_qt(QString flag);
//    //扫描系统最近打开文件的历史记录
//    Q_INVOKABLE void scan_system_history_qt();
//    //扫描Dash历史记录
////    Q_INVOKABLE int scan_dash_history_qt();
//    //扫描同名文件
////    Q_INVOKABLE QStringList scan_of_same_qt(QString abspath);
//    //扫描大文件
//    Q_INVOKABLE void scan_of_large_qt(QString abspath, int size);
//    //扫描firefox和chromium的cookies
//    Q_INVOKABLE void cookies_scan_function_qt(QString flag);



//    //扫描apt和软件中心缓存
//    Q_INVOKABLE void cache_scan_function_qt(QStringList argList, QString flag);
//    //扫描不需要的package和old kernel
//    Q_INVOKABLE void package_scan_function_qt(QStringList argList);
//    Q_INVOKABLE QStringList get_cache_arglist(int i);
//    Q_INVOKABLE QStringList get_package_arglist(int i);
//    //扫描浏览器缓存时的参数获取
//    Q_INVOKABLE QStringList get_browser_cache_arglist();

    //退出sessiondubs服务
    /*Q_INVOKABLE*/ void exit_qt();
    //弹出新特性对话框
//    Q_INVOKABLE void showFeatureDialog();
//    //弹出屏幕坏点检测对话框
//    Q_INVOKABLE void showCheckscreenDialog();
//    //弹出警告提示对话框
//    Q_INVOKABLE void showWarningDialog(QString title, QString content);
//    //弹出确认对话框
//    Q_INVOKABLE bool showConfirmDialog(QString title, QString content);

//    //得到安装操作系统的语言版本
//    Q_INVOKABLE QString get_locale_version();
//    //得到当前登录用户的主目录
    /*Q_INVOKABLE*/ QString getHomePath();

    //----get system message
    //存放当前系统和桌面信息
    QMap<QString, QVariant> systemInfo;
    //得到当前系统和桌面信息
    /*Q_INVOKABLE */QMap<QString, QVariant>  get_system_message_qt();
    //通过键得到对应的单个信息的值
//    Q_INVOKABLE QString getSingleInfo(QString key);
//    Q_INVOKABLE QString getBatterySingleInfo(QString key);

//    //恢复ubuntukylin默认配置
//    Q_INVOKABLE QString get_uk_default_setting_string(QString key, QString name);
//    Q_INVOKABLE double get_uk_default_setting_double(QString key, QString name);
//    Q_INVOKABLE int get_uk_default_setting_int(QString key, QString name);
//    Q_INVOKABLE bool get_uk_default_setting_bool(QString key, QString name);
//    Q_INVOKABLE void restore_uk_default_setting(QString key, QString name);

//    /*-------------------get and set default value-------------------*/
//    //获取和设置字体默认值:sound.py
//    Q_INVOKABLE QString get_default_sound_string_qt(QString flag/*QString schema, QString key*/);
//    Q_INVOKABLE void set_default_launcher_have_showdesktopicon_qt();

//    /*-------------------desktop of beauty-------------------*/
    /*Q_INVOKABLE*/ bool set_show_desktop_icons_qt(bool flag);
    /*Q_INVOKABLE*/ bool get_show_desktop_icons_qt();
    /*Q_INVOKABLE*/ bool set_show_homefolder_qt(bool flag);
    /*Q_INVOKABLE*/ bool get_show_homefolder_qt();
    /*Q_INVOKABLE*/ bool set_show_network_qt(bool flag);
    /*Q_INVOKABLE*/ bool get_show_network_qt();
    /*Q_INVOKABLE*/ bool set_show_trash_qt(bool flag);
    /*Q_INVOKABLE*/ bool get_show_trash_qt();
    /*Q_INVOKABLE*/ bool set_show_devices_qt(bool flag);
    /*Q_INVOKABLE*/ bool get_show_devices_qt();


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

//    /*-------------------unity of beauty-------------------*/
    /*Q_INVOKABLE*/ bool set_launcher_autohide_qt(bool flag);
    /*Q_INVOKABLE*/ bool get_launcher_autohide_qt();
    /*Q_INVOKABLE*/ bool set_launcher_icon_size_qt(int num);
    /*Q_INVOKABLE*/ int get_launcher_icon_size_qt();
    /*Q_INVOKABLE*/ bool set_launcher_have_showdesktopicon_qt(bool flag);
    /*Q_INVOKABLE*/ bool get_launcher_have_showdesktopicon_qt();

//    // for v1.1.0
//    //透明度
    /*Q_INVOKABLE*/ double get_launcher_transparency_qt();
    /*Q_INVOKABLE*/ bool set_launcher_transparency_qt(double opacity);
//    //图标背景
    /*Q_INVOKABLE*/ QStringList get_all_launcher_icon_colourings_qt();
    /*Q_INVOKABLE*/ int get_launcher_icon_colouring_qt();
    /*Q_INVOKABLE*/ bool set_launcher_icon_colouring_qt(int colouring);
//    //Dash背景模糊类型
    /*Q_INVOKABLE*/ int get_dash_blur_experimental_qt();
    /*Q_INVOKABLE*/ bool set_dash_blur_experimental_qt(int blur);
//    //面板菜单透明度
    /*Q_INVOKABLE*/ double get_panel_transparency_qt();
    /*Q_INVOKABLE*/ bool set_panel_transparency_qt(double opacity);
//    //日期时间格式
    /*Q_INVOKABLE*/ QStringList get_all_time_format_qt();
    /*Q_INVOKABLE*/ QString get_time_format_qt();
    /*Q_INVOKABLE*/ bool set_time_format_qt(QString format);
    /*Q_INVOKABLE*/ bool get_show_seconds_qt();
    /*Q_INVOKABLE*/ bool set_show_seconds_qt(bool flag);
    /*Q_INVOKABLE*/ bool get_show_week_qt();
    /*Q_INVOKABLE*/ bool set_show_week_qt(bool flag);
    /*Q_INVOKABLE*/ bool get_show_date_qt();
    /*Q_INVOKABLE*/ bool set_show_date_qt(bool flag);
//    //电源
    /*Q_INVOKABLE*/ QStringList get_all_power_icon_policy_qt();
    /*Q_INVOKABLE*/ QString get_power_icon_policy_qt();
    /*Q_INVOKABLE*/ bool set_power_icon_policy_qt(QString flag);
    /*Q_INVOKABLE*/ bool get_show_power_time_qt();
    /*Q_INVOKABLE*/ bool set_show_power_time_qt(bool flag);
    /*Q_INVOKABLE*/ bool get_show_power_percentage_qt();
    /*Q_INVOKABLE*/ bool set_show_power_percentage_qt(bool flag);

//    /*-------------------theme of beauty-------------------*/
    /*Q_INVOKABLE */QStringList get_themes_qt();
    /*Q_INVOKABLE */QString get_theme_qt();
    /*Q_INVOKABLE */void set_theme_qt(QString theme);
    /*Q_INVOKABLE */QStringList get_icon_themes_qt();
    /*Q_INVOKABLE */QString get_icon_theme_qt();
    /*Q_INVOKABLE*/ void set_icon_theme_qt(QString theme);
    /*Q_INVOKABLE*/ QStringList get_cursor_themes_qt();
    /*Q_INVOKABLE*/ QString get_cursor_theme_qt();
    /*Q_INVOKABLE*/ void set_cursor_theme_qt(QString theme);
    /*Q_INVOKABLE*/ int get_cursor_size_qt();
    /*Q_INVOKABLE*/ void set_cursor_size_qt(int size);
//    //window theme
//    Q_INVOKABLE QStringList get_window_themes_qt();
//    Q_INVOKABLE QString get_current_window_theme_qt();
//    Q_INVOKABLE void set_window_theme_qt(QString theme);

//    /*-------------------fonts of beauty-------------------*/
//    Q_INVOKABLE void restore_default_font_signal(QString flag);
//    Q_INVOKABLE void show_font_dialog(QString flag, QString current_font);
//    Q_INVOKABLE QString show_folder_dialog();
    /*Q_INVOKABLE*/ QString show_file_path_dialog();
    /*Q_INVOKABLE*/ QString get_font_qt();
//    Q_INVOKABLE bool set_font_qt_default(QString font);
    bool set_font_qt(QString font);
    /*Q_INVOKABLE*/ QString get_desktop_font_qt();
    /*Q_INVOKABLE*/ bool set_desktop_font_qt_default();//when is null ,we set a default value
    bool set_desktop_font_qt(QString font);
    /*Q_INVOKABLE*/ QString get_document_font_qt();
//    Q_INVOKABLE bool set_document_font_qt_default(QString font);
    bool set_document_font_qt(QString font);
    /*Q_INVOKABLE*/ QString get_monospace_font_qt();
//    Q_INVOKABLE bool set_monospace_font_qt_default(QString font);
    bool set_monospace_font_qt(QString font);
    /*Q_INVOKABLE*/ QString get_window_title_font_qt();
//    Q_INVOKABLE bool set_window_title_font_qt_default(QString font);
    bool set_window_title_font_qt(QString font);
    /*Q_INVOKABLE*/ double get_font_zoom_qt();
    /*Q_INVOKABLE*/ bool set_font_zoom_qt(double zoom);

    /*Q_INVOKABLE*/ QStringList get_smooth_style_list_qt();
    /*Q_INVOKABLE*/ QString get_smooth_style_qt();
    /*Q_INVOKABLE*/ bool set_smooth_style_qt(QString style);
    /*Q_INVOKABLE*/ QStringList get_antialiasing_style_list_qt();
    /*Q_INVOKABLE*/ QString get_antialiasing_style_qt();
    /*Q_INVOKABLE*/ bool set_antialiasing_style_qt(QString style);

//    /*-------------------scrollbars of beauty-------------------*/
    /*Q_INVOKABLE*/ bool set_scrollbars_mode_overlay_qt();
    /*Q_INVOKABLE*/ bool set_scrollbars_mode_legacy_qt();
    /*Q_INVOKABLE*/ QString get_scrollbars_mode_qt();

//    /*-------------------touchpad of beauty-------------------*/
    /*Q_INVOKABLE*/ bool set_touchpad_enable_qt(bool flag);
    /*Q_INVOKABLE*/ bool get_touchpad_enable_qt();
    /*Q_INVOKABLE*/ bool set_touchscrolling_mode_edge_qt();
    /*Q_INVOKABLE*/ bool set_touchscrolling_mode_twofinger_qt();
    /*Q_INVOKABLE*/ QString get_touchscrolling_mode_qt();
    /*Q_INVOKABLE*/ bool set_touchscrolling_use_horizontal_qt(bool flag);
    /*Q_INVOKABLE*/ bool get_touchscrolling_use_horizontal_qt();

//    /*-------------------window of beauty-------------------*/
//    Q_INVOKABLE void set_window_button_align_left_qt();
//    Q_INVOKABLE void set_window_button_align_right_qt();
//    Q_INVOKABLE QString get_window_button_align_qt();
    /*Q_INVOKABLE*/ bool set_menus_have_icons_qt(bool flag);
    /*Q_INVOKABLE*/ bool get_menus_have_icons_qt();
    /*Q_INVOKABLE*/ QStringList get_titlebar_wheel_qt();
    /*Q_INVOKABLE*/ QString get_current_titlebar_wheel_qt();
    /*Q_INVOKABLE*/ void set_titlebar_wheel_qt(QString value);
    /*Q_INVOKABLE*/ QStringList get_titlebar_double_qt();
    /*Q_INVOKABLE*/ QString get_current_titlebar_double_qt();
    /*Q_INVOKABLE*/ void set_titlebar_double_qt(QString value);
    /*Q_INVOKABLE*/ QStringList get_titlebar_middle_qt();
    /*Q_INVOKABLE*/ QString get_current_titlebar_middle_qt();
    /*Q_INVOKABLE*/ void set_titlebar_middle_qt(QString value);
    /*Q_INVOKABLE*/ QStringList get_titlebar_right_qt();
    /*Q_INVOKABLE*/ QString get_current_titlebar_right_qt();
    /*Q_INVOKABLE*/ void set_titlebar_right_qt(QString value);

//    /*-------------------sound of beauty-------------------*/
    /*Q_INVOKABLE*/ void set_sound_event_enable_qt(bool flag);
    /*Q_INVOKABLE*/ bool get_sound_event_enable_qt();
    /*Q_INVOKABLE*/ void set_input_feedback_sounds_enable_qt(bool flag);
    /*Q_INVOKABLE*/ bool get_input_feedback_sounds_enable_qt();
    /*Q_INVOKABLE*/ void set_login_music_enable_qt(bool flag);
    /*Q_INVOKABLE*/ bool get_login_music_enable_qt();
    /*Q_INVOKABLE*/ QString get_sound_theme_qt();
    /*Q_INVOKABLE*/ void set_sound_theme_qt(QString theme);

    /*-------------------filemanager of beauty-------------------*/
    /*Q_INVOKABLE*/ void set_location_replace_pathbar_qt(bool flag);
    /*Q_INVOKABLE*/ bool get_location_replace_pathbar_qt();
    /*Q_INVOKABLE*/ void set_auto_mount_media_qt(bool flag);
    /*Q_INVOKABLE*/ bool get_auto_mount_media_qt();
    /*Q_INVOKABLE*/ void set_auto_open_folder_qt(bool flag);
    /*Q_INVOKABLE*/ bool get_auto_open_folder_qt();
    /*Q_INVOKABLE*/ void set_prompt_autorun_programs_qt(bool flag);
    /*Q_INVOKABLE*/ bool get_prompt_autorun_programs_qt();
    /*Q_INVOKABLE*/ void set_thumbnail_icon_size_qt(int size);
    /*Q_INVOKABLE*/ int get_thumbnail_icon_size_qt();
    /*Q_INVOKABLE*/ void set_thumbnail_cache_time_qt(int value);
    /*Q_INVOKABLE*/ int get_thumbnail_cache_time_qt();
    /*Q_INVOKABLE*/ void set_thumbnail_cache_size_qt(int size);
    /*Q_INVOKABLE*/ int get_thumbnail_cache_size_qt();

//    Q_INVOKABLE QString access_current_desktop_qt();
////    Q_INVOKABLE QString judge_desktop_is_unity_qt();
////    Q_INVOKABLE QString judge_desktop_is_cinnamon_qt();

//    //-------------pinback
//    bool submit_uk_pingback();
//    /*bool*/void access_server_pingback();

//    void get_current_weather_dict_qt();//当天天气数据获取完成后，通过该函数返回其获取的值给currentInfo

//    QMap<QString, QVariant> currentInfo;
//    QMap<QString, QVariant> yahoocurrentInfo;
//    //通过键得到对应的单个信息的值,flag= forecast/current
//    Q_INVOKABLE QString getSingleWeatherInfo(QString key, QString flag);

//    //显示wizard
//    Q_INVOKABLE void showWizardController();
//    void initConfigFile();
//    QString getCityIdInfo();
//    QStringList getLatandLon();//得到纬度和经度
//    void get_current_yahoo_weather_dict_qt();//yahoo当天天气数据获取完成后，通过该函数返回其获取的值给yahoocurrentInfo

//    //改变主checkbox的状态
//    Q_INVOKABLE void change_maincheckbox_status(QString status);
//    //一键清理扫描
    /*Q_INVOKABLE*/ void onekey_scan_function_qt(QStringList selectedList);
//    Q_INVOKABLE void let_detail_info_page_to_update_data(QString infoFlag);

signals:
    void tellAutoModel(const QStringList &data);
    void showAutoModel();
    void finishScanWork(QString msg);
    void isScanning(QString msg);


    void tellCleanerDetailData(const QStringList &data);
    void tellCleanerDetailStatus(const QString &status);
    void tellCleanerDetailError(const QString &status);
//    void notifyFontStyleToQML(QString font_style);
//    void startChangeQMLCity();//发送开始更换QML城市
//    void startUpdateForecastWeahter(QString flag);//发送开始更换六天天气预报
//    void showKeyandData(QString key, QString value);//根据天气的key显示对应的数据
//    //改变主checkbox的状态
//    void startChangeMaincheckboxStatus(QString status);
//    //把cache扫描结果告诉QML
//    void appendContentToCacheModel(QString flag, QString path, QString fileFlag, QString sizeValue);
//    //cache扫描完后告诉QML
//    void tellQMLCaheOver(QString flag);
//    //把package和old kernel扫描结果告诉QML
//    void appendPackageContentToCacheModel(QString flag, QString pkgName, QString description, QString sizeValue);
//    //package和old kernel扫描完后告诉QML
//    void tellQMLPackageOver();
//    //把cookies扫描结果告诉QML
//    void appendCookiesContentToModel(QString flag, QString domain, QString num);
//    //cookies扫描完后告诉QML
//    void tellQMLCookiesOver(QString cookiesFlag);
//    //把一键扫描的总数告诉QML
    void tellScanResultToQML(QString flag, QString msg);
    void ssoSuccessSignal(QString displayName, QString emailAddress);
    void ssoLoginLogoutSignal(bool loginFlag);
//    //告诉QML界面，标题栏控制按钮位置发生变化了，准备改变优客助手自身的控制按钮位置
//    void startChangeControlBtnPosition(QString position);
//    void tellQMLHistoryNumber(QString flag, int num);
//    void tellQMLLargeFileList(QStringList filelist);
//    void tellDetailPageUpdateData(QString infoFlag);
//    //返回主页面信号
//    void backToHomePage(int index);//0412
//    void finishAccessAllDistrowatch(QString update_rate);
//    void finishAccessUKDistrowatch();
public slots:

    void handlerAutoManageData(QStringList data);
//    void handlerAutoManageData(const QVariantMap &data);

    void handlerAutoManageStatus(QString status);
    void handlerAutoManageError(QString status);

    void handlerScanCleanerData(QStringList data);
    void handlerScanCleanerStatus(QString status);
    void handlerScanCleanerError(QString status);

//    Q_INVOKABLE void get_current_weather_qt();
//    //获取天气预报槽函数
//    void accord_flag_access_weather(QString key, QString value);
    //扫描完成槽函数
    void handler_scan_complete(QString msg);
    //扫描过程的函数
    void handler_scan_process(QString msg);
    //扫描的总数
    void handler_total_data_transmit(QString flag, QString msg);
//    //更换城市槽函数
//    void handler_change_city();
//    //接收缓存信号，把数据动态堆加到model中
//    void handler_append_cache_data_to_model(QString flag, QString path, QString fileFlag, QString sizeValue);//data_transmit_by_cache(self, flag0, path, flag1, size):
//    //接收cache扫描完后的信号
//    void handler_cache_scan_over(QString flag);
//    //接收package和old kernel信号，把数据动态堆加到model中
//    void handler_append_package_data_to_model(QString flag, QString pkgName, QString description, QString sizeValue);
//    //接收package和old kernel扫描完后的信号
//    void handler_package_scan_over();
//    //接收cookies信号，把数据动态堆加到model中
//    void handler_append_cookies_to_model(QString flag, QString domain, QString num);
//    //接收cookies扫描完后的信号
//    void handler_cookies_scan_over(QString cookiesFlag);
//    //根据积分计算用户等级
//    QString score_count_level(int score);
//    //接受标题栏控制按钮位置改变
//    void handler_change_titlebar_position(QString position);
//    void handlerHistoryNumber(QString flag, int num);
//    void handlerLargeFileList(QStringList filelist);
//    //返回主页面槽函数
//    void handlerBackToHomePage(int index);
//    void handlerDistrowatchAllSignal(QString update_rate);
//    void handlerDistrowatchUKSignal(bool uk_flag);

    void handlerYoukerID(QString displayName, QString emailAddress);
    void handlerLogoutSuccess();
    void handlerLoginFail();

//    void handlerWeatherPingback(bool result);
//    void handlerUnZip(bool result);

private:
//    int mainwindow_width;
//    int mainwindow_height;
//    QSettings * mSettings;
//    QSettings * default_Settings;
//    QSettings * distrowatch_Settings;
//    QTimer *updatetimer;
//    NewCharacter *slidershow; //新版特性界面
//    SelectDialog *selectDialog;
//    HttpDownLoad *httpdownload;
    KThread *thread;

//public slots:
//    void unzip_resource_uk();
};

#endif // SESSIONDISPATCHER_H
