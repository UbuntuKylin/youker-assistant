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

#ifndef NORMALWIDGET_H
#define NORMALWIDGET_H

#include <QWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <QVBoxLayout>


class NormalWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NormalWidget(int cardwidth = 0, int cardheight = 0, int space = 0, QWidget *parent = 0);
    ~NormalWidget();
    void calculate_data();
    void add_card(QWidget *card);
    QWidget *cardPanel;
    void resetData();

private:
    int cardcount;
    int number_per_row;
    int itemwidth;
    int itemheight;
    int cardspace;
    QScrollArea *scrollArea;
};

#endif // NORMALWIDGET_H
