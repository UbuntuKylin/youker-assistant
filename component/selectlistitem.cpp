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

#include "selectlistitem.h"

SelectListItem::SelectListItem(QWidget *parent, QString description, QString tipMsg, bool hasTip, int itemWidth) :
    QWidget(parent)
    , m_description(description)
    , m_tip(tipMsg)
    , m_hasTip(hasTip)
{
    this->setStyleSheet("QWidget{padding: 2px 0;} QWidget:hover{background-color:rgba(43,182,234,0.1);border-radius:2px;}");//#2bb6ea
    this->setFixedHeight(30);

    m_mainLayout = new QHBoxLayout(this);
    m_mainLayout->setSpacing(0);
    m_mainLayout->setMargin(0);
    m_mainLayout->setContentsMargins(0,0,0,0);

    m_checkBox = new QCheckBox(this);
    m_checkBox->setFixedSize(20, 13);
    m_checkBox->setFocusPolicy(Qt::NoFocus);
    m_checkBox->setChecked(true);

    connect(m_checkBox, &QCheckBox::clicked, [=] (bool checked) {
        emit this->selectedSignal(checked, this->itemDescription());
    });

    int maxWidth = itemWidth - m_checkBox->width();
    m_descLabel = new QLabel(this);
    m_descLabel->setFixedWidth(maxWidth);

    QFont ft;
    QFontMetrics fm(ft);
    QString elided_text = fm.elidedText(description, Qt::ElideMiddle, maxWidth);
    m_descLabel->setText(elided_text);

    /*QFont font;
    font.setPixelSize(12);
    const QFontMetrics fm(font);
    QString msg = fm.elidedText(description, Qt::ElideMiddle, maxWidth);
//    m_descLabel->setWordWrap(true);
    m_descLabel->setText(msg);*/

    m_mainLayout->setAlignment(Qt::AlignLeft);
    m_mainLayout->addWidget(m_checkBox, 0, Qt::AlignLeft | Qt::AlignVCenter);
    m_mainLayout->addWidget(m_descLabel, 0, Qt::AlignLeft | Qt::AlignVCenter);
}

SelectListItem::~SelectListItem()
{

}

bool SelectListItem::itemIsChecked()
{
    return m_checkBox->isChecked();
}

QString SelectListItem::itemDescription()
{
    if (m_hasTip)
        return this->m_tip;
    else
        return this->m_description;
}
