/*
 * Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd.
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
#include "alertdialog.h"
#include "ui_alertdialog.h"

AlertDialog::AlertDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlertDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    connect(ui->alertBG,SIGNAL(clicked()),this,SLOT(hide()));
    ui->alertBG->setStyleSheet("QPushButton{background-image:url('://res/alert.png');border:0px;padding-top:-10px;}");
    ui->alertBG->setFocusPolicy(Qt::NoFocus);
//    this->hide();
}

AlertDialog::~AlertDialog()
{
    delete ui;
}

void AlertDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void AlertDialog::setMSG(QString msg)
{
    ui->alertBG->setText(msg);
}
