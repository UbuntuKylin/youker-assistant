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

#ifndef MEMORYINFO_H
#define MEMORYINFO_H

#include <QWidget>
#include <kinfolistitem.h>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QMap>

#include "../../src/kajsondef.h"
#include "kainfotitle.h"
#include "kabaseinfopage.h"

enum MMI_INDEX{
    MEMORYINFO_TITLE,
    MEMORYINFO_INVALID,
    MEMORYINFO_SLOT,
    MEMORYINFO_NAME,
    MEMORYINFO_FREQ,
    MEMORYINFO_BUSWIDTH,
    MEMORYINFO_TOTALCAPACITY,
    MEMORYINFO_USEDCAPACITY,
    MEMORYINFO_SERIALNUM,
    MEMORYINFO_MANUFACTURER,
    MEMORYINFO_DATAWIDTH,
    MEMORYINFO_TYPE,
    MEMORYINFO_SPEED,
    MEMORYINFO_CONFIGSPEED,
    MEMORYINFO_PIPE,
    MEMORYINFO_ARRAYHANDLE,
    MEMORYINFO_PARTNUMBER,
    MEMORYINFO_PHYSICALID
};

class MemoryInfo : public KABaseInfoPage
{
    Q_OBJECT
public:
    explicit MemoryInfo(QWidget *parent = nullptr);

    void initUI();

    void initConnections();
    void updateInfoItems(QString strInfoJson);

public slots:
    void onUpdateInfo(QString strInfoJson) override;
    void onRefreshInfo() override;

private:
    void addInfoItems(unsigned uGroup, unsigned uId, QString strTitle, QString strContent, bool bMulti);
    void clearInfoItems();
    void chkNoDevice();

private:
    QString m_strInfoJson;

    QVBoxLayout *m_mainLayout = nullptr;
    QFrame *m_listFrame = nullptr;
    QVBoxLayout *m_listLayout = nullptr;
    QScrollArea *m_scrollFrame = nullptr;

    QMap<unsigned,QMap<unsigned, QWidget*>> m_mapInfoItems;
};

#endif // MEMORYINFO_H
