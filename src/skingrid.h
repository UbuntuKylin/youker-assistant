/*
 * Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd.
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

#ifndef SKINGRID_H
#define SKINGRID_H

#include <QWidget>
#include <QtGui>

class SkinGrid : public QWidget
{
    Q_OBJECT

public:
    explicit SkinGrid(QWidget *parent = 0);
    ~SkinGrid();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void paintEvent(QPaintEvent *event);

signals:
    void skinSignal(QString picName);

public slots:
    void showSkinGrid(QString picName, QString skinName, bool flag=true);

private:
    QLabel *skin_icon;//皮肤缩略图
    QLabel *skin_title;//皮肤名字
    QString picName;
    bool mouse_press;
    bool mouse_enter;
};

#endif // SKINGRID_H
