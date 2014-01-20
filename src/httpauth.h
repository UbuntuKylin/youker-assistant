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

signals:
//    void response(int len);
    void error(int errCode);
    void response(QString username, QString password, QString score);

public slots:
    void replyFinished(QNetworkReply *reply);
    
private:
    QNetworkAccessManager *mManager;
    QUrl mUrl;
};

#endif // HTTPAUTH_H
