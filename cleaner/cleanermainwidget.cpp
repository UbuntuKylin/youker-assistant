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

#include "cleanermainwidget.h"
#include "../component/kylintoolbutton.h"
#include <QDebug>
#include "../mainui/mainwindow.h"

CleanerMainWidget::CleanerMainWidget(QWidget *parent, MainWindow *window)
    : QWidget(parent), parentWindow(window)
{
    this->setFixedSize(900, 403);
    this->setAutoFillBackground(true);
    this->setObjectName("transparentWidget");

    tip_label = new QLabel();
    tip_label->setObjectName("tipLabel");
    QStringList cache_list;
    cache_list << tr("Cleanup Package Cache") << tr("Cleanup Software Center Cache") << tr("Cleanup Thumbnails Cache") << tr("Cleanup FireFox Cache") << tr("Cleanup Chromium Cache");
    cache_items = new CleanerItems(cache_list, 280, tr("Cache Items"));
    cache_btn = new KylinCheckBox(0, "://res/cache.png");
    cache_btn->setFixedSize(260, 130);
    cache_btn->setToolTip("cache");
    cache_btn->setLabelText(tr("System Cache"), tr("Cleanup  cache of system, software-center, thumbnails and browser"));//系统缓存垃圾    清除包、软件中心、缩略图和浏览器缓存
    //子checkbox的状态被改变时，重新设置总按钮的状态
    connect(cache_items, SIGNAL(notifyMainCheckBox(int)), cache_btn, SLOT(resetMainStatus(int)));
    //点击自定义按钮后，根据总按钮的状态去改变子checkbox的状态
    connect(cache_btn, SIGNAL(customButtonClicked()), this, SLOT(onButtonClicked()));
    //点击总按钮后，根据总按钮的状态去改变子checkbox的状态
    connect(cache_btn, SIGNAL(spreadStatus(int)), cache_items, SLOT(resetSubCheckbox(int)));

    QStringList package_list;
    package_list << tr("Uninstall unnecessary procedures") << tr("Uninstall old kernel packages") << tr("Cleanup software configfile");
    package_items = new CleanerItems(package_list, 200, tr("Package Items"));
    package_btn = new KylinCheckBox(0, "://res/package.png");
    package_btn->setFixedSize(260, 130);
    package_btn->setLabelText(tr("Packages and configfile"), tr("Cleaning up the software that installed by other software bundled, old kernel packages and configfile, to improve system performance"));//包垃圾   清除不必要的程序、旧内核包、配置文件
    package_btn->setToolTip("package");
    //子checkbox的状态被改变时，重新设置总按钮的状态
    connect(package_items, SIGNAL(notifyMainCheckBox(int)), package_btn, SLOT(resetMainStatus(int)));
    //点击自定义按钮后，根据总按钮的状态去改变子checkbox的状态
    connect(package_btn, SIGNAL(customButtonClicked()), this, SLOT(onButtonClicked()));
    //点击总按钮后，根据总按钮的状态去改变子checkbox的状态
    connect(package_btn, SIGNAL(spreadStatus(int)), package_items, SLOT(resetSubCheckbox(int)));

    QStringList cookies_list;
    cookies_list << tr("Cleanup the Cookies saving in Firefox") << tr("Cleanup the Cookies saving in Chromium");
    cookies_items = new CleanerItems(cookies_list , 170, tr("Cookies Items"));
    cookies_btn = new KylinCheckBox(0, "://res/cookie.png");
    cookies_btn->setFixedSize(260, 130);
    cookies_btn->setLabelText(tr("Cookies"), tr("Clean up user login information, support Firefox and Chromium browser"));//清除上网、游戏、购物等记录
    cookies_btn->setToolTip("cookies");
    //子checkbox的状态被改变时，重新设置总按钮的状态
    connect(cookies_items, SIGNAL(notifyMainCheckBox(int)), cookies_btn, SLOT(resetMainStatus(int)));
    //点击自定义按钮后，根据总按钮的状态去改变子checkbox的状态
    connect(cookies_btn, SIGNAL(customButtonClicked()), this, SLOT(onButtonClicked()));
    //点击总按钮后，根据总按钮的状态去改变子checkbox的状态
    connect(cookies_btn, SIGNAL(spreadStatus(int)), cookies_items, SLOT(resetSubCheckbox(int)));

//    QStringList browser_list;
//    browser_list << tr("Cleanup Firefox Cache") << tr("Cleanup Chromium Cache");
//    browser_items = new CleanerItems(browser_list);
//    browser_btn = new KylinCheckBox(0, "://res/history-max.png");
//    browser_btn->setToolTip("browser");
//    //子checkbox的状态被改变时，重新设置总按钮的状态
//    connect(browser_items, SIGNAL(notifyMainCheckBox(int)), browser_btn, SLOT(resetMainStatus(int)));
//    //点击自定义按钮后，根据总按钮的状态去改变子checkbox的状态
//    connect(browser_btn, SIGNAL(customButtonClicked()), this, SLOT(onButtonClicked()));
//    //点击总按钮后，根据总按钮的状态去改变子checkbox的状态
//    connect(browser_btn, SIGNAL(spreadStatus(int)), browser_items, SLOT(resetSubCheckbox(int)));

    QStringList trace_list;
    trace_list << tr("Clean up the Firefox Internet records") << tr("Clean up the Chromium Internet records") << tr("Clean up the recently opened documents records");
    trace_items = new CleanerItems(trace_list, 200, tr("Trace Items"));
    trace_btn = new KylinCheckBox(0, "://res/trace.png");
    trace_btn->setFixedSize(260, 130);
    trace_btn->setLabelText(tr("History trace"), tr("Cleaning the internet and opened documents recently records"));//使用痕迹    清除浏览器和系统使用痕迹
    trace_btn->setToolTip("trace");
    //子checkbox的状态被改变时，重新设置总按钮的状态
    connect(trace_items, SIGNAL(notifyMainCheckBox(int)), trace_btn, SLOT(resetMainStatus(int)));
    //点击自定义按钮后，根据总按钮的状态去改变子checkbox的状态
    connect(trace_btn, SIGNAL(customButtonClicked()), this, SLOT(onButtonClicked()));
    //点击总按钮后，根据总按钮的状态去改变子checkbox的状态
    connect(trace_btn, SIGNAL(spreadStatus(int)), trace_items, SLOT(resetSubCheckbox(int)));





//    QHBoxLayout *button_layout = new QHBoxLayout();
//    QSignalMapper *signal_mapper = new QSignalMapper(this);
//    for(int i=0; i<6; i++)
//    {
//        QToolButton *tool_button = new QToolButton();
//        tool_button->setFocusPolicy(Qt::NoFocus);
//        tool_button->setText(text_list.at(i));
//        tool_button->setIcon(QIcon(icon_list.at(i)));
//        tool_button->setIconSize(QPixmap(icon_list.at(i)).size());
//        tool_button->setAutoRaise(true);
////        tool_button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
//        tool_button->setObjectName("commonToolButton");
//        tool_button->setFixedSize(110, 110);
////        tool_button->setContentsMargins(0, 20, 0, 30);

//        button_list.append(tool_button);
//        connect(tool_button, SIGNAL(clicked()), signal_mapper, SLOT(map()));
//        signal_mapper->setMapping(tool_button, QString::number(i, 10));
//        button_layout->addWidget(tool_button, 0, Qt::AlignBottom);
//    }
//    connect(signal_mapper, SIGNAL(mapped(QString)), this, SLOT(switchPageIndex(QString)));

//    main_checkbox = new QCheckBox("main");//三态复选框
//    main_checkbox->setObjectName("mainCheckBox");
//    main_checkbox->setTristate(true);
//    main_checkbox->setEnabled(true);
//    main_checkbox->setCheckState(Qt::Unchecked);
//    connect(main_checkbox, SIGNAL(clicked()), this, SLOT(reset_sub_checkboxes()));

//    checkbox1 = new QCheckBox("checkbox1");
//    checkbox2 = new QCheckBox("checkbox2");
//    checkbox3 = new QCheckBox("checkbox3");


    QHBoxLayout *tip_layout = new QHBoxLayout();
    tip_layout->addWidget(tip_label);
    tip_layout->addStretch();
//    tip_layout->addWidget(main_checkbox);
//    tip_layout->setSpacing(50);
    tip_layout->setMargin(0);
    tip_layout->setContentsMargins(38,20,72,0);

    QHBoxLayout *layout1 = new QHBoxLayout;
    layout1->addWidget(cache_btn);
    layout1->addWidget(package_btn);
    layout1->addWidget(cookies_btn);
    layout1->setMargin(0);
    layout1->setContentsMargins(0,0,0,0);

    QHBoxLayout *layout2 = new QHBoxLayout;
//    layout2->addWidget(browser_btn);
    layout2->addWidget(trace_btn);
    layout2->addStretch();
    layout1->setMargin(0);
    layout2->setContentsMargins(20,0,0,0);

    QVBoxLayout *layoutbox = new QVBoxLayout;
    layoutbox->addLayout(layout1);
    layoutbox->addLayout(layout2);
    layoutbox->setSpacing(20);
    layoutbox->setMargin(0);
    layoutbox->setContentsMargins(0,0,0,0);

    QVBoxLayout *main_layout = new QVBoxLayout;
    main_layout->addLayout(tip_layout);
    main_layout->addLayout(layoutbox);
    main_layout->addStretch();
    main_layout->setSpacing(30);
    main_layout->setMargin(0);
    main_layout->setContentsMargins(0,0,0,0);

    setLayout(main_layout);
    this->setLanguage();

//    main_checkbox = new QCheckBox();
//    main_checkbox->setFocusPolicy(Qt::NoFocus);
//    main_checkbox->setObjectName("mainCheckBox");
//    main_checkbox->setTristate(true);
//    main_checkbox->setEnabled(true);
//    main_checkbox->setCheckState(Qt::Checked);
//    cache_items = NULL;





////    checkbox_list.append(checkbox1);
////    checkbox_list.append(checkbox2);
////    checkbox_list.append(checkbox3);
////    connect(checkbox1, SIGNAL(clicked()), this, SLOT(scan_all_checkbox()));
////    connect(checkbox2, SIGNAL(clicked()), this, SLOT(scan_all_checkbox()));
////    connect(checkbox3, SIGNAL(clicked()), this, SLOT(scan_all_checkbox()));

}

