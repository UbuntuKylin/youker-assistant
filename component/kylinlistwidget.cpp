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

#include <QMouseEvent>
#include "kylinlistwidget.h"
#include "kylinlistwidgetitem.h"
#include "mainwindow.h"

KylinListWidget::KylinListWidget(QWidget *parent)
    :QListWidget(parent)
{
    connect(this, SIGNAL(itemPressed(QListWidgetItem*)), this, SLOT(onItemClicked(QListWidgetItem*)));
}

KylinListWidget::~KylinListWidget()
{
}

void KylinListWidget::onItemClicked(QListWidgetItem *item)
{
    KylinListWidgetItem* listitem = static_cast<KylinListWidgetItem*>(item);
    emit this->sendBackgroundName(listitem->getSkinName());
    mainwindow->changeSkin(listitem->getSkinName());
}

void  KylinListWidget::leaveEvent (QEvent *event)
{
    mainwindow->reViewTheOrgSkin();
}

void KylinListWidget::mouseMoveEvent(QMouseEvent *event)
{
    QPoint point = event->pos();
    KylinListWidgetItem *item = (KylinListWidgetItem*)itemAt(point);
    if (item)
    {
        item->paintPointSkin();
    }
    event->ignore();
}
