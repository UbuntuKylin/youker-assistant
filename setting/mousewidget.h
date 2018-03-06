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

#ifndef MOUSEWIDGET_H
#define MOUSEWIDGET_H

#include <QWidget>
#include <QHBoxLayout>

class QLabel;
class QPushButton;
class QComboBox;
class QRadioButton;
#include "settingmodulelpage.h"

class MouseWidget : public SettingModulePage
{
    Q_OBJECT
public:
    explicit MouseWidget(QWidget *parent = 0, QString cur_desktop = "");
    ~MouseWidget();
    void setLanguage();
    void initConnect();
    void initSettingData() Q_DECL_OVERRIDE;
    QString settingModuleName() Q_DECL_OVERRIDE;

signals:
//    void showSettingMainWidget();
    void requestMouseData();

    void resetMouseCursorTheme(const QString &theme);
    void resetMouseCursorSize(int cursorSize);

public slots:
    void setMouseCursorTheme(QString selectTheme);
    void setRadioButtonRowStatus(/*bool status*/);

    void mousewidget_notify_string(QString key, QString value);
    void mousewidget_notify_int(QString key, int value);

    void onReceiveMouseThemeAndCusorSize(const QString &currentTheme, const QStringList &themeList, int cursorSize);

private:
    QStringList cursorlist;
    QLabel *theme_label;
    QLabel *size_label;
    QComboBox *theme_combo;
    QRadioButton *small_size;
    QRadioButton *big_size;
    QString desktop;
};

#endif // MOUSEWIDGET_H
