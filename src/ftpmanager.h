#ifndef FTPMANAGER_H
#define FTPMANAGER_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QFile>
#include <QFtp>
#include <QTcpSocket>

class FtpManager : public QObject
{
    Q_OBJECT
public:
    explicit FtpManager(QString _host, QString userName = "", QString passWd = "",qint16 _port = 21,QObject *parent = 0);
    ~FtpManager();

signals:
    void send_progress_value(int);
    void downloadok();

public slots:
    void ftp_command_finish(int,bool);
    void start_update_progress(qint64,qint64);
    void start_abort();
    void start_download(QString _remoteFile,QString _localFile);
    void start_upload(QString _localFile,QString _remoteFile);

private:
    QString m_userName;
    QString m_passwd;
    QFtp *myFtp;
    QFile *m_File;
    bool m_IsOpenFile;
};

#endif // FTPMANAGER_H

