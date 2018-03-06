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

#include "iconwidget.h"
#include <QDebug>
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>

IconWidget::IconWidget(QWidget *parent, QString cur_desktop) :
    SettingModulePage(parent),desktop(cur_desktop)
{
    theme_label = new QLabel();
//    show_label = new QLabel();
    computer_label = new QLabel();

    folder_label = new QLabel();
    network_label = new QLabel();
    recycle_label = new QLabel();
    disk_label = new QLabel();
    theme_combo = new QComboBox();
//    show_switcher = new KylinSwitcher();
    computer_switcher = new KylinSwitcher();
    folder_switcher = new KylinSwitcher();
    network_switcher = new KylinSwitcher();
    recycle_switcher = new KylinSwitcher();
    disk_switcher = new KylinSwitcher();

    if (this->desktop != "mate" && this->desktop != "MATE")
    {
        computer_label->hide();
        computer_switcher->hide();
    }

    theme_label->setFixedWidth(150);
//    show_label->setFixedWidth(150);
    computer_label->setFixedWidth(150);
    folder_label->setFixedWidth(150);
    network_label->setFixedWidth(150);
    recycle_label->setFixedWidth(150);
    disk_label->setFixedWidth(150);


//    switcher = new KylinSwitcher();
//    connect(switcher, SIGNAL(clicked()), this, SLOT(changeSwitcherStatus()));
    QHBoxLayout *layout1 = new QHBoxLayout();
    layout1->setSpacing(10);
    layout1->addWidget(theme_label);
    layout1->addWidget(theme_combo);
    layout1->addStretch();
//    QHBoxLayout *layout2 = new QHBoxLayout();
//    layout2->setSpacing(10);
//    layout2->addWidget(show_label);
//    layout2->addWidget(show_switcher);
//    layout2->addStretch();
    QHBoxLayout *layout3 = new QHBoxLayout();
    layout3->setSpacing(10);
    layout3->addWidget(computer_label);
    layout3->addWidget(computer_switcher);
    layout3->addStretch();
    QHBoxLayout *layout4 = new QHBoxLayout();
    layout4->setSpacing(10);
    layout4->addWidget(folder_label);
    layout4->addWidget(folder_switcher);
    layout4->addStretch();
    QHBoxLayout *layout5 = new QHBoxLayout();
    layout5->setSpacing(10);
    layout5->addWidget(network_label);
    layout5->addWidget(network_switcher);
    layout5->addStretch();
    QHBoxLayout *layout6 = new QHBoxLayout();
    layout6->setSpacing(10);
    layout6->addWidget(recycle_label);
    layout6->addWidget(recycle_switcher);
    layout6->addStretch();
    QHBoxLayout *layout7 = new QHBoxLayout();
    layout7->setSpacing(10);
    layout7->addWidget(disk_label);
    layout7->addWidget(disk_switcher);
    layout7->addStretch();
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addLayout(layout1);
//    layout->addLayout(layout2);
    layout->addLayout(layout3);
    layout->addLayout(layout4);
    layout->addLayout(layout5);
    layout->addLayout(layout6);
    layout->addLayout(layout7);
    layout->addStretch();
    setLayout(layout);
    layout->setSpacing(10);
    layout->setContentsMargins(20, 20, 0, 0);
//    QGridLayout *grid_layout = new QGridLayout;
//    grid_layout->addWidget(theme_label, 0, 0/* ,1, 1*/);
//    grid_layout->addWidget(theme_combo, 0, 1/* ,1, 1*/);
//    grid_layout->addWidget(folder_label, 1, 0/* ,1, 1*/);
//    grid_layout->addWidget(show_switcher, 1, 1/* ,1, 1*/);
//    grid_layout->addWidget(show_label, 2, 0 /*,1, 1*/);
//    grid_layout->addWidget(folder_switcher, 2, 1/* ,1, 1*/);
//    grid_layout->addWidget(network_label, 3, 0 /*,1, 1*/);
//    grid_layout->addWidget(network_switcher, 3, 1 /*,1, 1*/);
//    grid_layout->addWidget(recycle_label, 4, 0 /*,1, 1*/);
//    grid_layout->addWidget(recycle_switcher, 4, 1/* ,1, 1*/);
//    grid_layout->addWidget(disk_label, 5, 0/* ,1, 1*/);
//    grid_layout->addWidget(disk_switcher, 5, 1/* ,1, 1*/);
//    grid_layout->setColumnStretch(0,1);
//    grid_layout->setColumnStretch(1,3);
//    bottom_widget->setLayout(grid_layout);

//    splitter->addWidget(top_widget);
//    splitter->addWidget(bottom_widget);

//    for(int i = 0; i<splitter->count();i++)
//    {
//        QSplitterHandle *handle = splitter->handle(i);
//        handle->setEnabled(false);
//    }



//    QHBoxLayout *main_layout = new QHBoxLayout;
//    main_layout->addStretch();
//    main_layout->addWidget(splitter);
//    main_layout->setSpacing(0);
//    main_layout->setContentsMargins(0, 0, 0, 0);
//    setLayout(main_layout);
//    this->initSettingData();
    this->setLanguage();
}

