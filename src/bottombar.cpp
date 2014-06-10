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

#include "bottombar.h"

BottomBar::BottomBar(QWidget *parent)
    :QStackedWidget(parent)
{
    this->setStyleSheet("background:transparent;");
    this->setAutoFillBackground(false);
    this->view = new QDeclarativeView(this);
    this->setup();
//    this->view->rootContext()->setContextProperty("mainwindow", this->view);
    this->setFixedSize(this->view->size());
    this->view->move(0, 0);
}

BottomBar::~BottomBar()
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

void BottomBar::setup() {
    this->view->engine()->setBaseUrl(QUrl::fromLocalFile(getAppDirectory()));
    this->view->setSource(QUrl::fromLocalFile("BottomBar.qml"));
}
