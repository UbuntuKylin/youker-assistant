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

#ifndef MOTHERBOARDINFO_H
#define MOTHERBOARDINFO_H

#include <QWidget>
#include <kinfolistitem.h>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QMap>

#include "../../src/kajsondef.h"
#include "kabaseinfopage.h"

enum MBI_INDEX{
    MOTHERBOARDINFO_NAME,
    MOTHERBOARDINFO_INVALID,
    MOTHERBOARDINFO_MANUFACTURER,
    MOTHERBOARDINFO_CHIPSET,
    MOTHERBOARDINFO_SERIALNUM,
    MOTHERBOARDINFO_PUBDATE,
    MOTHERBOARDINFO_VERSION,
    MOTHERBOARDINFO_BIOSMANUFACTURER,
    MOTHERBOARDINFO_BIOSVERSION,
};

class MotherBoardInfo : public KABaseInfoPage
{
    Q_OBJECT
public:
    explicit MotherBoardInfo(QWidget *parent = nullptr);

    void initUI();

    void initConnections();
    void updateInfoItems(QString strInfoJson);

public slots:
    void onUpdateInfo(QString strInfoJson) override;
    void onRefreshInfo() override;

private:
    void addInfoItems(unsigned uId, QString strTitle, QString strContent);
    void clearInfoItems();
    void chkNoDevice();

private:
    QString m_strInfoJson;

    QVBoxLayout *m_mainLayout = nullptr;
    QFrame *m_listFrame = nullptr;
    QVBoxLayout *m_listLayout = nullptr;
    QScrollArea *m_scrollFrame = nullptr;

    QMap<unsigned, KInfoListItem*> m_mapItem;
};

#endif // MOTHERBOARDINFO_H
