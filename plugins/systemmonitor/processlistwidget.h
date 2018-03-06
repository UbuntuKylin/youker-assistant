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


#ifndef PROCESSLISTWIDGET_H
#define PROCESSLISTWIDGET_H

#include "processlistitem.h"

#include <QList>
#include <QPixmap>
#include <QTimer>
#include <QWidget>

typedef bool (* SortFunction) (const ProcessListItem *item1, const ProcessListItem *item2, bool sort);
typedef bool (* SearchFunction) (const ProcessListItem *item, QString text);

class ProcessListWidget : public QWidget
{
    Q_OBJECT

public:
    ProcessListWidget(QList<bool> toBeDisplayedColumns, QWidget *parent = 0);
    ~ProcessListWidget();

    void readyToHideScrollbar();
    void setProcessSortFunctions(QList<SortFunction> *list, int sortColumn=-1, bool isSort=false);
    void setSearchFunction(SearchFunction func);
    void addItems(QList<ProcessListItem*> items);
    void clearItems();
    void addSelectedItems(QList<ProcessListItem*> items, bool recordLastItem=true);
    void clearSelectedItems(bool clearLast=true);
    void refreshItems(QList<ProcessListItem*> items);
    void doSearch(QString text);

    void selectTheFirstItem();
    void selectTheLastItem();
    void selectThePrevItem(int offset);
    void selectTheNextItem(int offset);

    void shiftToHomeItem();
    void shiftToEndItem();
    void shiftToPrevItem(int offset);
    void shiftToNextItem(int offset);
    void shiftToSelectedItems(int start, int end);

    int getItemsTotalHeight();
    QList<ProcessListItem*> getSearchedItems(QList<ProcessListItem*> items);
    void sortItemsByColumn(int column, bool isSort);

    int getBottomOffset();
    int getScrollbarY();
    int getScrollbarHeight();
    int getTheScrollAreaHeight();

    QList<int> getTitleItemsWidths();

    int setOffset(int offset);

    bool mouseAtScrollArea(int x);
    bool mouseAtTitleArea(int y);

signals:
    void rightMouseClickedItems(QPoint pos, QList<ProcessListItem*> items);
    void changeColumnVisible(int index, bool visible, QList<bool> columnVisible);
    void changeSortStatus(int index, bool isSort);

public slots:
    void hideScrollbar();

protected:
    virtual void leaveEvent(QEvent *event);
    void keyPressEvent(QKeyEvent *keyEvent);
    void mouseMoveEvent(QMouseEvent *mouseEvent);
    void mousePressEvent(QMouseEvent *mouseEvent);
    void mouseReleaseEvent(QMouseEvent *mouseEvent);
    void paintEvent(QPaintEvent *);
    void wheelEvent(QWheelEvent *event);
    void paintScrollbar(QPainter *painter);

private:
    QTimer *m_hideScrollbarTimer = nullptr;
    SearchFunction m_searchFunc;

    ProcessListItem *m_lastItem = nullptr;
    QList<ProcessListItem*> *m_listItems;
    QList<ProcessListItem*> *m_searchedItems;
    QList<ProcessListItem*> *m_selectedItems;
    QList<QString> columnTitles;
    QList<SortFunction> *m_sortFuncList;
    QList<bool> *m_isSortList;
    QList<int> m_columnWidths;
    QList<bool> m_columnVisibles;
    QString m_searchText;

    bool m_isSort;
    bool m_mouseAtScrollArea;
    bool m_mouseDragScrollbar;
    int m_currentSortIndex;
    int m_origOffset;
    int m_offSet;
    int m_rowHeight;
    int m_scrollbarWidth;
    int m_titleHeight;
    int m_titleHoverColumn;
    int m_titlePadding;
    int m_titlePressColumn;

    QPixmap m_downArrowPixmap;
    QPixmap m_upArrowPixmap;
};

#endif // PROCESSLISTWIDGET_H
