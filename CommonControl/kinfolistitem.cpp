/*
 * Copyright (C) 2021 KylinSoft Co., Ltd.
 *
 * Authors:
 *  Yang Min yangmin@kylinos.cn
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "kinfolistitem.h"

#include <QFrame>
#include <QLabel>
#include <QIcon>
#include <QPaintEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainterPath>
#include <QPainter>
#include <QStyleOption>
#include <QPixmap>
#include <QIcon>
#include <QFileInfo>
#include <QAction>
#include <QClipboard>
#include <QApplication>
#include <QMouseEvent>
#include <QDebug>

#include "../../src/commondef.h"

KInfoListItem::KInfoListItem(QString strTitle, QString strIcon, QString strDetail, bool isOdd, QWidget *parent)
    : QFrame(parent)
{
    this->setAttribute(Qt::WA_TranslucentBackground);
    m_strTitle = strTitle;
    m_strIcon = strIcon;
    m_strDetail = strDetail;
    m_isOdd = isOdd;
    m_alternateBase = palette().alternateBase().color();
    initUI();
}

KInfoListItem::~KInfoListItem()
{
    if (m_styleSettings) {
        delete m_styleSettings;
        m_styleSettings = nullptr;
    }
}

void KInfoListItem::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainterPath path;

    QPainter painter(this);
    painter.setOpacity(1);
    painter.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    painter.setClipping(true);
    painter.setPen(Qt::transparent);

    path.addRoundedRect(this->rect(), 6, 6);
    path.setFillRule(Qt::WindingFill);
    if(m_isOdd) {
        painter.setBrush(this->palette().base());
    } else {
        QBrush brush = this->palette().alternateBase();
        brush.setColor(m_alternateBase);
        painter.setBrush(brush);
    }
    painter.drawPath(path);
}

void KInfoListItem::initUI()
{
    m_mainLayout = new QHBoxLayout();
    m_mainLayout->setContentsMargins(0,0,0,0);
    m_mainLayout->setSpacing(0);

    m_mainLayout->addSpacing(22);

    if (!m_strIcon.isEmpty()) {
        m_labelIcon = new QLabel();
        QIcon icon;
        if (m_strIcon.contains("/")) {
            QFileInfo fileInfo(m_strIcon);
            if (fileInfo.exists()) {
                icon = QIcon(m_strIcon);
            }
        } else {
            icon = QIcon::fromTheme(m_strIcon);
        }
        m_labelIcon->setPixmap(icon.pixmap(16,16));
        m_mainLayout->addWidget(m_labelIcon, 0, Qt::AlignHCenter);
        m_mainLayout->addSpacing(12);
    }
    m_labelTitle = new KALabel();
    m_labelTitle->setText(m_strTitle);
    m_labelTitle->setFixedWidth(150);
    m_mainLayout->addWidget(m_labelTitle, 0, Qt::AlignLeft);
    m_labelDetail = new KALabel();
    m_labelDetail->setText(m_strDetail);
    m_labelDetail->setFixedWidth(460);
    //m_labelDetail->setWordWrap(true);
    m_mainLayout->addWidget(m_labelDetail, 0, Qt::AlignLeft);
    m_mainLayout->addStretch();

    m_rkeyMenu = new QMenu(this);
    QAction *copyAction = new QAction(QIcon::fromTheme("edit-copy-symbolic"), tr("Copy"), this);
    connect(copyAction, &QAction::triggered, this, &KInfoListItem::onCopyContent);
    m_rkeyMenu->addAction(copyAction);

    this->setLayout(m_mainLayout);
    initStyleTheme();
}

void KInfoListItem::initStyleTheme()
{
    const QByteArray idd(THEME_QT_SCHEMA);
    if(QGSettings::isSchemaInstalled(idd)) {
        m_styleSettings = new QGSettings(idd);
    }
    if (m_styleSettings) {
        connect(m_styleSettings, &QGSettings::changed, this, [=](const QString &key) {
            if (key == "styleName") {
                auto styleNameValue = m_styleSettings->get("styleName");
                if (styleNameValue.isValid()) {
                    auto styleName = styleNameValue.toString();
                    if (styleName == "ukui-black" || styleName == "ukui-dark") {
                        m_alternateBase = QColor(COLOR_ALTERNATEBASE_DARK);
                    } else {
                        m_alternateBase = QColor(COLOR_ALTERNATEBASE_LIGHT);
                    }
                    repaint();
                }
            }
        });
        auto styleNameValue = m_styleSettings->get("styleName");
        if (styleNameValue.isValid()) {
            auto styleName = styleNameValue.toString();
            if (styleName == "ukui-black" || styleName == "ukui-dark") {
                m_alternateBase = QColor(COLOR_ALTERNATEBASE_DARK);
            } else {
                m_alternateBase = QColor(COLOR_ALTERNATEBASE_LIGHT);
            }
        }
    }
}

void KInfoListItem::updateDetailInfo(QString strDetail)
{
    if (m_labelDetail)
        m_labelDetail->setText(strDetail);
}

void KInfoListItem::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        m_rkeyMenu->popup(event->globalPos());
    }
    QFrame::mousePressEvent(event);
}

void KInfoListItem::onCopyContent()
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(m_strTitle+":"+m_strDetail);
}
