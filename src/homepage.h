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

#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QtGui/QApplication>
#include <QDesktopWidget>
#include <QDeclarativeView>
#include <QDeclarativeEngine>
#include <QDeclarativeContext>
#include <QDebug>
#include <QDir>

#include "topbar.h"
#include "tabbar.h"
#include "contentfield.h"
#include "bottombar.h"
#include "tray.h"

class HomePage : public QWidget//QStackedWidget
{
    Q_OBJECT
public:
    explicit HomePage(QWidget *parent = 0);
    ~HomePage();
    void setup();

private:
    QDeclarativeView *view;
    QBoxLayout *hlayout;
    TopBar *topBar;
    TabBar *tabBar;
    ContentField *contentField;
    BottomBar *bottomBar;
    QPoint dragPos;
    //系统托盘
    Tray *tray;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

public slots:
    //主界面显示和隐藏
    void showOrHideMainPage();
};

#endif // HOMEPAGE_H
