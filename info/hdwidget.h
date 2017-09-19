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

#ifndef HDWIDGET_H
#define HDWIDGET_H

#include <QWidget>
#include "../component/scrollwidget.h"
#include <QMap>
#include <QVariant>

class SystemDispatcher;

class HDWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HDWidget(QWidget *parent = 0, SystemDispatcher *proxy = 0);
    ~HDWidget();
    void initData();
    bool getStatus();
    void clear_page_list();
    bool displaySwitch();

signals:

public slots:

private:
    ScrollWidget *scroll_widget;
    QMap<QString, QVariant> hd_info_map;
    QMap<QString, QVariant> tmp_info_map;
    SystemDispatcher *systemproxy;
    bool dataOK;
    QList<ComputerPage *> page_list;
};

#endif // HDWIDGET_H
