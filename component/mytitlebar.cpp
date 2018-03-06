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

#include "mytitlebar.h"
#include "utils.h"
#include "../../plugins/widgets/mytristatebutton.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>

MyTitleBar::MyTitleBar(const QString &title, bool needMin, QWidget *parent)
    :QFrame(parent)
    , m_title(title)
    , m_needMin(needMin)
{
    this->setWindowFlags(Qt::FramelessWindowHint);//this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint  | Qt::WindowCloseButtonHint);
//    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);//Attention: Qt::WindowCloseButtonHint make showMinimized() valid

    this->setMouseTracking(true);
    this->setFixedHeight(TITLE_BAR_HEIGHT);

    this->setAutoFillBackground(true);
//    this->setAttribute(Qt::WA_TranslucentBackground);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor("#0d87ca"));
    this->setPalette(palette);

    initWidgets();
}

MyTitleBar::~MyTitleBar()
{
    QLayoutItem *child;
    while ((child = m_lLayout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }
    while ((child = m_mLayout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }
    while ((child = m_rLayout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }
    delete m_layout;
}

void MyTitleBar::setLeftContent(QWidget *content)
{
    QLayoutItem *child;
    while ((child = m_lLayout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }

    m_lLayout->addWidget(content);
}

void MyTitleBar::setMiddleContent(QWidget *content)
{
    QLayoutItem *child;
    while ((child = m_mLayout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }

    m_mLayout->addWidget(content);
}


void MyTitleBar::initLeftContent()
{
    QWidget *w = new QWidget;
    m_lLayout = new QHBoxLayout(w);
    m_lLayout->setContentsMargins(6, 0, 0, 0);
    m_lLayout->setSpacing(0);

    QLabel *titleLabel = new QLabel;
    titleLabel->setStyleSheet("QLabel{background-color:transparent;color:#ffffff; font-size:12px;}");
    titleLabel->setText(m_title);
    m_lLayout->addWidget(titleLabel);

    m_layout->addWidget(w, 1, Qt::AlignLeft);
}

void MyTitleBar::initMiddleContent()
{
    QWidget *w = new QWidget;
    w->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_mLayout = new QHBoxLayout(w);
    m_mLayout->setContentsMargins(0, 0, 0, 0);
    m_mLayout->setSpacing(0);

    m_layout->addWidget(w);
}

void MyTitleBar::initRightContent()
{
    QWidget *w = new QWidget;
    m_rLayout = new QHBoxLayout(w);
    m_rLayout->setContentsMargins(0, 0, 0, 0);
    m_rLayout->setSpacing(0);

    m_layout->addWidget(w, 1, Qt::AlignRight);

    if (m_needMin) {
        MyTristateButton *minBtn = new MyTristateButton;
        minBtn->setObjectName("MinButton");
        connect(minBtn, SIGNAL(clicked()), this, SIGNAL(minSignal()));
        m_rLayout->addWidget(minBtn);
    }

    MyTristateButton *closeBtn = new MyTristateButton;
    closeBtn->setObjectName("CloseButton");
    connect(closeBtn, SIGNAL(clicked()), this, SIGNAL(closeSignal()));
    m_rLayout->addWidget(closeBtn);
}

void MyTitleBar::initWidgets()
{
    m_layout = new QHBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);

    initLeftContent();
    initMiddleContent();
    initRightContent();
}
