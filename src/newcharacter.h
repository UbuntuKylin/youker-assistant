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

#ifndef NEWCHARACTER_H
#define NEWCHARACTER_H

#include <QWidget>
#include <QLabel>
#include <QApplication>
#include "kbutton.h"
#include "icontext.h"
#include <QTimer>

class NewCharacter : public QWidget
{
    Q_OBJECT

public:
    explicit NewCharacter(QWidget *parent = 0);
    ~NewCharacter();
    void showSlider();

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void changeCurrentPage(int);//点击按钮时更换成对应的图片
    void timerChangePosition();
    void hideSlider();

private:
    int current_pos_x;

    QLabel *background_label; //背景图片
    int current_index; //当前图片下标
    QLabel *master_label;
    IconText *pic_array[5];
    KButton *close_button; //关闭按钮

    int page_count;
    int window_btn_count;

    QTimer *timer;
    QPoint dragPos;
    bool mouse_move;
};

#endif //NEWCHARACTER_H
