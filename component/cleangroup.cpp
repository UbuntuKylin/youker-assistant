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

#include "cleangroup.h"
#include "cleanbutton.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QFontMetrics>

CleanGroup::CleanGroup(QWidget *parent, const QString &picture) :
    QWidget(parent), tristateStatus(2)
{
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedSize(260, 150);
    this->setFocusPolicy(Qt::NoFocus);
    img_btn = new CleanButton();
//    img_btn->setAttribute(Qt::WA_TransparentForMouseEvents);//屏蔽鼠标事件
    connect(img_btn, SIGNAL(clicked()),this, SIGNAL(clicked()));
    img_btn->setIconPath(picture);
    img_btn->setCheckboxStatus(tristateStatus);//全选状态
    img_btn->setFocusPolicy(Qt::NoFocus);

    name_label = new QLabel();
    description_label = new QLabel();
    name_label->setObjectName("middleblackLabel");
    name_label->setAlignment(Qt::AlignCenter);
    description_label->setAlignment(Qt::AlignCenter);
    description_label->setObjectName("smallgrayLabel");

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addWidget(img_btn, 0, Qt::AlignHCenter);
    main_layout->addWidget(name_label, 0, Qt::AlignHCenter);
    main_layout->addWidget(description_label, 0, Qt::AlignHCenter);
    main_layout->setSpacing(5);
    main_layout->setMargin(0);
    main_layout->setContentsMargins(0, 0, 0, 0);

    this->setLayout(main_layout);
}

CleanGroup::~CleanGroup()
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
}

void CleanGroup::setLabelText(const QString &name, const QString &desc)
{
    QFont ft;
    QFontMetrics fm(ft);
    QString elided_text = fm.elidedText(name, Qt::ElideRight, 260);
    name_label->setText(elided_text);
    elided_text = fm.elidedText(desc, Qt::ElideRight, 260);
    description_label->setText(elided_text);
    if(elided_text.endsWith("…"))
        description_label->setToolTip(desc);
}

//sub item's change to make it work
void CleanGroup::resetMainStatus(int status)
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

int CleanGroup::getCheckBoxStatus()
{
    return tristateStatus;
}
