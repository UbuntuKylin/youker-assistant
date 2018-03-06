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

#ifndef WINDOWWIDGET_H
#define WINDOWWIDGET_H

#include <QWidget>
#include "../component/kylinswitcher.h"
#include "settingmodulelpage.h"

class QLabel;
class QPushButton;
class QComboBox;
class QRadioButton;

class WindowWidget : public SettingModulePage
{
    Q_OBJECT
public:
    explicit WindowWidget(QWidget *parent = 0, QString cur_desktop = "");
    ~WindowWidget();
    void setLanguage();
    void initConnect();
    void initSettingData() Q_DECL_OVERRIDE;
    QString settingModuleName() Q_DECL_OVERRIDE;

public slots:
    void setMenuIcon();
    void setMouseWheel(QString selected);
    void setMouseDoubleClick(QString selected);
    void setMouseMiddleClick(QString selected);
    void setMouseRightClick(QString selected);
    void setRadioButtonRowStatus();

    void windowwidget_notify_string(QString key, QString value);
    void windowwidget_notify_bool(QString key, bool value);

    void onSendWindowButtonAlign(const QString &current_value);
    void onSendMenusHaveIcons(bool menuHaveIcons);
    void onSendWindowTitileTags(const QString &current_wheel_type, const QStringList &wheellist, const QStringList &titlebarOptions, const QString &current_double_type, const QString &current_middle_type, const QString &current_right_type);


signals:
    void requesetWindowButtonAlign();
    void requesetMenusHaveIcons();
    void requesetWindowTitileTags();
    void resetMenusHaveIcon(bool b);
    void resetTitlebarWheel(const QString &selected);
    void resetTitlebarDoubleClick(const QString &selected);
    void resetMouseMiddleClick(const QString &selected);
    void resetMouseRightClick(const QString &selected);
    void resetWindowButtonLeftOrRightAlign(bool isLeft);


private:
    QString desktop;
    QStringList m_wheellist;
    QStringList m_titlebarOptions;
    QLabel *icon_label;
    QLabel *wheel_label;
    QLabel *double_click_label;
    QLabel *middle_click_label;
    QLabel *right_click_label;
    KylinSwitcher *icon_switcher;
    QComboBox *wheel_combo;
    QComboBox *double_click_combo;
    QComboBox *middle_click_combo;
    QComboBox *right_click_combo;
    QLabel *position_label;
    QRadioButton *left_radio;
    QRadioButton *right_radio;
};

#endif // WINDOWWIDGET_H
