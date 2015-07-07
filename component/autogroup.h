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

#ifndef AUTOGROUP_H
#define AUTOGROUP_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QMap>
#include "kylinswitcher.h"

class AutoGroup : public QWidget
{
    Q_OBJECT
public:
    explicit AutoGroup(QWidget *parent = 0);
    ~AutoGroup();
    void initData(QMap<QString,QString> data);
    QString dekstopFile;
    bool getSwitcherStatus();

signals:
    void autoStatusChange();

private:
    QLabel *logo_label;
    QLabel *name_label;
    QLabel *comment_label;
    KylinSwitcher *switcher;
    QLabel *splitlabel;
};

#endif // AUTOGROUP_H
