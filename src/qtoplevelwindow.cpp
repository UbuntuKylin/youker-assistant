/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Components project on Qt Labs.
**
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions contained
** in the Technology Preview License Agreement accompanying this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
****************************************************************************/

#include "qtoplevelwindow.h"

#include <QDesktopWidget>

QTopLevelWindow::QTopLevelWindow()
    : QMainWindow(), _view(new QDeclarativeView), _positionIsDefined(false) {
    setVisible(false);
    // Ensure that we have a default size, otherwise an empty window statement will
    // result in no window
//    resize(QSize(100, 100));
    _view->setBackgroundBrush(palette().window());
    setCentralWidget(_view);
}

QTopLevelWindow::~QTopLevelWindow()
{
    foreach(QTopLevelWindow* child, findChildren<QTopLevelWindow*>())
        child->setParent(0);
    //we need this to break the parental loop of QWindowItem and QTopLevelWindow
    _view->scene()->setParent(0);
}

void QTopLevelWindow::registerChildWindow(QTopLevelWindow* child)
{
    child->setParent(this);
}

void QTopLevelWindow::hideChildWindows()
{
    foreach(QTopLevelWindow* child, findChildren<QTopLevelWindow*>()) {
        child->hide();
    }
}

void QTopLevelWindow::initPosition()
{
    if (!_positionIsDefined)
        center();
    foreach(QTopLevelWindow* child, findChildren<QTopLevelWindow*>()) {
        child->initPosition();
    }
}

void QTopLevelWindow::center()
{
    QPoint parentCenter;
    if (parentWidget())
        parentCenter = parentWidget()->geometry().center();
    else
        parentCenter = QDesktopWidget().screenGeometry().center();
    QRect thisGeometry = geometry();
    thisGeometry.moveCenter(parentCenter);
    setGeometry(thisGeometry);
}

void QTopLevelWindow::move(int x, int y)
{
    qDebug("a %d, %d", x, y);
    move(QPoint(x,y));
}

void QTopLevelWindow::move(const QPoint &point)
{
    _positionIsDefined = true;
    QMainWindow::move(point);
}

void QTopLevelWindow::setWindowFlags(Qt::WindowFlags type)
{
    QWidget::setWindowFlags(type | Qt::Window);
}

bool QTopLevelWindow::event(QEvent *event) {
    switch (event->type()) {
        case QEvent::WindowStateChange:
            emit windowStateChanged();
            break;
        case QEvent::Show:
            emit visibilityChanged();
            break;
        case QEvent::Hide:
            hideChildWindows();
            emit visibilityChanged();
            break;
        case QEvent::Resize: {
            const QResizeEvent *resize = static_cast<const QResizeEvent *>(event);
            emit sizeChanged(resize->size());
            break;
        }
        default: break;
    }
    return QMainWindow::event(event);
}
