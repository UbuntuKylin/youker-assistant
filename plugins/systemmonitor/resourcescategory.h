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

#ifndef RESOURCESCATEGORY_H
#define RESOURCESCATEGORY_H

#include <QWidget>
#include <QVBoxLayout>

class NetworkIndicator;
class ResourcesIndicator;

class ResourcesCategory : public QWidget
{
    Q_OBJECT
    
public:
    explicit ResourcesCategory(int tabIndex, QWidget *parent = 0);
    ~ResourcesCategory();

public slots:
    void onUpdateCpuPercent(double value);
    void onUpdateMemoryPercent(const QString &info, double value);
//    void onUpdateNetworkPainterPath(QPainterPath downloadPath, QPainterPath uploadPath);
    void onUpdateNetworkStatus(long recvTotalBytes, long sentTotalBytes, long recvRateKbs, long sentRateKbs);
    
signals:
    void switchResoucesPage(int index);

private:
    int activeIndex;
    QVBoxLayout *layout = nullptr;
    ResourcesIndicator *cpuButton = nullptr;
    ResourcesIndicator *memoryButton = nullptr;
    NetworkIndicator *networkButton = nullptr;
};

#endif // RESOURCESCATEGORY_H
