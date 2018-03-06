/*
 * Copyright (C) 2013 ~ 2018 National University of Defense Technology(NUDT) & Tianjin Kylin Ltd.
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
#include "theme/themeview.h"

#include <QStandardItemModel>
#include <QSignalMapper>
#include <QListWidgetItem>
#include <QLabel>
#include <QDebug>
#include <QGridLayout>

ThemeWidget::ThemeWidget(QWidget *parent) :
    SettingModulePage(parent)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    this->resize(parent->size());
//    this->setFixedSize(900, 403);

    label = new QLabel(this);
    label->setObjectName("tipLabel");
    label->setFixedHeight(30);
//    label->setGeometry(QRect(30, 15, 860, 50));
    label->setText(tr("Please choose theme which you need"));

    m_themeView = new ThemeView(this);
    connect(m_themeView, SIGNAL(sendSelectThemeName(QString)), this, SLOT(changeTheme(QString)));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(5);
    layout->setMargin(0);
    layout->setContentsMargins(10, 5, 10, 0);
    layout->addWidget(label);
    layout->addWidget(m_themeView);
    this->setLayout(layout);
}

QString ThemeWidget::settingModuleName()
{
    return "ThemePage";
}

void ThemeWidget::onReceiveThemeList(const QString &currentTheme, const QStringList &themeList)
{
//    qDebug() << "currentTheme="<<currentTheme<<", themeList="<<themeList;

    if (!themeList.isEmpty()) {
        m_themeView->clearData();

        syslist.clear();
        syslist = themeList;
        //kobe test 2018

        for (const QString theme : themeList) {
            if(currentTheme == theme)
                m_themeView->loadOneTheme(theme, true);
            else
                m_themeView->loadOneTheme(theme, false);
        }
    }
}


void ThemeWidget::initSettingData()
{
    emit this->requestThemeData();

    this->initConnect();
}

ThemeWidget::~ThemeWidget()
{
    this->resetUI();
}

void ThemeWidget::resetUI()
{

}

void ThemeWidget::initConnect() {

//    connect(sessionproxy, SIGNAL(string_value_notify(QString, QString)), this, SLOT(themewidget_notify_string(QString, QString)));
}

void ThemeWidget::switchUsingLogo(QString index)
{

}

void ThemeWidget::changeTheme(QString name)
{
    emit changeSystemTheme(name);
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
