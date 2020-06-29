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

#include "kylintoolbutton.h"
#include <QDebug>
#include <QtSvg/QSvgRenderer>

KylinToolButton::KylinToolButton(const QString &pic_name, const QString &text, QWidget *parent)
    :QToolButton(parent)
{
    setDown(false);
    setFocusPolicy(Qt::NoFocus);

    txt=text;
    this->setText(text);
    this->setStyleSheet("color:white");

//	QPalette text_palette = palette();
//	text_palette.setColor(QPalette::ButtonText, QColor(230, 230, 230));
//	setPalette(text_palette);

//	QFont &text_font = const_cast<QFont &>(font());
//	text_font.setWeight(QFont::Bold);

    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
//    setToolButtonStyle( Qt::ToolButtonTextUnderIcon);
    setPopupMode(QToolButton::InstantPopup);

    pixmap.load(pic_name);

//    QSvgRenderer* svgRender = new QSvgRenderer(QString(pic_name));
//    QPixmap *pixmap = new QPixmap(32,32);
//    pixmap->fill(Qt::transparent);//设置背景透明
//    QPainter p(pixmap);
//    svgRender->render(&p);

//    normal_icon = QIcon(pic_name);
//    hover_icon = QIcon(pic_name + "-hover");
//    press_icon = QIcon(pic_name + "-press");
//    hover_icon = QIcon(pic_name);
//    press_icon = QIcon(pic_name);
//    setIcon(pixmap);
//    setIconSize(pixmap.size());

//    setFixedSize(pixmap.width(), pixmap.height() + 10);
	setAutoRaise(true);
    this->setObjectName("transparentToolButton");
	mouse_over = false;
	m_mousePressed = false;
    pressed = false;
}

KylinToolButton::~KylinToolButton()
{

}

void KylinToolButton::enterEvent(QEvent *event)
{
    if(isEnabled())
    {
        mouse_over = true;
//        this->setMouseHover();
    }
}

void KylinToolButton::leaveEvent(QEvent *event)
{
    if(isEnabled())
    {
        mouse_over = false;
//        this->setMouseHover();
    }
}

void KylinToolButton::mousePressEvent(QMouseEvent *event)
{
    if(isEnabled() && event->button() == Qt::LeftButton)
    {
        //kobe: don't emit, it will emit by click it self.
//        emit clicked();
//        pressed = true;
    }
    QToolButton::mousePressEvent(event);
}

/**
  * 在此函数里面绘制按钮的三态样式
  *
  * @param   {QPaintEvent *}event
  * @return  null
**/
void KylinToolButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing); //反锯齿

    //设置渐变色的样式和范围
    QLinearGradient linear(this->height()/2,0,this->height()/2,this->width());
    linear.setColorAt(0, Qt::transparent);
    linear.setColorAt(1, QColor(255,255,255,80));


    //绘制按钮的 hover 状态的样式
    if(mouse_over)
    {
        painter.setPen(Qt::transparent);
        painter.setBrush(linear);//设置渐变色给 brush
        painter.drawRect(0,0,this->height(),this->width());//用渐变色填充这个 Rect 区域
        painter.drawPixmap(QRect(22,8,48,48),QPixmap(pixmap)); //绘制 pixmap 图片
//        qDebug() << Q_FUNC_INFO << txt;
        painter.setPen(Qt::white);
        painter.drawText(QRect(16,60,60,18),Qt::AlignCenter,txt); //绘制文字
    }
    else //绘制按钮从 hover 转换到非 hover 状态的样式
    {
        painter.setPen(Qt::transparent);
        painter.setBrush(Qt::transparent);
        painter.drawRect(0,0,this->height(),this->width());
        painter.drawPixmap(QRect(22,8,48,48),QPixmap(pixmap));
//        qDebug() << Q_FUNC_INFO << txt;
        painter.setPen(Qt::white);
        painter.drawText(QRect(16,60,60,18),Qt::AlignCenter,txt);
    }

    //绘制按钮的 pressed 状态的样式
    if(pressed)
    {
        painter.setPen(Qt::transparent);
        painter.setBrush(linear);   //设置渐变色给 brush
        painter.drawRect(0,0,this->height(),this->width()); //将渐变色填充带这个 Rect 区域
        painter.drawPixmap(QRect(22,8,48,48),QPixmap(pixmap));  //绘制 pixmap 图片
//        qDebug() << Q_FUNC_INFO << txt;
        painter.setPen(Qt::white);
        painter.drawText(QRect(16,60,60,18),Qt::AlignCenter,txt); //绘制文字
    }
    else //绘制按钮从 pressed 转换到非 pressed 状态的样式
    {
        painter.setPen(Qt::transparent);
        painter.setBrush(Qt::transparent);
        painter.drawRect(0,0,this->height(),this->width());
        painter.drawPixmap(QRect(22,8,48,48),QPixmap(pixmap));
//        qDebug() << Q_FUNC_INFO << txt;
        painter.setPen(Qt::white);
        painter.drawText(QRect(16,60,60,18),Qt::AlignCenter,txt);
    }

}

void KylinToolButton::setMouseHover()
{
//    if(this->mouse_over)
//    {
//        this->setIcon(QIcon(hover_icon));
//    }
//    else {
//        if(pressed){
//            this->setIcon(QIcon(press_icon));
//        }
//        else{
//            this->setIcon(QIcon(normal_icon));
//        }
//    }
//    this->setStyleSheet("ToolButton{background-color:qlineargradient(x1:0, y1:0, x2:92, y2:85,stop:0 green,stop:1 red);color:white;}");
}

void KylinToolButton::setMousePress(bool is_press)
{
    this->m_mousePressed = is_press;

    if(this->m_mousePressed)
    {
//        this->setIcon(QIcon(press_icon));
        this->update();
        pressed = true;
    }
    else
    {
//        this->setIcon(QIcon(normal_icon));
        this->update();
        pressed = false;
    }

//    if(this->mouse_over)
//    {
//        this->setIcon(QIcon(hover_icon));
//    }
//    else
//    {
//        if(this->m_mousePressed)
//        {
//            this->setIcon(QIcon(press_icon));
//        }
//        else
//        {
//            this->setIcon(QIcon(normal_icon));
//        }
//    }
}
