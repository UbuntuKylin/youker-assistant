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

#ifndef CLEANGROUP_H
#define CLEANGROUP_H

#include <QWidget>
class QLabel;
class CleanButton;

class CleanGroup : public QWidget
{
    Q_OBJECT
public:
    explicit CleanGroup(QWidget *parent = 0, const QString &picture= "");
    ~CleanGroup();
    void setLabelText(const QString &name, const QString &desc);
    int getCheckBoxStatus();

public slots:
    void resetMainStatus(int status);

signals:
    void clicked();

private:
    CleanButton *img_btn;
    QLabel *name_label;
    QLabel *description_label;
    int tristateStatus;
};

#endif // CLEANGROUP_H
