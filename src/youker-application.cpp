/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  Kobe Lee    kobe24_lixiang@126.com
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

#include "youker-application.h"
#include <QDeclarativeView>
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QtGui/QApplication>
#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeComponent>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeItem>
#include <QMetaObject>
#include <QDeclarativeContext>
#include <QDesktopWidget>
#include <QGraphicsObject>
#include <QDialog>
#include <QProcess>
#include "authdialog.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include <QtDBus>

extern QString passwd;

IhuApplication::IhuApplication(int &argc, char **argv)
    : QApplication(argc, argv), viewer(0)
{

}
inline bool isRunningInstalled() {
    static bool installed = (QCoreApplication::applicationDirPath() ==
                             QDir(("/usr/bin")).canonicalPath());
    return installed;
}

inline QString getAppDirectory() {
    if (isRunningInstalled()) {
        qDebug() << "1111111";
        qDebug() << QCoreApplication::applicationDirPath();
        return QString("/usr/share/youker-assistant/qml/");
//        return QString("/usr/share/youker-assistant/qml/main.qml");//0720
    } else {
        qDebug() << "22222222";
//        qDebug() << QCoreApplication::applicationDirPath() + "/../qml/main.qml";
//        return QString(QCoreApplication::applicationDirPath() + "/../qml/main.qml");//0720
        return QString(QCoreApplication::applicationDirPath() + "/../qml/");
    }
}


//QString IhuApplication::get_dbus_method_value() {
//    system1iface = new QDBusInterface("com.ubuntukylin.Password",
//                               "/",
//                                "com.ubuntukylin.Password",
//                               QDBusConnection::systemBus());
////    qDebug() << system1iface->property("DaemonVersion");//QVariant(QString, "0.6.29")
//    QDBusReply<QString> reply = system1iface->call("auth_password");
//    qDebug() << reply.value();
//    return reply.value();
//}

//void IhuApplication::judge_process(QString flagstr, QString pwd) {
//    int value = 0;
//    QString str = "";
//    FILE *stream;
//    char buf[64];
//    memset(buf, '\0', sizeof(buf));
//    QString cmd = "ps -ef | grep " + flagstr + " | grep -v grep | wc -l";
//    QByteArray ba = cmd.toLatin1();
//    const char *str_cmd = ba.data();
////    stream = popen("ps -ef | grep " + str_flag + " | grep -v grep | wc -l", "r" );
//    stream = popen(str_cmd, "r" );
//    fread(buf, sizeof(char), sizeof(buf), stream);
//    str = QString(buf);
//    value = str.toInt();
//    if (value == 0) {
//        qDebug() << "1234567";
//        QProcess *process = new QProcess;
//        if (flagstr == "youkersession") {
//            qDebug() << "001";
//            process->start("/usr/bin/" + flagstr);
//        }
//        else {
//            qDebug() << "002";
//            process->start("/usr/bin/" + flagstr + " " + pwd);
//        }
//    }
//    else
//        qDebug() << "123456789";
//    pclose(stream);
//}

