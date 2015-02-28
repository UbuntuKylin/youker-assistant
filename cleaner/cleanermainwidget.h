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

#ifndef CLEANERMAINWIDGET_H
#define CLEANERMAINWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QSignalMapper>
#include <QVBoxLayout>
#include "../component/kylinbutton.h"
#include "../component/kylintoolbutton.h"
#include "../component/systembutton.h"
#include "../component/loadinglabel.h"
#include "../component/kylincheckbox.h"

#include <QCheckBox>
#include "cleaneritems.h"

class MainWindow;
class CleanerMainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CleanerMainWidget(QWidget *parent = 0, MainWindow *window = 0);
    ~CleanerMainWidget();
    void setLanguage();

public slots:
    void onButtonClicked();

private:
//    QList<QCheckBox *> checkbox_list;
    MainWindow *parentWindow;
    QLabel *tip_label;
//    QCheckBox *main_checkbox;

    KylinCheckBox *cache_btn;
    CleanerItems *cache_items;
    KylinCheckBox *package_btn;
    CleanerItems *package_items;
    KylinCheckBox *cookies_btn;
    CleanerItems *cookies_items;
//    KylinCheckBox *browser_btn;
    CleanerItems *browser_items;
    KylinCheckBox *trace_btn;
    CleanerItems *trace_items;

};

#endif // CLEANERMAINWIDGET_H




