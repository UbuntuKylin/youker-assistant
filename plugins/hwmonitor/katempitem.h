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

#ifndef KATEMPITEM_H
#define KATEMPITEM_H

#include <QWidget>
#include <QList>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QColor>
#include <qgsettings.h>
#include <QtCharts>
QT_CHARTS_USE_NAMESPACE

#define TEMP_CHARTSDATA_MAX     30

class KATempItem : public QWidget
{
    Q_OBJECT
public:
    typedef enum TEMP_STATUS_e {
        STATUS_NORMAL,
        STATUS_HIGH,
        STATUS_VHIGH
    }TEMP_STATUS;
    explicit KATempItem(QString strTitle, QWidget *parent = nullptr);
    virtual ~KATempItem();

    void initUI();
    void setTitle(QString strTitle);
    qreal getCurTemperature();
    void setThresholdValue(qreal rHigh, qreal rVHigh);
    TEMP_STATUS getCurStatus() {
        return m_curStatus;
    }

public slots:
    void onUpdateTemperature(qreal fTemp);

protected:
    void paintEvent(QPaintEvent *event);

private:
    void initStyleTheme();

private:
    QChart *m_chart = nullptr;
    QChartView *m_chartView = nullptr;
    QLineSeries *m_upLineSeriesTemp = nullptr;
    QLineSeries *m_lowLineSeriesTemp = nullptr;
    QAreaSeries *m_areaSeriesTemp = nullptr;
    QValueAxis *m_valueAxisX = nullptr;
    QValueAxis *m_valueAxisY = nullptr;
    QSplineSeries *m_valueLine = nullptr;

    QColor m_colorBg;
    QColor m_colorBgDark;
    QColor m_colorBgCur;
    QColor m_colorNormal;
    QColor m_colorHigh;
    QColor m_colorVHigh;

    qreal m_tempThresholdHigh;
    qreal m_tempThresholdVHigh;
    qreal m_tempMax;

    QList<qreal> m_historyTemp;
    QString m_strTitle;
    QLabel *m_labelTitle = nullptr;
    QLabel *m_labelTemp = nullptr;

    QVBoxLayout *m_mainLayout = nullptr;
    QHBoxLayout *m_topLayout = nullptr;
    QHBoxLayout *m_chartLayout = nullptr;

    QGSettings *m_styleSettings = nullptr;
    TEMP_STATUS m_curStatus;
};

#endif // KATEMPITEM_H
