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
#include "tray.h"
#include <QDebug>
Tray::Tray(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);
    dispather = new SystemDispatcher;
    sedispather = new SessionDispatcher;
    ratio_sus = 0;
    double trans_cpu = sedispather->get_cpu_percent_qt();
    cpu_value = QString::number(trans_cpu, 'f', 0);
    used_memory = sedispather->get_used_memory_qt().toDouble();
    free_memory = sedispather->get_free_memory_qt();
    total_size = sedispather->get_total_memory_qt().toDouble();
    double size = used_memory / total_size;
    ratio = QString::number(size, 'f', 2);
    double trans = ratio.toDouble() * 100;
    ratio = QString::number(trans,'f',0);
    total_speed = sedispather->get_network_flow_total_qt();

    this->setWindowOpacity(1.0);
    icon = QIcon(":/pixmap/image/icon.png");
    this->createTray();
    this->setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    QDesktopWidget *desktop = QApplication::desktop();
    this->move(desktop->width() - this->width(), 25);
    this->show();

    frame = new SuspensionFrame;
    frame->hide();
    connect(this, SIGNAL(sysc_data(QString, QString,QString,int,QString, QString)), frame, SLOT(get_sysc_data(QString,QString,QString,int,QString, QString)));
    connect(frame, SIGNAL(accelerate_memory()), this, SLOT(startMemoryAccelerate()));

    QTimer *timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateData()));
    timer->start();
}

Tray::~Tray() {
    if(frame) {
        delete frame;
    }
    if(dispather) {
        delete dispather;
    }
    if(sedispather) {
        delete sedispather;
    }
}

void Tray::updateData() {
    QStringList current_speed = sedispather->get_network_flow_total_qt();
    double up_before = 0.0;
    double down_before = 0.0;
    if(!total_speed.isEmpty()) {
        up_before = total_speed[0].toDouble();
        down_before = total_speed[1].toDouble();
    }
    double up_now = 0.0;
    double down_now = 0.0;
    if(!current_speed.isEmpty()) {
        up_now = current_speed[0].toDouble();
        down_now = current_speed[1].toDouble();
        total_speed = current_speed;
    }

    double up_final = up_now - up_before;
    double down_final = down_now - down_before;

    if(up_final < 1024) {
        up_speed = QString("%1%2").arg(up_final).arg("K/s");
    }
    else if(up_final >= 1024) {
        up_speed = QString("%1%2").arg(QString::number((float)up_final/1024,'f',2)).arg("M/s");
    }
    if(down_final < 1024) {
        down_speed = QString("%1%2").arg(down_final).arg("K/s");
    }
    else if(down_final >= 1024) {
        down_speed = QString("%1%2").arg(QString::number((float)down_final/1024,'f',2)).arg("M/s");
    }

    double trans_cpu = sedispather->get_cpu_percent_qt();
    cpu_value = QString::number(trans_cpu, 'f', 0);
    used_memory = sedispather->get_used_memory_qt().toDouble();
    free_memory = sedispather->get_free_memory_qt();
    double size = used_memory / total_size;
    ratio = QString::number(size, 'f', 2);
    double trans = ratio.toDouble() * 100;
    ratio = QString::number(trans,'f',0);

    emit sysc_data(up_speed, down_speed, ratio, used_memory, free_memory, cpu_value);
    this->uplabel->setText(up_speed);
    this->downlabel->setText(down_speed);
    this->ratiolabel->setText(ratio + "%");
    ratio_sus = ratio.toInt();
    update();
}

void Tray::startMemoryAccelerate() {
    dispather->cleanup_memory_qt();
    updateData();
}

