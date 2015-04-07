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

SkinCenter::SkinCenter(QWidget *parent/*, Qt::WindowFlags f*/)
    :QDialog(parent)
{
    this->setFixedSize(500, 271);
    this->setStyleSheet("QDialog{border: 1px solid gray;border-radius:2px}");
    setWindowFlags(Qt::FramelessWindowHint);
    title_bar = new KylinTitleBar();
    list_widget = new KylinListWidget();
    connect(list_widget, SIGNAL(sendBackgroundName(QString)), this, SLOT(changeSkinCenterBackground(QString)));
    list_widget->setMouseTracking(true);//hover need it
    list_widget->setAutoFillBackground(false);

    QHBoxLayout *list_layout  = new QHBoxLayout();
    list_layout->addWidget(list_widget);
    list_layout->setSpacing(0);
    list_layout->setMargin(0);
    list_layout->setContentsMargins(1, 0, 1, 1);

    QVBoxLayout *layout  = new QVBoxLayout();
    layout->addWidget(title_bar);
//    layout->addWidget(list_widget);
    layout->addLayout(list_layout);
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

//    delayTimer = QTimer();

    this->setLanguage();
    this->initConnect();
}

SkinCenter::~SkinCenter()
{
//    disconnect(delayTimer,SIGNAL(timeout()),this,SLOT(changeAnimationStep()));
//    if(delayTimer->isActive()) {
//        delayTimer->stop();
//    }
//    if (delayTimer != NULL) {
//        delete delayTimer;
//        delayTimer = NULL;
//    }
}

void SkinCenter::setLanguage()
{

}

void SkinCenter::initConnect()
{
    connect(title_bar,SIGNAL(closeDialog()), this, SLOT(onCloseButtonClicked()));
//    connect(delayTimer, SIGNAL(timeout()), this, SLOT(changeAnimationStep()));
}

void SkinCenter::onCloseButtonClicked()
{
    this->close();
}

void SkinCenter::changeSkinCenterBackground(QString pciture)
{
    last_skin_path = pciture;
    title_bar->resetBackground(last_skin_path);
}

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
        QString iconPath = QString(":/background/res/skin/%1.png").arg(index + 1);
        QPixmap pixMap(iconPath);
        KylinListWidgetItem *item = new KylinListWidgetItem(QIcon(pixMap.scaled(QSize(150,100))), "");
        item->setMainWindow(mainwindow);
        item->setSkinName(iconPath);
        item->setSizeHint(QSize(150,100));
        list_widget->insertItem(index, item);
    }
}

void SkinCenter::initTitleBar(const QString &path)
{
    title_bar->setTitleWidth(500);
    title_bar->setTitleName(tr("Skin Center"));
    last_skin_path = path;
    title_bar->setTitleBackgound(last_skin_path);
}

//void MainWindow::reViewThePointSkin(QString pciture)
//{
//  if (review_skin_pixmap.isDetached())
//  {
//    review_skin_pixmap.detach();
//  }

//  review_skin_pixmap.load(pciture);
//  QPalette palette_back;
//  palette_back.setBrush(QPalette::Background, review_skin_pixmap);
//  action_widget->setPalette(palette_back);
//}

//void  SkinCenter::enterEvent (QEvent *)
//{
//    delayTimer->start(300);
//}

//void  SkinCenter::leaveEvent (QEvent *)
//{
//    if(delayTimer->isActive())
//        delayTimer->stop();
//}

void SkinCenter::closeEvent(QCloseEvent *event)
{
    title_bar->setTitleBackgound(last_skin_path);
    mainwindow->restoreSkin();
}
