/*
 * Copyright (C) 2021 KylinSoft Co., Ltd.
 *
 * Authors:
 *  Yang Min yangmin@kylinos.cn
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DEVICEMONITORPAGE_H
#define DEVICEMONITORPAGE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLabel>
#include <qgsettings.h>
#include <QFrame>
#include <QMap>

#include "kausageitem.h"
#include "katempitem.h"

class DeviceMonitorPage : public QWidget
{
    Q_OBJECT
public:
    explicit DeviceMonitorPage(QWidget *parent = nullptr);
    virtual ~DeviceMonitorPage();

    void initUI();
    void initConnections();
    void refreshInfo();

public slots:
    void onUpdateInfo(unsigned uStatus, QString strInfoJson);

signals:
    void updateInfo(unsigned uStatus, QString strInfoJson);

private:
    void initStyleTheme();
    void clearInfoItems();
    void addInfoItems(int nType, QString strTitle, qreal rHigh, qreal rVHigh, qreal newValue);
    void checkTempStatus();

private:
    QVBoxLayout *m_mainLayout = nullptr;
    QVBoxLayout *m_tempLayout = nullptr;
    QVBoxLayout *m_usageLayout = nullptr;
    QHBoxLayout *m_tempTitleLayout = nullptr;
    QHBoxLayout *m_tempContentLayout = nullptr;
    QVBoxLayout *m_scrollLayout = nullptr;
    QScrollArea *m_scrollFrame = nullptr;
    QFrame *m_scrollWidget = nullptr;
    //usage items
    KAUsageItem *m_usageItemCPU = nullptr;
    KAUsageItem *m_usageItemMem = nullptr;
    // temperature items
    QLabel *m_tempTitle = nullptr;
    KATempItem *m_tempCpu = nullptr;
    KATempItem *m_tempDev = nullptr;
    KATempItem *m_tempBaseBoard = nullptr;

    QGSettings *m_styleSettings = nullptr;
    QList<QString> m_listStatus;
    QMap<QString, QWidget*> m_mapSubWidgets;
};

#endif // DEVICEMONITORPAGE_H
