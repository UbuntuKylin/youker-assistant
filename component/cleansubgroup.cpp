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

#include "cleansubgroup.h"
#include "cleansubbutton.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFontMetrics>

CleanSubGroup::CleanSubGroup(QWidget *parent, const QString &picture) :
    QWidget(parent), tristateStatus(2)
{
    this->setStyleSheet("QWidget{background:transparent;}");
//    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedSize(160, 110);
    this->setFocusPolicy(Qt::NoFocus);
    img_btn = new CleanSubButton();
//    img_btn->setAttribute(Qt::WA_TransparentForMouseEvents);//屏蔽鼠标事件
    img_btn->setIconPath(picture);
    img_btn->setCheckboxStatus(tristateStatus);//全选状态
    img_btn->setFocusPolicy(Qt::NoFocus);

    name_label = new QLabel();
    description_label = new QLabel();
    name_label->setObjectName("smallgrayLabel");
    name_label->setAlignment(Qt::AlignCenter);
    description_label->setAlignment(Qt::AlignCenter);
    description_label->setObjectName("smallgrayLabel");

    custom_btn = new QPushButton();
    custom_btn->setFocusPolicy(Qt::NoFocus);
    custom_btn->setObjectName("checkButton");
    custom_btn->setCursor(Qt::PointingHandCursor);
    custom_btn->setFixedSize(91, 25);
    custom_btn->setText(tr("Custom"));

//    QVBoxLayout *main_layout = new QVBoxLayout();
//    main_layout->addWidget(img_btn, 0, Qt::AlignHCenter);
//    main_layout->addWidget(name_label, 0, Qt::AlignHCenter);
//    main_layout->addWidget(description_label, 0, Qt::AlignHCenter);
//    main_layout->setSpacing(5);
//    main_layout->setMargin(0);
//    main_layout->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *h_layout = new QHBoxLayout();
    h_layout->addStretch();
    h_layout->addWidget(name_label);
    h_layout->addWidget(description_label);
    h_layout->addStretch();

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addWidget(img_btn, 0, Qt::AlignHCenter);
    main_layout->addLayout(h_layout);
    main_layout->addWidget(custom_btn,0, Qt::AlignHCenter);
    main_layout->setSpacing(5);
    main_layout->setMargin(0);
    main_layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(main_layout);

    this->initConnect();
}

CleanSubGroup::~CleanSubGroup()
{
    if(img_btn != NULL)
    {
        delete img_btn;
        img_btn = NULL;
    }
    if(name_label != NULL)
    {
        delete name_label;
        name_label = NULL;
    }
    if(description_label != NULL)
    {
        delete description_label;
        description_label = NULL;
    }
    if(custom_btn != NULL)
    {
        delete custom_btn;
        custom_btn = NULL;
    }
}

void CleanSubGroup::initConnect()
{
    connect(img_btn, SIGNAL(clicked()), this, SLOT(onZoneClicked()));
    connect(custom_btn, SIGNAL(clicked()), this, SIGNAL(customButtonClicked()));
}

void CleanSubGroup::setLabelText(const QString &title, int count)
{
    QFont ft;
    QFontMetrics fm(ft);
    QString elided_text = fm.elidedText(title, Qt::ElideRight, 80);
    name_label->setText(elided_text);
    description_label->setText(QString::number(count));
    if(elided_text.endsWith("…"))
        name_label->setToolTip(title + QString::number(count));
}

void CleanSubGroup::setLabelStringText(const QString &title, QString size)
{
    QFont ft;
    QFontMetrics fm(ft);
    QString elided_text = fm.elidedText(title, Qt::ElideRight, 80);
    name_label->setText(elided_text);
    description_label->setText(size);
    if(elided_text.endsWith("…"))
        name_label->setToolTip(title + size);
}

void CleanSubGroup::hideCustomButton()
{
    custom_btn->hide();
}

void CleanSubGroup::onZoneClicked()
{
    if(tristateStatus == 0) {
        tristateStatus = 2;
        img_btn->setCheckboxStatus(2);
        emit this->spreadStatus(2);
    }
    else if(tristateStatus == 1) {
        tristateStatus = 2;
        img_btn->setCheckboxStatus(2);
        emit this->spreadStatus(2);
    }
    else if(tristateStatus == 2) {
        tristateStatus = 0;
        img_btn->setCheckboxStatus(0);
        emit this->spreadStatus(0);
    }
}

//sub item's change to make it work
void CleanSubGroup::resetMainStatus(int status)
{
    tristateStatus = status;
    if(status == 0) {
        img_btn->setCheckboxStatus(0);
    }
    else if(status == 1) {
        img_btn->setCheckboxStatus(1);
    }
    else if(status == 2) {
        img_btn->setCheckboxStatus(2);
    }
}

int CleanSubGroup::getCheckBoxStatus()
{
    return tristateStatus;
}
