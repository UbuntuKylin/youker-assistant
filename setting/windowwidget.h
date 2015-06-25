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

class QLabel;
class QPushButton;
class QComboBox;
class QRadioButton;

class SessionDispatcher;

class WindowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WindowWidget(QWidget *parent = 0, SessionDispatcher *proxy = 0, QString cur_desktop = "");
    ~WindowWidget();
    void setLanguage();
    void initConnect();
    void initData();
    bool getStatus();

public slots:
    void setMenuIcon();
    void setMouseWheel(QString selected);
    void setMouseDoubleClick(QString selected);
    void setMouseMiddleClick(QString selected);
    void setMouseRightClick(QString selected);
    void setRadioButtonRowStatus();

    void windowwidget_notify_string(QString key, QString value);
    void windowwidget_notify_bool(QString key, bool value);

private:
    SessionDispatcher *sessionproxy;
    bool dataOK;
    QString desktop;
    QStringList wheellist;
    QStringList titlebar_options;
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
