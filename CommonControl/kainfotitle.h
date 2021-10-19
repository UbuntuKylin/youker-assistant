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

#ifndef KAINFOTITLE_H
#define KAINFOTITLE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>

class KAInfoTitle : public QWidget
{
    Q_OBJECT
public:
    explicit KAInfoTitle(QString strTitle = "", QWidget *parent = nullptr);
    void setText(QString strTitle);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QHBoxLayout *m_mainLayout = nullptr;
    QLabel *m_labelTitle = nullptr;
    QString m_strTitle;
};

#endif // KAINFOTITLE_H
