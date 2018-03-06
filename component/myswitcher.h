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

#ifndef MYSWITCHER_H
#define MYSWITCHER_H

#include <QFrame>
#include <QPixmap>

class MySwitcher : public QFrame
{
    Q_OBJECT

public:
    explicit MySwitcher(QWidget *parent = 0);

    bool isOn() const;

public slots:
    void setOnStatus(bool b);

signals:
    void statusChanged(bool b);

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    bool m_isOn;
    QPixmap m_onImage;
    QPixmap m_offImage;
};

#endif // MYSWITCHER_H
