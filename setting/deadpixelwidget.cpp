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

#include "deadpixelwidget.h"

DeadpixelWidget::DeadpixelWidget(QWidget *parent) :
    QWidget(parent)
{
//    splitter = new QSplitter();
//    splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    splitter->setOrientation(Qt::Vertical);
//    splitter->setHandleWidth(1);

//    top_widget = new QWidget();
//    bottom_widget = new QWidget();
//    left_widget = new QWidget();
//    left_widget->setFixedWidth(240);
//    right_widget = new QWidget();

//    title_label = new QLabel();
//    title_label->setFixedHeight(20);
//    description_label = new QLabel();
//    description_label->setFixedHeight(20);
//    back_btn = new QPushButton();

//    QVBoxLayout *v_layout = new QVBoxLayout();
//    v_layout->addWidget(title_label);
//    v_layout->addWidget(description_label);
//    v_layout->setMargin(0);
//    v_layout->setSpacing(1);

//    QHBoxLayout *h_layout = new QHBoxLayout();
//    h_layout->addWidget(back_btn);
//    h_layout->addLayout(v_layout);
//    h_layout->addStretch();
//    top_widget->setLayout(h_layout);
//    top_widget->setFixedSize(900,60);
//    h_layout->setSpacing(20);
//    h_layout->setContentsMargins(20, 0, 0, 0);

    this->qtui = NULL;
    tip_label = new QLabel();
    tip_label->setWordWrap(true);//QLabel自动换行
    tip_label->setFixedWidth(500);
    ok_btn = new QPushButton();
    ok_btn->setFixedSize(91, 25);
    ok_btn->setObjectName("blackButton");
    ok_btn->setFocusPolicy(Qt::NoFocus);
//    QVBoxLayout *layout = new QVBoxLayout();
//    layout->addStretch();
//    layout->addWidget(tip_label);
//    layout->addWidget(ok_btn);
//    layout->addStretch();
//    bottom_widget->setLayout(layout);

//    splitter->addWidget(top_widget);
//    splitter->addWidget(bottom_widget);

    QHBoxLayout *main_layout = new QHBoxLayout(this);
//    main_layout->addWidget(splitter);
    main_layout->addStretch();
    main_layout->addWidget(tip_label);
    main_layout->addWidget(ok_btn);
    main_layout->addStretch();
    main_layout->setSpacing(0);
    main_layout->setMargin(0);
    main_layout->setContentsMargins(0, 0, 0, 0);
    setLayout(main_layout);

    this->setLanguage();
    this->initConnect();
}

DeadpixelWidget::~DeadpixelWidget()
{
    if(qtui != NULL)
    {
        delete qtui;
        qtui = NULL;
    }
}

void DeadpixelWidget::setLanguage()
{
//    title_label->setText(tr("Monitor Check"));
//    description_label->setText(tr("Monitor Check."));
//    back_btn->setText(tr("Back"));
    tip_label->setText(tr("Left-click to change the color, right-click to exit from this detection."));
    ok_btn->setText(tr("OK"));
}

void DeadpixelWidget::initConnect()
{
//    connect(back_btn, SIGNAL(clicked()), this, SIGNAL(showSettingMainWidget()));
    connect(ok_btn, SIGNAL(clicked()), this, SLOT(startMonitorCheck()));
}

void DeadpixelWidget::startMonitorCheck() {
    if (this->qtui)
    {
        delete this->qtui;
        this->qtui = NULL;
    }
    this->qtui = new QUIBO();
}
