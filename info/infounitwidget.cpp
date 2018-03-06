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

#include "infounitwidget.h"
#include "infoitemline.h"
#include "infoitemsgroup.h"

#include <QEvent>
#include <QDebug>
#include <QPainter>

InfoUnitWidget::InfoUnitWidget(QString title, QWidget *parent)
    : QWidget(parent)
    , m_currentRunningTimeUIIndex(-1)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setStyleSheet("QWidget {background-color: rgba(255, 255, 255, 0.1);border-radius: 2px;}");

    //kobe: QHBoxLayout *mainLayout = static_cast<QHBoxLayout *>(layout());
    m_titleLabel = new QLabel;
    m_titleLabel->setStyleSheet("QLabel{background-color:transparent;color:#000000;font-size:15px;font-weight:bold;}");
    m_titleLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    m_titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    m_vendorLabel = new QLabel;
    m_titleLabel->setStyleSheet("QLabel{background-color:transparent;}");
    m_vendorLabel->setFixedSize(48, 48);

    this->setInfoTitle(title);

    QHBoxLayout *headerLayout = new QHBoxLayout;
    headerLayout->setContentsMargins(10, 0, 30, 0);
    headerLayout->addWidget(m_titleLabel);
    headerLayout->addStretch();
    headerLayout->addWidget(m_vendorLabel);
    headerLayout->setAlignment(m_vendorLabel, Qt::AlignCenter);

    QFrame *headerWidget = new QFrame;
    headerWidget->setStyleSheet("QFrame {padding:5px 0;} QFrame:hover {background-color:rgba(141,238,238,0.2);border-radius:4px;}");
    headerWidget->setLayout(headerLayout);

    m_infoLayout = new QVBoxLayout;
    m_infoLayout->addWidget(headerWidget);
    m_infoLayout->setSpacing(5);
    m_infoLayout->setMargin(0);
    m_infoLayout->setContentsMargins(0,0,0,0);

    m_infoItemsGroup = new InfoItemsGroup;
    m_infoLayout->addWidget(m_infoItemsGroup);

    setLayout(m_infoLayout);
//    m_infoItemsGroup->getInfoItem()
}

InfoUnitWidget::~InfoUnitWidget()
{
    m_currentRunningTimeUIIndex = -1;
    QList<InfoItemLine *> items = findChildren<InfoItemLine*>();
    for (InfoItemLine *item : items) {
        m_infoItemsGroup->removeItem(item);
        item->deleteLater();
    }
    if (m_infoItemsGroup) {
        delete m_infoItemsGroup;
        m_infoItemsGroup = 0;
    }
}

const QString InfoUnitWidget::title() const
{
    return m_titleLabel->text();
}

void InfoUnitWidget::setInfoTitle(const QString &title)
{
    m_titleLabel->setText(title);
    setAccessibleName(title);
}

void InfoUnitWidget::setInfoVendor(const QString &vendor)
{
    QPainterPath painterPath;
    painterPath.addEllipse(QRect(0, 0, 48, 48));

    QPixmap pixmap = QPixmap(vendor);
    if (pixmap.isNull())
        return;
    pixmap = pixmap.scaled(48, 48, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QPixmap pic(48, 48);
    pic.fill(Qt::transparent);
    QPainter painter(&pic);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setClipPath(painterPath);

    painter.drawPixmap(QRect(0, 0, 48, 48), pixmap);

    m_vendorLabel->setPixmap(pic);
}

void InfoUnitWidget::addInfoItem(const QString &key, const QString &value)
{
    InfoItemLine *w = new InfoItemLine;
    const int index = m_infoItemsGroup->appendItem(w);
    if (key == "uptime") {
        m_currentRunningTimeUIIndex = index;
    }
    w->setInfoKey(key);
    w->setInfoValue(value);

    connect(w, &InfoItemLine::clicked, [=] (const QString &context) { qDebug() << context; });
}

void InfoUnitWidget::refreshInfoItem(const QString &key, const QString &value)
{
    QList<InfoItemLine *> items = findChildren<InfoItemLine*>();
    for (InfoItemLine *item : items) {
        if (item->getLineKey() == key) {
            item->setInfoValue(value);
        }
    }
}

int InfoUnitWidget::getCurrentRunningTimeUIIndex()
{
    return m_currentRunningTimeUIIndex;
}
