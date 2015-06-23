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

#include "kylinlistview.h"
#include <QDebug>
#include <QEvent>
#include <QtGui/qabstractitemview.h>

KylinListView::KylinListView(QWidget *parent)
    : QListView(parent)
{
}

KylinListView::~KylinListView()
{

}

bool KylinListView::viewportEvent(QEvent *pEvent)
{
    bool bRes = QAbstractItemView::viewportEvent(pEvent);
    QEvent::Type enumType = pEvent->type();
    switch (enumType)
    {
    case QEvent::HoverEnter:
        {
            qDebug() << "hover enter......";
        }
        break;
    case QEvent::HoverLeave:
        {
            qDebug() << "hover leave......";
        }
        break;
    case QEvent::HoverMove:
        {
            qDebug() << "hover move......";
        }
        break;
    default:
        break;
    }
    return QAbstractItemView::viewportEvent(pEvent);
}
