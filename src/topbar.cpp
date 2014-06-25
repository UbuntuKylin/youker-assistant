/*
 * Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd.
 * Author: Kobe Lee
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

#include "topbar.h"

TopBar::TopBar(QWidget *parent)
    :QWidget(parent)
{
    close_button = new KButton(this);
    close_button->setPicName(":/pixmap/image/closeBtn");
    close_button->resize(QSize(29, 29));
    min_button = new KButton(this);
    min_button->setPicName(":/pixmap/image/minBtn");
    min_button->resize(QSize(29, 29));
    connect(min_button, SIGNAL(clicked()), this, SLOT(showMinWidget()));
    connect(close_button, SIGNAL(clicked()), this, SLOT(hideWidget()));
    QHBoxLayout *title_layout = new QHBoxLayout();
    title_layout->addWidget(close_button, 0, Qt::AlignTop);
    title_layout->addWidget(min_button, 0, Qt::AlignTop);
    title_layout->addStretch();
    title_layout->setSpacing(0);
    title_layout->setContentsMargins(0, 0, 5, 0);
    setLayout(title_layout);
    setFixedHeight(29);
}

TopBar::~TopBar()
{
    if (min_button != NULL) {
        delete min_button;
    }
    if (close_button != NULL) {
        delete close_button;
    }
}

void TopBar::showMinWidget() {
    emit this->readyShowMin();
}

void TopBar::hideWidget() {
    emit this->readyHideWidget();
}
