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
        return QString("/usr/share/youker-assistant/qml/main.qml");
    } else {
        return QString(QCoreApplication::applicationDirPath() + "/../qml/main.qml");
    }
}

bool IhuApplication::setup()
{
    IhuApplication::setApplicationName("Youker Assistant");
//    QDeclarativeView *view = new QDeclarativeView;
    viewer = new QDeclarativeView;
    viewer->setSource(QUrl("../qml/main.qml"));
    viewer->rootContext()->setContextProperty("mainwindow", viewer);
    viewer->setStyleSheet("background:transparent");
    viewer->setAttribute(Qt::WA_TranslucentBackground);
    viewer->setWindowFlags(Qt::FramelessWindowHint);
//    QPainter p(this);
//    p.setCompositionMode( QPainter::CompositionMode_Clear ); p.fillRect( 10, 10, 300, 300, Qt::SolidPattern );

    QPalette palette;
    palette.setColor(QPalette::Base, Qt::transparent);
    viewer->setPalette(palette);
//    viewer->setWindowTitle("98love");
    viewer->setAutoFillBackground(false);
    viewer->setWindowOpacity(10);

    QObject::connect(viewer->engine(), SIGNAL(quit()), qApp, SLOT(quit()));
    viewer->rootContext()->setContextProperty("WindowControl",viewer);

//    QObject *rootObject = dynamic_cast<QObject *>(view->rootObject());
//    QObject::connect(rootObject, SIGNAL(dataRequired()), )

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


//        QStringList dataList;
//        dataList.append("Item 1");
//        dataList.append("Item 2");
//        dataList.append("Item 3");
//        dataList.append("Item 4");
//        QDeclarativeView *viewer = new QDeclarativeView;
//        QDeclarativeContext *ctxt = viewer->rootContext();
//        ctxt->setContextProperty("myModel", QVariant::fromValue(dataList));
//        viewer->setSource(QUrl("../qml/func/BrowserHistory.qml"));
    return true;
}

IhuApplication::~IhuApplication()
{
    if (viewer) {
        delete viewer;
    }
}

