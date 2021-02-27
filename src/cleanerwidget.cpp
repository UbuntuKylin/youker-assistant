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

#include "cleanerwidget.h"
#include <QVBoxLayout>
#include <QDebug>
#include "../component/utils.h"
#include <QPainter>
#include <QStyleOption>
#include "../cleaner/cleandetailveiw.h"

CleanerWidget::CleanerWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setFixedSize(860, 460);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Widget);

    this->setStyleSheet("QWidget{background: #ffffff; border: none;/*border-bottom-right-radius:10px;border-bottom-left-radius:6px*/}");
    //set white background color
    this->setAutoFillBackground(true);
//    QPalette palette;
//    palette.setBrush(QPalette::Window, QBrush(Qt::white));
//    this->setPalette(palette);

    statked_widget = new QStackedWidget(this);
    p_mainwindow = NULL;
    main_widget = NULL;
//    detail_widget = NULL;
}

CleanerWidget::~CleanerWidget()
{

}

void CleanerWidget::initUI(QString skin)
{
    //20180101
    main_widget = new CleanerMainWidget(this, p_mainwindow, toolKits, skin);
//    detail_widget = new CleanerDetailWidget(this, p_mainwindow, toolKits ,skin);
    detailview = new CleandetailVeiw(this);

//    connect(this, SIGNAL(transCleanSignal()), detail_widget, SLOT(receiveCleanSignal()));
    connect(detailview,SIGNAL(hideThisWidget()),this,SLOT(displayMainPage()));
//    connect(this,SIGNAL(isScanning(QString)),detailview,SLOT(getScanResult(QString))/*,Qt::BlockingQueuedConnection*/);
//    connect(this,SIGNAL(finishScanWork(QString)),detailview,SLOT(finishScanResult(QString))/*,Qt::BlockingQueuedConnection*/);
//    connect(this,SIGNAL(tellScanResult(QString,QString)),detailview,SLOT(getScanAllResult(QString,QString))/*,Qt::BlockingQueuedConnection*/);
    connect(detailview,SIGNAL(startOneKeyClean()),this,SIGNAL(startOneKeyClean()));
    connect(this,SIGNAL(finishCleanWorkMain(QString)),detailview,SLOT(getCleanResult(QString)));

    connect(main_widget,SIGNAL(onKeyClean(QStringList)),this,SIGNAL(startOneKeyScan(QStringList)));
    connect(main_widget,SIGNAL(hideThisWidget()),this,SLOT(displayDetailPage()));
    connect(this, SIGNAL(transScanSignal()), main_widget, SLOT(receiveScanSignal()));
    connect(main_widget, SIGNAL(showActionAnimaiton()), this, SIGNAL(tranActionAnimaitonSignal()));
//    connect(detail_widget, SIGNAL(showActionAnimaiton()), this, SIGNAL(tranCleanActionAnimaitonSignal()));
//    connect(detail_widget, SIGNAL(sendScanOverStatus(bool)), this, SIGNAL(tranScanOverSignal(bool)));

    statked_widget->addWidget(main_widget);
//    statked_widget->addWidget(detail_widget);
    statked_widget->addWidget(detailview);
    QVBoxLayout *layout1 = new QVBoxLayout();
    layout1->addWidget(statked_widget);
    layout1->setSpacing(0);
    layout1->setMargin(0);
    layout1->setContentsMargins(0, 0, 0, 0);

    setLayout(layout1);

    connect(main_widget, SIGNAL(startScanSystem(QMap<QString,QVariant>)), this, SIGNAL(startScanSystem(QMap<QString,QVariant>)));
    connect(detailview, SIGNAL(startCleanSystem(QMap<QString,QVariant>)), this, SIGNAL(startCleanSystem(QMap<QString,QVariant>)));
    connect(this, SIGNAL(tellCleanerDetailData(QStringList)), detailview, SLOT(showReciveData(QStringList)));
    connect(this, SIGNAL(tellCleanerDetailStatus(QString)), detailview, SLOT(showReciveStatus(QString)));

    connect(this, SIGNAL(tellCleanerMainData(QStringList)), detailview, SLOT(showCleanerData(QStringList))/*, Qt::BlockingQueuedConnection*/);
    connect(this, SIGNAL(tellCleanerMainStatus(QString, QString)), detailview, SLOT(showCleanerStatus(QString, QString))/*, Qt::BlockingQueuedConnection*/);
    connect(this, SIGNAL(sendCleanErrorSignal(QString)), detailview, SLOT(showCleanerError(QString))/*, Qt::BlockingQueuedConnection*/);
    connect(this, SIGNAL(policykitCleanSignal(bool)), detailview, SLOT(receivePolicyKitSignal(bool)));
    connect(this, SIGNAL(sendCleanOverSignal()), detailview, SLOT(showCleanOverStatus()));
}

void CleanerWidget::paintEvent(QPaintEvent *event)
{

}

void CleanerWidget::resetSkin(QString skin)
{
    if(main_widget != NULL)
        main_widget->resetCurrentSkin(skin);
//    if(detail_widget != NULL)
//        detail_widget->resetCurrentSkin(skin);
}

void CleanerWidget::displayDetailPage()
{
    statked_widget->setCurrentIndex(1);
    detailview->ResetUI();
}

void CleanerWidget::displayMainPage()
{
    statked_widget->setCurrentIndex(0);
    main_widget->resetDefaultStatus();
    //    detail_widget->CleanUIAndData();
}
