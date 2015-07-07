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

#include "cacheactionwidget.h"
#include "mainwindow.h"
#include <QLabel>

CacheActionWidget::CacheActionWidget(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize(900, 150);
    this->setAutoFillBackground(true);
    this->setObjectName("transparentWidget");

    img_label = new QLabel();
    title_label = new QLabel();
    description_label = new QLabel();

    img_label->setScaledContents(true);//自动缩放,显示图像大小自动调整为Qlabel大小
    QPixmap label_pixmap("://res/cache.png");
    img_label->setPixmap(label_pixmap);
    img_label->setFixedSize(label_pixmap.size());

    title_label->setObjectName("whiteLabel");
    description_label->setWordWrap(true);//QLabel自动换行
    description_label->setObjectName("tipLabel");

    QVBoxLayout *layout1 = new QVBoxLayout();
    layout1->addStretch();
    layout1->addWidget(title_label);
    layout1->addWidget(description_label);
    layout1->addStretch();
    layout1->setSpacing(15);
    layout1->setMargin(0);
    layout1->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *layout2 = new QHBoxLayout();
    layout2->addWidget(img_label, 0, Qt::AlignVCenter);
    layout2->addLayout(layout1);
    layout2->setSpacing(20);
    layout2->setMargin(0);
    layout2->setContentsMargins(20, 20, 0, 0);

    setLayout(layout2);

    this->setLanguage();
}

CacheActionWidget::~CacheActionWidget()
{
    if(img_label != NULL) {
        delete img_label;
        img_label = NULL;
    }
    if(title_label != NULL) {
        delete title_label;
        title_label = NULL;
    }
    if(description_label != NULL) {
        delete description_label;
        description_label = NULL;
    }
}

void CacheActionWidget::setLanguage()
{
    title_label->setText(tr("Cleaning up the system cache"));
    description_label->setText(tr("Deep cleaning up the system cache, to save disk space"));
}
