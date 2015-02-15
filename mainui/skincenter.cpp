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

#include "skincenter.h"
#include "mainwindow.h"
#include <QDebug>
#include <QVBoxLayout>

SkinCenter::SkinCenter(QWidget *parent, Qt::WindowFlags f)
:QDialog(parent)
{

//    m_Dlg.setupUi(this);
    this->setFixedSize(500, 271);
    setWindowFlags(Qt::FramelessWindowHint);

    title_bar = new KylinTitleBar();
//    initTitleBar();

    list_widget = new KylinListWidget();
    list_widget->setMouseTracking(true);//hover need it
    list_widget->setAutoFillBackground(false);

    QVBoxLayout *layout  = new QVBoxLayout();
    layout->addWidget(title_bar);
    layout->addWidget(list_widget);
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);
    this->setLanguage();
    this->initConnect();
}

SkinCenter::~SkinCenter()
{
}

void SkinCenter::setLanguage()
{

}

void SkinCenter::initConnect()
{
//    connect(title_bar, SIGNAL(showMinDialog()), this, SLOT(onMinButtonClicked()));
    connect(title_bar,SIGNAL(closeDialog()), this, SLOT(onCloseButtonClicked()));
}

void SkinCenter::onCloseButtonClicked()
{
    this->close();
}

//void SkinCenter::onMinButtonClicked()
//{
////    this->showMinimized();
//    this->hide();
//}

void SkinCenter::initBackgroundList()
{
    list_widget->setIconSize(QSize(150, 100));
    list_widget->setResizeMode(QListView::Adjust);
    list_widget->setViewMode(QListView::IconMode);
    list_widget->setMovement(QListView::Static);
    list_widget->setSpacing(5);
    list_widget->setMainWindow(mainwindow);
    for(int index = 0; index < 4; ++index)
    {
        QString strPath = QString(":/background/res/skin/%1.png").arg(index + 1);
        QString pciture_path = QString(":/background/res/skin/%1.png").arg(index + 1);
        QPixmap objPixmap(strPath);
        KylinListWidgetItem *item = new KylinListWidgetItem(QIcon(objPixmap.scaled(QSize(150,100))),"");
        item->setMainWindow(mainwindow);
        item->setSkinName(pciture_path);
        item->setSizeHint(QSize(150,100));
        list_widget->insertItem(index, item);
    }
}

void SkinCenter::initTitleBar(const QString &path)
{
    title_bar->setTitleWidth(500);
    title_bar->setTitleName(tr("Skin Center"));
    title_bar->setTitleBackgound(path);
}

void SkinCenter::closeEvent(QCloseEvent *event)
{
   mainwindow->restoreSkin();
}
