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

#ifndef MONITORINFO_H
#define MONITORINFO_H

#include <QWidget>
#include <kinfolistitem.h>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QMap>
#include <QAbstractNativeEventFilter>

#include "../../src/kajsondef.h"
#include "kainfotitle.h"
#include "kabaseinfopage.h"

enum MNI_INDEX{
    MONITORINFO_TITLE,
    MONITORINFO_INVALID,
    MONITORINFO_MANUFACTURER,
    MONITORINFO_NAME,
    MONITORINFO_SIZE,
    MONITORINFO_RATIO,
    MONITORINFO_RESOLUTION,
    MONITORINFO_MAXAVARES,
    MONITORINFO_ISMAIN,
    MONITORINFO_GAMMA,
    MONITORINFO_INTERFACE,
    MONITORINFO_MODEL,
    MONITORINFO_VISIBLEAREA,
    MONITORINFO_YEAR,
    MONITORINFO_WEEK,
};

class MonitorInfo : public KABaseInfoPage, public QAbstractNativeEventFilter
{
    Q_OBJECT
public:
    explicit MonitorInfo(QWidget *parent = nullptr);

    void initUI();

    void initConnections();
    void updateInfoItems(QString strInfoJson);

public slots:
    void onUpdateInfo(QString strInfoJson) override;
    void onRefreshInfo() override;

protected:
    virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) override;

private:
    void addInfoItems(unsigned uGroup, unsigned uId, QString strTitle, QString strContent, bool bMulti);
    void clearInfoItems();
    void chkNoDevice();
    void RRScreenChangeEvent();

private:
    QString m_strInfoJson;

    QVBoxLayout *m_mainLayout = nullptr;
    QFrame *m_listFrame = nullptr;
    QVBoxLayout *m_listLayout = nullptr;
    QScrollArea *m_scrollFrame = nullptr;

    QMap<unsigned,QMap<unsigned, QWidget*>> m_mapInfoItems;
    int m_xrrEventBase = 0;
    int m_xrrErrorBase = 0;
};

#endif // MONITORINFO_H
