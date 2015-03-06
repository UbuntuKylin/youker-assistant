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

#ifndef CLEANBUTTON_H
#define CLEANBUTTON_H

#include <QWidget>
#include "utils.h"

class CleanButton : public QWidget
{
    Q_OBJECT
public:
    explicit CleanButton(QWidget *parent = 0);
    void setIconPath(const QString &icon);
    void setCleanButtonStatus(BUTTONSTATUS status);
    void setCheckboxStatus(int status);

signals:
    void clicked();

protected:
    void paintEvent(QPaintEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    int tristateStatus;
    QPixmap hoverPixmap;
    QPixmap grayhoverPixmap;
    QPixmap checkPixmap;
    QPixmap uncheckPixmap;
    QList<QPixmap> checkboxList;
    BUTTONSTATUS buttonStatus;
    QRect checkboxRect;
};

#endif // CLEANBUTTON_H
