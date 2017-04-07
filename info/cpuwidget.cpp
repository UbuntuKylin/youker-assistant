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

#include "cpuwidget.h"

CpuWidget::CpuWidget(QWidget *parent, SystemDispatcher *proxy) :
    QWidget(parent),
    systemproxy(proxy)
{
    this->setStyleSheet("QWidget{border: none;background-color: #ffffff;}");
    setFixedSize(750, 403);
    page = NULL;
    scroll_widget = new ScrollWidget(this);
    scroll_widget->setGeometry(0, 0, 750, 403 - 3);
    dataOK = false;
//    timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(updateCpuTemp()));
}

CpuWidget::~CpuWidget()
{
//    disconnect(timer,SIGNAL(timeout()),this,SLOT(updateCpuTemp()));
//    if(timer->isActive()) {
//        timer->stop();
//    }
//    if (timer != NULL) {
//        delete timer;
//        timer = NULL;
//    }
    this->clear_page_list();
    if (scroll_widget != NULL) {
        delete scroll_widget;
        scroll_widget = NULL;
    }
}

void CpuWidget::clear_page_list()
{
    if (page != NULL) {
        delete page;
        page = NULL;
    }
    if (scroll_widget)
        scroll_widget->resetWidget();
}

bool CpuWidget::getStatus()
{
    return this->dataOK;
}

void CpuWidget::initData()
{
    this->clear_page_list();
    QMap<QString, QVariant> tmpMap = systemproxy->get_cpu_info_qt();
    if (tmpMap.isEmpty() || tmpMap.count() <= 0) {
        page = NULL;
    }
    else {
        QMap<QString,QVariant>::iterator it;
        for ( it = tmpMap.begin(); it != tmpMap.end(); ++it ) {
            if (it.value().toString().length() > 0) {
                cpu_info_map.insert(it.key(), it.value());
            }
        }
        if(cpu_info_map.isEmpty() || cpu_info_map.count() <= 0) {
            page = NULL;
        }
        else {
            page = new ComputerPage(scroll_widget->zone, tr("CPU Info"));
            page->setSystemDbusProxy(systemproxy);
            page->setMap(cpu_info_map, cpu_info_map.value("CpuVendor").toString().toUpper());
            page->initUI(true);
            scroll_widget->addScrollWidget(page);
        }
    }
    /*QMap<QString,QVariant>::iterator it;
    for ( it = tmpMap.begin(); it != tmpMap.end(); ++it ) {
        if (it.value().toString().length() > 0) {
            cpu_info_map.insert(it.key(), it.value());
        }
    }
    if(cpu_info_map.count() == 1 && cpu_info_map.contains("kylinkobe"))
    {
        page = NULL;
    }
    else {
        page = new ComputerPage(scroll_widget->zone, tr("CPU Info"));
        page->setMap(cpu_info_map, cpu_info_map.value("CpuVendor").toString().toUpper());
        page->initUI();
        scroll_widget->addScrollWidget(page);
    }*/
//    dataOK = true;
}

//void CpuWidget::updateCpuTemp()
//{
//}
