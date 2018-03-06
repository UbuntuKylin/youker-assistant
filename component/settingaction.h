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

#ifndef SETTINGACTION_H
#define SETTINGACTION_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QSignalMapper>
#include <QVBoxLayout>
#include "../component/kylinbutton.h"
#include "../component/systembutton.h"

class SettingAction : public QWidget
{
    Q_OBJECT
public:
    /*enum SettingModuleID{
        ThemePage = 0,
        IconPage,
        MousePage,
        SoundPage,
        PanelPage,
        MenuPage,
        WindowPage,
        FontPage,
        TouchPadPage,
        EnergyPage,
        FMPage
    };*/

    explicit SettingAction(QString cur_dekstop = "", QWidget *parent = 0);
    ~SettingAction();
//    void setParentWindow(MainWindow* window) { p_mainwindow = window;}
    void setLanguage(int index);

//    QString getModuleName() const;
//    void setModuleName(const QString &name);
    QString getModuleName();
    void setModuleName(QString name);


//    SettingModuleID getModuleNameID() const;
//    void setModuleNameID(const SettingModuleID &id);

signals:
    void showSettingMainWidget();

private:
    QPushButton *back_btn;
    QLabel *img_label;
    QLabel *title_label;
//    QLabel *description_label;
//    MainWindow *p_mainwindow;
    QString desktop;
    QString m_moduleName;
//    SettingModuleID m_id;
};

#endif // SETTINGACTION_H
