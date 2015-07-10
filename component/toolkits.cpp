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

#include "toolkits.h"

Toolkits::Toolkits(QObject *parent, int width, int height) :
    QObject(parent), parent_width(width), parent_height(height)
{
    this->alert_width = 200;
    this->alert_height = 75;

    alertBG = new AlertDialog();
    this->alertTimer = new QTimer(this);
    connect(alertTimer, SIGNAL(timeout()), this, SLOT(updateAlert()));
    this->alertDelayTimer = new QTimer(this);
    connect(alertDelayTimer, SIGNAL(timeout()), this, SLOT(hideAlert()));
    this->alertGOE = new QGraphicsOpacityEffect();
    this->alertBG->setGraphicsEffect(alertGOE);
    this->ao = 0.0;
    this->alertBG->hide();
}

Toolkits::~Toolkits()
{
    if(alertGOE != NULL) {
        delete alertGOE;
        alertGOE = NULL;
    }
    if(alertBG != NULL) {
        delete alertBG;
        alertBG = NULL;
    }
    if (alertTimer != NULL) {
        disconnect(alertTimer,SIGNAL(timeout()),this,SLOT(updateAlert()));
        if(alertTimer->isActive()) {
            alertTimer->stop();
        }
        delete alertTimer;
        alertTimer = NULL;
    }
    if (alertDelayTimer != NULL) {
        disconnect(alertDelayTimer,SIGNAL(timeout()),this,SLOT(hideAlert()));
        if(alertDelayTimer->isActive()) {
            alertDelayTimer->stop();
        }
        delete alertDelayTimer;
        alertDelayTimer = NULL;
    }
}

//启动alert提示
void Toolkits::alertMSG(int x, int y, const QString &alertText) {
    this->alert_x = x + (this->parent_width / 2) - (this->alert_width  / 2);
    this->alert_y = y + (this->parent_height /2) - (this->alert_height  / 2);

    this->ay = this->alert_y;
    this->ao = 0.0;
    this->alertBG->move(this->alert_x, this->alert_y);
    this->alertGOE->setOpacity(this->ao);
    this->alertBG->setMSG(alertText);
    this->alertBG->show();
    this->alertTimer->start(15);
}
//alert提示框的步处理
void Toolkits::updateAlert()  {
    if(this->ao < 0.90){
        this->ao += 0.02;
        this->alertGOE->setOpacity(this->ao);
    }
    if(this->ay <= (this->alert_y - 150)){
        this->alertTimer->stop();
        //5秒后自动关闭alert提示框
        this->alertDelayTimer->start(1000);
    }else{
        this->ay -= 3;
        this->alertBG->move(this->alert_x,this->ay);
    }
}
//隐藏alert提示框
void Toolkits::hideAlert() {
    this->alertBG->hide();
    this->alertDelayTimer->stop();
}
