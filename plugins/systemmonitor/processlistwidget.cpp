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

#include "processlistwidget.h"
#include <QTimer>
#include <QApplication>
#include <QDebug>
#include <QEvent>
#include <QMenu>
#include <QStyleFactory>
#include <QWheelEvent>
#include <QPainter>
#include <QtMath>
#include <QPen>

ProcessListWidget::ProcessListWidget(QList<bool> toBeDisplayedColumns, QWidget *parent) : QWidget(parent)
  ,m_titlePadding(10)
  ,m_titleHeight(40)
  ,m_rowHeight(29)
  ,m_offSet(0)
  ,m_origOffset(0)
  ,m_scrollbarWidth(10)
  ,m_titleHoverColumn(-1)
  ,m_titlePressColumn(-1)
  ,m_mouseAtScrollArea(false)
  ,m_mouseDragScrollbar(false)
{
    this->m_searchFunc = NULL;
    this->m_searchText = "";
    this->m_lastItem = NULL;
    this->m_listItems = new QList<ProcessListItem*>();
    this->m_searchedItems = new QList<ProcessListItem*>();
    this->m_selectedItems = new QList<ProcessListItem*>();

    this->m_sortFuncList = new QList<SortFunction>();
    this->m_isSortList = new QList<bool>();

    this->m_downArrowPixmap = QPixmap(":/res/arrow_down.png");
    this->m_upArrowPixmap = QPixmap(":/res/arrow_up.png");

    this->columnTitles << tr("Process Name") << tr("User") << tr("Status") << tr("CPU") << tr("ID") << tr("Command Line") << tr("Memory") << tr("Priority");
    QList<int> widths;
    widths << 180 << 80 << 80 << 60 << 50 << -1 << 80 << 80;//-1时让改行填充所有剩余空间

    QFont font;
    font.setPixelSize(12);//需要和填充所有剩余空间的那个的文字字体大小一致 font.setPointSize(9)
    QFontMetrics fm(font);

    this->m_columnWidths.clear();
    for (int i = 0; i < widths.length(); i++) {
        if (widths[i] == -1) {
            this->m_columnWidths << widths[i];
        } else {//-1时让改行填充所有剩余空间
            int maxWidth = fm.width(this->columnTitles[i]) + this->m_titlePadding + m_upArrowPixmap.width() / m_upArrowPixmap.devicePixelRatio() + 2 * 2;
            this->m_columnWidths << std::max(widths[i], maxWidth);
        }
    }

    this->m_columnVisibles.clear();
    for (int i = 0; i < toBeDisplayedColumns.count(); i++) {
        this->m_columnVisibles.append(toBeDisplayedColumns[i]);
    }

    this->setFocus();
}

ProcessListWidget::~ProcessListWidget()
{
    if (this->m_hideScrollbarTimer != NULL) {
        disconnect(this->m_hideScrollbarTimer,SIGNAL(timeout()),this,SLOT(hideScrollbar()));
        if(this->m_hideScrollbarTimer->isActive()) {
            this->m_hideScrollbarTimer->stop();
        }
        delete this->m_hideScrollbarTimer;
        this->m_hideScrollbarTimer = nullptr;
    }
    delete this->m_lastItem;
    delete this->m_listItems;
    delete this->m_searchedItems;
    delete this->m_selectedItems;
    delete this->m_sortFuncList;
    delete this->m_isSortList;
}

void ProcessListWidget::setProcessSortFunctions(QList<SortFunction> *list, int currentSortIndex, bool isSort)
{
    this->m_sortFuncList = list;

    for (int i = 0; i < this->m_sortFuncList->count(); i++) {
        this->m_isSortList->append(false);
    }
    this->m_currentSortIndex = currentSortIndex;
    this->m_isSort = isSort;
}

void ProcessListWidget::setSearchFunction(SearchFunction func)
{
    this->m_searchFunc = func;
}

void ProcessListWidget::addItems(QList<ProcessListItem*> items)
{
    this->m_listItems->append(items);
    QList<ProcessListItem*> s_items = this->getSearchedItems(items);
    this->m_searchedItems->append(s_items);
    if (this->m_currentSortIndex != -1) {
        this->sortItemsByColumn(this->m_currentSortIndex, this->m_isSort);
    }
}

void ProcessListWidget::clearItems()
{
    qDeleteAll(this->m_listItems->begin(), this->m_listItems->end());
    this->m_listItems->clear();
    this->m_searchedItems->clear();
}

