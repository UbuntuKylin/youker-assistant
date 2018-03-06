/*
 * Copyright (C) 2013 ~ 2018 National University of Defense Technology(NUDT) & Tianjin Kylin Ltd.
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

#ifndef THEMEWIDGET_H
#define THEMEWIDGET_H

#include <QWidget>

class QLabel;
class QPushButton;
class QListWidget;
class QListWidgetItem;
class ThemeView;

#include "settingmodulelpage.h"

//class ThemeWidget : public QWidget
class ThemeWidget : public SettingModulePage
{
    Q_OBJECT
public:
    explicit ThemeWidget(QWidget *parent = 0);
    ~ThemeWidget();
    void initConnect();

    void resetUI();

    void initSettingData() Q_DECL_OVERRIDE;
    QString settingModuleName() Q_DECL_OVERRIDE;

public slots:
    void themewidget_notify_string(QString key, QString value);
    void switchUsingLogo(QString index);
    void changeTheme(QString name);

    void onReceiveThemeList(const QString &currentTheme, const QStringList &themeList);

signals:
    void requestThemeData();
    void changeSystemTheme(const QString &name);

private:
    ThemeView *m_themeView = nullptr;
    QStringList syslist;
    QLabel *label = nullptr;
};

#endif // THEMEWIDGET_H
