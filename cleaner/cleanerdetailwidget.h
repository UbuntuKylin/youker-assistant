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
#include <QScrollArea>
#include <QMap>
#include <QVariant>
#include "../component/utils.h"

class QLabel;
class QBoxLayout;
class QHBoxLayout;
class QVBoxLayout;
class QGridLayout;
class Toolkits;
class MainWindow;
class CleanSubGroup;

class CleanerDetailWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CleanerDetailWidget(QWidget *parent = 0, MainWindow *window = 0, Toolkits *kits = 0, QString skin = ":/background/res/skin/1.png");
    ~CleanerDetailWidget();

    void setUIData();
    void setLanguage();
    void initConnect();
    void getAllSelectedItems();
    void resetCurrentSkin(QString skin);
    void addItem(CleanSubGroup *item);

public slots:
    void showCustomPage();
    void showReciveData(const QStringList &data);
    void receiveCleanSignal();
    void showReciveStatus(const QString &status);
    void CleanUIAndData();
//    void receivePolicyKitSignal(bool status);
    void onRefreshSelectedItems(CleanerModuleID id, const QStringList &infos);

    void clearItems();

signals:
//    void notifyMainCheckBox(int status);
//    void showActionAnimaiton();
    void sendScanOverStatus(bool status);
    void startCleanSystem(QMap<QString, QVariant> itemsMap);

private:
    MainWindow *parentWindow;
    Toolkits *toolKits;
    QMap<QString, QVariant> argsData;

    QStringList cache_apt_list;
    QStringList cache_software_list;
    QStringList cache_thumbnails_list;
    QStringList cache_firefox_list;
    QStringList cache_chromium_list;
    /*QStringList package_unneed_list;
    QStringList package_oldkernel_list;
    QStringList package_configfile_list;*/
    QStringList cookies_firefox_list;
    QStringList cookies_chromium_list;
    QString trace_firefox_count;
    QString trace_chromium_count;
    QString trace_system_count;
    QString trace_bash_size;
    QString trace_bash_path;
    QStringList trace_x11_list;

    QStringList m_selectedAptList;
    QStringList m_selectedSoftwareList;
    QStringList m_selectedThumbnailsList;
    QStringList m_selectedFirefoxCacheList;
    QStringList m_selectedChromiumCacheList;
    QStringList m_selectedFirefoxCookieList;
    QStringList m_selectedChromiumCookieList;
    QStringList m_selectedTraceX11List;

    bool scanResult;
    QString cur_skin;

    QVBoxLayout *mainLayout = nullptr;
    QLabel *m_emptyLabel = nullptr;
    QScrollArea *m_scrollArea = nullptr;
    QWidget *areaWidget = nullptr;
    QGridLayout *areaWidgetLayout = nullptr;
    QList <CleanSubGroup *> m_cardlist;
    int m_row;
    int m_column;
};

#endif // CLEANERDETAILWIDGET_H
