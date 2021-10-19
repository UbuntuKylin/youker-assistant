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

#include "katempitem.h"

#include <QPainter>
#include <QPainterPath>
#include <QLinearGradient>
#include <QTimer>
#include <ctime>

#include "../../src/commondef.h"

KATempItem::KATempItem(QString strTitle, QWidget *parent)
    : QWidget(parent)
    , m_strTitle(strTitle)
{
    m_curStatus = STATUS_NORMAL;
    m_tempMax = 100;
    m_tempThresholdHigh = 80;
    m_tempThresholdVHigh = 90;
    this->setFixedHeight(90);
    setAttribute(Qt::WA_TranslucentBackground);
    m_colorBg = QColor("#F4F5F5");
    m_colorBgDark = QColor("#333333");
    m_colorNormal = QColor("#3CDF57");
    m_colorHigh = QColor("#F68C27");
    m_colorVHigh = QColor("#F3222D");
    initUI();
}

KATempItem::~KATempItem()
{
    if (m_styleSettings) {
        delete m_styleSettings;
        m_styleSettings = nullptr;
    }
}

void KATempItem::setTitle(QString strTitle)
{
    m_strTitle = strTitle;
    if (m_labelTitle) {
        m_labelTitle->setText(m_strTitle);
    }
}

void KATempItem::setThresholdValue(qreal rHigh, qreal rVHigh)
{
    rHigh = rHigh > rVHigh ? rVHigh : rHigh;
    if (rHigh <= 0) {
        return;
    }
    m_tempThresholdHigh = rHigh;
    m_tempThresholdVHigh = rVHigh;
    if (getCurTemperature() >= m_tempThresholdVHigh) {
        m_curStatus = STATUS_VHIGH;
    } else if (getCurTemperature() >= m_tempThresholdHigh) {
        m_curStatus = STATUS_HIGH;
    } else {
        m_curStatus = STATUS_NORMAL;
    }
}

void KATempItem::initUI()
{
    m_mainLayout = new QVBoxLayout();
    m_mainLayout->setContentsMargins(12,12,12,10);
    m_mainLayout->setSpacing(0);
    m_topLayout = new QHBoxLayout();
    m_topLayout->setContentsMargins(0,0,0,0);
    m_topLayout->setSpacing(0);
    m_chartLayout = new QHBoxLayout();
    m_chartLayout->setContentsMargins(0,0,0,0);
    m_chartLayout->setMargin(0);
    m_chartLayout->setSpacing(0);

    m_labelTitle = new QLabel();
    m_labelTitle->setText(m_strTitle);
    m_topLayout->addWidget(m_labelTitle, 0, Qt::AlignLeft|Qt::AlignTop);
    m_topLayout->addStretch();
    m_labelTemp = new QLabel();
    m_labelTemp->setText(QString("%1℃").arg(getCurTemperature()));
    m_topLayout->addWidget(m_labelTemp, 0, Qt::AlignRight|Qt::AlignTop);

    // init chart view
    m_chart = new QChart();
    m_chart->legend()->hide();
    m_chart->setMargins(QMargins(-8,-8,-8,-8));
    m_chartView = new QChartView(this);
    m_chartView->setChart(m_chart);
    m_chartView->setRenderHint(QPainter::Antialiasing);
    m_chartView->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    m_chartView->setContentsMargins(0,0,0,0);
    m_chartLayout->addWidget(m_chartView);
    m_upLineSeriesTemp = new QLineSeries(this);
    m_lowLineSeriesTemp = new QLineSeries(this);
    m_areaSeriesTemp = new QAreaSeries(this);
    m_areaSeriesTemp->setPen(Qt::NoPen);
    QLinearGradient linearGrad(QPointF(0, 0), QPointF(0, 100));
    QColor desColor = m_colorNormal;
    desColor.setAlpha(0);
    linearGrad.setColorAt(0, m_colorNormal);
    linearGrad.setColorAt(1, desColor);
    m_areaSeriesTemp->setBrush(QBrush(linearGrad));
    m_areaSeriesTemp->setUpperSeries(m_upLineSeriesTemp);
    m_areaSeriesTemp->setLowerSeries(m_upLineSeriesTemp);
    m_chart->addSeries(m_areaSeriesTemp);
    m_valueAxisX = new QValueAxis(this);
    m_valueAxisY = new QValueAxis(this);
    m_valueAxisX->setRange(0, 30.0);
    m_valueAxisX->setVisible(false);
   // m_valueAxisX->setReverse();
    m_valueAxisY->setRange(0, 100.0);
    m_valueAxisY->setVisible(false);

    m_chart->addAxis(m_valueAxisX, Qt::AlignBottom);
    m_areaSeriesTemp->attachAxis(m_valueAxisX);
    m_chart->addAxis(m_valueAxisY, Qt::AlignLeft);
    m_areaSeriesTemp->attachAxis(m_valueAxisY);

    m_chart->setBackgroundVisible(false);
    m_chartView->setStyleSheet("background: transparent");

    m_mainLayout->addLayout(m_topLayout);
    m_mainLayout->addSpacing(8);
    m_mainLayout->addLayout(m_chartLayout);
    this->setLayout(m_mainLayout);
    initStyleTheme();
#if 0
    QTimer *testTimer = new QTimer(this);
    connect(testTimer, &QTimer::timeout, this, [&,this](){
        qsrand(time(NULL));
        this->onUpdateTemperature(qrand()%100);
    });
    testTimer->start(500);
#endif
}

