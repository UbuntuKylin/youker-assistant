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

#ifndef SELECTWIDGET_H
#define SELECTWIDGET_H

#include <QDialog>
#include <QVBoxLayout>
#include <QMouseEvent>

#include "mytitlebar.h"
#include "selectlistwidget.h"
#include "../component/utils.h"

class SelectWidget : public QDialog
{
    Q_OBJECT
public:
    SelectWidget(CleanerModuleID id = InvalidID, const QString &title = "", bool needMin = false, QWidget *parent = 0);
    ~SelectWidget();

    void loadData(const QString &title, const QStringList &cachelist);
    void moveCenter();

public slots:
    void onClose();

signals:
    void notifyMainCheckBox(int status);
    void refreshSelectedItems(CleanerModuleID id, const QStringList &selecteds);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    CleanerModuleID m_id;
    QVBoxLayout *m_mainLayout = nullptr;
    MyTitleBar *m_titleBar = nullptr;
    SelectListWidget *m_listWidget = nullptr;
    QPoint m_dragPosition; //移动的距离
    bool m_mousePressed; //按下鼠标左键
};

#endif // SELECTWIDGET_H