void ProcessListWidget::addSelectedItems(QList<ProcessListItem*> items, bool recordLastItem)
{
    this->m_selectedItems->append(items);

    if (recordLastItem && this->m_selectedItems->count() > 0) {
        this->m_lastItem = this->m_selectedItems->last();
    }
}

void ProcessListWidget::clearSelectedItems(bool clearLast)
{
    this->m_selectedItems->clear();
    if (clearLast) {
        this->m_lastItem = NULL;
    }
}

void ProcessListWidget::refreshItems(QList<ProcessListItem*> items)
{
    QList<ProcessListItem*> *allItems = new QList<ProcessListItem*>();
    ProcessListItem *newLastItem = NULL;

    for (ProcessListItem *item:items) {
        for (ProcessListItem *selectionItem:*this->m_selectedItems) {
            if (item->isSameItem(selectionItem)) {
                allItems->append(item);
                break;
            }
        }
    }
    if (this->m_lastItem != NULL) {
        for (ProcessListItem *item:items) {
            if (item->isSameItem(this->m_lastItem)) {
                newLastItem = item;
                break;
            }
        }
    }

    clearItems();
    this->m_listItems->append(items);
    QList<ProcessListItem*> s_items = this->getSearchedItems(items);
    this->m_searchedItems->append(s_items);

    if (this->m_currentSortIndex != -1) {
        this->sortItemsByColumn(this->m_currentSortIndex, this->m_isSort);
    }

    clearSelectedItems();
    addSelectedItems(*allItems, false);

    this->m_lastItem = newLastItem;
    this->m_offSet = setOffset(this->m_offSet);

    repaint();
}

void ProcessListWidget::doSearch(QString text)
{
    if (text == "" && this->m_searchText != text) {
        this->m_searchText = text;
        this->m_searchedItems->clear();
        this->m_searchedItems->append(*this->m_listItems);
    } else {
        this->m_searchText = text;
        QList<ProcessListItem*> s_items = this->getSearchedItems(*this->m_listItems);
        this->m_searchedItems->clear();
        this->m_searchedItems->append(s_items);
    }

    repaint();
}

void ProcessListWidget::selectTheFirstItem()
{
    this->m_origOffset = this->m_offSet;

    clearSelectedItems();

    QList<ProcessListItem*> items = QList<ProcessListItem*>();
    items << this->m_searchedItems->first();
    addSelectedItems(items);

    this->m_offSet = 0;

    repaint();
}

void ProcessListWidget::selectTheLastItem()
{
    this->m_origOffset = this->m_offSet;

    clearSelectedItems();

    QList<ProcessListItem*> items = QList<ProcessListItem*>();
    items << this->m_searchedItems->last();
    addSelectedItems(items);

    this->m_offSet = getBottomOffset();

    repaint();
}

void ProcessListWidget::selectThePrevItem(int offset)
{
    this->m_origOffset = this->m_offSet;

    if (this->m_selectedItems->empty()) {
        selectTheFirstItem();
    } else {
        int firstIndex = this->m_searchedItems->count();
        for (ProcessListItem *item:*this->m_selectedItems) {
            int index = this->m_searchedItems->indexOf(item);
            if (index < firstIndex) {
                firstIndex = index;
            }
        }

        if (firstIndex != -1) {
            firstIndex = std::max(0, firstIndex - offset);
            clearSelectedItems();
            QList<ProcessListItem*> items = QList<ProcessListItem*>();
            items << (*this->m_searchedItems)[firstIndex];
            addSelectedItems(items);
            int itemIndex = firstIndex - 1;
            int itemOffset = setOffset(itemIndex * this->m_rowHeight + this->m_titleHeight);
            if ((this->m_offSet / this->m_rowHeight) > itemIndex) {
                this->m_offSet = itemOffset;
            }
            repaint();
        }
    }
}

void ProcessListWidget::selectTheNextItem(int offset)
{
    this->m_origOffset = this->m_offSet;

    if (this->m_selectedItems->empty()) {
        selectTheFirstItem();
    } else {
        int lastIndex = 0;
        for (ProcessListItem *item:*this->m_selectedItems) {
            int index = this->m_searchedItems->indexOf(item);
            if (index > lastIndex) {
                lastIndex = index;
            }
        }

        if (lastIndex != -1) {
            lastIndex = std::min(this->m_searchedItems->count() - 1, lastIndex + offset);

            clearSelectedItems(false);

            QList<ProcessListItem*> items = QList<ProcessListItem*>();
            items << (*this->m_searchedItems)[lastIndex];

            addSelectedItems(items);

            int itemIndex = lastIndex + 1;
            int itemOffset = setOffset(itemIndex * this->m_rowHeight - rect().height() + this->m_titleHeight);
            if (((this->m_offSet + getTheScrollAreaHeight()) / this->m_rowHeight) < itemIndex) {
                this->m_offSet = itemOffset;
            }

            repaint();
        }
    }
}

