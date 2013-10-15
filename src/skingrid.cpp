/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
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

#include "skingrid.h"

SkinGrid::SkinGrid(QWidget *parent)
    :QWidget(parent)
{
    this->setFixedSize(140, 160);
    mouse_press = false;
    mouse_enter = false;
    skin_icon = new QLabel();
    skin_title = new QLabel();
    this->setCursor(Qt::PointingHandCursor);
    skin_icon->setScaledContents(true);
    skin_icon->setFixedSize(100, 65);
    QVBoxLayout *background_layout = new QVBoxLayout();
    background_layout->addWidget(skin_icon, 0, Qt::AlignCenter);
    background_layout->addWidget(skin_title, 0, Qt::AlignCenter);
    background_layout->setSpacing(5);
    background_layout->setContentsMargins(0, 10, 0, 10);
    this->setLayout(background_layout);
}


SkinGrid::~SkinGrid() {

}

void SkinGrid::showSkinGrid(QString picName, QString skinName, bool flag) {
    if(flag) {
        QString background_name = picName + "_bg";
        this->picName = background_name;
        QPixmap pixmap(background_name);
        skin_icon->setPixmap(pixmap);
        skin_title->setText(skinName);
    }
}

void SkinGrid::paintEvent(QPaintEvent *) {
    if(mouse_enter) {
        QPainter painter(this);
        QPen pen(QColor(210, 225, 230));
        painter.setPen(pen);
        painter.drawRoundRect(0,0,this->width()-1, this->height()-1, 5, 5);
    }
}

void SkinGrid::mousePressEvent(QMouseEvent * event) {
    if(event->button() == Qt::LeftButton) {
        mouse_press = true;
        emit skinSignal(picName);//触发信号开始更换皮肤
    }
}

void SkinGrid::mouseReleaseEvent(QMouseEvent *) {
    mouse_press = false;
}

void SkinGrid::enterEvent(QEvent *event) {
    mouse_enter = true;
    update();
}

void SkinGrid::leaveEvent(QEvent *event) {
    mouse_enter = false;
    update();
}
