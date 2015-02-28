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

#include "cameramanager.h"
#include "mainwindow.h"
#include <QDebug>
#include <QVBoxLayout>
#include "../dbusproxy/youkersessiondbus.h"

CameraManager::CameraManager(QWidget *parent, SessionDispatcher *proxy)
:QDialog(parent),sessionproxy(proxy)
{

//    m_Dlg.setupUi(this);
    this->setFixedSize(500, 271);
    setWindowFlags(Qt::FramelessWindowHint);

    title_bar = new KylinTitleBar();
    initTitleBar();
    msg_label = new QLabel();
    msg_label->setWordWrap(true);//QLabel自动换行
    msg_label->setFixedWidth(480);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::red);
    msg_label->setPalette(pa);

    msg_label->hide();
    tip_label = new QLabel();
    tip_label->setWordWrap(true);//QLabel自动换行
    tip_label->setFixedWidth(480);
    description_label = new QLabel();
    description_label->setWordWrap(true);//QLabel自动换行
    description_label->setFixedWidth(480);

    okBtn = new QPushButton();
    viewBtn = new QPushButton();
    okBtn->setFixedSize(91, 25);
    okBtn->setObjectName("blackButton");
    okBtn->setFocusPolicy(Qt::NoFocus);
    viewBtn->setFixedSize(91, 25);
    viewBtn->setObjectName("blackButton");
    viewBtn->setFocusPolicy(Qt::NoFocus);

    QHBoxLayout *h_layout = new QHBoxLayout();
    h_layout->addStretch();
    h_layout->addWidget(okBtn);
    h_layout->addWidget(viewBtn);
    h_layout->addStretch();
    h_layout->setSpacing(50);
    h_layout->setMargin(0);
    h_layout->setContentsMargins(0,0,0,0);

    QVBoxLayout *v_layout  = new QVBoxLayout();
    v_layout->addWidget(msg_label);
    v_layout->addWidget(tip_label);
    v_layout->addWidget(description_label);
    v_layout->addLayout(h_layout);
    v_layout->setSpacing(30);
    v_layout->setMargin(0);
    v_layout->setContentsMargins(10, 40, 10, 0);

    QVBoxLayout *main_layout  = new QVBoxLayout();
    main_layout->addWidget(title_bar);
    main_layout->addLayout(v_layout);
    main_layout->addStretch();
    main_layout->setSpacing(0);
    main_layout->setMargin(0);
    main_layout->setContentsMargins(0, 0, 0, 0);
    setLayout(main_layout);
    this->setLanguage();
    this->initConnect();
}

CameraManager::~CameraManager()
{
}

void CameraManager::setLanguage()
{
    msg_label->setText(tr("NO found camara"));
    tip_label->setText(tr("An application to take pictures with the device camera."));
    description_label->setText(tr("Press the [ESC] button to take picture and turn the camera off , the photo saved in home directory by default."));
    okBtn->setText(tr("Open camera"));
    viewBtn->setText(tr("View Photos"));
}

void CameraManager::setOKButtonEnable(bool enable)
{
    if(enable)
    {
        msg_label->hide();
        okBtn->setEnabled(true);
    }
    else
    {
        msg_label->show();
        okBtn->setEnabled(false);
    }
}

void CameraManager::onOKButtonClicked()
{
    sessionproxy->call_camera_qt();
}

void CameraManager::onViewButtonClicked()
{
    sessionproxy->open_folder_qt(sessionproxy->getHomePath());
}

void CameraManager::initConnect()
{
    connect(title_bar,SIGNAL(closeDialog()), this, SLOT(onCloseButtonClicked()));
    connect(okBtn,SIGNAL(clicked()), this, SLOT(onOKButtonClicked()));
    connect(viewBtn,SIGNAL(clicked()), this, SLOT(onViewButtonClicked()));
}

void CameraManager::onCloseButtonClicked()
{
    this->close();
}

void CameraManager::initTitleBar()
{
    title_bar->setTitleWidth(500);
    title_bar->setTitleName(tr("Camera Manager"));
    title_bar->setTitleBackgound(":/background/res/skin/1.png");
}
