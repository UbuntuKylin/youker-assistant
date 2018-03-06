/*
 * Copyright (C) 2013 ~ 2018 National University of Defense Technology(NUDT) & Tianjin Kylin Ltd.
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

#include "resourcescategory.h"
#include "resourcesindicator.h"
#include "networkindicator.h"

#include <QDebug>

ResourcesCategory::ResourcesCategory(int tabIndex, QWidget *parent)
    : QWidget(parent)
    ,activeIndex(tabIndex)
{
    this->setFixedWidth(196);

    layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    cpuButton = new ResourcesIndicator(0, this);
    cpuButton->setTitle(tr("CPU"));
    memoryButton = new ResourcesIndicator(1, this);
    memoryButton->setTitle(tr("Memory"));
    networkButton = new NetworkIndicator(this);
    networkButton->setTitle(tr("Network"));

    if (activeIndex == 0) {
        cpuButton->setChecked(true);
        memoryButton->setChecked(false);
        networkButton->setChecked(false);
    }
    else if (activeIndex == 1) {
        cpuButton->setChecked(false);
        memoryButton->setChecked(true);
        networkButton->setChecked(false);
    }
    else {
        cpuButton->setChecked(false);
        memoryButton->setChecked(false);
        networkButton->setChecked(true);
    }

    connect(cpuButton, &ResourcesIndicator::clicked, this, [=] {
        activeIndex = 0;
        emit this->switchResoucesPage(activeIndex);
        cpuButton->setChecked(true);
        memoryButton->setChecked(false);
        networkButton->setChecked(false);
    });
    connect(memoryButton, &ResourcesIndicator::clicked, this, [=] {
        activeIndex = 1;
        emit this->switchResoucesPage(activeIndex);
        cpuButton->setChecked(false);
        memoryButton->setChecked(true);
        networkButton->setChecked(false);
    });
    connect(networkButton, &NetworkIndicator::clicked, this, [=] {
        activeIndex = 2;
        emit this->switchResoucesPage(activeIndex);
        cpuButton->setChecked(false);
        memoryButton->setChecked(false);
        networkButton->setChecked(true);
    });

    layout->addWidget(cpuButton, 0, Qt::AlignHCenter);
    layout->addWidget(memoryButton, 0, Qt::AlignHCenter);
    layout->addWidget(networkButton, 0, Qt::AlignHCenter);
    layout->addStretch();
}

ResourcesCategory::~ResourcesCategory()
{
    delete cpuButton;
    delete memoryButton;
    delete networkButton;
    delete layout;
}

void ResourcesCategory::onUpdateCpuPercent(double value)
{
    cpuButton->updatePercentAndInfo(value, QString::number(value, 'f', 1) + "%");
}

void ResourcesCategory::onUpdateMemoryPercent(const QString &info, double value)
{
    memoryButton->updatePercentAndInfo(value, info);
}

//void ResourcesCategory::onUpdateNetworkPainterPath(QPainterPath downloadPath, QPainterPath uploadPath)
//{
////    networkButton->updateNetworkPainterPath(downloadPath, uploadPath);
//}

void ResourcesCategory::onUpdateNetworkStatus(long recvTotalBytes, long sentTotalBytes, long recvRateKbs, long sentRateKbs)
{
    networkButton->onUpdateNetworkStatus(recvTotalBytes, sentTotalBytes, recvRateKbs, sentRateKbs);
}
