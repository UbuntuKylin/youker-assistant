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
#include "../src/mainwindow.h"
#include <QEvent>
#include <QHelpEvent>

KylinMenu::KylinMenu(QWidget *widget)
    : QMenu(widget)
{
    this->createActions();
    this->setLanguage();
}

KylinMenu::~KylinMenu()
{
    if(check_label != NULL)
    {
        delete check_label;
        check_label = NULL;
    }
    if(help_label != NULL)
    {
        delete help_label;
        help_label = NULL;
    }
    if(feedback_label != NULL)
    {
        delete feedback_label;
        feedback_label = NULL;
    }
    if(about_label != NULL)
    {
        delete about_label;
        about_label = NULL;
    }
    if(check_button != NULL)
    {
        delete check_button;
        check_button = NULL;
    }
    if(help_button != NULL)
    {
        delete help_button;
        help_button = NULL;
    }
    if(feedback_button != NULL)
    {
        delete feedback_button;
        feedback_button = NULL;
    }
    if(about_button != NULL)
    {
        delete about_button;
        about_button = NULL;
    }
    if(check_widget != NULL)
    {
        delete check_widget;
        check_widget = NULL;
    }
    if(help_widget != NULL)
    {
        delete help_widget;
        help_widget = NULL;
    }
    if(feedback_widget != NULL)
    {
        delete feedback_widget;
        feedback_widget = NULL;
    }
    if(about_widget != NULL)
    {
        delete about_widget;
        about_widget = NULL;
    }
}

void KylinMenu::createActions()
{
//    help_action = new QAction(this);
////    features_action = new QAction(this);
//    feedback_action = new QAction(this);
////    setting_action = new QAction(this);
//    about_action = new QAction(this);
    check_widget = new QWidget();
    help_widget = new QWidget();
    feedback_widget = new QWidget();
    about_widget = new QWidget();
    check_widget_action = new QWidgetAction(this);
    help_widget_action = new QWidgetAction(this);
    feedback_widget_action = new QWidgetAction(this);
    about_widget_action = new QWidgetAction(this);
    check_label = new QLabel();
    help_label = new QLabel();
    feedback_label = new QLabel();
    about_label = new QLabel();
    check_button = new QPushButton();
    help_button = new QPushButton();
    feedback_button = new QPushButton();
    about_button = new QPushButton();
    check_button->setStyleSheet("QPushButton{background-color:transparent;border:none;text-align:left;font-family: 方正黑体_GBK;font-size:14px;color:#666666;}QPushButton:hover{color:#0396DC;}");//background:transparent;
    help_button->setStyleSheet("QPushButton{background-color:transparent;border:none;text-align:left;font-family: 方正黑体_GBK;font-size:14px;color:#666666;}QPushButton:hover{color:#0396DC;}");//background:transparent;
    feedback_button->setStyleSheet("QPushButton{background-color:transparent;border:none;text-align:left;font-family: 方正黑体_GBK;font-size:14px;color:#666666;}QPushButton:hover{color:#0396DC;}");//background:transparent;
    about_button->setStyleSheet("QPushButton{background-color:transparent;border:none;text-align:left;font-family: 方正黑体_GBK;font-size:14px;color:#666666;}QPushButton:hover{color:#0396DC;}");//background:transparent;

    QPixmap check_pixmap(":/tool/res/menu/upgrade.png");
    check_label->setPixmap(check_pixmap);
    check_label->setFixedSize(check_pixmap.size());
    check_button->setFocusPolicy(Qt::NoFocus);

    QPixmap help_pixmap(":/tool/res/menu/help.png");
    help_label->setPixmap(help_pixmap);
    help_label->setFixedSize(help_pixmap.size());
//    help_button->setIcon(help_pixmap);
//    help_button->setIconSize(help_pixmap.size());
    help_button->setFocusPolicy(Qt::NoFocus);

    QPixmap feedback_pixmap(":/tool/res/menu/feedback.png");
    feedback_label->setPixmap(feedback_pixmap);
    feedback_label->setFixedSize(feedback_pixmap.size());
    feedback_button->setFocusPolicy(Qt::NoFocus);

    QPixmap about_pixmap(":/tool/res/menu/about.png");
    about_label->setPixmap(about_pixmap);
    about_label->setFixedSize(about_pixmap.size());
    about_button->setFocusPolicy(Qt::NoFocus);

    QHBoxLayout *check_layout = new QHBoxLayout();
    check_layout->addWidget(check_label);
    check_layout->addWidget(check_button);
    check_layout->setSpacing(10);
    check_layout->setContentsMargins(20, 0, 20, 0);
    check_widget->setLayout(check_layout);
    check_widget_action->setDefaultWidget(check_widget);

    QHBoxLayout *help_layout = new QHBoxLayout();
    help_layout->addWidget(help_label);
    help_layout->addWidget(help_button);
    help_layout->setSpacing(10);
    help_layout->setContentsMargins(20, 0, 20, 0);
    help_widget->setLayout(help_layout);
    help_widget_action->setDefaultWidget(help_widget);

    QHBoxLayout *feedback_layout = new QHBoxLayout();
    feedback_layout->addWidget(feedback_label);
    feedback_layout->addWidget(feedback_button);
    feedback_layout->setSpacing(10);
    feedback_layout->setContentsMargins(20, 0, 20, 0);
    feedback_widget->setLayout(feedback_layout);
    feedback_widget_action->setDefaultWidget(feedback_widget);

    QHBoxLayout *about_layout = new QHBoxLayout();
    about_layout->addWidget(about_label);
    about_layout->addWidget(about_button);
    about_layout->setSpacing(10);
    about_layout->setContentsMargins(20, 0, 20, 0);
    about_widget->setLayout(about_layout);
    about_widget_action->setDefaultWidget(about_widget);

//    this->addAction(check_widget_action);
    if (GlobalData::globalarch == "x86_64")
    {
        this->addAction(help_widget_action);
        this->addAction(feedback_widget_action);
        this->addSeparator();
    }

    this->addAction(about_widget_action);

//    this->addAction(help_action);
////    this->addAction(features_action);
//    this->addAction(feedback_action);
////    this->addAction(setting_action);
//    this->addSeparator();
//    this->addAction(about_action);
//    this->addSeparator();
//    this->addAction(play_widget_action);
}

