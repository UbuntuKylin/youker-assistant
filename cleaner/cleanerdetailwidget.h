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

//#include <QWidget>
//#include "../component/kylinlistwidget.h"
//#include "../component/kylintitlebar.h"
//#include "../component/autogroup.h"
//#include <QCheckBox>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QSignalMapper>
#include <QVBoxLayout>
#include "../component/kylinbutton.h"
#include "../component/kylintoolbutton.h"
#include "../component/systembutton.h"
#include "../component/commoncheckbox.h"
#include <QCheckBox>
#include "cleaneritems.h"
#include "cleanlistwidget.h"
#include <QGridLayout>

class SessionDispatcher;
class SystemDispatcher;
class MainWindow;

namespace Ui {
class CleanerDetailWidget;
}

class CleanerDetailWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CleanerDetailWidget(QWidget *parent = 0, SessionDispatcher *seroxy = 0, SystemDispatcher *syproxy = 0, MainWindow *window = 0);
    ~CleanerDetailWidget();
    void setUIData();
    void setLanguage();
    void initConnect();
    void getAllSelectedItems();

public slots:
    void onButtonClicked();
    void showReciveData(const QStringList &data);

    void receiveCleanSignal();
    void showReciveStatus(const QString &status);
    void CleanUIAndData();


signals:
    void notifyMainCheckBox(int status);

private:
    void initTitleBar();

private:
    Ui::CleanerDetailWidget *ui;
    MainWindow *parentWindow;
    SessionDispatcher *sessionproxy;
    SystemDispatcher *systemproxy;
    QMap<QString, QVariant> argsData;
    CleanListWidget *cache_apt_items ;
    CommonCheckBox *cache_apt_btn;
    CleanListWidget *cache_software_items ;
    CommonCheckBox *cache_software_btn;
    CleanListWidget *cache_thumbnails_items ;
    CommonCheckBox *cache_thumbnails_btn;
    CleanListWidget *cache_firefox_items ;
    CommonCheckBox *cache_firefox_btn;
    CleanListWidget *cache_chromium_items ;
    CommonCheckBox *cache_chromium_btn;

    CleanListWidget *package_unneed_items ;
    CommonCheckBox *package_unneed_btn;
    CleanListWidget *package_oldkernel_items ;
    CommonCheckBox *package_oldkernel_btn;
    CleanListWidget *package_configfile_items ;
    CommonCheckBox *package_configfile_btn;

    CleanListWidget *cookies_firefox_items ;
    CommonCheckBox *cookies_firefox_btn;
    CleanListWidget *cookies_chromium_items ;
    CommonCheckBox *cookies_chromium_btn;

    CommonCheckBox *trace_firefox_btn;
    CommonCheckBox *trace_chromium_btn;
//    KylinCheckBox *trace_system_btn;

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
