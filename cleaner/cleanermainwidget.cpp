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
#include <QtSvg/QSvgRenderer>
#include "../src/mainwindow.h"
#include "../component/selectcategorywidget.h"
#include "../component/cleangroup.h"
#include "../component/detailsbutton.h"

CleanerMainWidget::CleanerMainWidget(QWidget *parent, MainWindow *window, Toolkits *kits, QString skin)
    : QWidget(parent), parentWindow(window), toolKits(kits)
{
    this->setFixedSize(900, 403);
    this->setObjectName("transparentWidget");

    tip_label = new QLabel(this);
    tip_label->setGeometry(QRect(120, 60, 800, 30));
    tip_label->setObjectName("tipLabel");
    tip_label->setFixedHeight(45);

//    cache_btn = new CleanGroup(this, "://res/cache");
//    cache_btn->setFocusPolicy(Qt::NoFocus);
//    cache_btn->setGeometry(QRect(30, 150, 260, 150));
//    cache_btn->setStatusTip("cache");
//    cache_btn->setLabelText(tr("System Cache"), tr("Cleans up cache of system"));//系统缓存垃圾    清除包、软件中心、缩略图和浏览器缓存

    QLabel *cache_icon = new QLabel(this);

    QSvgRenderer* svgRender = new QSvgRenderer(QString(":/svg/res/svg/virus.svg"));

    QPixmap *icon = new QPixmap(32,32);
    icon->fill(Qt::transparent);//设置背景透明
    QPainter p(icon);
    svgRender->render(&p);

//    QPixmap icon(":/res/cache.png");
    cache_icon->setPixmap(*icon);
    cache_icon->setGeometry(QRect(125,150,32,32));

    QPushButton *cache_btn = new QPushButton(this);
    cache_btn->setFocusPolicy(Qt::NoFocus);
    cache_btn->setGeometry(QRect(110,194,108,36));
    cache_btn->setText(tr("Cache"));
    cache_btn->setStatusTip("cache");
    cache_btn->setStyleSheet("QPushButton{width:108px;height:36px;background:rgba(64,64,64,30);border-radius:18px;color:black;}\
                              QPushButton:hover{background:rgba(64,64,64,80);}");

    QLabel *cache_label = new QLabel(this);
    cache_label->setText(tr("Clear package、thumbnails and browser cache"));
    cache_label->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    cache_label->setGeometry(QRect(120,240,200,35*3));
    cache_label->setWordWrap(true);
    cache_label->setStyleSheet("color:rgb(0,0,0,165)");

    //点击按钮后，显示子页面
    connect(cache_btn, SIGNAL(clicked()), this, SLOT(onButtonClicked()));


//    cookies_btn = new CleanGroup(this, "://res/cookie");
//    cookies_btn->setFocusPolicy(Qt::NoFocus);
//    cookies_btn->setGeometry(QRect(290, 150, 260, 150));
//    cookies_btn->setLabelText(tr("Cookies"), tr("Cleans up cookies in browser"));
//    cookies_btn->setStatusTip("cookies");

    QSvgRenderer* svgRender1 = new QSvgRenderer(QString(":/svg/res/svg/cookies.svg"));

    QPixmap *icon1 = new QPixmap(32,32);
    icon1->fill(Qt::transparent);//设置背景透明
    QPainter p1(icon1);
    svgRender1->render(&p1);

    QLabel *cookie_icon = new QLabel(this);
//    QPixmap icon1(":/res/cookies.png");
    cookie_icon->setPixmap(*icon1);
    cookie_icon->setGeometry(QRect(352,150,32,32));

    QPushButton *cookie_btn = new QPushButton(this);
    cookie_btn->setFocusPolicy(Qt::NoFocus);
    cookie_btn->setGeometry(QRect(337,194,108,36));
    cookie_btn->setStatusTip("cookies");
    cookie_btn->setText(tr("Cookies"));
    cookie_btn->setStyleSheet("QPushButton{width:108px;height:36px;background:rgba(64,64,64,30);border-radius:18px;color:black;}\
                               QPushButton:hover{background:rgba(64,64,64,80);}");

    QLabel *cookie_label = new QLabel(this);
    cookie_label->setText(tr("Clear internet、games、shopping history, etc."));
    cookie_label->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    cookie_label->setGeometry(QRect(347,240,200,35*3));
    cookie_label->setWordWrap(true);
    cookie_label->setStyleSheet("color:rgb(0,0,0,165)");


    //点击按钮后，显示子页面
    connect(cookie_btn, SIGNAL(clicked()), this, SLOT(onButtonClicked()));

//    trace_btn = new CleanGroup(this, "://res/trace");
//    trace_btn->setFocusPolicy(Qt::NoFocus);
//    trace_btn->setGeometry(QRect(550, 150, 260, 150));
//    trace_btn->setLabelText(tr("History trace"), tr("Cleans up records of history"));
//    trace_btn->setStatusTip("trace");

    QSvgRenderer* svgRender2 = new QSvgRenderer(QString(":/svg/res/svg/history.svg"));

    QPixmap *icon2 = new QPixmap(32,32);
    icon2->fill(Qt::transparent);//设置背景透明
    QPainter p2(icon2);
    svgRender2->render(&p2);

    QLabel *history_icon = new QLabel(this);
//    QPixmap icon2(":/res/history.png");
    history_icon->setPixmap(*icon2);
    history_icon->setGeometry(QRect(584,150,32,32));

    QPushButton *history_btn = new QPushButton(this);
    history_btn->setFocusPolicy(Qt::NoFocus);
    history_btn->setGeometry(QRect(569,194,108,36));
    history_btn->setStatusTip("trace");
    history_btn->setText(tr("Trace"));
    history_btn->setStyleSheet("QPushButton{width:108px;height:36px;background:rgba(64,64,64,30);border-radius:18px;color:black;}\
                                QPushButton:hover{background:rgba(64,64,64,80);}");

    QLabel *history_label = new QLabel(this);
    history_label->setText(tr("Clear browser and system usage traces"));
    history_label->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    history_label->setGeometry(QRect(579,240,200,35*3));
    history_label->setWordWrap(true);
    history_label->setStyleSheet("color:rgb(0,0,0,165)");

    //点击按钮后，显示子页面
    connect(history_btn, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    this->setLanguage();


    start_clean = new QPushButton(this);
    start_clean->setFocusPolicy(Qt::NoFocus);
    start_clean->setFlat(true);
    start_clean->setText(tr("Start Clean"));
    start_clean->setGeometry(QRect(120,340,220,60));
    start_clean->setStyleSheet("QPushButton{background:rgba(34,103,242,1);color:white;border-radius:30px;font-size:24px}\
                                QPushButton:hover{background:rgba(67,127,240,1);color:white}");

    connect(start_clean,SIGNAL(clicked()),this,SLOT(onClickedCleanbtn()));
    connect(start_clean,SIGNAL(clicked()),this,SLOT(receiveScanSignal()));

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
//    tip_label->setText(tr("Please select the items you want to clean"));
    tip_label->setStyleSheet("QLabel{color:rgb(0,0,0,185);font-size:36px;}");
    tip_label->setText(tr("Cleanup makes computers safer."));
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

/**
  *判断当前的系统存在哪些浏览器
  *
  * @param null
  * @return null
**/
void CleanerMainWidget::Browser_to_judge_existence()
{
    QFileInfo fileinfo;
    fileinfo.setFile("/usr/bin/google-chrome-stable");
    if(fileinfo.isFile())
        google = true;
    else
        google = false;

    fileinfo.setFile("/usr/bin/firefox");
    if(fileinfo.isFile())
        firefox = true;
    else
        firefox = false;

    fileinfo.setFile("/usr/bin/browser360-cn-stable");
    if(fileinfo.isFile())
        browser360 = true;
    else
        browser360 = false;
}

void CleanerMainWidget::receiveScanSignal()
{
//    this->getAllScanSelectedItems();
//    if (argsMap.empty()) {
//        toolKits->alertMSG(parentWindow->geometry().topLeft().x(), parentWindow->geometry().topLeft().y(), tr("Scan args is empty!"));
//    }
//    else {
//        emit this->showActionAnimaiton();
//        emit this->startScanSystem(argsMap);
//    }
}

void CleanerMainWidget::getAllScanSelectedItems()
{
    argsMap.clear();

    if (m_selectedCache.length() != m_selectedCache.removeAll("")){
        argsMap.insert("Cache", m_selectedCache);
    }
    if (m_selectedCookie.length() != m_selectedCookie.removeAll("")){
        argsMap.insert("Cookies", m_selectedCookie);
    }
    if (m_selectedTrace.length() != m_selectedTrace.removeAll("")){
        argsMap.insert("History", m_selectedTrace);
    }


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
//    qDebug() << "AAAA" << id;
//    qDebug() << infos;
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
//    cache_btn->resetMainStatus(2);
//    cookies_btn->resetMainStatus(2);
//    trace_btn->resetMainStatus(2);

    m_selectedCache = cache_status_list;
    m_selectedCookie = cookies_status_list;
    m_selectedTrace = trace_status_list;
}

void CleanerMainWidget::onClickedCleanbtn()
{


    this->getAllScanSelectedItems();
    if (argsMap.empty()) {
        toolKits->alertMSG(parentWindow->geometry().topLeft().x(), parentWindow->geometry().topLeft().y(), tr("Scan args is empty!"));
        resetDefaultStatus();
    }
    else {
        qDebug() << Q_FUNC_INFO << "+" << argsMap;
        emit this->hideThisWidget();
        emit this->startScanSystem(argsMap);
    }

//    QStringList args;
//    args << "cache" << "history" << "cookies";
//    emit this->onKeyClean(args);
}

void CleanerMainWidget::onButtonClicked()
{
//    qDebug() << Q_FUNC_INFO ;
    Browser_to_judge_existence();//每次点击都更新浏览器的存在数据

    //对google浏览器存在添加选择字段，如不存在则去除选择字段
    if(google)
    {
        //对字符串做存在判断，避免重读添加字段
        if(!cache_status_list.contains("chromium"))
        {
            cache_list << tr("Cleanup Chromium Cache");
            cache_status_list << "chromium";
        }

        //同上
        if(!cookies_status_list.contains("chromium"))
        {
            cookies_list << tr("Cleanup the Cookies saving in Chromium");
            cookies_status_list << "chromium";
        }

        //同上
        if(!trace_status_list.contains("chromium"))
        {
            trace_list << tr("Clean up the Chromium Internet records");
            trace_status_list << "chromium";
        }
    }
    else
    {
        //对字符串做存在判断,存在则去除字段
        if(cache_status_list.contains("chromium"))
        {
            cache_list.removeOne(tr("Cleanup Chromium Cache"));
            cache_status_list.removeOne("chromium");
        }

        //同上
        if(cookies_status_list.contains("chromium"))
        {
            cookies_list.removeOne(tr("Cleanup the Cookies saving in Chromium"));
            cookies_status_list.removeOne("chromium");
        }

        //同上
        if(trace_status_list.contains("chromium"))
        {
            trace_list.removeOne(tr("Clean up the Chromium Internet records"));
            trace_status_list.removeOne("chromium");
        }
    }

    //对firefox浏览器存在添加选择字段，如不存在则去除选择字段
    if(firefox)
    {
        //对字符串做存在判断，避免重读添加字段
        if(!cache_status_list.contains("firefox"))
        {
            cache_list << tr("Cleanup FireFox Cache");
            cache_status_list << "firefox";
        }

        //同上
        if(!cookies_status_list.contains("firefox"))
        {
            cookies_list << tr("Cleanup the Cookies saving in Firefox");
            cookies_status_list << "firefox";
        }

        //同上
        if(!trace_status_list.contains("firefox"))
        {
            trace_list << tr("Clean up the Firefox Internet records");
            trace_status_list << "firefox";
        }
    }
    else
    {
        //对字符串做存在判断,存在则去除字段
        if(cache_status_list.contains("firefox"))
        {
            cache_list.removeOne(tr("Cleanup FireFox Cache"));
            cache_status_list.removeOne("firefox");
        }

        //同上
        if(cookies_status_list.contains("firefox"))
        {
            cookies_list.removeOne(tr("Cleanup the Cookies saving in Firefox"));
            cookies_status_list.removeOne("firefox");
        }

        //同上
        if(trace_status_list.contains("firefox"))
        {
            trace_list.removeOne(tr("Clean up the Firefox Internet records"));
            trace_status_list.removeOne("firefox");
        }
    }

    QObject *object = QObject::sender();
//    KylinCheckBox *checkbox = qobject_cast<KylinCheckBox *>(object);
//    CleanGroup *checkbox = qobject_cast<CleanGroup *>(object);
    QPushButton *checkbox = qobject_cast<QPushButton *>(object);
    QString object_name = checkbox->statusTip();
    if (object_name == "cache") {
//        int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (410  / 2);
//        int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (280 / 2);
//        cache_items->move(w_x, w_y);
//        cache_items->exec();

        if(flag_cache){
            m_selectedCache.clear();
            m_selectedCache = cache_status_list;
            flag_cache=false;
        }
        SelectCategoryWidget *w = new SelectCategoryWidget(CleanerCategoryID::CacheCategory, tr("Cache Items"));
        w->loadData(cache_list, m_selectedCache,cache_status_list);
//        connect(w, SIGNAL(notifyMainCheckBox(int)), cache_btn, SLOT(resetMainStatus(int)));
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

        if(flag_cookie){
            m_selectedCookie.clear();
            m_selectedCookie = cookies_status_list;
            flag_cookie=false;
        }
        SelectCategoryWidget *w = new SelectCategoryWidget(CleanerCategoryID::CookieCategory, tr("Cookies Items"));
        w->loadData(cookies_list, m_selectedCookie, cookies_status_list);
//        connect(w, SIGNAL(notifyMainCheckBox(int)), cookies_btn, SLOT(resetMainStatus(int)));
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

        if(flag_trace){
            m_selectedTrace.clear();
            m_selectedTrace = trace_status_list;
            flag_trace=false;
        }
        SelectCategoryWidget *w = new SelectCategoryWidget(CleanerCategoryID::TraceCategory, tr("Trace Items"));
        w->loadData(trace_list, m_selectedTrace, trace_status_list);
//        connect(w, SIGNAL(notifyMainCheckBox(int)), trace_btn, SLOT(resetMainStatus(int)));
        connect(w, SIGNAL(refreshSelectedItems(CleanerCategoryID,QStringList)), this, SLOT(onRefreshSelectedItems(CleanerCategoryID,QStringList)));
        w->exec();
        delete w;
    } 
}
