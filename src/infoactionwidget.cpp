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

#include "infoactionwidget.h"
#include "mainwindow.h"

InfoActionWidget::InfoActionWidget(QWidget *parent)
	: QWidget(parent)
{
    this->setFixedSize(900, 150);
    this->setAutoFillBackground(true);
    this->setObjectName("transparentWidget");

    img_label = new QLabel();
    suggest_label = new QLabel();

    img_label->setScaledContents(true);//自动缩放,显示图像大小自动调整为Qlabel大小
    QPixmap label_pixmap("://res/systeminfo.png");
    img_label->setPixmap(label_pixmap);
    img_label->setFixedSize(label_pixmap.size());

    suggest_label->setObjectName("whiteLabel");
    suggest_label->setWordWrap(true);//QLabel自动换行

    QHBoxLayout *layout2 = new QHBoxLayout();
    layout2->addWidget(img_label, 0, Qt::AlignVCenter);
    layout2->addWidget(suggest_label, 0, Qt::AlignVCenter);
    layout2->setSpacing(20);
    layout2->setMargin(0);
    layout2->setContentsMargins(20, 20, 0, 0);

    setLayout(layout2);

    this->setLanguage();
}

InfoActionWidget::~InfoActionWidget()
{
    if(img_label != NULL) {
        delete img_label;
        img_label = NULL;
    }
    if(suggest_label != NULL) {
        delete suggest_label;
        suggest_label = NULL;
    }
}


void InfoActionWidget::setLanguage()
{
    suggest_label->setText(tr("Understand hardware information, provide more convenient channel to obtain hardware information"));//了解电脑硬件详细信息，为用户提供更加方便的获取硬件信息渠道
}
