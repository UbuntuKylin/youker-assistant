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

#include "cpufmpage.h"

#include <QDebug>
#include <QIcon>
#include <QDebug>
#include <QTimer>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <kinfolistitem.h>

#include "../../src/commondef.h"
#include "../../src/kajsondef.h"
#include "dataworker.h"

CpuFMPage::CpuFMPage(QWidget *parent)
    : QWidget(parent)
{
    initUI();
    initConnections();
}

CpuFMPage::~CpuFMPage()
{
    if (m_styleSettings) {
        delete m_styleSettings;
        m_styleSettings = nullptr;
    }
}

void CpuFMPage::initUI()
{
    m_layoutMain = new QVBoxLayout();
    m_layoutMain->setContentsMargins(0,24,32,16);
    m_layoutMain->setSpacing(0);
    m_layoutMain->setAlignment(Qt::AlignTop);
    m_layoutFreq = new QHBoxLayout();
    m_layoutFreq->setContentsMargins(0,0,0,0);
    m_layoutFreq->setSpacing(0);
    m_layoutSetting = new QHBoxLayout();
    m_layoutSetting->setContentsMargins(0,0,0,0);
    m_layoutSetting->setSpacing(0);
    m_layoutTips = new QHBoxLayout();
    m_layoutTips->setContentsMargins(0,0,0,0);
    m_layoutTips->setSpacing(0);
    m_layoutFreqRight = new QVBoxLayout();
    m_layoutFreqRight->setContentsMargins(0,0,0,0);
    m_layoutFreqRight->setSpacing(0);

    m_iconFreq = new QLabel();
    QPixmap pixmap;
    pixmap.load(":/imgres/img_res/icon-cpu.svg");
    pixmap.scaled(42,42);
    m_iconFreq->setPixmap(pixmap);
    m_layoutFreq->addWidget(m_iconFreq);

    QHBoxLayout *rightTop = new QHBoxLayout();
    rightTop->setContentsMargins(0,0,0,0);
    rightTop->setSpacing(0);
    QHBoxLayout *rightBottom = new QHBoxLayout();
    rightBottom->setContentsMargins(0,0,0,0);
    rightBottom->setSpacing(0);
    m_labelFreqValue = new QLabel();
    m_labelFreqValue->setText("0.0GHz");
    rightTop->addWidget(m_labelFreqValue);
    rightTop->addStretch(1);
    m_labelFreq = new QLabel();
    m_labelFreq->setText(tr("Current average CPU core frequency"));
    rightBottom->addWidget(m_labelFreq);
    rightBottom->addStretch(1);
    m_layoutFreqRight->addLayout(rightTop);
    m_layoutFreqRight->addLayout(rightBottom);

    m_cpuFMSetWidget = new CpuFMSetWidget();
    m_layoutSetting->addWidget(m_cpuFMSetWidget);

    m_labelTips = new QLabel();
    m_labelTips->setWordWrap(true);
    m_labelTips->setText(tr("CPU FM Note: The CPU FM function has some risks, please use it carefully! After FM is completed, restarting will restore the default configuration!"));
    m_layoutTips->addWidget(m_labelTips);

    m_layoutFreq->addSpacing(12);
    m_layoutFreq->addLayout(m_layoutFreqRight);
    m_layoutMain->addLayout(m_layoutFreq);
    m_layoutMain->addSpacing(24);
    m_layoutMain->addLayout(m_layoutSetting);
    m_layoutMain->addSpacing(12);
    m_layoutMain->addLayout(m_layoutTips);
    this->setLayout(m_layoutMain);
    initStyleTheme();
    if (!DataWorker::getInstance()->getCpuFMEnable()) {
        m_iconFreq->hide();
        m_labelFreqValue->hide();
        m_labelFreq->hide();
        m_cpuFMSetWidget->hide();
        m_labelTips->hide();
        KInfoListItem *listItem = new KInfoListItem("", "", tr("Device not exitst or Get Device is Empty"), 0);
        listItem->setMinimumHeight(40);
        listItem->setFixedWidth(666);
        m_layoutFreq->addWidget(listItem);
    }
}

void CpuFMPage::initStyleTheme()
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
                    float fFontSize = styleFontSizeValue.toFloat();
                    QFont font = m_labelFreqValue->font();
                    font.setPointSize(fFontSize+2);
                    m_labelFreqValue->setFont(font);
                }
            }
        });
        auto styleNameValue = m_styleSettings->get("styleName");
        if (styleNameValue.isValid()) {
        }
        auto styleFontSizeValue = m_styleSettings->get("systemFontSize");
        if (styleFontSizeValue.isValid()) {
            float fFontSize = styleFontSizeValue.toFloat();
            QFont font = m_labelFreqValue->font();
            font.setPointSize(fFontSize+2);
            m_labelFreqValue->setFont(font);
        }
    }
}

void CpuFMPage::initConnections()
{
    connect(m_cpuFMSetWidget, &CpuFMSetWidget::modelChanged, this, &CpuFMPage::onCpuFMChange);
    // 连接dbus信号
    DataWorker::getInstance()->connectCpuFMInfoSignal();
    connect(DataWorker::getInstance(), SIGNAL(updateCpuFMInfo(unsigned, QString)), this, SLOT(onUpdateInfo(unsigned, QString)));
    connect(m_cpuFMSetWidget, &CpuFMSetWidget::updateCpuFreq, this, &CpuFMPage::onUpdateCoreFreq);
}

void CpuFMPage::onCpuFMChange(QString strModel, QString strCurFreq)
{
    qInfo()<<"CurCpuFM:"<<strModel<<","<<strCurFreq;
    QJsonObject objRoot;
    objRoot.insert(CPUFM_CURFREQMODEL, strModel);
    objRoot.insert(CPUFM_CURFREQ, strCurFreq);
    QJsonDocument rootDoc;
    rootDoc.setObject(objRoot);
    QString strAdjust = QString(rootDoc.toJson(QJsonDocument::Compact));
    DataWorker::getInstance()->setCpuFMInfo(strAdjust);
}

void CpuFMPage::onUpdateCoreFreq(QString strFreq)
{
    m_labelFreqValue->setText(strFreq);
}

/**
 * {\"cpu_fm\": {\"cpu_model_list\": [\"performance\", \"powersave\"],
 * \"cpu_freq_list\": [], \"cpu_curmodel\": \"performance\", \"cpu_corefreq\": \"3.6Ghz\"}}
 */
void CpuFMPage::onUpdateInfo(unsigned uStatus, QString strInfoJson)
{
    //qDebug()<<"CPU FM info:"<<uStatus<<","<<strInfoJson;
    if (m_cpuFMSetWidget)
        m_cpuFMSetWidget->onUpdateInfo(strInfoJson);
}

void CpuFMPage::refreshInfo()
{
    DataWorker::getInstance()->getCpuFMInfo();
}
