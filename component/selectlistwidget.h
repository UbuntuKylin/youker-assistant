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

#ifndef SELECTLISTWIDGET_H
#define SELECTLISTWIDGET_H

#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QApplication>
#include <QLabel>
#include <QEventLoop>
#include <QDesktopWidget>
#include <QCheckBox>

#include "selectlistitem.h"

class SelectListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SelectListWidget(bool hasTip = false, QWidget *parent = 0);
    ~SelectListWidget();

public slots:
    void loadListItems(const QString &title, const QStringList &cachelist, int itemWidth);
    void loadListItemsWithTips(const QStringList &arglist, const QStringList &statuslist, int itemWidth);
    void removeOneItem(const QString &description);
    void resetToDefault();
    QStringList getSelectedItems();
    void resetSubCheckbox(int status);
    void scanAllSubCheckbox();
    void onSelectedSignal(bool checked, QString description);

signals:
    void notifyMainCheckBox(int status);

private:
    bool m_hasTip;
    QGridLayout *m_gridLayout = nullptr;
    QScrollArea *m_scrollArea = nullptr;
    QWidget *m_widget = nullptr;
    QVBoxLayout *m_listAreaWidgetLayout = nullptr;
    QLabel *m_titleLabel = nullptr;
//    QLabel *m_countLabel = nullptr;
    QMap<QString, SelectListItem *> m_itemsMap;
};

#endif // SELECTLISTWIDGET_H