void KATempItem::initStyleTheme()
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
                        m_colorBgCur = m_colorBgDark;
                    } else {
                        m_colorBgCur = m_colorBg;
                    }
                    repaint();
                }
            } else if (key == "systemFontSize" || key == "systemFont") {
                auto styleFontSizeValue = m_styleSettings->get("systemFontSize");
                if (styleFontSizeValue.isValid()) {
                }
            }
        });
        auto styleNameValue = m_styleSettings->get("styleName");
        if (styleNameValue.isValid()) {
            auto styleName = styleNameValue.toString();
            if (styleName == "ukui-black" || styleName == "ukui-dark") {
                m_colorBgCur = m_colorBgDark;
            } else {
                m_colorBgCur = m_colorBg;
            }
        }
        auto styleFontSizeValue = m_styleSettings->get("systemFontSize");
        if (styleFontSizeValue.isValid()) {
        }
    }
}

void KATempItem::onUpdateTemperature(qreal fTemp)
{
    if (fTemp > m_tempMax) {
        fTemp = m_tempMax;
    }
    if (fTemp >= m_tempThresholdVHigh) {
        m_curStatus = STATUS_VHIGH;
    } else if (fTemp >= m_tempThresholdHigh) {
        m_curStatus = STATUS_HIGH;
    } else {
        m_curStatus = STATUS_NORMAL;
    }
    m_historyTemp.append(fTemp);
    while (m_historyTemp.size() > TEMP_CHARTSDATA_MAX)    {
        m_historyTemp.pop_front();
    }
    QList<QPointF> listUp;
    QList<QPointF> listLow;
    for (int n = 0; n < m_historyTemp.size(); n++) {
        QPointF pointUp;
        QPointF pointLow;
        pointUp.setX(n);
        pointUp.setY(m_historyTemp[n]*100.0/m_tempMax);
        listUp.append(pointUp);
        pointLow.setX(n);
        pointLow.setY(0);
        listLow.append(pointLow);
    }

    m_upLineSeriesTemp->clear();
    m_upLineSeriesTemp->replace(listUp);

    m_lowLineSeriesTemp->clear();
    m_lowLineSeriesTemp->replace(listLow);

    QPalette pe;// = m_labelTemp->palette();
    if (fTemp >= m_tempThresholdVHigh) {
        QLinearGradient linearGrad(QPointF(0, 0), QPointF(0, 100));
        QColor desColor = m_colorVHigh;
        desColor.setAlpha(128);
        linearGrad.setColorAt(0, desColor);
        desColor.setAlpha(0);
        linearGrad.setColorAt(1, desColor);
        m_areaSeriesTemp->setBrush(QBrush(linearGrad));
        pe.setColor(QPalette::Foreground, m_colorVHigh);//设置颜色
    } else if (fTemp >= m_tempThresholdHigh) {
        QLinearGradient linearGrad(QPointF(0, 0), QPointF(0, 100));
        QColor desColor = m_colorHigh;
        desColor.setAlpha(128);
        linearGrad.setColorAt(0, desColor);
        desColor.setAlpha(0);
        linearGrad.setColorAt(1, desColor);
        m_areaSeriesTemp->setBrush(QBrush(linearGrad));
        pe.setColor(QPalette::Foreground, m_colorHigh);//设置颜色
    } else {
        QLinearGradient linearGrad(QPointF(0, 0), QPointF(0, 100));
        QColor desColor = m_colorNormal;
        desColor.setAlpha(128);
        linearGrad.setColorAt(0, desColor);
        desColor.setAlpha(0);
        linearGrad.setColorAt(1, desColor);
        m_areaSeriesTemp->setBrush(QBrush(linearGrad));
        pe.setColor(QPalette::Foreground, Qt::red);//设置颜色
    }

    m_areaSeriesTemp->setUpperSeries(m_upLineSeriesTemp);
    m_areaSeriesTemp->setLowerSeries(m_lowLineSeriesTemp);

    m_labelTemp->setPalette(pe);
    m_labelTemp->setText(QString("%1℃").arg(getCurTemperature()));
}

qreal KATempItem::getCurTemperature()
{
    if (m_historyTemp.isEmpty()) {
        return 0;
    }
    return m_historyTemp.at(m_historyTemp.size()-1);
}

void KATempItem::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //background of rect
    painter.save();
    painter.setOpacity(1);
    QPainterPath framePath;
    QStyleOption opt;
    opt.init(this);
    framePath.addRoundedRect(rect(), 6, 6);
    painter.fillPath(framePath, this->m_colorBgCur);
    painter.restore();

    QWidget::paintEvent(event);
}
