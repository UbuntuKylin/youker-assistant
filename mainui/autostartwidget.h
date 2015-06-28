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

#ifndef AUTOSTARTWIDGET_H
#define AUTOSTARTWIDGET_H

#include <QWidget>
#include <QDialog>
#include "../component/kylinlistwidget.h"
#include "../component/kylintitlebar.h"
#include "../component/autogroup.h"

class SessionDispatcher;

namespace Ui {
class AutoStartWidget;
}

class AutoStartWidget : public QDialog//QWidget
{
    Q_OBJECT

public:
//    explicit AutoStartWidget(QWidget *parent = 0, SessionDispatcher *proxy = 0);
    explicit AutoStartWidget(QDialog *parent = 0, SessionDispatcher *proxy = 0, QString skin = ":/background/res/skin/1.png");
    ~AutoStartWidget();
    void initConnect();
    void initData();
    void scanAllSwitcher();
    void resetTitleSkin(QString skin);

public slots:
    void onCloseButtonClicked();
//    void onMinButtonClicked();
    void setCurrentItemAutoStatus(QString dekstopName);
    void readyReciveData(const QStringList &data);
    void readyShowUI();

private:
    void initTitleBar(QString skin);

private:
    Ui::AutoStartWidget *ui;
    SessionDispatcher *sessionproxy;
    QList<QStringList> data_list;
    QList<AutoGroup *> switcher_list;
    KylinTitleBar *title_bar;
    QLabel *tip_label;
    QLabel *num_label;
    QLabel *on_label;
    QLabel *on_num_label;
    QLabel *off_label;
    QLabel *off_num_label;
    QLabel *name_label;
    QLabel *status_label;
    int onNum;
    int offNum;
};

#endif // AUTOSTARTWIDGET_H
