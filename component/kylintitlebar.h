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

#ifndef KYLINTITLEBAR_H
#define KYLINTITLEBAR_H

#include <QWidget>
#include <QPoint>
#include <QMouseEvent>
#include <QLabel>
#include "systembutton.h"

class KylinTitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit KylinTitleBar(QWidget *parent = 0);
    virtual ~KylinTitleBar();
    void setTitleWidth(int width);// { title_width = width;}20161228
    void setTitleName(QString title) { title_content = title;}
    void setTitleBackgound(QString img) { backgroud_image = img;}
    void resetBackground(QString name);

protected:
    virtual void resizeEvent (QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:
//    void showMinDialog();
    void closeDialog();

private:
    QPoint  press_point;
    QPoint  move_point;
    bool left_btn_pressed;
//    QLabel *logo_label;
    QLabel *title_label;
    int title_width;
    QString title_content;
    QString backgroud_image;
//    SystemButton *min_btn;
    SystemButton *close_btn;
};

#endif // KYLINTITLEBAR_H
