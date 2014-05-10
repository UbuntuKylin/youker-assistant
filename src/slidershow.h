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

#ifndef SLIDERSHOW_H
#define SLIDERSHOW_H

#include <QWidget>
#include <QLabel>
#include <QApplication>
#include "kbutton.h"
#include "icontext.h"
#include <QTimer>
#include <QDialog>

class SliderShow : public QDialog
{
    Q_OBJECT

public:
    explicit SliderShow(QWidget *parent = 0);
    ~SliderShow();
//    void showSlider();


protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
//    void changeCurrentPage(IconText *);//点击按钮时更换成对应的图片
    void changeCurrentPage(int);//点击按钮时更换成对应的图片
    void timerChangePosition();

//    void hideSlider();
    void start_run_program();

private:
//    void changeCurrentButton();
//    void movePicPosition(bool);
//    QPoint mouseSrcPos;//鼠标起始位置
//    QPoint mouseDstPos;//鼠标结束位置
    int current_pos_x;

    QLabel *background_label; //背景图片
    int current_index; //当前图片下标
    QLabel *master_label;
    IconText *pic_array[5];
//    IconText *cur_pic;
//    KButton *close_button; //关闭按钮
    KButton *start_button; //开始按钮
    QHBoxLayout *hLayout;

    int page_count;
    int window_btn_count;

    QTimer *timer;
    QPoint dragPos;
    bool mouse_move;

};

#endif //SLIDERSHOW_H
