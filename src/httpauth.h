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
#ifndef HTTPAUTH_H
#define HTTPAUTH_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
class HttpAuth : public QObject
{
    Q_OBJECT
public:
    explicit HttpAuth(QObject *parent = 0);
    void sendPostRequest(const QUrl &url, const QByteArray &data);
    void sendGetRequest(const QUrl &url);

signals:
//    void response(int len);
    void error(int errCode);
    void response(/*QString username, QString password, */QString score);
    void insertDataToServer(QString data);
    void updateServerData(QString data);

public slots:
    void replyFinished(QNetworkReply *reply);
    
private:
    QNetworkAccessManager *mManager;
    QUrl mUrl;
};

#endif // HTTPAUTH_H
