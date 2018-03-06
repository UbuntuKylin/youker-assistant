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

#include "cpuballwidget.h"

#include <QApplication>
#include <QDebug>
#include <QPainter>
#include <QImageReader>
#include <QGraphicsDropShadowEffect>

#include <QtMath>
qreal gradientDistance(qreal x)
{
    return (1 - qCos(M_PI * x)) / 2;
}

CpuBallWidget::CpuBallWidget(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(210, 210);

    m_frontImagePath = "://res/wave_front.png";
    m_backimagePath = "://res/wave_back.png";

    m_xFrontOffset = 0;
    m_xBackOffset = this->width();
    m_prevPercentValue = 0.0;
    m_percentValue = 0.0;
    m_progressText = QString("%1%").arg(QString::number(m_percentValue, 'f', 1));

    m_shadowEffect = new QGraphicsDropShadowEffect(this);
    m_shadowEffect->setOffset(0, 3);
    m_shadowEffect->setColor(QColor(232, 232, 232, 127));
    m_shadowEffect->setBlurRadius(10);
    this->setGraphicsEffect(m_shadowEffect);

    this->loadWaveImage();

    m_waveTimer = new QTimer(this);
    connect(m_waveTimer, SIGNAL(timeout()), this, SLOT(onRepaintWaveImage()));
    m_waveTimer->setInterval(200);

    m_animationIndex = 0;
    m_animationCounts = 2000/200;//2000为数据更新的时间间隔，200为波浪更新的时间间隔
}

CpuBallWidget::~CpuBallWidget()
{
    delete m_shadowEffect;

    if (m_waveTimer) {
        disconnect(m_waveTimer, SIGNAL(timeout()), this, SLOT(onRepaintWaveImage()));
        if(m_waveTimer->isActive()) {
            m_waveTimer->stop();
        }
        delete m_waveTimer;
        m_waveTimer = nullptr;
    }
}

void CpuBallWidget::loadWaveImage()
{
    QImageReader frontReader(m_frontImagePath);
    int w = frontReader.size().width();
    int h = frontReader.size().height();
//    w = w * this->width() / 100;
//    h = h * this->height() / 100;
    QImage image(w, h, QImage::Format_ARGB32_Premultiplied);//QImage::Format_ARGB32
    image.fill(Qt::transparent);
    image.load(m_frontImagePath);
    /*QPainter painter(&image);
//    painter.setCompositionMode(QPainter::CompositionMode_Source);
//    painter.fillRect(image.rect(), Qt::transparent);
//    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(QPoint(0,0), image);
    painter.end();*/
    m_frontImage = image;

    QImageReader backReader(m_backimagePath);
    w = backReader.size().width();
    h = backReader.size().height();
//    w = w * this->width() / 100;
//    h = h * this->height() / 100;
    QImage backImage(w, h, QImage::Format_ARGB32_Premultiplied);//QImage::Format_ARGB32
    backImage = backImage.scaled(QSize(w, h), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    backImage.fill(Qt::transparent);
    backImage.load(m_backimagePath);
    /*QPainter backPainter(&backImage);
//    backPainter.setCompositionMode(QPainter::CompositionMode_Source);
//    backPainter.fillRect(image.rect(), Qt::transparent);
//    backPainter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    backPainter.drawImage(QPoint(0,0), backImage);
    backPainter.end();*/
    m_backImage = backImage;
}

void CpuBallWidget::onRepaintWaveImage()
{
    m_xFrontOffset += 2;
    m_xBackOffset += 2;
    if (m_xFrontOffset > m_frontImage.width()) {//保留整个显示直径的大小不做处理，避免出现断层
        m_xFrontOffset = 0;
    }
    if (m_xBackOffset > m_backImage.width()) {//保留整个显示直径的大小不做处理，避免出现断层
        m_xBackOffset = 0;
    }

    if (m_animationIndex < m_animationCounts) {
        m_animationIndex++;
        repaint();
    } else {
        m_waveTimer->stop();
    }
//    this->update();//this->repaint();
}

//value:0 ~ 100
void CpuBallWidget::updateCpuPercent(double value)
{
    if (this->m_percentValue == value || value > 100 || value < 0) {
        return;
    }
    m_prevPercentValue = m_percentValue;
    m_percentValue = value;
    m_progressText = QString("%1%").arg(QString::number(value, 'f', 1));

    m_animationIndex = 0;
    m_waveTimer->start();
}

void CpuBallWidget::startTimer()
{
//    if (this->m_waveTimer && !this->m_waveTimer->isActive())
//        this->m_waveTimer->start();
}

void CpuBallWidget::stopTimer()
{
//    if (this->m_waveTimer && this->m_waveTimer->isActive())
//        this->m_waveTimer->stop();
}

//在不同的平台上得到一样的效果，但绘制的文字除外
void CpuBallWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);//设置反走样，避免锯齿

    QRectF rect = QRectF(0, 0, this->width(), this->height());
    QSize waveSize = this->size();

//    int currentPercent = static_cast<int>(m_percentValue);
    double percent = m_prevPercentValue + gradientDistance(m_animationIndex / m_animationCounts) * (m_percentValue - m_prevPercentValue);
    int currentPercent = static_cast<int>(percent);

    //Step1:整个矩形背景
    QImage waveRectImage = QImage(waveSize, QImage::Format_ARGB32_Premultiplied);//创建一个Format_ARGB32_Premultiplied 格式的QIamge，大小和控件相同
    QPainter wavePainter(&waveRectImage);//创建一个QPainter绘制waveRectImage这个图像
    wavePainter.setRenderHint(QPainter::Antialiasing, true);//setRenderHint() 来设置反走样，要么绘制出来的线条会出现锯齿