void ProcessListWidget::shiftToHomeItem()
{
    if (this->m_selectedItems->empty()) {
        selectTheFirstItem();
    }
    else {
        int lastSelectionIndex = this->m_searchedItems->indexOf(this->m_lastItem);
        shiftToSelectedItems(0, lastSelectionIndex);
        this->m_offSet = 0;
        repaint();
    }
}

void ProcessListWidget::shiftToEndItem()
{
    if (this->m_selectedItems->empty()) {
        selectTheLastItem();
    }
    else {
        shiftToSelectedItems(this->m_searchedItems->indexOf(this->m_lastItem), this->m_searchedItems->count() - 1);
        this->m_offSet = getBottomOffset();
        repaint();
    }
}

void ProcessListWidget::shiftToPrevItem(int offset)
{
    this->m_origOffset = this->m_offSet;
    if (this->m_selectedItems->empty()) {
        selectTheFirstItem();
    }
    else {
        int firstIndex = this->m_searchedItems->count();
        int lastIndex = 0;
        for (ProcessListItem *item : *this->m_selectedItems) {
            int index = this->m_searchedItems->indexOf(item);
            if (index < firstIndex) {
                firstIndex = index;
            }
            if (index > lastIndex) {
                lastIndex = index;
            }
        }

        if (firstIndex != -1) {
            int lastSelectionIndex = this->m_searchedItems->indexOf(this->m_lastItem);
            int selectionStartIndex, selectionEndIndex;
            if (lastIndex == lastSelectionIndex) {
                selectionStartIndex = std::max(0, firstIndex - offset);
                selectionEndIndex = lastSelectionIndex;
            } else {
                selectionStartIndex = firstIndex;
                selectionEndIndex = std::max(0, lastIndex - offset);
            }
            shiftToSelectedItems(selectionStartIndex, selectionEndIndex);
            if (this->m_offSet / this->m_rowHeight >= selectionStartIndex) {
                this->m_offSet = setOffset((selectionStartIndex - 1) * this->m_rowHeight + this->m_titleHeight);
            }
            repaint();
        }
    }
}

void ProcessListWidget::shiftToNextItem(int offset)
{
    this->m_origOffset = this->m_offSet;

    if (this->m_selectedItems->empty()) {
        selectTheFirstItem();
    } else {
        int firstIndex = this->m_searchedItems->count();
        int lastIndex = 0;
        for (ProcessListItem *item:*this->m_selectedItems) {
            int index = this->m_searchedItems->indexOf(item);

            if (index < firstIndex) {
                firstIndex = index;
            }

            if (index > lastIndex) {
                lastIndex = index;
            }
        }

        if (firstIndex != -1) {
            int lastSelectionIndex = this->m_searchedItems->indexOf(this->m_lastItem);
            int selectionStartIndex, selectionEndIndex;

            if (firstIndex == lastSelectionIndex) {
                selectionStartIndex = firstIndex;
                selectionEndIndex = std::min(this->m_searchedItems->count() - 1, lastIndex + offset);
            } else {
                selectionStartIndex = std::min(this->m_searchedItems->count() - 1, firstIndex + offset);
                selectionEndIndex = lastIndex;
            }

            shiftToSelectedItems(selectionStartIndex, selectionEndIndex);

            if ((this->m_offSet + rect().height()) / this->m_rowHeight <= selectionEndIndex + 1) {
                this->m_offSet = setOffset((selectionEndIndex + 1) * this->m_rowHeight + this->m_titleHeight - rect().height());
            }


            repaint();
        }
    }
}

void ProcessListWidget::shiftToSelectedItems(int start, int end)
{
    clearSelectedItems(false);
    QList<ProcessListItem*> items = QList<ProcessListItem*>();
    int index = 0;
    for (ProcessListItem *item:*this->m_searchedItems) {
        if (index >= start && index <= end) {
            items << item;
        }

        index++;
    }
    addSelectedItems(items, false);
}

