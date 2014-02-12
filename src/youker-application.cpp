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

#include "youker-application.h"
#include <QDeclarativeView>
#include <QDebug>
#include <QtDeclarative/QDeclarativeEngine>
#include <QMetaObject>
#include <QDeclarativeContext>
#include <QDesktopWidget>
#include <QGraphicsObject>
#include <QtDBus>

//#include "toplevel.h"
IhuApplication::IhuApplication(QWidget *parent)
    : QWidget(parent), viewer(0)/*, m_shadow("image/window_shadow.png")*/
{
    viewer = new QDeclarativeView;
    tray = new Tray();
//    mTopLevel = new TopLevel;
    connect(tray,SIGNAL(showOrHideQmlSignal()),this,SLOT(showOrHideMainPage()));
//    QHBoxLayout* layout = new QHBoxLayout(this);
//    layout->addWidget(viewer);
//    layout->setContentsMargins(5, 3, 4, 6);
////    layout->setContentsMargins(5, 3, 5, 7);
//    setLayout(layout);
//    setFixedSize(860, 610);
//    this->setAttribute(Qt::WA_DeleteOnClose);//防止内存泄漏
//    this->setWindowFlags(Qt::FramelessWindowHint);
//    this->setAttribute(Qt::WA_TranslucentBackground);
////    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
////    setAttribute(Qt::WA_TranslucentBackground);
//    viewer->rootContext()->setContextProperty("mainwindow", this);
}

IhuApplication::~IhuApplication() {
    if (viewer) {
        delete viewer;
    }
    if (tray) {
        delete tray;
    }


//    if (mTopLevel)
//        delete mTopLevel;
}

inline bool isRunningInstalled() {
    static bool installed = (QCoreApplication::applicationDirPath() ==
                             QDir(("/usr/bin")).canonicalPath());
    return installed;
}

inline QString getAppDirectory() {
    if (isRunningInstalled()) {
        return QString("/usr/share/youker-assistant/qml/");
    } else {
        return QString(QCoreApplication::applicationDirPath() + "/../qml/");
    }
}

void IhuApplication::showOrHideMainPage() {
    if(viewer->isHidden()) {
        viewer->show();
    }
    else {
        viewer->hide();
    }
}

void IhuApplication::setup() {
//    viewer->engine()->setBaseUrl(QUrl::fromLocalFile(getAppDirectory()));
//    viewer->setSource(QUrl::fromLocalFile("main.qml"));
//    this->show();


    viewer->engine()->setBaseUrl(QUrl::fromLocalFile(getAppDirectory()));
    viewer->setSource(QUrl::fromLocalFile("main.qml"));
    viewer->rootContext()->setContextProperty("mainwindow", viewer);
    viewer->setStyleSheet("background:transparent");
    viewer->setAttribute(Qt::WA_TranslucentBackground);
    viewer->setWindowFlags(Qt::FramelessWindowHint);
//    viewer->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::X11BypassWindowManagerHint);
    QObject::connect(viewer->engine(), SIGNAL(quit()), qApp, SLOT(quit()));
//    mTopLevel->setCenterWidget(viewer);
////    mTopLevel->setTopLevelVisible(true,true,true);
//    viewer->setContentsMargins(0, 0, 0, 0);
//    viewer->setResizeMode(QDeclarativeView::SizeViewToRootObject);
//    viewer->setResizeAnchor(QGraphicsView::AnchorViewCenter);
//    viewer->viewport()->setAutoFillBackground(false);
//    viewer->rootContext()->setContextProperty("mainwindow", mTopLevel);
//    viewer->engine()->setBaseUrl(QUrl::fromLocalFile(getAppDirectory()));
//    viewer->setSource(QUrl::fromLocalFile("main.qml"));
//    QObject::connect(viewer->engine(), SIGNAL(quit()), qApp, SLOT(quit()));
}

void IhuApplication::showQMLWidget() {
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
}




//------------------
//void IhuApplication::paintEvent(QPaintEvent *e) {
//    QPainter painter(this);

//    QRect bottom(5, 136, 200, 7);
//    QRect top(5, 0, 200, 3);
//    QRect left(0, 3, 5, 133);
//    QRect right(205, 3, 5, 133);
//    QRect topRight(205, 0, 5, 3);
//    QRect topLeft(0, 0, 5, 3);
//    QRect bottomLeft(0, 136, 5, 7);
//    QRect bottomRight(205, 136, 5, 7);

//    QRect tBottom(5, this->height() - 7, this->width() - 10, 7);
//    QRect tTop(5, 0, this->width() - 10, 3);
//    QRect tLeft(0, 3, 5, this->height() - 10);
//    QRect tRight(this->width() - 5, 3, 5, this->height() - 10);
//    QRect tTopLeft(0, 0, 5, 3);
//    QRect tTopRight(this->width() - 5, 0, 5, 3);
//    QRect tBottomLeft(0, this->height() - 7, 5, 7);
//    QRect tBottomRight(this->width() - 5, this->height() - 7, 5, 7);

//    painter.drawPixmap(tBottom, m_shadow, bottom);
//    painter.drawPixmap(tTop, m_shadow, top);
//    painter.drawPixmap(tLeft, m_shadow, left);
//    painter.drawPixmap(tRight, m_shadow, right);
//    painter.drawPixmap(tTopRight, m_shadow, topRight);
//    painter.drawPixmap(tTopLeft, m_shadow, topLeft);
//    painter.drawPixmap(tBottomLeft, m_shadow, bottomLeft);
//    painter.drawPixmap(tBottomRight, m_shadow, bottomRight);
//}

//void IhuApplication::showEvent(QShowEvent *e) {
//    repaint();
//}
