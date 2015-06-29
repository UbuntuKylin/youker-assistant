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

#include "QDesktopWidget"

#include "aboutdialog.h"
//#include "ui_aboutdialog.h"
#include <QtGui>

AboutDialog::AboutDialog(QWidget *parent, const QString &version, QString skin) :
    QDialog(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
//    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->setFixedSize(560, 398);
    this->setStyleSheet("QDialog{border: 1px solid gray;border-radius:2px}");

    title_bar = new KylinTitleBar();
//    title_bar->setGeometry(QRect(0, 0, 400, 32));
    title_bar->setTitleName(tr("About"));
    title_bar->setTitleWidth(560);
    title_bar->setTitleBackgound(skin);

    iconLabel = new QLabel();
    nameLabel = new QLabel();
    versionLabel = new QLabel();
    linkLabel = new QLabel();
    iconLabel->setFixedSize(64, 64);
    iconLabel->setStyleSheet("QLabel{background-image:url(':/res/youker-assistant.png')}");
    nameLabel->setAlignment(Qt::AlignCenter);
    nameLabel->setText(tr("Youker Assisant"));
    versionLabel->setAlignment(Qt::AlignCenter);
    versionLabel->setText(version);
    linkLabel->setAlignment(Qt::AlignRight);
    linkLabel->setText(QString::fromLocal8Bit("<a style='color: green;' href = https://launchpad.net/youker-assistant> home page</a>"));

    QVBoxLayout *v_layout = new QVBoxLayout();
    v_layout->addWidget(nameLabel);
    v_layout->addWidget(versionLabel);
    QHBoxLayout *h_layout = new QHBoxLayout();
    h_layout->addWidget(iconLabel, 0, Qt::AlignVCenter);
    h_layout->addStretch();
    h_layout->addLayout(v_layout);
    h_layout->addStretch();
    h_layout->addWidget(linkLabel, 0, Qt::AlignVCenter);
    h_layout->setContentsMargins(10, 0, 10, 0);

    aboutBtn = new QPushButton();
    aboutBtn->setText(tr("About"));
    contributorBtn = new QPushButton();
    contributorBtn->setText(tr("Contributor"));

    aboutIndicator = new QLabel();
    aboutIndicator->setFixedSize(53, 5);
    contributorIndicator = new QLabel();
    contributorIndicator->setFixedSize(53, 5);
    aboutIndicator->setStyleSheet("QLabel{background-image:url('://res/indicator.png');background-position:center;}");
    contributorIndicator->setStyleSheet("QLabel{background-image:url('://res/indicator.png');background-position:center;}");
    contributorIndicator->hide();

    QVBoxLayout *about_layout = new QVBoxLayout();
    about_layout->addWidget(aboutBtn, 0, Qt::AlignHCenter);
    about_layout->addWidget(aboutIndicator, 0, Qt::AlignHCenter);
    QVBoxLayout *contri_layout = new QVBoxLayout();
    contri_layout->addWidget(contributorBtn, 0, Qt::AlignHCenter);
    contri_layout->addWidget(contributorIndicator, 0, Qt::AlignHCenter);

    QHBoxLayout *btn_layout = new QHBoxLayout();
    btn_layout->addLayout(about_layout);
    btn_layout->addLayout(contri_layout);
    btn_layout->addStretch();
    btn_layout->setSpacing(5);
    btn_layout->setContentsMargins(20, 0, 0, 0);

    aboutEdit = new QTextEdit();
    contributorEdit = new QTextEdit();
    aboutEdit->setFixedSize(500, 230);
    contributorEdit->setFixedSize(500, 230);
    aboutEdit->setReadOnly(true);
    contributorEdit->setReadOnly(true);
    aboutEdit->setText(tr("      Youker Assistant is a powerful system supporting software which is developed by Ubuntu Kylin team. Mainly for the naive user, it can help users manage the system. At present, It provides system junk scanning and cleaning, viewing the system hardware and software information , system customization, task manager, monitoring ball, and some other functions. \n      The software is still under development. Please visit www.ubuntukylin.com for more information. Welcome everyone to join with us. youker-assistant Homepage: https://launchpad.net/youker-assistant."));
    contributorEdit->setText(tr("Maintainer:\nUbuntu Kylin Team <ubuntukylin-members@list.launchpad.net>"));
    contributorEdit->hide();

    QHBoxLayout *edit_layout = new QHBoxLayout();
    edit_layout->addWidget(aboutEdit);
    edit_layout->addWidget(contributorEdit);
    edit_layout->setContentsMargins(20, 0, 20, 0);

    aboutBtn->setFocusPolicy(Qt::NoFocus);
    aboutBtn->setObjectName("transparentButton");
    contributorBtn->setFocusPolicy(Qt::NoFocus);
    contributorBtn->setObjectName("transparentButton");
    aboutBtn->setFixedWidth(100);
    contributorBtn->setFixedWidth(100);
    aboutBtn->setStyleSheet("QPushButton{background:transparent;text-align:center;font-family: 方正黑体_GBK;font-size:14px;color:#666666;}QPushButton:hover{color:#0396DC;}");
    contributorBtn->setStyleSheet("QPushButton{background:transparent;text-align:center;font-family: 方正黑体_GBK;font-size:14px;color:#666666;}QPushButton:hover{color:#0396DC;}");

    aboutEdit->setStyleSheet("QLineEdit{border:1px solid #bebebe;}");
    contributorEdit->setStyleSheet("QLineEdit{border:1px solid #bebebe;}");

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(title_bar);
    layout->addLayout(h_layout);
    layout->addLayout(btn_layout);
    layout->addLayout(edit_layout);
    layout->addStretch();
    layout->setMargin(0);
    layout->setSpacing(5);
    layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(layout);

    this->initConnect();
}

AboutDialog::~AboutDialog()
{

}

void AboutDialog::initConnect()
{
    connect(aboutBtn, SIGNAL(clicked()), this, SLOT(onAboutBtnClicked()));
    connect(contributorBtn, SIGNAL(clicked()), this, SLOT(onContributorBtnClicked()));
    connect(title_bar,SIGNAL(closeDialog()), this, SLOT(onCloseBtnClicked()));
    connect(linkLabel,SIGNAL(linkActivated(QString)),this,SLOT(openUrl(QString)));
}

void AboutDialog::onAboutBtnClicked()
{
    aboutEdit->show();
    aboutIndicator->show();
    contributorEdit->hide();
    contributorIndicator->hide();
}

void AboutDialog::onContributorBtnClicked()
{
    contributorEdit->show();
    contributorIndicator->show();
    aboutEdit->hide();
    aboutIndicator->hide();
}

void AboutDialog::resetTitleSkin(QString skin)
{
    title_bar->resetBackground(skin);
}

void AboutDialog::onCloseBtnClicked()
{
    this->close();
}

void AboutDialog::openUrl(QString url)
{
    QDesktopServices::openUrl(QUrl(url));
}
