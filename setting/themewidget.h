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
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QListView>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QListWidget>
#include <QSplitter>

class SessionDispatcher;

class ThemeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ThemeWidget(QWidget *parent = 0, SessionDispatcher *proxy = 0);
    ~ThemeWidget();
    void setLanguage();
    void initConnect();
    void initCurrentTheme(QListWidgetItem *init_item);

protected:
    void paintEvent(QPaintEvent *);

//signals:
//    void showSettingMainWidget();

public slots:
    void onItemClicked(QListWidgetItem *selected_item);

private:
//    QSplitter *splitter;
//    QWidget * top_widget;
//    QWidget * bottom_widget;

//    QPushButton *back_btn;
//    QLabel *title_label;
//    QLabel *description_label;

//    QListView *list_view;
//    QStringListModel *model;
//    QStandardItemModel *cokMusicListModel;
    QListWidget *list_widget;
    int current_index;
    QLabel *using_label;
    SessionDispatcher *sessionproxy;
};

#endif // THEMEWIDGET_H
