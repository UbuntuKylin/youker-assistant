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

#include "startupwidget.h"
#include "startuptitlewidget.h"
#include "startuplistwidget.h"
#include "startupdata.h"

#include <QFileSystemWatcher>
#include <QLabel>
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QFile>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QApplication>
#include <QScreen>

QDataStream &operator<<(QDataStream &dataStream, const StartupDataPtr &object)
{
    auto ptr = object.data();
    auto ptrval = reinterpret_cast<qulonglong>(ptr);
    auto var = QVariant::fromValue(ptrval);
    dataStream << var;
    return dataStream;
}

QDataStream &operator>>(QDataStream &dataStream, StartupDataPtr &object)
{
    QVariant var;
    dataStream >> var;
    qulonglong ptrval = var.toULongLong();
    auto ptr = reinterpret_cast<StartupData *>(ptrval);
    object = StartupDataPtr(ptr);
    return dataStream;
}

StartupWidget::StartupWidget(QWidget *parent)
    : QFrame(parent)
    , mousePressed(false)
{
    qRegisterMetaType<StartupDataPtr>();
    qRegisterMetaTypeStreamOperators<StartupDataPtr>();
    qRegisterMetaType<StartupDataPtrList>();
    qRegisterMetaType<QList<StartupData>>();

//    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);//Attention: Qt::WindowCloseButtonHint make showMinimized() valid
    this->setAutoFillBackground(true);
    this->setMouseTracking(true);
    this->setWindowFlags(/*this->windowFlags() | */Qt::FramelessWindowHint  | Qt::WindowCloseButtonHint);//去掉边框
//    this->setAttribute(Qt::WA_TranslucentBackground);//背景透明
//    this->setAutoFillBackground(true);
//    this->setMouseTracking(true);

    this->setWindowTitle(tr("Kylin Startup Manager"));
    this->setWindowIcon(QIcon(":/model/res/plugin/startupmanager.png"));

    this->setFixedSize(500, 645);

    m_titleWidget = new StartupTitleWidget(this);
    m_titleWidget->setFixedSize(this->width() - 2, 39);

    m_layout = new QVBoxLayout();
    m_layout->setSpacing(0);
    m_layout->setMargin(0);
    m_layout->setContentsMargins(1,1,1,1);

    m_startupView = new StartupListWidget(this);
    m_layout->addWidget(m_titleWidget, 0, Qt::AlignTop);
    m_layout->addWidget(m_startupView, 0, Qt::AlignHCenter);

    this->setLayout(m_layout);

    this->moveCenter();



//#ifdef QT_NO_INOTIFY
//    qDebug() << "QT_NO_INOTIFY mode";
//#else
//    qDebug() << "NO QT_NO_INOTIFY";
//#endif

}

StartupWidget::~StartupWidget()
{
    if (m_titleWidget) {
        delete m_titleWidget;
        m_titleWidget = nullptr;
    }
    if (m_startupView) {
        delete m_startupView;
        m_startupView = nullptr;
    }
    delete m_layout;
}

void StartupWidget::moveCenter()
{
    QPoint pos = QCursor::pos();
    QRect primaryGeometry;
    for (QScreen *screen : qApp->screens()) {
        if (screen->geometry().contains(pos)) {
            primaryGeometry = screen->geometry();
        }
    }

    if (primaryGeometry.isEmpty()) {
        primaryGeometry = qApp->primaryScreen()->geometry();
    }

    this->move(primaryGeometry.x() + (primaryGeometry.width() - this->width())/2,
               primaryGeometry.y() + (primaryGeometry.height() - this->height())/2);
}

void StartupWidget::closeEvent(QCloseEvent *event)
{
    event->accept();
}

void StartupWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        this->dragPosition = event->globalPos() - frameGeometry().topLeft();
        this->mousePressed = true;
    }
    QFrame::mousePressEvent(event);
}

void StartupWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        this->mousePressed = false;
    }

    QFrame::mouseReleaseEvent(event);
}

void StartupWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (this->mousePressed) {
        move(event->globalPos() - this->dragPosition);
    }

    QFrame::mouseMoveEvent(event);
}

void StartupWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    //绘制圆角矩形
    painter.setPen(QPen(QColor("#0d87ca"), 0));//边框颜色 #3f96e4
    painter.setBrush(QColor("#e9eef0"));//背景色
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setOpacity(1);
    QRectF r(0 / 2.0, 0 / 2.0, width() - 0, height() - 0);//左边 上边 右边 下边
    painter.drawRoundedRect(r, 4, 4);

    //绘制背景色
//    QPainterPath path;
//    path.addRect(QRectF(rect()));
//    painter.setOpacity(1);
//    painter.fillPath(path, QColor("#ffffff"));

    QFrame::paintEvent(event);
}

