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

#ifndef ICONTEXT_H
#define ICONTEXT_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPainter>

class IconText : public QWidget
{
    Q_OBJECT

public:
    explicit IconText(int index, QWidget *parent = 0);
    ~IconText();
    void setIcon(const QPixmap &);
    void setMouseEnterFlag(bool);
    void setMousePressFlag(bool);

protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

signals:
//    void ukclicked(IconText *);
    void ukclicked(int);

private:
    void paintChangePic(bool);//设置图标遮罩层
    bool mouseEnter;
    bool mousePress;
    QLabel *btnIcon;
    int cur_index;
};

#endif //ICONTEXT_H
