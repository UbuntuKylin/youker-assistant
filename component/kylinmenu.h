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

#ifndef KYLINMENU_H
#define KYLINMENU_H

#include <QMenu>
#include <QDesktopServices>
#include <QUrl>

class MainWindow;

class KylinMenu : public QMenu
{
    Q_OBJECT

public:
    explicit KylinMenu(QWidget *parent = 0);
    void setLanguage();
    void initConnect();
    void setParentWindow(MainWindow* window) { p_mainwindow = window;}

private:
    void createActions();

public slots:
    void forumHelp();
    void questionFeedback();

private:
    QAction *help_action;
//    QAction *features_action;
    QAction *feedback_action;
//    QAction *setting_action;
    QAction *about_action;
    MainWindow *p_mainwindow;
};

#endif // KYLINMENU_H
