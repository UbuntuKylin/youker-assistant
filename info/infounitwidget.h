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

#ifndef INFOUNITWIDGET_H
#define INFOUNITWIDGET_H

#include "infounitwidget.h"
#include "infoitemsgroup.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

class InfoUnitWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InfoUnitWidget(QString title, QWidget *parent = 0);
    ~InfoUnitWidget();

    const QString title() const;
    void setInfoTitle(const QString &title);
    void setInfoVendor(const QString &vendor);

    int getCurrentRunningTimeUIIndex();
    void refreshInfoItem(const QString &key, const QString &value);

protected:
    QVBoxLayout *m_infoLayout = nullptr;

public slots:
    void addInfoItem(const QString &key, const QString &value);

private:
    InfoItemsGroup *m_infoItemsGroup = nullptr;
    QLabel *m_titleLabel = nullptr;
    QLabel *m_vendorLabel = nullptr;
    int m_currentRunningTimeUIIndex;
};

#endif // INFOUNITWIDGET_H
