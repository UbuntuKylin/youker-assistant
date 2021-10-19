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

#include "cpufmsetwidget.h"

#include <QPainter>
#include <QPainterPath>
#include <QDebug>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

#include "../../src/commondef.h"
#include "../../src/kajsondef.h"

CpuFMSetWidget::CpuFMSetWidget(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    m_alternateBase = palette().alternateBase().color();
    initUI();
    initConnections();
}

CpuFMSetWidget::~CpuFMSetWidget()
{
    if (m_styleSettings) {
        delete m_styleSettings;
        m_styleSettings = nullptr;
    }
}

void CpuFMSetWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainterPath path;

    QPainter painter(this);
    painter.setOpacity(1);
    painter.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    painter.setClipping(true);
    painter.setPen(Qt::transparent);

    path.addRoundedRect(this->rect(), 6.0, 6.0);
    path.setFillRule(Qt::WindingFill);
    QBrush brush = this->palette().alternateBase();
    brush.setColor(m_alternateBase);
    painter.setBrush(brush);
    painter.setPen(Qt::transparent);

    painter.drawPath(path);
}

void CpuFMSetWidget::initUI()
{
    m_layoutMain = new QVBoxLayout();
    m_layoutMain->setContentsMargins(16,4,28,0);
    m_layoutMain->setSpacing(0);
    m_layoutTitle = new QHBoxLayout();
    m_layoutTitle->setContentsMargins(0,0,0,0);
    m_layoutTitle->setSpacing(0);
    m_layoutSingleChk = new QHBoxLayout();
    m_layoutSingleChk->setContentsMargins(0,0,0,0);
    m_layoutSingleChk->setSpacing(0);
    m_layoutSlider = new QHBoxLayout();
    m_layoutSlider->setContentsMargins(0,0,0,0);
    m_layoutSlider->setSpacing(0);

    m_labelTitle = new KAInfoTitle(tr("CPU Management Strategy"));
    m_labelTitle->setMinimumHeight(36);
    m_layoutTitle->addWidget(m_labelTitle);
    m_layoutTitle->addStretch(1);

    m_bgRadio = new QButtonGroup(this);
    m_bgRadio->setExclusive(true);
    m_radioPerformance = new QRadioButton();
    m_radioPerformance->setText(tr("performance"));
    m_radioPerformance->setObjectName("performance");
    m_radioPerformance->hide();
    m_layoutSingleChk->addWidget(m_radioPerformance);
    m_bgRadio->addButton(m_radioPerformance);

    m_radioPowerSave = new QRadioButton();
    m_radioPowerSave->setText(tr("powersave"));
    m_radioPowerSave->setObjectName("powersave");
    m_radioPowerSave->hide();
    m_layoutSingleChk->addWidget(m_radioPowerSave);
    m_bgRadio->addButton(m_radioPowerSave);

    m_radioUserSpace = new QRadioButton();
    m_radioUserSpace->setText(tr("userspace"));
    m_radioUserSpace->setObjectName("userspace");
    m_radioUserSpace->hide();
    m_layoutSingleChk->addWidget(m_radioUserSpace);
    m_bgRadio->addButton(m_radioUserSpace);

    m_radioBalance = new QRadioButton();
    m_radioBalance->setText(tr("schedutil"));
    m_radioBalance->setObjectName("schedutil");
    m_radioBalance->hide();
    m_layoutSingleChk->addWidget(m_radioBalance);
    m_bgRadio->addButton(m_radioBalance);

    m_radioOndemand = new QRadioButton();
    m_radioOndemand->setText(tr("ondemand"));
    m_radioOndemand->setObjectName("ondemand");
    m_radioOndemand->hide();
    m_layoutSingleChk->addWidget(m_radioOndemand);
    m_bgRadio->addButton(m_radioOndemand);

    m_radioConservative = new QRadioButton();
    m_radioConservative->setText(tr("conservative"));
    m_radioConservative->setObjectName("conservative");
    m_radioConservative->hide();
    m_layoutSingleChk->addWidget(m_radioConservative);
    m_bgRadio->addButton(m_radioConservative);

    m_layoutSingleChk->setSpacing(10);
    m_layoutSingleChk->addStretch(1);
    m_layoutSingleChk->setContentsMargins(12, 0, 0, 0);

    QStringList strList;
    strList << "2.5GHz" << "2.8GHz" << "3.0GHz" << "3.6GHz" << "4.0GHz";
    m_sliderUserSpace = new KASlider(strList);
    m_sliderUserSpace->setRange(0,strList.size()-1);
    m_sliderUserSpace->setTickInterval(1);
    m_sliderUserSpace->setPageStep(1);
    m_sliderUserSpace->hide();
    m_layoutSlider->addSpacing(12);
    m_layoutSlider->addWidget(m_sliderUserSpace);

    m_layoutMain->setSpacing(18);
    m_layoutMain->addLayout(m_layoutTitle);
    m_layoutMain->addLayout(m_layoutSingleChk);
    m_layoutMain->addLayout(m_layoutSlider);
    m_layoutMain->addSpacing(16);
    this->setLayout(m_layoutMain);
    initStyleTheme();
}

