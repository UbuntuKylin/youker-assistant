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

#include "cleanerdetailwidget.h"
#include "../src/mainwindow.h"
#include "../component/cleansubgroup.h"
#include "../component/selectwidget.h"
#include <QDebug>
#include <QBoxLayout>

const int defaultColumn = 4;//5 items for one line

CleanerDetailWidget::CleanerDetailWidget(QWidget *parent, MainWindow *window, Toolkits *kits, QString skin)
    : QWidget(parent), parentWindow(window), toolKits(kits),cur_skin(skin)
{
//    this->setStyleSheet("QWidget{border: none}");
    this->setFixedSize(900, 403);
    this->setObjectName("transparentWidget");
    this->setWindowIcon(QIcon(":/res/kylin-assistant.png"));

    mainLayout = new QVBoxLayout(this);
    m_emptyLabel = new QLabel(this);
    m_emptyLabel->setText(tr("No garbage"));
    m_emptyLabel->setVisible(false);

    /*this->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    this->setPalette(palette);*/
//    this->setObjectName("transparentWidget");
//    this->setAutoFillBackground(true);
//    QPalette palette;
//    palette.setBrush(QPalette::Window, QBrush(Qt::white));
//    this->setPalette(palette);

//    this->number_per_row = -1;
//    this->itemwidth = 160;
//    this->itemheight = 110;
//    this->cardspace = 10;
//    subCount = 0;
    scanResult = false;

    m_row = 0;
    m_column = 0;

    m_scrollArea = new QScrollArea(this);
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setStyleSheet("QScrollArea{border: none;background-color: #ffffff;}");
    areaWidget = new QWidget(/*this*/);
    areaWidget->setObjectName("transparentWidget");
    m_scrollArea->setWidget(areaWidget);
    areaWidgetLayout = new QGridLayout(areaWidget);
    areaWidgetLayout->setAlignment(Qt::AlignTop);

    mainLayout->addWidget(m_emptyLabel);//QStackedLayout
    mainLayout->addWidget(m_scrollArea);

    /*ui->scrollAreaWidgetContents->setGeometry(0, 0, this->width(), this->height());
    ui->scrollArea->setFixedSize(900, 403);
    ui->scrollArea->setAutoFillBackground(true);
    ui->scrollArea->setBackgroundRole(QPalette::Light);
    ui->label->hide();*/

//    grid_layout = new QGridLayout();
//    rowIndex = columnIndex = 0;

//    cache_apt_items = NULL;
//    cache_apt_btn = NULL;
////    cache_software_items = NULL;
//    cache_software_btn = NULL;
////    cache_thumbnails_items = NULL;
//    cache_thumbnails_btn = NULL;
////    cache_firefox_items = NULL;
//    cache_firefox_btn = NULL;
////    cache_chromium_items = NULL;
//    cache_chromium_btn = NULL;

//    package_unneed_items = NULL;
//    package_unneed_btn = NULL;
//    package_oldkernel_items = NULL;
//    package_oldkernel_btn = NULL;
//    package_configfile_items = NULL;
//    package_configfile_btn = NULL;

//    cookies_firefox_items = NULL;
//    cookies_firefox_btn = NULL;
////    cookies_chromium_items = NULL;
//    cookies_chromium_btn = NULL;

//    trace_firefox_btn = NULL;
//    trace_chromium_btn = NULL;
//    trace_system_btn = NULL;
//    trace_bash_btn = NULL;
//    trace_x11_btn = NULL;
//    trace_x11_items = NULL;

//    ui->scrollAreaWidgetContents->setLayout(grid_layout);
//    this->number_per_row = (this->width() + this->cardspace - 60) / (this->itemwidth + this->cardspace);
    this->setLanguage();


    /*
    //test for adding a title
    QLabel *titleLabel = new QLabel(tr("List"));
    areaWidgetLayout->addWidget(titleLabel, m_row, m_column, 1, 4);
    m_row ++;
    */

    /*
    //test for another module append to this page
    m_column = 0;
    m_row ++;
    */
}

CleanerDetailWidget::~CleanerDetailWidget()
{
    this->CleanUIAndData();
//    if(cache_apt_items != NULL)
//    {
//        delete cache_apt_items;
//        cache_apt_items = NULL;
//    }
//    if(cache_software_items != NULL)
//    {
//        delete cache_software_items;
//        cache_software_items = NULL;
//    }
//    if(cache_thumbnails_items != NULL)
//    {
//        delete cache_thumbnails_items;
//        cache_thumbnails_items = NULL;
//    }
//    if(cache_firefox_items != NULL)
//    {
//        delete cache_firefox_items;
//        cache_firefox_items = NULL;
//    }
//    if(cache_chromium_items != NULL)
//    {
//        delete cache_chromium_items;
//        cache_chromium_items = NULL;
//    }
    /*if(package_unneed_items != NULL)
    {
        delete package_unneed_items;
        package_unneed_items = NULL;
    }
    if(package_oldkernel_items != NULL)
    {
        delete package_oldkernel_items;
        package_oldkernel_items = NULL;
    }
    if(package_configfile_items != NULL)
    {
        delete package_configfile_items;
        package_configfile_items = NULL;
    }*/
//    if(cookies_firefox_items != NULL)
//    {
//        delete cookies_firefox_items;
//        cookies_firefox_items = NULL;
//    }
//    if(cookies_chromium_items != NULL)
//    {
//        delete cookies_chromium_items;
//        cookies_chromium_items = NULL;
//    }
//    if(trace_x11_items != NULL)
//    {
//        delete trace_x11_items;
//        trace_x11_items = NULL;
//    }
//    if(grid_layout != NULL)
//    {
//        delete grid_layout;
//        grid_layout = NULL;
//    }
//    delete ui;
}

void CleanerDetailWidget::onRefreshSelectedItems(CleanerModuleID id, const QStringList &infos)
{
    switch (id) {
    case CleanerModuleID::CacheApt:
        m_selectedAptList.clear();
        m_selectedAptList = infos;
        break;
    case CleanerModuleID::CacheSoftware:
        m_selectedSoftwareList.clear();
        m_selectedSoftwareList = infos;
        break;
    case CleanerModuleID::CacheThumbnail:
        m_selectedThumbnailsList.clear();
        m_selectedThumbnailsList = infos;
        break;
    case CleanerModuleID::CacheFirefox:
        m_selectedFirefoxCacheList.clear();
        m_selectedFirefoxCacheList = infos;
        break;
    case CleanerModuleID::CacheChromium:
        m_selectedChromiumCacheList.clear();
        m_selectedChromiumCacheList = infos;
        break;
    case CleanerModuleID::CookieFirefox:
        m_selectedFirefoxCookieList.clear();
        m_selectedFirefoxCookieList = infos;
        break;
    case CleanerModuleID::CookieChromium:
        m_selectedChromiumCookieList.clear();
        m_selectedChromiumCookieList = infos;
        break;
    case CleanerModuleID::TraceX11:
        m_selectedTraceX11List.clear();
        m_selectedTraceX11List = infos;
        break;
    default:
        break;
    }
}

void CleanerDetailWidget::CleanUIAndData()
{
    this->m_emptyLabel->setVisible(false);
//    if(!ui->label->isHidden())
//        ui->label->hide();
    scanResult = false;
//    subCount = 0;
//    rowIndex = columnIndex = 0;
    cache_apt_list.clear();
    cache_software_list.clear();
    cache_thumbnails_list.clear();
    cache_firefox_list.clear();
    cache_chromium_list.clear();
    /*package_unneed_list.clear();
    package_oldkernel_list.clear();
    package_configfile_list.clear();*/
    cookies_firefox_list.clear();
    cookies_chromium_list.clear();
    trace_firefox_count.clear();
    trace_chromium_count.clear();
    trace_system_count.clear();
    trace_bash_size.clear();
    trace_bash_path.clear();
    trace_x11_list.clear();

    m_selectedAptList.clear();
    m_selectedSoftwareList.clear();
    m_selectedThumbnailsList.clear();
    m_selectedFirefoxCacheList.clear();
    m_selectedChromiumCacheList.clear();
    m_selectedFirefoxCookieList.clear();
    m_selectedChromiumCookieList.clear();
    m_selectedTraceX11List.clear();

    //clear ui
//    foreach (QObject *child, ui->scrollAreaWidgetContents->children()) {
//        QWidget *widget = static_cast<QWidget *>(child);
//        widget->deleteLater();
//    }
    /*for(int i=0; i<m_cardlist.count(); i++)
    {
        CleanSubGroup *card = m_cardlist.at(i);
        delete card;
        card = NULL;
    }
    m_cardlist.clear();*/


    this->clearItems();

//    ui->scrollAreaWidgetContents->setGeometry(0, 0, this->width(), this->height());
//    this->subCount = 0;
//    while(grid_layout != NULL && grid_layout->count() > 0)
//    {
//        QWidget* widget = grid_layout->itemAt(0)->widget();
//        grid_layout->removeWidget(widget);
//        delete widget;
//    }
}