CleanerMainWidget::~CleanerMainWidget()
{

}

void CleanerMainWidget::setLanguage()
{
    tip_label->setText(tr("Please select the items you want to clean"));
//    main_checkbox->setText(tr("All"));
}

void CleanerMainWidget::onButtonClicked()
{
    QObject *object = QObject::sender();
    KylinCheckBox *checkbox = qobject_cast<KylinCheckBox *>(object);
    QString object_name = checkbox->toolTip();
    if(object_name == "cache")
    {
        if(cache_items->isHidden()) {
            int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (410  / 2);
            int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (280 / 2);
            cache_items->move(w_x, w_y);
            cache_items->show();
        }
        else
        {
            cache_items->hide();
        }
        if(!package_items->isHidden()) {
            package_items->hide();
        }
        if(!cookies_items->isHidden()) {
            cookies_items->hide();
        }
        if(!trace_items->isHidden()) {
            trace_items->hide();
        }
    }
    else if(object_name == "package")
    {
        if(package_items->isHidden()) {
            int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (410  / 2);
            int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (200  / 2);
            package_items->move(w_x, w_y);
            package_items->show();
        }
        else
        {
            package_items->hide();
        }
        if(!cache_items->isHidden()) {
            cache_items->hide();
        }
        if(!cookies_items->isHidden()) {
            cookies_items->hide();
        }
        if(!trace_items->isHidden()) {
            trace_items->hide();
        }
    }
    if(object_name == "cookies")
    {
        if(cookies_items->isHidden()) {
            int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (410  / 2);
            int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (170  / 2);
            cookies_items->move(w_x, w_y);
            cookies_items->show();
        }
        else
        {
            cookies_items->hide();
        }
        if(!cache_items->isHidden()) {
            cache_items->hide();
        }
        if(!package_items->isHidden()) {
            package_items->hide();
        }
        if(!trace_items->isHidden()) {
            trace_items->hide();
        }
    }
    if(object_name == "trace")
    {
        if(trace_items->isHidden()) {
            int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (410  / 2);
            int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (200  / 2);
            trace_items->move(w_x, w_y);
            trace_items->show();
        }
        else
        {
            trace_items->hide();
        }
        if(!cache_items->isHidden()) {
            cache_items->hide();
        }
        if(!package_items->isHidden()) {
            package_items->hide();
        }
        if(!cookies_items->isHidden()) {
            cookies_items->hide();
        }
    }
}
