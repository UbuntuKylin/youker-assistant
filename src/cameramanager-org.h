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

#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include <QDialog>

#include "../component/kylinlistwidget.h"
#include "../component/kylintitlebar.h"

class SessionDispatcher;
class MainWindow;
class CameraManager :public QDialog
{
  Q_OBJECT
public:
    CameraManager(QWidget *parent = 0, SessionDispatcher *proxy = 0, QString skin = ":/background/res/skin/1.png");
    ~CameraManager();
    void setParentWindow(MainWindow *From) { mainwindow = From;}
//    void initBackgroundList();
    void setLanguage();
    void initConnect();
    void setOKButtonEnable(bool enable);
    void resetTitleSkin(QString skin);

public slots:
    void onCloseButtonClicked();
    void onOKButtonClicked();
    void onViewButtonClicked();

private:
    void initTitleBar(QString skin);

private:
    MainWindow *mainwindow;
    SessionDispatcher *sessionproxy;
    KylinTitleBar *title_bar;
    QLabel *msg_label;
    QLabel *tip_label;
    QLabel *description_label;
    QPushButton *okBtn;
    QPushButton *viewBtn;
};

#endif // CAMERAMANAGER_H
