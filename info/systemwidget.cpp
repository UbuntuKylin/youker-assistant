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

#include "systemwidget.h"
#include <QScrollBar>
#include <QPushButton>

#include <QMap>

SystemWidget::SystemWidget(QWidget *parent, SystemDispatcher *proxy) :
    QWidget(parent),
    systemproxy(proxy)
{
    setFixedSize(750, 403);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimeValue()));
    scroll_widget = new ScrollWidget(this);
    scroll_widget->setGeometry(0, 0, 750, 403);
    this->initData();
    page = new ComputerPage(scroll_widget->zone, tr("Computer Base Info"));
    page->setMap(sys_info_map, sys_info_map.value("ComVendor").toString().toUpper());
    page->initUI();
    scroll_widget->addScrollWidget(page);
    timer->start(1000*4);
//    page2 = new ComputerPage(scroll_widget->zone, "lixiang");
//    page2->setMap(sys_info_map);
//    page2->initUI();
//    scroll_widget->addWidget(page2);



//    QHBoxLayout *layout = new QHBoxLayout();
//    layout->addWidget(scroll_widget);
//    layout->setSpacing(50);
//    setLayout(layout);

    //kobe test
//    QScrollArea *pArea= new QScrollArea(this);
//    QWidget * qw = new QWidget(/*pArea*/);//需要滚动的是一个Qwidget，而如果是在设计器里面拖入控件，会自动添加一个
//    pArea->verticalScrollBar()->setStyleSheet("QScrollBar:vertical{margin:0px 0px 0px 0px;background-color:rgb(255,255,255,100);border:0px;width:6px;}"
//         "QScrollBar::sub-line:vertical{subcontrol-origin:margin;border:1px solid red;height:13px}"
//         "QScrollBar::up-arrow:vertical{subcontrol-origin:margin;background-color:blue;height:13px}"
//         "QScrollBar::sub-page:vertical{background-color:#EEEDF0;}"
//         "QScrollBar::handle:vertical{background-color:#D1D0D2;width:6px;} QScrollBar::handle:vertical:hover{background-color:#14ACF5;width:6px;}  QScrollBar::handle:vertical:pressed{background-color:#0B95D7;width:6px;}"
//         "QScrollBar::add-page:vertical{background-color:#EEEDF0;}"
//        "QScrollBar::down-arrow:vertical{background-color:yellow;}"
//         "QScrollBar::add-line:vertical{subcontrol-origin:margin;border:1px solid green;height:13px}");
//    pArea->horizontalScrollBar()->hide();
//    QPushButton * pb = new QPushButton(qw);//测试用，实际你使用就是把按钮设置父窗口，放进qw
//    pb->setText("1235647");
//    pArea->setWidget(qw);//这里设置滚动窗口qw，
//    pArea->setGeometry(0,0,700, 490);//要显示的区域大小
//    qw->setGeometry(0,0,700, 600);//这里变大后，看出他实际滚动的是里面的QWidget窗口
}

SystemWidget::~SystemWidget()
{
    disconnect(timer,SIGNAL(timeout()),this,SLOT(updateTimeValue()));
    if(timer->isActive()) {
        timer->stop();
    }
    if (timer != NULL) {
        delete timer;
        timer = NULL;
    }
}

void SystemWidget::updateTimeValue()
{
    QString result;
    int time_value = systemproxy->get_time_value_qt().toInt();
    int hour_value = time_value/60;
    int minutes_value =time_value%60;
    if(hour_value < 1)
    {
        result = QString::number(minutes_value) + tr(" Minutes");//分钟
    }
    else
    {
        result = QString::number(hour_value) + tr(" Hours ") + QString::number(minutes_value) + tr(" Minutes");//小时 分钟
    }
    page->resetTimeValue(result);
}

void SystemWidget::initData()
{
    sys_info_map = systemproxy->get_computer_info_qt();
}