void ProcessListWidget::leaveEvent(QEvent * event)
{
    hideScrollbar();
    QWidget::leaveEvent(event);
}

void ProcessListWidget::hideScrollbar()
{
    this->m_mouseAtScrollArea = false;
    this->m_origOffset = this->m_offSet;

    repaint();
}

void ProcessListWidget::keyPressEvent(QKeyEvent *keyEvent)
{
    if (keyEvent->key() == Qt::Key_Up) {
        if (keyEvent->modifiers() == Qt::ShiftModifier)
            shiftToPrevItem(1);
        else
            selectThePrevItem(1);
    }
    else if (keyEvent->key() == Qt::Key_Down) {
        if (keyEvent->modifiers() == Qt::ShiftModifier)
            shiftToNextItem(1);
        else
            selectTheNextItem(1);
    }
    else if (keyEvent->key() == Qt::Key_Home) {
        if (keyEvent->modifiers() == Qt::ControlModifier) {
            this->m_offSet = 0;
            repaint();
        }
        else if (keyEvent->modifiers() == Qt::ShiftModifier) {
            shiftToHomeItem();
        }
        else {
            selectTheFirstItem();
        }
    } else if (keyEvent->key() == Qt::Key_End) {
        if (keyEvent->modifiers() == Qt::ControlModifier) {
            this->m_offSet = getBottomOffset();
            repaint();
        }
        else if (keyEvent->modifiers() == Qt::ShiftModifier) {
            shiftToEndItem();
        }
        else {
            selectTheLastItem();
        }
    }
    else if (keyEvent->key() == Qt::Key_PageUp) {
        if (keyEvent->modifiers() == Qt::ControlModifier) {
            this->m_offSet = setOffset(this->m_offSet - getTheScrollAreaHeight());
            repaint();
        }
        else if (keyEvent->modifiers() == Qt::ShiftModifier) {
            shiftToPrevItem(getTheScrollAreaHeight() / this->m_rowHeight);
        }
        else {
            selectThePrevItem(getTheScrollAreaHeight() / this->m_rowHeight);
        }
    }
    else if (keyEvent->key() == Qt::Key_PageDown) {
        if (keyEvent->modifiers() == Qt::ControlModifier) {
            this->m_offSet = setOffset(this->m_offSet + getTheScrollAreaHeight());
            repaint();
        }
        else if (keyEvent->modifiers() == Qt::ShiftModifier) {
            shiftToNextItem(getTheScrollAreaHeight() / this->m_rowHeight);
        }
        else {
            selectTheNextItem(getTheScrollAreaHeight() / this->m_rowHeight);
        }
    }
}

void ProcessListWidget::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    if (this->m_mouseDragScrollbar) {
        this->m_offSet = setOffset((mouseEvent->y() - getScrollbarHeight() / 2 - this->m_titleHeight) / (getTheScrollAreaHeight() * 1.0) * this->getItemsTotalHeight());
        repaint();
    }
    else if (mouseAtScrollArea(mouseEvent->x()) != this->m_mouseAtScrollArea) {
        this->m_mouseAtScrollArea = mouseAtScrollArea(mouseEvent->x());
        repaint();
    }
    else {
        bool isTitleArea = mouseAtTitleArea(mouseEvent->y());
        if (isTitleArea) {
            int currentHoverIndex = -1;
            if (this->m_sortFuncList->count() != 0 && this->m_sortFuncList->count() == this->columnTitles.count() && this->m_isSortList->count() == this->columnTitles.count()) {
                QList<int> titleItemsWidths = getTitleItemsWidths();
                int counter = 0;
                int pos_X = 0;
                for (int t_width : titleItemsWidths) {
                    if (t_width > 0) {
                        if (mouseEvent->x() > pos_X && mouseEvent->x() < pos_X + t_width) {
                            currentHoverIndex = counter;
                            break;
                        }
                        pos_X += t_width;
                    }
                    counter++;
                }
            }
            if (currentHoverIndex != this->m_titleHoverColumn) {
                this->m_titleHoverColumn = currentHoverIndex;
                repaint();
            }
        }
    }
}

