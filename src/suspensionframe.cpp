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
#include "suspensionframe.h"
#include "ui_suspensionframe.h"
#include <QMouseEvent>
SuspensionFrame::SuspensionFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SuspensionFrame)
{
    ui->setupUi(this);

    this->setWindowOpacity(1.0);
    ui->title1->setText(tr("System runs smoothly"));//系统运行流畅
    ui->title2->setText(tr("No need to accelerate"));//无需进行加速
    ui->memory_title->setStyleSheet("color:white");//设置字颜色
    this->setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->move(QApplication::desktop()->width() - this->width(), 80);
    ratio_sus = 0;
    cpu_sus = 0;
    nowtotalCPU = 0;
    lastTotalCPU = 0;
    nowIdle = 0;
    lastIdle = 0;

    locale_Lan = this->get_locale_version();
    if(locale_Lan == "zh_CN") {
        ui->fastBtn->setStyleSheet("QPushButton {border-image:url(:/pixmap/image/upshiftZH.png);color: white; font-size: 12px}"
                    "QPushButton:hover{border-image:url(:/pixmap/image/upshiftZH-hover.png);}"
                    "QPushButton:pressed{border-image:url(:/pixmap/image/upshiftZH-press.png);}");
    }
    else {
        ui->fastBtn->setStyleSheet("QPushButton {border-image:url(:/pixmap/image/upshiftEN.png);color: white; font-size: 12px}"
                    "QPushButton:hover{border-image:url(:/pixmap/image/upshiftEN-hover.png);}"
                    "QPushButton:pressed{border-image:url(:/pixmap/image/upshiftEN-press.png);}");
    }

    ui->descBtn->setStyleSheet("QPushButton {border:0px;color:#1790c9}");
    ui->descBtn->setText(tr("Details"));//详细
    ui->descBtn->setFlat(true);
    ui->descBtn->setFocusPolicy(Qt::NoFocus);
    this->resize(265, 173);
}

SuspensionFrame::~SuspensionFrame() {
    delete ui;
}

QString SuspensionFrame::get_locale_version() {
    QString locale = QLocale::system().name();
    return locale;
}

QStringList SuspensionFrame::readStatFile()
{
    QFile file("/proc/stat");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug()<<"Cann't open /proc/stat!";
    }
    QTextStream stream(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    QString fileLine;
    QStringList statList;
    do {
        fileLine = stream.readLine();
        statList += fileLine;
    } while (!fileLine.isNull());
    QApplication::restoreOverrideCursor();
    file.close();
    return statList;
}

QString SuspensionFrame::getCPURatio()
{
    QStringList strList = readStatFile();
    for(int i=1;i<10;i++) {
        nowtotalCPU+=strList.at(0).split(" ",QString::SkipEmptyParts).at(i).toDouble();
    }
    nowIdle = strList.at(0).split(" ",QString::SkipEmptyParts).at(4).toDouble();
    double allCPU = nowtotalCPU - lastTotalCPU;
    double unusedCPU = nowIdle - lastIdle;
//    result.setNum(100*(allCPU-unusedCPU)/allCPU);
    lastTotalCPU = nowtotalCPU;
    lastIdle = nowIdle;
    nowtotalCPU = 0;
    QString result  = QString::number(100*(allCPU-unusedCPU)/allCPU, 'f', 1);
    return result;
}

void SuspensionFrame::get_sysc_data(QString upspeed, QString downspeed, QString ratio, int used_memory, QString free_memory, QString cpu_ratio) {
    ratio_sus = ratio.toInt();
    QString tmp_cpu = this->getCPURatio();
    if (tmp_cpu.isEmpty()) {
        cpu_sus = cpu_ratio.toInt();
        ui->ratiolabel_2->setText(cpu_ratio + "%");
    }
    else {
        cpu_sus = tmp_cpu.toInt();
        ui->ratiolabel_2->setText(tmp_cpu+ "%");
    }
    cpu_sus = cpu_ratio.toInt();
    ui->uplabel->setText(upspeed);
    ui->downlabel->setText(downspeed);
    ui->ratiolabel->setText(ratio + "%");
    ui->memory_1->setText(tr("%1").arg(used_memory)+"M");
    ui->memory_2->setText(free_memory+"M");
    update();
}

void SuspensionFrame::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        dragPos = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void SuspensionFrame::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton ) {
        move(event->globalPos() - dragPos);
        setWindowOpacity(0.5);
    }
    event->accept();
}

void SuspensionFrame::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        setWindowOpacity(1);
    }
    event->accept();
}

void SuspensionFrame::on_descBtn_clicked() {
    if(this->height() == 173) {
        this->resize(265, 288);
    }
    else if(this->height() == 288) {
        this->resize(265, 173);
    }
}

void SuspensionFrame::on_fastBtn_clicked() {
    emit accelerate_memory();
}

QSize SuspensionFrame::sizeHint()const {
    return QSize(height(),height());
}

void SuspensionFrame::resizeEvent(QResizeEvent *event) {
    wheel=QImage(event->size(),QImage::Format_ARGB32_Premultiplied);
    wheel.fill(palette().background().color());
    update();
}

