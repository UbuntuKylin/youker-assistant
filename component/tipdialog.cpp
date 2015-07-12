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

#include "tipdialog.h"
#include "mainwindow.h"
#include <QDebug>
#include <QVBoxLayout>

TipDialog::TipDialog(QWidget *parent, QString msg)
    :QDialog(parent), message(msg)
{
    this->setStyleSheet("QDialog{border: 1px solid white;border-radius:1px;background-color: #ffffff;}");
    this->setFixedSize(410, 180);
    setWindowFlags(Qt::FramelessWindowHint);

    title_bar = new KylinTitleBar();
    initTitleBar();
    msg_label = new QLabel();
    msg_label->setWordWrap(true);//QLabel自动换行
    msg_label->setFixedWidth(380);
    msg_label->setText(message);
    okBtn = new QPushButton();
    okBtn->setFixedSize(91, 25);
    okBtn->setObjectName("blackButton");
    okBtn->setFocusPolicy(Qt::NoFocus);

    QHBoxLayout *h_layout = new QHBoxLayout();
    h_layout->addStretch();
    h_layout->addWidget(okBtn);
    h_layout->setMargin(0);
    h_layout->setContentsMargins(0,0,0,0);

    QVBoxLayout *v_layout  = new QVBoxLayout();
    v_layout->addWidget(msg_label);
    v_layout->addLayout(h_layout);
    v_layout->setSpacing(40);
    v_layout->setMargin(0);
    v_layout->setContentsMargins(10, 40, 10, 0);

    QVBoxLayout *main_layout  = new QVBoxLayout();
    main_layout->addWidget(title_bar);
    main_layout->addLayout(v_layout);
    main_layout->addStretch();
    main_layout->setSpacing(0);
    main_layout->setMargin(0);
    main_layout->setContentsMargins(0, 0, 0, 0);
    setLayout(main_layout);
    this->setLanguage();
    this->initConnect();
}

TipDialog::~TipDialog()
{
    if(title_bar != NULL) {
        delete title_bar;
        title_bar = NULL;
    }
    if(msg_label != NULL) {
        delete msg_label;
        msg_label = NULL;
    }
    if(okBtn != NULL) {
        delete okBtn;
        okBtn = NULL;
    }
}

void TipDialog::setLanguage()
{
    okBtn->setText(tr("OK"));
}


void TipDialog::onOKButtonClicked()
{
    this->close();
}

void TipDialog::initConnect()
{
    connect(title_bar,SIGNAL(closeDialog()), this, SLOT(onCloseButtonClicked()));
    connect(okBtn,SIGNAL(clicked()), this, SLOT(onOKButtonClicked()));
}

void TipDialog::onCloseButtonClicked()
{
    this->close();
}

void TipDialog::initTitleBar()
{
    title_bar->setTitleWidth(410);
    title_bar->setTitleName(tr("Tip Dialog"));
    title_bar->setTitleBackgound(":/background/res/skin/1.png");
}