void CleanerDetailWidget::addItem(CleanSubGroup *item)
{
    this->m_cardlist.append(item);
    areaWidgetLayout->addWidget(item, m_row, m_column, 1, 1);
    if(m_column == defaultColumn) {
        m_column = 0;
        m_row++;
    }
    else {
        m_column++;
    }
}

void CleanerDetailWidget::showReciveData(const QStringList &data)
{
    //----------------------------------------------------------------Cache---------------------------
    if(data.at(0) == "Belong:Cache.apt" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":"))
        {
            if (scanResult == false)
                scanResult = true;
            cache_apt_list.append(data.at(1).split(":").at(1));
        }
    }
    else if(data.at(0) == "Belong:Cache.software-center" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":"))
        {
            if (scanResult == false)
                scanResult = true;
            cache_software_list.append(data.at(1).split(":").at(1));
        }
    }
    else if(data.at(0) == "Belong:Cache.thumbnails" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":"))
        {
            if (scanResult == false)
                scanResult = true;
            cache_thumbnails_list.append(data.at(1).split(":").at(1));
        }
    }
    else if(data.at(0) == "Belong:Cache.firefox" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":"))
        {
            if (scanResult == false)
                scanResult = true;
            cache_firefox_list.append(data.at(1).split(":").at(1));
        }
    }
    else if(data.at(0) == "Belong:Cache.chromium" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":"))
        {
            if (scanResult == false)
                scanResult = true;
            cache_chromium_list.append(data.at(1).split(":").at(1));
        }
    }
    //----------------------------------------------------------------Package---------------------------
    /*else if(data.at(0) == "Belong:Packages.unneed" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":"))
        {
            if (scanResult == false)
                scanResult = true;
            package_unneed_list.append(data.at(1).split(":").at(1));
        }
    }
    else if(data.at(0) == "Belong:Packages.oldkernel" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":"))
        {
            if (scanResult == false)
                scanResult = true;
            package_oldkernel_list.append(data.at(1).split(":").at(1));
        }
    }
    else if(data.at(0) == "Belong:Packages.configfile" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":"))
        {
            if (scanResult == false)
                scanResult = true;
            package_configfile_list.append(data.at(1).split(":").at(1));
        }
    }*/

    //----------------------------------------------------------------Cookies---------------------------
    else if(data.at(0) == "Belong:Cookies.firefox" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":") && !data.at(1).split(":").at(1).isEmpty())
        {
            if (scanResult == false)
                scanResult = true;
            cookies_firefox_list.append(data.at(1).split(":").at(1));
        }
    }
    else if(data.at(0) == "Belong:Cookies.chromium" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":") && !data.at(1).split(":").at(1).isEmpty())
        {
            if (scanResult == false)
                scanResult = true;
            cookies_chromium_list.append(data.at(1).split(":").at(1));
        }
    }

    //----------------------------------------------------------------History Trace---------------------------
    else if(data.at(0) == "Belong:History.firefox" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":"))
        {
            if(data.at(1).split(":").at(1).toInt() != 0) {
                if (scanResult == false)
                    scanResult = true;
                trace_firefox_count = data.at(1).split(":").at(1);
            }
        }
    }
    else if(data.at(0) == "Belong:History.chromium" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":"))
        {
            if(data.at(1).split(":").at(1).toInt() != 0) {
                if (scanResult == false)
                    scanResult = true;
                trace_chromium_count = data.at(1).split(":").at(1);
            }
        }
    }
    else if(data.at(0) == "Belong:History.system" && !data.at(1).isEmpty())
    {
        if(data.at(1).contains(":"))
        {
            if(data.at(1).split(":").at(1).toInt() != 0) {
                if (scanResult == false)
                    scanResult = true;
                trace_system_count = data.at(1).split(":").at(1);
            }
        }
    }
    else if(data.at(0) == "Belong:History.bash" && !data.at(1).isEmpty() && !data.at(2).isEmpty())
    {
        if(data.at(1).contains(":"))
        {
            if (scanResult == false)
                scanResult = true;
            trace_bash_size= data.at(1).split(":").at(1);
            trace_bash_path= data.at(2).split(":").at(1);
        }
//        qDebug() << "bash------------";
//        qDebug() << data.at(1);//"Size:55.67 KB"
//        qDebug() << data.at(2);/"Path:/home/kobe/.bash_history"
    }
    else if(data.at(0) == "Belong:History.X11")// && !data.at(1).isEmpty() && !data.at(2).isEmpty()
    {
//        qDebug() << "x11------------";
//        qDebug() << data.at(1);//Path:/home/kobe/.xsession-errors
//        qDebug() << data.at(2);//Type:file
//        qDebug() << data.at(3);//Size:0.98 KB
        if(data.at(1).contains(":"))
        {
            if (scanResult == false)
                scanResult = true;
            trace_x11_list.append(data.at(1).split(":").at(1));
        }
    }
}

