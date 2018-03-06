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

#include "networkflow.h"
#include "smoothcurvegenerator.h"
#include "util.h"

#include <QDebug>
#include <QPainter>
#include <QApplication>
#include <QButtonGroup>
#include <QSvgRenderer>
#include <QGraphicsScene>
#include <QGraphicsSvgItem>

inline QString formatNetworkBrandWidth(guint64 size, bool isTotal)
{
    enum {
        K_INDEX,
        M_INDEX,
        G_INDEX,
        T_INDEX
    };

    QList<guint64> factorList;
    factorList.append(G_GUINT64_CONSTANT(1) << 10);//KiB
    factorList.append(G_GUINT64_CONSTANT(1) << 20);//MiB
    factorList.append(G_GUINT64_CONSTANT(1) << 30);//GiB
    factorList.append(G_GUINT64_CONSTANT(1) << 40);//TiB

    if (size < factorList.at(K_INDEX)) {
        if ((guint) size > 1) {
            if (isTotal)
                return QString("%1 %2").arg((guint) size).arg(QObject::tr("byte"));
            else
                return QString("%1 %2").arg((guint) size).arg(QObject::tr("byte/s"));
        }
        else {
            if (isTotal)
                return QString("%1 %2").arg((guint) size).arg(QObject::tr("bytes"));
            else
                return QString("%1 %2").arg((guint) size).arg(QObject::tr("bytes/s"));
        }
    } else {
        guint64 factor;
        QString format;
        if (size < factorList.at(M_INDEX)) {
            factor = factorList.at(K_INDEX);
            if (isTotal)
                format = QObject::tr("KiB");
            else
                format = QObject::tr("KiB/s");
        }else if (size < factorList.at(G_INDEX)) {
            factor = factorList.at(M_INDEX);
            if (isTotal)
                format = QObject::tr("MiB");
            else
                format = QObject::tr("MiB/s");
        } else if (size < factorList.at(T_INDEX)) {
            factor = factorList.at(G_INDEX);
            if (isTotal)
                format = QObject::tr("GiB");
            else
                format = QObject::tr("GiB/s");
        } else {
            factor = factorList.at(T_INDEX);
            if (isTotal)
                format = QObject::tr("TiB");
            else
                format = QObject::tr("TiB/s");
        }
        std::string formatted_result(make_string(g_strdup_printf("%.1f", size / (double)factor)));
        return QString::fromStdString(formatted_result) + format;
    }
}

inline QString formatNetwork(guint64 rate)
{
    return formatNetworkBrandWidth(rate, true);
}

inline QString formatNetworkRate(guint64 rate)
{
    return formatNetworkBrandWidth(rate, false);
}

NetworkFlow::NetworkFlow(QWidget *parent) : QWidget(parent)
  ,m_outsideBorderColor(QColor("#009944"))
  ,m_bgColor(QColor("#ffffff"))
  ,m_downloadColor(QColor("#009944"))
  ,m_uploadColor(QColor("#e60012"))
{
    setFixedSize(403, 300);

    receiveText = tr("Receive");
    sendText = tr("Send");

    m_netMaxHeight = 60;
    m_pointSpace = 10;

    m_pointsCount = int((this->width() -2) / m_pointSpace);
    m_downloadSpeedList = new QList<long>();
    for (int i = 0; i < m_pointsCount; i++) {
        m_downloadSpeedList->append(0);
    }

    m_uploadSpeedList = new QList<long>();
    for (int i = 0; i < m_pointsCount; i++) {
        m_uploadSpeedList->append(0);
    }

    m_gridY = new QList<int>();

    /*connect(ui->generateCurveButton, SIGNAL(clicked(bool)), this, SLOT(generateCurves()));
    connect(ui->showKnotsCheckBox, SIGNAL(clicked(bool)), this, SLOT(update()));
    connect(ui->showSmoothCurveCheckBox, SIGNAL(clicked(bool)), this, SLOT(update()));
    connect(ui->smoothCurveGeneratorComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(update()));
    ui->generateCurveButton->click();*/
}

NetworkFlow::~NetworkFlow()
{
    delete m_downloadSpeedList;
    delete m_uploadSpeedList;
    delete m_gridY;
}

