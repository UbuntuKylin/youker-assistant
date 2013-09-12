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
#ifndef SYSTEMDISPATCHER_H
#define SYSTEMDISPATCHER_H

#include <QObject>
#include <QDBusInterface>
#include <QDBusConnection>
#include <QApplication>
#include <QString>
#include <QDeclarativeView>
class SystemDispatcher : public QObject
{
    Q_OBJECT
public:
    explicit SystemDispatcher(QObject *parent = 0);
    Q_INVOKABLE int get_add_value();
    Q_INVOKABLE void send_btn_msg(QString);
    Q_INVOKABLE void exit_qt();

    Q_INVOKABLE void check_screen_break_point();

    Q_INVOKABLE QString get_system_daemon_qt();
    QString get_system_daemon_qt_default();

    //---------------------------------
    //password
    Q_INVOKABLE void show_passwd_dialog(int window_x, int window_y);

    //get music path
    Q_INVOKABLE void get_music_path(QString musicpath);
    Q_INVOKABLE void set_homedir_qt();
    Q_INVOKABLE void set_user_homedir_qt();

    Q_INVOKABLE QString show_file_dialog(QString flag);

    Q_INVOKABLE void clean_by_main_one_key_qt(QStringList strlist);
    Q_INVOKABLE void clean_by_second_one_key_qt(QStringList strlist);
    Q_INVOKABLE void clean_history_records_qt(/*QStringList strlist*/);
    Q_INVOKABLE void clean_system_history_qt(/*QString flag*/);
    Q_INVOKABLE void clean_dash_history_qt();
    Q_INVOKABLE void clean_cookies_records_qt(QStringList strlist);
    Q_INVOKABLE void clean_package_cruft_qt(QStringList strlist);
    Q_INVOKABLE void clean_file_cruft_qt(QStringList strlist, QString str);

    Q_INVOKABLE QStringList get_apt_data();
    Q_INVOKABLE QStringList get_center_data();

    //---------------------------------


    //-----------------------sound------------------------
    Q_INVOKABLE QStringList get_sound_themes_qt();
    Q_INVOKABLE QStringList get_sounds_qt();
    Q_INVOKABLE void replace_sound_file_qt(QString origfile, QString targetfile);
    Q_INVOKABLE void restore_sound_file_qt(QString targetfile);
    Q_INVOKABLE void restore_all_sound_file_qt(QString soundtheme);
    //-----------------------------------------------

    //-----------------------sound------------------------
    Q_INVOKABLE double get_cpu_percent_qt();
    Q_INVOKABLE QString get_total_memory_qt();
    Q_INVOKABLE QString get_used_memory_qt();
    Q_INVOKABLE QString get_free_memory_qt();
//    Q_INVOKABLE QStringList get_network_flow_qt();
    Q_INVOKABLE QStringList get_network_flow_total_qt();
    Q_INVOKABLE void get_network_flow_qt();
    Q_INVOKABLE void cleanup_memory_qt();
    //-----------------------------------------------

    //-----------------------others------------------------
    Q_INVOKABLE void custom_plymouth_bg_qt(QString plymouthName);
    Q_INVOKABLE void add_new_plymouth_qt(QString customBG, QString plymouthName);
    Q_INVOKABLE void send_boot_signal();
    Q_INVOKABLE QStringList get_existing_plymouth_list_qt();
    Q_INVOKABLE void plymouth_init_check_qt();

    //-----------------------------------------------

    Q_INVOKABLE int get_the_record_qt(QString mode);
    Q_INVOKABLE void clean_the_browser_qt(QString mode);
    Q_INVOKABLE QMap<QString, QVariant> search_same_files(QString path);
    Q_INVOKABLE QStringList search_largest_file(QString path);

    QMap<QString, QVariant> apt_center;
    QDBusInterface *systemiface;
    QStringList cachelist;
    QStringList systemlist;
    QStringList alllist;
    Q_INVOKABLE QStringList get_history_args(QString flag);

//-------------
    bool history_flag;
    Q_INVOKABLE void set_history_flag(bool flag);
    Q_INVOKABLE bool get_history_flag();