void CleanerDetailWidget::showReciveStatus(const QString &status)
{
    if(status == "Complete:Cache") {
        if(cache_apt_list.length() > 0) {
            m_selectedAptList.clear();
            m_selectedAptList = cache_apt_list;

//            cache_apt_btn = new CommonCheckBox(0, "://res/cache");
            CleanSubGroup *cache_apt_btn = new CleanSubGroup(this, "://res/janitor/apt");
            cache_apt_btn->setFocusPolicy(Qt::NoFocus);
//            cache_apt_btn->setFixedSize(160, 130);
//            cache_apt_btn->setFixedSize(160, 200);
            cache_apt_btn->setStatusTip("cache-apt");
            cache_apt_btn->setLabelText(tr("Apt Cache count:"), cache_apt_list.length());
            //点击自定义按钮后，显示自定义页面
            connect(cache_apt_btn, SIGNAL(customButtonClicked()), this, SLOT(showCustomPage()));
            this->addItem(cache_apt_btn);

            /*cache_apt_items = new CleanListWidget(cache_apt_list, this->cur_skin, tr("Apt Cache Clean Items"));
            //子checkbox的状态被改变时，重新设置总按钮的状态
            connect(cache_apt_items, SIGNAL(notifyMainCheckBox(int)), cache_apt_btn, SLOT(resetMainStatus(int)));
            //点击总按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(cache_apt_btn, SIGNAL(spreadStatus(int)), cache_apt_items, SLOT(resetSubCheckbox(int)));*/
//            if(grid_layout == NULL)
//            {
//                grid_layout = new QGridLayout();
//            }
//            grid_layout->addWidget(cache_apt_btn, subCount/5, subCount%5);
            /*int x = int(this->subCount % this->number_per_row) * (this->itemwidth + this->cardspace) + 30;
            int y = int(this->subCount / this->number_per_row) * (this->itemheight + this->cardspace) + 30;
            int nowHeight = y + this->itemheight;
            if(nowHeight >= ui->scrollAreaWidgetContents->height())
                ui->scrollAreaWidgetContents->resize(ui->scrollAreaWidgetContents->width(), nowHeight);
            cache_apt_btn->move(x, y);
            cache_apt_btn->show();*/




//            m_cardlist.append(cache_apt_btn);
//            subCount += 1;


//            if(columnIndex < 5)
//            {
//                grid_layout->addWidget(cache_apt_btn, rowIndex, columnIndex);
//                columnIndex += 1;
//            }
//            else {
//                rowIndex += 1;
//                columnIndex = 0;
//                grid_layout->addWidget(cache_apt_btn, rowIndex, columnIndex);
//                columnIndex += 1;
//            }
        }
        if(cache_software_list.length() > 0) {
            m_selectedSoftwareList.clear();
            m_selectedSoftwareList = cache_software_list;

//            cache_software_btn = new CommonCheckBox(0, "://res/cache");
            CleanSubGroup *cache_software_btn = new CleanSubGroup(this, "://res/janitor/software");
            cache_software_btn->setFocusPolicy(Qt::NoFocus);
//            cache_software_btn->setFixedSize(160, 130);
//            cache_software_btn->setFixedSize(160, 200);
            cache_software_btn->setStatusTip("cache-software");
            cache_software_btn->setLabelText(tr("Software Cache count:"), cache_software_list.length());
            //点击自定义按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(cache_software_btn, SIGNAL(customButtonClicked()), this, SLOT(showCustomPage()));
            this->addItem(cache_software_btn);
            /*cache_software_items = new CleanListWidget(cache_software_list, this->cur_skin, tr("Software Cache Clean Items"));
            //子checkbox的状态被改变时，重新设置总按钮的状态
            connect(cache_software_items, SIGNAL(notifyMainCheckBox(int)), cache_software_btn, SLOT(resetMainStatus(int)));
            //点击总按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(cache_software_btn, SIGNAL(spreadStatus(int)), cache_software_items, SLOT(resetSubCheckbox(int)));*/

            /*int x = int(this->subCount % this->number_per_row) * (this->itemwidth + this->cardspace) + 30;
            int y = int(this->subCount / this->number_per_row) * (this->itemheight + this->cardspace) + 30;
            int nowHeight = y + this->itemheight;
            if(nowHeight >= ui->scrollAreaWidgetContents->height())
                ui->scrollAreaWidgetContents->resize(ui->scrollAreaWidgetContents->width(), nowHeight);
            cache_software_btn->move(x, y);
            cache_software_btn->show();*/



//            m_cardlist.append(cache_software_btn);
//            subCount += 1;

            //            if(grid_layout == NULL)
//            {
//                grid_layout = new QGridLayout();
//            }
//            grid_layout->addWidget(cache_software_btn, subCount/5, subCount%5);
//             subCount += 1;
//            if(columnIndex < 5)
//            {
//                grid_layout->addWidget(cache_software_btn, rowIndex, columnIndex);
//                columnIndex += 1;
//            }
//            else {
//                rowIndex += 1;
//                columnIndex = 0;
//                grid_layout->addWidget(cache_software_btn, rowIndex, columnIndex);
//                columnIndex += 1;
//            }
        }
        if (cache_thumbnails_list.length() > 0) {
            m_selectedThumbnailsList.clear();
            m_selectedThumbnailsList = cache_thumbnails_list;

//            cache_thumbnails_btn = new CommonCheckBox(0, "://res/cache");
            CleanSubGroup *cache_thumbnails_btn = new CleanSubGroup(this, "://res/janitor/thumbnails");
            cache_thumbnails_btn->setFocusPolicy(Qt::NoFocus);
//            cache_thumbnails_btn->setFixedSize(160, 130);
//            cache_thumbnails_btn->setFixedSize(160, 200);
            cache_thumbnails_btn->setStatusTip("cache-thumbnails");
            cache_thumbnails_btn->setLabelText(tr("Thumbnails Cache Count:"), cache_thumbnails_list.length());
            //点击自定义按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(cache_thumbnails_btn, SIGNAL(customButtonClicked()), this, SLOT(showCustomPage()));
            this->addItem(cache_thumbnails_btn);
            /*cache_thumbnails_items = new CleanListWidget(cache_thumbnails_list, this->cur_skin,  tr("Thumbnails Cache Clean Items"));
            //子checkbox的状态被改变时，重新设置总按钮的状态
            connect(cache_thumbnails_items, SIGNAL(notifyMainCheckBox(int)), cache_thumbnails_btn, SLOT(resetMainStatus(int)));
            //点击总按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(cache_thumbnails_btn, SIGNAL(spreadStatus(int)), cache_thumbnails_items, SLOT(resetSubCheckbox(int)));*/

            /*int x = int(this->subCount % this->number_per_row) * (this->itemwidth + this->cardspace) + 30;
            int y = int(this->subCount / this->number_per_row) * (this->itemheight + this->cardspace) + 30;
            int nowHeight = y + this->itemheight;
            if(nowHeight >= ui->scrollAreaWidgetContents->height())
                ui->scrollAreaWidgetContents->resize(ui->scrollAreaWidgetContents->width(), nowHeight);
            cache_thumbnails_btn->move(x, y);
            cache_thumbnails_btn->show();*/


//            m_cardlist.append(cache_thumbnails_btn);
//            subCount += 1;

            //            if(grid_layout == NULL)
//            {
//                grid_layout = new QGridLayout();
//            }
//            grid_layout->addWidget(cache_thumbnails_btn, subCount/5, subCount%5);
//            subCount += 1;
//            if(columnIndex < 5)
//            {
//                grid_layout->addWidget(cache_thumbnails_btn, rowIndex, columnIndex);
//                columnIndex += 1;
//            }
//            else {
//                rowIndex += 1;
//                columnIndex = 0;
//                grid_layout->addWidget(cache_thumbnails_btn, rowIndex, columnIndex);
//                columnIndex += 1;
//            }
        }


        if(cache_firefox_list.length() > 0) {
            m_selectedFirefoxCacheList.clear();
            m_selectedFirefoxCacheList = cache_firefox_list;

//            cache_firefox_btn = new CommonCheckBox(0, "://res/cache");
            CleanSubGroup *cache_firefox_btn = new CleanSubGroup(this, "://res/janitor/firefox");
            cache_firefox_btn->setFocusPolicy(Qt::NoFocus);
//            cache_firefox_btn->setFixedSize(160, 130);
            cache_firefox_btn->setStatusTip("cache-firefox");
            cache_firefox_btn->setLabelText(tr("Firefox Cache Count:"), cache_firefox_list.length());
            //点击自定义按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(cache_firefox_btn, SIGNAL(customButtonClicked()), this, SLOT(showCustomPage()));
            this->addItem(cache_firefox_btn);

            /*cache_firefox_items = new CleanListWidget(cache_firefox_list, this->cur_skin,  tr("Firefox Cache Clean Items"));
            //子checkbox的状态被改变时，重新设置总按钮的状态
            connect(cache_firefox_items, SIGNAL(notifyMainCheckBox(int)), cache_firefox_btn, SLOT(resetMainStatus(int)));
            //点击总按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(cache_firefox_btn, SIGNAL(spreadStatus(int)), cache_firefox_items, SLOT(resetSubCheckbox(int)));*/

            /*int x = int(this->subCount % this->number_per_row) * (this->itemwidth + this->cardspace) + 30;
            int y = int(this->subCount / this->number_per_row) * (this->itemheight + this->cardspace) + 30;
            int nowHeight = y + this->itemheight;
            if(nowHeight >= ui->scrollAreaWidgetContents->height())
                ui->scrollAreaWidgetContents->resize(ui->scrollAreaWidgetContents->width(), nowHeight);
            cache_firefox_btn->move(x, y);
            cache_firefox_btn->show();*/


//            m_cardlist.append(cache_firefox_btn);
//            subCount += 1;
            //            if(grid_layout == NULL)
//            {
//                grid_layout = new QGridLayout();
//            }
//            grid_layout->addWidget(cache_firefox_btn, subCount/5, subCount%5);
//            subCount += 1;
//            if(columnIndex < 5)
//            {
//                grid_layout->addWidget(cache_firefox_btn, rowIndex, columnIndex);
//                columnIndex += 1;
//            }
//            else {
//                rowIndex += 1;
//                columnIndex = 0;
//                grid_layout->addWidget(cache_firefox_btn, rowIndex, columnIndex);
//                columnIndex += 1;
//            }
        }
        if(cache_chromium_list.length() > 0) {
            m_selectedChromiumCacheList.clear();
            m_selectedChromiumCacheList = cache_chromium_list;

//            cache_chromium_btn = new CommonCheckBox(0, "://res/cache");
            CleanSubGroup *cache_chromium_btn = new CleanSubGroup(this, "://res/janitor/chromium");
            cache_chromium_btn->setFocusPolicy(Qt::NoFocus);
//            cache_chromium_btn->setFixedSize(160, 130);
            cache_chromium_btn->setStatusTip("cache-chromium");
            cache_chromium_btn->setLabelText(tr("Chromium Cache Count:"), cache_chromium_list.length());
            //点击自定义按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(cache_chromium_btn, SIGNAL(customButtonClicked()), this, SLOT(showCustomPage()));
            this->addItem(cache_chromium_btn);

            /*cache_chromium_items = new CleanListWidget(cache_chromium_list, this->cur_skin, tr("Thumbnails Cache Clean Items"));
            //子checkbox的状态被改变时，重新设置总按钮的状态
            connect(cache_chromium_items, SIGNAL(notifyMainCheckBox(int)), cache_chromium_btn, SLOT(resetMainStatus(int)));
            //点击总按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(cache_chromium_btn, SIGNAL(spreadStatus(int)), cache_chromium_items, SLOT(resetSubCheckbox(int)));*/

            /*int x = int(this->subCount % this->number_per_row) * (this->itemwidth + this->cardspace) + 30;
            int y = int(this->subCount / this->number_per_row) * (this->itemheight + this->cardspace) + 30;
            int nowHeight = y + this->itemheight;
            if(nowHeight >= ui->scrollAreaWidgetContents->height())
                ui->scrollAreaWidgetContents->resize(ui->scrollAreaWidgetContents->width(), nowHeight);
            cache_chromium_btn->move(x, y);
            cache_chromium_btn->show();*/



//            m_cardlist.append(cache_chromium_btn);
//            subCount += 1;
//            if(grid_layout == NULL)
//            {
//                grid_layout = new QGridLayout();
//            }
//            grid_layout->addWidget(cache_chromium_btn, subCount/5, subCount%5);
//            subCount += 1;
//            if(columnIndex < 5)
//            {
//                grid_layout->addWidget(cache_chromium_btn, rowIndex, columnIndex);
//                columnIndex += 1;
//            }
//            else {
//                rowIndex += 1;
//                columnIndex = 0;
//                grid_layout->addWidget(cache_chromium_btn, rowIndex, columnIndex);
//                columnIndex += 1;
//            }
        }
    }
    else if(status == "Complete:Cookies") {
//        doing_label->setText(tr("Cookies Scan OK......"));
        if(cookies_firefox_list.length() > 0) {
            m_selectedFirefoxCookieList.clear();
            m_selectedFirefoxCookieList = cookies_firefox_list;

//            cookies_firefox_btn = new CommonCheckBox(0, "://res/cookie");
            CleanSubGroup *cookies_firefox_btn = new CleanSubGroup(this, "://res/janitor/firefox");
            cookies_firefox_btn->setFocusPolicy(Qt::NoFocus);
//            cookies_firefox_btn->setFixedSize(160, 130);
            cookies_firefox_btn->setStatusTip("cookes-firefox");
            cookies_firefox_btn->setLabelText(tr("Firefox Cookies Count:"), cookies_firefox_list.length());
            //点击自定义按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(cookies_firefox_btn, SIGNAL(customButtonClicked()), this, SLOT(showCustomPage()));
            this->addItem(cookies_firefox_btn);
            /*cookies_firefox_items = new CleanListWidget(cookies_firefox_list, this->cur_skin, tr("Firefox Cookies Clean Items"));
            //子checkbox的状态被改变时，重新设置总按钮的状态
            connect(cookies_firefox_items, SIGNAL(notifyMainCheckBox(int)), cookies_firefox_btn, SLOT(resetMainStatus(int)));
            //点击总按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(cookies_firefox_btn, SIGNAL(spreadStatus(int)), cookies_firefox_items, SLOT(resetSubCheckbox(int)));*/


            /*int x = int(this->subCount % this->number_per_row) * (this->itemwidth + this->cardspace) + 30;
            int y = int(this->subCount / this->number_per_row) * (this->itemheight + this->cardspace) + 30;
            int nowHeight = y + this->itemheight;
            if(nowHeight >= ui->scrollAreaWidgetContents->height())
                ui->scrollAreaWidgetContents->resize(ui->scrollAreaWidgetContents->width(), nowHeight);
            cookies_firefox_btn->move(x, y);
            cookies_firefox_btn->show();*/



//            m_cardlist.append(cookies_firefox_btn);
//            subCount += 1;
//            if(grid_layout == NULL)
//            {
//                grid_layout = new QGridLayout();
//            }
//            grid_layout->addWidget(cookies_firefox_btn, subCount/5, subCount%5);
//            subCount += 1;
//            if(columnIndex < 5)
//            {
//                grid_layout->addWidget(cookies_firefox_btn, rowIndex, columnIndex);
//                columnIndex += 1;
//            }
//            else {
//                rowIndex += 1;
//                columnIndex = 0;
//                grid_layout->addWidget(cookies_firefox_btn, rowIndex, columnIndex);
//                columnIndex += 1;
//            }
        }
        if(cookies_chromium_list.length() > 0) {
            m_selectedChromiumCookieList.clear();
            m_selectedChromiumCookieList = cookies_chromium_list;

//            cookies_chromium_btn = new CommonCheckBox(0, "://res/cache");
            CleanSubGroup *cookies_chromium_btn = new CleanSubGroup(this, "://res/janitor/chromium");
            cookies_chromium_btn->setFocusPolicy(Qt::NoFocus);
//            cookies_chromium_btn->setFixedSize(160, 130);
            cookies_chromium_btn->setStatusTip("cookes-chromium");
            cookies_chromium_btn->setLabelText(tr("Chromium Cookies Count:"), cookies_chromium_list.length());
            //点击自定义按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(cookies_chromium_btn, SIGNAL(customButtonClicked()), this, SLOT(showCustomPage()));
            this->addItem(cookies_chromium_btn);
            /*cookies_chromium_items = new CleanListWidget(cookies_chromium_list, this->cur_skin, tr("Chromium Cookies Clean Items"));
            //子checkbox的状态被改变时，重新设置总按钮的状态
            connect(cookies_chromium_items, SIGNAL(notifyMainCheckBox(int)), cookies_chromium_btn, SLOT(resetMainStatus(int)));
            //点击总按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(cookies_chromium_btn, SIGNAL(spreadStatus(int)), cookies_chromium_items, SLOT(resetSubCheckbox(int)));*/

            /*int x = int(this->subCount % this->number_per_row) * (this->itemwidth + this->cardspace) + 30;
            int y = int(this->subCount / this->number_per_row) * (this->itemheight + this->cardspace) + 30;
            int nowHeight = y + this->itemheight;
            if(nowHeight >= ui->scrollAreaWidgetContents->height())
                ui->scrollAreaWidgetContents->resize(ui->scrollAreaWidgetContents->width(), nowHeight);
            cookies_chromium_btn->move(x, y);
            cookies_chromium_btn->show();*/


//            m_cardlist.append(cookies_chromium_btn);
//            subCount += 1;
//            if(grid_layout == NULL)
//            {
//                grid_layout = new QGridLayout();
//            }
//            grid_layout->addWidget(cookies_chromium_btn, subCount/5, subCount%5);
//            subCount += 1;
//            if(columnIndex < 5)
//            {
//                grid_layout->addWidget(cookies_chromium_btn, rowIndex, columnIndex);
//                columnIndex += 1;
//            }
//            else {
//                rowIndex += 1;
//                columnIndex = 0;
//                grid_layout->addWidget(cookies_chromium_btn, rowIndex, columnIndex);
//                columnIndex += 1;
//            }
        }
    }
    else if(status == "Complete:History") {
//        doing_label->setText(tr("History Scan OK"));
        if(trace_firefox_count.length() > 0) {
//            trace_firefox_btn = new CommonCheckBox(0, "://res/cache");
            CleanSubGroup *trace_firefox_btn = new CleanSubGroup(this, "://res/janitor/firefox");
            trace_firefox_btn->setFocusPolicy(Qt::NoFocus);
//            trace_firefox_btn->setFixedSize(160, 130);
            trace_firefox_btn->hideCustomButton();
            trace_firefox_btn->setStatusTip("history-firefox");
            trace_firefox_btn->setLabelText(tr("Firefox History Count:"), trace_firefox_count.toInt());
            this->addItem(trace_firefox_btn);
            /*int x = int(this->subCount % this->number_per_row) * (this->itemwidth + this->cardspace) + 30;
            int y = int(this->subCount / this->number_per_row) * (this->itemheight + this->cardspace) + 30;
            int nowHeight = y + this->itemheight;
            if(nowHeight >= ui->scrollAreaWidgetContents->height())
                ui->scrollAreaWidgetContents->resize(ui->scrollAreaWidgetContents->width(), nowHeight);
            trace_firefox_btn->move(x, y);
            trace_firefox_btn->show();*/


//            m_cardlist.append(trace_firefox_btn);
//            subCount += 1;
//            if(grid_layout == NULL)
//            {
//                grid_layout = new QGridLayout();
//            }
//            grid_layout->addWidget(trace_firefox_btn, subCount/5, subCount%5);
//            subCount += 1;
//            if(columnIndex < 5)
//            {
//                grid_layout->addWidget(trace_firefox_btn, rowIndex, columnIndex);
//                columnIndex += 1;
//            }
//            else {
//                rowIndex += 1;
//                columnIndex = 0;
//                grid_layout->addWidget(trace_firefox_btn, rowIndex, columnIndex);
//                columnIndex += 1;
//            }
        }
        if(trace_chromium_count.length() > 0) {
            CleanSubGroup *trace_chromium_btn = new CleanSubGroup(this, "://res/janitor/chromium");
            trace_chromium_btn->setFocusPolicy(Qt::NoFocus);
            trace_chromium_btn->hideCustomButton();
            trace_chromium_btn->setStatusTip("history-chromium");
            trace_chromium_btn->setLabelText(tr("Chromium History Count:"), trace_chromium_count.toInt());
            this->addItem(trace_chromium_btn);
            /*int x = int(this->subCount % this->number_per_row) * (this->itemwidth + this->cardspace) + 30;
            int y = int(this->subCount / this->number_per_row) * (this->itemheight + this->cardspace) + 30;
            int nowHeight = y + this->itemheight;
            if(nowHeight >= ui->scrollAreaWidgetContents->height())
                ui->scrollAreaWidgetContents->resize(ui->scrollAreaWidgetContents->width(), nowHeight);
            trace_chromium_btn->move(x, y);
            trace_chromium_btn->show();*/


//            m_cardlist.append(trace_chromium_btn);
//            subCount += 1;
//            if(grid_layout == NULL)
//            {
//                grid_layout = new QGridLayout();
//            }
//            grid_layout->addWidget(trace_chromium_btn, subCount/5, subCount%5);
//            subCount += 1;
//            if(columnIndex < 5)
//            {
//                grid_layout->addWidget(trace_chromium_btn, rowIndex, columnIndex);
//                columnIndex += 1;
//            }
//            else {
//                rowIndex += 1;
//                columnIndex = 0;
//                grid_layout->addWidget(trace_chromium_btn, rowIndex, columnIndex);
//                columnIndex += 1;
//            }
        }

        if(trace_system_count.length() > 0) {
            CleanSubGroup *trace_system_btn = new CleanSubGroup(this, "://res/janitor/trace");
            trace_system_btn->setFocusPolicy(Qt::NoFocus);
            trace_system_btn->hideCustomButton();
            trace_system_btn->setStatusTip("history-system");
            trace_system_btn->setLabelText(tr("System History Count:"), trace_system_count.toInt());
            this->addItem(trace_system_btn);

            /*int x = int(this->subCount % this->number_per_row) * (this->itemwidth + this->cardspace) + 30;
            int y = int(this->subCount / this->number_per_row) * (this->itemheight + this->cardspace) + 30;
            int nowHeight = y + this->itemheight;
            if(nowHeight >= ui->scrollAreaWidgetContents->height())
                ui->scrollAreaWidgetContents->resize(ui->scrollAreaWidgetContents->width(), nowHeight);
            trace_system_btn->move(x, y);
            trace_system_btn->show();*/



//            m_cardlist.append(trace_system_btn);
//            subCount += 1;
//            if(grid_layout == NULL)
//            {
//                grid_layout = new QGridLayout();
//            }
//            grid_layout->addWidget(trace_system_btn, subCount/5, subCount%5);
//            subCount += 1;
//            if(columnIndex < 5)
//            {
//                grid_layout->addWidget(trace_system_btn, rowIndex, columnIndex);
//                columnIndex += 1;
//            }
//            else {
//                rowIndex += 1;
//                columnIndex = 0;
//                grid_layout->addWidget(trace_system_btn, rowIndex, columnIndex);
//                columnIndex += 1;
//            }
        }
        //kobe
        if(!trace_bash_path.isEmpty()) {
            CleanSubGroup *trace_bash_btn = new CleanSubGroup(this, "://res/janitor/trace");
            trace_bash_btn->setFocusPolicy(Qt::NoFocus);
            trace_bash_btn->hideCustomButton();
            trace_bash_btn->setStatusTip("history-bash");
            trace_bash_btn->setLabelStringText(tr("Command history size:"), trace_bash_size);
            this->addItem(trace_bash_btn);

            /*int x = int(this->subCount % this->number_per_row) * (this->itemwidth + this->cardspace) + 30;
            int y = int(this->subCount / this->number_per_row) * (this->itemheight + this->cardspace) + 30;
            int nowHeight = y + this->itemheight;
            if(nowHeight >= ui->scrollAreaWidgetContents->height())
                ui->scrollAreaWidgetContents->resize(ui->scrollAreaWidgetContents->width(), nowHeight);
            trace_bash_btn->move(x, y);
            trace_bash_btn->show();*/


//            m_cardlist.append(trace_bash_btn);
//            subCount += 1;
//            if(grid_layout == NULL)
//            {
//                grid_layout = new QGridLayout();
//            }
//            grid_layout->addWidget(trace_bash_btn, subCount/5, subCount%5);
//            subCount += 1;
//            if(columnIndex < 5)
//            {
//                grid_layout->addWidget(trace_bash_btn, rowIndex, columnIndex);
//                columnIndex += 1;
//            }
//            else {
//                rowIndex += 1;
//                columnIndex = 0;
//                grid_layout->addWidget(trace_bash_btn, rowIndex, columnIndex);
//                columnIndex += 1;
//            }
        }

        if(trace_x11_list.length() > 0) {
            m_selectedTraceX11List.clear();
            m_selectedTraceX11List = trace_x11_list;

            CleanSubGroup *trace_x11_btn = new CleanSubGroup(this, "://res/janitor/debug");
            trace_x11_btn->setFocusPolicy(Qt::NoFocus);
            trace_x11_btn->setStatusTip("x11-history");
            trace_x11_btn->setLabelText(tr("Debug log:"), trace_x11_list.length());
            //点击自定义按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(trace_x11_btn, SIGNAL(customButtonClicked()), this, SLOT(showCustomPage()));
            this->addItem(trace_x11_btn);
            /*trace_x11_items = new CleanListWidget(trace_x11_list, this->cur_skin, tr("Debug log Items"));
            //子checkbox的状态被改变时，重新设置总按钮的状态
            connect(trace_x11_items, SIGNAL(notifyMainCheckBox(int)), trace_x11_btn, SLOT(resetMainStatus(int)));
            //点击总按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(trace_x11_btn, SIGNAL(spreadStatus(int)), trace_x11_items, SLOT(resetSubCheckbox(int)));*/

            /*int x = int(this->subCount % this->number_per_row) * (this->itemwidth + this->cardspace) + 30;
            int y = int(this->subCount / this->number_per_row) * (this->itemheight + this->cardspace) + 30;
            int nowHeight = y + this->itemheight;
            if(nowHeight >= ui->scrollAreaWidgetContents->height())
                ui->scrollAreaWidgetContents->resize(ui->scrollAreaWidgetContents->width(), nowHeight);
            trace_x11_btn->move(x, y);
            trace_x11_btn->show();*/


//            m_cardlist.append(trace_x11_btn);
//            subCount += 1;
//            if(grid_layout == NULL)
//            {
//                grid_layout = new QGridLayout();
//            }
//            grid_layout->addWidget(trace_x11_btn, subCount/5, subCount%5);
//            subCount += 1;
//            if(columnIndex < 5)
//            {
//                grid_layout->addWidget(trace_x11_btn, rowIndex, columnIndex);
//                columnIndex += 1;
//            }
//            else {
//                rowIndex += 1;
//                columnIndex = 0;
//                grid_layout->addWidget(trace_x11_btn, rowIndex, columnIndex);
//                columnIndex += 1;
//            }
        }
    }
    /*else if(status == "Complete:Packages")
    {
//        doing_label->setText(tr("Packages Scan OK"));
        if(package_unneed_list.length() > 0)
        {
            package_unneed_items = new CleanListWidget(package_unneed_list, this->cur_skin, tr("Thumbnails Cache Clean Items"));
//            package_unneed_btn = new CommonCheckBox(0, "://res/cache");
            package_unneed_btn = new CleanSubGroup(this, "://res/janitor/package");
            package_unneed_btn->setFocusPolicy(Qt::NoFocus);
//            package_unneed_btn->setFixedSize(160, 130);
            package_unneed_btn->setStatusTip("package-unneed");
            package_unneed_btn->setLabelText(tr("Package Unneed Count:"),package_unneed_list.length());
            //子checkbox的状态被改变时，重新设置总按钮的状态
            connect(package_unneed_items, SIGNAL(notifyMainCheckBox(int)), package_unneed_btn, SLOT(resetMainStatus(int)));
            //点击自定义按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(package_unneed_btn, SIGNAL(customButtonClicked()), this, SLOT(showCustomPage()));
            //点击总按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(package_unneed_btn, SIGNAL(spreadStatus(int)), package_unneed_items, SLOT(resetSubCheckbox(int)));

            int x = int(this->subCount % this->number_per_row) * (this->itemwidth + this->cardspace) + 30;
            int y = int(this->subCount / this->number_per_row) * (this->itemheight + this->cardspace) + 30;
            int nowHeight = y + this->itemheight;
            if(nowHeight >= ui->scrollAreaWidgetContents->height())
                ui->scrollAreaWidgetContents->resize(ui->scrollAreaWidgetContents->width(), nowHeight);
            package_unneed_btn->move(x, y);
            package_unneed_btn->show();
            m_cardlist.append(package_unneed_btn);
            subCount += 1;
//            if(grid_layout == NULL)
//            {
//                grid_layout = new QGridLayout();
//            }
//            grid_layout->addWidget(package_unneed_btn, subCount/5, subCount%5);
//            subCount += 1;
//            if(columnIndex < 5)
//            {
//                grid_layout->addWidget(package_unneed_btn, rowIndex, columnIndex);
//                columnIndex += 1;
//            }
//            else {
//                rowIndex += 1;
//                columnIndex = 0;
//                grid_layout->addWidget(package_unneed_btn, rowIndex, columnIndex);
//                columnIndex += 1;
//            }
        }
        if(package_oldkernel_list.length() > 0)
        {
            package_oldkernel_items = new CleanListWidget(package_oldkernel_list, this->cur_skin, tr("Thumbnails Cache Clean Items"));
//            package_oldkernel_btn = new CommonCheckBox(0, "://res/cache");
            package_oldkernel_btn = new CleanSubGroup(this, "://res/janitor/package");
            package_oldkernel_btn->setFocusPolicy(Qt::NoFocus);
//            package_oldkernel_btn->setFixedSize(160, 130);
            package_oldkernel_btn->setStatusTip("package-oldkernel");
            package_oldkernel_btn->setLabelText(tr("Package oldkernel Count:"), package_oldkernel_list.length());
            //子checkbox的状态被改变时，重新设置总按钮的状态
            connect(package_oldkernel_items, SIGNAL(notifyMainCheckBox(int)), package_oldkernel_btn, SLOT(resetMainStatus(int)));
            //点击自定义按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(package_oldkernel_btn, SIGNAL(customButtonClicked()), this, SLOT(showCustomPage()));
            //点击总按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(package_oldkernel_btn, SIGNAL(spreadStatus(int)), package_oldkernel_items, SLOT(resetSubCheckbox(int)));

            int x = int(this->subCount % this->number_per_row) * (this->itemwidth + this->cardspace) + 30;
            int y = int(this->subCount / this->number_per_row) * (this->itemheight + this->cardspace) + 30;
            int nowHeight = y + this->itemheight;
            if(nowHeight >= ui->scrollAreaWidgetContents->height())
                ui->scrollAreaWidgetContents->resize(ui->scrollAreaWidgetContents->width(), nowHeight);
            package_oldkernel_btn->move(x, y);
            package_oldkernel_btn->show();
            m_cardlist.append(package_oldkernel_btn);
            subCount += 1;
//            if(grid_layout == NULL)
//            {
//                grid_layout = new QGridLayout();
//            }
//            grid_layout->addWidget(package_oldkernel_btn, subCount/5, subCount%5);
//            subCount += 1;
//            if(columnIndex < 5)
//            {
//                grid_layout->addWidget(package_oldkernel_btn, rowIndex, columnIndex);
//                columnIndex += 1;
//            }
//            else {
//                rowIndex += 1;
//                columnIndex = 0;
//                grid_layout->addWidget(package_oldkernel_btn, rowIndex, columnIndex);
//                columnIndex += 1;
//            }
        }
        if(package_configfile_list.length() > 0)
        {
            package_configfile_items = new CleanListWidget(package_configfile_list, this->cur_skin, tr("Thumbnails Cache Clean Items"));
//            package_configfile_btn = new CommonCheckBox(0, "://res/cache");
            package_configfile_btn = new CleanSubGroup(this, "://res/janitor/package");
            package_configfile_btn->setFocusPolicy(Qt::NoFocus);
//            package_configfile_btn->setFixedSize(160, 130);
            package_configfile_btn->setStatusTip("package-configfile");
            package_configfile_btn->setLabelText(tr("Package configfile Count:"),package_configfile_list.length());
            //子checkbox的状态被改变时，重新设置总按钮的状态
            connect(package_configfile_items, SIGNAL(notifyMainCheckBox(int)), package_configfile_btn, SLOT(resetMainStatus(int)));
            //点击自定义按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(package_configfile_btn, SIGNAL(customButtonClicked()), this, SLOT(showCustomPage()));
            //点击总按钮后，根据总按钮的状态去改变子checkbox的状态
            connect(package_configfile_btn, SIGNAL(spreadStatus(int)), package_configfile_items, SLOT(resetSubCheckbox(int)));

            int x = int(this->subCount % this->number_per_row) * (this->itemwidth + this->cardspace) + 30;
            int y = int(this->subCount / this->number_per_row) * (this->itemheight + this->cardspace) + 30;
            int nowHeight = y + this->itemheight;
            if(nowHeight >= ui->scrollAreaWidgetContents->height())
                ui->scrollAreaWidgetContents->resize(ui->scrollAreaWidgetContents->width(), nowHeight);
            package_configfile_btn->move(x, y);
            package_configfile_btn->show();
            m_cardlist.append(package_configfile_btn);
            subCount += 1;
//            if(grid_layout == NULL)
//            {
//                grid_layout = new QGridLayout();
//            }
//            grid_layout->addWidget(package_configfile_btn, subCount/5, subCount%5);
//            subCount += 1;
//            if(columnIndex < 5)
//            {
//                grid_layout->addWidget(package_configfile_btn, rowIndex, columnIndex);
//                columnIndex += 1;
//            }
//            else {
//                rowIndex += 1;
//                columnIndex = 0;
//                grid_layout->addWidget(package_configfile_btn, rowIndex, columnIndex);
//                columnIndex += 1;
//            }
        }
    }*/
    else if(status == "Complete:All") {
        if(!scanResult) {
            this->m_emptyLabel->setVisible(true);
//            ui->label->show();
        }
        emit this->sendScanOverStatus(scanResult);
    }
}



