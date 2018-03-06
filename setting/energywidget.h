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

#ifndef ENERGYWIDGET_H
#define ENERGYWIDGET_H

#include <QWidget>
#include "../component/kylinswitcher.h"

#include <QtDBus>
#include <QDBusInterface>
#include <QDBusConnection>

class QLabel;
class QComboBox;
class QDoubleSpinBox;
class QSlider;
class QRadioButton;
class QVBoxLayout;

#include "settingmodulelpage.h"

class EnergyWidget : public SettingModulePage
{
    Q_OBJECT
public:
    explicit EnergyWidget(QStringList cpulist, QString cpu, QString cur_desktop, bool has_battery = false, QWidget *parent = 0);
    ~EnergyWidget();
    void setLanguage();
    void initConnect();
    void initSettingData() Q_DECL_OVERRIDE;
    QString settingModuleName() Q_DECL_OVERRIDE;

public slots:
    void setScreenGammaValue(double value);
    void setBrightnessValue(int value);
//    void setIdleDelay(QString value);
    void setIdleDelay(int index);
    void setLockEnabled();
//    void setLockDelay(QString value);
    void setLockDelay(int index);
    void onCpuRadioButtonClicked();
    void setRadioButtonRowStatus();
    void setSleepTimeoutBattery(int index);
    void setSleepTimeoutAC(int index);
    void setSleepTimeoutDisplayBattery(int index);
    void setSleepTimeoutDisplayAC(int index);

    void onSendIdleAndGammaData(double gamma, const QStringList &aclist, int brightnessValue, const QString &sleepTimeoutDisplayBattery, const QString &sleepTimeoutFisplayAC, const QString &idle_delay, const QStringList &idledelaylist);
    void onSendLockAndSleepData(bool lockEnabled, const QString &lock_delay, const QStringList &lockdelaylist, const QString &critical_low, const QString &laptop_battery, const QString &laptop_ac, const QString &sleepTimeoutBattery, const QStringList &batterylist, const QString &sleepTimeoutAc);

signals:
    void requestPowerAndBatteryData();
    void resetScreenGammaValue(double value);
    void resetBrightnessValue(int value);
    void resetIdleDelay(int index, int curValue);
    void resetLockEnabled(bool b);
    void resetLockDelay(int index, int curValue);
    void setCurrentCriticalLow(const QString &value);
    void setCurrentLidBattery(const QString &value);
    void setCurrentLidAC(const QString &value);
    void resetSleepTimeoutBattery(int index, int value);
    void resetSleepTimeoutAC(int index, int value);
    void resetSleepTimeoutDisplayBattery(int index, int value);
    void resetSleepTimeoutDisplayAC(int index, int value);
    void setCurrentCpuMode(const QString &mode);

private:
    QString desktop;
    QString current_idle_delay;
    QString current_lock_delay;
    QString sleep_timeout_battery;
    QString sleep_timeout_ac;
    QString sleep_timeout_display_battery;
    QString sleep_timeout_display_ac;
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
    QLabel *critical_low_label;
    QRadioButton *suspend_low_radio;
    QRadioButton *shutdown_radio;
    QLabel *laptop_lid_battery_label;
    QRadioButton *suspend_lid_battery_radio;
    QRadioButton *nothing_battery_radio;
    QLabel *laptop_lid_ac_label;
    QRadioButton *suspend_lid_ac_radio;
    QRadioButton *nothing_ac_radio;
    QLabel *sleep_battery_label;
    QComboBox *sleep_battery_combo;
    QLabel *sleep_ac_label;
    QComboBox *sleep_ac_combo;

    QLabel *sleep_battery_display_label;
    QComboBox *sleep_battery_display_combo;
    QLabel *sleep_ac_display_label;
    QComboBox *sleep_ac_display_combo;

    QStringList m_aclist;
    QVBoxLayout *m_layout = nullptr;
};

#endif // ENERGYWIDGET_H
