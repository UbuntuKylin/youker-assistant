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
#include "progressdialog.h"
#include "ui_progressdialog.h"

ProgressDialog::ProgressDialog(QString msg, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgressDialog)
{
    ui->setupUi(this);
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    ui->label->setStyleSheet("QLabel {color: green; font-size: 12px}");
    ui->label->setText(msg);
    ui->progressBar->setStyleSheet("QProgressBar {border: 1px solid grey;border-radius: 2px;text-align: center;}"
                                    "QProgressBar::chunk {background-color: #05B8CC;width: 10px;}");
}

ProgressDialog::~ProgressDialog()
{
    delete ui;
}
