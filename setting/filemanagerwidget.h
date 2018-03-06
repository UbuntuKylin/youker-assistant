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

#ifndef FILEMANAGERWIDGET_H
#define FILEMANAGERWIDGET_H

#include <QWidget>
#include "../component/kylinswitcher.h"

class QLabel;
class QPushButton;
class QSlider;
#include "settingmodulelpage.h"

class FileManagerWidget : public SettingModulePage
{
    Q_OBJECT
public:
    explicit FileManagerWidget(QWidget *parent = 0);
    ~FileManagerWidget();
    void setLanguage();
    void initConnect();
    void initSettingData() Q_DECL_OVERRIDE;
    QString settingModuleName() Q_DECL_OVERRIDE;

public slots:
    void setLocation();
    void setMountMedia();
    void setOpenFolder();
    void setAutorunProgram();
    void setIconSizeValue(int value);
    void setCacheTimeValue(int value);
    void setCacheSizeValue(int value);

    void nautiluswidget_notify_bool(QString key, bool value);
    void nautiluswidget_notify_int(QString key, int value);

    void onSendFileManagerData(bool locationReplacePathbar, bool autoMountMedia, bool autoOpenFolder, bool promptAutorunPrograms, int thumbnailIconSize, int thumbnailCacheTime, int thumbnailCacheSize);


signals:
    void requestFileManagerData();
    void resetLocationReplacePathbar(bool b);
    void resetAutoMountMedia(bool b);
    void resetAutoOpenFolder(bool b);
    void resetPromptAutorunPrograms(bool b);
    void resetThumbnailIconSize(int value);
    void resetThumbnailCacheTime(int value);
    void resetThumbnailCacheSize(int value);

private:
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

#endif // FILEMANAGERWIDGET_H
