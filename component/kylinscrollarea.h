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

#ifndef KYLINSCROLLAREA_H
#define KYLINSCROLLAREA_H

#include <QWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <QVBoxLayout>

class AutoGroup;

class KylinScrollArea : public QWidget
{
    Q_OBJECT
public:
    explicit KylinScrollArea(QWidget *parent = 0/*, int width = 0, int height = 0, int spacing = 0*/);
    void calculate_data();
    void add_card(AutoGroup *card);
    QWidget *cardPanel;

private:
    QScrollArea *scroll_area;
    int cardcount;
    int number_per_row;
    int itemwidth;
    int itemheight;
    int cardspacing;
};

#endif // KYLINSCROLLAREA_H
