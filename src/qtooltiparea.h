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

#ifndef QTOOLTIPAREA_H
#define QTOOLTIPAREA_H

#include <QDeclarativeItem>
#include <QTimer>

class QTooltipArea : public QDeclarativeItem
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(bool containsMouse READ containsMouse NOTIFY containsMouseChanged)

public:
    QTooltipArea(QDeclarativeItem *parent = 0);
    void setText(const QString &t);
    QString text() const {return m_text;}
    bool containsMouse() const {return m_containsMouse;}
    void showToolTip(const QString &str) const;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

public slots:
    void timeout();

signals:
    void textChanged();
    void containsMouseChanged();

private:

    QTimer m_tiptimer;
    QString m_text;
    bool m_containsMouse;
};

#endif // QTOOLTIPAREA_H
