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

#include "clounddispatcher.h"
#include "warningdialog.h"

extern QPoint widgetPosition;

CloundDispatcher::CloundDispatcher(QObject *parent) :
    QObject(parent)
{
    cloundiface = new QDBusInterface("com.ubuntukylin.session",
                               "/",
                               "com.ubuntukylin.session",
                               QDBusConnection::sessionBus());
    this->mainwindow_width = 850;
    this->mainwindow_height = 600;
    //cloud conf
    QObject::connect(cloundiface, SIGNAL(upload_cloud_conf_signal(QString)), this, SLOT(handler_upload_cloud_conf(QString)));
    QObject::connect(cloundiface, SIGNAL(download_cloud_conf_signal(QString)), this, SLOT(handler_download_cloud_conf(QString)));
    QObject::connect(cloundiface, SIGNAL(access_weather(QString, QString)), this, SLOT(accord_flag_ip(QString, QString)));
}

CloundDispatcher::~CloundDispatcher() {
    this->exit_qt();
    if (cloundiface != NULL) {
        delete cloundiface;
    }
}

//dbus服务退出
void CloundDispatcher::exit_qt() {
    cloundiface->call("exit");
}

void CloundDispatcher::get_ip_address_qt() {
    //then get ip
    cloundiface->call("get_ip_address");
}

QString CloundDispatcher::show_ip_address_qt() {
    QDBusReply<QString> reply = cloundiface->call("show_ip_address");
    return reply.value();
}

void CloundDispatcher::download_kysoft_cloud_conf_qt() {
    cloundiface->call("download_kysoft_cloud_conf");
}

void CloundDispatcher::upload_kysoft_cloud_conf_qt() {
    cloundiface->call("upload_kysoft_cloud_conf");
}

//接收下载和使用云端配置的信号
void CloundDispatcher::handler_download_cloud_conf(QString download) {
    emit this->tellDownloadCloudConfToQML(download);
}

//接收上传配置到云端时的信号
void CloundDispatcher::handler_upload_cloud_conf(QString upload) {
    emit this->tellUploadCloudConfToQML(upload);
}

void CloundDispatcher::accord_flag_ip(QString key, QString value) {
    if(key == "ip_addr" && value == "kobe") {
        QString ip_addr = this->show_ip_address_qt();
        emit startShowIPAddress(ip_addr);
    }
}

QString CloundDispatcher::get_session_daemon_qt() {
    QDBusReply<QString> reply = cloundiface->call("get_session_daemon");
    return reply.value();
}


void CloundDispatcher::showWarningDialog(QString title, QString content) {
    //WarningDialog width:329; WarningDialog height:195
    WarningDialog *dialog = new WarningDialog(title, content);
    int w_x = widgetPosition.x() + (this->mainwindow_width / 2) - (329  / 2);
    int w_y = widgetPosition.y() + (this->mainwindow_height /2) - (195  / 2);
    dialog->move(w_x, w_y);
    dialog->exec();
}

bool CloundDispatcher::showConfirmDialog(QString title, QString content) {
    //WarningDialog width:329; WarningDialog height:195
    WarningDialog *dialog = new WarningDialog(title, content);
    int w_x = widgetPosition.x() + (this->mainwindow_width / 2) - (329  / 2);
    int w_y = widgetPosition.y() + (this->mainwindow_height /2) - (195  / 2);
    dialog->move(w_x, w_y);
    dialog-> QWidget::setAttribute(Qt::WA_DeleteOnClose);
    if(dialog->exec()==QDialog::Rejected) {
        return false;
    }
    else {
        return true;
    }
}
