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

#include "filesystemlistitem.h"
#include <QCollator>
#include <QDebug>
#include <QLocale>
#include "util.h"


#include <QStyleOptionProgressBar>
#include <QProgressBar>
#include <QApplication>

FileSystemListItem::FileSystemListItem(FileSystemData *info)
{
    m_data = info;
    iconSize = 16;
    padding = 14;
    textPadding = 5;
}

bool FileSystemListItem::isSameItem(FileSystemListItem *item)
{
    return m_data->deviceName() == ((static_cast<FileSystemListItem*>(item)))->m_data->deviceName();
}

void FileSystemListItem::drawBackground(QRect rect, QPainter *painter, int index, bool isSelect)
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

void FileSystemListItem::drawForeground(QRect rect, QPainter *painter, int column, int, bool isSelect, bool isSeparator)
{
    setFontSize(*painter, 12);
    painter->setOpacity(1);
    painter->setPen(QPen(QColor("#000000")));
    if (column == 0) {
        painter->drawPixmap(QRect(rect.x() + padding, rect.y() + (rect.height() - iconSize) / 2, iconSize, iconSize), QPixmap(":/res/disk.png"));
        int nameMaxWidth = rect.width() - iconSize - padding * 3;
        QFont font = painter->font();
        QFontMetrics fm(font);
        QString deviceName = fm.elidedText(m_data->deviceName(), Qt::ElideRight, nameMaxWidth);//Qt::ElideMiddle
        painter->drawText(QRect(rect.x() + iconSize + padding * 2, rect.y(), nameMaxWidth, rect.height()), Qt::AlignLeft | Qt::AlignVCenter, deviceName);
        if (isSeparator) {
            painter->setOpacity(0.8);
            QPainterPath separatorPath;
            separatorPath.addRect(QRectF(rect.x() + rect.width() - 1, rect.y(), 1, rect.height()));
            painter->fillPath(separatorPath, QColor("#e0e0e0"));
        }
    }
    else if (column == 1) {
        if (!m_data->mountDir().isEmpty()) {
            int maxWidth = rect.width();
            QFont font = painter->font();
            QFontMetrics fm(font);
            QString mountDir = fm.elidedText(m_data->mountDir(), Qt::ElideMiddle, maxWidth);
            painter->drawText(QRect(rect.x(), rect.y(), rect.width() - textPadding, rect.height()), Qt::AlignLeft | Qt::AlignVCenter, mountDir);
        }
        if (isSeparator) {
            painter->setOpacity(0.8);
            QPainterPath separatorPath;
            separatorPath.addRect(QRectF(rect.x() + rect.width() - 1, rect.y(), 1, rect.height()));
            painter->fillPath(separatorPath, QColor("#e0e0e0"));
        }
    }
    else if (column == 2) {
        if (!m_data->diskType().isEmpty()) {
            int maxWidth = rect.width();
            QFont font = painter->font();
            QFontMetrics fm(font);
            QString diskType = fm.elidedText(m_data->diskType(), Qt::ElideRight, maxWidth);
            painter->drawText(QRect(rect.x(), rect.y(), rect.width() - textPadding, rect.height()), Qt::AlignRight | Qt::AlignVCenter, diskType);
        }
        if (isSeparator) {
            painter->setOpacity(0.8);
            QPainterPath separatorPath;
            separatorPath.addRect(QRectF(rect.x() + rect.width() - 1, rect.y(), 1, rect.height()));
            painter->fillPath(separatorPath, QColor("#e0e0e0"));
        }
    }
    else if (column == 3) {
        if (!m_data->totalCapacity().isEmpty()) {
            int maxWidth = rect.width();
            QFont font = painter->font();
            QFontMetrics fm(font);
            QString tCapacity = fm.elidedText(m_data->totalCapacity(), Qt::ElideRight, maxWidth);
            painter->drawText(QRect(rect.x(), rect.y(), rect.width() - textPadding, rect.height()), Qt::AlignRight | Qt::AlignVCenter, tCapacity);
        }
        if (isSeparator) {
            painter->setOpacity(0.8);
            QPainterPath separatorPath;
            separatorPath.addRect(QRectF(rect.x() + rect.width() - 1, rect.y(), 1, rect.height()));
            painter->fillPath(separatorPath, QColor("#e0e0e0"));
        }
    }
    else if (column == 4) {
        if (!m_data->freeCapacity().isEmpty()) {
            int maxWidth = rect.width();
            QFont font = painter->font();
            QFontMetrics fm(font);
            QString fCapacity = fm.elidedText(m_data->freeCapacity(), Qt::ElideRight, maxWidth);
            painter->drawText(QRect(rect.x(), rect.y(), rect.width() - textPadding, rect.height()), Qt::AlignRight | Qt::AlignVCenter, fCapacity);
        }
        if (isSeparator) {
            painter->setOpacity(0.8);
            QPainterPath separatorPath;
            separatorPath.addRect(QRectF(rect.x() + rect.width() - 1, rect.y(), 1, rect.height()));
            painter->fillPath(separatorPath, QColor("#e0e0e0"));
        }
    }
    else if (column == 5) {
        if (!m_data->availCapacity().isEmpty()) {
            int maxWidth = rect.width();
            QFont font = painter->font();
            QFontMetrics fm(font);
            QString aCapacity = fm.elidedText(m_data->availCapacity(), Qt::ElideRight, maxWidth);
            painter->drawText(QRect(rect.x(), rect.y(), rect.width() - textPadding, rect.height()), Qt::AlignRight | Qt::AlignVCenter, aCapacity);
        }
        if (isSeparator) {
            painter->setOpacity(0.8);
            QPainterPath separatorPath;
            separatorPath.addRect(QRectF(rect.x() + rect.width() - 1, rect.y(), 1, rect.height()));
            painter->fillPath(separatorPath, QColor("#e0e0e0"));
        }
    }
    else if (column == 6) {
        int leftPadding = 10;
        int topPadding = 5;
        int progressWidth = 100;
        int progressHeight = rect.height() - 2 * topPadding;
        int textMaxWidth = rect.width() - progressWidth - 2 * leftPadding;
        if (!m_data->usedCapactiy().isEmpty()) {
            QFont font = painter->font();
            QFontMetrics fm(font);
            QString uCapacity = fm.elidedText(m_data->usedCapactiy(), Qt::ElideRight, textMaxWidth - textPadding);
            painter->drawText(QRect(rect.x() + textPadding, rect.y(), textMaxWidth - textPadding, rect.height()), Qt::AlignLeft | Qt::AlignVCenter, uCapacity);
        }
        QPainterPath bgPath;
        bgPath.addRect(QRectF(rect.x() + textMaxWidth + leftPadding, rect.y() + topPadding, progressWidth, progressHeight));
        painter->fillPath(bgPath, QColor("#eeeeee"));
        QPainterPath fillPath;
        fillPath.addRect(QRectF(rect.x() + textMaxWidth + leftPadding, rect.y() + topPadding, m_data->usedPercentage(), progressHeight));
        painter->setOpacity(0.5);
        if (m_data->usedPercentage() < 75)
            painter->fillPath(fillPath, QColor("#0288d1"));
        else
            painter->fillPath(fillPath, QColor("#f8b551"));
        painter->setOpacity(1);
        painter->drawText(QRect(rect.x() + textMaxWidth + leftPadding, rect.y() + topPadding, progressWidth, progressHeight), Qt::AlignHCenter | Qt::AlignVCenter, QString::number(m_data->usedPercentage()).append("%"));

        /*
        QStyleOptionProgressBar progressBarStyle;//progressBarStyle.initFrom(this);
        progressBarStyle.rect = QRect(rect.x() + 60, rect.y() + topPadding, pWidth, pHeight);
        progressBarStyle.minimum = 0;
        progressBarStyle.maximum = 100;
        progressBarStyle.textAlignment = Qt::AlignCenter;
        progressBarStyle.progress = m_data->usedPercentage();
        progressBarStyle.text = QString("%1%").arg(m_data->usedPercentage());
        progressBarStyle.textVisible = true;
        QProgressBar progressBar;
        progressBar.setStyleSheet("QProgressBar{border: none;text-align: center;background:#eeeeee;}QProgressBar::chunk {background:#0288d1;}");
        QApplication::style()->drawControl(QStyle::CE_ProgressBar, &progressBarStyle, painter, &progressBar);//绘制进度条
        */

        if (isSeparator) {
            painter->setOpacity(0.8);
            QPainterPath separatorPath;
            separatorPath.addRect(QRectF(rect.x() + rect.width() - 1, rect.y(), 1, rect.height()));
            painter->fillPath(separatorPath, QColor("#e0e0e0"));
        }
    }
}

QString FileSystemListItem::getDeviceName() const
{
    return m_data->deviceName();
}

QString FileSystemListItem::getDirectory() const
{
    return m_data->mountDir();
}