void ProcessListWidget::mousePressEvent(QMouseEvent *mouseEvent)
{
    setFocus();

    bool isTitleArea = mouseAtTitleArea(mouseEvent->y());
    bool isScrollArea = mouseAtScrollArea(mouseEvent->x());

    if (isTitleArea) {//点击列表的标题栏区域
        if (mouseEvent->button() == Qt::LeftButton) {
            if (this->m_sortFuncList->count() != 0 && this->m_sortFuncList->count() == this->columnTitles.count() && this->m_isSortList->count() == this->columnTitles.count()) {
                QList<int> titleItemsWidths = getTitleItemsWidths();
                int counter = 0;
                int posX = 0;
                for (int t_width : titleItemsWidths) {
                    if (t_width > 0) {
                        if (mouseEvent->x() > posX && mouseEvent->x() < posX + t_width) {
                            if (counter != this->m_currentSortIndex) {
                                (*this->m_isSortList)[counter] = true;
                            }
                            else {
                                (*this->m_isSortList)[counter] = !(*this->m_isSortList)[counter];
                            }
                            this->m_currentSortIndex = counter;
                            this->m_isSort = (*this->m_isSortList)[counter];
                            emit this->changeSortStatus(this->m_currentSortIndex, this->m_isSort);
                            this->sortItemsByColumn(counter, (*this->m_isSortList)[counter]);
                            if (counter != this->m_titlePressColumn) {
                                this->m_titlePressColumn = counter;
                            }
                            repaint();
                            break;
                        }
                        posX += t_width;
                    }
                    counter++;
                }
            }
        }
        else if (mouseEvent->button() == Qt::RightButton) {
            if (m_columnVisibles.count() == this->columnTitles.count()) {
                QMenu *menu = new QMenu();
                menu->setObjectName("MonitorMenu");
                for (int i = 0; i < m_columnVisibles.count(); i++) {
                    if (i != 0) {//让第一行总是显示，不可以设置显示或者不显示，其他行可以设置
                        QAction *action = new QAction(menu);
                        action->setText(this->columnTitles[i]);
                        action->setCheckable(true);
                        action->setChecked(m_columnVisibles[i]);
                        connect(action, &QAction::triggered, this, [this, action, i] {
                                m_columnVisibles[i] = !m_columnVisibles[i];
                                emit this->changeColumnVisible(i, m_columnVisibles[i], m_columnVisibles);
                                repaint();
                            });
                        menu->addAction(action);
                    }
                }
                menu->exec(this->mapToGlobal(mouseEvent->pos()));
                delete menu;
            }
        }
    }
    else if (isScrollArea) {//点击滚动条区域
        int barHeight = getScrollbarHeight();
        int barY = getScrollbarY();
        if (mouseEvent->y() > barY && mouseEvent->y() < barY + barHeight) {
            this->m_mouseDragScrollbar = true;
        }
        else {
            this->m_offSet = setOffset((mouseEvent->y() - barHeight / 2 - this->m_titleHeight) / (getTheScrollAreaHeight() * 1.0) * this->getItemsTotalHeight());
            repaint();
        }
    }
    else {
        int pressedItemIndex = (this->m_offSet + mouseEvent->y() - this->m_titleHeight) / this->m_rowHeight;
        if (pressedItemIndex >= this->m_searchedItems->count()) {
            clearSelectedItems();

            repaint();
        }
        else {
            if (mouseEvent->button() == Qt::LeftButton) {
                if (pressedItemIndex < this->m_searchedItems->count()) {
                    if (mouseEvent->modifiers() == Qt::ControlModifier) {
                        ProcessListItem *item = (*this->m_searchedItems)[pressedItemIndex];
                        if (this->m_selectedItems->contains(item)) {
                            this->m_selectedItems->removeOne(item);
                        } else {
                            QList<ProcessListItem*> items = QList<ProcessListItem*>();
                            items << item;
                            addSelectedItems(items);
                        }
                    }
                    else if ((mouseEvent->modifiers() == Qt::ShiftModifier) && !this->m_selectedItems->empty()) {
                        int lastSelectionIndex = this->m_searchedItems->indexOf(this->m_lastItem);
                        int selectionStartIndex = std::min(pressedItemIndex, lastSelectionIndex);
                        int selectionEndIndex = std::max(pressedItemIndex, lastSelectionIndex);
                        shiftToSelectedItems(selectionStartIndex, selectionEndIndex);
                    }
                    else {
                        clearSelectedItems();

                        QList<ProcessListItem*> items = QList<ProcessListItem*>();
                        items << (*this->m_searchedItems)[pressedItemIndex];
                        addSelectedItems(items);
                    }
                    repaint();
                }
            }
            else if (mouseEvent->button() == Qt::RightButton) {
                ProcessListItem *pressItem = (*this->m_searchedItems)[pressedItemIndex];
                bool pressInSelectionArea = false;
                for (ProcessListItem *item : *this->m_selectedItems) {
                    if (item == pressItem) {
                        pressInSelectionArea = true;
                        break;
                    }
                }
                if (!pressInSelectionArea && pressedItemIndex < this->m_searchedItems->length()) {
                    clearSelectedItems();
                    QList<ProcessListItem*> items = QList<ProcessListItem*>();
                    items << (*this->m_searchedItems)[pressedItemIndex];
                    addSelectedItems(items);
                    repaint();
                }
                if (this->m_selectedItems->length() > 0) {
                    emit this->rightMouseClickedItems(this->mapToGlobal(mouseEvent->pos()), *this->m_selectedItems);
                }
            }
        }
    }
}

