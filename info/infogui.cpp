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

#include "infogui.h"
#include "infounitwidget.h"

#include <QApplication>
#include <QResizeEvent>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QDebug>

InfoGui::InfoGui(QWidget *parent)
    : QWidget(parent)
{
//    this->setAutoFillBackground(true);
//    QPalette palette;
//    palette.setColor(QPalette::Background, QColor("#0d87ca"));
//    this->setPalette(palette);
//    setFixedSize(750, 403);
//    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setStyleSheet("QWidget {background-color: rgba(255, 255, 255, 0.1);border:none;}");
    this->resize(750, parent->size().height());
    m_infoGuiName = "";

    m_vLayout = new QVBoxLayout,
    m_widget = new QFrame;
    m_scrollArea = new QScrollArea;
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollArea->setStyleSheet("QScrollArea{border: none;background-color: #ffffff;}");

    m_vLayout->setSpacing(10);
    m_vLayout->setMargin(0);
    m_widget->setLayout(m_vLayout);

    m_widget->setFixedWidth(750);//m_scrollArea->width()
    m_scrollArea->setWidget(m_widget);

    QVBoxLayout *layout = new QVBoxLayout;//QHBoxLayout *mainLayout = static_cast<QHBoxLayout *>(layout());
    layout->addWidget(m_scrollArea);
    layout->setContentsMargins(5, 5, 5, 5);
    layout->setSpacing(0);

    this->setLayout(layout);

//    this->loadOnePage(0, "AAA1", QMap<QString, QVariant>());
//    this->loadOnePage(1, "AAA2", QMap<QString, QVariant>());
}

const QString InfoGui::infoGuiName() const
{
    return this->m_infoGuiName;
}

void InfoGui::setInfoGuiName(const QString &name)
{
    if (name != m_infoGuiName)
        m_infoGuiName = name;
}

InfoGui::~InfoGui()
{
    qDeleteAll(m_pageList);
    m_pageList.clear();

    if (m_vLayout) {
        delete m_vLayout;
        m_vLayout = nullptr;
    }
    if (m_widget) {
        delete m_widget;
        m_widget = nullptr;
    }
    if (m_scrollArea) {
        delete m_scrollArea;
        m_scrollArea = nullptr;
    }
}

void InfoGui::clearWidget()
{
    qDeleteAll(m_pageList);
    m_pageList.clear();
}

void InfoGui::loadOnePage(int index, const QString &title, QMap<QString, QVariant> infoMap)
{
    InfoUnitWidget *w = new InfoUnitWidget(title, this);
    QMap<QString,QVariant>::iterator it; //遍历map

    for (it = infoMap.begin(); it != infoMap.end(); ++it) {
        QString valueStr = it.value().toString().trimmed();
        if (QString::compare(valueStr, "UNKOWN", Qt::CaseInsensitive) == 0 || QString::compare(valueStr, "UNKNOWN", Qt::CaseInsensitive) == 0) {//for arm memory
            //do nothing
        }
        else if (it.key().length() > 0 && valueStr.length() > 0) {
            if (it.key() == "MemVendor") {
                w->setInfoVendor(":/vendor/res/manufacturer/" + valueStr.toUpper() + ".jpg");
            }
            else if (it.key() == "BoaVendor") {
                w->setInfoVendor(":/vendor/res/manufacturer/" + valueStr.toUpper() + ".jpg");
            }
            else if (it.key() == "DiskVendor") {
                w->setInfoVendor(":/vendor/res/manufacturer/" + valueStr.toUpper() + ".jpg");
            }
            else if (it.key() == "Vga_vendor") {
                w->setInfoVendor(":/vendor/res/manufacturer/" + valueStr.toUpper() + ".jpg");
            }
            else if (it.key() == "MulVendor") {
                w->setInfoVendor(":/vendor/res/manufacturer/" + valueStr.toUpper() + ".jpg");
            }
            else if (it.key() == "POWER_SUPPLY_MANUFACTURER") {
                w->setInfoVendor(":/vendor/res/manufacturer/" + valueStr.toUpper() + ".jpg");
            }
            else {
                if (it.key().contains("INTEL"))
                    w->setInfoVendor(":/vendor/res/manufacturer/INTEL.jpg");
                else if (it.key().contains("REALTEK"))
                    w->setInfoVendor(":/vendor/res/manufacturer/REALTEK.jpg");
            }
            w->addInfoItem(it.key(), valueStr);
        }
    }
    m_vLayout->addWidget(w, 0, Qt::AlignTop);//m_vLayout->insertWidget(index, w);
    m_pageList.append(w);
}

void InfoGui::updatePageData(const QString &title, QMap<QString, QVariant> infoMap)
{
    if (m_pageList.count() <= 0) {
        InfoUnitWidget *m_testWidget = new InfoUnitWidget(title);
        QMap<QString,QVariant>::iterator it; //遍历map
        for (it = infoMap.begin(); it != infoMap.end(); ++it) {
            QString valueStr = it.value().toString().trimmed();
            if (QString::compare(valueStr, "UNKOWN", Qt::CaseInsensitive) == 0 || QString::compare(valueStr, "UNKNOWN", Qt::CaseInsensitive) == 0) {//for arm memory
                //do nothing
            }
            else if (it.key().length() > 0 && valueStr.length() > 0) {
                m_testWidget->addInfoItem(it.key(), valueStr);
            }
        }
        m_vLayout->addWidget(m_testWidget, 0, Qt::AlignTop);//m_vLayout->insertWidget(index, m_testWidget);
        m_pageList.append(m_testWidget);
    }

    foreach (InfoUnitWidget *widget, m_pageList) {
        if (widget->title() == title) {
            QMap<QString,QVariant>::iterator it; //遍历map
            for (it = infoMap.begin(); it != infoMap.end(); ++it) {
                QString valueStr = it.value().toString().trimmed();
                if (QString::compare(valueStr, "UNKOWN", Qt::CaseInsensitive) == 0 || QString::compare(valueStr, "UNKNOWN", Qt::CaseInsensitive) == 0) {//for arm memory
                    //do nothing
                }
                else if (it.key().length() > 0 && valueStr.length() > 0) {
                    widget->refreshInfoItem(it.key(), valueStr);
                }
            }
            break;
        }
    }


}

void InfoGui::updateRunningTime(const QString &runningTime)
{
    foreach (InfoUnitWidget *widget, m_pageList) {
        int index = widget->getCurrentRunningTimeUIIndex();
        if (index >= 0) {
//            getInfoItem
        }
    }
}
