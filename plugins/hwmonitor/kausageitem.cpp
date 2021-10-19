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

#include "kausageitem.h"

#include <QDebug>

#include "../../src/commondef.h"

KAUsageItem::KAUsageItem(QString strTitle, QWidget *parent)
    : QWidget(parent)
    , m_strTitle(strTitle)
{
    initUI();
    setFixedWidth(320);
}

KAUsageItem::~KAUsageItem()
{
    if (m_styleSettings) {
        delete m_styleSettings;
        m_styleSettings = nullptr;
    }
}

void KAUsageItem::initUI()
{
    m_mainLayout = new QVBoxLayout();
    m_mainLayout->setContentsMargins(0,0,0,0);
    m_mainLayout->setSpacing(0);
    m_topLayout = new QHBoxLayout();
    m_topLayout->setContentsMargins(0,0,0,0);
    m_topLayout->setSpacing(0);
    m_midLayout = new QHBoxLayout();
    m_midLayout->setContentsMargins(0,0,0,0);
    m_midLayout->setSpacing(0);
    m_buttomLayout = new QHBoxLayout();
    m_buttomLayout->setContentsMargins(0,0,0,0);
    m_buttomLayout->setSpacing(0);

    m_progressBar = new KAProgressBar();
    m_progressBar->setMaxValue(100);
    m_progressBar->setThresholdValue(80,90);
    m_labelTitle = new QLabel();
    m_labelTitle->setText(QString("%1：%2\%").arg(m_strTitle).arg(getCurValue()*100/getMaxValue()));
    m_labelUsed = new QLabel();
    m_labelUsed->setText(tr("Used"));
    m_labelLeft = new QLabel();
    m_labelLeft->setText(tr("Left"));

    m_topLayout->setAlignment(Qt::AlignLeft);
    m_topLayout->addWidget(m_labelTitle);
    m_midLayout->setAlignment(Qt::AlignLeft);
    m_midLayout->addWidget(m_progressBar);
    m_buttomLayout->addWidget(m_labelUsed, 0, Qt::AlignLeft);
    m_buttomLayout->addWidget(m_labelLeft, 0, Qt::AlignRight);

    m_mainLayout->setAlignment(Qt::AlignTop);
    m_mainLayout->addLayout(m_topLayout);
    m_mainLayout->addSpacing(16);
    m_mainLayout->addLayout(m_midLayout);
    m_mainLayout->addSpacing(8);
    m_mainLayout->addLayout(m_buttomLayout);
    this->setLayout(m_mainLayout);
    initStyleTheme();
}

void KAUsageItem::initStyleTheme()
{
    const QByteArray idd(THEME_QT_SCHEMA);
    if(QGSettings::isSchemaInstalled(idd)) {
        m_styleSettings = new QGSettings(idd);
    }
    if (m_styleSettings) {
        connect(m_styleSettings, &QGSettings::changed, this, [=](const QString &key) {
            if (key == "systemFontSize" || key == "systemFont") {
                qDebug()<<"style font changed";
                auto styleFontSizeValue = m_styleSettings->get("systemFontSize");
                if (styleFontSizeValue.isValid()) {
                    float fFontSize = styleFontSizeValue.toFloat();
                    QFont font = m_labelTitle->font();
                    font.setPointSize(fFontSize+2);
                    m_labelTitle->setFont(font);
                    font = m_labelUsed->font();
                    font.setPointSize(fFontSize-2);
                    m_labelUsed->setFont(font);
                    m_labelLeft->setFont(font);
                }
            }
        });
        auto styleFontSizeValue = m_styleSettings->get("systemFontSize");
        if (styleFontSizeValue.isValid()) {
            float fFontSize = styleFontSizeValue.toFloat();
            QFont font = m_labelTitle->font();
            font.setPointSize(fFontSize+2);
            m_labelTitle->setFont(font);
            font = m_labelUsed->font();
            font.setPointSize(fFontSize-2);
            m_labelUsed->setFont(font);
            m_labelLeft->setFont(font);
        }
    }
}

void KAUsageItem::setTitle(QString strTitle)
{
    m_strTitle = strTitle;
    m_labelTitle->setText(QString("%1：%2\%").arg(m_strTitle).arg(getCurValue()*100/getMaxValue()));
}

void KAUsageItem::setMaxValue(qreal rMaxValue)
{
    m_progressBar->setMaxValue(rMaxValue);
    m_labelTitle->setText(QString("%1：%2\%").arg(m_strTitle).arg(getCurValue()*100/getMaxValue()));
}

void KAUsageItem::setThresholdValue(qreal rHigh, qreal rVHigh)
{
    m_progressBar->setThresholdValue(rHigh, rVHigh);
}

qreal KAUsageItem::getMaxValue()
{
    return m_progressBar->getMaxValue();
}

qreal KAUsageItem::getCurValue()
{
    return m_progressBar->getCurValue();
}

void KAUsageItem::onUpdateValue(qreal rCurValue)
{
    m_progressBar->setCurValue(rCurValue);
    m_labelTitle->setText(QString("%1：%2\%").arg(m_strTitle).arg(getCurValue()*100/getMaxValue()));
}
