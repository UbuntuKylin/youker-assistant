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
//#include "progressdialog.h"
#include "updatedialog.h"
class QSettings;

const QString APP_LIST_FILE = "/usr/share/youker-assistant/qml/applist.ini";

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
//    Q_INVOKABLE void showProgressDialog(int window_x, int window_y);
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
//    Q_INVOKABLE QStringList getUKSoftwareList();
    Q_INVOKABLE bool getUKSignalFlag();
    Q_INVOKABLE void setUKSignalFlag(bool flag);
//    通知软件的当前状态
//    Q_INVOKABLE void notifySoftwareCurrentStatus(QString current_status);

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
    //获取所有软件的的可执行程序的名字列表，此名字对应着源里面的安装程序的名字，用该名字可以获取软件状态
    Q_INVOKABLE QStringList getAllSoftwareExecNameList();
    //得到下载或者是操作过程中发送过来的数据，在显示在进度条上之前处理优化下，返回要显示的文字
    QString dealProgressData(QString type, QString msg);
//    //添加UbuntuKylin软件源
//    Q_INVOKABLE void add_source_ubuntukylin_qt();
//    //删除UbuntuKylin软件源
//    Q_INVOKABLE void remove_source_ubuntukylin_qt();
    //得到所有app的列表，根据列表的名字可以显示所有软件机器logo到推荐界面上
    Q_INVOKABLE void getAppListForDisPlay();
    //发送标记，根据标记准备显示对应app的页面信息
    Q_INVOKABLE void ready_show_app_page(QString flag);
    //得到对应app的信息
    Q_INVOKABLE void getAppInfo(QString flag);
    //通过键得到对应的单个信息的值
    Q_INVOKABLE QString getSingleInfo(QString key);


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
//    void sendSoftwareStatus(QString current_status);
    //将软件操作过程中的状态和进度告诉给进度条去显示
    void sendDynamicSoftwareProgress(QString type, QString msg);
    //将软件操作过程中的状态和进度告诉给进度条去显示
    void sendDynamicSoftwareProgressQML(QString type, QString info, int ratio_sus);//1028
    //将软件源更新进度通知给QML
    void notifySourceStatusToQML(QString download_items, QString total_items);
    //调用遮罩层
    void callMasklayer();
    //重新获取所有软件状态
//    void reGetList();

    //准备显示对应app的页面信息的信号
    void sendAppInfo(QString flag);
    //发送软件列表给QML去显示
    void sendAppListToQML(QStringList appList);


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
//    得到进度条传来的软件源更新的实时进度
//    void getSoftwareSourceUpdateProgress(QString cur_status);
    //返回软件主页面时重新获取所有软件的状态
//    void reGetStatusList();
private:
    QDBusInterface *sudoiface;
    AuthDialog *authdialog;
//    ProgressDialog *progressdialog;
    UpdateDialog *updatedialog;
    //存放软件列表的状态
    QMap<QString, QString> status_dict;

    //存放app的信息
    QMap<QString, QString> appInfo;
    QSettings *config;
    //存放软件列表
    QStringList appList;
    //存放进度数据
    int ratio_sus;
    //判断是软件源更新还是软件操作，如果是软件源更新，则为true;如果是软件操作，则为默认的false
    bool progressFlag;

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
