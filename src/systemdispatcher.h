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
    ~SystemDispatcher();
    //退出systemdbus服务
    Q_INVOKABLE void exit_qt();
    //得到SystemDbus的验证值，可以通过其判断该服务是否正在运行
    Q_INVOKABLE QString get_system_daemon_qt();
    //得到音乐文件的绝对路径
    Q_INVOKABLE void getMusicFileAbsolutePath(QString musicpath);
    //为系统设置来设置登录系统的普通用户的用户目录
    Q_INVOKABLE void set_homedir_qt();
    //为系统清理来设置登录系统的普通用户的用户目录
    Q_INVOKABLE void set_user_homedir_qt();
    //弹出QT的文件选择对话框
    Q_INVOKABLE QString showSelectFileDialog(QString flag);
    //首页一键清理
    Q_INVOKABLE void clean_by_main_one_key_qt(QStringList strlist);
    //系统清理页面一键清理
    Q_INVOKABLE void clean_by_second_one_key_qt(QStringList strlist);
    //清理浏览器历史痕迹
    Q_INVOKABLE void clean_history_records_qt();
    //清理系统最近打开文件的记录
    Q_INVOKABLE void clean_system_history_qt();
    //清理dash使用记录
    Q_INVOKABLE void clean_dash_history_qt();
    //清理cookies
    Q_INVOKABLE void clean_cookies_records_qt(QStringList strlist);
    //清理apt缓存、软件中心缓存、最大文件和同名文件
    Q_INVOKABLE void clean_file_cruft_qt(QStringList strlist, QString str);
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
    Q_INVOKABLE QStringList get_network_flow_total_qt();
    Q_INVOKABLE void get_network_flow_qt();
    Q_INVOKABLE void cleanup_memory_qt();
    //-----------------------------------------------

    //-----------------------others------------------------
    Q_INVOKABLE void custom_plymouth_bg_qt(QString plymouthName);
    Q_INVOKABLE void add_new_plymouth_qt(QString customBG, QString plymouthName);
    //添加新的开机动画图片后运行该函数
    Q_INVOKABLE void readyAddBootImageToList();
    Q_INVOKABLE QStringList get_existing_plymouth_list_qt();
    Q_INVOKABLE void plymouth_init_check_qt();
    //-----------------------------------------------

    Q_INVOKABLE int get_the_record_qt(QString mode);
    Q_INVOKABLE void clean_the_browser_qt(QString mode);
    Q_INVOKABLE QMap<QString, QVariant> search_same_files(QString path);
    Q_INVOKABLE QStringList search_largest_file(QString path);

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

signals:
    //添加新的开机动画图片后触发该信号
    void finishAddBootImage();
    void finishCleanWork(QString msg);
    void finishCleanWorkError(QString msg);
    void finishCleanWorkMain(QString msg);
    void finishCleanWorkMainError(QString msg);
    void finishCleanWorkSecond(QString msg);
    void finishCleanWorkSecondError(QString msg);
    void finishCleanDataMain(QString type, QString msg);
    void finishCleanDataSecond(QString type, QString msg);

public slots:
    void handler_clear_rubbish(QString msg);
    void handler_clear_rubbish_error(QString msg);
    void handler_clear_rubbish_main_onekey(QString msg);
    void handler_clear_rubbish_main_error(QString msg);
    void handler_clear_rubbish_second_onekey(QString msg);
    void handler_clear_rubbish_second_error(QString msg);
    void handler_clean_data_main(QString type, QString msg);
    void handler_clean_data_second(QString type, QString msg);
private:
    QStringList tmplist;
    QDBusInterface *systemiface;
};

#endif // SYSTEMDISPATCHER_H