void CleanerDetailWidget::showCustomPage()
{
    QObject *object = QObject::sender();
//    CommonCheckBox *checkbox = qobject_cast<CommonCheckBox *>(object);
    CleanSubGroup *checkbox = qobject_cast<CleanSubGroup *>(object);
    QString object_name = checkbox->statusTip();
    if(object_name == "cache-apt") {
        /*int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (410  / 2);
        int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (280 / 2);
        cache_apt_items->move(w_x, w_y);
        cache_apt_items->exec();*/

        SelectWidget *w = new SelectWidget(CleanerModuleID::CacheApt, tr("Apt Cache Clean Items"));
        w->loadData(tr("Apt Cache Clean Items"), cache_apt_list);
        //子checkbox的状态被改变时，重新设置总按钮的状态
//        connect(w, SIGNAL(notifyMainCheckBox(int)), cache_apt_btn, SLOT(resetMainStatus(int)));
        connect(w, &SelectWidget::notifyMainCheckBox, [=] (int status) {
            foreach (CleanSubGroup *item, m_cardlist) {
                if (item->statusTip() == "cache-apt") {
                    item->resetMainStatus(status);
                    break;
                }
            }
        });

        connect(w, SIGNAL(refreshSelectedItems(CleanerModuleID,QStringList)), this, SLOT(onRefreshSelectedItems(CleanerModuleID,QStringList)));
        w->exec();
        delete w;
    }
    else if(object_name == "cache-software") {
        /*int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (410  / 2);
        int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (280 / 2);
        cache_software_items->move(w_x, w_y);
        cache_software_items->exec();*/

        SelectWidget *w = new SelectWidget(CleanerModuleID::CacheSoftware, tr("Software Cache Clean Items"));
        w->loadData(tr("Software Cache Clean Items"), cache_software_list);
        //子checkbox的状态被改变时，重新设置总按钮的状态
//        connect(w, SIGNAL(notifyMainCheckBox(int)), cache_software_btn, SLOT(resetMainStatus(int)));
        connect(w, &SelectWidget::notifyMainCheckBox, [=] (int status) {
            foreach (CleanSubGroup *item, m_cardlist) {
                if (item->statusTip() == "cache-software") {
                    item->resetMainStatus(status);
                    break;
                }
            }
        });
        connect(w, SIGNAL(refreshSelectedItems(CleanerModuleID,QStringList)), this, SLOT(onRefreshSelectedItems(CleanerModuleID,QStringList)));
        w->exec();
        delete w;
    }
    else if(object_name == "cache-thumbnails") {
        /*int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (410  / 2);
        int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (280 / 2);
        cache_thumbnails_items->move(w_x, w_y);
        cache_thumbnails_items->exec();*/

        SelectWidget *w = new SelectWidget(CleanerModuleID::CacheThumbnail, tr("Thumbnails Cache Clean Items"));
        w->loadData(tr("Thumbnails Cache Clean Items"), cache_thumbnails_list);
        //子checkbox的状态被改变时，重新设置总按钮的状态
//        connect(w, SIGNAL(notifyMainCheckBox(int)), cache_thumbnails_btn, SLOT(resetMainStatus(int)));
        connect(w, &SelectWidget::notifyMainCheckBox, [=] (int status) {
            foreach (CleanSubGroup *item, m_cardlist) {
                if (item->statusTip() == "cache-thumbnails") {
                    item->resetMainStatus(status);
                    break;
                }
            }
        });
        connect(w, SIGNAL(refreshSelectedItems(CleanerModuleID,QStringList)), this, SLOT(onRefreshSelectedItems(CleanerModuleID,QStringList)));
        w->exec();
        delete w;
    }
    else if(object_name == "cache-firefox") {
        /*int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (410  / 2);
        int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (280 / 2);
        cache_firefox_items->move(w_x, w_y);
        cache_firefox_items->exec();*/
        SelectWidget *w = new SelectWidget(CleanerModuleID::CacheFirefox, tr("Firefox Cache Clean Items"));
        w->loadData(tr("Firefox Cache Clean Items"), cache_firefox_list);
        //子checkbox的状态被改变时，重新设置总按钮的状态
//        connect(w, SIGNAL(notifyMainCheckBox(int)), cache_firefox_btn, SLOT(resetMainStatus(int)));
        connect(w, &SelectWidget::notifyMainCheckBox, [=] (int status) {
            foreach (CleanSubGroup *item, m_cardlist) {
                if (item->statusTip() == "cache-firefox") {
                    item->resetMainStatus(status);
                    break;
                }
            }
        });
        connect(w, SIGNAL(refreshSelectedItems(CleanerModuleID,QStringList)), this, SLOT(onRefreshSelectedItems(CleanerModuleID,QStringList)));
        w->exec();
        delete w;
    }
    else if(object_name == "cache-chromium") {
        /*int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (410  / 2);
        int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (280 / 2);
        cache_chromium_items->move(w_x, w_y);
        cache_chromium_items->exec();*/
        SelectWidget *w = new SelectWidget(CleanerModuleID::CacheChromium, tr("Chromium Cache Clean Items"));
        w->loadData(tr("Chromium Cache Clean Items"), cache_chromium_list);
        //子checkbox的状态被改变时，重新设置总按钮的状态
//        connect(w, SIGNAL(notifyMainCheckBox(int)), cache_chromium_btn, SLOT(resetMainStatus(int)));
        connect(w, &SelectWidget::notifyMainCheckBox, [=] (int status) {
            foreach (CleanSubGroup *item, m_cardlist) {
                if (item->statusTip() == "cache-chromium") {
                    item->resetMainStatus(status);
                    break;
                }
            }
        });
        connect(w, SIGNAL(refreshSelectedItems(CleanerModuleID,QStringList)), this, SLOT(onRefreshSelectedItems(CleanerModuleID,QStringList)));
        w->exec();
        delete w;
    }
    else if(object_name == "cookes-firefox") {
        /*int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (410  / 2);
        int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (280 / 2);
        cookies_firefox_items->move(w_x, w_y);
        cookies_firefox_items->exec();*/
        SelectWidget *w = new SelectWidget(CleanerModuleID::CookieFirefox, tr("Firefox Cookies Clean Items"));
        w->loadData(tr("Firefox Cookies Clean Items"), cookies_firefox_list);
        //子checkbox的状态被改变时，重新设置总按钮的状态
//        connect(w, SIGNAL(notifyMainCheckBox(int)), cookies_firefox_btn, SLOT(resetMainStatus(int)));
        connect(w, &SelectWidget::notifyMainCheckBox, [=] (int status) {
            foreach (CleanSubGroup *item, m_cardlist) {
                if (item->statusTip() == "cookes-firefox") {
                    item->resetMainStatus(status);
                    break;
                }
            }
        });
        connect(w, SIGNAL(refreshSelectedItems(CleanerModuleID,QStringList)), this, SLOT(onRefreshSelectedItems(CleanerModuleID,QStringList)));
        w->exec();
        delete w;
    }
    else if(object_name == "cookes-chromium") {
        /*int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (410  / 2);
        int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (280 / 2);
        cookies_chromium_items->move(w_x, w_y);
        cookies_chromium_items->exec();*/

        SelectWidget *w = new SelectWidget(CleanerModuleID::CookieChromium, tr("Chromium Cookies Clean Items"));
        w->loadData(tr("Chromium Cookies Clean Items"), cookies_chromium_list);
        //子checkbox的状态被改变时，重新设置总按钮的状态
//        connect(w, SIGNAL(notifyMainCheckBox(int)), cookies_chromium_btn, SLOT(resetMainStatus(int)));
        connect(w, &SelectWidget::notifyMainCheckBox, [=] (int status) {
            foreach (CleanSubGroup *item, m_cardlist) {
                if (item->statusTip() == "cookes-chromium") {
                    item->resetMainStatus(status);
                    break;
                }
            }
        });
        connect(w, SIGNAL(refreshSelectedItems(CleanerModuleID,QStringList)), this, SLOT(onRefreshSelectedItems(CleanerModuleID,QStringList)));
        w->exec();
        delete w;
    }
    /*else if(object_name == "package-unneed")
    {
        int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (410  / 2);
        int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (280 / 2);
        package_unneed_items->move(w_x, w_y);
        package_unneed_items->exec();
    }
    else if(object_name == "package-oldkernel")
    {
        int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (410  / 2);
        int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (280 / 2);
        package_oldkernel_items->move(w_x, w_y);
        package_oldkernel_items->exec();
    }
    else if(object_name == "package-configfile")
    {
        int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (410  / 2);
        int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (280 / 2);
        package_configfile_items->move(w_x, w_y);
        package_configfile_items->exec();
    }*/
    else if(object_name == "x11-history") {
        /*int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (410  / 2);
        int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (280 / 2);
        trace_x11_items->move(w_x, w_y);
        trace_x11_items->exec();*/

        SelectWidget *w = new SelectWidget(CleanerModuleID::TraceX11, tr("Debug log Items"));
        w->loadData(tr("Debug log Items"), trace_x11_list);
        //子checkbox的状态被改变时，重新设置总按钮的状态
//        connect(w, SIGNAL(notifyMainCheckBox(int)), trace_x11_btn, SLOT(resetMainStatus(int)));
        connect(w, &SelectWidget::notifyMainCheckBox, [=] (int status) {
            foreach (CleanSubGroup *item, m_cardlist) {
                if (item->statusTip() == "x11-history") {
                    item->resetMainStatus(status);
                    break;
                }
            }
        });
        connect(w, SIGNAL(refreshSelectedItems(CleanerModuleID,QStringList)), this, SLOT(onRefreshSelectedItems(CleanerModuleID,QStringList)));
        w->exec();
        delete w;
    }
//    else if(object_name == "history-firefox" || object_name == "history-chromium" || object_name == "history-system"|| object_name == "history-bash" ) {
//    }
}

