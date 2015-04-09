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

#ifndef CONSERVEWIDGET_H
#define CONSERVEWIDGET_H

#include <QWidget>
#include "../component/kylinswitcher.h"

#include <QtDBus>
#include <QDBusInterface>
#include <QDBusConnection>

class QLabel;
class QComboBox;
class QDoubleSpinBox;
class QSlider;

class SessionDispatcher;

class ConserveWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConserveWidget(QWidget *parent = 0, SessionDispatcher *proxy = 0, QString cur_desktop = "");
    ~ConserveWidget();
    void setLanguage();
    void initConnect();
    void initData();

public slots:
    void setScreenGammaValue(double value);
    void setBrightnessValue(int value);
    void setIdleDelay(QString value);
    void setLockEnabled();
    void setLockDelay(QString value);

private:
    QDBusInterface *iface;
    SessionDispatcher *sessionproxy;
    QLabel *gamma_label;
    QDoubleSpinBox *gamma_slider;
    QLabel *brightness_label;
    QLabel *brightness_value_label;
    QSlider *brightness_slider;
    QLabel *idle_delay_label;
    QComboBox *idle_delay_combo;
    QLabel *lock_enabled_label;
    KylinSwitcher *lock_enabled_switch;
    QLabel *lock_delay_label;
    QComboBox *lock_delay_combo;
};

#endif // CONSERVEWIDGET_H
