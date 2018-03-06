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
#include "../src/mainwindow.h"
#include "../component/selectcategorywidget.h"
#include "../component/cleangroup.h"

CleanerMainWidget::CleanerMainWidget(QWidget *parent, MainWindow *window, Toolkits *kits, QString skin)
    : QWidget(parent), parentWindow(window), toolKits(kits)
{
    this->setFixedSize(900, 403);
    this->setObjectName("transparentWidget");
//    this->setAutoFillBackground(true);
//    QPalette palette;
//    palette.setBrush(QPalette::Window, QBrush(Qt::white));
//    this->setPalette(palette);

    tip_label = new QLabel(this);
    tip_label->setGeometry(QRect(30, 10, 800, 30));
    tip_label->setObjectName("tipLabel");
//    QStringList cache_list, status_list;
//    cache_list << tr("Cleanup Package Cache") << tr("Cleanup Software Center Cache") << tr("Cleanup Thumbnails Cache") << tr("Cleanup FireFox Cache") << tr("Cleanup Chromium Cache");
//    status_list << "apt" << "software-center" << "thumbnails" << "firefox" << "chromium";
//    cache_items = new CleanerItems(cache_list, status_list, skin, 280, tr("Cache Items"));
//    cache_btn = new KylinCheckBox(0, "://res/cache.png");
    cache_btn = new CleanGroup(this, "://res/cache");
    cache_btn->setFocusPolicy(Qt::NoFocus);
//    cache_btn->setGeometry(QRect(10, 50, 260, 150));
    cache_btn->setGeometry(QRect(10, 150, 260, 150));
//    cache_btn->setFixedSize(260, 130);
    cache_btn->setStatusTip("cache");
    cache_btn->setLabelText(tr("System Cache"), tr("Cleanup  cache of system, software-center, thumbnails and browser"));//系统缓存垃圾    清除包、软件中心、缩略图和浏览器缓存
    //子checkbox的状态被改变时，重新设置总按钮的状态
//    connect(cache_items, SIGNAL(notifyMainCheckBox(int)), cache_btn, SLOT(resetMainStatus(int)));
    //点击按钮后，显示子页面
    connect(cache_btn, SIGNAL(clicked()), this, SLOT(onButtonClicked()));

    //20160711
    /*QStringList package_list;
    package_list << tr("Uninstall unnecessary procedures") << tr("Uninstall old kernel packages") << tr("Cleanup software configfile");
    status_list.clear();
    status_list << "unneed" << "oldkernel" << "configfile";
    package_items = new CleanerItems(package_list, status_list, skin, 200, tr("Package Items"));
//    package_btn = new KylinCheckBox(0, "://res/package.png");
    package_btn = new CleanGroup(this, "://res/package");
    package_btn->setFocusPolicy(Qt::NoFocus);
    package_btn->setGeometry(QRect(320, 50, 260, 150));
//    package_btn->setFixedSize(260, 130);
    package_btn->setLabelText(tr("Packages and configfile"), tr("Cleaning up the software that installed by other software bundled, old kernel packages and configfile, to improve system performance"));//包垃圾   清除不必要的程序、旧内核包、配置文件
    package_btn->setStatusTip("package");
    //子checkbox的状态被改变时，重新设置总按钮的状态
    connect(package_items, SIGNAL(notifyMainCheckBox(int)), package_btn, SLOT(resetMainStatus(int)));
    //点击按钮后，显示子页面
    connect(package_btn, SIGNAL(clicked()), this, SLOT(onButtonClicked()));*/

//    QStringList cookies_list;
//    cookies_list << tr("Cleanup the Cookies saving in Firefox") << tr("Cleanup the Cookies saving in Chromium");
//    status_list.clear();
//    status_list << "firefox" << "chromium";
//    cookies_items = new CleanerItems(cookies_list, status_list, skin, 170, tr("Cookies Items"));
//    cookies_btn = new KylinCheckBox(0, "://res/cookie.png");
    cookies_btn = new CleanGroup(this, "://res/cookie");
    cookies_btn->setFocusPolicy(Qt::NoFocus);
    cookies_btn->setGeometry(QRect(320, 150, 260, 150));
//    cookies_btn->setGeometry(QRect(630, 50, 260, 150));
//    cookies_btn->setFixedSize(260, 130);
    cookies_btn->setLabelText(tr("Cookies"), tr("Clean up user login information, support Firefox and Chromium browser"));//清除上网、游戏、购物等记录
    cookies_btn->setStatusTip("cookies");
    //子checkbox的状态被改变时，重新设置总按钮的状态
//    connect(cookies_items, SIGNAL(notifyMainCheckBox(int)), cookies_btn, SLOT(resetMainStatus(int)));
    //点击按钮后，显示子页面
    connect(cookies_btn, SIGNAL(clicked()), this, SLOT(onButtonClicked()));

//    QStringList trace_list;
//    trace_list << tr("Clean up the Firefox Internet records") << tr("Clean up the Chromium Internet records") << tr("Clean up the recently opened documents records") << tr("Delete the command history") << tr("Delete the debug logs");
//    status_list.clear();
//    status_list << "firefox" << "chromium" << "system" << "bash" << "X11";
//    trace_items = new CleanerItems(trace_list, status_list, skin, 280, tr("Trace Items"));
//    trace_btn = new KylinCheckBox(0, "://res/trace.png");
    trace_btn = new CleanGroup(this, "://res/trace");
    trace_btn->setFocusPolicy(Qt::NoFocus);
//    trace_btn->setGeometry(QRect(10, 240, 260, 150));
    trace_btn->setGeometry(QRect(630, 150, 260, 150));
//    trace_btn->setFixedSize(260, 130);
    trace_btn->setLabelText(tr("History trace"), tr("Cleaning the internet and opened documents recently records"));//使用痕迹    清除浏览器和系统使用痕迹
    trace_btn->setStatusTip("trace");
    //子checkbox的状态被改变时，重新设置总按钮的状态
//    connect(trace_items, SIGNAL(notifyMainCheckBox(int)), trace_btn, SLOT(resetMainStatus(int)));
    //点击按钮后，显示子页面
    connect(trace_btn, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    this->setLanguage();

    cache_list << tr("Cleanup Package Cache") << tr("Cleanup Software Center Cache") << tr("Cleanup Thumbnails Cache") << tr("Cleanup FireFox Cache") << tr("Cleanup Chromium Cache");
    cache_status_list << "apt" << "software-center" << "thumbnails" << "firefox" << "chromium";
    cookies_list << tr("Cleanup the Cookies saving in Firefox") << tr("Cleanup the Cookies saving in Chromium");
    cookies_status_list << "firefox" << "chromium";
    trace_list << tr("Clean up the Firefox Internet records") << tr("Clean up the Chromium Internet records") << tr("Clean up the recently opened documents records") << tr("Delete the command history") << tr("Delete the debug logs");
    trace_status_list << "firefox" << "chromium" << "system" << "bash" << "X11";

    m_selectedCache = cache_status_list;
    m_selectedCookie = cookies_status_list;
    m_selectedTrace = trace_status_list;
}

CleanerMainWidget::~CleanerMainWidget()
{
    argsMap.clear();
//    if(cache_items != NULL) {
//        delete cache_items;
//        cache_items = NULL;
//    }
//    if(package_items != NULL) {
//        delete package_items;
//        package_items = NULL;
//    }
//    if(cookies_items != NULL) {
//        delete cookies_items;
//        cookies_items = NULL;
//    }
//    if(trace_items != NULL) {
//        delete trace_items;
//        trace_items = NULL;
//    }
}

void CleanerMainWidget::setLanguage()
{
    tip_label->setText(tr("Please select the items you want to clean"));
}

void CleanerMainWidget::resetCurrentSkin(QString skin)
{
//    if(cache_items != NULL)
//        cache_items->resetTitleSkin(skin);
//    if(trace_items != NULL)
//        trace_items->resetTitleSkin(skin);
//    if(package_items != NULL)
//        package_items->resetTitleSkin(skin);
//    if(cookies_items != NULL)
//        cookies_items->resetTitleSkin(skin);
}

void CleanerMainWidget::receiveScanSignal()
{
    this->getAllScanSelectedItems();
    if (argsMap.empty()) {
        toolKits->alertMSG(parentWindow->geometry().topLeft().x(), parentWindow->geometry().topLeft().y(), tr("Scan args is empty!"));
    }
    else {
        emit this->showActionAnimaiton();
        emit this->startScanSystem(argsMap);
    }
}

void CleanerMainWidget::getAllScanSelectedItems()
{
    argsMap.clear();

    if (!m_selectedCache.isEmpty())
        argsMap.insert("Cache", m_selectedCache);
    if (!m_selectedCookie.isEmpty())
        argsMap.insert("Cookies", m_selectedCookie);
    if (!m_selectedTrace.isEmpty())
        argsMap.insert("History", m_selectedTrace);


//    QStringList cacheTmp;
////    QStringList packageTmp;
//    QStringList cookieTmp;
//    QStringList historyTmp;

//    if(cache_btn != NULL && cache_btn->getCheckBoxStatus() != 0)
//    {
//        QStringList tmp = cache_items->getSelectedItems();
//        for(int i = 0; i<tmp.length();i++)
//        {
//            cacheTmp.append(tmp.at(i));
//        }
//    }

//    if(package_btn != NULL && package_btn->getCheckBoxStatus() != 0)
//    {
//        QStringList tmp = package_items->getSelectedItems();
//        for(int i = 0; i<tmp.length();i++)
//        {
//            packageTmp.append(tmp.at(i));
//        }
//    }

//    if(cookies_btn != NULL && cookies_btn->getCheckBoxStatus() != 0)
//    {
//        QStringList tmp = cookies_items->getSelectedItems();
//        for(int i = 0; i<tmp.length();i++)
//        {
//            cookieTmp.append(tmp.at(i));
//        }
//    }

//    if(trace_btn != NULL && trace_btn->getCheckBoxStatus() != 0)
//    {
//        QStringList tmp = trace_items->getSelectedItems();
//        for(int i = 0; i<tmp.length();i++)
//        {
//            historyTmp.append(tmp.at(i));
//        }
//    }
//    if(cacheTmp.length() > 0)
//        argsMap.insert("Cache", cacheTmp);
////    if(packageTmp.length() > 0)
////        argsMap.insert("Packages", packageTmp);
//    if(cookieTmp.length() > 0)
//        argsMap.insert("Cookies", cookieTmp);
//    if(historyTmp.length() > 0)
//        argsMap.insert("History", historyTmp);
}

void CleanerMainWidget::onRefreshSelectedItems(CleanerCategoryID id, const QStringList &infos)
{
    qDebug() << "AAAA" << id;
    qDebug() << infos;
    switch (id) {
    case CleanerCategoryID::CacheCategory:
        m_selectedCache.clear();
        m_selectedCache = infos;
        break;
    case CleanerCategoryID::CookieCategory:
        m_selectedCookie.clear();
        m_selectedCookie = infos;
        break;
    case CleanerCategoryID::TraceCategory:
        m_selectedTrace.clear();
        m_selectedTrace = infos;
        break;
    default:
        break;
    }
}

void CleanerMainWidget::resetDefaultStatus()
{
    cache_btn->resetMainStatus(2);
    cookies_btn->resetMainStatus(2);
    trace_btn->resetMainStatus(2);

    m_selectedCache = cache_status_list;
    m_selectedCookie = cookies_status_list;
    m_selectedTrace = trace_status_list;
}

void CleanerMainWidget::onButtonClicked()
{
    QObject *object = QObject::sender();
//    KylinCheckBox *checkbox = qobject_cast<KylinCheckBox *>(object);
    CleanGroup *checkbox = qobject_cast<CleanGroup *>(object);
    QString object_name = checkbox->statusTip();
    if (object_name == "cache") {
//        int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (410  / 2);
//        int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (280 / 2);
//        cache_items->move(w_x, w_y);
//        cache_items->exec();

        m_selectedCache.clear();
        m_selectedCache = cache_status_list;
        SelectCategoryWidget *w = new SelectCategoryWidget(CleanerCategoryID::CacheCategory, tr("Cache Items"));
        w->loadData(cache_list, cache_status_list);
        connect(w, SIGNAL(notifyMainCheckBox(int)), cache_btn, SLOT(resetMainStatus(int)));
        connect(w, SIGNAL(refreshSelectedItems(CleanerCategoryID,QStringList)), this, SLOT(onRefreshSelectedItems(CleanerCategoryID,QStringList)));
        w->exec();
        delete w;
    }
//    if(object_name == "package")
//    {
//        int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (410  / 2);
//        int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (200  / 2);
//        package_items->move(w_x, w_y);
//        package_items->exec();
//    }
    if (object_name == "cookies") {
//        int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (410  / 2);
//        int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (170  / 2);
//        cookies_items->move(w_x, w_y);
//        cookies_items->exec();

        m_selectedCookie.clear();
        m_selectedCookie = cookies_status_list;
        SelectCategoryWidget *w = new SelectCategoryWidget(CleanerCategoryID::CookieCategory, tr("Cookies Items"));
        w->loadData(cookies_list, cookies_status_list);
        connect(w, SIGNAL(notifyMainCheckBox(int)), cookies_btn, SLOT(resetMainStatus(int)));
        connect(w, SIGNAL(refreshSelectedItems(CleanerCategoryID,QStringList)), this, SLOT(onRefreshSelectedItems(CleanerCategoryID,QStringList)));
        w->exec();
        delete w;
    }
    if (object_name == "trace") {
//        m_selectedTrace.clear();
//        m_selectedTrace = status_list;
//        int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (410  / 2);
//        int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (280  / 2);
//        trace_items->move(w_x, w_y);
//        trace_items->exec();

        m_selectedCookie.clear();
        m_selectedCookie = trace_status_list;
        SelectCategoryWidget *w = new SelectCategoryWidget(CleanerCategoryID::TraceCategory, tr("Trace Items"));
        w->loadData(trace_list, trace_status_list);
        connect(w, SIGNAL(notifyMainCheckBox(int)), trace_btn, SLOT(resetMainStatus(int)));
        connect(w, SIGNAL(refreshSelectedItems(CleanerCategoryID,QStringList)), this, SLOT(onRefreshSelectedItems(CleanerCategoryID,QStringList)));
        w->exec();
        delete w;
    } 
}
