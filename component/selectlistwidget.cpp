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

#include "selectlistwidget.h"
#include "utils.h"
#include <QDebug>
#include <QStringList>

SelectListWidget::SelectListWidget(bool hasTip, QWidget *parent) :
    QWidget(parent)
  , m_hasTip(hasTip)
{
    this->setStyleSheet("QWidget{background-color:transparent;}");
    m_gridLayout = new QGridLayout(this);
    m_gridLayout->setContentsMargins(ITEM_LEFT_RIGHT_PADDING,0,ITEM_LEFT_RIGHT_PADDING,0);
    m_gridLayout->setVerticalSpacing(0);
    m_widget = new QWidget(this);
    m_widget->setObjectName("transparentWidget");
    m_listAreaWidgetLayout = new QVBoxLayout(m_widget);
    m_listAreaWidgetLayout->setContentsMargins(0,0,0,0);
    m_scrollArea = new QScrollArea(this);
    m_scrollArea->setStyleSheet("QScrollArea{border:none;background-color:#ffffff;}");
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setWidget(m_widget);

    if (hasTip) {
        m_gridLayout->addWidget(m_scrollArea);
    }
    else {
        m_titleLabel = new QLabel;
        m_titleLabel->setFixedHeight(30);
        m_titleLabel->setIndent(30);
        m_titleLabel->setStyleSheet("QLabel{background-color:white;color:#000000;font-family: 方正黑体_GBK;font-size:12px;text-align:left;}");
        m_titleLabel->setText(tr("Clean Items:"));
        m_gridLayout->addWidget(m_titleLabel,1,0,5,5/*, Qt::AlignLeft | Qt::AlignVCenter*/);
        m_gridLayout->addWidget(m_scrollArea,0,0,1,5);
    }

    resetToDefault();
}

SelectListWidget::~SelectListWidget()
{
    this->resetToDefault();
}

void SelectListWidget::loadListItems(const QString &title, const QStringList &cachelist, const QStringList &baklist, int itemWidth)
{
    cacheitem.clear();
    cacheitem = baklist;

    m_itemsMap.clear();
    int count = 0;
    for (int i = 0; i < baklist.length(); ++i) {
        SelectListItem *item = new SelectListItem(0, baklist.at(i), "", false, itemWidth-2*ITEM_LEFT_RIGHT_PADDING, cachelist.at(i) != "");
        connect(item, SIGNAL(selectedSignal(bool,QString)), this, SLOT(onSelectedSignal(bool,QString)));
        m_listAreaWidgetLayout->addWidget(item);
        m_itemsMap.insert(baklist.at(i), item);
        if(cachelist.at(i) != "")
            count ++;
    }
    m_titleLabel->setText(QString("%1 %2").arg(tr("Clean Items:")).arg(QString::number(count)));
    m_listAreaWidgetLayout->addStretch();
}

void SelectListWidget::loadListItemsWithTips(const QStringList &arglist, const QStringList &statuslist, const QStringList &baklist, int itemWidth)
{
    if (arglist.length() != statuslist.length())
        return;

    itemlist.clear();
    itemlist = baklist;

    if(baklist.isEmpty()){
        m_listAreaWidgetLayout->addStretch();
        QLabel *tip_labrl = new QLabel(tr("No items to clean"));
        tip_labrl->setAlignment(Qt::AlignCenter);
        tip_labrl->setFixedSize(itemWidth,60);
        tip_labrl->setStyleSheet("QLabel{font-size:18px;color:gray;}");
        m_listAreaWidgetLayout->addWidget(tip_labrl);
        m_listAreaWidgetLayout->addStretch();

        return;
    }

    m_itemsMap.clear();

    for (int i = 0; i < arglist.length(); ++i) {
        SelectListItem *item = new SelectListItem(0, arglist.at(i), baklist.at(i), true, itemWidth-2*ITEM_LEFT_RIGHT_PADDING, statuslist.at(i) != "");
        connect(item, SIGNAL(selectedSignal(bool,QString)), this, SLOT(onSelectedSignal(bool,QString)));
        item->setMaximumSize(itemWidth, 30);
        m_listAreaWidgetLayout->addWidget(item);
        m_itemsMap.insert(arglist.at(i), item);
    }

    m_listAreaWidgetLayout->addStretch();
}

