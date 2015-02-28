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
#ifndef QUIBO_H
#define QUIBO_H

#include <QWidget>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QMouseEvent>

namespace Ui {
class QUIBO;
}

class QUIBO : public QWidget
{
    Q_OBJECT
    
public:
    explicit QUIBO(QWidget *parent = 0);
    ~QUIBO();

    void myshow();
private:
    Ui::QUIBO *ui;

    int cindex;
    QStringList *colors;
    void mouseReleaseEvent(QMouseEvent *me);
    void changeColor();
};

#endif // QUIBO_H