void Tray::createTray() {
    this->actionQml = new QAction(tr("Hide/show main widget"), this);//隐藏/显示主界面
    connect(actionQml, SIGNAL(triggered()), this, SLOT(showOrHideQml()));
    this->actionShow = new QAction(tr("Hide/show monitor ball"), this);//隐藏/显示监控球
    connect(actionShow, SIGNAL(triggered()), this, SLOT(showOrHide()));
//    QShortcut *shortcut = new QShortcut(QKeySequence("Ctrl+H"), this);
//    connect(shortcut, SIGNAL(activated()), this, SLOT(showOrHide()));

    this->actionQuit = new QAction(tr("&Exit"), this);//退出
    connect(actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
    QShortcut *shortexit = new QShortcut(QKeySequence("Ctrl+E"), this);
    connect(shortexit, SIGNAL(activated()), this, SLOT(exit()));

    this->trayMenu = new QMenu(this);
    this->trayMenu->addAction(actionQml);
    this->trayMenu->addAction(actionShow);
    this->trayMenu->addSeparator();
    this->trayMenu->addAction(actionQuit);

    this->trayIcon = new QSystemTrayIcon(this);
    this->trayIcon->setIcon(icon);
    this->trayIcon->setContextMenu(trayMenu);
    connect(this->trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(handle_trayIcon_activated(QSystemTrayIcon::ActivationReason)));
    this->trayIcon->show();
}

void Tray::handle_trayIcon_activated(QSystemTrayIcon::ActivationReason reason) {
    switch(reason) {
        case QSystemTrayIcon::Trigger:
            this->showOrHide();
            break;
        default:
            ;
    }
}

void Tray::exit() {
    qApp->quit();
}

void Tray::showOrHide() {
    if(this->isHidden()) {
        this->show();
    }else {
        this->hide();
        if(!frame->isHidden()) {
            frame->hide();
        }
    }
}

void Tray::showOrHideQml() {
    emit showOrHideQmlSignal();
}

void Tray::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        dragPos = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void Tray::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton ) {
        move(event->globalPos() - dragPos);
        setWindowOpacity(0.5);
    }
    event->accept();
}

void Tray::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        setWindowOpacity(1);
    }
    event->accept();
}

void Tray::mouseDoubleClickEvent(QMouseEvent *event) {
    if(event->buttons() == Qt::RightButton) {
        this->hide();
        if(frame->isVisible()) {
            frame->hide();
        }
    }
    if(event->buttons() == Qt::LeftButton) {
        if(frame->isHidden()) {
            frame->show();
        }
        else {
            frame->hide();
        }
    }
}

QSize Tray::sizeHint()const {
    return QSize(height(),height());
}

void Tray::resizeEvent(QResizeEvent *event) {
    wheel=QImage(event->size(),QImage::Format_ARGB32_Premultiplied);
    wheel.fill(palette().background().color());
    update();
}

void Tray::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QStyleOption opt;

    QPixmap background;
    background.load(":/pixmap/image/accelerate-bg0.png");
    painter.drawPixmap(0, 0, background);

    painter.setRenderHint(QPainter::Antialiasing);  //消除锯齿
    wheel.fill(Qt::transparent);
    blister.load(":/pixmap/image/blister-small.png");
    //线性渐变
    QLinearGradient linearGradient(66,1,66,31);
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
    else if(ratio_sus > 80) {
        color2="#d13625";
        color3="#d13625";
        blister.load(":/pixmap/image/blister-small.png");
    }
    else {
        color2="#00b0ff";
        color3="#006eff";
        blister.load(":/pixmap/image/blister-small.png");
    }

    linearGradient.setColorAt(0.0,color1);
    linearGradient.setColorAt( 1.0 - ratio_sus * 0.01,color1);
    linearGradient.setColorAt((ratio_sus <= 0) ? 0.0 : (1.0 - ratio_sus * 0.01 + 0.01),color2);
    linearGradient.setColorAt(1.0,color3);
    painter.setBrush(QBrush(linearGradient));
    painter.drawRoundRect(51,1,30,30,5,5);

    opt.init(this);
    painter.drawImage(0,0,wheel);

    painter.drawPixmap(0,0, blister);
    style()->drawPrimitive(QStyle::PE_Widget,&opt,&painter,this);
}
