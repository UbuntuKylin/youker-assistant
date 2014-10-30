/*
 * Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd.
 * Author: Kobe Lee
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

#include "slidershow.h"
#include <QDebug>
#include <QDesktopWidget>
//513 417    680 370

SliderShow::SliderShow(QWidget *parent)
    :QDialog(parent)
{
    current_index = 0;
    page_count = 5;
    window_btn_count = 5;

    this->setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->resize(QSize(680, 372));

    //背景底片
    background_label = new QLabel(this);
    background_label->setPixmap(QPixmap(":/pixmap/image/bg_bottom"));
    background_label->setGeometry(QRect(0, 0, this->width(), this->height()));

    //把所有要显示的图片设置到一个大的label中
    QPixmap pixmap(QSize(this->width()*page_count, 372));
    QPainter painter(&pixmap);
    for(int i = 0; i < page_count; i++) {
        painter.drawImage(QRect(680*i, 0, 680, 372), QImage(QString(":/pixmap/image/desktop_%1").arg(i)));
    }
    master_label = new QLabel(this);
    master_label->resize(pixmap.size());
    master_label->setPixmap(pixmap);
    master_label->move(0, 0);

    //设置图片上的index按钮
    for(int i = 0; i < window_btn_count; i++)
    {
        IconText *label;
        label = new IconText(i, this);
        label->resize(QSize(14, 14));
        label->setIcon(QPixmap(QString(":/pixmap/image/dot_normal")));
        label->move(300+i*14, 319);
        connect(label, SIGNAL(ukclicked(int)), this, SLOT(changeCurrentPage(int)));
        pic_array[i] = label;
        label->raise();
    }
    pic_array[0]->setMousePressFlag(true);
    pic_array[0]->installEventFilter(this);
    pic_array[1]->installEventFilter(this);
    pic_array[2]->installEventFilter(this);
    pic_array[3]->installEventFilter(this);
    pic_array[4]->installEventFilter(this);
    //设置隐藏按钮属性
    close_button = new KButton(this);
    close_button->setPicName(":/pixmap/image/closeBtn");
    close_button->resize(QSize(26, 20));
    close_button->move(1, 1);
    close_button->raise();
    close_button->installEventFilter(this);
    connect(close_button, SIGNAL(clicked()), this, SLOT(accept()));

    //设置开始按钮属性
    hLayout = new QHBoxLayout(this);
    start_button = new KButton(this);

    locale_Lan = this->get_locale_version();
    if(locale_Lan == "zh_CN") {
        start_button->setPicName(":/pixmap/image/start");
    }
    else {
        start_button->setPicName(":/pixmap/image/start_en");
    }
    start_button->resize(QSize(180, 57));
    start_button->raise();
    start_button->hide();
    hLayout->addWidget(start_button);
    hLayout->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);
    start_button->installEventFilter(this);
    connect(start_button, SIGNAL(clicked()), this, SLOT(start_run_program()));

    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerChangePosition()));
    timer->start(3000);

    int windowWidth = QApplication::desktop()->width();
    int windowHeight = QApplication::desktop()->height();
    this->move((windowWidth - this->width()) / 2,(windowHeight - this->height()) / 2);
}

SliderShow::~SliderShow()
{
    for (int i = 0; i < page_count; i++) {
        delete pic_array[i];
    }
    delete master_label;
    delete close_button;
    delete background_label;
    delete start_button;

    disconnect(timer,SIGNAL(timeout()),this,SLOT(timerChangePosition()));
    if(timer->isActive()) {
        timer->stop();
    }
    if (timer != NULL) {
        delete timer;
    }
}

QString SliderShow::get_locale_version() {
    QString locale = QLocale::system().name();
    return locale;
}

bool SliderShow::eventFilter(QObject *obj, QEvent *event) {
    if(obj == start_button || obj == close_button || obj == pic_array[0] || obj == pic_array[1] || obj == pic_array[2] || obj == pic_array[3] || obj == pic_array[4])
    {
        if (((QMouseEvent *)event)->button() == Qt::LeftButton) {
            if (event->type() == QEvent::MouseButtonPress) {
                mouse_move = false;
            }
        }
    }
    return QObject::eventFilter(obj, event);
}

void SliderShow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        dragPos = event->globalPos() - frameGeometry().topLeft();
        event->accept();
        mouse_move = true;
    }
}

void SliderShow::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton ) {
        if(mouse_move) {
            move(event->globalPos() - dragPos);
            setWindowOpacity(0.7);
        }
    }
    event->accept();
}

void SliderShow::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        setWindowOpacity(1);
    }
    event->accept();
}

//点击按钮时更换成对应的图片
void SliderShow::changeCurrentPage(int index/*IconText *iconText*/)
{
    timer->stop();
    //更换按钮状态
    for(int i = 0; i < window_btn_count; i++)
    {
        if(index == i) {
            pic_array[i]->setMousePressFlag(true);
        }
        else {
            pic_array[i]->setMousePressFlag(false);
        }
    }
        if(index == 4) {
            start_button->show();
        }
        else {
            start_button->hide();
        }

    int current_pos_x = master_label->x();
    int dest_pos_x = -680 * index;
    if(current_pos_x > dest_pos_x) {
        while(current_pos_x > dest_pos_x)
        {
            master_label->move(current_pos_x-20, 0);
            current_pos_x = master_label->x();
            qApp->processEvents(QEventLoop::AllEvents);//防止界面冻结
        }
    }
    else if(current_pos_x < dest_pos_x) {
        while(current_pos_x < dest_pos_x)
        {
            master_label->move(current_pos_x+20, 0);
            current_pos_x = master_label->x();
            qApp->processEvents(QEventLoop::AllEvents);//防止界面冻结
        }
    }
    master_label->move(dest_pos_x, 0);
    current_index = index;
    timer->start();
}

void SliderShow::timerChangePosition() {
    if(current_index == page_count-1) {
        current_index = 0;
        pic_array[0]->setMousePressFlag(true);
        this->changeCurrentPage(current_index);
    }
    else {
        ++current_index;
        this->changeCurrentPage(current_index);
    }
}

void SliderShow::start_run_program() {
    this->accept();
}
