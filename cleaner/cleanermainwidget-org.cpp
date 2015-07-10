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
#include <QDebug>
#include "../mainui/mainwindow.h"
#include "../component/cleangroup.h"

CleanerMainWidget::CleanerMainWidget(QWidget *parent, SessionDispatcher *seroxy, MainWindow *window, Toolkits *kits, QString skin)
    : QWidget(parent), sessionproxy(seroxy), parentWindow(window), toolKits(kits)
{
    this->setFixedSize(900, 403);
    this->setObjectName("transparentWidget");
//    this->setAutoFillBackground(true);
//    QPalette palette;
//    palette.setBrush(QPalette::Window, QBrush(Qt::white));
//    this->setPalette(palette);

    tip_label = new QLabel();
    tip_label->setObjectName("tipLabel");
    QStringList cache_list, status_list;
    cache_list << tr("Cleanup Package Cache") << tr("Cleanup Software Center Cache") << tr("Cleanup Thumbnails Cache") << tr("Cleanup FireFox Cache") << tr("Cleanup Chromium Cache");
    status_list << "apt" << "software-center" << "thumbnails" << "firefox" << "chromium";
    cache_items = new CleanerItems(cache_list, status_list, skin, 280, tr("Cache Items"));
//    cache_btn = new KylinCheckBox(0, "://res/cache.png");
    cache_btn = new CleanGroup(0, "://res/cache");
//    cache_btn->setFixedSize(260, 130);
    cache_btn->setStatusTip("cache");
    cache_btn->setLabelText(tr("System Cache"), tr("Cleanup  cache of system, software-center, thumbnails and browser"));//系统缓存垃圾    清除包、软件中心、缩略图和浏览器缓存
    //子checkbox的状态被改变时，重新设置总按钮的状态
    connect(cache_items, SIGNAL(notifyMainCheckBox(int)), cache_btn, SLOT(resetMainStatus(int)));
    //点击按钮后，显示子页面
    connect(cache_btn, SIGNAL(clicked()), this, SLOT(onButtonClicked()));

    QStringList package_list;
    package_list << tr("Uninstall unnecessary procedures") << tr("Uninstall old kernel packages") << tr("Cleanup software configfile");
    status_list.clear();
    status_list << "unneed" << "oldkernel" << "configfile";
    package_items = new CleanerItems(package_list, status_list, skin, 200, tr("Package Items"));
//    package_btn = new KylinCheckBox(0, "://res/package.png");
    package_btn = new CleanGroup(0, "://res/cache");
//    package_btn->setFixedSize(260, 130);
    package_btn->setLabelText(tr("Packages and configfile"), tr("Cleaning up the software that installed by other software bundled, old kernel packages and configfile, to improve system performance"));//包垃圾   清除不必要的程序、旧内核包、配置文件
    package_btn->setStatusTip("package");
    //子checkbox的状态被改变时，重新设置总按钮的状态
    connect(package_items, SIGNAL(notifyMainCheckBox(int)), package_btn, SLOT(resetMainStatus(int)));
    //点击按钮后，显示子页面
    connect(package_btn, SIGNAL(clicked()), this, SLOT(onButtonClicked()));

    QStringList cookies_list;
    cookies_list << tr("Cleanup the Cookies saving in Firefox") << tr("Cleanup the Cookies saving in Chromium");
    status_list.clear();
    status_list << "firefox" << "chromium";
    cookies_items = new CleanerItems(cookies_list, status_list, skin, 170, tr("Cookies Items"));
//    cookies_btn = new KylinCheckBox(0, "://res/cookie.png");
    cookies_btn = new CleanGroup(0, "://res/cache");
//    cookies_btn->setFixedSize(260, 130);
    cookies_btn->setLabelText(tr("Cookies"), tr("Clean up user login information, support Firefox and Chromium browser"));//清除上网、游戏、购物等记录
    cookies_btn->setStatusTip("cookies");
    //子checkbox的状态被改变时，重新设置总按钮的状态
    connect(cookies_items, SIGNAL(notifyMainCheckBox(int)), cookies_btn, SLOT(resetMainStatus(int)));
    //点击按钮后，显示子页面
    connect(cookies_btn, SIGNAL(clicked()), this, SLOT(onButtonClicked()));

    ////Debug logs调试日志   command history  命令历史记录
    QStringList trace_list;
    trace_list << tr("Clean up the Firefox Internet records") << tr("Clean up the Chromium Internet records") << tr("Clean up the recently opened documents records") << tr("Delete the command history") << tr("Delete the debug logs");
    status_list.clear();
    status_list << "firefox" << "chromium" << "system" << "bash" << "X11";
    trace_items = new CleanerItems(trace_list, status_list, skin, 280, tr("Trace Items"));
//    trace_btn = new KylinCheckBox(0, "://res/trace.png");
    trace_btn = new CleanGroup(0, "://res/cache");
//    trace_btn->setFixedSize(260, 130);
    trace_btn->setLabelText(tr("History trace"), tr("Cleaning the internet and opened documents recently records"));//使用痕迹    清除浏览器和系统使用痕迹
    trace_btn->setStatusTip("trace");
    //子checkbox的状态被改变时，重新设置总按钮的状态
    connect(trace_items, SIGNAL(notifyMainCheckBox(int)), trace_btn, SLOT(resetMainStatus(int)));
    //点击按钮后，显示子页面
    connect(trace_btn, SIGNAL(clicked()), this, SLOT(onButtonClicked()));

//    main_checkbox = new QCheckBox("main");//三态复选框
//    main_checkbox->setObjectName("mainCheckBox");
//    main_checkbox->setTristate(true);
//    main_checkbox->setEnabled(true);
//    main_checkbox->setCheckState(Qt::Unchecked);
//    connect(main_checkbox, SIGNAL(clicked()), this, SLOT(reset_sub_checkboxes()));

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
//    scanWidgets = new QStackedWidget(this);
//    scanWidgets->setGeometry(rect());
//    scanWidgets->lower();
}

