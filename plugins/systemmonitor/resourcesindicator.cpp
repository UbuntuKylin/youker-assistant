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


#include "resourcesindicator.h"

#include <QMouseEvent>
#include <QEvent>
#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>

ResourcesIndicator::ResourcesIndicator(int flag, QWidget *parent)
    : QWidget(parent)
    ,m_state(Normal)
    ,m_isChecked(false)
    ,m_currentPercent(0)
    ,m_posX(5)
    ,m_rectTopPadding(9)
    ,m_rectTotalHeight(38)
    ,m_rectTotalWidth(58)
    ,m_outsideBorderColor(Qt::transparent)
    ,m_bgColor(QColor("#ffffff"))
{
    this->setFixedSize(188, 56);

    if (flag == 0) {
        m_borderColor = QColor("#0973b4");
    }
    else if (flag == 1) {
        m_borderColor = QColor("#9528b4");
    }
    else {
        m_borderColor = Qt::transparent;
    }
    setResourcesState(Normal);
}

ResourcesIndicator::~ResourcesIndicator()
{

}

void ResourcesIndicator::enterEvent(QEvent *event)
{
    setCursor(Qt::PointingHandCursor);

    if (!m_isChecked) {
        setResourcesState(Hover);
    }

    event->accept();
    //QWidget::enterEvent(event);
}

void ResourcesIndicator::leaveEvent(QEvent *event)
{
    if (!m_isChecked) {
        setResourcesState(Normal);
    }

    event->accept();
    //QWidget::leaveEvent(event);
}

void ResourcesIndicator::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
        return;

    setResourcesState(Press);

    event->accept();
    //QWidget::mousePressEvent(event);
}

void ResourcesIndicator::mouseReleaseEvent(QMouseEvent *event)
{
    if (!rect().contains(event->pos()))
        return;

    m_isChecked = !m_isChecked;
    if (m_isChecked) {
        setResourcesState(Checked);
    } else {
        setResourcesState(Normal);
    }

    event->accept();
    //QWidget::mouseReleaseEvent(event);

    if (event->button() == Qt::LeftButton)
        emit clicked();
}

void ResourcesIndicator::mouseMoveEvent(QMouseEvent *event)
{
    if (!rect().contains(event->pos())) {
        setResourcesState(Normal);
    }
}

void ResourcesIndicator::updateBgColor()
{
    switch (m_state) {
    case Hover:
        this->m_outsideBorderColor = Qt::transparent;
        this->m_bgColor = QColor("#f6fcfe");
        break;
    case Press:
        this->m_outsideBorderColor = Qt::transparent;
        this->m_bgColor = QColor("#f6fcfe");
        break;
    case Checked:
        this->m_outsideBorderColor = QColor("#0973b4");
        this->m_bgColor = QColor("#e9f8fd");
        break;
    default:
        this->m_outsideBorderColor = Qt::transparent;
        this->m_bgColor = QColor("#ffffff");
        break;
    }
    repaint();
}

void ResourcesIndicator::setResourcesState(ResourcesIndicator::ResourcesState state)
{
    if (m_state == state)
        return;

    m_state = state;
    updateBgColor();
}

void ResourcesIndicator::setChecked(bool flag)
{
    m_isChecked = flag;
    if (m_isChecked){
        setResourcesState(Checked);
    } else {
        setResourcesState(Normal);
    }
}

bool ResourcesIndicator::isChecked()
{
    return m_isChecked;
}

void ResourcesIndicator::setTitle(const QString &title)
{
    this->m_title = title;
}

void ResourcesIndicator::updatePercentAndInfo(double percent, const QString &info)
{

    this->m_currentPercent = static_cast<int>(percent);
    this->m_info = info;
    repaint();
}

ResourcesIndicator::ResourcesState ResourcesIndicator::getResourcesState() const
{
    return m_state;
}

void ResourcesIndicator::paintEvent(QPaintEvent *event)
{
    //渐变填充
    /*QRadialGradient gradient(50, 50, 50, 50, 50);
    gradient.setColorAt(0, QColor::fromRgbF(0, 1, 0, 1));
    gradient.setColorAt(1, QColor::fromRgbF(0, 0, 0, 0));
    QBrush brush(gradient);*/

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    //border of rect
    QPainterPath borderPath;
    borderPath.addRoundedRect(this->rect(), 0, 0);
    QPen pen(this->m_outsideBorderColor, 1);
//    QPen pen(QColor("#B22222"), 1);
    painter.setPen(pen);
    painter.drawPath(borderPath);

    //background of rect
    painter.setOpacity(1);
    QPainterPath path;
    path.addRect(QRectF(1, 1, width()-2, height()-2));
    painter.fillPath(path, this->m_bgColor);
//    painter.fillPath(path, QColor("#f6fcfe"));

    int convertPercent = static_cast<int>(m_rectTotalHeight*this->m_currentPercent/100);

    //percent rect
    painter.setPen(QPen(this->m_borderColor, 0.5));//设置画笔颜色、宽度
    painter.setBrush(QColor("#ffffff"));//设置画刷颜色
    painter.drawRect(this->m_posX, this->m_rectTopPadding, this->m_rectTotalWidth, this->m_rectTotalHeight - convertPercent);
    painter.setBrush(QColor("#f4f2f4"));
    painter.drawRect(this->m_posX, this->m_rectTopPadding + this->m_rectTotalHeight - convertPercent, this->m_rectTotalWidth, convertPercent);

    //draw title
    painter.setRenderHint(QPainter::Antialiasing, false);
    QFont font = painter.font() ;
    font.setPixelSize(16);
    painter.setFont(font);
    painter.setPen(QPen(QColor("#000000")));
    painter.drawText(QRect(68, 1, 118, 28), Qt::AlignLeft | Qt::AlignVCenter, this->m_title);

    //draw content
    font.setPixelSize(12);
    painter.setFont(font);
    QFontMetrics fm(font);
    QString text = fm.elidedText(this->m_info, Qt::ElideRight, 120);
    painter.drawText(QRect(68, 30, 120, 20), Qt::AlignLeft | Qt::AlignVCenter, text);

    QWidget::paintEvent(event);
}
