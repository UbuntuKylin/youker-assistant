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

#include "QDesktopWidget"

#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include <QtGui>

AboutDialog::AboutDialog(QWidget *parent, const QString &version) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    ui->versionlabel->setText(version);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    move((QApplication::desktop()->width() - this->width())/2, (QApplication::desktop()->height() - this->height())/2);
    ui->tabWidget->setCurrentIndex(0);
    connect(ui->homeBtn, SIGNAL(linkActivated(QString)), this, SLOT(openUrl(QString)));
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::on_closeBtn_clicked()
{
//    QDialog::accept();
    this->hide();
}

void AboutDialog::openUrl(QString url)
{
    QDesktopServices::openUrl(QUrl(url));
}
