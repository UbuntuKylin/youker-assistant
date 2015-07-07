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

#ifndef CLEANSUBGROUP_H
#define CLEANSUBGROUP_H

#include <QWidget>
class QLabel;
class QPushButton;
class CleanSubButton;

class CleanSubGroup : public QWidget
{
    Q_OBJECT
public:
    explicit CleanSubGroup(QWidget *parent = 0, const QString &picture= "");
    ~CleanSubGroup();
    void setLabelText(const QString &title, int count);
    void setLabelStringText(const QString &title, QString size);
    int getCheckBoxStatus();
    void initConnect();
    void hideCustomButton();

public slots:
    void onZoneClicked();
    void resetMainStatus(int status);

signals:
    void clicked();
    void customButtonClicked();
    void spreadStatus(int status);

private:
    CleanSubButton *img_btn;
    QLabel *name_label;
    QLabel *description_label;
    QPushButton *custom_btn;
    int tristateStatus;
};

#endif // CLEANSUBGROUP_H