    QStringList apt_args;
    Q_INVOKABLE void set_apt_args(QString str);
    Q_INVOKABLE void del_apt_args(QString str);
    Q_INVOKABLE void clear_apt_args();
    Q_INVOKABLE QStringList get_apt_args();

    QStringList software_args;
    Q_INVOKABLE void set_software_args(QString str);
    Q_INVOKABLE void del_software_args(QString str);
    Q_INVOKABLE void clear_software_args();
    Q_INVOKABLE QStringList get_software_args();

    QStringList cookies_args;
    Q_INVOKABLE void set_cookies_args(QString str);
    Q_INVOKABLE void del_cookies_args(QString str);
    Q_INVOKABLE void clear_cookies_args();
    Q_INVOKABLE QStringList get_cookies_args();

    QStringList package_args;
    Q_INVOKABLE void set_package_args(QString str);
    Q_INVOKABLE void del_package_args(QString str);
    Q_INVOKABLE void clear_package_args();
    Q_INVOKABLE QStringList get_package_args();

    QStringList onekey_args;
    Q_INVOKABLE void set_onekey_args(QString str);
    Q_INVOKABLE void del_onekey_args(QString str);
    Q_INVOKABLE void clear_onekey_args();
    Q_INVOKABLE QStringList get_onekey_args();

    QStringList onekey_args2;
    Q_INVOKABLE void set_onekey_args2(QString str);
    Q_INVOKABLE void del_onekey_args2(QString str);
    Q_INVOKABLE void clear_onekey_args2();
    Q_INVOKABLE QStringList get_onekey_args2();

    QStringList largestfile_args;
    Q_INVOKABLE void set_largestfile_args(QString str);
    Q_INVOKABLE void del_largestfile_args(QString str);
    Q_INVOKABLE void clear_largestfile_args();
    Q_INVOKABLE QStringList get_largestfile_args();

//-------------


    /*-------------------one key scan-------------------*/
    Q_INVOKABLE QMap<QString, QVariant> scan_by_one_key_qt();

signals:
    void addBootImage();
    void finishCleanTrace(QString msg);
    void finishCleanTraceError(QString msg);
    void finishCleanWork(QString msg);//绑定到QML的Handler：onFinishCleanWork
    void finishCleanWorkError(QString msg);
    void finishCleanWorkMain(QString msg);//绑定到QML的Handler：onFinishCleanWorkMain
    void finishCleanWorkMainError(QString msg);//绑定到QML的Handler：onFinishCleanWorkMainError
    void finishCleanWorkSecond(QString msg);//绑定到QML的Handler：onFinishCleanWorkSecond
    void finishCleanWorkSecondError(QString msg);//绑定到QML的Handler：onFinishCleanWorkMainError
    void finishGetNetworkSpeed(QStringList speed);
    void finishCleanDataMain(QString type, QString msg);
    void finishCleanDataSecond(QString type, QString msg);

public slots:
    void handler_clear_trace(QString msg);
    void handler_clear_trace_error(QString msg);
    void handler_clear_rubbish(QString msg);
    void handler_clear_rubbish_error(QString msg);
    void handler_clear_rubbish_main_onekey(QString msg);
    void handler_clear_rubbish_main_error(QString msg);
    void handler_clear_rubbish_second_onekey(QString msg);
    void handler_clear_rubbish_second_error(QString msg);
    void handler_network_speed(QStringList speed);
    void handler_clean_data_main(QString type, QString msg);
    void handler_clean_data_second(QString type, QString msg);
private:
    QStringList tmplist;
    int mainwindow_width;
    int mainwindow_height;
    int alert_width;
    int alert_height;
    //本次alert的x坐标
    int alert_x;
    //保额次alert的y坐标
    int alert_y;
};

#endif // SYSTEMDISPATCHER_H
