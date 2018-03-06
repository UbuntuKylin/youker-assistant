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

#include "processlistitem.h"
#include <QCollator>
#include <QDebug>
#include <QLocale>
#include "util.h"

ProcessListItem::ProcessListItem(ProcData info)
{
    m_data = info;
    iconSize = 16;
    padding = 14;
    textPadding = 5;
}

bool ProcessListItem::isSameItem(ProcessListItem *item)
{
    return m_data.pid == ((static_cast<ProcessListItem*>(item)))->m_data.pid;
}

void ProcessListItem::drawCellBackground(QRect rect, QPainter *painter, int level)
{
    QPainterPath path;
    path.addRect(QRectF(rect.x(), rect.y(), rect.width(), rect.height()));
    painter->setOpacity(0.5);//0.1
    if (level == 0) {
        painter->fillPath(path, QColor("#fff4c4"));
    }
    else if (level == 1) {
        painter->fillPath(path, QColor("#f9eca8"));
    }
    else {
        painter->fillPath(path, QColor("#fca71d"));
    }
}

void ProcessListItem::drawBackground(QRect rect, QPainter *painter, int index, bool isSelect)
{
    QPainterPath path;
    path.addRect(QRectF(rect));

    if (isSelect) {
        painter->setOpacity(0.1);
        painter->fillPath(path, QColor("#2bb6ea"));
    }
    else {
        painter->setOpacity(1);
        painter->fillPath(path, QColor("#ffffff"));
//        if (index % 2 == 0) {
//            painter->fillPath(path, QColor("#ffffff"));
//        } else {
//            painter->fillPath(path, QColor("#e9eef0"));
//        }
    }
}

