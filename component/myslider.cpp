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

    minlable->setFixedSize(QSize(70,30));
    minlable->setText(tr("Mintip"));
    minlable->setStyleSheet("color:rgb(0,0,0,185);");
    minlable->setAlignment(Qt::AlignLeft);
    minlable->move(0,50);

    maxlable->setFixedSize(QSize(70,30));
    maxlable->setText(tr("Maxtip"));
    maxlable->setStyleSheet("color:rgb(0,0,0,185);");
    maxlable->setAlignment(Qt::AlignRight);
    maxlable->move(490,50);

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
    if(tmpMap.contains("minimum") && !tmpMap["minimum"].isNull())
    {
        minlable->setText(tmpMap["minimum"].toString());
        minlable->update();
        min = tmpMap["minimum"].toString().mid(0,3).toFloat();
    }
    if(tmpMap.contains("maximum") && !tmpMap["maximum"].isNull())
    {
        maxlable->setText(tmpMap["maximum"].toString());
        maxlable->update();
        max = tmpMap["maximum"].toString().mid(0,3).toFloat();
    }
    if(tmpMap.contains("cur_freq") && !tmpMap["cur_freq"].isNull())
    {
        if(tmpMap["cur_freq"].toString() == "0")
        {
            cur_value = min*1000;
        }
        else
        {
            cur_value = tmpMap["cur_freq"].toString().mid(0,3).toFloat()*1000;
        }
    }

    this->setRange(min*1000,max*1000);
    this->setValue(cur_value);
    tiplable->setText(QString::number(cur_value)+"MHz");
    tiplable->move((this->width()-tiplable->width())*(this->value()-min*1000)/(this->maximum()-this->minimum()),5);
    this->setSingleStep(10);
//    qDebug() << Q_FUNC_INFO << min  << max << (max-min)*10 << this->value() << cur_value;
}

void mySlider::keyPressEvent(QKeyEvent *event)
{
//    qDebug() << Q_FUNC_INFO << event->key();
    QAbstractSlider::keyPressEvent(event);
    updateTipLabel();
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
    updateTipLabel();
    QSlider::mouseReleaseEvent(event);
}

void mySlider::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << Q_FUNC_INFO << event->pos().rx();
    updateTipLabel();
    QSlider::mouseMoveEvent(event);
}

void mySlider::wheelEvent(QWheelEvent *event)
{
    QAbstractSlider::wheelEvent(event);
    updateTipLabel();
}

void mySlider::updateTipLabel()
{
    tiplable->setText(QString::number(this->value())+"MHz");
    tiplable->move((this->width()-tiplable->width())*(this->value()-min*1000)/(this->maximum()-this->minimum()),5);
}
