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

#include "myswitcher.h"

#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QDebug>

MySwitcher::MySwitcher(QWidget *parent) :
    QFrame(parent),
    m_isOn(false)
{
    this->setFixedSize(76, 29);
    m_offImage.load("://res/off.png");
    m_onImage.load("://res/on.png");
}

bool MySwitcher::isOn() const
{
    return m_isOn;
}

void MySwitcher::setOnStatus(bool b)
{
    if (m_isOn != b) {
        m_isOn = b;
        emit this->statusChanged(b);
        this->update();
    }
}

void MySwitcher::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        this->setOnStatus(!m_isOn);
        event->accept();
    }
}

void MySwitcher::paintEvent(QPaintEvent *event)
{
    QPixmap *m_nowImagePix;

    if(this->m_isOn) {
        m_nowImagePix = &m_onImage;
    }
    else {
        m_nowImagePix = &m_offImage;
    }

    if(m_nowImagePix->isNull())
        return;

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing, true);

    QPainterPath path;
    path.addRoundedRect(rect(), m_nowImagePix->height() / 2.0, m_nowImagePix->height() / 2.0);
    path.closeSubpath();

    painter.setClipPath(path);
    painter.drawPixmap(rect(), *m_nowImagePix);
}