//http://www.qtdebug.com/qtbook-paint-smooth-curve/
void NetworkFlow::onUpdateNetworkStatus(long recvTotalBytes, long sentTotalBytes, long recvRateBytes, long sentRateBytes)
{
    m_recvTotalBytes = recvTotalBytes;
    m_sentTotalBytes = sentTotalBytes;
    m_recvRateBytes = recvRateBytes;
    m_sentRateBytes = sentRateBytes;

    //download
    QList<QPointF> downloadPoints;
    m_downloadSpeedList->append(m_recvRateBytes);
    if (m_downloadSpeedList->size() > m_pointsCount) {
        m_downloadSpeedList->pop_front();
    }
    //计算出下载速度中最大的值
    long downloadMaxHeight = 0;
    for (int i = 0; i < m_downloadSpeedList->size(); i++) {
        if (m_downloadSpeedList->at(i) > downloadMaxHeight) {
            downloadMaxHeight = m_downloadSpeedList->at(i);
        }
    }
    for (int i = 0; i < m_downloadSpeedList->size(); i++) {
        if (downloadMaxHeight < m_netMaxHeight) {
            downloadPoints.append(QPointF(i * m_pointSpace, m_downloadSpeedList->at(i)));
        }
        else {
            downloadPoints.append(QPointF(i * m_pointSpace, m_downloadSpeedList->at(i) * m_netMaxHeight / downloadMaxHeight));
        }
    }
    m_downloadPath = SmoothCurveGenerator::generateSmoothCurve(downloadPoints);


    /*// 根据曲线上的点创建平滑曲线
    smoothCurve1 = SmoothCurveGenerator1::generateSmoothCurve(downloadPoints);
    smoothCurve2 = SmoothCurveGenerator2::generateSmoothCurve(downloadPoints);
    // 连接点创建非平滑曲线曲线
    nonSmoothCurve = QPainterPath();
    nonSmoothCurve.moveTo(downloadPoints[0]);
    for (int i = 1; i < downloadPoints.size(); ++i) {
        nonSmoothCurve.lineTo(downloadPoints[i]);
    }*/


    //upload
    QList<QPointF> uploadPoints;
    m_uploadSpeedList->append(m_sentRateBytes);
    if (m_uploadSpeedList->size() > m_pointsCount) {
        m_uploadSpeedList->pop_front();
    }
    //计算出上传速度中最大的值
    long uploadMaxHeight = 0;
    for (int i = 0; i < m_uploadSpeedList->size(); i++) {
        if (m_uploadSpeedList->at(i) > uploadMaxHeight) {
            uploadMaxHeight = m_uploadSpeedList->at(i);
        }
    }

    for (int i = 0; i < m_uploadSpeedList->size(); i++) {
        if (uploadMaxHeight < m_netMaxHeight) {
            uploadPoints.append(QPointF(i * m_pointSpace, m_uploadSpeedList->at(i)));
        }
        else {
            uploadPoints.append(QPointF(i * m_pointSpace, m_uploadSpeedList->at(i) * m_netMaxHeight / uploadMaxHeight));
        }
    }
    m_uploadPath = SmoothCurveGenerator::generateSmoothCurve(uploadPoints);

    repaint();
}


