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

#ifndef ANIMATIONWIDGET_H
#define ANIMATIONWIDGET_H

#include <QWidget>
#include <QListWidget>

class SystemDispatcher;
class MainWindow;
class QLabel;
class QPushButton;

class AnimationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AnimationWidget(QWidget *parent = 0, SystemDispatcher *proxy = 0, MainWindow *window = 0);
    ~AnimationWidget();
    void setLanguage();
    void initConnect();
    void initData();
    bool getStatus();

public slots:
    void selectCustomAnimation();
    void setCustomAnimation();
    void deleteSelectedAnimation(QString name);
    void displayCurrentItemInfo(QString info);

private:
    SystemDispatcher *systemproxy;
    bool dataOK;
    MainWindow *parentWindow;
    QWidget * left_widget;
    QWidget * right_widget;

    QLabel *title_label;
    QPushButton *custom_btn;
    QPushButton *ok_btn;
    QWidget *view_widget;
    QWidget *show_widget;
    QLabel *tip_label;

    QListWidget *list_widget;
    QString selected_animation;
};

#endif // ANIMATIONWIDGET_H
