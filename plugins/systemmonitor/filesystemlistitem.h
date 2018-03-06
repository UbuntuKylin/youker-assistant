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


#ifndef FILESYSTEMLISTITEM_H
#define FILESYSTEMLISTITEM_H

#include <QObject>
#include <QPainter>
#include <QPen>

#include "filesystemdata.h"

class FileSystemListItem : public QObject
{
    Q_OBJECT
    
public:
    FileSystemListItem(FileSystemData *info);
    
    bool isSameItem(FileSystemListItem *item);
    void drawCellBackground(QRect rect, QPainter *painter, int level);
    void drawBackground(QRect rect, QPainter *painter, int index, bool isSelect);
    void drawForeground(QRect rect, QPainter *painter, int column, int index, bool isSelect, bool isSeparator);

    QString getDeviceName() const;
    QString getDirectory() const;
    
private:
    FileSystemData *m_data;
    int iconSize;
    int padding;
    int textPadding;
};

#endif // FILESYSTEMLISTITEM_H
