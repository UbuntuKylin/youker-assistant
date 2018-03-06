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

#ifndef SETTINGACTIONWIDGET_H
#define SETTINGACTIONWIDGET_H

#include <QWidget>
#include "../component/kylinbutton.h"
#include "../component/systembutton.h"
#include "../component/settingaction.h"

class MainWindow;
class QStackedWidget;

class SettingActionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SettingActionWidget(QString cur_desktop = "", QWidget *parent = 0);
    ~SettingActionWidget();
    void setParentWindow(MainWindow* window) { p_mainwindow = window;}
    void setLanguage();
    void initConnect();

public slots:
    void displayActionMainPage();
    void displayActionSubPage(QString moduleName);//void displayActionSubPage(SettingAction::SettingModuleID moduleId);

signals:
    void notifyContentPageToMain();

private:
    QLabel *img_label;
    QLabel *title_label;
    QStackedWidget *stacked_widget;
    QWidget *main_action;
//    SettingAction *main_action;
    SettingAction *theme_action;
    SettingAction *icon_action;
    SettingAction *mouse_action;
    SettingAction *voice_action;
//    SettingAction *animation_action;
    SettingAction *launcher_action;
    SettingAction *panel_action;
    SettingAction *window_action;
    SettingAction *font_action;
    SettingAction *touchpad_action;
//    SettingAction *deadpixel_action;
    SettingAction *conserve_aciton;
    SettingAction *nautilus_action;

    MainWindow *p_mainwindow;
    QString desktop;
};

#endif // SETTINGACTIONWIDGET_H
