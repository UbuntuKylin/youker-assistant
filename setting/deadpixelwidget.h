/*
 * Copyright (C) 2013 ~ 2015 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  Kobe Lee    xiangli@ubuntukylin.com/kobe24_lixiang@126.com
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

#ifndef DEADPIXELWIDGET_H
#define DEADPIXELWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include "../component/quibo.h"
#include <QSplitter>

class DeadpixelWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DeadpixelWidget(QWidget *parent = 0);
    ~DeadpixelWidget();
    void setLanguage();
    void initConnect();

//signals:
//    void showSettingMainWidget();

public slots:
    void startMonitorCheck();

private:
//    QSplitter *splitter;
//    QWidget * top_widget;
//    QWidget * bottom_widget;
//    QWidget * left_widget;
//    QWidget * right_widget;

//    QPushButton *back_btn;
//    QLabel *title_label;
//    QLabel *description_label;

    QUIBO *qtui;
    QLabel *tip_label;
    QPushButton *ok_btn;
};

#endif // DEADPIXELWIDGET_H
