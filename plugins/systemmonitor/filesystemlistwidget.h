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


#ifndef FILESYSTEMLISTWIDGET_H
#define FILESYSTEMLISTWIDGET_H

#include "filesystemlistitem.h"

#include <QList>
#include <QPixmap>
#include <QTimer>
#include <QWidget>

class FileSystemListWidget : public QWidget
{
    Q_OBJECT

public:
    FileSystemListWidget(QList<bool> toBeDisplayedColumns, QWidget *parent = 0);
    ~FileSystemListWidget();

    void readyToHideScrollbar();
    void clearItems();
    void addSelectedItems(QList<FileSystemListItem*> items, bool recordLastItem=true);
    void clearSelectedItems(bool clearLast=true);
    void refreshFileSystemItems(QList<FileSystemListItem*> items);

    int getItemsTotalHeight();
    int getBottomOffset();
    int getScrollbarY();
    int getScrollbarHeight();
    int getTheScrollAreaHeight();

    QList<int> getTitleItemsWidths();

    int setOffset(int offset);

    bool mouseAtScrollArea(int x);
    bool mouseAtTitleArea(int y);

signals:
    void rightMouseClickedItem(QPoint pos);
    void changeColumnVisible(int index, bool visible, QList<bool> columnVisible);

public slots:
    void hideScrollbar();

protected:
    virtual void leaveEvent(QEvent *event);
    void mouseMoveEvent(QMouseEvent *mouseEvent);
    void mousePressEvent(QMouseEvent *mouseEvent);
    void mouseReleaseEvent(QMouseEvent *mouseEvent);
    void paintEvent(QPaintEvent *);
    void wheelEvent(QWheelEvent *event);
    void paintScrollbar(QPainter *painter);
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    QTimer *m_hideScrollbarTimer = nullptr;
    FileSystemListItem *m_lastItem = nullptr;
    QList<FileSystemListItem*> *m_listItems;
    QList<FileSystemListItem*> *m_selectedItems;
    QList<QString> columnTitles;
    QList<int> m_columnWidths;
    QList<bool> m_columnVisibles;

    bool m_mouseAtScrollArea;
    bool m_mouseDragScrollbar;
    int m_origOffset;
    int m_offSet;
    int m_rowHeight;
    int m_scrollbarWidth;
    int m_titleHeight;
    int m_titleHoverColumn;
    int m_titlePadding;
    int m_titlePressColumn;
};

#endif // PROCESSLISTWIDGET_H