void KylinMenu::setLanguage() {
//    help_action->setText(tr("Forum Help"));
////    features_action->setText(tr("Features"));
//    feedback_action->setText(tr("Feedback"));
////    setting_action->setText(tr("Set up"));
//    about_action->setText(tr("About us"));
//    help_action->setIcon(QIcon("://res/icon.png"));
//    help_action->setToolTip(tr("Help"));
    check_button->setText(tr("Check and update"));
    help_button->setText(tr("Forum Help"));
    feedback_button->setText(tr("Feedback"));
    about_button->setText(tr("About us"));
}

void KylinMenu::initConnect()
{
//    connect(help_action, SIGNAL(triggered()), this, SLOT(forumHelp()));
////    connect(features_action, SIGNAL(triggered()), p_mainwindow, SLOT(newFeatures()));
//    connect(feedback_action, SIGNAL(triggered()), this, SLOT(questionFeedback()));
////    connect(setting_action, SIGNAL(triggered()), p_mainwindow, SLOT(setupConfigure()));
//    connect(about_action, SIGNAL(triggered()), p_mainwindow, SLOT(aboutUs()));
    connect(check_button, SIGNAL(clicked()), p_mainwindow, SLOT(openUpgradePage()));
    connect(help_button, SIGNAL(clicked()), this, SLOT(forumHelp()));
    connect(feedback_button, SIGNAL(clicked()), this, SLOT(questionFeedback()));
    connect(about_button, SIGNAL(clicked()), p_mainwindow, SLOT(aboutUs()));
}

void KylinMenu::forumHelp()
{
    this->close();
    QUrl url(QString("http://www.ubuntukylin.com/ukylin/forum.php"));
    QDesktopServices::openUrl(url);
}

void KylinMenu::questionFeedback()
{
    this->close();
    QUrl url(QString("https://bugs.launchpad.net/youker-assistant"));
    QDesktopServices::openUrl(url);
}

//bool KylinMenu::event(QEvent* e)
//{
//    switch(e->type())
//    {
//        case QEvent::ToolTip:
//        //show action tooltip instead of widget tooltip
//        {
//            QHelpEvent *he = dynamic_cast(e);
//            QAction *act = actionAt(he->pos());
//            if(act)
//            {
//                QToolTip::showText(he->globalPos(), act->toolTip(), this);
//                return true;
//            }
//        }
//        break;
//    }
//    QMenu::event(e);
//}
