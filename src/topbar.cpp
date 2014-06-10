/*
 * Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd.
 * Author: Kobe Lee
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

#include "topbar.h"
#include "messengerproxy.h"
#include <QDebug>

TopBar::TopBar(QWidget *parent)
    :QStackedWidget(parent)
{
    this->view = new QDeclarativeView(this);
    this->view->rootContext()->setContextProperty("topbarObject", MessengerProxy::get_instance_object());
    this->setup();
//    this->view->setSource(QUrl("../qml/TopBar.qml"));
    this->addWidget(this->view);
    this->setAutoFillBackground(false);
    this->setStyleSheet("background:transparent;");
    this->resize(this->view->size());
    this->setFixedSize(this->view->size());
    this->setMouseTracking(true);
    this->view->move(0, 0);
}

TopBar::~TopBar()
{
    delete this->view;
}

inline bool isRunningInstalled() {
    static bool installed = (QCoreApplication::applicationDirPath() ==
                             QDir(("/usr/bin")).canonicalPath());
    return installed;
}

inline QString getAppDirectory() {
    if (isRunningInstalled()) {
//        qDebug() << QCoreApplication::applicationDirPath();
        return QString("/usr/share/youker-assistant/qml/");
    } else {
        return QString(QCoreApplication::applicationDirPath() + "/../qml/");
    }
}

void TopBar::setup() {
    this->view->engine()->setBaseUrl(QUrl::fromLocalFile(getAppDirectory()));
    this->view->setSource(QUrl::fromLocalFile("TopBar.qml"));
}
