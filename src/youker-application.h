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

#ifndef SYSTEMAPPLICATION_H
#define SYSTEMAPPLICATION_H

//#include <QtQuick/QQuickView>
#include <QDeclarativeView>
#include <QApplication>
#include <QMouseEvent>
#include "QPoint"
//#include <QtWidgets>
#include <QBoxLayout>
#include <QStackedWidget>

class IhuApplication : public QApplication
{
    Q_OBJECT
public:
    IhuApplication(int &argc, char **argv);
    virtual ~IhuApplication();
    bool setup();
private:
    QDeclarativeView *viewer;
};



//class IhuApplication : public QStackedWidget
//{
//    Q_OBJECT
//public:
//    explicit IhuApplication(QWidget *parent = 0);
//    ~IhuApplication();
//    void mouseMoveEvent(QMouseEvent*event);
//    void mousePressEvent(QMouseEvent*event);


//private:
//    QDeclarativeView *m_view;
//    QBoxLayout *hlayout;
//    QPoint dragPosition;
//};
#endif // SYSTEMAPPLICATION_H
