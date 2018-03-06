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

#include "networkwidget.h"
#include "networkflow.h"

#include <QDebug>
#include <QPainter>
#include <QApplication>
#include <QButtonGroup>

NetworkWidget::NetworkWidget(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QWidget *w = new QWidget;
    m_widgetLayout = new QVBoxLayout(w);
    m_widgetLayout->setContentsMargins(6, 0, 0, 0);
    m_widgetLayout->setSpacing(0);

    m_title = new QLabel(tr("Network"));
    m_title->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_title->setStyleSheet("background:transparent;font-size:24px;color:#000000");
    /*QFont font = m_title->font();
    font.setPointSize(24);
    font.setWeight(QFont::Light);
    m_title->setFont(font);*/

    m_networkFlow = new NetworkFlow;

    m_widgetLayout->addWidget(m_title);
    m_widgetLayout->addWidget(m_networkFlow);

    mainLayout->addWidget(w, 0, Qt::AlignCenter);

//    math1_radio = new QRadioButton();
//    math2_radio = new QRadioButton();
//    math1_radio->setFocusPolicy(Qt::NoFocus);
//    math1_radio->setObjectName("math1");
//    math2_radio->setFocusPolicy(Qt::NoFocus);
//    math2_radio->setObjectName("math2");
//    math1_radio->setChecked(false);
//    math2_radio->setChecked(true);
//    math1_radio->move(10,10);
//    math2_radio->move(100,10);
//    connect(math1_radio, SIGNAL(clicked()), this, SLOT(setRadioButtonRowStatus()));
//    connect(math2_radio, SIGNAL(clicked()), this, SLOT(setRadioButtonRowStatus()));
}

NetworkWidget::~NetworkWidget()
{
    delete m_title;
    delete m_networkFlow;
    QLayoutItem *child;
    while ((child = m_widgetLayout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }
    delete mainLayout;
}

void NetworkWidget::setRadioButtonRowStatus()
{
    QObject *obj = sender(); //返回发出信号的对象，用QObject类型接收
    QRadioButton* pbtn = qobject_cast<QRadioButton*>(obj);
    QString obj_name = pbtn->objectName();
    if(obj_name == "math1")
    {

    }
    else if(obj_name == "math2")
    {

    }
}

void NetworkWidget::onUpdateNetworkStatus(long recvTotalBytes, long sentTotalBytes, long recvRateBytes, long sentRateBytes)
{
    m_networkFlow->onUpdateNetworkStatus(recvTotalBytes, sentTotalBytes, recvRateBytes, sentRateBytes);
}
