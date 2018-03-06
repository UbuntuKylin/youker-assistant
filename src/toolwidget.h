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

#ifndef TOOLWIDGET_H
#define TOOLWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QSignalMapper>
#include <QVBoxLayout>
#include "../component/kylinbutton.h"
#include "../component/kylintoolbutton.h"

class MainWindow;
//class QParallelAnimationGroup;

class ToolWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ToolWidget(QWidget *parent = 0, QString arch = "", QString os = "");
    ~ToolWidget();
    void setParentWindow(MainWindow* window) { p_mainwindow = window;}
    void initConnect();
//    void initAnimation();

signals:
    void turnCurrentPage(int index);

public slots:
    void switchSelectedPageIndex(QString index);
    void showBoxTool();

private:
    QPoint press_point;//鼠标按下去的点
    bool is_move;
    QList<KylinToolButton *> button_list;
    MainWindow *p_mainwindow;
    QString cur_arch;
    QString osname;
//    QParallelAnimationGroup *openGroup;
//    QParallelAnimationGroup *closeGroup;
};

#endif // TOOLWIDGET_H
