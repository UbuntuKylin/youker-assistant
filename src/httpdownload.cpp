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

#include "httpdownload.h"
#include <QObject>
#include <QDebug>
#include <QFileInfo>
#include <QDir>

HttpDownLoad::HttpDownLoad(QObject *parent) :
    QObject(parent)
{
    mManager = new QNetworkAccessManager(this);
}

HttpDownLoad::~HttpDownLoad()
{
    if (mManager != NULL) {
        delete mManager;
    }
}

void HttpDownLoad::sendDownLoadRequest(const QUrl &url) {
   QFileInfo info(url.path());
   QString fileName(info.fileName());
   if (fileName.isEmpty()) {
       fileName = "/tmp/uk-img.zip";
   }
   file = new QFile(fileName);
   if(!file->open(QIODevice::WriteOnly)) {
       delete file;
       file = 0;
       return;
   }
   startRequest(url);
}

void HttpDownLoad::startRequest(QUrl url) {
//    QString uk_path = QDir::homePath() + "/.config/ubuntukylin/youker-assistant/uk-img/";
    QString uk_path = QDir::homePath() + "/.cache/youker-assistant/uk-img/";
    QDir tmpDir(uk_path);
    if(!tmpDir.exists())
    {
        reply = mManager->get(QNetworkRequest(url));
        connect(reply,SIGNAL(finished()),this,SLOT(httpFinished()));//下载完成
        connect(reply,SIGNAL(readyRead()),this,SLOT(httpReadyRead()));//有可用数据
    //    connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(updateDataReadProgress(qint64,qint64)));//更新进度
    }
}

//save data
void HttpDownLoad::httpReadyRead() {
    if (file) {
        file->write(reply->readAll());
    }
}

//update progress
//void HttpDownLoad::updateDataReadProgress(qint64 bytesRead, qint64 totalBytes) {
//    qDebug() << totalBytes << "-------------" << bytesRead;
//}

//finish download
void HttpDownLoad::httpFinished() {
    file->flush();
    file->close();
    reply->deleteLater();
    reply = 0;
    delete file;
    file = 0;
    emit this->downloadok();
}
