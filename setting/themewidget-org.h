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

#ifndef THEMEWIDGET_H
#define THEMEWIDGET_H

#include <QWidget>

class SessionDispatcher;
class QLabel;
class QPushButton;
class QListWidget;
class QListWidgetItem;

class ThemeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ThemeWidget(QWidget *parent = 0, SessionDispatcher *proxy = 0);
    ~ThemeWidget();
    void initConnect();
    void initCurrentTheme(QListWidgetItem *init_item);
    void initData();
    bool getStatus();

protected:
    void paintEvent(QPaintEvent *);

public slots:
    void onItemClicked(QListWidgetItem *selected_item);
    void themewidget_notify_string(QString key, QString value);

private:
    QListWidget *list_widget;
    int current_index;
    QLabel *using_label;
    SessionDispatcher *sessionproxy;
    bool dataOK;
    int initIndex;
    QStringList syslist;
};

#endif // THEMEWIDGET_H
