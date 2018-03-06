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

#ifndef SELECTLISTITEM_H
#define SELECTLISTITEM_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QCheckBox>

class SelectListItem : public QWidget
{
    Q_OBJECT
public:
    explicit SelectListItem(QWidget *parent = 0, QString description = "", QString tipMsg = "", bool hasTip = false, int itemWidth = 0);
    ~SelectListItem();

    bool itemIsChecked();
    QString itemDescription();

signals:
    void selectedSignal(bool checked, QString description);

private:
    bool m_hasTip;
    QString m_description;
    QString m_tip;
    QHBoxLayout *m_mainLayout = nullptr;
    QCheckBox *m_checkBox = nullptr;
    QLabel *m_descLabel = nullptr;
};

#endif // SELECTLISTITEM_H
