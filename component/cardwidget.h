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

#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <QVBoxLayout>


class CardWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CardWidget(int cardwidth = 0, int cardheight = 0, int space = 0, QWidget *parent = 0);
    ~CardWidget();
    void calculate_data();
    void add_card(QWidget *card);
    void clear_card();
    QWidget *cardPanel;

private:
    int cardcount;
    int number_per_row;
    int itemwidth;
    int itemheight;
    int cardspace;
    QScrollArea *scrollArea;
};

#endif // CARDWIDGET_H
