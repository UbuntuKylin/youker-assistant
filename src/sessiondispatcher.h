/*
 * Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd.
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
//#include "skinswidget.h"
#include "httpauth.h"
//#include "skincenter.h"
#include "newcharacter.h"
#include "wizarddialog.h"
class QSettings;

class SessionDispatcher : public QObject
{
    Q_OBJECT
public:
    explicit SessionDispatcher(QObject *parent = 0);
    ~SessionDispatcher();
    QDBusInterface *sessioniface;
    Q_INVOKABLE void show_slider_qt();
    //退出前的准备工作
    void ready_exit_normally();
    //打开文件夹
    Q_INVOKABLE void open_folder_qt(QString path);

    Q_INVOKABLE bool judge_camera_qt();
    Q_INVOKABLE void call_camera_qt();
    QMap<QString, QVariant> batteryInfo;
    Q_INVOKABLE bool judge_power_is_exists_qt();
    Q_INVOKABLE bool read_battery_info_qt();

    //弹出登录框
    Q_INVOKABLE void popup_login_dialog();
    //退出登录
    Q_INVOKABLE void logout_ubuntukylin_account();

    //得到yahoo城市列表
    Q_INVOKABLE QStringList search_city_names_qt(QString search_name);
    //得到对应yahoo城市列表的geonameid列表
    Q_INVOKABLE QStringList get_geonameid_list_qt();
    //得到经度
    Q_INVOKABLE QStringList get_longitude_list_qt();
    //得到纬度
    Q_INVOKABLE QStringList get_latitude_list_qt();
    //得到可以获取天气数据的id
    Q_INVOKABLE QString get_yahoo_city_id_qt(QString geonameid);

    //得到SessionDbus的验证值，可以通过其判断该服务是否正在运行
    Q_INVOKABLE QString get_session_daemon_qt();
    //扫描浏览器历史记录
    Q_INVOKABLE void scan_history_records_qt(QString flag);
    //扫描系统最近打开文件的历史记录
    Q_INVOKABLE void scan_system_history_qt();
    //扫描Dash历史记录
//    Q_INVOKABLE int scan_dash_history_qt();
    //扫描同名文件
//    Q_INVOKABLE QStringList scan_of_same_qt(QString abspath);
    //扫描大文件
    Q_INVOKABLE /*QStringList*/void scan_of_large_qt(QString abspath, int size);
    //扫描cookies
//    Q_INVOKABLE QStringList scan_cookies_records_qt();
    //扫描firefox和chromium的cookies
    Q_INVOKABLE void cookies_scan_function_qt(QString flag);

    //扫描apt和软件中心缓存
    Q_INVOKABLE void cache_scan_function_qt(QStringList argList, QString flag);
    //扫描不需要的package和old kernel
    Q_INVOKABLE void package_scan_function_qt(QStringList argList);
    Q_INVOKABLE QStringList get_cache_arglist(int i);
    Q_INVOKABLE QStringList get_package_arglist(int i);
    //扫描旧内核安装包
