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

#ifndef AUDIOWIDGET_H
#define AUDIOWIDGET_H

#include <QWidget>
#include <QMap>
#include <QVariant>
#include "../component/scrollwidget.h"

class SystemDispatcher;

class AudioWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AudioWidget(QWidget *parent = 0, SystemDispatcher *proxy = 0);
    int initData();

signals:

public slots:

private:
    ScrollWidget *scroll_widget;
    QMap<QString, QVariant> audio_info_map;
    QMap<QString, QVariant> tmp_info_map;
    SystemDispatcher *systemproxy;
    int mulNum;
};

#endif // AUDIOWIDGET_H
