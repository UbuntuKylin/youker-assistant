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

#ifndef INFOITEMLINE_H
#define INFOITEMLINE_H

#include <QLabel>

class QRadioButton;

class InfoItemLine : public QFrame
{
    Q_OBJECT

public:
    explicit InfoItemLine(QFrame *parent = 0);
    ~InfoItemLine();

    void setInfoKey(const QString &key);
    void setInfoValue(const QString &value);

    QString getLineKey();

signals:
    void clicked(const QString &context) const;

private:
    QLabel *m_keyLabel = nullptr;
    QLabel *m_valueLabel = nullptr;
    QString m_key;
    int keyWidth;
};

#endif // INFOITEMLINE_H
