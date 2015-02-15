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
//#include "mainwindow.h"
#include "../dbusproxy/youkersessiondbus.h"
//#include "../dbusproxy/youkersystemdbus.h"

CleanerWidget::CleanerWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setFixedSize(900, 403);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Widget);
    //set white background color
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    this->setPalette(palette);

    statked_widget = new QStackedWidget(this);
    p_mainwindow = NULL;
    systemProxy = NULL;
    sessionProxy = NULL;
    main_widget = NULL;
    detail_widget = NULL;


    kthread.setCleanerWidget(this);
}

CleanerWidget::~CleanerWidget()
{

}

void CleanerWidget::initUI()
{
    main_widget = new CleanerMainWidget(this, p_mainwindow);
    detail_widget = new CleanerDetailWidget(this, sessionProxy, systemProxy, p_mainwindow);
    connect(this, SIGNAL(transCleanSignal()), detail_widget, SLOT(receiveCleanSignal()));
    connect(this, SIGNAL(clearDetailPage()), detail_widget, SLOT(CleanUIAndData()));
    connect(sessionProxy, SIGNAL(tellCleanerDetailData(QStringList)), detail_widget, SLOT(showReciveData(QStringList)));
    connect(sessionProxy, SIGNAL(tellCleanerDetailStatus(QString)), detail_widget, SLOT(showReciveStatus(QString)));
    statked_widget->addWidget(main_widget);
    statked_widget->addWidget(detail_widget);
    QVBoxLayout *layout1 = new QVBoxLayout();
    layout1->addWidget(statked_widget);
    layout1->setSpacing(0);
    layout1->setMargin(0);
    layout1->setContentsMargins(0, 0, 0, 0);

    setLayout(layout1);
}

void CleanerWidget::displayDetailPage()
{
    statked_widget->setCurrentIndex(1);
}

void CleanerWidget::displayMainPage()
{
    statked_widget->setCurrentIndex(0);
    emit this->clearDetailPage();
}
