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

#include "themewidget.h"
#include <QStandardItemModel>
#include <QListWidgetItem>
#include <QLabel>
#include <QDebug>
#include <QGridLayout>
#include "../dbusproxy/youkersessiondbus.h"

ThemeWidget::ThemeWidget(QWidget *parent, SessionDispatcher *proxy) :
    QWidget(parent),
    sessionproxy(proxy)
{
    //创建QListWidget部件
    list_widget = new QListWidget(this);
    list_widget->setFocusPolicy(Qt::NoFocus);
    //设置QListWidget中的单元项的图片大小
    list_widget->setIconSize(QSize(106, 106));
    list_widget->setResizeMode(QListView::Adjust);
    //设置QListWidget的显示模式
    list_widget->setViewMode(QListView::IconMode);
    //设置QListWidget中的单元项不可被拖动
    list_widget->setMovement(QListView::Static);
    //设置QListWidget中的单元项的间距
    list_widget->setSpacing(26);
//    QPalette palette1;
//    palette1.setBrush(QPalette::Normal, QPalette::Highlight, Qt::black);
//    palette1.setBrush(QPalette::Inactive, QPalette::Highlight, Qt::black);
//    list_widget->setPalette(palette1);

    dataOK = false;
    current_index = 0;
    initIndex = 0;

    using_label = new QLabel(list_widget);
    using_label->setFixedSize(20, 20);
    using_label->setAutoFillBackground(true);
    QPalette palette;
//    palette.setBrush(using_label->backgroundRole(), QBrush(QPixmap("://res/using.png")));
    palette.setBrush(QPalette::Background, QBrush(QPixmap("://res/checkbox-press.png")));
    using_label->setPalette(palette);
    using_label->show();
//    using_label->move(26, 26);

    //    QHBoxLayout *layout = new QHBoxLayout();
    //    layout->addWidget(list_widget);
    //    setLayout(layout);
    QGridLayout *layout = new QGridLayout();
    layout->addWidget(list_widget);
    setLayout(layout);
}

bool ThemeWidget::getStatus()
{
    return this->dataOK;
}

void ThemeWidget::initData() {
    QString current_theme = sessionproxy->get_theme_qt();
    /*QStringList */syslist = sessionproxy->get_themes_qt();
    QList<QString>::Iterator it = syslist.begin(), itend = syslist.end();
    initIndex = 0;
    for(;it != itend; it++,initIndex++)
    {
        if(*it == current_theme)
            break;
    }

    for(int i = 0; i<syslist.length(); ++i)
    {
        QString strPath=QString(":/gtk/res/theme/" + syslist[i] + ".png");
        QPixmap pixmap(strPath);
        if(pixmap.isNull())
        {
            pixmap = QPixmap(":/gtk/res/theme/disappear.png");
        }
        //伸缩106*106
        QListWidgetItem *pItem = new QListWidgetItem(QIcon(pixmap.scaled(QSize(106,106))), tr("%1").arg(syslist[i]));
        pItem->setSizeHint(QSize(130,130));
//        pItem->setFlags(Qt::ItemIsSelectable);
//        pItem->setBackgroundColor(QColor(0, 0, 255, 127));
//        pItem->setTextColor(QColor(0, 0, 255, 127));//0629
        list_widget->insertItem(i, pItem);

//        QListWidgetItem *pItem = new QListWidgetItem(QIcon(pixmap.scaled(QSize(106,106))), tr("%1").arg(syslist[i]), list_widget);
//        QWidget *wContainer = new QWidget(list_widget);
////        wContainer->setStyleSheet("QWidget{background:transparent url(://res/menu-big-hover.png);}");
//        wContainer->resize(130, 130);
//        QLabel *label = new QLabel();
//        label->setStyleSheet("QLabel{background-image:url('://res/menu-big-hover.png')}");
//        QHBoxLayout *hLayout = new QHBoxLayout(wContainer);
//        hLayout->addWidget(label);
//        list_widget->setItemWidget(pItem,wContainer);
    }

    //set using logo
    QListWidgetItem *cur_item = list_widget->item(initIndex);
    this->initCurrentTheme(cur_item);
    dataOK = true;
    this->initConnect();
}

ThemeWidget::~ThemeWidget()
{
}

void ThemeWidget::initConnect() {
    connect(list_widget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(onItemClicked(QListWidgetItem*)));
    connect(sessionproxy, SIGNAL(string_value_notify(QString, QString)), this, SLOT(themewidget_notify_string(QString, QString)));
}

void ThemeWidget::themewidget_notify_string(QString key, QString value)
{
    if (key == "gtk-theme")
    {
        QList<QString>::Iterator it = syslist.begin(), itend = syslist.end();
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
        if(exist)
        {
            exist = false;
            QListWidgetItem *cur_item = list_widget->item(index);
            this->initCurrentTheme(cur_item);
        }
    }
}

void ThemeWidget::initCurrentTheme(QListWidgetItem *init_item)
{
    int nRowIndex = list_widget->row(init_item);
    QRect rect = list_widget->visualItemRect(init_item);
//    QPoint p = rect.topLeft();
//    using_label->move(p.x(), p.y());
    QPoint p = rect.bottomRight();
    using_label->move(p.x()-20, p.y()-40);
//    using_label->move(p.x(), p.y());
    //reset current item status
    QListWidgetItem *pre_item = list_widget->item(current_index);
//    pre_item->setTextColor(QColor(0, 0, 255, 127));//0629
    pre_item->setTextColor(QColor("4f4f4f"));
    current_index = nRowIndex;
    init_item->setTextColor(QColor("4f4f4f"));
}

void ThemeWidget::onItemClicked(QListWidgetItem *selected_item)
{
    if(!selected_item)
    {
        return;
    }
    sessionproxy->set_theme_qt(selected_item->text());

    int nRowIndex = list_widget->row(selected_item);
    QRect rect = list_widget->visualItemRect(selected_item);
//    QPoint p = rect.topLeft();
    QPoint p = rect.bottomRight();
    using_label->move(p.x()-20, p.y()-40);
//    p.setX(p.x() + 58);
//    p.setY(p.y() + 29);
//    using_label->move(p.x(), p.y());

    //reset current item status
    QListWidgetItem *pre_item = list_widget->item(current_index);
//    pre_item->setTextColor(QColor(0, 0, 255, 127));
    pre_item->setTextColor(QColor("4f4f4f"));
    pre_item->setBackground(Qt::white);

    current_index = nRowIndex;
//    item->setBackgroundColor(QColor(0, 0, 255, 127));
    selected_item->setTextColor(QColor("4f4f4f"));
//    selected_item->setSizeHint(QSize(130,130));
}

void ThemeWidget::paintEvent(QPaintEvent *)
{
    //kobe: if the scrollbar move, the using_label should move the the select item
    QListWidgetItem *select_item = list_widget->item(current_index);
    QRect rect = list_widget->visualItemRect(select_item);
//    QPoint p = rect.topLeft();
//    using_label->move(p.x(), p.y());
    QPoint p = rect.bottomRight();
    using_label->move(p.x()-20, p.y()-40);
}
