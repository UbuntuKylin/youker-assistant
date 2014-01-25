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
#include "httpauth.h"
//#include "skincenter.h"
class QSettings;

class SessionDispatcher : public QObject
{
    Q_OBJECT
public:
    explicit SessionDispatcher(QObject *parent = 0);
    ~SessionDispatcher();
    QDBusInterface *sessioniface;
    Q_INVOKABLE void show_slider_qt();
    QString get_currrent_date_qt();
    int login_in_forum_account_qt();

    Q_INVOKABLE void login_ubuntukylin_account(int window_x, int window_y);
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
    Q_INVOKABLE int scan_history_records_qt(QString flag);
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

    //扫描firefox和chromium的cookies
    Q_INVOKABLE void cookies_scan_function_qt(QString flag);

    //扫描不需要的deb包
    Q_INVOKABLE QStringList scan_unneed_packages_qt();
    //扫描apt缓存
    Q_INVOKABLE QStringList scan_apt_cruft_qt();
    //扫描软件中心缓存
    Q_INVOKABLE QStringList scan_softwarecenter_cruft_qt();
    //扫描apt和软件中心缓存
    Q_INVOKABLE void cache_scan_function_qt(QStringList argList, QString flag);
    //扫描不需要的package和old kernel
    Q_INVOKABLE void package_scan_function_qt(QStringList argList);
    Q_INVOKABLE QStringList get_cache_arglist(int i);
    Q_INVOKABLE QStringList get_package_arglist(int i);
    //扫描旧内核安装包
    Q_INVOKABLE QStringList scan_oldkernel_packages_qt();
    //扫描浏览器缓存时的参数获取
    Q_INVOKABLE QStringList get_browser_cache_arglist();

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
    //更新六天天气预报
    Q_INVOKABLE void update_forecast_weather();
    Q_INVOKABLE void change_select_city_name_qt(QString cityName);

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
    Q_INVOKABLE bool showChangeCityDialog(/*int window_x, int window_y*/);
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

    //更新登录状态
    void updateLoginStatus(QString username, QString password, QString score);

    //程序退出之前用户信息写入服务器端完毕后，告诉tray退出程序
    void ready_to_exit();
public slots:
    void handler_access_user_password(QString user, QString pwd);
    void handler_access_login_success_info(QString username, QString password, QString score);
    //获取天气预报槽函数
    void handler_access_forecast_weather(QString key, QString value);
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


    //    //判断是否有firefox浏览器
//    void handler_deb_exists_firefox(QString flag);
//    //判断是否有chromium浏览器
//    void handler_deb_exists_chromium(QString flag);
    //程序退出之前接受传递过来的用户信息，准备写入服务器端
    void handler_write_user_info_when_exit();

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
    SkinsWidget *skin_widget;
//    SkinCenter *skinCenter;

    QSettings * mSettings;
    QString initCityId;
    HttpAuth *httpauth;
};

#endif // SESSIONDISPATCHER_H
