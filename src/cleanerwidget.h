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
#include "../cleaner/cleanlistwidget.h"
#include <QStackedWidget>

class Toolkits;
class MainWindow;
class CleandetailVeiw;

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

    void paintEvent(QPaintEvent *);

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

    //add by tangguang 2020.05.14========
    void startOneKeyScan(const QStringList &categorys);
    void isScanning(QString msg);
    void finishScanWork(QString msg);
    void tellScanResult(QString flag, QString msg);
    void startOneKeyClean();

    void finishCleanWorkMain(QString msg);

    void tellCleanerMainData(const QStringList &data);
    void tellCleanerMainStatus(const QString &status, const QString &domain);
    void sendCleanErrorSignal(const QString &status);

    void policykitCleanSignal(bool status);
    void sendCleanOverSignal();
    //===================================
private:
    QStackedWidget *statked_widget;
    CleanerMainWidget *main_widget;
//    CleanerDetailWidget *detail_widget;
    CleandetailVeiw *detailview;
    MainWindow *p_mainwindow;
    Toolkits *toolKits;
};

#endif // CLEANERWIDGET_H
