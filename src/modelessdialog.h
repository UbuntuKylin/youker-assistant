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
#ifndef MODELESSDIALOG_H
#define MODELESSDIALOG_H
#include <QDeclarativeView>
#include <QStackedWidget>
#include <QUrl>
#include <QBoxLayout>
#include "QPalette"
#include "QPoint"
#include <QMouseEvent>
#include <QDebug>
#include <qdebug.h>
#include <QDialog>

class ModelessDialog : public QDialog//public QStackedWidget
{
    Q_OBJECT
public:
    explicit ModelessDialog(QWidget *parent = 0);
    ~ModelessDialog();
//    void mouseMoveEvent(QMouseEvent*event);
//    void mousePressEvent(QMouseEvent*event);


private:
    QDeclarativeView *view;
    QPoint dragPosition;
};

#endif // MODELESSDIALOG_H
