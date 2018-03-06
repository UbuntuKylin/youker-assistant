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

#ifndef CLEANERWIDGET_H
#define CLEANERWIDGET_H

#include <QWidget>
#include "../cleaner/cleanermainwidget.h"
#include "../cleaner/cleanerdetailwidget.h"
#include <QStackedWidget>

class Toolkits;
class MainWindow;

class CleanerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CleanerWidget(QWidget *parent = 0);
    ~CleanerWidget();
    void setParentWindow(MainWindow* window) { p_mainwindow = window;}
    void setToolKits(Toolkits* kits) { toolKits = kits;}
    void initUI(QString skin);
    void resetSkin(QString skin);

public slots:
    void displayDetailPage();
    void displayMainPage();

signals:
    void transCleanSignal();
    void transScanSignal();
    void tranActionAnimaitonSignal();
//    void tranCleanActionAnimaitonSignal();
    void tranScanOverSignal(bool status);

    void tellCleanerDetailData(const QStringList &data);
    void tellCleanerDetailStatus(const QString &status);

    void startScanSystem(QMap<QString, QVariant> itemsMap);
    void startCleanSystem(QMap<QString, QVariant> itemsMap);


private:
    QStackedWidget *statked_widget;
    CleanerMainWidget *main_widget;
    CleanerDetailWidget *detail_widget;
    MainWindow *p_mainwindow;
    Toolkits *toolKits;
};

#endif // CLEANERWIDGET_H
