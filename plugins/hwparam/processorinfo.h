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

#ifndef PROCESSORINFO_H
#define PROCESSORINFO_H

#include <QWidget>
#include <kinfolistitem.h>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QMap>

#include "../../src/kajsondef.h"
#include "kabaseinfopage.h"

enum PSI_INDEX{
    PROCESSORINFO_PROCESSOR,
    PROCESSORINFO_CORESNUM,
    PROCESSORINFO_THREADSNUM,
    PROCESSORINFO_SLOT,
    PROCESSORINFO_FREQ,
    PROCESSORINFO_L1CACHE,
    PROCESSORINFO_L1DCACHE,
    PROCESSORINFO_L1ICACHE,
    PROCESSORINFO_L2CACHE,
    PROCESSORINFO_L3CACHE,
    PROCESSORINFO_INSTSET,
    PROCESSORINFO_EXTINSTSET,
    PROCESSORINFO_USED,
    PROCESSORINFO_MANUFACTURER,
    PROCESSORINFO_ARCH,
    PROCESSORINFO_CORESONLINE,
    PROCESSORINFO_FREQMAX,
};

class ProcessorInfo : public KABaseInfoPage
{
    Q_OBJECT
public:
    explicit ProcessorInfo(QWidget *parent = nullptr);

    void initUI();

    void initConnections();
    void updateInfoItems(QString strInfoJson);

public slots:
    void onUpdateInfo(QString strInfoJson) override;
    void onRefreshInfo() override;

private:
    void addInfoItems(unsigned uId, QString strTitle, QString strContent);
    void clearInfoItems();

private:
    QString m_strInfoJson;

    QVBoxLayout *m_mainLayout = nullptr;
    QFrame *m_listFrame = nullptr;
    QVBoxLayout *m_listLayout = nullptr;
    QScrollArea *m_scrollFrame = nullptr;

    QMap<unsigned, KInfoListItem*> m_mapItem;
};

#endif // PROCESSORINFO_H
