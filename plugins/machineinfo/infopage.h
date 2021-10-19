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

#ifndef INFOPAGE_H
#define INFOPAGE_H

#include <QWidget>
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QMap>

#include "kinfolistitem.h"
#include "../../src/commondef.h"
#include "../../src/kajsondef.h"

enum MI_INDEX{
    MACHINEINFO_MANUFACTURER,
    MACHINEINFO_MACHINEMODEL,
    MACHINEINFO_SERIALNUM,
    MACHINEINFO_SYSTEMBITS,
    MACHINEINFO_KERNELARCH,
    MACHINEINFO_HOSTNAME,
    MACHINEINFO_OSVERSION,
    MACHINEINFO_KERNELVERSION,
    MACHINEINFO_PROCESSOR,
    MACHINEINFO_MEMORY,
    MACHINEINFO_MAINBOARD,
    MACHINEINFO_HARDDISK,
    MACHINEINFO_GRAPHICSCARD,
    MACHINEINFO_MONITOR,
    MACHINEINFO_NETWORKCARD,
    MACHINEINFO_SOUNDCARD,
};

class InfoPage : public QWidget
{
    Q_OBJECT
public:
    explicit InfoPage(QWidget *parent = nullptr);

    void initUI();

    void initConnections();
    void updateInfoItems(QString strInfoJson);

public slots:
    void onUpdateInfo(QString strInfoJson);
    void onUpdateInfo(unsigned uStatus, QString strInfoJson);
    void onRefreshInfo();

signals:
    void updateInfo(unsigned, QString);

private:
    void addInfoItems(unsigned uId, QString strTitle, QString strIcon, QString strContent);
    void clearInfoItems();

private:
    QString m_strInfoJson;

    QHBoxLayout *m_mainLayout = nullptr;
    QFrame *m_listFrame = nullptr;
    QVBoxLayout *m_listLayout = nullptr;
    QScrollArea *m_scrollFrame = nullptr;

    QMap<unsigned, KInfoListItem*> m_mapItem;
};

#endif // INFOPAGE_H