IconWidget::~IconWidget()
{
    if (theme_label != NULL) {
        delete theme_label;
        theme_label = NULL;
    }
    if (computer_label != NULL) {
        delete computer_label;
        computer_label = NULL;
    }
    if (folder_label != NULL) {
        delete folder_label;
        folder_label = NULL;
    }
    if (network_label != NULL) {
        delete network_label;
        network_label = NULL;
    }
    if (recycle_label != NULL) {
        delete recycle_label;
        recycle_label = NULL;
    }
    if (disk_label != NULL) {
        delete disk_label;
        disk_label = NULL;
    }
    if (theme_combo != NULL) {
        delete theme_combo;
        theme_combo = NULL;
    }
    if (computer_switcher != NULL) {
        delete computer_switcher;
        computer_switcher = NULL;
    }
    if (folder_switcher != NULL) {
        delete folder_switcher;
        folder_switcher = NULL;
    }
    if (network_switcher != NULL) {
        delete network_switcher;
        network_switcher = NULL;
    }
    if (recycle_switcher != NULL) {
        delete recycle_switcher;
        recycle_switcher = NULL;
    }
    if (disk_switcher != NULL) {
        delete disk_switcher;
        disk_switcher = NULL;
    }
}

QString IconWidget::settingModuleName()
{
    return "IconPage";
}

void IconWidget::changeSwitcherStatus() {

}

void IconWidget::setLanguage() {
//    title_label->setText(tr("Desktop Icons"));
//    description_label->setText(tr("Set the desktop icon theme and the visibility of desktop icons."));
//    back_btn->setText(tr("Back"));
    theme_label->setText(tr("Icon theme") + ":");
//    show_label->setText(tr("Show Desktop Icons") + ":");
    computer_label->setText(tr("Computer") + ":");
    folder_label->setText(tr("Home Folder") + ":");
    network_label->setText(tr("Network") + ":");
    recycle_label->setText(tr("Trash") + ":");
    disk_label->setText(tr("Mounted Volumes") + ":");
}

void IconWidget::onReceiveIconThemeList(const QString &currentTheme, const QStringList &themeList)
{
    iconlist.clear();
    iconlist = themeList;
    theme_combo->clear();
    theme_combo->clearEditText();
    theme_combo->addItems(iconlist);

    QList<QString>::Iterator it = iconlist.begin(), itend = iconlist.end();
    int initIndex = 0;
    for(;it != itend; it++,initIndex++)
    {
        if(*it == currentTheme)
            break;
    }
    theme_combo->setCurrentIndex(initIndex);
}

void IconWidget::onReceiveDisplayIconValue(bool computer, bool folder, bool network, bool recycle, bool disk)
{
    if (this->desktop == "mate" || this->desktop == "MATE" || this->desktop == "UKUI" || this->desktop == "ukui")
    {
        computer_switcher->switchedOn = computer;
    }

    folder_switcher->switchedOn = folder;
    network_switcher->switchedOn = network;
    recycle_switcher->switchedOn = recycle;
    disk_switcher->switchedOn = disk;
}

void IconWidget::initSettingData()
{
    emit this->requestIconData();
    this->initConnect();

    /*QString current_icon_theme = sessionproxy->get_icon_theme_qt();
    iconlist  = sessionproxy->get_icon_themes_qt();
    theme_combo->clear();
    theme_combo->clearEditText();
    theme_combo->addItems(iconlist);

    QList<QString>::Iterator it = iconlist.begin(), itend = iconlist.end();
    int initIndex = 0;
    for(;it != itend; it++,initIndex++)
    {
        if(*it == current_icon_theme)
            break;
    }
    theme_combo->setCurrentIndex(initIndex);

//    show_switcher->setSwitchStatus(sessionproxy->get_show_desktop_icons_qt());
//    folder_switcher->setSwitchStatus(sessionproxy->get_show_homefolder_qt());
//    network_switcher->setSwitchStatus(sessionproxy->get_show_network_qt());
//    recycle_switcher->setSwitchStatus(sessionproxy->get_show_trash_qt());
//    disk_switcher->setSwitchStatus(sessionproxy->get_show_devices_qt());
//    show_switcher->switchedOn = sessionproxy->get_show_desktop_icons_qt();

    if (this->desktop == "mate" || this->desktop == "MATE" || this->desktop == "UKUI" || this->desktop == "ukui")
    {
        computer_switcher->switchedOn = sessionproxy->get_show_computer_qt();
    }

    folder_switcher->switchedOn = sessionproxy->get_show_homefolder_qt();
    network_switcher->switchedOn = sessionproxy->get_show_network_qt();
    recycle_switcher->switchedOn = sessionproxy->get_show_trash_qt();
    disk_switcher->switchedOn = sessionproxy->get_show_devices_qt();

    */
}

