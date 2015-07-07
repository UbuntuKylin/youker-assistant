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

#include "loadinglabel.h"
#include <QHBoxLayout>
#include <QBitmap>
#include <QDebug>

LoadingLabel::LoadingLabel(QWidget *parent, QString flag) :
    QLabel(parent), category(flag)
{
    if(category == "firstkey") {
        page_count = 18;
        this->setFixedSize(150, 150);
    }
    else if(category == "clean") {
        page_count = 18;
        this->setFixedSize(96, 96);
    }
    else if(category == "upgrading") {
        page_count = 32;
        this->setFixedSize(182, 181);
    }
    else if(category == "working") {
        page_count = 36;
        this->setFixedSize(182, 181);
    }
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    currentpage = 0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(changeAnimationStep()));

    this->loadAllPictures();
    this->raise();

    //init animation
    QPixmap cur_pix = png_vector.at(0);
    this->setPixmap(cur_pix);
    setMask(QBitmap(cur_pix.mask()));
}

LoadingLabel::~LoadingLabel()
{
    if (timer != NULL) {
        disconnect(timer,SIGNAL(timeout()),this,SLOT(changeAnimationStep()));
        if(timer->isActive()) {
            timer->stop();
        }
        delete timer;
        timer = NULL;
    }
}

void LoadingLabel::changeAnimationStep()
{

    if(currentpage == this->page_count)
    {
        currentpage = 0;
    }
//    qDebug() << currentpage;
    QPixmap cur_pix = png_vector.at(currentpage);
    this->setPixmap(cur_pix);
    setMask(QBitmap(cur_pix.mask()));
    currentpage += 1;
}

void LoadingLabel::loadAllPictures()
{
    QString path;
    if(category == "firstkey") {
        path = ":/movie/res/loading/";
    }
    else if(category == "clean") {
        path = ":/movie/res/loading/small/";
    }
    else if(category == "upgrading") {
        path = ":/movie/res/upgrading/";
    }
    else if(category == "working") {
        path = ":/movie/res/working/";
    }
    for(int i =1; i <= this->page_count; i++)
    {
        QPixmap img = QPixmap(path + QString::number(i, 10) + ".png");
        png_vector.append(img);
    }
}

void LoadingLabel::startLoading()
{
    currentpage = 0;
    if(category == "upgrading" || category == "working")
        timer->start(50);
    else
        timer->start(60);
}

void LoadingLabel::stopLoading()
{
    timer->stop();
}
