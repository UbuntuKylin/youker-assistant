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
#include "quibo.h"
#include "ui_quibo.h"

QUIBO::QUIBO(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QUIBO)
{
    ui->setupUi(this);

    this->colors = new QStringList();
    this->colors->append("blue");
    this->colors->append("purple");
    this->colors->append("green");
    this->colors->append("orange");
    this->colors->append("red");
    this->colors->append("black");
    this->colors->append("white");
    this->cindex = 1;

    ui->bg->setStyleSheet("QLabel{background-color:" + this->colors->at(0)  + ";}");

    this->show();
    this->setWindowState(Qt::WindowActive);
    this->setWindowState(Qt::WindowFullScreen);
}

QUIBO::~QUIBO() {
    if(colors != NULL) {
        delete colors;
        colors = NULL;
    }
    delete ui;
}

void QUIBO::mouseReleaseEvent(QMouseEvent *me) {
    if(me->button() == Qt::LeftButton){
        this->changeColor();
    }else if(me->button() == Qt::RightButton){
        this->close();
    }else{
    }
}

void QUIBO::myshow() {
}

void QUIBO::changeColor() {
    if(this->cindex >= 7){
        this->close();
    }else{
        ui->bg->setStyleSheet("QLabel{background-color:" + this->colors->at(this->cindex)  + ";}");
        this->cindex ++;
    }
}
