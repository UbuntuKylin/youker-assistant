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

#include "kylintitlebar.h"
#include <QDebug>
#include <QHBoxLayout>

KylinTitleBar::KylinTitleBar(QWidget *parent) :
    QWidget(parent)
  , left_btn_pressed(false)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedHeight(32);
    this->setAutoFillBackground(true);

//    min_btn = new SystemButton();
    close_btn = new SystemButton(this);
    close_btn->setFocusPolicy(Qt::NoFocus);
//    min_btn->loadPixmap(":/sys/res/sysBtn/min_button.png");
    close_btn->loadPixmap(":/sys/res/sysBtn/close_button.png");

    title_label = new QLabel(this);
    title_label->setAlignment(Qt::AlignCenter);
    title_label->setStyleSheet("QLabel{color:#ffffff;font-family: 方正黑体_GBK;font-size: 14px;text-align: center;font-weight:bold;}");
//    logo_label = new QLabel();
//    logo_label->setFixedSize(22, 22);
//    logo_label->setFrameShape(QFrame::NoFrame);
//    logo_label->setAutoFillBackground(true);
//    logo_label->setScaledContents(true);//自动缩放,显示图像大小自动调整为Qlabel大小
//    QPixmap label_pixmap("://res/icon.png");
//    logo_label->setPixmap(label_pixmap);

//    logo_label->setFixedSize(label_pixmap.size());
//    QPalette palette;
//    palette.setBrush(QPalette::Background, QBrush(QPixmap("://res/logo.png")));
//    logo_label->setPalette(palette);

//    QHBoxLayout *label_layout = new QHBoxLayout();
//    label_layout->addWidget(logo_label, 0, Qt::AlignVCenter);
//    label_layout->addWidget(title_label, 0, Qt::AlignVCenter);
//    label_layout->setSpacing(5);
//    label_layout->setMargin(0);
//    label_layout->setContentsMargins(2, 2, 0, 0);

//    QHBoxLayout *btn_layout = new QHBoxLayout();
//    btn_layout->addWidget(min_btn, 0, Qt::AlignTop);
//    btn_layout->addWidget(close_btn, 0, Qt::AlignVCenter);
//    QHBoxLayout *main_layout = new QHBoxLayout();
//    main_layout->addWidget(close_btn, 0, Qt::AlignVCenter);
//    main_layout->addLayout(btn_layout);
//    main_layout->addStretch();
//    main_layout->addWidget(title_label, 0, Qt::AlignVCenter);
//    main_layout->addStretch();
//    main_layout->addWidget(logo_label, 0, Qt::AlignVCenter);
//    main_layout->addLayout(label_layout);

//    main_layout->setSpacing(0);
//    main_layout->setMargin(0);
//    main_layout->setContentsMargins(0, 0, 2, 0);
//    setLayout(main_layout);

//    connect(min_btn, SIGNAL(clicked()), this, SIGNAL(showMinDialog()));
    connect(close_btn, SIGNAL(clicked()), this, SIGNAL(closeDialog()));
}

KylinTitleBar::~KylinTitleBar(void)
{
    if(title_label != NULL)
    {
        delete title_label;
        title_label = NULL;
    }
    if(close_btn != NULL)
    {
        delete close_btn;
        close_btn = NULL;
    }
}

void KylinTitleBar::resetBackground(QString name)
{
    backgroud_image = name;
    QPalette palette_widget;
    palette_widget.setBrush(QPalette::Background, QBrush(QPixmap(backgroud_image)));
    setPalette(palette_widget);
}

//20161228
void KylinTitleBar::setTitleWidth(int width)
{
    title_width = width;

//#ifdef __aarch64__
    close_btn->move(title_width - 36, 0);
//#else
//    close_btn->move(0, 0);
//#endif
}

void KylinTitleBar::resizeEvent(QResizeEvent *event)
{
    //width
    this->setFixedWidth(title_width);

    //backgrond
    QPalette palette_widget;
    palette_widget.setBrush(QPalette::Background, QBrush(QPixmap(backgroud_image)));
    setPalette(palette_widget);

    //title and font
    title_label->setText(title_content);
    title_label->setGeometry(QRect(40, 0, title_width- 80, 32));
//    title_label->setGeometry(QRect(40, 0, 40, 32));
//    QPalette objPalette = palette();
//    objPalette.setColor(QPalette::WindowText, Qt::white);
//    title_label->setPalette(objPalette);
//    QFont &objFont = const_cast<QFont&>(font());
//    objFont.setWeight(QFont::Bold);
//    title_label->setFont(objFont);
}

void KylinTitleBar::mousePressEvent ( QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if(event->y() < 5 || event->x() < 5 || rect().width() - event->x() < 5) {
            event->ignore();
            return;
        }
        press_point = event->globalPos();
        left_btn_pressed = true;
    }
    event->ignore();
}

void KylinTitleBar::mouseMoveEvent ( QMouseEvent *event)
{
    if(left_btn_pressed) {
        move_point = event->globalPos();
        QWidget *pMainWindow = (qobject_cast<QWidget *>(parent()));
        pMainWindow->move(pMainWindow->pos() + move_point - press_point);
        press_point = move_point;
    }
    event->ignore();
}

void KylinTitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        left_btn_pressed = false;
    }
    event->ignore();
}
