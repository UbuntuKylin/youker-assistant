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

#include "kalabel.h"

#include "utils.h"

KALabel::KALabel(QWidget *parent)
    : QLabel(parent)
{
    m_strText = "";
}

KALabel::KALabel(QString strText, QWidget *parent)
    : QLabel(strText, parent)
{
    m_strText = strText;
}

void KALabel::setText(const QString &strText)
{
    m_strText = strText;
    QLabel::setText(strText);
}

void KALabel::paintEvent(QPaintEvent *event)
{
    QString strEText = getElidedText(font(), m_strText, width());
    if (strEText != m_strText) {
        QLabel::setText(strEText);
        setToolTip(m_strText);
    } else {
        QLabel::setText(m_strText);
        setToolTip("");
    }
    QLabel::paintEvent(event);
}
