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
    : QApplication(argc, argv), m_view(0)
{

}
inline bool isRunningInstalled() {
    static bool installed = (QCoreApplication::applicationDirPath() ==
                             QDir(("/usr/bin")).canonicalPath());
    return installed;
}

inline QString getAppDirectory() {
    if (isRunningInstalled()) {
        return QString("/usr/share/i-help-you/qml/main.qml");
    } else {
        return QString(QCoreApplication::applicationDirPath() + "/../qml/main.qml");
    }
}

//IhuApplication::IhuApplication(QWidget *parent)
//    :QStackedWidget(parent), m_view(0)
//{
//    this->setStyleSheet("background:transparent;");
//    this->setWindowTitle("I-help-you");
//    this->setAutoFillBackground(false);
//    this->setWindowOpacity(1);
//    this->setAttribute(Qt::WA_TranslucentBackground);
//    this->setWindowFlags(Qt::FramelessWindowHint);

//    this->m_view = new QDeclarativeView(this);
//    this->m_view->setSource(QUrl(getAppDirectory()));
//    this->addWidget(this->m_view);
//    this->hlayout = new QBoxLayout(QBoxLayout::TopToBottom, this->m_view);
//    this->hlayout->setMargin(0);
//    this->hlayout->setSpacing(0);
//    QObject::connect(this->m_view->engine(), SIGNAL(quit()), qApp, SLOT(quit()));
////    this->setMouseTracking(true);
//}


//void IhuApplication::mousePressEvent(QMouseEvent *event)
//{
//    if (event->button() == Qt::LeftButton) {
//        dragPosition = event->globalPos() - frameGeometry().topLeft();
//        event->accept();
//    }
//    qDebug() << "mouse press event";
//}

//void IhuApplication::mouseMoveEvent(QMouseEvent *event)
//{
//    qDebug() << "mouse move11111";
//    if (event->buttons() & Qt::LeftButton) {
//        move(event->globalPos()-dragPosition);
//        event->accept();
//        qDebug() << "mouse moving";
//    }
//    qDebug() << "mouse move event";
//}

bool IhuApplication::setup()
{
    IhuApplication::setApplicationName("I-help-you");

//    QDeclarativeView *view = new QDeclarativeView;
//    view->setWindowFlags(Qt::FramelessWindowHint);
//    view->setAttribute(Qt::WA_TranslucentBackground);
//    QObject::connect(view->engine(), SIGNAL(quit()), qApp, SLOT(quit()));
//    view->setSource(QUrl(getAppDirectory()));
////    view->setSource(QUrl::fromLocalFile("qrc:/qml.qml"));
//    view->show();



    QDeclarativeView *view = new QDeclarativeView;
    view->setSource(QUrl("../qml/main.qml"));
    view->rootContext()->setContextProperty("mainwindow", view);
    view->setStyleSheet("background:transparent;");
    view->setAttribute(Qt::WA_TranslucentBackground);
    view->setWindowFlags(Qt::FramelessWindowHint);

    view->setWindowTitle("98love");
    view->setAutoFillBackground(false);
    view->setWindowOpacity(10);

    QObject::connect(view->engine(), SIGNAL(quit()), qApp, SLOT(quit()));
    view->rootContext()->setContextProperty("WindowControl",view);


//    QObject *rootObject = dynamic_cast<QObject *>(view->rootObject());
//    QObject::connect(rootObject, SIGNAL(dataRequired()), )

    QDesktopWidget* desktop = QApplication::desktop();
    QSize size = view->sizeHint();
    int width = desktop->width();
    int height = desktop->height();
    int mw = size.width();
    int mh = size.height();
    int centerW = (width/2) - (mw/2);
    int centerH = (height/2) - (mh/2);
    view->move(centerW, centerH);

    view->show();

    return true;
}

IhuApplication::~IhuApplication()
{
    if (m_view) {
        delete m_view;
    }
}

