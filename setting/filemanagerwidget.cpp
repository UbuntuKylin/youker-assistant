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

#include "filemanagerwidget.h"
#include <QDebug>
#include <QLabel>
#include <QSlider>
#include <QHBoxLayout>

FileManagerWidget::FileManagerWidget(QWidget *parent) :
    SettingModulePage(parent)
{
    location_label = new QLabel();
    mount_media_label = new QLabel();
    open_folder_label = new QLabel();
    autorun_program_label = new QLabel();
    icon_size_label = new QLabel();
    cache_time_label = new QLabel();
    cache_size_label = new QLabel();
    size_value_label = new QLabel();
    time_value_label = new QLabel();
    cache_value_label = new QLabel();
    location_switcher = new KylinSwitcher();
    mount_media_switcher = new KylinSwitcher();
    open_folder_switcher = new KylinSwitcher();
    autorun_program_switcher = new KylinSwitcher();
    icon_size_slider = new QSlider(Qt::Horizontal);
    icon_size_slider->setRange(16, 512);
    icon_size_slider->setSingleStep(1);
//    icon_size_slider->setTickPosition(QSlider::TicksRight);
    icon_size_slider->setFocusPolicy(Qt::NoFocus);
//    icon_size_slider->setMinimum(1);
//    icon_size_slider->setMaximum(10);
//    icon_size_slider->setValue(2);

    cache_time_slider = new QSlider(Qt::Horizontal);
    cache_time_slider->setRange(-1, 180);
    cache_time_slider->setSingleStep(1);
//    cache_time_slider->setTickPosition(QSlider::TicksRight);
    cache_time_slider->setFocusPolicy(Qt::NoFocus);
//    cache_time_slider->setValue(2);

    cache_size_slider = new QSlider(Qt::Horizontal);
    cache_size_slider->setRange(-1, 512);
    cache_size_slider->setSingleStep(1);
//    cache_size_slider->setTickPosition(QSlider::TicksRight);
    cache_size_slider->setFocusPolicy(Qt::NoFocus);
//    cache_size_slider->setValue(2);

    location_label->setFixedWidth(245);
    mount_media_label->setFixedWidth(245);
    open_folder_label->setFixedWidth(245);
    autorun_program_label->setFixedWidth(245);
    icon_size_label->setFixedWidth(245);
    cache_time_label->setFixedWidth(245);
    cache_size_label->setFixedWidth(245);



//    QFormLayout *form_layout = new QFormLayout();
//    form_layout->setSpacing(10);
//    form_layout->setHorizontalSpacing(5);
//    form_layout->setRowWrapPolicy(QFormLayout::DontWrapRows);
//    form_layout->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
//    form_layout->addRow(QString(tr("Display entry location") + ":"), location_switcher);
//    form_layout->addRow(QString(tr("Automatically mount media") + ":"), mount_media_switcher);
//    form_layout->addRow(QString(tr("Automatically open a folder") + ":"), open_folder_switcher);
//    form_layout->addRow(QString(tr("Prompt autorun programs") + ":"), autorun_program_switcher);
//    form_layout->addRow(QString(tr("Thumbnail icon size (pixels)") + ":"), icon_size_slider);
//    form_layout->addRow(QString(tr("Thumbnail cache time (days)") + ":"), cache_time_slider);
//    form_layout->addRow(QString(tr("Maximum thumbnail cache size (MB)") + ":"), cache_size_slider);



    QHBoxLayout *layout1 = new QHBoxLayout();
    layout1->setSpacing(10);
    layout1->addWidget(location_label);
    layout1->addWidget(location_switcher);
    layout1->addStretch();
    QHBoxLayout *layout2 = new QHBoxLayout();
    layout2->setSpacing(10);
    layout2->addWidget(mount_media_label);
    layout2->addWidget(mount_media_switcher);
    layout2->addStretch();
    QHBoxLayout *layout3 = new QHBoxLayout();
    layout3->setSpacing(10);
    layout3->addWidget(open_folder_label);
    layout3->addWidget(open_folder_switcher);
    layout3->addStretch();
    QHBoxLayout *layout4 = new QHBoxLayout();
    layout4->setSpacing(10);
    layout4->addWidget(autorun_program_label);
    layout4->addWidget(autorun_program_switcher);
    layout4->addStretch();
    QHBoxLayout *layout5 = new QHBoxLayout();
    layout5->setSpacing(10);
    layout5->addWidget(icon_size_label);
    layout5->addWidget(icon_size_slider);
    layout5->addWidget(size_value_label);
    layout5->addStretch();
    QHBoxLayout *layout6 = new QHBoxLayout();
    layout6->setSpacing(10);
    layout6->addWidget(cache_time_label);
    layout6->addWidget(cache_time_slider);
    layout6->addWidget(time_value_label);
    layout6->addStretch();
    QHBoxLayout *layout7 = new QHBoxLayout();
    layout7->setSpacing(10);
    layout7->addWidget(cache_size_label);
    layout7->addWidget(cache_size_slider);
    layout7->addWidget(cache_value_label);
    layout7->addStretch();
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addLayout(layout1);
    layout->addLayout(layout2);
    layout->addLayout(layout3);
    layout->addLayout(layout4);
    layout->addLayout(layout5);
    layout->addLayout(layout6);
    layout->addLayout(layout7);
    layout->addStretch();
    setLayout(layout);
    layout->setSpacing(10);
    layout->setContentsMargins(20, 20, 0, 0);


//    setLayout(form_layout);

//    splitter->addWidget(top_widget);
//    splitter->addWidget(bottom_widget);

//    QHBoxLayout *main_layout = new QHBoxLayout;
//    main_layout->addStretch();
//    main_layout->addWidget(splitter);
//    main_layout->setSpacing(0);
//    main_layout->setContentsMargins(0, 0, 0, 0);
//    setLayout(main_layout);
//    this->initSettingData();
    this->setLanguage();
}

