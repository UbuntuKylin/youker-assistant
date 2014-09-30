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
#ifndef CLOUNDDISPATCHER_H
#define CLOUNDDISPATCHER_H

#include <QObject>
#include <QtDBus>
#include <QDBusInterface>
#include <QDBusConnection>

class CloundDispatcher : public QObject
{
    Q_OBJECT
public:
    explicit CloundDispatcher(QObject *parent = 0);
    ~CloundDispatcher();
    QDBusInterface *cloundiface;
    Q_INVOKABLE void get_ip_address_qt();
    Q_INVOKABLE QString show_ip_address_qt();
    //得到SessionDbus的验证值，可以通过其判断该服务是否正在运行
    Q_INVOKABLE QString get_session_daemon_qt();
    //退出sessiondubs服务
    Q_INVOKABLE void exit_qt();
    //弹出警告提示对话框
    Q_INVOKABLE void showWarningDialog(QString title, QString content);
    //弹出确认对话框
    Q_INVOKABLE bool showConfirmDialog(QString title, QString content);
    //金山快盘云配置
//    Q_INVOKABLE void download_kysoft_cloud_conf_qt();
//    Q_INVOKABLE void upload_kysoft_cloud_conf_qt();

signals:
    void startShowIPAddress(QString ip_addr);
    //把下载和使用云端配置的情况告诉QML
//    void tellDownloadCloudConfToQML(QString download);
    //把上传配置到云端的情况告诉QML
//    void tellUploadCloudConfToQML(QString upload);

public slots:
    //接收下载和使用云端配置的信号
//    void handler_download_cloud_conf(QString download);
    //接收上传配置到云端时的信号
//    void handler_upload_cloud_conf(QString upload);
    void accord_flag_ip(QString key, QString value);

private:
    int mainwindow_width;
    int mainwindow_height;
};

#endif // CLOUNDDISPATCHER_H
