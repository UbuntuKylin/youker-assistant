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

#ifndef SELECTCATEGORYWIDGET_H
#define SELECTCATEGORYWIDGET_H

#include <QDialog>
#include <QVBoxLayout>
#include <QMouseEvent>

#include "mytitlebar.h"
#include "selectlistwidget.h"
#include "../component/utils.h"

class SelectCategoryWidget : public QDialog
{
    Q_OBJECT

public:
    SelectCategoryWidget(CleanerCategoryID id = InvalidCategory, const QString &title = "", bool needMin = false, QWidget *parent = 0);
    ~SelectCategoryWidget();

    void loadData(const QStringList &arglist, const QStringList &statuslist);
    void moveCenter();

public slots:
    void onClose();

signals:
    void notifyMainCheckBox(int status);
    void refreshSelectedItems(CleanerCategoryID id, const QStringList &selecteds);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    CleanerCategoryID m_id;
    QVBoxLayout *m_mainLayout = nullptr;
    MyTitleBar *m_titleBar = nullptr;
    SelectListWidget *m_listWidget = nullptr;
    QPoint m_dragPosition; //移动的距离
    bool m_mousePressed; //按下鼠标左键
};

#endif // SELECTCATEGORYWIDGET_H
