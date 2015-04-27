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

#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>
#include <QSplitter>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QPen>
#include <QHBoxLayout>
#include <QEvent>
#include <QVBoxLayout>
#include <QStackedWidget>
#include "../setting/themewidget.h"
#include "../setting/iconwidget.h"
#include "../setting/mousewidget.h"
#include "../setting/voicewidget.h"
#include "../setting/animationwidget.h"
#include "../setting/launcherwidget.h"
#include "../setting/panelwidget.h"
#include "../setting/windowwidget.h"
#include "../setting/fontwidget.h"
#include "../setting/touchpadwidget.h"
#include "../setting/deadpixelwidget.h"
#include "../setting/conservewidget.h"
#include "../setting/nautiluswidget.h"

class SessionDispatcher;
class SystemDispatcher;
class MainWindow;

class SettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SettingWidget(QString cur_desktop = "", QWidget *parent = 0);
    ~SettingWidget();
    void initIndividuationWidget();
    void initDesktopWidget();
    void initFontWidget();
    void initOptionWidget();
    void initOtherWidget();
    void setParentWindow(MainWindow* window) { p_mainwindow = window;}
    void setSessionDbusProxy(SessionDispatcher *dispatcher) { sessionProxy = dispatcher;}
    void setSystemDbusProxy(SystemDispatcher *dispatcher) { systemProxy = dispatcher;}
    void initUI();

signals:
    void changeActionPage(int index);

public slots:
    void displaySettingHomePage();
    void displaySettingSubPage();
//    void slot_notify_boolean(QString key, bool value);

private:
    MainWindow *p_mainwindow;
    SessionDispatcher *sessionProxy;
    SystemDispatcher *systemProxy;
    QString desktop;

    QStackedWidget *stacked_widget;
    ThemeWidget *theme_widget;
    IconWidget *icon_widget;
    MouseWidget *mouse_widget;
    VoiceWidget *voice_widget;
    AnimationWidget *animation_widget;
    LauncherWidget *launcher_widget;
    PanelWidget *panel_widget;
    WindowWidget *window_widget;
    FontWidget *font_widget;
    TouchpadWidget *touchpad_widget;
    DeadpixelWidget *deadpixel_widget;
    ConserveWidget *conserve_widget;
    NautilusWidget *nautilus_widget;
    QSplitter *h_splitter;
    QWidget *individuation_widget;
    QLabel *individuation_icon;
    QLabel *individuation_title;
    QLabel *dot1;
    QPushButton *theme_button;
    QLabel *dot2;
    QPushButton *icon_button;
    QLabel *dot3;
    QPushButton *mouse_button;
    QLabel *dot4;
    QPushButton *voice_button;
    QLabel *dot5;
    QPushButton *animation_button;

    QWidget *dekstop_widget;
    QLabel *dekstop_icon;
    QLabel *dekstop_title;
    QLabel *dot6;
    QPushButton *launcher_button;
    QLabel *dot7;
    QPushButton *panel_button;
    QLabel *dot8;
    QPushButton *window_button;

    QWidget *fonts_widget;
    QLabel *font_icon;
    QLabel *font_title;
    QLabel *dot9;
    QPushButton *font_button;

    QWidget *option_widget;
    QLabel *option_icon;
    QLabel *option_title;
    QLabel *dot10;
    QPushButton *touch_button;
    QLabel *dot11;
    QPushButton *pixel_button;
    QLabel *dot12;
    QPushButton *conserve_button;

    QWidget *other_widget;
    QLabel *other_icon;
    QLabel *other_title;
    QLabel *dot13;
    QPushButton *nautilus_button;
};

#endif // SETTINGWIDGET_H
