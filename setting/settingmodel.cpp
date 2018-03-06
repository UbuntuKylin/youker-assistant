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

#include "settingmodel.h"

#include <QSize>
#include <QDebug>


SettingModel::SettingModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

void SettingModel::addItem(const QString &moduleName)
{
    if (!m_moduleList.contains(moduleName))
        m_moduleList.append(moduleName);
}

void SettingModel::setCurrentItem(const QModelIndex &index)
{
    const QModelIndex origIndex = m_currentIndex;
    m_currentIndex = index;

    emit dataChanged(origIndex, origIndex);
    emit dataChanged(m_currentIndex, m_currentIndex);
}

int SettingModel::rowCount(const QModelIndex &index) const
{
    Q_UNUSED(index);

    const int itemCount = m_moduleList.size();
    const int rowCount = itemCount % 6;//按每行6个来计算

    return itemCount + (rowCount ? 6 - rowCount : rowCount);
}

QVariant SettingModel::data(const QModelIndex &index, int role) const
{
    switch (role)
    {
    case Qt::DisplayRole:
    {
        const int order = index.row();
        if (m_moduleList.size() > order)
            return m_moduleList[order];
        else
            return QVariant();
    }
    case Qt::SizeHintRole:
        return QSize(120, 78);
    case HoverRole:
        return index == m_currentIndex;
    default:
        break;
    }

    return QVariant();
}
