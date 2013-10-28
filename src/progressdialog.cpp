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
//#include "ui_progressdialog.h"
#include <QDebug>
#include <QMouseEvent>
#include <stdio.h>

//progressFlag:判断是软件源更新还是软件操作，如果是软件源更新，则为true，qt的进度条隐藏;如果是软件操作，则为默认的false，qt的进度条显示
extern bool progressFlag;

ProgressDialog::ProgressDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgressDialog)
{
    ui->setupUi(this);
    progressFlag = false;
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    ui->label->setStyleSheet("QLabel {color: green; font-size: 12px}");
//    ui->label_2->setStyleSheet("QLabel {color: black; font-size: 12px}");
//    ui->progressBar->setStyleSheet("QProgressBar {border: 1px solid grey;border-radius: 2px;text-align: center;}"
//                                    "QProgressBar::chunk {background-color: #6be2fa;width: 10px;}");
    QDesktopWidget* desktop = QApplication::desktop();
    ratio_sus=1;
    move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);
}

ProgressDialog::~ProgressDialog() {
    delete ui;
}

void ProgressDialog::reset_status() {
    ratio_sus=0;
    ui->label_2->setText(tr("%1").arg(ratio_sus)+"%");
    update();
    ui->label->setText("开始");
    this->hide();
}

//得到下载或者是操作过程中发送过来的数据，显示在进度条上
void ProgressDialog::setDynamicSoftwareProgress(QString type, QString msg) {
    if(this->isHidden()) {
        this->show();
    }
    if(type == "down_start") {
        ui->label->setText("开始下载");
//        ui->progressBar->setValue(0);
        ui->label_2->setText(tr("%1").arg(ratio_sus)+"%");
        ratio_sus=1;
    }
    else if(type == "down_pulse"){
        if(!msg.isEmpty()) {
            if(msg.contains("download_bytes") && msg.contains("total_bytes")) {
                QStringList process_value = msg.split(",");
                if (process_value.size() == 4) {
                    QStringList download_bytes = process_value.at(0).split(":");
                    double download_bytes_value = download_bytes.at(1).toDouble();
                    QStringList total_bytes = process_value.at(1).split(":");
                    double total_bytes_value = total_bytes.at(1).toDouble();
                    double percent = download_bytes_value / total_bytes_value;
                    QString ratio = QString::number(percent, 'f', 2);
                    double trans = ratio.toDouble() * 100;
                    ratio = QString::number(trans,'f',0);
//                    ui->progressBar->setValue(ratio.toInt());
                    ratio_sus=ratio.toInt();
                    if(progressFlag) {//更新软件源的下载，此时不需要qt的这个进度条，进度状态是在QML上显示的，所以隐藏进度条
                        this->hide();
                        softwareSourceUpdateProgressToSudoDispather(ratio);
                    }
                    else {//软件操作的下载
                        ui->label->setText("正在下载安装包...");
                        ui->label_2->setText(tr("%1").arg(ratio_sus)+"%");
                    }
                }
            }
        }
    }
    else if(type == "down_stop") {
        if(progressFlag) {//更新软件源的下载，此时如果下载完成，则代码整个更新的过程已经结束，需要把进度条隐藏了。
            this->hide();
        }
        else {//软件操作的下载，此时下载完成，并不是整个操作过程的结束，所以进度条不能隐藏。
            ui->label->setText("下载完成");
            ratio_sus=0;
            ui->label_2->setText(tr("%1").arg(ratio_sus)+"%");
        }
    }
    else if(type == "apt_start"){
        if(this->isHidden()) {
            this->show();
        }
        ui->label->setText("开始");
//        ui->progressBar->setValue(0);
        ui->label_2->setText(tr("%1").arg(ratio_sus)+"%");
        ratio_sus=1;

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
                    ui->label->setText("正在进行:" + act);
//                    ui->progressBar->setValue(value);
                    ratio_sus=value;
                    ui->label_2->setText(tr("%1").arg(ratio_sus)+"%");
                }
            }
        }
    }
    else if(type == "apt_stop") {
        ui->label->setText("完成");
//        ui->progressBar->setValue(0);
        ratio_sus=100;
        ui->label_2->setText(tr("%1").arg(ratio_sus)+"%");
        update();
//        sleep(2000);
        QTimer *timer = new QTimer(this);
        timer->setInterval(2000);
        connect(timer,SIGNAL(timeout()),this,SLOT(reset_status()));
        timer->start();
        ratio_sus=100;
        update();
    }
    update();
}


void ProgressDialog::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        dragPos = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void ProgressDialog::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton ) {
        move(event->globalPos() - dragPos);
        setWindowOpacity(0.5);
    }
    event->accept();
}

void ProgressDialog::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        setWindowOpacity(1);
    }
    event->accept();
}


QSize ProgressDialog::sizeHint()const {
    return QSize(height(),height());
}

void ProgressDialog::resizeEvent(QResizeEvent *) {
    update();
}

void ProgressDialog::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QStyleOption opt;
    QPixmap progress_bar1;
    QPixmap progress_bar2;
    QPixmap background;
    background.load(":/pixmap/image/progress-bg.png");
    progress_bar1.load(":/pixmap/image/progress-bar1.png");
    progress_bar2.load(":/pixmap/image/progress-bar2.png");
    painter.drawPixmap(0,0, background);
    painter.setPen(Qt::transparent);
    opt.init(this);
    painter.drawPixmap(10,30,progress_bar1);
//    painter.drawPixmap(10,30,progress_bar2,0,0,progress_bar2.width()*(ratio_sus*0.01),progress_bar2.height());
    painter.drawPixmap(10,30,progress_bar2.width()*(ratio_sus*0.01),progress_bar2.height(),progress_bar2);
    style()->drawPrimitive(QStyle::PE_Widget,&opt,&painter,this);
}