void CleanerDetailWidget::setLanguage()
{
//    ui->label->setText(tr("No garbage "));
//    title_label->setText(tr("Cleaning up the system cache"));
//    description_label->setText(tr("Deep cleaning up the system cache, to save disk space"));
}

void CleanerDetailWidget::resetCurrentSkin(QString skin)
{
    this->cur_skin = skin;

    //can remove this code
//    if(cache_apt_items != NULL)
//        cache_apt_items->resetTitleSkin(skin);
//    if(cache_software_items != NULL)
//        cache_software_items->resetTitleSkin(skin);
//    if(cache_thumbnails_items != NULL)
//        cache_thumbnails_items->resetTitleSkin(skin);
//    if(cache_firefox_items != NULL)
//        cache_firefox_items->resetTitleSkin(skin);
//    if(cache_chromium_items != NULL)
//        cache_chromium_items->resetTitleSkin(skin);
//    if(cookies_firefox_items != NULL)
//        cookies_firefox_items->resetTitleSkin(skin);
//    if(cookies_chromium_items != NULL)
//        cookies_chromium_items->resetTitleSkin(skin);
    /*if(package_unneed_items != NULL)
        package_unneed_items->resetTitleSkin(skin);
    if(package_oldkernel_items != NULL)
        package_oldkernel_items->resetTitleSkin(skin);
    if(package_configfile_items != NULL)
        package_configfile_items->resetTitleSkin(skin);*/
//    if(trace_x11_items != NULL)
//        trace_x11_items->resetTitleSkin(skin);
}