void ProcessListWidget::mouseReleaseEvent(QMouseEvent *)
{
    if (this->m_mouseDragScrollbar) {
        this->m_mouseDragScrollbar = false;
        repaint();
    }
    else {
        if (this->m_titlePressColumn != -1) {
            this->m_titlePressColumn = -1;
            repaint();
        }
    }
}

void ProcessListWidget::wheelEvent(QWheelEvent *event)
{
    if (event->orientation() == Qt::Vertical) {
        this->m_origOffset = this->m_offSet;
        qreal scrollStep = event->angleDelta().y() / 100.0;
        this->m_offSet = setOffset(this->m_offSet - scrollStep * this->m_rowHeight);
        repaint();
    }
    event->accept();
}

void ProcessListWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QList<int> titleItemsWidths = getTitleItemsWidths();

    painter.setOpacity(0.05);

    int penWidth = 1;
    QPainterPath framePath;
    framePath.addRoundedRect(QRect(rect().x() + penWidth, rect().y() + penWidth, rect().width() - penWidth * 2, rect().height() - penWidth * 2), 5, 5);//背景弧度
    painter.setClipPath(framePath);

    //标题的背景
    if (this->m_titleHeight > 0) {
        QPainterPath titlePath;
        titlePath.addRect(QRectF(rect().x(), rect().y(), rect().width(), this->m_titleHeight));
        painter.setOpacity(0.02);
        painter.fillPath(titlePath, QColor("#ffffff"));
    }

    int title_Y = 0;
    int title_Height = 0;
    if (this->m_titleHeight > 0) {
        int counter = 0;
        int posX = 0;
        for (int itemWidth:titleItemsWidths) {
            if (itemWidth > 0) {
                //标题文字左上方的排序箭头图标
                if (this->m_currentSortIndex == counter) {
                    painter.setOpacity(1);
                    if (this->m_isSort) {
                        painter.drawPixmap(QPoint(rect().x() + posX + 5, rect().y() + 10), m_downArrowPixmap);
                    } else {
                        painter.drawPixmap(QPoint(rect().x() + posX + 5, rect().y() + 10), m_upArrowPixmap);
                    }
                }

                //标题文字
                painter.setOpacity(1);
                QFont font = painter.font();
//                font.setPointSize(10);
                font.setPixelSize(12);
                painter.setFont(font);
                painter.setPen(QPen(QColor("#999999")));

                if (this->columnTitles[counter] == tr("Process Name") || this->columnTitles[counter] == tr("Command Line") || this->columnTitles[counter] == tr("Priority"))
                    painter.drawText(QRect(posX + this->m_titlePadding, 0, itemWidth, this->m_titleHeight), Qt::AlignBottom | Qt::AlignLeft, this->columnTitles[counter]);
                else
                    painter.drawText(QRect(posX, 0, itemWidth - this->m_titlePadding, this->m_titleHeight), Qt::AlignBottom | Qt::AlignRight, this->columnTitles[counter]);

                //水平下划线
                painter.setOpacity(0.8);
                QPainterPath h_separatorPath;
                h_separatorPath.addRect(QRectF(posX, rect().y() + this->m_titleHeight - 1, itemWidth, 1));
                painter.fillPath(h_separatorPath, QColor("#e0e0e0"));

                if (counter < titleItemsWidths.size()) {//垂直分割线
                    QPainterPath v_separatorPath;
                    v_separatorPath.addRect(QRectF(rect().x() + posX - 1, rect().y() + 5, 1, this->m_titleHeight - 5));
                    painter.fillPath(v_separatorPath, QColor("#e0e0e0"));
                }

                posX += itemWidth;
            }
            counter++;
        }

        title_Y += this->m_titleHeight;
        title_Height += this->m_titleHeight;
    }

    //去掉列表标题栏后的列表显示区域的背景
    painter.setOpacity(0.05);
    QPainterPath backgroundPath;
    backgroundPath.addRect(QRectF(rect().x(), rect().y() + this->m_titleHeight, rect().width(), rect().height() - this->m_titleHeight));
    painter.fillPath(backgroundPath, QColor("#ffffff"));

    //进程信息
    QPainterPath scrollAreaPath;
    scrollAreaPath.addRect(QRectF(rect().x(), rect().y() + this->m_titleHeight, rect().width(), getTheScrollAreaHeight()));

    int rowCounter = 0;
    for (ProcessListItem *item:*this->m_searchedItems) {
        if (rowCounter > ((this->m_offSet - this->m_rowHeight) / this->m_rowHeight)) {
            QPainterPath itemPath;
            itemPath.addRect(QRect(0, title_Y + rowCounter * this->m_rowHeight - this->m_offSet, rect().width(), this->m_rowHeight));
            painter.setClipPath((framePath.intersected(scrollAreaPath)).intersected(itemPath));

            bool isSelect = this->m_selectedItems->contains(item);
            painter.save();
            item->drawBackground(QRect(0, title_Y + rowCounter * this->m_rowHeight - this->m_offSet, rect().width(), this->m_rowHeight), &painter, rowCounter, isSelect);
            painter.restore();

            int columnCounter = 0;
            int columnTitleX = 0;
            for (int titleItemWidth : titleItemsWidths) {
                if (titleItemWidth > 0) {
                    painter.save();
                    if (columnCounter < titleItemsWidths.size() - 1)
                        item->drawForeground(QRect(columnTitleX, title_Y + rowCounter * this->m_rowHeight - this->m_offSet, titleItemWidth, this->m_rowHeight), &painter, columnCounter, rowCounter, isSelect, true);
                    else
                        item->drawForeground(QRect(columnTitleX, title_Y + rowCounter * this->m_rowHeight - this->m_offSet, titleItemWidth, this->m_rowHeight), &painter, columnCounter, rowCounter, isSelect, false);
                    painter.restore();
                    columnTitleX += titleItemWidth;
                }
                columnCounter++;
            }
            title_Height += this->m_rowHeight;
            if (title_Height > rect().height()) {
                break;
            }
        }
        rowCounter++;
    }
    painter.setClipPath(framePath);

    //没有搜索结果时绘制提示文字
    if (this->m_searchText != "" && this->m_searchedItems->size() == 0) {
        painter.setOpacity(1);
        painter.setPen(QPen(QColor("#666666")));
        QFont font = painter.font() ;
        font.setPointSize(22);
        painter.setFont(font);
        painter.drawText(QRect(rect().x(), rect().y() + this->m_titleHeight, rect().width(), rect().height() - this->m_titleHeight), Qt::AlignCenter, tr("No search result"));
    }

    //背景