void SelectListWidget::removeOneItem(const QString &description)
{
    SelectListItem *item = m_itemsMap.value(description);
    if(item == Q_NULLPTR)
        return;
}

QStringList SelectListWidget::getSelectedItems()
{
//    QStringList text_list;

    /*foreach (QString text, m_itemsMap.keys()) {

    }*/
    QMap<QString, SelectListItem*>::iterator it;
    for (it = m_itemsMap.begin(); it != m_itemsMap.end(); ++it) {
        SelectListItem *item = static_cast<SelectListItem *>(it.value());
        if (!item->itemIsChecked()){
//            text_list.append(item->itemDescription());
            itemlist.replaceInStrings(item->itemDescription(),"",Qt::CaseInsensitive);
        }
    }

    return itemlist;
}

QStringList SelectListWidget::getSelectedItemsAll()
{
    /*foreach (QString text, m_itemsMap.keys()) {

    }*/
    QMap<QString, SelectListItem*>::iterator it;
    for (it = m_itemsMap.begin(); it != m_itemsMap.end(); ++it) {
        SelectListItem *item = static_cast<SelectListItem *>(it.value());
        if (!item->itemIsChecked()){
            cacheitem.replaceInStrings(item->itemDescription(),"",Qt::CaseInsensitive);
        }
    }
    qDebug() << Q_FUNC_INFO << cacheitem;
    return cacheitem;
}

void SelectListWidget::scanAllSubCheckbox()
{
    int selectedCount = 0;
    QMap<QString, SelectListItem*>::iterator it;
    for (it = m_itemsMap.begin(); it != m_itemsMap.end(); ++it) {
        SelectListItem *item = static_cast<SelectListItem *>(it.value());
        if (item->itemIsChecked())
            selectedCount += 1;
    }
    if (!m_hasTip)
        m_titleLabel->setText(QString("%1 %2").arg(tr("Clean Items:")).arg(QString::number(selectedCount)));

    if (selectedCount == 0) {
        emit this->notifyMainCheckBox(0);
    }
    else if (selectedCount == m_itemsMap.count()) {
        emit this->notifyMainCheckBox(2);
    }
    else {
        emit this->notifyMainCheckBox(1);
    }

    /*int count = checkbox_list.count();
    int m = 0;
    for(int i=0; i<count; i++)
    {
        QCheckBox *checkbox = checkbox_list.at(i);
        if (checkbox->isChecked()) {
            m +=1;
        }
    }
    num_label->setText(QString::number(m));
    if (m == 0) {
        emit this->notifyMainCheckBox(0);
    }
    else if (m == count) {
        emit this->notifyMainCheckBox(2);
    }
    else {
        emit this->notifyMainCheckBox(1);
    }*/
}

void SelectListWidget::resetSubCheckbox(int status)
{
    /*if(status == 0) {
        for(int i=0; i<checkbox_list.count(); i++)
        {
            QCheckBox *checkbox = checkbox_list.at(i);
            checkbox->setChecked(false);
        }
        num_label->setText("0");
    }
    else if(status == 2) {
        for(int i=0; i<checkbox_list.count(); i++)
        {
            QCheckBox *checkbox = checkbox_list.at(i);
            checkbox->setChecked(true);
        }
        int count = checkbox_list.count();
        num_label->setText(QString::number(count));
    }*/
}

void SelectListWidget::onSelectedSignal(bool checked, QString description)
{
    this->scanAllSubCheckbox();
}

void SelectListWidget::resetToDefault()
{
    m_itemsMap.clear();
    while(m_listAreaWidgetLayout->count() > 0) {
        QWidget* widget = m_listAreaWidgetLayout->itemAt(0)->widget();
        m_listAreaWidgetLayout->removeWidget(widget);
        delete widget;
    }
}
