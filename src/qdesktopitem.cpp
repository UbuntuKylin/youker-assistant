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
#include "qdesktopitem.h"


QDesktopItem::QDesktopItem(QObject* obj) : QObject(obj) {
    connect(&desktopWidget, SIGNAL(resized(int)), this, SIGNAL(screenGeometryChanged()));
    connect(&desktopWidget, SIGNAL(resized(int)), this, SIGNAL(availableGeometryChanged()));
    connect(&desktopWidget, SIGNAL(workAreaResized(int)), this, SIGNAL(availableGeometryChanged()));
    connect(&desktopWidget, SIGNAL(screenCountChanged(int)), this, SIGNAL(screenCountChanged()));
}

int QDesktopItem::screenCount() const
{
    return desktopWidget.screenCount();
}

QRect QDesktopItem::screenGeometry(int screen) const {
    return desktopWidget.screenGeometry(screen);
}

QRect QDesktopItem::availableGeometry(int screen) const {
    return desktopWidget.availableGeometry(screen);
}

int QDesktopItem::screenWidth() const
{
    return desktopWidget.screenGeometry().width();
}

int QDesktopItem::screenHeight() const
{
    return desktopWidget.screenGeometry().height();
}

int QDesktopItem::availableWidth() const
{
    return desktopWidget.availableGeometry().width();
}

int QDesktopItem::availableHeight() const
{
    return desktopWidget.availableGeometry().height();
}

QDesktopItem *QDesktopItem::qmlAttachedProperties(QObject *obj) {
    return new QDesktopItem(obj);
}
