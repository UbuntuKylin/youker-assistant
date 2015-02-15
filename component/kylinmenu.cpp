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

#include "kylinmenu.h"
#include "../mainui/mainwindow.h"

KylinMenu::KylinMenu(QWidget *widget)
    : QMenu(widget)
{
    this->createActions();
    this->setLanguage();
}


void KylinMenu::createActions()
{
    help_action = new QAction(this);
//    features_action = new QAction(this);
    feedback_action = new QAction(this);
//    setting_action = new QAction(this);
    about_action = new QAction(this);

    this->addAction(help_action);
//    this->addAction(features_action);
    this->addAction(feedback_action);
//    this->addAction(setting_action);
    this->addSeparator();
    this->addAction(about_action);
}

void KylinMenu::setLanguage() {
    help_action->setText(tr("Forum Help"));
//    features_action->setText(tr("Features"));
    feedback_action->setText(tr("Feedback"));
//    setting_action->setText(tr("Set up"));
    about_action->setText(tr("About us"));
    help_action->setIcon(QIcon("://res/icon.png"));
    help_action->setToolTip(tr("Help"));
}

void KylinMenu::initConnect()
{
    connect(help_action, SIGNAL(triggered()), this, SLOT(forumHelp()));
//    connect(features_action, SIGNAL(triggered()), p_mainwindow, SLOT(newFeatures()));
    connect(feedback_action, SIGNAL(triggered()), this, SLOT(questionFeedback()));
//    connect(setting_action, SIGNAL(triggered()), p_mainwindow, SLOT(setupConfigure()));
    connect(about_action, SIGNAL(triggered()), p_mainwindow, SLOT(aboutUs()));
}

void KylinMenu::forumHelp()
{
    QUrl url(QString("http://www.ubuntukylin.com/ukylin/forum.php"));
    QDesktopServices::openUrl(url);
}

void KylinMenu::questionFeedback()
{
    QUrl url(QString("https://bugs.launchpad.net/youker-assistant"));
    QDesktopServices::openUrl(url);
}
