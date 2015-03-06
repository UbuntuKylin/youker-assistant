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

#ifndef CLEANERDETAILWIDGET_H
#define CLEANERDETAILWIDGET_H

#include <QWidget>
#include "cleaneritems.h"
#include "cleanlistwidget.h"

class QLabel;
class QBoxLayout;
class QHBoxLayout;
class QGridLayout;
class SessionDispatcher;
class SystemDispatcher;
class Toolkits;
class MainWindow;
class CleanSubGroup;

namespace Ui {
class CleanerDetailWidget;
}

class CleanerDetailWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CleanerDetailWidget(QWidget *parent = 0, SessionDispatcher *seroxy = 0, SystemDispatcher *syproxy = 0, MainWindow *window = 0, Toolkits *kits = 0);
    ~CleanerDetailWidget();
    void setUIData();
    void setLanguage();
    void initConnect();
    void getAllSelectedItems();

public slots:
    void showCustomPage();
    void showReciveData(const QStringList &data);
    void receiveCleanSignal();
    void showReciveStatus(const QString &status);
    void CleanUIAndData();
//    void receivePolicyKitSignal(bool status);

signals:
    void notifyMainCheckBox(int status);
//    void showActionAnimaiton();

private:
    void initTitleBar();

private:
    Ui::CleanerDetailWidget *ui;
    MainWindow *parentWindow;
    SessionDispatcher *sessionproxy;
    SystemDispatcher *systemproxy;
    Toolkits *toolKits;
    QMap<QString, QVariant> argsData;
    CleanListWidget *cache_apt_items ;
    CleanSubGroup *cache_apt_btn;
    CleanListWidget *cache_software_items ;
    CleanSubGroup *cache_software_btn;
    CleanListWidget *cache_thumbnails_items ;
    CleanSubGroup *cache_thumbnails_btn;
    CleanListWidget *cache_firefox_items ;
    CleanSubGroup *cache_firefox_btn;
    CleanListWidget *cache_chromium_items ;
    CleanSubGroup *cache_chromium_btn;

    CleanListWidget *package_unneed_items ;
    CleanSubGroup *package_unneed_btn;
    CleanListWidget *package_oldkernel_items ;
    CleanSubGroup *package_oldkernel_btn;
    CleanListWidget *package_configfile_items ;
    CleanSubGroup *package_configfile_btn;

    CleanListWidget *cookies_firefox_items ;
    CleanSubGroup *cookies_firefox_btn;
    CleanListWidget *cookies_chromium_items ;
    CleanSubGroup *cookies_chromium_btn;

    CleanSubGroup *trace_firefox_btn;
    CleanSubGroup *trace_chromium_btn;
    CleanSubGroup *trace_system_btn;

    QStringList cache_apt_list;
    QStringList cache_software_list;
    QStringList cache_thumbnails_list;
    QStringList cache_firefox_list;
    QStringList cache_chromium_list;
    QStringList package_unneed_list;
    QStringList package_oldkernel_list;
    QStringList package_configfile_list;
    QStringList cookies_firefox_list;
    QStringList cookies_chromium_list;
    QString trace_firefox_count;
    QString trace_chromium_count;
    QString trace_system_count;

    bool colorFlag;
    QBoxLayout *main_layout;
    QHBoxLayout *layout1;
    QHBoxLayout *layout2;
    QHBoxLayout *layout3;
    int appendNum1;
    int appendNum2;
    int appendNum3;

    QGridLayout *grid_layout;
    int rowIndex;
    int columnIndex;
};

#endif // CLEANERDETAILWIDGET_H
