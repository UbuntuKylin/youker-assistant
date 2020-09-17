/*
 * Copyright (C) 2013 ~ 2015 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  tang guang   tangguang@kylinos.cn
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

#include "myslider.h"
#include <QDebug>
#include <QString>

mySlider::mySlider(QWidget *parent):QSlider(parent)
{
//    QPalette palette1;
//    palette1.setColor(QPalette::Background, Qt::green);
//    this->setPalette(palette1);

//    this->setFixedSize(parent->width(),40);
    this->setTickInterval(10);

    tiplable=new QLabel(this);
    minlable=new QLabel(this);
    maxlable=new QLabel(this);

    minlable->setFixedSize(QSize(60,20));
    minlable->setAlignment(Qt::AlignCenter);
    minlable->setText("mintip");
    minlable->setStyleSheet("color:rgb(0,0,0,185);");
    minlable->setAlignment(Qt::AlignLeft);
    minlable->move(0,50);

    maxlable->setFixedSize(QSize(60,20));
    maxlable->setAlignment(Qt::AlignCenter);
    maxlable->setText("maxtip");
    maxlable->setStyleSheet("color:rgb(0,0,0,185);");
    maxlable->setAlignment(Qt::AlignRight);
    maxlable->move(500,50);

    tiplable->setFixedSize(QSize(60,24));
    //设置游标背景为白色
//    tiplable->setAutoFillBackground(true);
//    QPalette palette;
//    palette.setColor(QPalette::Background, Qt::green);
//    tiplable->setPalette(palette);
    tiplable->setStyleSheet("background:rgba(231,231,231,1);color:rgb(0,0,0,185);\
                             border-radius:4px;font-size:14px");

    tiplable->setAlignment(Qt::AlignCenter);

//    tiplable->setVisible(false);
    tiplable->setText(QString::number(this->value()) + "MHz");
    tiplable->move(0,5);
}

mySlider::~mySlider()
{

}

void mySlider::setRangeLable(QMap<QString, QVariant> tmpMap)
{
//    qDebug() << Q_FUNC_INFO <<tmpMap;
    if(tmpMap.isEmpty()){
        qDebug() << Q_FUNC_INFO <<" Parameters are null.";
        return;
    }

    QMap<QString ,QVariant> map = tmpMap;
    QMap<QString ,QVariant>::iterator it;
    for( it=map.begin() ; it!=map.end() ; ++it )
    {
        if(it.key() == "maximum" && !it.value().isNull())
        {
            maxlable->setText(it.value().toString());
            maxlable->update();
            max = it.value().toString().mid(0,3).toFloat();
        }
        else if(it.key() == "minimum" && !it.value().isNull())
        {
            minlable->setText(it.value().toString());
            minlable->update();
            min = it.value().toString().mid(0,3).toFloat();
        }
        else if(it.key() == "cur_freq" && !it.value().isNull())
        {
            if(it.value().toString() == "0")
            {
                cur_value = min*1000;
            }
            else
            {
                cur_value = it.value().toString().mid(0,3).toFloat()*1000;
            }
        }
    }

    this->setRange(min*1000,max*1000+1);
    this->setValue(cur_value);
    tiplable->setText(QString::number(cur_value)+"MHz");
    tiplable->move((this->width()-tiplable->width())*(this->value()-800)/(this->maximum()-this->minimum()),5);
    this->setSingleStep(10);
//    qDebug() << Q_FUNC_INFO << min  << max << (max-min)*10 << this->value() << cur_value;
}

void mySlider::mousePressEvent(QMouseEvent *event)
{
//    if(!tiplable->isVisible())
//    {
//        tiplable->setVisible(true);
//        tiplable->setText(QString::number(this->value()));
//    }
//    tiplable->setText(QString::number(this->value())+"Hz");
//    tiplable->move((this->width()-tiplable->width())*this->value()/(this->maximum()-this->minimum()),5);
    QSlider::mousePressEvent(event);
}

void mySlider::mouseReleaseEvent(QMouseEvent *event)
{
//    if(tiplable->isVisible())
//    {
//        tiplable->setVisible(false);
//    }
    tiplable->setText(QString::number(this->value())+"MHz");
    tiplable->move((this->width()-tiplable->width())*(this->value()-800)/(this->maximum()-this->minimum()),5);
    QSlider::mouseReleaseEvent(event);
}

void mySlider::mouseMoveEvent(QMouseEvent *event)
{
    tiplable->setText(QString::number(this->value())+"MHz");
    tiplable->move((this->width()-tiplable->width())*(this->value()-800)/(this->maximum()-this->minimum()),5);
    QSlider::mouseMoveEvent(event);
}
