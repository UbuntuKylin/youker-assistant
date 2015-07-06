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
#include "normalcard.h"
#include "ui_normalcard.h"
#include <QDebug>

NormalCard::NormalCard(QString title, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NormalCard)
{
    ui->setupUi(this);
//    ui->raiseWidget->setStyleSheet("QWidget{background:transparent url(:/background/res/skin/1.png);icon-size:20px 5px}");
    ui->raiseWidget->setStyleSheet("QWidget{background:transparent url(://res/theme-cover.png);}");
    ui->baseWidget->setStyleSheet("QWidget{background:transparent;}");
    this->icon_name = title;
    iconpath=QString(":/gtk/res/theme/" + title + ".png");
    QPixmap pixmap(iconpath);
    if(pixmap.isNull())
    {
        pixmap = QPixmap(":/gtk/res/theme/disappear.png");
    }
    pixmap.copy(QRect(0,0,119,119));
    ui->icon->setPixmap(pixmap);
//    ui->icon->setStyleSheet("QLabel{background-image:url('" + iconpath + "')}");
    ui->icon->installEventFilter(this);
    ui->raiseWidget->installEventFilter(this);
    ui->name->setStyleSheet("QLabel{background: transparent;color:#666666;方正黑体_GBK;font-size: 14px;text-align: center;}");
    ui->name->setText(title);
    ui->using_label->setStyleSheet("QLabel{background-image:url('://res/choose.png')}");
    ui->using_label->hide();
}

NormalCard::~NormalCard() {
    delete ui;
}

void NormalCard::showUsingLogo(bool flag)
{
    if(flag) {
        ui->using_label->show();
        ui->raiseWidget->hide();
    }
    else {
        ui->using_label->hide();
        ui->raiseWidget->show();
    }
}

void NormalCard::enterEvent(QEvent *)
{

}

void NormalCard::leaveEvent(QEvent *)
{

}

bool NormalCard::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == ui->icon || obj == ui->raiseWidget){
        if(event->type() == QEvent::MouseButtonRelease){
            emit this->sendSelectThemeName(this->icon_name);
        }
    }
    return QObject::eventFilter(obj, event);
}
