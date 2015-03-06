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

#ifndef NAUTILUSWIDGET_H
#define NAUTILUSWIDGET_H

#include <QWidget>
#include "../component/kylinswitcher.h"

class SessionDispatcher;
class QLabel;
class QPushButton;
class QSlider;

class NautilusWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NautilusWidget(QWidget *parent = 0, SessionDispatcher *proxy = 0);
    ~NautilusWidget();
    void setLanguage();
    void initConnect();
    void initData();

public slots:
    void setLocation();
    void setMountMedia();
    void setOpenFolder();
    void setAutorunProgram();
    void setIconSizeValue(int value);
    void setCacheTimeValue(int value);
    void setCacheSizeValue(int value);

private:
    SessionDispatcher *sessionproxy;
    QLabel *location_label;
    QLabel *mount_media_label;
    QLabel *open_folder_label;
    QLabel *autorun_program_label;
    QLabel *icon_size_label;
    QLabel *size_value_label;
    QLabel *cache_time_label;
    QLabel *time_value_label;
    QLabel *cache_size_label;
    QLabel *cache_value_label;
    KylinSwitcher *location_switcher;
    KylinSwitcher *mount_media_switcher;
    KylinSwitcher *open_folder_switcher;
    KylinSwitcher *autorun_program_switcher;
    QSlider *icon_size_slider;
    QSlider *cache_time_slider;
    QSlider *cache_size_slider;

};

#endif // NAUTILUSWIDGET_H