void CleanerDetailWidget::receiveCleanSignal()
{
    this->getAllSelectedItems();
    if(argsData.empty()) {
        toolKits->alertMSG(parentWindow->geometry().topLeft().x(), parentWindow->geometry().topLeft().y(), tr("Clean args is empty!"));
    }
    else {
        emit this->startCleanSystem(argsData);
    }
}

void CleanerDetailWidget::clearItems()
{
    while(areaWidgetLayout->count() > 0) {
        QWidget* widget = areaWidgetLayout->itemAt(0)->widget();
        areaWidgetLayout->removeWidget(widget);
        delete widget;
    }
    this->m_cardlist.clear();
    m_row = 0;
    m_column = 0;
}

//void CleanerDetailWidget::receivePolicyKitSignal(bool status)
//{
//    //status = true:ok
//    //status = false:cacel
//    if(status)//ok
//    {
//        emit this->showActionAnimaiton();
//    }
//}

void CleanerDetailWidget::getAllSelectedItems()
{
    argsData.clear();
    QStringList fileTmp;
//    QStringList packageTmp;
//    QStringList firefoxcookieTmp;
//    QStringList chromiumcookieTmp;
//    QStringList traceTmp;

    foreach (QString info, m_selectedAptList) {
        fileTmp.append(info);
    }
    foreach (QString info, m_selectedSoftwareList) {
        fileTmp.append(info);
    }
    foreach (QString info, m_selectedThumbnailsList) {
        fileTmp.append(info);
    }
    foreach (QString info, m_selectedFirefoxCacheList) {
        fileTmp.append(info);
    }
    foreach (QString info, m_selectedChromiumCacheList) {
        fileTmp.append(info);
    }

    foreach (CleanSubGroup *item, m_cardlist) {
        if (item->getCheckBoxStatus() != 0) {
            if (item->statusTip() == "history-firefox") {
                argsData.insert("firefox-history", QStringList() << trace_firefox_count);
            }
            else if (item->statusTip() == "history-chromium") {
                argsData.insert("chromium-history", QStringList() << trace_chromium_count);
            }
            else if (item->statusTip() == "history-system") {
                argsData.insert("system-history", QStringList() << trace_system_count);
            }
            else if (item->statusTip() == "history-bash") {
                argsData.insert("bash-history", QStringList() << trace_bash_path);
            }
        }
    }

    if(fileTmp.length() > 0)
        argsData.insert("file", fileTmp);
    if(m_selectedFirefoxCookieList.length() > 0)
        argsData.insert("firefox-cookie", m_selectedFirefoxCookieList);
    if(m_selectedChromiumCookieList.length() > 0)
        argsData.insert("chromium-cookie", m_selectedChromiumCookieList);
    if(m_selectedTraceX11List.length() > 0)
        argsData.insert("x11-history", m_selectedTraceX11List);

//    if(cache_apt_btn != NULL && cache_apt_btn->getCheckBoxStatus() != 0)
//    {
//        QStringList tmp = cache_apt_items->getSelectedItems();
//        for(int i = 0; i<tmp.length();i++)
//        {
//            fileTmp.append(tmp.at(i));
//        }
//    }
//    if(cache_software_btn != NULL && cache_software_btn->getCheckBoxStatus() != 0)
//    {
//        QStringList tmp = cache_software_items->getSelectedItems();
//        for(int i = 0; i<tmp.length();i++)
//        {
//            fileTmp.append(tmp.at(i));
//        }
//    }
//    if(cache_thumbnails_btn != NULL && cache_thumbnails_btn->getCheckBoxStatus() != 0)
//    {
//        QStringList tmp = cache_thumbnails_items->getSelectedItems();
//        for(int i = 0; i<tmp.length();i++)
//        {
//            fileTmp.append(tmp.at(i));
//        }
//    }
//    if(cache_firefox_btn != NULL && cache_firefox_btn->getCheckBoxStatus() != 0)
//    {
//        QStringList tmp = cache_firefox_items->getSelectedItems();
//        for(int i = 0; i<tmp.length();i++)
//        {
//            fileTmp.append(tmp.at(i));
//        }
//    }
//    if(cache_chromium_btn != NULL && cache_chromium_btn->getCheckBoxStatus() != 0)
//    {
//        QStringList tmp = cache_chromium_items->getSelectedItems();
//        for(int i = 0; i<tmp.length();i++)
//        {
//            fileTmp.append(tmp.at(i));
//        }
//    }
    /*if(package_unneed_btn != NULL && package_unneed_btn->getCheckBoxStatus() != 0)
    {
        QStringList tmp = package_unneed_items->getSelectedItems();
        for(int i = 0; i<tmp.length();i++)
        {
            packageTmp.append(tmp.at(i));
        }
    }
    if(package_oldkernel_btn != NULL && package_oldkernel_btn->getCheckBoxStatus() != 0)
    {
        QStringList tmp = package_oldkernel_items->getSelectedItems();
        for(int i = 0; i<tmp.length();i++)
        {
            packageTmp.append(tmp.at(i));
        }
    }
    if(package_configfile_btn != NULL && package_configfile_btn->getCheckBoxStatus() != 0)
    {
        QStringList tmp = package_configfile_items->getSelectedItems();
        for(int i = 0; i<tmp.length();i++)
        {
            packageTmp.append(tmp.at(i));
        }
    }*/
//    if(cookies_firefox_btn != NULL && cookies_firefox_btn->getCheckBoxStatus() != 0)
//    {
//        QStringList tmp = cookies_firefox_items->getSelectedItems();
//        for(int i = 0; i<tmp.length();i++)
//        {
//            firefoxcookieTmp.append(tmp.at(i));
//        }
//    }
//    if(cookies_chromium_btn != NULL && cookies_chromium_btn->getCheckBoxStatus() != 0)
//    {
//        QStringList tmp = cookies_chromium_items->getSelectedItems();
//        for(int i = 0; i<tmp.length();i++)
//        {
//            chromiumcookieTmp.append(tmp.at(i));
//        }
//    }
//    if(trace_firefox_btn != NULL && trace_firefox_btn->getCheckBoxStatus() != 0)
//    {
//        argsData.insert("firefox-history", QStringList() << trace_firefox_count);
//    }
//    if(trace_chromium_btn != NULL && trace_chromium_btn->getCheckBoxStatus() != 0)
//    {
//       argsData.insert("chromium-history", QStringList() << trace_chromium_count);
//    }
//    if(trace_system_btn != NULL && trace_system_btn->getCheckBoxStatus() != 0)
//    {
//       argsData.insert("system-history", QStringList() << trace_system_count);
//    }
//    //kobe
//    if(trace_bash_btn != NULL && trace_bash_btn->getCheckBoxStatus() != 0)
//    {
//       argsData.insert("bash-history", QStringList() << trace_bash_path);
//    }
////    if(trace_x11_btn != NULL && trace_x11_btn->getCheckBoxStatus() != 0)
////    {
////        QStringList tmp = trace_x11_items->getSelectedItems();
////        for(int i = 0; i<tmp.length();i++)
////        {
////            traceTmp.append(tmp.at(i));
////        }
////    }

//    if(fileTmp.length() > 0)
//        argsData.insert("file", fileTmp);
////    if(packageTmp.length() > 0)
////        argsData.insert("package", packageTmp);
//    if(firefoxcookieTmp.length() > 0)
//        argsData.insert("firefox-cookie", firefoxcookieTmp);
//    if(chromiumcookieTmp.length() > 0)
//        argsData.insert("chromium-cookie", chromiumcookieTmp);
//    if(traceTmp.length() > 0)
//        argsData.insert("x11-history", traceTmp);
}