FileManagerWidget::~FileManagerWidget()
{
    if (location_label != NULL) {
        delete location_label;
        location_label = NULL;
    }
    if (mount_media_label != NULL) {
        delete mount_media_label;
        mount_media_label = NULL;
    }
    if (open_folder_label != NULL) {
        delete open_folder_label;
        open_folder_label = NULL;
    }
    if (autorun_program_label != NULL) {
        delete autorun_program_label;
        autorun_program_label = NULL;
    }
    if (icon_size_label != NULL) {
        delete icon_size_label;
        icon_size_label = NULL;
    }
    if (size_value_label != NULL) {
        delete size_value_label;
        size_value_label = NULL;
    }
    if (cache_time_label != NULL) {
        delete cache_time_label;
        cache_time_label = NULL;
    }
    if (time_value_label != NULL) {
        delete time_value_label;
        time_value_label = NULL;
    }
    if (cache_size_label != NULL) {
        delete cache_size_label;
        cache_size_label = NULL;
    }
    if (cache_value_label != NULL) {
        delete cache_value_label;
        cache_value_label = NULL;
    }
    if (location_switcher != NULL) {
        delete location_switcher;
        location_switcher = NULL;
    }
    if (mount_media_switcher != NULL) {
        delete mount_media_switcher;
        mount_media_switcher = NULL;
    }
    if (open_folder_switcher != NULL) {
        delete open_folder_switcher;
        open_folder_switcher = NULL;
    }
    if (autorun_program_switcher != NULL) {
        delete autorun_program_switcher;
        autorun_program_switcher = NULL;
    }
    if (icon_size_slider != NULL) {
        delete icon_size_slider;
        icon_size_slider = NULL;
    }
    if (cache_time_slider != NULL) {
        delete cache_time_slider;
        cache_time_slider = NULL;
    }
    if (cache_size_slider != NULL) {
        delete cache_size_slider;
        cache_size_slider = NULL;
    }
}

QString FileManagerWidget::settingModuleName()
{
    return "FMPage";
}

void FileManagerWidget::setLanguage() {
//    title_label->setText(tr("File Manager"));
//    description_label->setText(tr("Manage the Nautilus file manager. Tips: if the thumbnail's cache time or size is set to -1, it will not be checked."));
//    back_btn->setText(tr("Back"));
    location_label->setText(tr("Display entry location") + ":");
    mount_media_label->setText(tr("Automatically mount media") + ":");
    open_folder_label->setText(tr("Automatically open a folder") + ":");
    autorun_program_label->setText(tr("Prompt autorun programs") + ":");
    icon_size_label->setText(tr("Thumbnail icon size (pixels)") + ":");
    cache_time_label->setText(tr("Thumbnail cache time (days)") + ":");
    cache_size_label->setText(tr("Maximum thumbnail cache size (MB)") + ":");
}

void FileManagerWidget::initSettingData()
{
    emit requestFileManagerData();
//    location_switcher->switchedOn = sessionproxy->get_location_replace_pathbar_qt();
//    mount_media_switcher->switchedOn = sessionproxy->get_auto_mount_media_qt();
//    open_folder_switcher->switchedOn = sessionproxy->get_auto_open_folder_qt();
//    autorun_program_switcher->switchedOn = sessionproxy->get_prompt_autorun_programs_qt();
//    icon_size_slider->setValue(sessionproxy->get_thumbnail_icon_size_qt());
//    cache_time_slider->setValue(sessionproxy->get_thumbnail_cache_time_qt());
//    cache_size_slider->setValue(sessionproxy->get_thumbnail_cache_size_qt());
//    size_value_label->setText(QString::number(icon_size_slider->value()));
//    time_value_label->setText(QString::number(cache_time_slider->value()));
//    cache_value_label->setText(QString::number(cache_size_slider->value()));

    this->initConnect();
}

