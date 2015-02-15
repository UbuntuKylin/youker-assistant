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

#pragma once

#include <QListWidgetItem>
#include <QPainter>
class MainWindow;

class KylinListWidgetItem :public QListWidgetItem
{
public:
    KylinListWidgetItem(const QIcon &icon, const QString &text, QListWidget *view = 0, int type = Type);
    ~KylinListWidgetItem();
    void setPress(bool flag);
    void setOver(bool flag);
    void painter();
    void setMainWindow(MainWindow *window) { mainwindow = window; }
    void setSkinName(QString picture) {point_skin = picture;}
    QString getSkinName() {return point_skin;}

private:
    bool is_over;
    bool is_press;
    MainWindow *mainwindow;
    QString point_skin;
};
