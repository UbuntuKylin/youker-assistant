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

#ifndef PANELWIDGET_H
#define PANELWIDGET_H

#include <QWidget>
#include "../component/kylinswitcher.h"

class SessionDispatcher;
class QLabel;
class QPushButton;
class QComboBox;
class QSlider;
class QDoubleSpinBox;
class QRadioButton;

class PanelWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PanelWidget(QWidget *parent = 0, SessionDispatcher *proxy = 0, QString cur_desktop = "");
    ~PanelWidget();
    void setLanguage();
    void initConnect();
    void initData();

//signals:
//    void showSettingMainWidget();

public slots:
    void setDateFormat(QString selected);
    void setShowBatteryIcon(QString selected);
    void setTransparencyValue(double value);
    void setRadioButtonRowStatus(/*bool status*/);
    void setDisplaySeconds();
    void setDisplayWeek();
    void setDisplayDate();
    void setDisplayBatteryPercentage();
    void setDisplayBatteryTime();
    void showApplications();
    void showDesktop();
    void showIcon();
    void showPlaces();

private:
    SessionDispatcher *sessionproxy;
    QLabel *blur_label;
    QLabel *transparency_label;
    QLabel *date_format_label;
    QLabel *second_label;
    QLabel *week_label;
    QLabel *date_label;
    QLabel *battery_icon_label;
    QLabel *battery_percentage_label;
    QLabel *battery_time_label;
    QLabel *show_app_label;
    QLabel *show_desktop_label;
    QLabel *show_icon_label;
    QLabel *show_places_label;
    QRadioButton *smart_radio;
    QRadioButton *static_radio;
    QRadioButton *clear_radio;
    QDoubleSpinBox *transparency_slider;
    QComboBox *date_combo;
    KylinSwitcher *second_switcher;
    KylinSwitcher *week_switcher;
    KylinSwitcher *date_switcher;
    QComboBox *battery_combo;
    KylinSwitcher *battery_percentage_switcher;
    KylinSwitcher *battery_time_switcher;
    KylinSwitcher *app_switcher;
    KylinSwitcher *desktop_switcher;
    KylinSwitcher *icon_switcher;
    KylinSwitcher *places_switcher;
};

#endif // PANELWIDGET_H
