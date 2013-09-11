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
#include <QDebug>
#include <QMouseEvent>
ProgressDialog::ProgressDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgressDialog)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(Qt::FramelessWindowHint);
//    this->setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    ui->label->setStyleSheet("QLabel {color: green; font-size: 12px}");
    ui->progressBar->setStyleSheet("QProgressBar {border: 1px solid grey;border-radius: 2px;text-align: center;}"
                                    "QProgressBar::chunk {background-color: #05B8CC;width: 10px;}");
    QDesktopWidget* desktop = QApplication::desktop();
    move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);
}

ProgressDialog::~ProgressDialog()
{
    delete ui;
}

void ProgressDialog::setValue(QString type, QString msg) {
    qDebug() << "kobe msg->";
    qDebug() << type;
    qDebug() << msg;
    if(type == "down_start") {
        ui->label->setText("开始下载");
    }
    else if(type == "down_pulse"){
        ui->label->setText("正在下载:" + msg);
    }
    else if(type == "down_stop") {
        ui->label->setText("下载完成");
    }
    else if(type == "apt_start"){
        ui->label->setText("开始");
    }
    else if(type == "apt_pulse"){
        if(!msg.isEmpty()) {
            if(msg.contains(",")) {
                QStringList process_value = msg.split(",");
                if (process_value.size() == 2) {
                    QStringList status_value = process_value.at(0).split(":");
                    int value = status_value.at(1).toInt();
                    QStringList action_value = process_value.at(1).split(":");
                    QString act = action_value.at(1);
                    qDebug() << "------------------";
                    qDebug() << value;
                    qDebug() << act;
                    ui->label->setText("正在进行:" + act);
                    ui->progressBar->setValue(value);
                }
            }
        }
    }
    else if(type == "apt_stop") {
        ui->label->setText("完成");
//        this->close();
    }
}


void ProgressDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        dragPos = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }

}

void ProgressDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton )
    {
        move(event->globalPos() - dragPos);
        setWindowOpacity(0.5);
    }
    event->accept();

}

void ProgressDialog::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        setWindowOpacity(1);
    }
    event->accept();
}
