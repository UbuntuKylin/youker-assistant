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

#ifndef MIDDLEWIDGET_H
#define MIDDLEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSignalMapper>
#include <QVBoxLayout>
#include "../component/kylinbutton.h"
#include "../component/kylintoolbutton.h"
#include "../component/systembutton.h"

class MiddleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MiddleWidget(QWidget *parent = 0, QString arch = "", QString os = "");
    ~MiddleWidget();
    void InitMiddlewidget();
    void initTitlebarLeftContent();
    void initTitlebarRightContent();
    void initBottomContent();

    void setHideMonitorWidget(bool f){this->hide = f;};

    void paintEvent(QPaintEvent *);
signals:
    void turnCurrentPage(QString index);
    void middle_showMenu();
    void middle_showMin();
    void middle_closeApp();

public slots:
    void switchSelectedPageIndex(QString index);
    void showBoxTool();

private:
    QPoint press_point;//鼠标按下去的点
    bool is_move;
    QList<KylinToolButton *> button_list;
    QString cur_arch;
    QString osname;

    QVBoxLayout *main_layout;
    QHBoxLayout *botton_layout;
    QHBoxLayout *top_layout;
    QHBoxLayout *m_titleLeftLayout;
    QHBoxLayout *m_titleRightLayout;

    bool hide = false;
};

#endif // MIDDLEWIDGET_H