CleanerMainWidget::~CleanerMainWidget()
{

}

void CleanerMainWidget::setLanguage()
{
    tip_label->setText(tr("Please select the items you want to clean"));
//    main_checkbox->setText(tr("All"));
}

void CleanerMainWidget::resetCurrentSkin(QString skin)
{
    if(cache_items != NULL)
        cache_items->resetTitleSkin(skin);
    if(trace_items != NULL)
        trace_items->resetTitleSkin(skin);
    if(package_items != NULL)
        package_items->resetTitleSkin(skin);
    if(cookies_items != NULL)
        cookies_items->resetTitleSkin(skin);
}

void CleanerMainWidget::receiveScanSignal()
{
    this->getAllScanSelectedItems();
    if(argsMap.empty())
    {
        toolKits->alertMSG(parentWindow->geometry().topLeft().x(), parentWindow->geometry().topLeft().y(), tr("Scan args is empty!"));
    }
    else
    {
//        qDebug() << "args is.........." << argsMap;
        emit this->showActionAnimaiton();
        sessionproxy->scanSystemCleanerItems(argsMap);
    }
}

void CleanerMainWidget::getAllScanSelectedItems()
{
    argsMap.clear();
    QStringList cacheTmp;
    QStringList packageTmp;
    QStringList cookieTmp;
    QStringList historyTmp;

    if(cache_btn != NULL && cache_btn->getCheckBoxStatus() != 0)
    {
        QStringList tmp = cache_items->getSelectedItems();
        for(int i = 0; i<tmp.length();i++)
        {
            cacheTmp.append(tmp.at(i));
        }
    }

    if(package_btn != NULL && package_btn->getCheckBoxStatus() != 0)
    {
        QStringList tmp = package_items->getSelectedItems();
        for(int i = 0; i<tmp.length();i++)
        {
            packageTmp.append(tmp.at(i));
        }
    }

    if(cookies_btn != NULL && cookies_btn->getCheckBoxStatus() != 0)
    {
        QStringList tmp = cookies_items->getSelectedItems();
        for(int i = 0; i<tmp.length();i++)
        {
            cookieTmp.append(tmp.at(i));
        }
    }

    if(trace_btn != NULL && trace_btn->getCheckBoxStatus() != 0)
    {
        QStringList tmp = trace_items->getSelectedItems();
        for(int i = 0; i<tmp.length();i++)
        {
            historyTmp.append(tmp.at(i));
        }
    }
    if(cacheTmp.length() > 0)
        argsMap.insert("Cache", cacheTmp);
    if(packageTmp.length() > 0)
        argsMap.insert("Packages", packageTmp);
    if(cookieTmp.length() > 0)
        argsMap.insert("Cookies", cookieTmp);
    if(historyTmp.length() > 0)
        argsMap.insert("History", historyTmp);
}

void CleanerMainWidget::onButtonClicked()
{
    QObject *object = QObject::sender();
//    KylinCheckBox *checkbox = qobject_cast<KylinCheckBox *>(object);
    CleanGroup *checkbox = qobject_cast<CleanGroup *>(object);
    QString object_name = checkbox->statusTip();
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
