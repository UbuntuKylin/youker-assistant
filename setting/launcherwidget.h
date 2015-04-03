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
#include "../component/kylinswitcher.h"

class SessionDispatcher;
class QLabel;
class QPushButton;
class QComboBox;
class QSlider;
class QDoubleSpinBox;

class LauncherWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LauncherWidget(QWidget *parent = 0, SessionDispatcher *proxy = 0, QString cur_desktop = "");
    ~LauncherWidget();
    void setLanguage();
    void initConnect();
    void initData();

public slots:
    void setIconColouring(QString selectColour);
    void setAutoHide();
    void setDisplayDesktopIcon();
    void setIconSizeValue(int value);
    void setTransparencyValue(double value);
    void setTopIconSizeValue(int value);
    void setBottomIconSizeValue(int value);
    void setTopAutoHide();
    void setBottomAutoHide();

private:
    SessionDispatcher *sessionproxy;
    QLabel *size_label;
    QLabel *size_value_label;
    QLabel *hide_label;
    QLabel *icon_label;
    QLabel *transparency_label;
    QLabel *background_label;
    QLabel *size_top_label;
    QLabel *hide_top_label;
    QLabel *size_top_value_label;
    QLabel *size_bottom_label;
    QLabel *hide_bottom_label;
    QLabel *size_bottom_value_label;
    QSlider *size_slider;
    KylinSwitcher *hide_switcher;
    KylinSwitcher *icon_switcher;
    QDoubleSpinBox *transparency_slider;
    QComboBox *backgound_combo;
    QSlider *size_top_slider;
    QSlider *size_bottom_slider;
    KylinSwitcher *hide_top_switcher;
    KylinSwitcher *hide_bottom_switcher;
};

#endif // LAUNCHERWIDGET_H
