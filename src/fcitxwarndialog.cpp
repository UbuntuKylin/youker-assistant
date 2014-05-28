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
#include "fcitxwarndialog.h"
#include "ui_fcitxwarndialog.h"
#include <QMouseEvent>
#include <qdebug.h>
#include <fcitxcfgwizard.h>

FcitxWarnDialog::FcitxWarnDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FcitxWarnDialog)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);//防止内存泄漏
    this->setWindowFlags(Qt::FramelessWindowHint);
//    this->setAttribute(Qt::WA_TranslucentBackground);

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
    ui->displaylabel->setText(tr("Are you sure you want to exit the wizard ?"));//您确定退出输入法配置向导？
    ui->okButton->setStyleSheet("QPushButton {border-image:url(:/pixmap/image/button12-gray.png);}"
                "QPushButton:hover{border-image:url(:/pixmap/image/button12-gray-hover.png);}");
    ui->closeButton->setStyleSheet("QPushButton {border-image:url(:/pixmap/image/button12-gray.png);}"
                "QPushButton:hover{border-image:url(:/pixmap/image/button12-gray-hover.png);}");

    QObject::connect(ui->closeButton,SIGNAL(clicked()),this,SLOT(accept()));

}

FcitxWarnDialog::~FcitxWarnDialog()
{
    delete ui;
}

bool FcitxWarnDialog::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == ui->btn_min){
            if(event->type() == QEvent::Enter){
                ui->btn_min->setPixmap(QPixmap(":/pixmap/image/minBtn-hover.png"));
            }else if(event->type() == QEvent::Leave){
                ui->btn_min->setPixmap(QPixmap(":/pixmap/image/minBtn.png"));
            }else if(event->type() == QEvent::MouseButtonPress){
                ui->btn_min->setPixmap(QPixmap(":/pixmap/image/minBtn-hover.png"));
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
    if(obj == ui->okButton ||obj == ui->closeButton)
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

void FcitxWarnDialog::on_okButton_clicked()
{
    emit fcitxWarntest();
  //  qDebug()<<"emit fcitxWarn";
    accept();
}

void FcitxWarnDialog::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        dragPos = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void FcitxWarnDialog::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton ) {
        move(event->globalPos() - dragPos);
        setWindowOpacity(1);//0.5
    }
    event->accept();
}

void FcitxWarnDialog::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        setWindowOpacity(1);
    }
    event->accept();
}