//    QPen framePen;
//    framePen.setColor(QColor("#F5F5F5"));
//    painter.setPen(framePen);
    painter.setOpacity(0.2);
    painter.drawPath(framePath);

    //垂直滚动条
    if (this->m_mouseAtScrollArea) {
        paintScrollbar(&painter);
    } else if (this->m_origOffset != this->m_offSet) {
        paintScrollbar(&painter);
        readyToHideScrollbar();
    }
}

void ProcessListWidget::paintScrollbar(QPainter *painter)
{
    if (this->getItemsTotalHeight() > getTheScrollAreaHeight()) {
        qreal opacitry = 0;
        if (this->m_mouseDragScrollbar) {
            opacitry = 0.8;
        }
        else {
            if (this->m_mouseAtScrollArea)
                opacitry = 0.7;
            else
                opacitry = 0.5;
        }

        int barWidth = (this->m_mouseAtScrollArea || this->m_mouseDragScrollbar) ? this->m_scrollbarWidth : 6;
        int barY = getScrollbarY();
        int barHeight = getScrollbarHeight();
        painter->setOpacity(opacitry);
        QPainterPath path;
        path.addRoundedRect(
            QRectF(rect().x() + rect().width() - barWidth - 4, barY + 2, barWidth, barHeight - 2 * 2), 2, 2);//2 is radius
        painter->fillPath(path, QColor("#0B95D7"));

        QPen pen;
        pen.setColor(QColor("#0B95D7"));
        pen.setWidth(1);
        painter->setOpacity(0);
        painter->setPen(pen);
        painter->drawPath(path);
    }
}