//    Q_INVOKABLE QStringList scan_oldkernel_packages_qt();
    //扫描浏览器缓存时的参数获取
    Q_INVOKABLE QStringList get_browser_cache_arglist();

    //退出sessiondubs服务
    Q_INVOKABLE void exit_qt();
    //弹出新特性对话框
    Q_INVOKABLE void showFeatureDialog();
    //弹出屏幕坏点检测对话框
    Q_INVOKABLE void showCheckscreenDialog();
    //弹出警告提示对话框
    Q_INVOKABLE void showWarningDialog(QString title, QString content);
    //弹出确认对话框
    Q_INVOKABLE bool showConfirmDialog(QString title, QString content);

    /*Q_INVOKABLE  */void set_page_num(int num);
    Q_INVOKABLE int get_page_num();
    int page_num;

    //得到安装操作系统的语言版本
    Q_INVOKABLE QString get_locale_version();
    //得到当前登录用户的主目录
    Q_INVOKABLE QString getHomePath();

    //----get system message
    //存放当前系统和桌面信息
    QMap<QString, QVariant> systemInfo;
    //得到当前系统和桌面信息
    Q_INVOKABLE void get_system_message_qt();
    //通过键得到对应的单个信息的值
    Q_INVOKABLE QString getSingleInfo(QString key);

    /*-------------------get and set default value-------------------*/
    //获取和设置字体默认值:theme.py
    Q_INVOKABLE QString get_default_theme_sring_qt(QString flag/*QString schema, QString key*/);
    Q_INVOKABLE double get_default_theme_double_qt(QString schema, QString key);
    Q_INVOKABLE void set_default_theme_qt(QString flag/*QString schema, QString key, QString type*/);
    //获取和设置字体默认值:desktop.py
    Q_INVOKABLE bool get_default_desktop_bool_qt(QString schema, QString key);
    Q_INVOKABLE void set_default_desktop_qt(QString flag);
    //获取和设置字体默认值:sound.py
    Q_INVOKABLE QString get_default_sound_string_qt(QString flag/*QString schema, QString key*/);
    Q_INVOKABLE void set_default_sound_qt(QString flag);
    //获取和设置字体默认值:unity.py
    Q_INVOKABLE int get_default_unity_qt(QString name, QString key);
    Q_INVOKABLE void set_default_unity_qt(QString flag, int value);
    Q_INVOKABLE void set_default_launcher_have_showdesktopicon_qt();
    //获取和设置字体默认值:system.py
    Q_INVOKABLE QString get_default_system_sring_qt(QString flag);
    Q_INVOKABLE bool get_default_system_bool_qt(QString schema, QString key);
    Q_INVOKABLE void set_default_system_qt(QString flag);
    //获取和设置文件管理器默认值:filemanager.py