void FileManagerWidget::onSendFileManagerData(bool locationReplacePathbar, bool autoMountMedia, bool autoOpenFolder, bool promptAutorunPrograms, int thumbnailIconSize, int thumbnailCacheTime, int thumbnailCacheSize)
{
    location_switcher->switchedOn = locationReplacePathbar;
    mount_media_switcher->switchedOn = autoMountMedia;
    open_folder_switcher->switchedOn = autoOpenFolder;
    autorun_program_switcher->switchedOn = promptAutorunPrograms;
    icon_size_slider->setValue(thumbnailIconSize);
    cache_time_slider->setValue(thumbnailCacheTime);
    cache_size_slider->setValue(thumbnailCacheSize);
    size_value_label->setText(QString::number(icon_size_slider->value()));
    time_value_label->setText(QString::number(cache_time_slider->value()));
    cache_value_label->setText(QString::number(cache_size_slider->value()));
}

void FileManagerWidget::initConnect() {
//    connect(back_btn, SIGNAL(clicked()), this, SIGNAL(showSettingMainWidget()));
    connect(location_switcher, SIGNAL(clicked()), this, SLOT(setLocation()));
    connect(mount_media_switcher, SIGNAL(clicked()), this, SLOT(setMountMedia()));
    connect(open_folder_switcher, SIGNAL(clicked()), this, SLOT(setOpenFolder()));
    connect(autorun_program_switcher, SIGNAL(clicked()), this, SLOT(setAutorunProgram()));
    connect(icon_size_slider, SIGNAL(valueChanged(int)), this, SLOT(setIconSizeValue(int)));
    connect(cache_time_slider, SIGNAL(valueChanged(int)), this, SLOT(setCacheTimeValue(int)));
    connect(cache_size_slider, SIGNAL(valueChanged(int)), this, SLOT(setCacheSizeValue(int)));

//    connect(sessionproxy, SIGNAL(bool_value_notify(QString, bool)), this, SLOT(nautiluswidget_notify_bool(QString, bool)));
//    connect(sessionproxy, SIGNAL(int_value_notify(QString, int)), this, SLOT(nautiluswidget_notify_int(QString, int)));
}

void FileManagerWidget::nautiluswidget_notify_bool(QString key, bool value)
{
    if (key == "always-use-location-entry") {
        location_switcher->switchedOn = value;
    }
    else if (key == "automount") {
        mount_media_switcher->switchedOn = value;
    }
    else if (key == "automount-open") {
        open_folder_switcher->switchedOn = value;
    }
    else if (key == "autorun-never") {
        autorun_program_switcher->switchedOn = value;
    }
}

void FileManagerWidget::nautiluswidget_notify_int(QString key, int value)
{
    if (key == "thumbnail-size") {
        icon_size_slider->setValue(value);
        size_value_label->setText(QString::number(value));
    }
    else if (key == "maximum-age") {
        cache_time_slider->setValue(value);
        time_value_label->setText(QString::number(value));
    }
    else if (key == "maximum-size") {
        cache_size_slider->setValue(value);
        cache_value_label->setText(QString::number(value));
    }
}

void FileManagerWidget::setLocation()
{
    emit resetLocationReplacePathbar(location_switcher->switchedOn);
//    sessionproxy->set_location_replace_pathbar_qt(location_switcher->switchedOn);
}

void FileManagerWidget::setMountMedia()
{
    emit resetAutoMountMedia(mount_media_switcher->switchedOn);
//    sessionproxy->set_auto_mount_media_qt(mount_media_switcher->switchedOn);
}

void FileManagerWidget::setOpenFolder()
{
    emit resetAutoOpenFolder(open_folder_switcher->switchedOn);
//    sessionproxy->set_auto_open_folder_qt(open_folder_switcher->switchedOn);
}

void FileManagerWidget::setAutorunProgram()
{
    emit resetPromptAutorunPrograms(autorun_program_switcher->switchedOn);
//    sessionproxy->set_prompt_autorun_programs_qt(autorun_program_switcher->switchedOn);
}

void FileManagerWidget::setIconSizeValue(int value)
{
    size_value_label->setText(QString::number(value));
    emit resetThumbnailIconSize(value);
//    sessionproxy->set_thumbnail_icon_size_qt(value);
}

void FileManagerWidget::setCacheTimeValue(int value)
{
    time_value_label->setText(QString::number(value));
    emit resetThumbnailCacheTime(value);
//    sessionproxy->set_thumbnail_cache_time_qt(value);
}

void FileManagerWidget::setCacheSizeValue(int value)
{
    cache_value_label->setText(QString::number(value));
    emit resetThumbnailCacheSize(value);
//    sessionproxy->set_thumbnail_cache_size_qt(value);
}
