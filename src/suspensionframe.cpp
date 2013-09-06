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
    ratio_sus = 0;
    ui->fastBtn->setStyleSheet("QPushButton {border-image:url(:/pixmap/image/ok.png);}"
                "QPushButton:hover{border-image:url(:/pixmap/image/ok-hover.png);}");
}

SuspensionFrame::~SuspensionFrame()
{
    delete ui;
}

void SuspensionFrame::get_sysc_data(QString upspeed, QString downspeed, QString ratio, int used_memory, QString free_memory, QString cpu_ratio) {
    ratio_sus = ratio.toInt();
    ui->uplabel->setText(upspeed + "K/s");
    ui->downlabel->setText(downspeed + "K/s");
    ui->ratiolabel->setText(ratio + "%");
//    this->drawLine();
//    update_draw();
    update();
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

QSize SuspensionFrame::sizeHint()const
{
    return QSize(height(),height());
}
void SuspensionFrame::resizeEvent(QResizeEvent*event)
{
    wheel=QImage(event->size(),QImage::Format_ARGB32_Premultiplied);
    wheel.fill(palette().background().color());
//    drawLine(event->size());
//    update_draw();
    update();
}
void SuspensionFrame::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QStyleOption opt;

    QPixmap background;
    background.load(":/pixmap/image/accelerate-bg.png");
    painter.drawPixmap(0,0, background);


//    QPainter painter(&wheel);   //wheel作为画图对象？
//    QPainter paint(&blister);
    painter.setRenderHint(QPainter::Antialiasing);  //消除锯齿
    wheel.fill(Qt::transparent);
    blister.load(":/pixmap/image/blister-big.png");
    //线性渐变
    QLinearGradient linearGradient(76,10,76,76);
    //创建了一个QLinearGradient对象实例，参数为起点和终点坐标，可作为颜色渐变的方向
    painter.setPen(Qt::transparent);
    QString color1;
    QString color2;
    QString color3;

    color1=(ratio_sus == 100) ? "#ff2f00" : "transparent";
    if (ratio_sus == 0)
    {
        color2="transparent";
        color3="transparent";
    }
    else if(ratio_sus > 60) {
        color2="#ff2f00";
        color3="#ff1900";
        blister.load(":/pixmap/image/blister-bigwarn.png");
    }
    else {
        color2="#00b0ff";
        color3="#006eff";
        blister.load(":/pixmap/image/blister-big.png");
    }

    linearGradient.setColorAt(0.0,color1);
    linearGradient.setColorAt( 1.0 - ratio_sus * 0.01,color1);
    linearGradient.setColorAt((ratio_sus <= 0) ? 0.0 : (1.0 - ratio_sus * 0.01 + 0.01),color2);
    linearGradient.setColorAt(1.0,color3);
    painter.setBrush(QBrush(linearGradient));
    painter.drawEllipse(7,7,65,65);


    opt.init(this);
    painter.drawImage(0,0,wheel);

    painter.drawPixmap(7,7, blister);
    style()->drawPrimitive(QStyle::PE_Widget,&opt,&painter,this);
}
