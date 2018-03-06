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


#ifndef PROCESSLISTITEM_H
#define PROCESSLISTITEM_H

#include <QObject>
#include <QPainter>
#include <QPen>
#include "processdata.h"

class ProcessListItem : public QObject
{
    Q_OBJECT
    
public:
    ProcessListItem(ProcData info);
    
    bool isSameItem(ProcessListItem *item);
    void drawCellBackground(QRect rect, QPainter *painter, int level);
    void drawBackground(QRect rect, QPainter *painter, int index, bool isSelect);
    void drawForeground(QRect rect, QPainter *painter, int column, int index, bool isSelect, bool isSeparator);
    static bool doSearch(const ProcessListItem *item, QString text);
    static bool sortByName(const ProcessListItem *item1, const ProcessListItem *item2, bool descendingSort);
    static bool sortByUser(const ProcessListItem *item1, const ProcessListItem *item2, bool descendingSort);
    static bool sortByStatus(const ProcessListItem *item1, const ProcessListItem *item2, bool descendingSort);
    static bool sortByCPU(const ProcessListItem *item1, const ProcessListItem *item2, bool descendingSort);
    static bool sortByPid(const ProcessListItem *item1, const ProcessListItem *item2, bool descendingSort);
    static bool sortByCommand(const ProcessListItem *item1, const ProcessListItem *item2, bool descendingSort);
    static bool sortByMemory(const ProcessListItem *item1, const ProcessListItem *item2, bool descendingSort);
    static bool sortByPriority(const ProcessListItem *item1, const ProcessListItem *item2, bool descendingSort);

    QString getProcessName() const;
    QString getDisplayName() const;
    QString getUser() const;
    double getCPU() const;
    pid_t getPid() const;
    long getMemory() const;
    QString getStatus() const;
    long getNice() const;
    QString getCommandLine() const;
    
private:
    ProcData m_data;
    int iconSize;
    int padding;
    int textPadding;
};

#endif // PROCESSLISTITEM_H
