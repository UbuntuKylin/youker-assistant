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

#include "infowidget.h"
#include <QDebug>

InfoWidget::InfoWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setFixedSize(900, 403);
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    this->setPalette(palette);

    splitter = new QSplitter();
    splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    splitter->setOrientation(Qt::Horizontal);
    splitter->setHandleWidth(1);

    category_widget = new QListWidget();
    category_widget->setFixedSize(150, 403);
    category_widget->setFocusPolicy(Qt::NoFocus);
    category_widget->setObjectName("infoList");
    type_list << tr("Computer") << tr("Desktop") << tr("CPU") << tr("Memory") << tr("Motherboard") << tr("HD") << tr("NIC") << tr("VGA") << tr("Audio") << tr("CD-ROM") << tr("Battery") << tr("Device Driver");
    icon_list << "computer"<< "unity" << "cpu"<<"memory"<<"board"<<"harddisk"<<"network"<<"monitor"<<"audio"<<"cdrom"<<"battery"<<"drive";

    category_widget->setIconSize(QSize(16, 16));//设置QListWidget中的单元项的图片大小
    category_widget->setResizeMode(QListView::Adjust);
    category_widget->setViewMode(QListView::ListMode);   //设置QListWidget的显示模式
    category_widget->setMovement(QListView::Static);//设置QListWidget中的单元项不可被拖动
    category_widget->setSpacing(1);//设置QListWidget中的单元项的间距

    stacked_widget = new QStackedWidget(this);//stacked_widget will delete when InfoWidget delete
    stacked_widget->setFocusPolicy(Qt::NoFocus);
    stacked_widget->setAutoFillBackground(true);

    system_widget = NULL;
    desktop_widget = NULL;
    cpu_widget = NULL;
    memory_widget = NULL;
    board_widget = NULL;
    hd_widget = NULL;
    nic_widget = NULL;
    monitor_widget = NULL;
    audio_widget = NULL;
    cdrom_widget = NULL;
    battery_widget = NULL;
    driver_widget = NULL;

    connect(category_widget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(changeInfoPage(QListWidgetItem*)));
}

InfoWidget::~InfoWidget()
{
    if(category_widget != NULL)
    {
        delete category_widget;
        category_widget = NULL;
    }
    if(stacked_widget != NULL)
    {
        delete stacked_widget;
        stacked_widget = NULL;
    }
}

