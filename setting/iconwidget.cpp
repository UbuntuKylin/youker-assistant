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
#include "../dbusproxy/youkersessiondbus.h"
#include <QDebug>
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>

IconWidget::IconWidget(QWidget *parent, SessionDispatcher *proxy, QString cur_desktop) :
    QWidget(parent),
    sessionproxy(proxy)
{
    theme_label = new QLabel();
    show_label = new QLabel();
    computer_label = new QLabel();

    folder_label = new QLabel();
    network_label = new QLabel();
    recycle_label = new QLabel();
    disk_label = new QLabel();
    theme_combo = new QComboBox();
    show_switcher = new KylinSwitcher();
    computer_switcher = new KylinSwitcher();
    folder_switcher = new KylinSwitcher();
    network_switcher = new KylinSwitcher();
    recycle_switcher = new KylinSwitcher();
    disk_switcher = new KylinSwitcher();

    if (cur_desktop != "mate")
    {
        computer_label->hide();
        computer_switcher->hide();
    }

    theme_label->setFixedWidth(150);
    show_label->setFixedWidth(150);
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
    QHBoxLayout *layout2 = new QHBoxLayout();
    layout2->setSpacing(10);
    layout2->addWidget(show_label);
    layout2->addWidget(show_switcher);
    layout2->addStretch();
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
    this->initData();
    this->setLanguage();
    this->initConnect();
}

IconWidget::~IconWidget()
{
//    if(title_label != NULL)
//    {
//        delete title_label;
//        title_label = NULL;
//    }
//    if(description_label != NULL)
//    {
//        delete description_label;
//        description_label = NULL;
//    }
//    if(back_btn != NULL)
//    {
//        delete back_btn;
//        back_btn = NULL;
//    }
//    if(switcher != NULL)
//    {
//        delete switcher;
//        switcher = NULL;
//    }

//    if(splitter != NULL)
//    {
//        delete splitter;
//        splitter = NULL;
//    }
//    if(top_widget != NULL)
//    {
//        delete top_widget;
//        top_widget = NULL;
//    }
//    if(bottom_widget != NULL)
//    {
//        delete bottom_widget;
//        bottom_widget = NULL;
//    }
}

void IconWidget::changeSwitcherStatus() {

}

void IconWidget::setLanguage() {
//    title_label->setText(tr("Desktop Icons"));
//    description_label->setText(tr("Set the desktop icon theme and the visibility of desktop icons."));
//    back_btn->setText(tr("Back"));
    theme_label->setText(tr("Icon theme") + ":");
    show_label->setText(tr("Show Desktop Icons") + ":");
    computer_label->setText(tr("Computer") + ":");
    folder_label->setText(tr("Home Folder") + ":");
    network_label->setText(tr("Network") + ":");
    recycle_label->setText(tr("Trash") + ":");
    disk_label->setText(tr("Mounted Volumes") + ":");
}

void IconWidget::initData()
{
    QString current_icon_theme = sessionproxy->get_icon_theme_qt();
    QStringList iconlist  = sessionproxy->get_icon_themes_qt();
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
    show_switcher->switchedOn = sessionproxy->get_show_desktop_icons_qt();
    computer_switcher->switchedOn = sessionproxy->get_show_computer_qt();
    folder_switcher->switchedOn = sessionproxy->get_show_homefolder_qt();
    network_switcher->switchedOn = sessionproxy->get_show_network_qt();
    recycle_switcher->switchedOn = sessionproxy->get_show_trash_qt();
    disk_switcher->switchedOn = sessionproxy->get_show_devices_qt();
}

void IconWidget::initConnect() {
//    connect(back_btn, SIGNAL(clicked()), this, SIGNAL(showSettingMainWidget()));
//    connect(theme_combo, SIGNAL(currentIndexChanged(int)),  this, SLOT(setIconTheme()));
    connect(theme_combo, SIGNAL(currentIndexChanged(QString)),  this, SLOT(setIconTheme(QString)));
    connect(show_switcher, SIGNAL(clicked()),  this, SLOT(setShowDesktopIcons()));
    connect(computer_switcher, SIGNAL(clicked()),  this, SLOT(setComputerIcon()));
    connect(folder_switcher, SIGNAL(clicked()),  this, SLOT(setFolderIcon()));
    connect(network_switcher, SIGNAL(clicked()),  this, SLOT(setNetworkIcon()));
    connect(recycle_switcher, SIGNAL(clicked()),  this, SLOT(setRecycleBinIcon()));
    connect(disk_switcher, SIGNAL(clicked()),  this, SLOT(setDiskIcon()));
}

void IconWidget::setIconTheme(QString selectTheme) {
    sessionproxy->set_icon_theme_qt(selectTheme);
}

void IconWidget::setShowDesktopIcons() {
    sessionproxy->set_show_desktop_icons_qt(show_switcher->switchedOn);
}

void IconWidget::setComputerIcon() {
    sessionproxy->set_show_computer_qt(computer_switcher->switchedOn);
}

void IconWidget::setFolderIcon() {
    sessionproxy->set_show_homefolder_qt(folder_switcher->switchedOn);
}

void IconWidget::setNetworkIcon() {
    sessionproxy->set_show_network_qt(network_switcher->switchedOn);
}

void IconWidget::setRecycleBinIcon() {
    sessionproxy->set_show_trash_qt(recycle_switcher->switchedOn);
}

void IconWidget::setDiskIcon() {
    sessionproxy->set_show_devices_qt(disk_switcher->switchedOn);
}