//    Q_INVOKABLE bool get_default_filemanager_bool_qt(QString flag);
//    Q_INVOKABLE int get_default_filemanager_int_qt(QString flag);
    Q_INVOKABLE void set_default_filemanager_qt(QString flag);




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



    // for v1.0.3
    //透明度
    Q_INVOKABLE double get_launcher_transparency_qt();
    Q_INVOKABLE bool set_launcher_transparency_qt(double opacity);
    //图标背景
    Q_INVOKABLE QStringList get_all_launcher_icon_colourings_qt();
    Q_INVOKABLE int get_launcher_icon_colouring_qt();
    Q_INVOKABLE bool set_launcher_icon_colouring_qt(int colouring);
    //Dash背景模糊类型
    Q_INVOKABLE int get_dash_blur_experimental_qt();
    Q_INVOKABLE bool set_dash_blur_experimental_qt(int blur);
    //面板菜单透明度
    Q_INVOKABLE double get_panel_transparency_qt();
    Q_INVOKABLE bool set_panel_transparency_qt(double opacity);
    //日期时间格式
    Q_INVOKABLE QStringList get_all_time_format_qt();
    Q_INVOKABLE QString get_time_format_qt();
    Q_INVOKABLE bool set_time_format_qt(QString format);
    Q_INVOKABLE bool get_show_seconds_qt();
    Q_INVOKABLE bool set_show_seconds_qt(bool flag);
    Q_INVOKABLE bool get_show_week_qt();
    Q_INVOKABLE bool set_show_week_qt(bool flag);
    Q_INVOKABLE bool get_show_date_qt();
    Q_INVOKABLE bool set_show_date_qt(bool flag);
    //电源
    Q_INVOKABLE QStringList get_all_power_icon_policy_qt();
    Q_INVOKABLE QString get_power_icon_policy_qt();
    Q_INVOKABLE bool set_power_icon_policy_qt(QString flag);
    Q_INVOKABLE bool get_show_power_time_qt();
    Q_INVOKABLE bool set_show_power_time_qt(bool flag);
    Q_INVOKABLE bool get_show_power_percentage_qt();
    Q_INVOKABLE bool set_show_power_percentage_qt(bool flag);


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
    //window theme
    Q_INVOKABLE QStringList get_window_themes_qt();
    Q_INVOKABLE QString get_current_window_theme_qt();
    Q_INVOKABLE void set_window_theme_qt(QString theme);

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

    Q_INVOKABLE QStringList get_smooth_style_list_qt();
    Q_INVOKABLE QString get_smooth_style_qt();
    Q_INVOKABLE bool set_smooth_style_qt(QString style);
    Q_INVOKABLE QStringList get_antialiasing_style_list_qt();
    Q_INVOKABLE QString get_antialiasing_style_qt();
    Q_INVOKABLE bool set_antialiasing_style_qt(QString style);


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
    Q_INVOKABLE void set_window_button_align_left_qt();
    Q_INVOKABLE void set_window_button_align_right_qt();
    Q_INVOKABLE QString get_window_button_align_qt();
    Q_INVOKABLE bool set_menus_have_icons_qt(bool flag);
    Q_INVOKABLE bool get_menus_have_icons_qt();
    Q_INVOKABLE QStringList get_titlebar_wheel_qt();
    Q_INVOKABLE QString get_current_titlebar_wheel_qt();
    Q_INVOKABLE void set_titlebar_wheel_qt(QString value);
    Q_INVOKABLE QStringList get_titlebar_double_qt();
    Q_INVOKABLE QString get_current_titlebar_double_qt();
    Q_INVOKABLE void set_titlebar_double_qt(QString value);
    Q_INVOKABLE QStringList get_titlebar_middle_qt();
    Q_INVOKABLE QString get_current_titlebar_middle_qt();
    Q_INVOKABLE void set_titlebar_middle_qt(QString value);
    Q_INVOKABLE QStringList get_titlebar_right_qt();
    Q_INVOKABLE QString get_current_titlebar_right_qt();
    Q_INVOKABLE void set_titlebar_right_qt(QString value);


    /*-------------------sound of beauty-------------------*/
    Q_INVOKABLE void set_login_music_enable_qt(bool flag);
    Q_INVOKABLE bool get_login_music_enable_qt();
    Q_INVOKABLE QString get_sound_theme_qt();
    Q_INVOKABLE void set_sound_theme_qt(QString theme);

    /*-------------------filemanager of beauty-------------------*/
    Q_INVOKABLE void set_location_replace_pathbar_qt(bool flag);
    Q_INVOKABLE bool get_location_replace_pathbar_qt();
    Q_INVOKABLE void set_auto_mount_media_qt(bool flag);
    Q_INVOKABLE bool get_auto_mount_media_qt();
    Q_INVOKABLE void set_auto_open_folder_qt(bool flag);
    Q_INVOKABLE bool get_auto_open_folder_qt();
    Q_INVOKABLE void set_prompt_autorun_programs_qt(bool flag);
    Q_INVOKABLE bool get_prompt_autorun_programs_qt();
    Q_INVOKABLE void set_thumbnail_icon_size_qt(int size);
    Q_INVOKABLE int get_thumbnail_icon_size_qt();
    Q_INVOKABLE void set_thumbnail_cache_time_qt(int value);
    Q_INVOKABLE int get_thumbnail_cache_time_qt();
    Q_INVOKABLE void set_thumbnail_cache_size_qt(int size);
    Q_INVOKABLE int get_thumbnail_cache_size_qt();

    /*-------------------monitorball-------------------*/
    Q_INVOKABLE double get_cpu_percent_qt();
    Q_INVOKABLE QString get_total_memory_qt();
    Q_INVOKABLE QString get_used_memory_qt();
    Q_INVOKABLE QString get_free_memory_qt();
    Q_INVOKABLE QStringList get_network_flow_total_qt();
    
    /*-------------------change skin-------------------*/
    Q_INVOKABLE QString setSkin();
    //皮肤对话框
    Q_INVOKABLE void showSkinWidget(/*int window_x, int window_y*/);
