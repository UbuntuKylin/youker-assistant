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

#include "loginwidget.h"
#include "../component/kylintoolbutton.h"
#include "mainwindow.h"
#include <QDebug>

LoginWidget::LoginWidget(QWidget *parent)
	: QWidget(parent)
{
    this->setFixedSize(220, 72);
    logo_label = new QPushButton();
    logo_label->setObjectName("whiteButton");
    logo_label->setCursor(Qt::PointingHandCursor);
//    logo_label->setCursor(Qt::ArrowCursor);
//    logo_label->setCursor(Qt::SizeHorCursor);
    logo_label->setFocusPolicy(Qt::NoFocus);
    login_button = new QPushButton();
    login_button->setObjectName("loginButton");
    login_button->setCursor(Qt::PointingHandCursor);
    login_button->setFocusPolicy(Qt::NoFocus);
    login_button->setFixedSize(44, 44);
//    login_button->setIcon(QIcon("://res/logo.png"));
    login_button->setIconSize(QSize(44, 44));
    login_button->setFlat(true);
//    login_button->setStyleSheet("QPushButton{background-image: url(://res/logo.png); border: none;}"
//        "QPushButton:hover{background-image: url(://res/logo-hover.png);}"
//        "QPushButton:pressed{background-image: url(://res/logo-hover.png);}");

    user_label = new QLabel();
    user_label->hide();
    logout_btn = new QPushButton();
    logout_btn->setObjectName("whiteButton");
    logout_btn->setCursor(Qt::PointingHandCursor);
    logout_btn->setFocusPolicy(Qt::NoFocus);
    logout_btn->hide();

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addStretch();
    layout->addWidget(logo_label, 0, Qt::AlignVCenter);
    layout->addWidget(login_button, 0, Qt::AlignVCenter);
    layout->addWidget(user_label, 0, Qt::AlignVCenter);
    layout->addWidget(logout_btn, 0, Qt::AlignVCenter);
    layout->setSpacing(11);
    layout->setMargin(0);
    layout->setContentsMargins(0, 0, 0, 0);

    setLayout(layout);

    is_move = false;
    this->initConnect();
    this->setLauguage();
}

LoginWidget::~LoginWidget()
{
}

void LoginWidget::initConnect()
{
    connect(logo_label, SIGNAL(clicked()), this, SLOT(onLoginButtonClicked()));
    connect(login_button, SIGNAL(clicked()), this, SLOT(onLoginButtonClicked()));
    connect(logout_btn, SIGNAL(clicked()), this, SLOT(onLogoutButtonClicked()));
}

void LoginWidget::showLoginInfo(QString name, QString email)
{
    logo_label->hide();
    login_button->hide();
    logout_btn->show();
    logout_btn->setText(name + "<" + email + ">");
    logout_btn->show();
}

void LoginWidget::showLoginAndLogoutStatus(bool status)
{
    if(status)
    {//logout success
        logo_label->show();
        login_button->show();
        logout_btn->hide();
        logout_btn->setText("");
        logout_btn->hide();
    }
    else
    {//login failed
        qDebug() << "login failed";
    }
}

void LoginWidget::setLauguage()
{
    logo_label->setText(tr("Login Youker Account"));
}

void LoginWidget::onLoginButtonClicked()
{
    sessionProxy->popup_login_dialog();
}

void LoginWidget::onLogoutButtonClicked()
{
    sessionProxy->logout_ubuntukylin_account();
}
