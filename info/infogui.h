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

#ifndef INFOGUI_H
#define INFOGUI_H

#include "infounitwidget.h"

#include <QMap>

class QVBoxLayout;
class QScrollArea;

class InfoGui : public QWidget
{
    Q_OBJECT

public:
    explicit InfoGui(QWidget *parent = 0);
    ~InfoGui();

    const QString infoGuiName() const;
    void setInfoGuiName(const QString &name);

    void clearWidget();
    void loadOnePage(int index, const QString &title, QMap<QString, QVariant> infoMap);
    void updatePageData(const QString &title, QMap<QString, QVariant> infoMap);
    void updateRunningTime(const QString &runningTime);

private:
    QVBoxLayout *m_vLayout = nullptr;
    QFrame *m_widget = nullptr;
    QScrollArea *m_scrollArea = nullptr;
    QList<InfoUnitWidget *> m_pageList;
    QString m_infoGuiName;
};

#endif // INFOGUI_H