void ProcessListItem::drawForeground(QRect rect, QPainter *painter, int column, int, bool isSelect, bool isSeparator)
{
    setFontSize(*painter, 12);
    painter->setOpacity(1);
    painter->setPen(QPen(QColor("#000000")));
    if (column == 0) {
        painter->drawPixmap(QRect(rect.x() + padding, rect.y() + (rect.height() - iconSize) / 2, iconSize, iconSize), m_data.iconPixmap);
        QString name = m_data.processName;
        if (m_data.m_status == tr("Stopped")) {//已停止
            painter->setPen(QPen(QColor("#fca71d")));
            name = QString("(%1) %2").arg(tr("Suspend")).arg(m_data.processName);
        }
        else if (m_data.m_status == tr("Zombie")) {//僵死
            painter->setPen(QPen(QColor("#808080")));
            name = QString("(%1) %2").arg(tr("No response")).arg(m_data.processName);
        }
        else if (m_data.m_status == tr("Uninterruptible")) {//不可中断
            painter->setPen(QPen(QColor("#ff6a6a")));
            name = QString("(%1) %2").arg(tr("Uninterruptible")).arg(m_data.processName);
        }
        else {//Sleeping 睡眠中  Running 运行中
        }
        int nameMaxWidth = rect.width() - iconSize - padding * 3;
        QFont font = painter->font();
        QFontMetrics fm(font);
        QString procName = fm.elidedText(name, Qt::ElideRight, nameMaxWidth);
        painter->drawText(QRect(rect.x() + iconSize + padding * 2, rect.y(), nameMaxWidth, rect.height()), Qt::AlignLeft | Qt::AlignVCenter, procName);
        if (isSeparator) {
            painter->setOpacity(0.8);
            QPainterPath separatorPath;
            separatorPath.addRect(QRectF(rect.x() + rect.width() - 1, rect.y(), 1, rect.height()));
            painter->fillPath(separatorPath, QColor("#e0e0e0"));
        }
    }
    else if (column == 1) {
        if (!m_data.user.isEmpty()) {
            painter->drawText(QRect(rect.x(), rect.y(), rect.width() - textPadding, rect.height()), Qt::AlignRight | Qt::AlignVCenter, m_data.user);
        }
        if (isSeparator) {
            painter->setOpacity(0.8);
            QPainterPath separatorPath;
            separatorPath.addRect(QRectF(rect.x() + rect.width() - 1, rect.y(), 1, rect.height()));
            painter->fillPath(separatorPath, QColor("#e0e0e0"));
        }
    }
    else if (column == 2) {
        if (!m_data.m_status.isEmpty()) {
            painter->drawText(QRect(rect.x(), rect.y(), rect.width() - textPadding, rect.height()), Qt::AlignRight | Qt::AlignVCenter, m_data.m_status);
        }
        if (isSeparator) {
            painter->setOpacity(0.8);
            QPainterPath separatorPath;
            separatorPath.addRect(QRectF(rect.x() + rect.width() - 1, rect.y(), 1, rect.height()));
            painter->fillPath(separatorPath, QColor("#e0e0e0"));
        }
    }
    else if (column == 3) {
        if (m_data.cpu < 10) {
            this->drawCellBackground(QRect(rect.x(), rect.y(), rect.width(), rect.height()), painter, 0);
        }
        else if (m_data.cpu < 33) {
            this->drawCellBackground(QRect(rect.x(), rect.y(), rect.width(), rect.height()), painter, 1);
        }
        else {
            this->drawCellBackground(QRect(rect.x(), rect.y(), rect.width(), rect.height()), painter, 2);
        }
        painter->drawText(QRect(rect.x(), rect.y(), rect.width() - textPadding, rect.height()), Qt::AlignRight | Qt::AlignVCenter, QString("%1%").arg(m_data.cpu));
        if (isSeparator) {
            painter->setOpacity(0.8);
            QPainterPath separatorPath;
            separatorPath.addRect(QRectF(rect.x() + rect.width() - 1, rect.y(), 1, rect.height()));
            painter->fillPath(separatorPath, QColor("#e0e0e0"));
        }
    }
    else if (column == 4) {
        painter->drawText(QRect(rect.x(), rect.y(), rect.width() - padding, rect.height()), Qt::AlignRight | Qt::AlignVCenter, QString("%1").arg(m_data.pid));
        if (isSeparator) {
            painter->setOpacity(0.8);
            QPainterPath separatorPath;
            separatorPath.addRect(QRectF(rect.x() + rect.width() - 1, rect.y(), 1, rect.height()));
            painter->fillPath(separatorPath, QColor("#e0e0e0"));
        }
    }
    else if (column == 5) {
        int commandMaxWidth = rect.width();
        QFont font = painter->font();
        QFontMetrics fm(font);
        QString command = fm.elidedText(m_data.commandLine, Qt::ElideRight, commandMaxWidth);
        painter->drawText(QRect(rect.x(), rect.y(), commandMaxWidth, rect.height()), Qt::AlignLeft | Qt::AlignVCenter, command);
        if (isSeparator) {
            painter->setOpacity(0.8);
            QPainterPath separatorPath;
            separatorPath.addRect(QRectF(rect.x() + rect.width() - 1, rect.y(), 1, rect.height()));
            painter->fillPath(separatorPath, QColor("#e0e0e0"));
        }
    }
    else if (column == 6) {
        if (m_data.m_memory > 0) {
            painter->setOpacity(1);
            QString memory = QString(g_format_size_full(m_data.m_memory, G_FORMAT_SIZE_IEC_UNITS));
            if (m_data.m_memory < 102400000) {//<100M
                this->drawCellBackground(QRect(rect.x(), rect.y(), rect.width(), rect.height()), painter, 0);
            }
            else if (m_data.m_memory < 1024000000) {//1G
                this->drawCellBackground(QRect(rect.x(), rect.y(), rect.width(), rect.height()), painter, 1);
            }
            else {
                this->drawCellBackground(QRect(rect.x(), rect.y(), rect.width(), rect.height()), painter, 2);
            }
            painter->drawText(QRect(rect.x(), rect.y(), rect.width() - textPadding, rect.height()), Qt::AlignRight | Qt::AlignVCenter, memory);
        }
        if (isSeparator) {
            painter->setOpacity(0.8);
            QPainterPath separatorPath;
            separatorPath.addRect(QRectF(rect.x() + rect.width() - 1, rect.y(), 1, rect.height()));
            painter->fillPath(separatorPath, QColor("#e0e0e0"));
        }
    }
    else if (column == 7) {
        painter->drawText(QRect(rect.x(), rect.y(), rect.width() - textPadding, rect.height()), Qt::AlignLeft | Qt::AlignVCenter, getNiceLevel(m_data.m_nice));
        if (isSeparator) {
            painter->setOpacity(0.8);
            QPainterPath separatorPath;
            separatorPath.addRect(QRectF(rect.x() + rect.width() - 1, rect.y(), 1, rect.height()));
            painter->fillPath(separatorPath, QColor("#e0e0e0"));
        }
    }
}

bool ProcessListItem::doSearch(const ProcessListItem *item, QString text)
{
    const ProcessListItem *procItem = static_cast<const ProcessListItem*>(item);
    QString content = text.toLower();
    return procItem->getProcessName().toLower().contains(content) || QString::number(procItem->getPid()).contains(content) || procItem->getDisplayName().toLower().contains(content) || procItem->getUser().toLower().contains(content);
}

bool ProcessListItem::sortByName(const ProcessListItem *item1, const ProcessListItem *item2, bool descendingSort)
{
    QString name1 = (static_cast<const ProcessListItem*>(item1))->getDisplayName();
    QString name2 = (static_cast<const ProcessListItem*>(item2))->getDisplayName();
    bool isSort;

    if (name1 == name2) {
        double cpu1 = static_cast<const ProcessListItem*>(item1)->getCPU();
        double cpu2 = (static_cast<const ProcessListItem*>(item2))->getCPU();
        isSort = cpu1 > cpu2;
    }
    else {
        QCollator qco(QLocale::system());
        int result = qco.compare(name1, name2);
        isSort = result < 0;
    }

    return descendingSort ? isSort : !isSort;
}