QList<int> ProcessListWidget::getTitleItemsWidths()
{
    QList<int> titleItemsWidths;
    if (this->m_columnWidths.length() > 0) {
        if (this->m_columnWidths.contains(-1)) {
            for (int i = 0; i < this->m_columnWidths.count(); i++) {
                if (this->m_columnWidths[i] != -1) {
                    if (m_columnVisibles[i]) {
                        titleItemsWidths << this->m_columnWidths[i];
                    } else {
                        titleItemsWidths << 0;
                    }
                } else {
                    if (m_columnVisibles[i]) {
                        int totalWidth = 0;
                        for (int j = 0; j < this->m_columnWidths.count(); j++) {
                            if (this->m_columnWidths[j] != -1 && m_columnVisibles[j]) {
                                totalWidth += this->m_columnWidths[j];
                            }
                        }
                        titleItemsWidths << rect().width() - totalWidth;
                    }
                    else {
                        titleItemsWidths << 0;
                    }
                }
            }
        } else {
            for (int i = 0; i < this->m_columnWidths.count(); i++) {
                if (m_columnVisibles[i]) {
                    titleItemsWidths << this->m_columnWidths[i];
                }
                else {
                    titleItemsWidths << 0;
                }
            }
        }
    }
    else {
        titleItemsWidths << rect().width();
    }

    return titleItemsWidths;
}

bool ProcessListWidget::mouseAtScrollArea(int x)
{
    return (x > rect().x() + rect().width() - this->m_scrollbarWidth) && (x < rect().x() + rect().width());
}

bool ProcessListWidget::mouseAtTitleArea(int y)
{
    return (y > rect().y() && y < rect().y() + this->m_titleHeight);
}

int ProcessListWidget::setOffset(int offset)
{
    return std::max(0, std::min(offset, getBottomOffset()));
}

int ProcessListWidget::getItemsTotalHeight()
{
    return m_searchedItems->count() * m_rowHeight;
}

int ProcessListWidget::getTheScrollAreaHeight()
{
    return this->rect().height() - this->m_titleHeight;
}

int ProcessListWidget::getScrollbarY()
{
    return static_cast<int>((this->m_offSet / (this->getItemsTotalHeight() * 1.0)) * getTheScrollAreaHeight() + this->m_titleHeight);
}

int ProcessListWidget::getScrollbarHeight()
{
    return std::max(static_cast<int>(getTheScrollAreaHeight() / (this->getItemsTotalHeight() * 1.0) * rect().height()), 30);//30 is min height
}

QList<ProcessListItem*> ProcessListWidget::getSearchedItems(QList<ProcessListItem*> items)
{
    if (m_searchText == "" || m_searchFunc == NULL) {
        return items;
    } else {
        QList<ProcessListItem*> *search_items = new QList<ProcessListItem*>();

        for (ProcessListItem *item : items) {
            if (m_searchFunc(item, m_searchText)) {
                search_items->append(item);
            }
        }
        return *search_items;
    }
}

int ProcessListWidget::getBottomOffset()
{
    int itemsHeight = this->getItemsTotalHeight();
    if (itemsHeight > rect().height() - this->m_titleHeight) {
        return this->getItemsTotalHeight() - rect().height() + this->m_titleHeight;
    } else {
        return 0;
    }
}

void ProcessListWidget::sortItemsByColumn(int column, bool isSort)
{
    if (m_sortFuncList->count() != 0 && m_sortFuncList->count() == columnTitles.count() && m_isSortList->count() == columnTitles.count()) {
        qSort(m_searchedItems->begin(), m_searchedItems->end(), [&](const ProcessListItem *item1, const ProcessListItem *item2) {
                return (*m_sortFuncList)[column](item1, item2, isSort);
            });
    }
}

void ProcessListWidget::readyToHideScrollbar()
{
    if (this->m_hideScrollbarTimer) {
         if (this->m_hideScrollbarTimer->isActive())
            this->m_hideScrollbarTimer->stop();
    }
    else {
        this->m_hideScrollbarTimer = new QTimer();
        this->m_hideScrollbarTimer->setSingleShot(true);
        connect(this->m_hideScrollbarTimer, SIGNAL(timeout()), this, SLOT(hideScrollbar()));
    }
    this->m_hideScrollbarTimer->start(2000);
}
