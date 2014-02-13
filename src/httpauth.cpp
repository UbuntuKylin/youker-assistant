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

void HttpAuth::replyFinished(QNetworkReply *reply){
    if(reply && reply->error() == QNetworkReply::NoError) {
        /*QByteArray*/QString data = reply->readAll();
        qDebug() << "Result:->";
        qDebug() << data;//status=success,id=5,level=0,name=kobe,score=5,isfirststart=0,lastlogintime=2014-02-13 16:41:05,lastlogouttime=2014-02-13 16:41:05,holdtime=0
        if(data.contains(",")) {
            QStringList tmp = data.split(",");
            if(tmp.at(0).contains("=")) {
                if (tmp.at(0).split("=").at(1) == "success") {
                    qDebug() << "login success..........";
                    emit this->response(tmp.at(1).split("=").at(1), tmp.at(2).split("=").at(1), tmp.at(3).split("=").at(1), tmp.at(4).split("=").at(1));
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
                    qDebug() << "communicate success...";
                    emit this->successCommunicate();//查询当前信息，动态显示在界面上
                }
                else if(data == "beat fail,") {//每隔30分钟链接服务器失败
                    emit this->failedCommunicate();
                }
            }
        }
        else if(data == "status=logout"){//正常注销
            qDebug() << "logout success......";
        }
//        else if() {//查询当前等级、积分成功后
//            qDebug() << "search info success......";
//            emit this->response(tmp.at(1).split("=").at(1), tmp.at(2).split("=").at(1), tmp.at(3).split("=").at(1), tmp.at(4).split("=").at(1));
//        }

//        qDebug() << QString("%1").arg(tmp.length());
//        if(tmp.at(0) == "success") {
////            qDebug() << "login success";
//            emit this->response(/*tmp.at(1), tmp.at(2), */"1000");
//        }
//        else {
////            qDebug() << "1111111111111";
////            qDebug() << data;
//            if(data.contains(",")/*,Qt::CaseSensitive*/) {
//                QStringList searchData = data.split(",");
////                qDebug() << searchData.at(0);//id=2
//                if(searchData.at(0).contains("=")) {
//                    QStringList idData = searchData.at(0).split("=");
////                    qDebug() << idData.at(1);//2
//                    if(idData.at(1).isEmpty()) {
//                    }
//                    else {
//                    }
//                }
//            }
//            else if(data == "no user") {
//                emit this->error(-1);
//            }
//            else if(data == "no pass") {
//                emit this->error(-2);
//            }
//            else if(data == "success") {
//                qDebug() << "update success...";
//            }
//            else if(data == "failed") {
//                qDebug() << "update failed...";
//            }
//            else if(data == "communicate success") {//每隔30分钟链接服务器成功
//                qDebug() << "communicate success...";
//            }
//            else if(data == "communicate failed") {//每隔30分钟链接服务器失败
//                emit this->failedCommunicate();
//            }
//        }
    } else {
//        qDebug() << "ERROR:->";
//        qDebug() << reply->errorString();//"网络不能访问"
//        qDebug() << QString("%1").arg((int)reply->error());//99
        emit this->error((int)reply->error());//99
    }
    reply->close();
}
