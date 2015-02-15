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

#ifndef KYLINCHECKBOX_H
#define KYLINCHECKBOX_H

#include <QWidget>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
//#include <QMouseEvent>
//#include <QHBoxLayout>
//#include <QSignalMapper>
//#include <QVBoxLayout>
//#include "../component/kylinbutton.h"
//#include "../component/kylintoolbutton.h"
//#include "../component/systembutton.h"
//#include "../component/loadinglabel.h"

//class MainWindow;

class KylinCheckBox : public QWidget
{
    Q_OBJECT
public:
    explicit KylinCheckBox(QWidget *parent = 0, const QString &picture= "");
    ~KylinCheckBox();
//    void setParentWindow(MainWindow* window) { p_mainwindow = window;}
    void initConnect();
    void setLabelText(const QString &name, const QString &tip);

public slots:
    void onZoneClicked();
    void resetMainStatus(int status);

signals:
    void customButtonClicked();
    void spreadStatus(int status);

private:
    QPushButton *img_btn;
    QCheckBox *checkbox;
    QLabel *name_label;
    QLabel *description_label;
//    QPushButton *custom_btn;

//    MainWindow *p_mainwindow;
};

#endif // KYLINCHECKBOX_H
