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

#ifndef KYLINSWITCHER_H
#define KYLINSWITCHER_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class KylinSwitcher : public QWidget
{
    Q_OBJECT
public:
    explicit KylinSwitcher(QWidget *parent = 0);
    bool switchedOn;
//    void setSwitchStatus(bool flag) {switchedOn = flag;}

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);
//    void enterEvent(QEvent *);

signals:
    void clicked();

public slots:

private:
    QPixmap pixmap_on;
    QPixmap pixmap_off;
    bool m_mousePressed;
};

#endif // KYLINSWITCHER_H