//    Q_INVOKABLE void showSkinCenter();

    /*-------------------weather forecast-------------------*/
    Q_INVOKABLE void get_forecast_weahter_qt();
    void get_forecast_dict_qt();//天气预报数据获取完成后，通过该函数返回其获取的值给forecastInfo
    void get_yahoo_forecast_dict_qt();
    Q_INVOKABLE void get_current_weather_qt();
    void get_current_weather_dict_qt();//当天天气数据获取完成后，通过该函数返回其获取的值给currentInfo
    void get_current_yahoo_weather_dict_qt();//yahoo当天天气数据获取完成后，通过该函数返回其获取的值给yahoocurrentInfo
    Q_INVOKABLE void get_current_pm25_qt();
    void get_pm25_str_qt();//当PM2.5获取成功后，返回给pm25Info
    Q_INVOKABLE QString access_pm25_str_qt();//把pm25Info给QML
    //得到配置文件中的更新周期
    Q_INVOKABLE int get_current_rate();
    //更新当天天气
    Q_INVOKABLE bool update_weather_data_qt();

    QMap<QString, QVariant> forecastInfo;
    QMap<QString, QVariant> currentInfo;
    QMap<QString, QVariant> yahoocurrentInfo;
    QMap<QString, QVariant> yahooforecastInfo;
    QString pm25Info;
    //通过键得到对应的单个信息的值,flag= forecast/current
    Q_INVOKABLE QString getSingleWeatherInfo(QString key, QString flag);

    //显示wizard
    Q_INVOKABLE bool showWizardController();
    //显示更改城市对话框
    Q_INVOKABLE bool showChangeCityDialog();
    Q_INVOKABLE int getLengthOfCityList();
    void initConfigFile();
    void getCityIdInfo();
    QStringList getLatandLon(QString id);//得到纬度和经度

    //改变主checkbox的状态
    Q_INVOKABLE void change_maincheckbox_status(QString status);

    //把优客助手运行时，系统的默认配置写到配置文件
    Q_INVOKABLE void write_default_configure_to_qsetting_file(QString key, QString name, QString value);
    //从Qsetting配置文件中读取系统启动时的默认配置
    Q_INVOKABLE QString read_default_configure_from_qsetting_file(QString key, QString name);

    //fcitxconfigtoolkey获取sekectedfcitxfont
    Q_INVOKABLE QString getSelectedFcitxFont();

    //一键清理扫描
    Q_INVOKABLE void onekey_scan_function_qt(QStringList selectedList);


    //金山快盘云配置
    Q_INVOKABLE void download_kysoft_cloud_conf_qt();
    Q_INVOKABLE void upload_kysoft_cloud_conf_qt();

    Q_INVOKABLE void let_detail_info_page_to_update_data(QString infoFlag);

signals:
    void finishScanWork(QString msg);
    void isScanning(QString msg);

    void notifyFontStyleToQML(QString font_style);
    void startChangeQMLSkin(QString skinName);//发送开始更换QML界面皮肤的信号
    void startChangeQMLCity();//发送开始更换QML城市
    void startUpdateForecastWeahter(QString flag);//发送开始更换六天天气预报
    void showKeyandData(QString key, QString value);//根据天气的key显示对应的数据
    void startUpdateRateTime(int rate);//发送开始更换天气自动更新周期时间
    //改变主checkbox的状态
    void startChangeMaincheckboxStatus(QString status);

    //把cache扫描结果告诉QML
    void appendContentToCacheModel(QString flag, QString path, QString fileFlag, QString sizeValue);
    //把cache的绝对路径告诉QML
//    void tellAbsPathToCacheModel(QString flag, QString path);
    //cache扫描完后告诉QML
    void tellQMLCaheOver(QString flag);
    //把package和old kernel扫描结果告诉QML
    void appendPackageContentToCacheModel(QString flag, QString pkgName, QString description, QString sizeValue);
    //package和old kernel扫描完后告诉QML
    void tellQMLPackageOver();
    //把largest file扫描结果告诉QML
    void appendLargestContentToModel(QString sizeValue, QString path);
    //largest file扫描完后告诉QML
    void tellQMLLargestOver();
    //把cookies扫描结果告诉QML
    void appendCookiesContentToModel(QString flag, QString domain, QString num);
    //cookies扫描完后告诉QML
    void tellQMLCookiesOver(QString cookiesFlag);

    //把一键扫描的总数告诉QML
    void tellScanResultToQML(QString flag, QString msg);

    //显示登录动态图片
    void showLoginAnimatedImage();
    //更新登录状态
    void updateLoginStatus(QString username, QString level, QString score);
    //刷新用户数据
    void refreshUserInfo(QString level, QString score);
    //登录失败
    void loginFailedStatus(int status);

    //告诉QML界面，标题栏控制按钮位置发生变化了，准备改变优客助手自身的控制按钮位置
    void startChangeControlBtnPosition(QString position);

    //把下载和使用云端配置的情况告诉QML
    void tellDownloadCloudConfToQML(QString download);
    //把上传配置到云端的情况告诉QML
    void tellUploadCloudConfToQML(QString upload);

    //程序退出之前用户信息写入服务器端完毕后，告诉tray退出程序
