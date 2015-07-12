/*
 * Copyright (C) 2013 ~ 2015 National University of Defense Technology(NUDT) & Kylin Ltd.
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

#include "toolbutton.h"
#include <QEvent>
#include <QMouseEvent>
#include <QLabel>
#include <QVBoxLayout>
#include <QFont>
#include <QFontMetrics>

ToolButton::ToolButton(QWidget *parent, bool whiteflag) :
    QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAutoFillBackground(true);
    this->setCursor(Qt::PointingHandCursor);
    this->setFixedSize(90, 90);
    this->setFocusPolicy(Qt::NoFocus);
    QPalette palette;
    palette.setColor(this->backgroundRole(), QColor(255,255,255));//#ffffff
    this->setPalette(palette);
    iconLabel = new QLabel;
    textLabel = new QLabel;
    if(whiteflag)
        textLabel->setObjectName("backgroundWhiteLabel");
    else
        textLabel->setObjectName("backgroundLabel");
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(iconLabel, 0, Qt::AlignCenter);
    layout->addWidget(textLabel, 0, Qt::AlignHCenter);
    layout->setContentsMargins(0, 10, 0, 10);
    this->setLayout(layout);
}

ToolButton::~ToolButton()
{
    if(iconLabel != NULL) {
        delete iconLabel;
        iconLabel = NULL;
    }
    if(textLabel != NULL) {
        delete textLabel;
        textLabel = NULL;
    }
}

void ToolButton::setIcon(const QString &icon)
{
    QPixmap pixmap(icon);
    iconLabel->setPixmap(pixmap);
    iconLabel->setFixedSize(pixmap.size());
}

void ToolButton::setText(const QString &text)
{
    QFont ft;
    QFontMetrics fm(ft);
    QString elided_text = fm.elidedText(text, Qt::ElideRight, 90);
    textLabel->setText(elided_text);
    textLabel->adjustSize();
    if(elided_text.endsWith("…"))
        this->setToolTip(text);
}

void ToolButton::setToolButtonStatus(BUTTONSTATUS status)
{
    QPalette palette;
    switch (status) {
    case BUTTON_ENTER:
        palette.setColor(this->backgroundRole(), QColor(233,238,241));//#e9eef1
        this->setPalette(palette);
        break;
    case BUTTON_LEAVE:
        palette.setColor(this->backgroundRole(), QColor(255,255,255));//#ffffff
        this->setPalette(palette);
        break;
    case BUTTON_PRESSED:
        palette.setColor(this->backgroundRole(), QColor(233,238,241));//#e9eef1
        this->setPalette(palette);
        break;
    default:
        break;
    }
//    QPalette palette;
////    palette.setBrush(this->backgroundRole(),QBrush(Qt::green));
////    palette.setBrush(QPalette::Window, QBrush(Qt::white));
////    palette.setColor(QPalette::Background, QColor(233,238,241));//#e9eef1
//    palette.setColor(this->backgroundRole(), QColor(233,238,241));//#e9eef1
//    this->setPalette(palette);
}

void ToolButton::enterEvent(QEvent *)
{
    setToolButtonStatus(BUTTON_ENTER);
}

void ToolButton::leaveEvent(QEvent *)
{
    setToolButtonStatus(BUTTON_LEAVE);
}

void ToolButton::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        ToolButton(BUTTON_PRESSED);
    }
    else
    {
        e->ignore();
    }
}

void ToolButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        if(rect().contains(e->pos()))
        {
            if(this->isEnabled()) {
                emit clicked();
            }
            setToolButtonStatus(BUTTON_ENTER);
            e->accept();
        }else{
            setToolButtonStatus(BUTTON_LEAVE);
            e->ignore();
        }
    }
    else
    {
        e->ignore();
    }
}
