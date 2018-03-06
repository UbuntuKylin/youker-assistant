/*
 * Copyright (C) 2013 ~ 2018 National University of Defense Technology(NUDT) & Tianjin Kylin Ltd.
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


#ifndef NETWORKFLOW_H
#define NETWORKFLOW_H

#include <QWidget>

class NetworkFlow : public QWidget
{
    Q_OBJECT

public:
    NetworkFlow(QWidget *parent = 0);
    ~NetworkFlow();

public slots:
    void onUpdateNetworkStatus(long recvTotalBytes, long sentTotalBytes, long recvRateKbs, long sentRateKbs);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QList<long> *m_downloadSpeedList;
    QList<long> *m_uploadSpeedList;
    QPainterPath m_downloadPath;
    QPainterPath m_uploadPath;

    int m_netMaxHeight;
    int m_pointsCount;

    long m_recvTotalBytes;
    long m_sentTotalBytes;
    long m_recvRateBytes;
    long m_sentRateBytes;
    QList<int> *m_gridY;
    int m_pointSpace;

    QColor m_outsideBorderColor;
    QColor m_bgColor;
    QColor m_downloadColor;
    QColor m_uploadColor;

    QString receiveText;
    QString sendText;
};

#endif // NETWORKFLOW_H
