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
#include "messengerproxy.h"

QPoint widgetPosition;//界面中心位置的全局变量

HomePage::HomePage(QWidget *parent)
    :QWidget(parent)
//    :QStackedWidget(parent)
{
    tray = new Tray();
    connect(tray, SIGNAL(showOrHideQmlSignal()), this, SLOT(showOrHideMainPage()));
//    connect(MessengerProxy::get_instance_object(), SIGNAL(mainHide()), this, SLOT(hide()));
//    connect(MessengerProxy::get_instance_object(), SIGNAL(showMin()), this, SLOT(showMinimized()));
}

HomePage::~HomePage()
{
    delete this->view;
    if (tray) {
        delete tray;
    }
}

inline bool isRunningInstalled() {
    static bool installed = (QCoreApplication::applicationDirPath() ==
                             QDir(("/usr/bin")).canonicalPath());
    return installed;
}

inline QString getAppDirectory() {
    if (isRunningInstalled()) {
        return QString("/usr/share/youker-assistant/qml/");
    } else {
        return QString(QCoreApplication::applicationDirPath() + "/../qml/");
    }
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
    this->setStyleSheet("background:transparent");
    this->setWindowTitle("Youker Assistant");
    this->setAutoFillBackground(false);
    this->setWindowOpacity(1);
//    this->setAttribute(Qt::WA_TranslucentBackground);
//    this->setWindowFlags(Qt::FramelessWindowHint);
    //设置窗体标题栏隐藏并设置位于顶层
     this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    //如果不设置Qt::WindowStaysOnTopHint，则存在问题，那就是界面能够拖动到任务栏之下
     //可获取鼠标跟踪效果
     setMouseTracking(true);

    this->view = new QDeclarativeView(this);
    this->view->engine()->setBaseUrl(QUrl::fromLocalFile(getAppDirectory()));
    this->view->setSource(QUrl::fromLocalFile("main.qml"));
    QObject::connect(this->view->engine(), SIGNAL(quit()), qApp, SLOT(quit()));
    this->hlayout = new QBoxLayout(QBoxLayout::TopToBottom, this->view);
    this->hlayout->setMargin(0);
    this->hlayout->setSpacing(0);

    this->topBar = new TopBar(this);
    connect(this->topBar, SIGNAL(readyShowMin()), this, SLOT(showMinimized()));
    connect(this->topBar, SIGNAL(readyHideWidget()), this, SLOT(hide()));

    this->tabBar = new TabBar(this);
    this->contentField = new ContentField(this);
    this->bottomBar = new BottomBar(this);
    this->hlayout->addWidget(this->topBar,0, Qt::AlignTop);
    this->hlayout->addWidget(this->tabBar);
////    this->hlayout->addWidget(this->mainWidget,0, Qt::AlignBottom);
    this->hlayout->addWidget(this->contentField);
    this->hlayout->addWidget(this->bottomBar,0, Qt::AlignBottom);
    setLayout(this->hlayout);

    QObject::connect(this->tabBar, SIGNAL(navigate(int)), this->contentField, SLOT(DoNavigate(int)));

    this->resize(850, 600);
    int windowWidth = QApplication::desktop()->width();
    int windowHeight = QApplication::desktop()->height();
    this->move((windowWidth - this->width()) / 2,(windowHeight - this->height()) / 2);
//    qDebug() << this->pos();
//    this->resize(860, 610);
}