void IconWidget::initConnect() {
//    connect(back_btn, SIGNAL(clicked()), this, SIGNAL(showSettingMainWidget()));
//    connect(theme_combo, SIGNAL(currentIndexChanged(int)),  this, SLOT(setIconTheme()));
    connect(theme_combo, SIGNAL(currentIndexChanged(QString)),  this, SLOT(setIconTheme(QString)));
//    connect(show_switcher, SIGNAL(clicked()),  this, SLOT(setShowDesktopIcons()));
    connect(computer_switcher, SIGNAL(clicked()),  this, SLOT(setComputerIcon()));
    connect(folder_switcher, SIGNAL(clicked()),  this, SLOT(setFolderIcon()));
    connect(network_switcher, SIGNAL(clicked()),  this, SLOT(setNetworkIcon()));
    connect(recycle_switcher, SIGNAL(clicked()),  this, SLOT(setRecycleBinIcon()));
    connect(disk_switcher, SIGNAL(clicked()),  this, SLOT(setDiskIcon()));

    //20180101
//    connect(sessionproxy, SIGNAL(string_value_notify(QString, QString)), this, SLOT(iconwidget_notify_string(QString, QString)));
//    connect(sessionproxy, SIGNAL(bool_value_notify(QString, bool)), this, SLOT(iconwidget_notify_bool(QString, bool)));
}

void IconWidget::iconwidget_notify_string(QString key, QString value)
{
    if (key == "icon-theme") {
        QList<QString>::Iterator it = iconlist.begin(), itend = iconlist.end();
        int index = -1;
        bool exist = false;
        for(;it != itend; it++)
        {
            ++index;
            if(*it == value) {
                exist = true;
                break;
            }
        }
        if (exist) {
            exist = false;
            theme_combo->setCurrentIndex(index);
        }
        else
            theme_combo->setCurrentIndex(-1);
    }
}

void IconWidget::iconwidget_notify_bool(QString key, bool value)
{
//    if (key == "show-desktop-icons") {
//        show_switcher->switchedOn = value;
//    }
    if (key == "computer-icon-visible") {
        computer_switcher->switchedOn = value;
    }
    else if (key == "home-icon-visible")
    {
        folder_switcher->switchedOn = value;
    }
    else if (key == "network-icon-visible") {
        network_switcher->switchedOn = value;
    }
    else if (key == "trash-icon-visible") {
        recycle_switcher->switchedOn = value;
    }
    else if (key == "volumes-visible") {
        disk_switcher->switchedOn = value;
    }
}

void IconWidget::setIconTheme(QString selectTheme) {
//    sessionproxy->set_icon_theme_qt(selectTheme);
    emit resetIconTheme(selectTheme);
}

//void IconWidget::setShowDesktopIcons() {
//    sessionproxy->set_show_desktop_icons_qt(show_switcher->switchedOn);
//}

void IconWidget::setComputerIcon() {
//    emit changeSystemTheme(name);
    emit displayComputerIcon(computer_switcher->switchedOn);
//    sessionproxy->set_show_computer_qt(computer_switcher->switchedOn);
}

void IconWidget::setFolderIcon() {
    emit displayFolderIcon(folder_switcher->switchedOn);
//    sessionproxy->set_show_homefolder_qt(folder_switcher->switchedOn);
}

void IconWidget::setNetworkIcon() {
    emit displayNetworkIcon(network_switcher->switchedOn);
//    sessionproxy->set_show_network_qt(network_switcher->switchedOn);
}

void IconWidget::setRecycleBinIcon() {
    emit displayRecycleBinIcon(recycle_switcher->switchedOn);
//    sessionproxy->set_show_trash_qt(recycle_switcher->switchedOn);
}

void IconWidget::setDiskIcon() {
    emit displayDiskIcon(disk_switcher->switchedOn);
//    sessionproxy->set_show_devices_qt(disk_switcher->switchedOn);
}
