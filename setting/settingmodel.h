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

#ifndef SETTINGMODEL_H
#define SETTINGMODEL_H

#include <QAbstractListModel>

class SettingModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit SettingModel(QObject *parent = 0);

    enum ItemRole
    {
        HoverRole = Qt::UserRole + 1,//101
    };

public slots:
    void addItem(const QString &moduleName);
    void setCurrentItem(const QModelIndex &index);
    int rowCount(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role) const;

private:
    QStringList m_moduleList;
//    QStringList m_nameList;
    QModelIndex m_currentIndex;
};

#endif // SETTINGMODEL_H
