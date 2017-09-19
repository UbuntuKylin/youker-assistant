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

#ifndef SYSTEMWIDGET_H
#define SYSTEMWIDGET_H

#include <QWidget>
#include "computerpage.h"
#include "../component/scrollwidget.h"
#include <QMap>
#include <QTimer>

class QVariant;
class SystemDispatcher;

class SystemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SystemWidget(QWidget *parent = 0, SystemDispatcher *proxy = 0);
    ~SystemWidget();
    void initData();
    void clear_page_list();
    bool displaySwitch();

signals:

public slots:
    void updateTimeValue();

private:
    ScrollWidget *scroll_widget;
    ComputerPage *page;
    QMap<QString, QVariant> sys_info_map;
    SystemDispatcher *systemproxy;
    QTimer *timer;
};

#endif // SYSTEMWIDGET_H
