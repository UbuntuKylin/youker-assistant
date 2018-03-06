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

#include "startuptitlewidget.h"
#include "../widgets/mytristatebutton.h"

#include <QApplication>
#include <QDebug>
#include <QHBoxLayout>
#include <QPainter>
#include <QResizeEvent>
#include <QStyleFactory>

StartupTitleWidget::StartupTitleWidget(QWidget *parent)
    :QFrame(parent)
{
    installEventFilter(this);
    setMouseTracking(true);
    setFixedHeight(39);

//    m_topBorderColor = QColor(255, 255, 255, 153);
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor("#0d87ca"));
    this->setPalette(palette);

    initWidgets();
}

StartupTitleWidget::~StartupTitleWidget()
{
    //Segmentation fault
    QLayoutItem *child;
    while ((child = m_lLayout->takeAt(0)) != 0) {
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

/*void StartupTitleWidget::paintEvent(QPaintEvent *e)
{

    QFrame::paintEvent(e);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    const QColor tc(m_topBorderColor);
    int borderHeight = 1;
    QPainterPath tPath;
    tPath.moveTo(QPointF(x(), y() + borderHeight - 0.5));
    tPath.lineTo(QPointF(x() + width(), y() + borderHeight - 0.5));
    p.setPen(QPen(tc));
    p.drawPath(tPath);
}*/

void StartupTitleWidget::initLeftContent()
{
    QWidget *w = new QWidget;
    m_lLayout = new QHBoxLayout(w);
    m_lLayout->setContentsMargins(6, 0, 0, 0);
    m_lLayout->setSpacing(0);

    QLabel *label = new QLabel;
    label->setStyleSheet("QLabel{border-image: url(://res/kylin-assistant.png);}");
    label->setFixedSize(24, 24);
    m_lLayout->addWidget(label);

    QLabel *titleLabel = new QLabel;
    titleLabel->setStyleSheet("QLabel{background-color:transparent;color:#ffffff; font-size:12px;}");
    titleLabel->setText(tr("Kylin Startup Manager"));
    m_lLayout->addSpacing(5);
    m_lLayout->addWidget(titleLabel);

    m_layout->addWidget(w, 1, Qt::AlignLeft);
}

void StartupTitleWidget::initRightContent()
{
    QWidget *w = new QWidget;
    m_rLayout = new QHBoxLayout(w);
    m_rLayout->setContentsMargins(0, 0, 6, 0);
    m_rLayout->setSpacing(0);

    m_layout->addWidget(w, 1, Qt::AlignRight);

    MyTristateButton *minBtn = new MyTristateButton;
    minBtn->setObjectName("MinButton");
    connect(minBtn, SIGNAL(clicked()), this, SLOT(onMinBtnClicked()));
//    connect(minBtn, &MyTristateButton::clicked, this, [=] {
//        if (parentWidget() && parentWidget()->parentWidget()) {
//            parentWidget()->parentWidget()->showMinimized();
//        }
//    });

    MyTristateButton *closeBtn = new MyTristateButton;
    closeBtn->setObjectName("CloseButton");
    connect(closeBtn, SIGNAL(clicked()), this, SLOT(onCloseBtnClicked()));
//    connect(closeBtn, &MyTristateButton::clicked, this, [=] {
//        window()->close();
//    });
    m_rLayout->addWidget(minBtn);
    m_rLayout->addWidget(closeBtn);
}

void StartupTitleWidget::onMinBtnClicked()
{
    if (parentWidget() && parentWidget()->parentWidget()) {
        parentWidget()->parentWidget()->showMinimized();
    }
}
void StartupTitleWidget::onCloseBtnClicked()
{
    window()->close();
}

void StartupTitleWidget::initWidgets()
{
    m_layout = new QHBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);
    this->setLayout(m_layout);

    initLeftContent();
    initRightContent();
}
