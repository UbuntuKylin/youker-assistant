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

#ifndef DRIVEINFOPAGE_H
#define DRIVEINFOPAGE_H

#include <QWidget>
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QList>
#include <QMap>

#include "kdriveinfoitem.h"
#include "../../src/commondef.h"
#include "../../src/kajsondef.h"

enum DI_TYPE{
    DRIVEINFOTYPE_MOTHERBOCARD,     // 主板
    DRIVEINFOTYPE_GRPHICS,          // 显卡
    DRIVEINFOTYPE_NETWORK,          // 有线网卡
    DRIVEINFOTYPE_AUDIO,            // 声卡
    DRIVEINFOTYPE_WIFI,             // 无线网卡
    DRIVEINFOTYPE_OTHER,            // 其他
};

typedef struct _DriveInfo_s
{
    QString strName;
    QString strType;
    QString strVersion;
}DriveInfo;

class DriveInfoPage : public QWidget
{
    Q_OBJECT
public:
    explicit DriveInfoPage(QWidget *parent = nullptr);

    void initUI();

    void initConnections();
    void updateInfoItems(QString strInfoJson);

public slots:
    void onUpdateInfo(QString strInfoJson);

private:
    void clearInfoItems();
    void refreshInfoItems();
    DI_TYPE getDriveType(QString strType);

private:
    QString m_strInfoJson;

    QHBoxLayout *m_mainLayout = nullptr;
    QFrame *m_listFrame = nullptr;
    QVBoxLayout *m_listLayout = nullptr;
    QScrollArea *m_scrollFrame = nullptr;

    QMap<unsigned, QList<KDriveInfoItem*>> m_mapItems;
    QMap<DI_TYPE, QList<DriveInfo>> m_mapDriveInfo;
};

#endif // DRIVEINFOPAGE_H
