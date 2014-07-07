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

#include "homepage.h"

QPoint widgetPosition;//界面中心位置的全局变量

HomePage::HomePage(QWidget *parent)
    :QWidget(parent)
{
    this->setWindowTitle("Youker Assistant");
//    this->setAutoFillBackground(false);
    this->setWindowOpacity(1);
    this->setWindowFlags(Qt::FramelessWindowHint);

    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/skin/image/0_bg.png")));
    this->setPalette(palette);

    tray = new Tray();
    connect(tray, SIGNAL(showOrHideQmlSignal()), this, SLOT(showOrHideMainPage()));
}

HomePage::~HomePage()
{
    if (tray != NULL) {
        delete tray;
    }
}

void HomePage::showPage() {
    this->show();
    tray->show();
}

void HomePage::showOrHideMainPage() {
    if(this->isHidden()) {
        int windowWidth = QApplication::desktop()->width();
        int windowHeight = QApplication::desktop()->height();
        this->move((windowWidth - this->width()) / 2,(windowHeight - this->height()) / 2);
        this->show();
    }
    else {
        this->hide();
    }
}

void HomePage::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        dragPos = event->globalPos() - frameGeometry().topLeft();
        event->accept();
        update();
    }
}

void HomePage::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton )
    {
        move(event->globalPos() - dragPos);
        setWindowOpacity(0.9);
        update();
    }
    event->accept();
}

void HomePage::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        setWindowOpacity(1);
        update();
    }
    event->accept();
}

void HomePage::paintEvent(QPaintEvent *) {
    widgetPosition = this->pos();
}

void HomePage::setup() {
    this->hlayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    this->topBar = new TopBar(this);
    connect(this->topBar, SIGNAL(readyShowMin()), this, SLOT(showMinimized()));
    connect(this->topBar, SIGNAL(readyHideWidget()), this, SLOT(hide()));
    this->tabBar = new TabBar(this);
    this->contentField = new ContentField(this);
    this->bottomBar = new BottomBar(this);

    this->hlayout->addWidget(this->topBar,0, Qt::AlignTop);
    this->hlayout->addWidget(this->tabBar);
    this->hlayout->addWidget(this->contentField);
    this->hlayout->addWidget(this->bottomBar,0, Qt::AlignBottom);
    this->hlayout->setMargin(0);
    this->hlayout->setSpacing(0);
    setLayout(this->hlayout);
    QObject::connect(this->tabBar, SIGNAL(navigate(int)), this->contentField, SLOT(DoNavigate(int)));
    this->resize(850, 600);
    int windowWidth = QApplication::desktop()->width();
    int windowHeight = QApplication::desktop()->height();
    this->move((windowWidth - this->width()) / 2,(windowHeight - this->height()) / 2);
}
