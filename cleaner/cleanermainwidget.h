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

#ifndef CLEANERMAINWIDGET_H
#define CLEANERMAINWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QMap>
#include <QVariant>

#include "../component/utils.h"

class QLabel;
class MainWindow;
class CleanGroup;
class Toolkits;

class CleanerMainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CleanerMainWidget(QWidget *parent = 0, MainWindow *window = 0, Toolkits *kits = 0, QString skin = ":/background/res/skin/1.png");
    ~CleanerMainWidget();
    void setLanguage();
    void getAllScanSelectedItems();
    void resetCurrentSkin(QString skin);

public slots:
    void onButtonClicked();
    void receiveScanSignal();
    void onRefreshSelectedItems(CleanerCategoryID id, const QStringList &infos);
    void resetDefaultStatus();

signals:
    void showActionAnimaiton();
    void startScanSystem(QMap<QString, QVariant> itemsMap);

private:
    MainWindow *parentWindow;
    QLabel *tip_label;

    CleanGroup *cache_btn;
//    CleanerItems *cache_items;
//    CleanGroup *package_btn;
//    CleanerItems *package_items;
    CleanGroup *cookies_btn;
//    CleanerItems *cookies_items;
    CleanGroup *trace_btn;
//    CleanerItems *trace_items;

    QMap<QString, QVariant> argsMap;
    Toolkits *toolKits;

    QStringList cache_list;
    QStringList cache_status_list;
    QStringList cookies_list;
    QStringList cookies_status_list;
    QStringList trace_list;
    QStringList trace_status_list;

    QStringList m_selectedCache;
    QStringList m_selectedCookie;
    QStringList m_selectedTrace;
};

#endif // CLEANERMAINWIDGET_H




