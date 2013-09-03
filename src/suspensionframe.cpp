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
#include "suspensionframe.h"
#include "ui_suspensionframe.h"
#include <QMouseEvent>
SuspensionFrame::SuspensionFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SuspensionFrame)
{
    ui->setupUi(this);

    this->setWindowOpacity(1.0);
    ui->msglabel->setText("试试鼠标左键双击屏幕右上角监控球...");
    ui->title1->setText("电脑运行缓慢");
    ui->title2->setText("建议一键加速");
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    QDesktopWidget *desktop = QApplication::desktop();
    this->move(desktop->width() - this->width(), 80);
}

SuspensionFrame::~SuspensionFrame()
{
    delete ui;
}

void SuspensionFrame::get_sysc_data(QString upspeed, QString downspeed, QString ratio, int used_memory, QString free_memory, QString cpu_ratio) {
    ui->uplabel->setText(upspeed + "K/s");
    ui->downlabel->setText(downspeed + "K/s");
    ui->ratiolabel->setText(ratio + "%");
//    qDebug() << "2222222222->";
//    qDebug() << cpu_ratio;
//    qDebug() << used_memory;
//    qDebug() << free_memory;
}

void SuspensionFrame::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        dragPos = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }

}

void SuspensionFrame::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton )
    {
        move(event->globalPos() - dragPos);
        setWindowOpacity(0.5);
    }
    event->accept();

}

void SuspensionFrame::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        setWindowOpacity(1);
    }
    event->accept();
}

void SuspensionFrame::on_descBtn_clicked()
{

}

void SuspensionFrame::on_fastBtn_clicked()
{
    emit accelerate_memory();
}
