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

#include "titlewidget.h"
#include "mainwindow.h"

TitleWidget::TitleWidget(QWidget *parent, QString arch, QString os)
	: QWidget(parent)
{
    this->setFixedSize(900, 36);
    min_button = new SystemButton();
    close_button = new SystemButton();
    skin_button = new SystemButton();
    main_menu_button = new SystemButton();
    min_button->loadPixmap(":/sys/res/sysBtn/min_button.png");
    close_button->loadPixmap(":/sys/res/sysBtn/close_button.png");
    skin_button->loadPixmap(":/sys/res/sysBtn/skin_button.png");
    main_menu_button->loadPixmap(":/sys/res/sysBtn/main_menu.png");
    min_button->setFocusPolicy(Qt::NoFocus);
    close_button->setFocusPolicy(Qt::NoFocus);
    skin_button->setFocusPolicy(Qt::NoFocus);
    main_menu_button->setFocusPolicy(Qt::NoFocus);

    QHBoxLayout *title_layout = new QHBoxLayout();
//    if(arch == "aarch64" || os == "Kylin" || os == "YHKylin")
//    {
        title_layout->addWidget(main_menu_button, 0, Qt::AlignTop);
        title_layout->addWidget(skin_button, 0, Qt::AlignTop);
        title_layout->addWidget(min_button, 0, Qt::AlignTop);
        title_layout->addWidget(close_button, 0, Qt::AlignTop);
//    }
//    else
//    {
//        title_layout->addWidget(close_button, 0, Qt::AlignTop);
//        title_layout->addWidget(min_button, 0, Qt::AlignTop);
//        title_layout->addWidget(skin_button, 0, Qt::AlignTop);
//        title_layout->addWidget(main_menu_button, 0, Qt::AlignTop);
//    }

    title_layout->addStretch();
    title_layout->setSpacing(0);
    title_layout->setContentsMargins(0, 0, 5, 0);

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addLayout(title_layout);
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);

    setLayout(main_layout);

    is_move = false;
}

TitleWidget::~TitleWidget()
{
    if(min_button != NULL)
    {
        delete min_button;
        min_button = NULL;
    }
    if(close_button != NULL)
    {
        delete close_button;
        close_button = NULL;
    }
    if(skin_button != NULL)
    {
        delete skin_button;
        skin_button = NULL;
    }
    if(main_menu_button != NULL)
    {
        delete main_menu_button;
        main_menu_button = NULL;
    }
}

void TitleWidget::initConnect() {
    connect(min_button, SIGNAL(clicked()), p_mainwindow, SLOT(showMinimized()));
    connect(close_button, SIGNAL(clicked()), this, SIGNAL(closeApp()));
    connect(skin_button, SIGNAL(clicked()), p_mainwindow, SLOT(openSkinCenter()));
    connect(main_menu_button, SIGNAL(clicked()), p_mainwindow, SLOT(showMainMenu()));
}

/*void TitleWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setOpacity(0.05);

    int penWidth = 1;
    QPainterPath framePath;
    framePath.addRoundedRect(QRect(rect().x() + penWidth, rect().y() + penWidth, rect().width() - penWidth * 2, rect().height() - penWidth * 2), 4, 4);//背景弧度
    painter.setClipPath(framePath);

    QPen framePen;
    framePen.setColor(QColor("#F5F5F5"));
    painter.setOpacity(0.2);
    painter.drawPath(framePath);
}*/
