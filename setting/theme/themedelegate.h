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

#ifndef THEMEDELEGATE_H
#define THEMEDELEGATE_H

#include <QStyledItemDelegate>

class ThemeDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit ThemeDelegate(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setEditorData(QWidget* editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex &index) const Q_DECL_OVERRIDE;
//    bool editorEvent(QEvent* event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;

    void drawBackground(const QStyleOptionViewItem &option, QPainter *painter) const;
    void drawImage(const QStyleOptionViewItem &option, const QModelIndex &index, QPainter *painter) const;
    void drawTitle(const QStyleOptionViewItem &option, const QModelIndex &index, QPainter *painter) const;

private:
    QColor m_textColor;
};

#endif // THEMEDELEGATE_H
