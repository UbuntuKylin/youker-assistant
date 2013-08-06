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

// Qt
#include <QApplication>
#include <QApplication>
//#include <QQmlComponent>
// local
#include "systemdispatcher.h"
#include "sessiondispatcher.h"
#include "youker-application.h"
#include <QDeclarativeEngine>
#include <QDeclarativeView>
#include <QtDeclarative>
#include "quibo.h"
#include "qmlaudio.h"
#include <QTextCodec>
#include <QProcess>


#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <QDialog>

#include "qrangemodel.h"
#include "qstyleitem.h"
#include "qwheelarea.h"
#include "qtmenu.h"
int main(int argc, char** argv)
{
//    qmlRegisterType<Person>("People",1,0,"Person");
    //通过qmlRegisterType<Person>("People",1,0,"Person");
//    向QML中导出Person类，这个类在People包中，在QML中需要使用Person类的
//    话就必须包含People包，通过import People 1.0来包含，之后就可以使用Person
//    创建对象使用来。
//    qmlRegisterType<DispatcherQml>("RegisterMyType", 0, 1, "Dispatcher");


    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    qmlRegisterType<SessionDispatcher>("SessionType", 0, 1, "SessionDispatcher");
    qmlRegisterType<SystemDispatcher>("SystemType", 0, 1, "SystemDispatcher");
    qmlRegisterType<QmlAudio>("AudioType", 0, 1, "QmlAudio");

    qmlRegisterType<QRangeModel>("RangeModelType", 0, 1, "RangeModel");
    qmlRegisterType<QStyleItem>("StyleItemType", 0, 1, "StyleItem");
    qmlRegisterType<QWheelArea>("WheelAreaType", 0, 1, "WheelArea");
    qmlRegisterType<QtMenu>("MenuType", 0, 1, "Menu");
    qmlRegisterUncreatableType<QtMenuBase>("MenuBaseType", 0, 1, "NativeMenuBase", QLatin1String("Do not create objects of type NativeMenuBase"));

//    system("ps -ef | grep youker-assistant-session-daemon | grep -v grep | wc -l");
//    system("ps -ef | grep youker-assistant-system-daemon | grep -v grep | wc -l");


//    int value = 0;
//    QString str = "";
//    FILE *stream_session;
//    char buf[128];
//    memset(buf, '\0', sizeof(buf));
//    stream_session = popen("ps -ef | grep youker-assistant-session-daemon | grep -v grep | wc -l", "r" );
//    fread(buf, sizeof(char), sizeof(buf), stream_session);
//    str = QString(buf);
//    value = str.toInt();
//    if (value == 0) {
//        QProcess *process_session = new QProcess;
//        process_session->start("/usr/bin/youker-assistant-session-daemon");
//    }
//    pclose(stream_session);

//    FILE *stream_system;
//    memset(buf, '\0', sizeof(buf));
//    stream_system = popen("ps -ef | grep youker-assistant-system-daemon | grep -v grep | wc -l", "r" );
//    fread(buf, sizeof(char), sizeof(buf), stream_system);
//    str = QString(buf);
//    value = str.toInt();
//    if (value == 0) {
//        QProcess *process_system = new QProcess;
//        process_system->start("/usr/bin/youker-assistant-system-daemon");
//    }
//    pclose(stream_system);





//    qDebug() << "121231232";
//    qDebug() << buf;
//    QString str = QString(buf);
//    int value = str.toInt();
//    qDebug() << value;
//    if (value == 1)
//        qDebug() << "is 1";
//    else if (value == 0)
//        qDebug() << "is 0";
//    else if (value == 2)
//        qDebug() << "is 2";
//    qDebug() << rets2;

//    QProcess *process_session = new QProcess;
//    process_session->start("/usr/bin/youker-assistant-session-daemon");
//    QProcess *process_system = new QProcess;
//    process_system->start("sudo /usr/bin/youker-assistant-system-daemon");

    IhuApplication application(argc, argv);


//    if (!application.setupdialog()) {
//        return 0;
//    }

    if (!application.setup()) {
        return 0;
    }
    return application.exec();

//    QApplication app(argc, argv);
//    QUIBO *ui = new QUIBO();
//    app.exec();

//    QApplication app(argc, argv);
//    IhuApplication ihu;
//    ihu.show();
//    return app.exec();
}
