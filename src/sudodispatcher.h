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
#ifndef SUDODISPATCHER_H
#define SUDODISPATCHER_H

#include <QObject>
#include <QDBusInterface>
#include <QDBusConnection>
#include <QApplication>
#include <QString>
#include <QDeclarativeView>
#include "authdialog.h"
#include "progressdialog.h"
#include "updatedialog.h"
class SudoDispatcher : public QObject
{
    Q_OBJECT
public:
    explicit SudoDispatcher(QObject *parent = 0);
    ~SudoDispatcher();
    //退出sudodbus服务
    Q_INVOKABLE void exit_qt();
    //弹出密码输入框
    Q_INVOKABLE void showPasswdDialog(int window_x, int window_y);
    //弹出进度条
    Q_INVOKABLE void showProgressDialog(int window_x, int window_y);
    //弹出更新软件源对话框
    Q_INVOKABLE void showUpdateSourceDialog(int window_x, int window_y);
    //得到sudodbus验证值，可以通过该值验证服务是否正在运行
    Q_INVOKABLE QString get_sudo_daemon_qt();
    //清理不需要的已经安装的软件
    Q_INVOKABLE void clean_package_cruft_qt(QStringList strlist);
    //绑定信号槽
    Q_INVOKABLE void bind_signals_after_dbus_start();
    //通过键值得到对应软件的状态
    Q_INVOKABLE QString getSoftwareStatus(QString);
    //得到UbuntuKylin软件源里面软件的列表
    Q_INVOKABLE QStringList getUKSoftwareList();
    Q_INVOKABLE bool getUKSignalFlag();
    Q_INVOKABLE void setUKSignalFlag(bool flag);
    //通知软件的当前状态
    Q_INVOKABLE void notifySoftwareCurrentStatus(QString current_status);

    // -------------------------software-center-------------------------
    //安装软件
    Q_INVOKABLE void install_pkg_qt(QString pkgName);
    //卸载软件
    Q_INVOKABLE void uninstall_pkg_qt(QString pkgName);
    //升级软件
    Q_INVOKABLE void update_pkg_qt(QString pkgName);
    //检查软件列表的状态
    Q_INVOKABLE void check_pkgs_status_qt(QStringList pkgNameList);
    //检查软件的状态
    Q_INVOKABLE QString check_pkg_status_qt(QString pkgName);
    //更新软件源
    Q_INVOKABLE void apt_get_update_qt();
    //得到优客助手提供的软件列表
    Q_INVOKABLE QStringList getAllSoftwareList();
//    //添加UbuntuKylin软件源
//    Q_INVOKABLE void add_source_ubuntukylin_qt();
//    //删除UbuntuKylin软件源
//    Q_INVOKABLE void remove_source_ubuntukylin_qt();

signals:
    //不需要的debu包清理完毕发送信号
    void finishCleanDeb(QString msg);
    //不需要的debu包清理异常发送信号
    void finishCleanDebError(QString msg);
    //软件下载过程发送的信号
    void finishSoftwareFetch(QString type, QString msg);
    //软件安装、卸载、升级过程发送的信号
    void finishSoftwareApt(QString type);
    //将软件状态通过信号告诉QML
    void sendSoftwareStatus(QString current_status);
    //将软件操作过程中的状态和进度告诉给进度条去显示
    void sendDynamicSoftwareProgress(QString type, QString msg);
    //将软件源更新进度通知给QML
    void notifySourceStatusToQML(QString cur_status);
    //调用遮罩层
    void callMasklayer();
    //重新获取所有软件状态
//    void reGetList();

public slots:
    //后台发来清理不需要的包的正确过程中的信号后响应该函数
    void handlerClearDeb(QString msg);
    //后台发来发来清理不需要的包发生错误的信号后响应该函数
    void handlerClearDebError(QString msg);
    //软件下载过程发送信号响应该函数
    void handlerSoftwareFetch(QString type, QString msg);
    //软件安装、卸载和升级过程发送信号响应该函数
    void handlerSoftwareApt(QString type, QString msg);
    //检查软件列表状态过程中发送状态信号响应该函数
    void handlerGetSoftwareListStatus(QStringList statusDict);
    //准备开始更新软件源
    void startUpdateSoftwareSource();
    //得到进度条传来的软件源更新的实时进度
    void getSoftwareSourceUpdateProgress(QString cur_status);
    //返回软件主页面时重新获取所有软件的状态
//    void reGetStatusList();
private:
    QDBusInterface *sudoiface;
    AuthDialog *authdialog;
    ProgressDialog *progressdialog;
    UpdateDialog *updatedialog;
    //存放软件列表的状态
    QMap<QString, QString> status_dict;

    QStringList strlist;
    int mainwindow_width;
    int mainwindow_height;
    int alert_width;
    int alert_height;
    int alert_width_bg;
    //本次alert的x坐标
    int alert_x;
    //保额次alert的y坐标
    int alert_y;
    bool signalFlag;
};

#endif // SUDODISPATCHER_H