void SuspensionFrame::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QStyleOption opt;
    QPixmap memory;
    QPixmap background;
    background.load(":/pixmap/image/accelerate-bg.png");
    memory.load(":/pixmap/image/memory.png");
    painter.drawPixmap(0,0, background);

    painter.setRenderHint(QPainter::Antialiasing);  //消除锯齿
    wheel.fill(Qt::transparent);
//    blister.load(":/pixmap/image/blister-big.png");
    //线性渐变
    QLinearGradient linearGradient(76,10,76,76);
    //创建了一个QLinearGradient对象实例，参数为起点和终点坐标，可作为颜色渐变的方向
    painter.setPen(Qt::transparent);
    QString color_start;
    QString color_end;

    if (ratio_sus == 0)
    {
        if (cpu_sus > 80) {
            color_start = "#940302";//950302
            color_end="#dd291c";//DE281C
            ui->title1->setText(tr("Detected the high usage of CPU"));//检测到CPU占用过高
            ui->title2->setText(tr("Using 'quick clean' ?"));//使用一键加速？
        }
        else {
            color_start = "#940302";//950302
            color_end="transparent";
        }
    }
    else if (ratio_sus > 0 && ratio_sus < 50) {
        if (cpu_sus > 80) {
            color_start = "#940302";//950302
            color_end="#dd291c";//DE281C
            ui->title1->setText(tr("Detected the high usage of CPU"));//检测到CPU占用过高
            ui->title2->setText(tr("Using 'quick clean' ?"));//使用一键加速？
        }
        else {
            color_start = "#006f45";//006F45
            color_end= "#48ca5e";//52D063
            ui->title1->setText(tr("System runs smoothly"));//系统运行流畅
            ui->title2->setText(tr("No need to accelerate"));//无需进行加速
        }
    }
    else if (ratio_sus >= 50 && ratio_sus <= 80) {
        if (cpu_sus > 80) {
            color_start = "#940302";//950302
            color_end="#dd291c";//DE281C
            ui->title1->setText(tr("Detected the high usage of CPU"));//检测到CPU占用过高
            ui->title2->setText(tr("Using 'quick clean' ?"));//使用一键加速？
        }
        else {
            color_start = "#af3a00";//AF3A00
            color_end="#ed711d";//F07620
            ui->title1->setText(tr("System runs smoothly"));//系统运行流畅
            ui->title2->setText(tr("No need to accelerate"));//无需进行加速
        }
    }
    else {// if(ratio_sus > 80) {
        color_start = "#940302";//950302
        color_end="#dd291c";//DE281C
        ui->title1->setText(tr("Computer runs slowly"));//电脑运行缓慢
        ui->title2->setText(tr("Using 'quick clean' ?"));//使用一键加速？
    }
    linearGradient.setColorAt(0.0, color_start);
    linearGradient.setColorAt( 1.0 - ratio_sus * 0.01, color_start);
    linearGradient.setColorAt((ratio_sus <= 0) ? 0.0 : (1.0 - ratio_sus * 0.01 + 0.01), color_end);
    linearGradient.setColorAt(1.0, color_end);
    painter.setBrush(QBrush(linearGradient));
    painter.drawEllipse(7,7,65,65);
    opt.init(this);


//    painter.drawImage(0,0,wheel);
//    painter.drawPixmap(44,231,memory,0,0,memory.width()*(ratio_sus* 0.01),memory.height());
////    painter.drawPixmap(7,7, blister);

     //图形宽度213,高度26
    //    QLinearGradient linearGradient1(44,231,257,231);//覆盖原图边界
        QLinearGradient linearGradient1(45,232,259,231);//显示原图边界
        //从点（72，250）开始到点（283，249）结束，确定一条直线
        //创建了一个QLinearGradient对象实例，参数为起点和终点坐标，可作为颜色渐变的方向
        painter.setPen(Qt::transparent);
        QString color_start1;
        QString color_end1;
        if (ratio_sus == 0)
        {
            color_start1 = "transparent";
            color_end1="#940302";
        }
        else if (ratio_sus > 0 && ratio_sus < 50) {
            color_start1 = "#48ca5e";
            color_end1= "#006f45";
        }
        else if (ratio_sus >= 50 && ratio_sus <= 80) {
            color_start1 = "#ed711d";
            color_end1="#af3a00";
        }
        else {// if(ratio_sus > 80) {
            color_start1 = "#dd291c";//950302
            color_end1="#940302";//DE281C
        }
        linearGradient1.setColorAt(0.0, color_start1);
        linearGradient1.setColorAt(ratio_sus * 0.01, color_start1);
        linearGradient1.setColorAt((ratio_sus <= 0) ? 1.0 : (ratio_sus * 0.01 + 0.01), color_end1);
        linearGradient1.setColorAt(1.0, color_end1);
        painter.setBrush(QBrush(linearGradient1));
        //绘制矩形
    //    painter.drawRect(44,231,213,26);//覆盖原图边界
        painter.drawRect(45,232,211,24);//显示原图边界

    QPixmap pixmap;
    pixmap.load(":/pixmap/image/shade.png");
    painter.drawPixmap(5, 7, pixmap);

    style()->drawPrimitive(QStyle::PE_Widget,&opt,&painter,this);
}