void InfoWidget::initUI()
{
    system_widget = new SystemWidget(this, systemProxy);
    desktop_widget = new DesktopWidget(this, sessionProxy);
    cpu_widget = new CpuWidget(this, systemProxy);
    memory_widget = new MemoryWidget(this, systemProxy);
    board_widget = new BoardWidget(this, systemProxy);
    hd_widget = new HDWidget(this, systemProxy);
    nic_widget = new NicWidget(this, systemProxy);
    monitor_widget = new MonitorWidget(this, systemProxy);
    audio_widget = new AudioWidget(this, systemProxy);

    QMap<QString, QVariant> tmpMap = systemProxy->get_cdrom_info_qt();
    QMap<QString, QVariant>::iterator iter = tmpMap.find("Dvdnum");
    int dvdNum = 0;
    if (iter == tmpMap.end())
    {
        dvdNum = 0;
    }
    else{
        dvdNum = iter.value().toInt();
    }
    if(dvdNum != 0)
    {
        cdrom_widget = new CDRowWidget(this, systemProxy);
    }
    bool power = sessionProxy->judge_power_is_exists_qt();
    if(power)
    {
        battery_widget = new BatteryWidget(this, sessionProxy);
    }
    driver_widget = new DriverWidget(this/*, systemProxy*/);


    for(int i = 0;i < type_list.length();i ++) {
        if(i == 9 && dvdNum == 0){

        }
        else if(i == 10 && !power) {

        }
        else {
            QIcon icon;
            icon.addFile(":/hd/res/hardware/" + icon_list.at(i), QSize(), QIcon::Normal, QIcon::Off);
            QListWidgetItem *item = new QListWidgetItem(type_list.at(i), category_widget);
            item->setSizeHint(QSize(120,31)); //设置单元项的宽度和高度
            item->setStatusTip(icon_list.at(i));
            item->setIcon(icon);
        }
    }
    category_widget->setCurrentRow(0);
    current_tip = category_widget->currentItem()->statusTip();

    stacked_widget->addWidget(system_widget);
    stacked_widget->addWidget(desktop_widget);
    stacked_widget->addWidget(cpu_widget);
    stacked_widget->addWidget(memory_widget);
    stacked_widget->addWidget(board_widget);
    stacked_widget->addWidget(hd_widget);
    stacked_widget->addWidget(nic_widget);
    stacked_widget->addWidget(monitor_widget);
    stacked_widget->addWidget(audio_widget);
    if(dvdNum != 0)
    {
        stacked_widget->addWidget(cdrom_widget);
    }
    if(power)
    {
        stacked_widget->addWidget(battery_widget);
    }
    stacked_widget->addWidget(driver_widget);


//    device_content = new QWidget();
//    QScrollArea scroll_area1;
//    scroll_area1.setWidget(device_content);
//    //设置背景色的方法。
//    scroll_area1.viewport()->setBackgroundRole(QPalette::Light);
//    scroll_area1.viewport()->setAutoFillBackground(true);
//    scroll_area1.show();

//    logo_view = new QWidget();
//    logo_view->setFixedWidth(150);
//    QScrollArea scroll_area2;
//    scroll_area2.setWidget(logo_view);
//    scroll_area2.show();

    QVBoxLayout *center_layout = new QVBoxLayout();
    center_layout->addWidget(stacked_widget);
    center_layout->setSpacing(0);
    center_layout->setMargin(0);
    center_layout->setContentsMargins(0, 0, 0, 0);
    splitter->addWidget(category_widget);
    splitter->addWidget(stacked_widget);

    for(int i = 0; i<splitter->count();i++)
    {
        QSplitterHandle *handle = splitter->handle(i);
        handle->setEnabled(false);
    }

    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addWidget(splitter);
    main_layout->setSpacing(0);
    main_layout->setMargin(0);
    main_layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(main_layout);
}

void InfoWidget::changeInfoPage(QListWidgetItem *item) {
    if (item->statusTip() != this->current_tip) {
        if (item->statusTip() == "computer") {
            stacked_widget->setCurrentWidget(system_widget);
        }
        else if (item->statusTip() == "unity") {
            if(!desktop_widget->getStatus())
                desktop_widget->initData();
            stacked_widget->setCurrentWidget(desktop_widget);
        }
        else if (item->statusTip() == "cpu") {
            if(!cpu_widget->getStatus())
                cpu_widget->initData();
            stacked_widget->setCurrentWidget(cpu_widget);
        }
        else if (item->statusTip() == "memory") {
            if(!memory_widget->getStatus())
                memory_widget->initData();
            stacked_widget->setCurrentWidget(memory_widget);
        }
        else if (item->statusTip() == "board") {
            if(!board_widget->getStatus())
                board_widget->initData();
            stacked_widget->setCurrentWidget(board_widget);
        }
        else if (item->statusTip() == "harddisk") {
            if(!hd_widget->getStatus())
                hd_widget->initData();
            stacked_widget->setCurrentWidget(hd_widget);
        }
        else if (item->statusTip() == "network") {
            if(!nic_widget->getStatus())
                nic_widget->initData();
            stacked_widget->setCurrentWidget(nic_widget);
        }
        else if (item->statusTip() == "monitor") {
            if(!monitor_widget->getStatus())
                monitor_widget->initData();
            stacked_widget->setCurrentWidget(monitor_widget);
        }
        else if (item->statusTip() == "audio") {
            if(!audio_widget->getStatus())
                audio_widget->initData();
            stacked_widget->setCurrentWidget(audio_widget);
        }
        else if (item->statusTip() == "cdrom") {
            if(!cdrom_widget->getStatus())
                cdrom_widget->initData();
            stacked_widget->setCurrentWidget(cdrom_widget);
        }
        else if (item->statusTip() == "battery") {
            if(!battery_widget->getStatus())
                battery_widget->initData();
            stacked_widget->setCurrentWidget(battery_widget);
        }
        else if (item->statusTip() == "drive") {
            stacked_widget->setCurrentWidget(driver_widget);
        }
        this->current_tip =  item->statusTip();
    }
}
