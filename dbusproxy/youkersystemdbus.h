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

#ifndef YOUKERSYSTEMDBUS_H
#define YOUKERSYSTEMDBUS_H

#include <QObject>
#include <QDBusInterface>
#include <QDBusConnection>
//#include "kthread.h"

class SystemDispatcher : public QObject
{
    Q_OBJECT
public:
    explicit SystemDispatcher(QObject *parent = 0);
    ~SystemDispatcher();
    //退出systemdbus服务
    void exit_qt();

    void adjust_cpufreq_scaling_governer_qt(QString value);
    QStringList get_cpufreq_scaling_governer_list_qt();
    QString get_current_cpufreq_scaling_governer_qt();

    void cleanAllSelectItems(QMap<QString, QVariant> selectMap);
    bool kill_uk_process_qt();
    //杀掉root用户的进程
//    void kill_root_process_qt(QString pid);
    //得到SystemDbus的验证值，可以通过其判断该服务是否正在运行
    QString get_system_daemon_qt();
    //为系统设置来设置登录系统的普通用户的用户目录
//    void set_homedir_qt();
    //为系统清理来设置登录系统的普通用户的用户目录
    void set_user_homedir_qt();
    //首页一键清理
    void clean_by_main_one_key_qt();
    bool copy_file_qt(QString filename);
    bool delete_file_qt(QString filename);
    bool update_myself();
    bool update_source();

    //-----------------------sound------------------------
    QStringList get_sound_themes_qt();
//    Q_INVOKABLE QStringList get_sounds_qt();
//    Q_INVOKABLE void replace_sound_file_qt(QString origfile, QString targetfile);
//    Q_INVOKABLE void restore_sound_file_qt(QString targetfile);
//    Q_INVOKABLE void restore_all_sound_file_qt(QString soundtheme);
    bool set_cursor_theme_with_root_qt(QString theme);

    //-----------------------others------------------------
    void custom_plymouth_bg_qt(QString plymouthName);
    void add_new_plymouth_qt(QString customBG, QString plymouthName);
    QStringList get_existing_plymouth_list_qt();
    void plymouth_init_check_qt();
    QString get_image_path_qt(QString name);
    QString delete_plymouth_qt(QString plymouthName);

    //得到当前系统和桌面的详细信息
    QString get_os_name_qt();
    bool judge_sensors_exists_qt();
    QMap<QString, QVariant> get_computer_info_qt();
    QMap<QString, QVariant> get_sensor_info_qt();
    QMap<QString, QVariant> get_cpu_info_qt();
    QMap<QString, QVariant> get_memory_info_qt();
    QMap<QString, QVariant> get_board_info_qt();
    QMap<QString, QVariant> get_harddisk_info_qt();
    QMap<QString, QVariant> get_networkcard_info_qt();
    QMap<QString, QVariant> get_monitor_info_qt();
    QMap<QString, QVariant> get_cdrom_info_qt();
    QMap<QString, QVariant> get_audiocard_info_qt();
    QString get_time_value_qt();

signals:
    void tellCleanerMainData(const QStringList &data);
    void tellCleanerMainStatus(const QString &status, const QString &domain);
    void sendCleanOverSignal();
    void sendCleanErrorSignal(const QString &status);
    void policykitCleanSignal(bool status);
    void finishCleanWorkMain(QString msg);
    void finishCleanWorkMainError(QString msg);
    void quickCleanProcess(QString type, QString status);

    //apt
    void get_fetch_signal(QString msg_type, QStringList msg);
    void get_apt_signal(QString msg_type, QStringList msg);

//    void dbusInitFinished();

public slots:
    void handler_interrupt_clean(bool status);
    void handler_clear_rubbish_main_onekey(QString msg);
    void handler_clear_rubbish_main_error(QString msg);
    void handler_status_for_quick_clean(QString type, QString status);
    void handlerCleanerSubPageDataSignal(QStringList data);
    void handlerCleanerSubPageStatusSignal(QString status, QString domain);
    void handlerCleanerSubPageErrorSignal(QString status);

    //apt
//    void handlerFetchSignal(QString msg_type, QStringList msg);
//    void handlerAptSignal(QString msg_type, QStringList msg);

private:
    QDBusInterface *systemiface;
//    KThread *thread;
//    KThread *clean_thread;
};

#endif // YOUKERSYSTEMDBUS_H
