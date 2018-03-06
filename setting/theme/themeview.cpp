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

#include "themeview.h"
#include "themedelegate.h"

#include <QApplication>
#include <QMouseEvent>
#include <QDebug>

namespace {

const QSize THEME_ITEM_DEFAULT_SIZE = QSize(139, 160);

}

ThemeView::ThemeView(QWidget *parent)
    : QListView(parent)
    , m_itemSize(THEME_ITEM_DEFAULT_SIZE)
    , m_prevModelIndex(QModelIndex())
{
    setMouseTracking(true);

    m_delegate = new ThemeDelegate(this);
    setItemDelegate(m_delegate);

    m_model = new QStandardItemModel(this);
    setModel(m_model);

    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setResizeMode(QListView::Adjust);
    setViewMode(QListView::IconMode);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setUniformItemSizes(true);
    setSpacing(60);
    setDragEnabled(false);

//    connect(this, SIGNAL(ri))
    connect(this, &ThemeView::doubleClicked, this, &ThemeView::onItemClicked);
    connect(this, &ThemeView::clicked, this, &ThemeView::onItemClicked);
    connect(selectionModel(), &QItemSelectionModel::currentChanged, this, [=] (const QModelIndex &current) {
        if (!current.isValid())
            return;

        if (m_prevModelIndex.isValid()) {//update the previous model index's data
            QList<QVariant> datas = m_prevModelIndex.model()->data(m_prevModelIndex, Qt::DisplayRole).toList();
            if (!datas.isEmpty()) {
                datas.replace(3, QVariant(false));
                m_model->setData(m_prevModelIndex, QVariant(datas), Qt::DisplayRole);
                m_model->setData(m_prevModelIndex, QVariant(m_itemSize), Qt::SizeHintRole);
            }
        }

        m_prevModelIndex = current;
    });
}

ThemeView::~ThemeView()
{
    this->clearData();
}

void ThemeView::clearData()
{
    setAutoScroll(false);
    for (int i = 0; i < this->m_model->rowCount(); ++i) {
        this->m_model->removeRow(i);
    }
    setAutoScroll(true);
    m_prevModelIndex = QModelIndex();
}

QModelIndex ThemeView::loadThemeData(const QString &name, bool isCurrrent)
{
    QVariantList datas;
    datas.append(QVariant(name));//theme name
    datas.append(QVariant(QString(":/gtk/res/theme/%1.png").arg(name)));//theme picture
    datas.append(QVariant(":/gtk/res/theme/disappear.png"));//default picture
    datas.append(QVariant(isCurrrent));

    QModelIndex index;
    const int existIndex = isExist(name);
    if (existIndex != -1) {//it exist, then update data
        index = m_model->index(existIndex, 0);
    }
    else {//it not exist, then new item
        QStandardItem *item = new QStandardItem();
        QList<QStandardItem *> items;
        items.append(item);
        m_model->appendRow(items);
        index = m_model->index(m_model->rowCount() - 1, 0);
    }

    m_model->setData(index, QVariant(datas), Qt::DisplayRole);
    m_model->setData(index, QVariant(m_itemSize), Qt::SizeHintRole);

    return index;
}

QSize ThemeView::itemSize() const
{
    return m_itemSize;
}

int ThemeView::isExist(const QString &name) const
{
    for (int i = 0; i < m_model->rowCount(); i++) {
        const QVariantList datas = m_model->data(m_model->index(i, 0), Qt::DisplayRole).toList();
        if (!datas.isEmpty() && datas[0].toString() == name) {
            return i;
        }
    }

    return -1;
}

void ThemeView::onItemClicked(const QModelIndex &index)
{
    if (!index.isValid())
        return;

    QList<QVariant> datas = index.model()->data(index, Qt::DisplayRole).toList();
    if (!datas.isEmpty()) {
        const QString name = datas[0].toString();
        const int ti = isExist(name);
        if (ti != -1) {//it must be exist, then update the current model index's data
            datas.replace(3, QVariant(true));
            m_model->setData(index, QVariant(datas), Qt::DisplayRole);
            m_model->setData(index, QVariant(m_itemSize), Qt::SizeHintRole);
            setCurrentIndex(index);

            emit this->sendSelectThemeName(name);
        }
    }
}

void ThemeView::loadOneTheme(const QString &name, bool isCurrrent)
{
    QModelIndex index = loadThemeData(name, isCurrrent);
    if (isCurrrent)
        setCurrentIndex(index);

    scrollTo(m_model->index(index.row() + 1, 0, index.parent()));
}

void ThemeView::mousePressEvent(QMouseEvent *e)
{
    if (!indexAt(e->pos()).isValid()) {
        this->selectionModel()->clearSelection();
    }

    QListView::mousePressEvent(e);
}

/*bool ThemeView::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *me = (QMouseEvent *)event;
    }


    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        qDebug("Key press %d", keyEvent->key());
        if (keyEvent->key() == Qt::Key_Tab) {

        }
        else if (keyEvent->key() == Qt::Key_Escape) {

        }
        return true;
    }
    else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}*/
