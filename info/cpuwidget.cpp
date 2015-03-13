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
    setFixedSize(750, 403);
    scroll_widget = new ScrollWidget(this);
    scroll_widget->setGeometry(0, 0, 750, 403 - 3);
    this->initData();
    if(cpu_info_map.count() == 1 && cpu_info_map.contains("kylinkobe"))
    {
        page = NULL;
    }
    else {
        page = new ComputerPage(scroll_widget->zone, tr("CPU Info"));
        page->setMap(cpu_info_map, cpu_info_map.value("CpuVendor").toString().toUpper());
        page->initUI();
        scroll_widget->addScrollWidget(page);
    }
}

void CpuWidget::initData()
{
    cpu_info_map = systemproxy->get_cpu_info_qt();
}
