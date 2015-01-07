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

#ifndef CONTENTFIELD_H
#define CONTENTFIELD_H

#include <QtGui/QApplication>
#include <QStackedWidget>
#include <QDeclarativeView>
#include <QDeclarativeContext>
#include <QDeclarativeEngine>
#include <QDir>

class ContentField : public QStackedWidget
{
    Q_OBJECT
public:
    explicit ContentField(QWidget *parent = 0);
    ~ContentField();
    void setup();

private:
    QDeclarativeView *view;
    QStringList strlist;

public slots:
    void DoNavigate(int index);

signals:
    void activePushStack(int index);
};
#endif // CONTENTFIELD_H
