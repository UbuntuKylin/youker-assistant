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

#include "kaslider.h"

#include <QStyle>
#include <QPainter>
#include <QStyleOptionSlider>
#include <QDebug>
#include <QPalette>
#include <QPainterPath>

KASlider::KASlider(QStringList listValues, QWidget *parent)
    : QSlider(Qt::Horizontal, parent)
    , m_listValues(listValues)
{
    this->setFixedHeight(64);
    this->setContentsMargins(0,24,0,0);
}

void KASlider::paintEvent(QPaintEvent *ev)
{
    QSlider::paintEvent(ev);

    auto painter = new QPainter(this);
    painter->setBrush(QBrush(QColor(QPalette::Base)));

    int nCurPos = (value() - minimum())/tickInterval();
    if (nCurPos < m_listValues.size()) {
        auto rect = this->geometry();
        int numTicks = (maximum() - minimum()) / tickInterval();
        if (this->orientation() == Qt::Horizontal) {
            QFontMetrics fontMetrics = QFontMetrics(this->font());
            QRect fontRect = fontMetrics.boundingRect(m_listValues.at(nCurPos));
            const int interval = (rect.width() - fontRect.width()) / numTicks;
            int tickX = 1+(interval*nCurPos);
            int tickY = rect.height() / 2 - 16;
            painter->drawText(QPoint(tickX, tickY),
                              this->m_listValues.at(nCurPos));
        }
    }
    painter->end();
}

QStringList KASlider::valueList()
{
    return m_listValues;
}

void KASlider::setValueList(QStringList listValues)
{
    m_listValues = listValues;
    repaint();
}