bool ProcessListItem::sortByUser(const ProcessListItem *item1, const ProcessListItem *item2, bool descendingSort)
{
    QString user1 = (static_cast<const ProcessListItem*>(item1))->getUser();
    QString user2 = (static_cast<const ProcessListItem*>(item2))->getUser();
    bool isSort;
    if (user1 == user2) {
        double cpu1 = static_cast<const ProcessListItem*>(item1)->getCPU();
        double cpu2 = (static_cast<const ProcessListItem*>(item2))->getCPU();
        isSort = cpu1 > cpu2;
    }
    else {
        QCollator qco(QLocale::system());
        int result = qco.compare(user1, user2);
        isSort = result < 0;
    }

    return descendingSort ? isSort : !isSort;
}

bool ProcessListItem::sortByStatus(const ProcessListItem *item1, const ProcessListItem *item2, bool descendingSort)
{
    QString status1 = (static_cast<const ProcessListItem*>(item1))->getStatus();
    QString status2 = (static_cast<const ProcessListItem*>(item2))->getStatus();
    bool isSort;
    if (status1 == status2) {
        double cpu1 = static_cast<const ProcessListItem*>(item1)->getCPU();
        double cpu2 = (static_cast<const ProcessListItem*>(item2))->getCPU();
        isSort = cpu1 > cpu2;
    }
    else {
        QCollator qco(QLocale::system());
        int result = qco.compare(status1, status2);
        isSort = result < 0;
    }

    return descendingSort ? isSort : !isSort;
}


bool ProcessListItem::sortByCPU(const ProcessListItem *item1, const ProcessListItem *item2, bool descendingSort)
{
    double cpu1 = (static_cast<const ProcessListItem*>(item1))->getCPU();
    double cpu2 = (static_cast<const ProcessListItem*>(item2))->getCPU();
    bool isSort;
    if (cpu1 == cpu2) {
        long memory1 = static_cast<const ProcessListItem*>(item1)->getMemory();
        long memory2 = (static_cast<const ProcessListItem*>(item2))->getMemory();
        isSort = memory1 > memory2;
    }
    else {
        isSort = cpu1 > cpu2;
    }

    return descendingSort ? isSort : !isSort;
}

bool ProcessListItem::sortByPid(const ProcessListItem *item1, const ProcessListItem *item2, bool descendingSort)
{
    bool isSort = (static_cast<const ProcessListItem*>(item1))->getPid() > (static_cast<const ProcessListItem*>(item2))->getPid();

    return descendingSort ? isSort : !isSort;
}

bool ProcessListItem::sortByCommand(const ProcessListItem *item1, const ProcessListItem *item2, bool descendingSort)
{
    QString command1 = (static_cast<const ProcessListItem*>(item1))->getCommandLine();
    QString command2 = (static_cast<const ProcessListItem*>(item2))->getCommandLine();
    bool isSort;
    if (command1 == command2) {
        double cpu1 = static_cast<const ProcessListItem*>(item1)->getCPU();
        double cpu2 = (static_cast<const ProcessListItem*>(item2))->getCPU();
        isSort = cpu1 > cpu2;
    }
    else {
        QCollator qco(QLocale::system());
        int result = qco.compare(command1, command2);
        isSort = result < 0;
    }

    return descendingSort ? isSort : !isSort;
}

bool ProcessListItem::sortByMemory(const ProcessListItem *item1, const ProcessListItem *item2, bool descendingSort)
{
    long memory1 = (static_cast<const ProcessListItem*>(item1))->getMemory();
    long memory2 = (static_cast<const ProcessListItem*>(item2))->getMemory();
    bool isSort;
    if (memory1 == memory2) {
        double cpu1 = static_cast<const ProcessListItem*>(item1)->getCPU();
        double cpu2 = (static_cast<const ProcessListItem*>(item2))->getCPU();
        isSort = cpu1 > cpu2;
    }
    else {
        isSort = memory1 > memory2;
    }

    return descendingSort ? isSort : !isSort;
}

bool ProcessListItem::sortByPriority(const ProcessListItem *item1, const ProcessListItem *item2, bool descendingSort)
{
    long nice1 = (static_cast<const ProcessListItem*>(item1))->getNice();
    long nice2 = (static_cast<const ProcessListItem*>(item2))->getNice();
    bool isSort;
    if (nice1 == nice2) {
        double cpu1 = static_cast<const ProcessListItem*>(item1)->getCPU();
        double cpu2 = (static_cast<const ProcessListItem*>(item2))->getCPU();
        isSort = cpu1 > cpu2;
    }
    else {
        isSort = nice1 > nice2;
    }

    return descendingSort ? isSort : !isSort;
}

QString ProcessListItem::getProcessName() const
{
    return m_data.processName;
}

QString ProcessListItem::getDisplayName() const
{
    return m_data.displayName;
}

QString ProcessListItem::getUser() const
{
    return m_data.user;
}

QString ProcessListItem::getStatus() const
{
    return m_data.m_status;
}

double ProcessListItem::getCPU() const
{
    return m_data.cpu;
}

pid_t ProcessListItem::getPid() const
{
    return m_data.pid;
}

long ProcessListItem::getMemory() const
{
    return m_data.m_memory;
}

long ProcessListItem::getNice() const
{
    return m_data.m_nice;
}

QString ProcessListItem::getCommandLine() const
{
    return m_data.commandLine;
}
