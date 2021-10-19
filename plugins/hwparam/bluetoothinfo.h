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

#ifndef BLUETOOTHINFO_H
#define BLUETOOTHINFO_H

#include <QWidget>
#include <kinfolistitem.h>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QMap>

#include "../../src/kajsondef.h"
#include "kainfotitle.h"
#include "kabaseinfopage.h"

enum BLI_INDEX{
    BLUETOOTHINFO_TITLE,
    BLUETOOTHINFO_INVALID,
    BLUETOOTHINFO_BUSADDR,
    BLUETOOTHINFO_FUNCTION,
    BLUETOOTHINFO_FREQ,
    BLUETOOTHINFO_CONF,
    BLUETOOTHINFO_DEVTYPE,
    BLUETOOTHINFO_ID,
    BLUETOOTHINFO_DEVMODEL,
    BLUETOOTHINFO_RESOURCE,
    BLUETOOTHINFO_MANUFACTURER,
    BLUETOOTHINFO_DEVVERSION,
    BLUETOOTHINFO_DATAWIDTH,
    BLUETOOTHINFO_NAME,
    BLUETOOTHINFO_DRIVER,
    BLUETOOTHINFO_SPEED,
    BLUETOOTHINFO_SERIALNUM,
    BLUETOOTHINFO_ADDRESS,
    BLUETOOTHINFO_LINKMODE,
    BLUETOOTHINFO_LINKPOLICY,
    BLUETOOTHINFO_CAPABILITIES,
    BLUETOOTHINFO_BUS,
    BLUETOOTHINFO_SCOMTU,
    BLUETOOTHINFO_ALCMTU,
    BLUETOOTHINFO_PACKETTYPE,
    BLUETOOTHINFO_FEATURES,
};

class BluetoothInfo : public KABaseInfoPage
{
    Q_OBJECT
public:
    explicit BluetoothInfo(QWidget *parent = nullptr);

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

#endif // BLUETOOTHINFO_H