void CpuFMSetWidget::initStyleTheme()
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

void CpuFMSetWidget::initConnections()
{
    connect(m_bgRadio, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(onButtonClicked(QAbstractButton*)));
    connect(m_sliderUserSpace, &QSlider::valueChanged, [=](int value){
        qInfo()<<"SetCpuFreq:"<<value;
        if (m_strCurModel != m_radioUserSpace->objectName()) {
            return;
        }
        m_strCurFreq = m_sliderUserSpace->valueList().at(value);
        Q_EMIT modelChanged(m_strCurModel, m_strCurFreq);
    });
}

/**
 * {\"cpu_fm\": {\"cpu_model_list\": [\"performance\", \"powersave\"],
 * \"cpu_freq_list\": [], \"cpu_curmodel\": \"performance\", \"cpu_corefreq\": \"3.6Ghz\"}}
 */
void CpuFMSetWidget::onUpdateInfo(QString strInfoJson)
{
    if (strInfoJson.isEmpty())
        return;
    QJsonParseError jsonParseErr;
    QJsonDocument  rootDoc = QJsonDocument::fromJson(strInfoJson.toUtf8(), &jsonParseErr);//字符串格式化为JSON
    if (jsonParseErr.error != QJsonParseError::NoError) {
        qWarning() << "JSON格式错误";
        return;
    } else {
         QJsonObject rootObj = rootDoc.object();
         if (rootObj.isEmpty()) {
             qWarning() << "JSON串为空";
             return;
         }
         QJsonValue valJson = rootObj.value(CPUFM_ROOT);
         if (valJson.isObject()) {
             QJsonObject objCPUFM = valJson.toObject();
             QJsonValue valCoreFreq = objCPUFM.value(CPUFM_AVERAGE_COREFREQ);
             if (valCoreFreq.isString()) {
                 Q_EMIT updateCpuFreq(valCoreFreq.toString());
             }
             QJsonValue valModel = objCPUFM.value(CPUFM_CURFREQMODEL);
             if (valModel.isString()) {
                 m_strCurModel = valModel.toString();
             }
             QJsonValue valFreq = objCPUFM.value(CPUFM_CURFREQ);
             if (valFreq.isString()) {
                 m_strCurFreq = valFreq.toString();
             }
             QJsonValue valFreqList = objCPUFM.value(CPUFM_FREQS);
             if (valFreqList.isArray()) {
                 QJsonArray arrayJson = valFreqList.toArray();
                 m_validFreqList.clear();
                 for (int n = 0; n < arrayJson.size(); n++) {
                     if (arrayJson.at(n).isString()) {
                         m_validFreqList.append(arrayJson.at(n).toString());
                     }
                 }
             }
             QJsonValue valModelList = objCPUFM.value(CPUFM_MODELS);
             if (valModelList.isArray()) {
                 QJsonArray arrayJson = valModelList.toArray();
                 m_validModelList.clear();
                 for (int n = 0; n < arrayJson.size(); n++) {
                     if (arrayJson.at(n).isString()) {
                         m_validModelList.append(arrayJson.at(n).toString());
                     }
                 }
             }
             updateUIStatus();
         }
    }
}

