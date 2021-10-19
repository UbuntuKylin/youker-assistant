/*
 * Copyright (C) 2021 KylinSoft Co., Ltd.
 *
 * Authors:
 *  Yang Min yangmin@kylinos.cn
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "kainfotitle.h"

#include <QPainterPath>
#include <QPainter>

#define KATITLE_LABEL_WIDTH 4
#define KATITLE_LABEL_HEIGHT 14

KAInfoTitle::KAInfoTitle(QString strTitle, QWidget *parent)
    : QWidget(parent)
    , m_strTitle(strTitle)
{
    this->setAttribute(Qt::WA_TranslucentBackground);

    m_mainLayout = new QHBoxLayout();
    m_mainLayout->setContentsMargins(0,0,0,0);

    m_labelTitle = new QLabel();
    m_labelTitle->setText(m_strTitle);
    m_mainLayout->addSpacing(KATITLE_LABEL_WIDTH+8);
    m_mainLayout->addWidget(m_labelTitle, 0, Qt::AlignLeft);

    this->setLayout(m_mainLayout);
}

void KAInfoTitle::setText(QString strTitle)
{
    m_strTitle = strTitle;
    m_labelTitle->setText(m_strTitle);
}

void KAInfoTitle::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainterPath path;

    QPainter painter(this);
    painter.setOpacity(1);
    painter.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    painter.setClipping(true);
    painter.setPen(Qt::transparent);

    /*path.addRect(this->rect());
    path.setFillRule(Qt::WindingFill);
    painter.setBrush(this->palette().base());
    painter.setPen(Qt::transparent);

    painter.drawPath(path);*/
    // 画小块
    QRect rectBlue = this->rect();
    int nX = 0;
    int nY = 0;
    int nWidth = 0;
    int nHeight = 0;
    if (KATITLE_LABEL_WIDTH > rectBlue.width()) {
        nX = rectBlue.x();
        nWidth = rectBlue.width();
    } else {
        nX = rectBlue.x();
        nWidth = KATITLE_LABEL_WIDTH;
    }
    if (KATITLE_LABEL_HEIGHT > rectBlue.height()) {
        nY = rectBlue.y();
        nHeight = rectBlue.height();
    } else {
        nY = rectBlue.y()+(rectBlue.height()-KATITLE_LABEL_HEIGHT)/2;
        nHeight = KATITLE_LABEL_HEIGHT;
    }
    rectBlue.setX(nX);
    rectBlue.setY(nY);
    rectBlue.setWidth(nWidth);
    rectBlue.setHeight(nHeight);
    QPainterPath path1;
    path1.addRect(rectBlue);
    path1.setFillRule(Qt::WindingFill);
    painter.setBrush(QColor("#3790FA"));
    painter.setPen(Qt::transparent);

    painter.drawPath(path1);
}
