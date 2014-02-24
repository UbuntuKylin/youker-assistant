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
#ifndef HTTPAUTH_H
#define HTTPAUTH_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
//#include <QNetworkCookieJar>
class HttpAuth : public QObject
{
    Q_OBJECT
public:
    explicit HttpAuth(QObject *parent = 0);
    void sendPostRequest(const QUrl &url, const QByteArray &data);
    void sendGetRequest(const QUrl &url);
    bool isDigitStr(const QString& str/*QString str*/);
//    QNetworkCookieJar jar;

signals:
    void error(int errCode);
    void response(QString id, QString level, QString name, QString score);
    void refresh(QString level, QString score);
    void successCommunicate();
    void failedCommunicate();

public slots:
    void replyFinished(QNetworkReply *reply);
    
private:
    QNetworkAccessManager *mManager;
    QUrl mUrl;
};

#endif // HTTPAUTH_H
