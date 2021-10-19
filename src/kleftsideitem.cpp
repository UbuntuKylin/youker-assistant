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

#include "kleftsideitem.h"

#include <QIcon>
#include <QPixmap>
#include <QVariant>

#include "commondef.h"
#include "utils.h"

KLeftSideItem::KLeftSideItem(QWidget *parent)
    : QPushButton(parent)
{
    m_strIcon = "";
    m_strText = "";
    this->setFlat(true);
    initUI();
}

KLeftSideItem::KLeftSideItem(QString strText, QString strIcon, QWidget *parent)
    : QPushButton(parent)
{
    m_strIcon = strIcon;
    m_strText = strText;
    this->setFlat(true);
    initUI();
}

KLeftSideItem::~KLeftSideItem()
{
    if (m_styleSettings) {
        delete m_styleSettings;
        m_styleSettings = nullptr;
    }
}

void KLeftSideItem::initUI()
{
    m_layoutMain = new QHBoxLayout();
    m_layoutMain->setContentsMargins(16,6,16,6);
    m_layoutMain->setSpacing(8);

    m_labelIcon = new QLabel();
    m_labelIcon->setProperty("useIconHighlightEffect", 0x2);
    setIcon(m_strIcon);
    m_layoutMain->addWidget(m_labelIcon);

    m_labelText = new QLabel();
    setText(m_strText);
    m_layoutMain->addWidget(m_labelText);

    m_layoutMain->addStretch();
    this->setLayout(m_layoutMain);
    initStyleTheme();
}

void KLeftSideItem::initStyleTheme()
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
                }
            } else if (key == "systemFontSize" || key == "systemFont") {
                auto styleFontSizeValue = m_styleSettings->get("systemFontSize");
                if (styleFontSizeValue.isValid()) {
                    this->setText(m_strText);
                }
            }
        });
        auto styleNameValue = m_styleSettings->get("styleName");
        if (styleNameValue.isValid()) {
        }
        auto styleFontSizeValue = m_styleSettings->get("systemFontSize");
        if (styleFontSizeValue.isValid()) {
            this->setText(m_strText);
        }
    }
}

void KLeftSideItem::setText(const QString &strText)
{
    m_strText = strText;
    if (!m_strText.isEmpty()) {
        QString ShowValue = getElidedText(m_labelText->font(), m_strText, width()-60); // 16+16+8+16 + 4
        m_labelText->setText(ShowValue);
        if (ShowValue != m_strText) {
            setToolTip(m_strText);
        } else {
            setToolTip("");
        }
        m_labelText->show();
    } else {
        m_labelText->hide();
    }
}

void KLeftSideItem::setIcon(QString &strIcon)
{
    m_strIcon = strIcon;
    QIcon icon;
    if (strIcon.contains("/")) {
        icon = QIcon(strIcon);
    } else {
        icon = QIcon::fromTheme(strIcon);
    }
    if (!icon.isNull()) {
        m_labelIcon->setPixmap(icon.pixmap(16,16));
        m_labelIcon->show();
    } else {
        m_labelIcon->hide();
    }
}