void NetworkFlow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);//反走样,绘制出来的线条会出现锯齿

    int penSize = 1;
    int gridX = rect().x() + penSize;
    int gridY = rect().y() + 10;
    int gridWidth = rect().width() - penSize * 2;
    int gridHeight = 90;

    //border of rect
    QPainterPath borderPath;
    borderPath.addRoundedRect(QRect(rect().x(), rect().y() + 9, gridWidth + penSize * 2, gridHeight + penSize * 2), 0, 0);
    QPen pen(this->m_outsideBorderColor, 1);
    painter.setPen(pen);
    painter.drawPath(borderPath);

    //background of rect
    painter.setOpacity(1);
    QPainterPath framePath;
    framePath.addRect(QRectF(gridX, gridY, gridWidth, gridHeight));
    painter.fillPath(framePath, this->m_bgColor);//painter.drawPath(framePath);

    painter.save();

    //draw download smoothcurve
    painter.setOpacity(1);
    painter.translate((rect().width() - m_pointsCount * m_pointSpace - 2) / 2 + 6, 80);//将坐标第原点移动到该点
    painter.scale(1, -1);//将横坐标扩大1倍,将纵坐标缩小1倍
    painter.setPen(QPen(this->m_downloadColor, 1));
    painter.setBrush(QBrush());//painter.setBrush(QBrush(QColor("#f4f2f4")));
    painter.drawPath(m_downloadPath);//绘制前面创建的path:m_downloadPath

    //draw upload smoothcurve
    painter.translate(0, -8);
    painter.setPen(QPen(this->m_uploadColor, 1));
    painter.setBrush(QBrush());//painter.setBrush(QBrush(QColor("#f4f2f4")));
    painter.drawPath(m_uploadPath);

    painter.restore();

    painter.setRenderHint(QPainter::Antialiasing, true);
    setFontSize(painter, 12);
    QFontMetrics fm = painter.fontMetrics();
    int receiveTextWidth = fm.width(this->receiveText);
    int sendTextWidth = fm.width(this->sendText);
    painter.setPen(QPen(QColor("#000000"), 1));
    painter.drawText(QRect(gridX, gridHeight + 10, receiveTextWidth, 30), Qt::AlignLeft | Qt::AlignVCenter, this->receiveText);
    painter.drawText(QRect(gridX + receiveTextWidth*2, gridHeight + 10, sendTextWidth, 30), Qt::AlignLeft | Qt::AlignVCenter, this->sendText);
    painter.setPen(QPen(QColor("#009944"), 1));
    painter.drawLine(gridX + receiveTextWidth + 5, gridHeight + 10 + 30/2, gridX + receiveTextWidth*2 - 10, gridHeight + 10 + 30/2);
    painter.setPen(QPen(QColor("#e60012"), 1));
    painter.drawLine(gridX + receiveTextWidth*2 + sendTextWidth + 5, gridHeight + 10 + 30/2, gridX + receiveTextWidth*3 + sendTextWidth - 10, gridHeight + 10 + 30/2);

    int contentWidth = 180;
    //draw title
    setFontSize(painter, 12);
    painter.setPen(QPen(QColor("#999999")));
    painter.drawText(QRect(gridX, gridHeight + 40, contentWidth, 30), Qt::AlignLeft |Qt::AlignVCenter, tr("Receiving"));
    painter.drawText(QRect(gridX + contentWidth, gridHeight + 40, contentWidth, 30), Qt::AlignLeft |Qt::AlignVCenter, tr("Sending"));
    painter.drawText(QRect(gridX, gridHeight + 100, contentWidth, 30), Qt::AlignLeft |Qt::AlignVCenter, tr("Total Received"));
    painter.drawText(QRect(gridX + contentWidth, gridHeight + 100, contentWidth, 30), Qt::AlignLeft |Qt::AlignVCenter, tr("Total Sent"));

    //draw text data
    setFontSize(painter, 20);
    QFontMetrics fms = painter.fontMetrics();
    painter.setPen(QPen(QColor("#000000")));
    const QString downloadRate = formatNetworkRate(m_recvRateBytes);
    const QString downloadContent = formatNetwork(m_recvTotalBytes);//接收
    const QString uploadRate = formatNetworkRate(m_sentRateBytes);
    const QString uploadContent = formatNetwork(m_sentTotalBytes);
    painter.drawText(QRect(gridX, gridHeight + 70, fms.width(downloadRate), 30), Qt::AlignLeft |Qt::AlignVCenter, downloadRate);
    painter.drawText(QRect(gridX + contentWidth, gridHeight + 70, fms.width(uploadRate), 30), Qt::AlignLeft |Qt::AlignVCenter, uploadRate);
    painter.drawText(QRect(gridX, gridHeight + 130, fms.width(downloadContent), 30), Qt::AlignLeft |Qt::AlignVCenter, downloadContent);
    painter.drawText(QRect(gridX + contentWidth, gridHeight + 130, fms.width(uploadContent), 30), Qt::AlignLeft |Qt::AlignVCenter, uploadContent);
}
