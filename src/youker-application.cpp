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

IhuApplication::IhuApplication(int &argc, char **argv)
    : QApplication(argc, argv), viewer(0)
{
    tray = new Tray();
    handler = new Handler();

}
inline bool isRunningInstalled() {
    static bool installed = (QCoreApplication::applicationDirPath() ==
                             QDir(("/usr/bin")).canonicalPath());
    return installed;
}

inline QString getAppDirectory() {
    if (isRunningInstalled()) {
        qDebug() << QCoreApplication::applicationDirPath();
        return QString("/usr/share/youker-assistant/qml/");
//        return QString("/usr/share/youker-assistant/qml/main.qml");
    } else {
//        return QString(QCoreApplication::applicationDirPath() + "/../qml/main.qml");
        return QString(QCoreApplication::applicationDirPath() + "/../qml/");
    }
}

bool IhuApplication::setup()
{
    IhuApplication::setApplicationName("Youker Assistant");
    viewer = new QDeclarativeView;
    viewer->engine()->setBaseUrl(QUrl::fromLocalFile(getAppDirectory()));
    viewer->setSource(QUrl::fromLocalFile("main.qml"));
//    viewer->setSource(QUrl("../qml/main.qml"));
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



//    viewer_float = new QDeclarativeView;
//    viewer_float->engine()->setBaseUrl(QUrl::fromLocalFile(getAppDirectory()));
//    viewer_float->setSource(QUrl::fromLocalFile("SuspensionFrame.qml"));
//    viewer_float->setResizeMode(QDeclarativeView::SizeRootObjectToView);
//    QObject *rootObject = dynamic_cast<QObject*>(viewer_float->rootObject());
//    QObject::connect(handler, SIGNAL(trans_signal_between_qml()), rootObject, SLOT(show_large_widget()));
//    QObject::connect(rootObject, SIGNAL(tansmitData(double, QString, QString)), handler, SLOT(getData(double, QString, QString)));
//    QObject::connect(tray, SIGNAL(showFloat()), rootObject, SLOT(show_large_frame()));
//    viewer_float->rootContext()->setContextProperty("fmainwindow", viewer_float);
//    viewer_float->setStyleSheet("background:transparent");
//    viewer_float->setAttribute(Qt::WA_TranslucentBackground);
//    viewer_float->setWindowFlags(Qt::FramelessWindowHint);
//    QDesktopWidget* fdesktop = QApplication::desktop();
//    viewer_float->move(fdesktop->width(), 60);
//    viewer_float->show();

//    viewer_small = new QDeclarativeView;
//    viewer_small->engine()->setBaseUrl(QUrl::fromLocalFile(getAppDirectory()));
//    viewer_small->setSource(QUrl::fromLocalFile("MonitorBall.qml"));
//    viewer_small->setResizeMode(QDeclarativeView::SizeRootObjectToView);
//    QObject *srootObject = dynamic_cast<QObject*>(viewer_small->rootObject());
//    QObject::connect(srootObject, SIGNAL(send_signal_to_large()), handler, SLOT(signalHandler()));
//    QObject::connect(handler, SIGNAL(send_data(QVariant, QVariant, QVariant)), srootObject, SLOT(receive_data(QVariant, QVariant, QVariant)));
//    QObject::connect(tray, SIGNAL(showFloat()), srootObject, SLOT(show_float_frame()));
//    viewer_small->rootContext()->setContextProperty("smallwindow", viewer_small);
//    viewer_small->setStyleSheet("background:transparent");
//    viewer_small->setAttribute(Qt::WA_TranslucentBackground);
//    viewer_small->setWindowFlags(Qt::FramelessWindowHint);
//    QDesktopWidget* sdesktop = QApplication::desktop();
//    viewer_small->move(sdesktop->width(), 0);
//    viewer_small->show();




//    viewer_small = new QDeclarativeView;
//    viewer_small->engine()->setBaseUrl(QUrl::fromLocalFile(getAppDirectory()));
//    viewer_small->setSource(QUrl::fromLocalFile("Smallfloat.qml"));
//    viewer_small->setResizeMode(QDeclarativeView::SizeRootObjectToView);
//    QObject *srootObject = dynamic_cast<QObject*>(viewer_small->rootObject());
//    QObject::connect(srootObject, SIGNAL(send_signal_to_large()), handler, SLOT(signalHandler()));
//    QObject::connect(srootObject, SIGNAL(tansmitData(double, QString, QString)), handler, SLOT(getData(double, QString, QString)));
//    QObject::connect(tray, SIGNAL(showFloat()), srootObject, SLOT(show_float_frame()));
//    viewer_small->rootContext()->setContextProperty("smallwindow", viewer_small);
//    viewer_small->setStyleSheet("background:transparent");
//    viewer_small->setAttribute(Qt::WA_TranslucentBackground);
//    viewer_small->setWindowFlags(Qt::FramelessWindowHint);
//    QDesktopWidget* sdesktop = QApplication::desktop();
//    viewer_small->move(sdesktop->width(), 0);
//    viewer_small->show();

//    viewer_float = new QDeclarativeView;
//    viewer_float->engine()->setBaseUrl(QUrl::fromLocalFile(getAppDirectory()));
//    viewer_float->setSource(QUrl::fromLocalFile("floatmain.qml"));
//    viewer_float->setResizeMode(QDeclarativeView::SizeRootObjectToView);
//    QObject *rootObject = dynamic_cast<QObject*>(viewer_float->rootObject());
//    QObject::connect(handler, SIGNAL(trans_signal_between_qml()), rootObject, SLOT(show_large_widget()));
//    QObject::connect(handler, SIGNAL(send_data(QVariant, QVariant, QVariant)), rootObject, SLOT(receive_data(QVariant, QVariant, QVariant)));
//    QObject::connect(tray, SIGNAL(showFloat()), rootObject, SLOT(show_large_frame()));
//    viewer_float->rootContext()->setContextProperty("fmainwindow", viewer_float);
//    viewer_float->setStyleSheet("background:transparent");
//    viewer_float->setAttribute(Qt::WA_TranslucentBackground);
//    viewer_float->setWindowFlags(Qt::FramelessWindowHint);
//    QDesktopWidget* fdesktop = QApplication::desktop();
//    viewer_float->move(fdesktop->width(), 60);
//    viewer_float->show();

    return true;
}

IhuApplication::~IhuApplication()
{
    if (viewer) {
        delete viewer;
    }
//    if (viewer_float) {
//        delete viewer_float;
//    }
    if (tray) {
        delete tray;
    }
//    if (viewer_small)
//        delete viewer_small;
}

