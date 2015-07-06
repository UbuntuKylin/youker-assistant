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
    label = new QLabel(this);
    label->setObjectName("tipLabel");
    label->setGeometry(QRect(30, 15, 860, 20));
    label->setText(tr("Please choose theme which you need"));
    list_widget = NULL;
    dataOK = false;
}

bool ThemeWidget::getStatus()
{
    return this->dataOK;
}

void ThemeWidget::initData() {
//    list_widget = new NormalWidget(150, 150, 20, this);
    list_widget = new NormalWidget(119, 139, 20, this);
    list_widget->setGeometry(QRect(30, 55, 860, 330));
    list_widget->calculate_data();

    QString current_theme = sessionproxy->get_theme_qt();
    /*QStringList */syslist = sessionproxy->get_themes_qt();
    card_list.clear();
    QSignalMapper *signal_mapper = new QSignalMapper(this);
    for(int i = 0; i<syslist.length(); ++i)
    {
        NormalCard *card = new NormalCard(syslist[i], list_widget->cardPanel);
        card_list.append(card);
        if(current_theme == syslist[i]) {
            card->showUsingLogo(true);
        }
        list_widget->add_card(card);
        connect(card, SIGNAL(sendSelectThemeName(QString)), signal_mapper, SLOT(map()));
        signal_mapper->setMapping(card, QString::number(i, 10));
        connect(signal_mapper, SIGNAL(mapped(QString)), this, SLOT(switchUsingLogo(QString)));
        connect(card, SIGNAL(sendSelectThemeName(QString)), this, SLOT(changeTheme(QString)));
    }
    dataOK = true;
    this->initConnect();
}

ThemeWidget::~ThemeWidget()
{
}

void ThemeWidget::initConnect() {
    connect(sessionproxy, SIGNAL(string_value_notify(QString, QString)), this, SLOT(themewidget_notify_string(QString, QString)));
}

void ThemeWidget::switchUsingLogo(QString index)
{
    bool ok;
    int current_index = index.toInt(&ok, 10);
    for(int i=0; i<card_list.count(); i++)
    {
        NormalCard *card = card_list.at(i);
        if(current_index == i)
        {
            card->showUsingLogo(true);
        }
        else
        {
            card->showUsingLogo(false);
        }
    }
}

void ThemeWidget::changeTheme(QString name)
{
    sessionproxy->set_theme_qt(name);
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
            this->switchUsingLogo(QString::number(index, 10));
        }
    }
}
