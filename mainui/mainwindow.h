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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QSettings>

#include "titlewidget.h"
#include "actionwidget.h"
#include "toolwidget.h"
#include "loginwidget.h"
#include "contentwidget.h"
#include "homepage.h"
#include "infowidget.h"
#include "settingwidget.h"
#include "cleanerwidget.h"
#include "boxwidget.h"
#include "skincenter.h"
#include "../component/kylinmenu.h"
#include "../component/utils.h"
#include "../component/toolkits.h"

#include "homeactionwidget.h"
#include "infoactionwidget.h"
#include "cleaneractionwidget.h"
#include "settingactionwidget.h"
#include "boxactionwidget.h"
#include "aboutdialog.h"


class QParallelAnimationGroup;
class SessionDispatcher;
class SystemDispatcher;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setTranslator(QTranslator* translator);
    void setMainWindowLayout();
    void display();
    void initConnect();
    void initSkinCenter();
    void showHomePage();
    void showInfoWidget();
    void showClearWidget();
    void showSettingWidget();
    void reViewThePointSkin(QString pciture);
    void reViewTheOrgSkin();
    void changeSkin(QString pciture);
    void restoreSkin();
//    void initAnimation();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void closeEvent(QCloseEvent *);

public slots:
    void showBoxWidget();
    void openSkinCenter();
    void showMainMenu();
    void closeYoukerAssistant();
    void setCurrentPageIndex(int index);
    void changeLanguage(LANGUAGE language);
    void newFeatures();
    void setupConfigure();
    void aboutUs();
    void startDbusDaemon();

signals:
    void chanegBoxToolStatus();

private:
    Ui::MainWindow *ui;
    QBoxLayout *main_layout;
    QGridLayout *top_grid_layout;
    QGridLayout *bottom_grid_layout;
    TitleWidget *title_widget;
    ActionWidget *action_widget;
    ToolWidget *tool_widget;
    LoginWidget *login_widget;
    ContentWidget *content_widget;
    HomePage *home_page;
    InfoWidget *info_widget;
    CleanerWidget *cleaner_widget;
    SettingWidget *setting_widget;
    BoxWidget *box_widget;

    HomeActionWidget *home_action_widget;
    InfoActionWidget *info_action_widget;
    CleanerActionWidget *cleaner_action_widget;
    SettingActionWidget *setting_action_widget;
    BoxActionWidget *box_action_widget;

    SkinCenter skin_center;
    KylinMenu *main_menu;

    QString version;

    QPoint drag_pos; //移动的距离
    bool mouse_press; //按下鼠标左键

    QTranslator* translator; //翻译器
    LANGUAGE current_language; //当前语言

    QPixmap main_skin_pixmap;
    QString last_skin_path;
    QPixmap review_skin_pixmap;

    SystemDispatcher *systeminterface;
    SessionDispatcher *sessioninterface;
    Toolkits *toolKits;
    AboutDialog *aboutDlg;
    QSettings * mSettings;
    QString desktop;

//    QParallelAnimationGroup *openGroup;
//    QParallelAnimationGroup *closeGroup;
};

#endif // MAINWINDOW_H
