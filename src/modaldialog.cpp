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

#include "modaldialog.h"
#include "ui_modaldialog.h"
#include <QMouseEvent>

ModalDialog::ModalDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModalDialog)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(Qt::FramelessWindowHint);

    ui->widget->setAutoFillBackground(true);
    QPalette palette;
    QPixmap img(":/pixmap/image/titlebg.png");
    palette.setBrush(QPalette::Window, img);//标题栏背景颜色
    ui->widget->setPalette(palette);
    //http://www.atool.org/colorpicker.php
    ui->widget_2->setAutoFillBackground(true);
    palette.setColor(QPalette::Background, QColor(228,242,252));//#e4f2fc
    ui->widget_2->setPalette(palette);

    ui->btn_close->installEventFilter(this);
    ui->btn_min->installEventFilter(this);
    ui->okButton->installEventFilter(this);
    ui->closeButton->installEventFilter(this);
    ui->btn_close->setStyleSheet("border-image:url(:/pixmap/image/closeBtn.png)");
    ui->btn_min->setStyleSheet("border-image:url(:/pixmap/image/minBtn.png)");
    ui->okButton->setStyleSheet("QPushButton {border-image:url(:/pixmap/image/button12-gray.png);}"
                "QPushButton:hover{border-image:url(:/pixmap/image/button12-gray-hover.png);}");
    ui->closeButton->setStyleSheet("QPushButton {border-image:url(:/pixmap/image/button12-gray.png);}"
                "QPushButton:hover{border-image:url(:/pixmap/image/button12-gray-hover.png);}");
    //QLabel自动换行
    ui->displaylabel->setWordWrap(true);
    ui->displaylabel->setText(tr("Left-click to change the color, right-click to exit from this detection."));//点击鼠标左键进行更换颜色检测操作，点击鼠标右键退出检测。
    QObject::connect(ui->okButton,SIGNAL(clicked()),this,SLOT(accept()));
    QObject::connect(ui->closeButton,SIGNAL(clicked()),this,SLOT(reject()));
    this->qtui = NULL;
}

ModalDialog::~ModalDialog() {
    delete ui;
}

void ModalDialog::on_closeButton_clicked() {
    close();
    QDialog::destroy(true);
}

void ModalDialog::on_okButton_clicked() {
    //开始屏幕检测
    monitor_check();
}

void ModalDialog::monitor_check() {
    if (this->qtui) {
        delete this->qtui;
    }
    this->qtui = new QUIBO();
}

bool ModalDialog::eventFilter(QObject *obj, QEvent *event) {
    if(obj == ui->btn_min){
            if(event->type() == QEvent::Enter){
                ui->btn_min->setPixmap(QPixmap(":/pixmap/image/minBtn_hover.png"));
            }else if(event->type() == QEvent::Leave){
                ui->btn_min->setPixmap(QPixmap(":/pixmap/image/minBtn.png"));
            }else if(event->type() == QEvent::MouseButtonPress){
                ui->btn_min->setPixmap(QPixmap(":/pixmap/image/minBtn_hover.png"));
            }else if(event->type() == QEvent::MouseButtonRelease){
                QMouseEvent *me = (QMouseEvent *)event;
                QLabel *lb = (QLabel *)obj;
                if(me->x() > 0 && me->x() < lb->width() && me->y() > 0 && me->y() < lb->height()){
                    this->showMinimized();
                }else{
                    ui->btn_min->setPixmap(QPixmap(":/pixmap/image/minBtn.png"));
                }
            } else {
                return QObject::eventFilter(obj, event);
            }
        }
    if(obj == ui->btn_close){
            if(event->type() == QEvent::Enter){
                ui->btn_close->setPixmap(QPixmap(":/pixmap/image/closeBtn_hover.png"));
            }else if(event->type() == QEvent::Leave){
                ui->btn_close->setPixmap(QPixmap(":/pixmap/image/closeBtn.png"));
            }else if(event->type() == QEvent::MouseButtonPress){
                ui->btn_close->setPixmap(QPixmap(":/pixmap/image/closeBtn_hover.png"));
            }else if(event->type() == QEvent::MouseButtonRelease){
                QMouseEvent *me = (QMouseEvent *)event;
                QLabel *lb = (QLabel *)obj;
                if(me->x() > 0 && me->x() < lb->width() && me->y() > 0 && me->y() < lb->height()){
                    this->close();
                }else{
                    ui->btn_close->setPixmap(QPixmap(":/pixmap/image/closeBtn.png"));
                }
            } else {
                return QObject::eventFilter(obj, event);
            }
    }
    if(obj == ui->okButton || obj == ui->closeButton)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *me = (QMouseEvent *)event;
            dragPos = me->globalPos() - frameGeometry().topLeft();
        }else if(event->type() == QEvent::MouseButtonRelease)
        {
            setWindowOpacity(1);
        }
    }
    return QObject::eventFilter(obj, event);


}

void ModalDialog::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
    {
        dragPos = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void ModalDialog::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton ) {
        move(event->globalPos() - dragPos);
        setWindowOpacity(1);//0.5
    }
    event->accept();
}

void ModalDialog::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        setWindowOpacity(1);
    }
    event->accept();
}
