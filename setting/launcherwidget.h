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

#ifndef LAUNCHERWIDGET_H
#define LAUNCHERWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QComboBox>
#include "../component/kylinswitcher.h"
#include <QSplitter>
#include <QSlider>
#include <QDoubleSpinBox>
class SessionDispatcher;

class LauncherWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LauncherWidget(QWidget *parent = 0, SessionDispatcher *proxy = 0);
    ~LauncherWidget();
    void setLanguage();
    void initConnect();
    void initData();

//signals:
//    void showSettingMainWidget();

public slots:
    void setIconColouring(QString selectColour);
    void setAutoHide();
    void setDisplayDesktopIcon();
    void setIconSizeValue(int value);
    void setTransparencyValue(double value);

private:
    SessionDispatcher *sessionproxy;
//    QSplitter *splitter;
//    QWidget * top_widget;
//    QWidget * bottom_widget;

//    QPushButton *back_btn;
//    QLabel *title_label;
//    QLabel *description_label;

    QLabel *size_label;
    QLabel *size_value_label;
    QLabel *hide_label;
    QLabel *icon_label;
    QLabel *transparency_label;
    QLabel *background_label;
    QSlider *size_slider;
    KylinSwitcher *hide_switcher;
    KylinSwitcher *icon_switcher;
    QDoubleSpinBox *transparency_slider;
    QComboBox *backgound_combo;
};

#endif // LAUNCHERWIDGET_H
