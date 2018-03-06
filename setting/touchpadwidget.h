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

#ifndef TOUCHPADWIDGET_H
#define TOUCHPADWIDGET_H

#include <QWidget>
#include "../component/kylinswitcher.h"
#include "settingmodulelpage.h"

class QLabel;
class QPushButton;
class QRadioButton;

class TouchpadWidget : public SettingModulePage
{
    Q_OBJECT
public:
    explicit TouchpadWidget(QWidget *parent = 0, QString cur_desktop = "");
    ~TouchpadWidget();
    void setLanguage();
    void initConnect();
    void initSettingData() Q_DECL_OVERRIDE;
    QString settingModuleName() Q_DECL_OVERRIDE;

public slots:
    void setRadioButtonRowStatus(/*bool status*/);
    void setTouchpad();
    void setHorizontalScrolling();

    void touchpadwidget_notify_string(QString key, QString value);
    void touchpadwidget_notify_bool(QString key, bool value);
    void touchpadwidget_notify_int(QString key, int value);

    void onSendTouchPadValue(bool touchpadEnable, bool touchscrollingHorizontal, const QString &mode_value, int scroll_int_value, const QString &scroll_string_value);

signals:
    void requestMateOrUnityTouchpadData(bool isMate);
    void resetTouchpad(bool b);
    void resetHorizontalScrolling(bool b);
    void setScrollbarOverlayOrLegacyMode(bool b);
    void setMateTouchscrollingMode(int flag);
    void setUnityTouchscrollingMode(int flag);

private:
    QLabel *touchpad_label;
    QLabel *horizontal_scrolling_label;
    QLabel *scrollbar_type_label;
    QLabel *scrolling_mode_label;
    KylinSwitcher *touchpad_switcher;
    KylinSwitcher *horizontal_scrolling_switcher;
    QRadioButton *features_radio;
    QRadioButton *standard_radio;
    QRadioButton *disable_radio;
    QRadioButton *edge_radio;
    QRadioButton *two_finger_radio;
    QString desktop;
    QString release;
};

#endif // TOUCHPADWIDGET_H
