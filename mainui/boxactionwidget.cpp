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

#include "boxactionwidget.h"
#include "mainwindow.h"
#include <QDebug>

BoxActionWidget::BoxActionWidget(QWidget *parent)
	: QWidget(parent)
{
    this->setFixedSize(900, 150);
    this->setAutoFillBackground(true);
    this->setObjectName("transparentWidget");

    img_label = new QLabel();
    title_label = new QLabel();
    more_btn = new QPushButton();

    img_label->setScaledContents(true);//自动缩放,显示图像大小自动调整为Qlabel大小
    QPixmap label_pixmap("://res/toolkits.png");
    img_label->setPixmap(label_pixmap);
    img_label->setFixedSize(label_pixmap.size());
    title_label->setObjectName("whiteLabel");
    title_label->setWordWrap(true);//QLabel自动换行
    more_btn->setFocusPolicy(Qt::NoFocus);
//    more_btn->setObjectName("transparentButton");
    more_btn->setObjectName("whiteButton");
    more_btn->hide();
//    title_label->setFixedWidth(400);
    title_label->setMinimumWidth(500);
    title_label->setMaximumWidth(600);


    QHBoxLayout *layout1 = new QHBoxLayout();
    layout1->addWidget(img_label);
    layout1->addWidget(title_label);
    layout1->addWidget(more_btn);
    layout1->addStretch();
    layout1->setSpacing(15);
    layout1->setContentsMargins(20, 20, 0, 0);
    setLayout(layout1);

    this->setLanguage();
}

BoxActionWidget::~BoxActionWidget()
{
    if(img_label != NULL) {
        delete img_label;
        img_label = NULL;
    }
    if(title_label != NULL) {
        delete title_label;
        title_label = NULL;
    }
    if(more_btn != NULL) {
        delete more_btn;
        more_btn = NULL;
    }
}


void BoxActionWidget::setLanguage()
{
    title_label->setText(tr("Provide a practical and lightweight tool, create fast and convenient experience for you"));//提供轻巧实用工具，为您打造快捷方便的体验
    more_btn->setText(tr("More App"));
}
