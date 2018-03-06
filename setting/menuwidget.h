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

#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include "../component/kylinswitcher.h"
#include "settingmodulelpage.h"

class QLabel;
class QPushButton;
class QComboBox;
class QSlider;
class QDoubleSpinBox;

class MenuWidget : public SettingModulePage
{
    Q_OBJECT
public:
    explicit MenuWidget(QWidget *parent = 0, QString cur_desktop = "");
    ~MenuWidget();
    void setLanguage();
    void initConnect();
    void initSettingData() Q_DECL_OVERRIDE;
    QString settingModuleName() Q_DECL_OVERRIDE;

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
    void setLauncherPosition(QString position);

    void launcherwidget_notify_double(QString key, double value);
    void launcherwidget_notify_bool(QString key, bool value);
    void launcherwidget_notify_int(QString key, int value);
    void launcherwidget_notify_string(QString key, QString value);

    void onSendMatePanelIconValue(int topIconSize, int bottomIconSize, bool topIconHide, bool bottomIconHide);
    void onSendUnityIconValue(int iconSize, bool iconHide, bool desktopIconShowed, double launcherTransparency, int iconColourIndex, const QStringList &colourlist);
    void onSendUnityLauncherPosition(const QString &current_position, const QStringList &positionlist);

signals:
    void requestMateOrUnityMenuData(bool isMate);
    void resetIconSizeValue(int value);
    void resetTransparencyValue(int value);
    void resetIconColouring(int value);
    void resetAutoHide(bool b);
    void resetDisplayDesktopIcon(bool b);
    void resetTopIconSizeValue(int value);
    void resetBottomIconSizeValue(int value);
    void resetTopAutoHide(bool b);
    void resetBottomAutoHide(bool b);
    void resetLauncherPosition(const QString &position);

private:
    QString desktop;
    QStringList m_colourlist;
    QStringList m_positionlist;
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
    QLabel *position_label;
    QSlider *size_slider;
    KylinSwitcher *hide_switcher;
    KylinSwitcher *icon_switcher;
    QDoubleSpinBox *transparency_slider;
    QComboBox *backgound_combo;
    QSlider *size_top_slider;
    QSlider *size_bottom_slider;
    KylinSwitcher *hide_top_switcher;
    KylinSwitcher *hide_bottom_switcher;
    QComboBox *position_combo;
};

#endif // MENUWIDGET_H