//    void ready_to_exit();

    //告诉QML确认云配置操作
//    void tellQMLCloudConfirm();

    void tellQMLHistoryNumber(QString flag, int num);
    void tellQMLLargeFileList(QStringList filelist);

    void tellDetailPageUpdateData(QString infoFlag);


    //返回主页面信号
    void backToHomePage(int index);//0412
public slots:
    void verify_user_and_password(QString user, QString pwd);
    void handle_data_after_login_success(QString id, /*QString level, */QString name, QString score);
    void handle_data_after_search_success(/*QString level, */QString score);
    void handle_data_when_login_failed(int status);
    //获取天气预报槽函数
    void accord_flag_access_weather(QString key, QString value);
    //扫描完成槽函数
    void handler_scan_complete(QString msg);
    //扫描过程的函数
    void handler_scan_process(QString msg);
    //扫描的总数
    void handler_total_data_transmit(QString flag, QString msg);

    void handler_change_skin(QString skinName);
    //更换城市槽函数
    void handler_change_city();
    //更换自动更新天气周期槽函数
    void handler_change_rate(int rate);

    //接收缓存信号，把数据动态堆加到model中
    void handler_append_cache_data_to_model(QString flag, QString path, QString fileFlag, QString sizeValue);//data_transmit_by_cache(self, flag0, path, flag1, size):
    //接收cache扫描完后的信号
    void handler_cache_scan_over(QString flag);
    //接收cache的绝对路径
//    void handler_cache_path(QString flag, QString path);

    //接收package和old kernel信号，把数据动态堆加到model中
    void handler_append_package_data_to_model(QString flag, QString pkgName, QString description, QString sizeValue);
    //接收package和old kernel扫描完后的信号
    void handler_package_scan_over();

    //接收largest file信号，把数据动态堆加到model中
    void handler_append_largest_file_to_model(QString sizeValue, QString path);
    //接收largest file扫描完后的信号
    void handler_largest_scan_over();

    //接收cookies信号，把数据动态堆加到model中
    void handler_append_cookies_to_model(QString flag, QString domain, QString num);
    //接收cookies扫描完后的信号
    void handler_cookies_scan_over(QString cookiesFlag);
    //程序退出之前接受传递过来的用户信息，准备写入服务器端
//    void handler_write_user_info_when_exit();

    //连接服务器
    void connectHttpServer();
    //处理连接服务器失败的时候
    void resetTimerStatus();
    //处理连接服务器成功的时候，查询当前用户的信息：积分、等级...
    void searchCurrentInfo();
    //根据积分计算用户等级
    QString score_count_level(int score);

    //接受标题栏控制按钮位置改变
    void handler_change_titlebar_position(QString position);

    //接收下载和使用云端配置的信号
    void handler_download_cloud_conf(QString download);
    //接收上传配置到云端时的信号
    void handler_upload_cloud_conf(QString upload);
    //接收确认云配置操作
//    void handler_confirm_cloud_action();

    void handlerHistoryNumber(QString flag, int num);
    void handlerLargeFileList(QStringList filelist);

    //返回主页面槽函数
    void handlerBackToHomePage(int index);//0412

private:
    int mainwindow_width;
    int mainwindow_height;
    int alert_width;
    int alert_height;
    //本次alert的x坐标
    int alert_x;
    //保额次alert的y坐标
    int alert_y;
    int alert_width_bg;

    //皮肤对话框对象
//    SkinsWidget *skin_widget;
//    SkinCenter *skinCenter;

    QSettings * mSettings;
    QString initCityId;
    HttpAuth *httpauth;

    int waitTime;//超时重试次数
    QTimer *timer;
    bool loginOK;
    NewCharacter *slidershow; //新版特性界面
    WizardDialog *wizardDialog;
};

#endif // SESSIONDISPATCHER_H