void CpuFMSetWidget::onButtonClicked(QAbstractButton* button)
{
    QRadioButton* radioBtn = qobject_cast<QRadioButton*>(button);
    if (radioBtn) {
        qInfo()<<"objName:"<<radioBtn->objectName();
        m_strCurModel = radioBtn->objectName();
        if (radioBtn != m_radioUserSpace) {
            Q_EMIT modelChanged(m_strCurModel, "");
            if (!m_sliderUserSpace->isHidden())
                m_sliderUserSpace->hide();
        } else {
            if (m_sliderUserSpace->valueList().contains(m_strCurFreq)) {
                Q_EMIT modelChanged(m_strCurModel, m_strCurFreq);
            } else {
                m_sliderUserSpace->setValue(0);
                m_strCurFreq = m_sliderUserSpace->valueList().at(0);
                Q_EMIT modelChanged(m_strCurModel, m_strCurFreq);
            }
            if (m_sliderUserSpace->isHidden())
                m_sliderUserSpace->show();
        }
    }
}

void CpuFMSetWidget::updateUIStatus()
{
    if (m_validModelList.contains(CPUFM_MODEL_PERFORMANCE)) {
        m_radioPerformance->show();
    }
    if (m_validModelList.contains(CPUFM_MODEL_POWERSAVE)) {
        m_radioPowerSave->show();
    }
    if (m_validModelList.contains(CPUFM_MODEL_USERSPACE)) {
        m_radioUserSpace->show();
    }
    if (m_validModelList.contains(CPUFM_MODEL_SCHEDUTIL)) {
        m_radioBalance->show();
    }
    if (m_validModelList.contains(CPUFM_MODEL_ONDEMAND)) {
        m_radioOndemand->show();
    }
    if (m_validModelList.contains(CPUFM_MODEL_CONSERVATIVE)) {
        m_radioConservative->show();
    }
    if (!m_validFreqList.empty()) {
        m_sliderUserSpace->setValueList(m_validFreqList);
        m_sliderUserSpace->setRange(0,m_validFreqList.size()-1);
        m_sliderUserSpace->setTickInterval(1);
        m_sliderUserSpace->setPageStep(1);
        if (m_validFreqList.contains(m_strCurFreq)) {
            m_sliderUserSpace->setValue(m_validFreqList.indexOf(m_strCurFreq));
        }
    }
    if (m_strCurModel == CPUFM_MODEL_PERFORMANCE) {
        m_radioPerformance->setChecked(true);
        m_radioPowerSave->setChecked(false);
        m_radioUserSpace->setChecked(false);
        m_radioBalance->setChecked(false);
        m_radioOndemand->setChecked(false);
        m_radioConservative->setChecked(false);
        m_sliderUserSpace->hide();
    } else if (m_strCurModel == CPUFM_MODEL_POWERSAVE) {
        m_radioPerformance->setChecked(false);
        m_radioPowerSave->setChecked(true);
        m_radioUserSpace->setChecked(false);
        m_radioBalance->setChecked(false);
        m_radioOndemand->setChecked(false);
        m_radioConservative->setChecked(false);
        m_sliderUserSpace->hide();
    } else if (m_strCurModel == CPUFM_MODEL_USERSPACE) {
        m_radioPerformance->setChecked(false);
        m_radioPowerSave->setChecked(false);
        m_radioUserSpace->setChecked(true);
        m_radioBalance->setChecked(false);
        m_radioOndemand->setChecked(false);
        m_radioConservative->setChecked(false);
        m_sliderUserSpace->show();
    } else if (m_strCurModel == CPUFM_MODEL_SCHEDUTIL) {
        m_radioPerformance->setChecked(false);
        m_radioPowerSave->setChecked(false);
        m_radioUserSpace->setChecked(false);
        m_radioBalance->setChecked(true);
        m_radioOndemand->setChecked(false);
        m_radioConservative->setChecked(false);
        m_sliderUserSpace->hide();
    } else if (m_strCurModel == CPUFM_MODEL_ONDEMAND) {
        m_radioPerformance->setChecked(false);
        m_radioPowerSave->setChecked(false);
        m_radioUserSpace->setChecked(false);
        m_radioBalance->setChecked(false);
        m_radioOndemand->setChecked(true);
        m_radioConservative->setChecked(false);
        m_sliderUserSpace->hide();
    } else if (m_strCurModel == CPUFM_MODEL_CONSERVATIVE) {
        m_radioPerformance->setChecked(false);
        m_radioPowerSave->setChecked(false);
        m_radioUserSpace->setChecked(false);
        m_radioBalance->setChecked(false);
        m_radioOndemand->setChecked(false);
        m_radioConservative->setChecked(true);
        m_sliderUserSpace->hide();
    }
}