bool IhuApplication::setup(QString str)
{

    bool debug_flag = false;
    //debug source
    if (!debug_flag) {
        if (str == "SessionDaemon") {
            qDebug() << "SessionDaemon6789";
        }
        else {
            qDebug() << "SessionDaemon5678";
            QProcess *process_session = new QProcess;
            process_session->start("/usr/bin/youkersession");
            qDebug() << "56789";
        }


//        int value = 0;
//        QString str = "";
//        char buf[64];
//        memset(buf, '\0', sizeof(buf));
//        FILE *stream_session;
//        stream_session = popen("ps -ef | grep youkersession | grep -v grep | wc -l", "r" );
//        fread(buf, sizeof(char), sizeof(buf), stream_session);
//        str = QString(buf);
//        value = str.toInt();
//        if (value == 0) {
//            qDebug() << "6789";
//            QProcess *process_session = new QProcess;
//            process_session->start("/usr/bin/youkersession");
//            qDebug() << "56789";
//        }
//        else
//            qDebug() << "67890";
//        memset(buf, '\0', sizeof(buf));
//        pclose(stream_session);
    }
    //run deb package
    else {
        AuthDialog *dialog = new AuthDialog;
        dialog->exec();
        qDebug() << "passwd111";
        qDebug() << passwd;
        qDebug() << "passwd222";

        int value = 0;
        QString str = "";
        FILE *stream_system;
        char buf[64];
        memset(buf, '\0', sizeof(buf));
        stream_system = popen("ps -ef | grep youkersystem | grep -v grep | wc -l", "r" );
        fread(buf, sizeof(char), sizeof(buf), stream_system);
        str = QString(buf);
        value = str.toInt();
        if (value == 0) {
            qDebug() << "1234567";
            QProcess *process_system = new QProcess;
            process_system->start("/usr/bin/youkersystem " + passwd);
        }
        else
            qDebug() << "123456789";
        pclose(stream_system);


        FILE *stream_session;
        memset(buf, '\0', sizeof(buf));
        stream_session = popen("ps -ef | grep youkersession | grep -v grep | wc -l", "r" );
        fread(buf, sizeof(char), sizeof(buf), stream_session);
        str = QString(buf);
        value = str.toInt();
        if (value == 0) {
            qDebug() << "6789";
            QProcess *process_session = new QProcess;
            process_session->start("/usr/bin/youkersession");
            qDebug() << "56789";
        }
        else
            qDebug() << "67890";
        memset(buf, '\0', sizeof(buf));
        pclose(stream_session);
    }









//    int a = system("/home/kobe/ps");
//    qDebug() << "a->";
//    qDebug() << a;

//    int value = 0;
//    QString str = "";
//    FILE *stream_system;
//    char buf[64];
//    memset(buf, '\0', sizeof(buf));
//    stream_system = popen("ps -ef | grep youkersystem | grep -v grep | wc -l", "r" );
//    fread(buf, sizeof(char), sizeof(buf), stream_system);
//    str = QString(buf);
//    value = str.toInt();
//    if (value == 0) {
//        qDebug() << "1234567";
//        QProcess *process_system = new QProcess;
//        process_system->start("/usr/bin/youkersystem " + passwd);
//    }
//    else
//        qDebug() << "123456789";
//    pclose(stream_system);


//    FILE *stream_session;
//    memset(buf, '\0', sizeof(buf));
//    stream_session = popen("ps -ef | grep youkersession | grep -v grep | wc -l", "r" );
//    fread(buf, sizeof(char), sizeof(buf), stream_session);
//    str = QString(buf);
//    value = str.toInt();
//    if (value == 0) {
//        qDebug() << "6789";
//        QProcess *process_session = new QProcess;
//        process_session->start("/usr/bin/youkersession");
//        qDebug() << "56789";
//    }
//    else
//        qDebug() << "67890";
//    memset(buf, '\0', sizeof(buf));
//    pclose(stream_session);



    IhuApplication::setApplicationName("Youker Assistant");
    viewer = new QDeclarativeView;
    viewer->engine()->setBaseUrl(QUrl::fromLocalFile(getAppDirectory()));//0720
    viewer->setSource(QUrl::fromLocalFile("main.qml"));//0720
//    viewer->setSource(QUrl("../qml/main.qml"));//0720
    viewer->rootContext()->setContextProperty("mainwindow", viewer);
    viewer->setStyleSheet("background:transparent");
    viewer->setAttribute(Qt::WA_TranslucentBackground);
    viewer->setWindowFlags(Qt::FramelessWindowHint);

    QPalette palette;
    palette.setColor(QPalette::Base, Qt::transparent);
    viewer->setPalette(palette);
    viewer->setAutoFillBackground(false);
    viewer->setWindowOpacity(10);
    QObject::connect(viewer->engine(), SIGNAL(quit()), qApp, SLOT(quit()));


    QDesktopWidget* desktop = QApplication::desktop();
    QSize size = viewer->sizeHint();
    int width = desktop->width();
    int height = desktop->height();
    int mw = size.width();
    int mh = size.height();
    int centerW = (width/2) - (mw/2);
    int centerH = (height/2) - (mh/2);
    viewer->move(centerW, centerH);
    viewer->show();

    return true;
}

IhuApplication::~IhuApplication()
{
    if (viewer) {
        delete viewer;
    }
}