//    wavePainter.initFrom(this);//用控件的设置初始化画笔，刷子和字体
    wavePainter.setCompositionMode(QPainter::CompositionMode_Source);//输出源像素，避免整个矩形背景区域出现花屏现象
    if (currentPercent > 88) {
        m_shadowEffect->setColor(QColor(255, 0, 0, 127));//红色
    } else if (currentPercent > 55) {
        m_shadowEffect->setColor(QColor(255, 193, 37, 127));//黄
    } else {
        m_shadowEffect->setColor(QColor(232, 232, 232, 127));//灰
    }
    wavePainter.fillRect(waveRectImage.rect(), QColor(255, 255, 255, 127));

    //Step2:波浪区域
    //CompositionMode_SourceOver保证波浪出现的时候其背景为通明的
    wavePainter.setCompositionMode(QPainter::CompositionMode_SourceOver);//混和模式QImage::CompositionMode_SourceOver ，即原象素（正在绘制的象素）和目标象素（已经存在的象素）混和，原象素的alpha分量定义为最终的透明度
    wavePainter.drawImage(static_cast<int>(m_xBackOffset), (100 - currentPercent)*this->width()/100, m_backImage);
    wavePainter.drawImage(static_cast<int>(m_xBackOffset) - m_backImage.width(), (100 - currentPercent)*this->width()/100, m_backImage);
    wavePainter.drawImage(static_cast<int>(m_xFrontOffset), (100 - currentPercent)*this->width()/100, m_frontImage);
    wavePainter.drawImage(static_cast<int>(m_xFrontOffset) - m_frontImage.width(), (100 - currentPercent)*this->width()/100, m_frontImage);

    //Step3:矩形区域中圆球的外径
    /*QRectF outRect = QRectF(0, 0, waveSize.width(), waveSize.height());
    QPainterPath outBorderPath;
    //QMargins定义了矩形的四个外边距量，left,top,right和bottom，描述围绕矩形的边框宽度
    outBorderPath.addEllipse(outRect.marginsRemoved(QMarginsF(0.5, 0.5, 0.5, 0.5)));//marginsAdded:增长矩形的边距，扩大它
    wavePainter.strokePath(outBorderPath, QPen(QColor("#0f84bc"), 1));//外边框*/
    //QGradient支持三种渐变画刷：线性渐变(QLinearGradient)、辐射渐变(QRadialGradient)、角度渐变(QConicalGradient)
    QRectF outRect = QRectF(0, 0, waveSize.width(), waveSize.height());
    QConicalGradient conicalGradient(waveSize.width()/2, waveSize.height()/2, waveSize.width());//参数分别为中心坐标和初始角度
    conicalGradient.setColorAt(0, QColor("#59aee2"));
    conicalGradient.setColorAt(1.0, QColor("#0f84bc"));
    wavePainter.setPen(QPen(QBrush(conicalGradient), 1));
    wavePainter.drawEllipse(outRect.marginsRemoved(QMarginsF(0.5, 0.5, 0.5, 0.5)));

    //Step4:占用率文字描述
    QFont font = wavePainter.font();
    font.setPixelSize(44);//waveSize.height() * 20 / this->height()
    wavePainter.setFont(font);
    wavePainter.setPen(Qt::white);
    wavePainter.drawText(QRect(rect.x(), rect.y() + rect.height()*2/3, rect.width(), rect.height()/3), Qt::AlignHCenter, m_progressText);
    wavePainter.end();

    QImage image = QImage(waveSize, QImage::Format_ARGB32_Premultiplied);
    QPainter m_painter(&image);
    //让矩形框中除掉圆形球以外的其他区域透明
    m_painter.setCompositionMode(QPainter::CompositionMode_Source);//输出源像素，避免区域出现花屏现象
    m_painter.fillRect(image.rect(), Qt::transparent);

    //为圆形球绘制一个圆形的白色遮罩层,目的是让矩形除了圆形区域外，其他区域为透明的没有任何东西显示在上面，方便后面的圆球和波浪的显示
    QPixmap maskPixmap(waveSize);
    maskPixmap.fill(Qt::transparent);
    QPainterPath path;
    path.addEllipse(QRectF(0, 0, waveSize.width(), waveSize.height()));
    QPainter maskPainter(&maskPixmap);
    maskPainter.setRenderHint(QPainter::Antialiasing, true);
    maskPainter.setPen(QPen(Qt::white, 1));
    maskPainter.fillPath(path, QBrush(Qt::white));
    m_painter.setCompositionMode(QPainter::CompositionMode_SourceOver);//默认模式,源的alpha将目标顶部的像素混合
    m_painter.drawImage(0, 0, maskPixmap.toImage());

    m_painter.setCompositionMode(QPainter::CompositionMode_SourceIn);//输出是源，其中alpha被目标的值减少   设置画刷的组合模式CompositionMode_SourceIn这个模式为目标图像在下
    m_painter.drawImage(0, 0, waveRectImage);

    m_painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);//目标的alpha用于将其混合到源像素的顶部。这种模式是QPainter::CompositionMode_Source逆
    m_painter.end();

    painter.drawImage(this->rect(), image);//drawPixmap
}
