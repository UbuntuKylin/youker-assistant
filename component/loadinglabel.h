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

#ifndef LOADINLABEL_H
#define LOADINLABEL_H

#include <QLabel>
#include <QTimer>
#include <QVector>
#include <QPixmap>

class LoadingLabel : public QLabel
{
    Q_OBJECT
public:
    explicit LoadingLabel(QWidget *parent = 0, QString flag = "");//flag=ture:big picture;flag=false:small picture
    ~LoadingLabel();
    void loadAllPictures();
    void startLoading();
    void stopLoading();

public slots:
    void changeAnimationStep();

private:
    QTimer *timer;
    QVector<QPixmap> png_vector;
    int currentpage;
    int page_count;
    QString category;
};

#endif // LOADINLABEL_H
