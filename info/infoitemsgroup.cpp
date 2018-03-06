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

#include "infoitemsgroup.h"
#include "infoitemline.h"

#include <QVBoxLayout>
#include <QDebug>

InfoItemsGroup::InfoItemsGroup(QFrame *parent) :
    QFrame(parent),
    m_layout(new QVBoxLayout)
{
    m_layout->setMargin(0);
    m_layout->setSpacing(1);
    this->setLayout(m_layout);
}


InfoItemsGroup::~InfoItemsGroup()
{
    /*if (m_layout) {
        foreach (QObject *child, m_layout->children()) {
            QWidget *widget = static_cast<QWidget *>(child);
            widget->deleteLater();
        }
    }*/

    for (int i = 0; i != m_layout->count(); ++i)
    {
        QLayoutItem *child = m_layout->takeAt(0);
        QWidget *w = child->widget();
        w->removeEventFilter(this);
        w->setParent(nullptr);
        delete child;
        child = nullptr;
    }

    /*QLayoutItem *child;
    while ((child = m_layout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }*/
}

int InfoItemsGroup::appendItem(InfoItemLine *item)
{
    m_layout->insertWidget(m_layout->count(), item);
    item->installEventFilter(this);
    return m_layout->count() - 1;
}

void InfoItemsGroup::removeItem(InfoItemLine *item)
{
    m_layout->removeWidget(item);
    item->removeEventFilter(this);
}

InfoItemLine *InfoItemsGroup::getInfoItem(int index)
{
    if(index < 0)
        return NULL;

    if(index < m_layout->count())
    {
        return qobject_cast<InfoItemLine *>(m_layout->itemAt(index)->widget());
    }

    return NULL;
}
