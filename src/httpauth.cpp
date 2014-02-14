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

#include "httpauth.h"
#include <QObject>
#include <QDebug>
#include <QStringList>

HttpAuth::HttpAuth(QObject *parent) :
    QObject(parent)
{
    mManager = new QNetworkAccessManager(this);
    QObject::connect(mManager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));
}

void HttpAuth::sendPostRequest(const QUrl &url, const QByteArray &data){
    mUrl = url;
    QNetworkRequest request(mUrl);
//    request.setUrl(QUrl(strUrl));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    mManager->post(request, data);
}

void HttpAuth::sendGetRequest(const QUrl &url) {
    mUrl = url;
    QNetworkRequest request;
    request.setUrl(mUrl);
//    request.setRawHeader("User-Agent", "Qt NetworkAccess 1.3");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    mManager->get(request);
}

bool HttpAuth::isDigitStr(const QString& str/*QString str*/)
{
    QByteArray ba = str.toLatin1();//QString转换为char*
    const char *s = ba.data();
    while(*s && *s>='0' && *s<='9') s++;
    if (*s) { //不是纯数字
        return false;
    }
    else { //纯数字
        return true;
    }
}

void HttpAuth::replyFinished(QNetworkReply *reply){
    if(reply && reply->error() == QNetworkReply::NoError) {
        /*QByteArray*/QString data = reply->readAll();
//        qDebug() << "Result:->";
//        qDebug() << data;//status=success,id=5,level=0,name=kobe,score=5,isfirststart=0,lastlogintime=2014-02-13 16:41:05,lastlogouttime=2014-02-13 16:41:05,holdtime=0
        if(data.contains(",")) {
            QStringList tmp = data.split(",");
            if(tmp.at(0).contains("=")) {
                if (tmp.at(0).split("=").at(1) == "success") {//login success
                    QMap<QString, QString> kmaps;
                    for(int i=1; i<tmp.length();i++) {
                        QStringList value = tmp.at(i).split("=");
                        kmaps.insert(value.at(0), value.at(1));
                    }
                    emit this->response(kmaps.value("id"), kmaps.value("level"), kmaps.value("name"), kmaps.value("score"));
                }
                else if(tmp.at(0).split("=").at(1) == "search_success") {//search success
                    QMap<QString, QString> ymaps;
                    for(int i=1; i<tmp.length();i++) {
                        QStringList value = tmp.at(i).split("=");
                        if(!this->isDigitStr(value.at(0))) {
                            ymaps.insert(value.at(0), value.at(1));
                            emit this->refresh(ymaps.value("level"), ymaps.value("score"));
                        }
                    }
                }
            }
            else {
                if(data == "no user,") {
                    emit this->error(-1);
                }
                else if(data == "no pass,") {
                    emit this->error(-2);
                }
                else if(data == "beat success,") {//每隔30分钟链接服务器成功
                    emit this->successCommunicate();//查询当前信息，动态显示在界面上
                }
                else if(data == "beat fail,") {//每隔30分钟链接服务器失败
                    emit this->failedCommunicate();
                }
            }
        }
        else if(data == "status=logout"){//正常注销
//            qDebug() << "logout success......";
        }
    }
    else {
//        qDebug() << reply->errorString();//"网络不能访问"
//        qDebug() << QString("%1").arg((int)reply->error());//99
        emit this->error((int)reply->error());//99
    }
    reply->close();
}
