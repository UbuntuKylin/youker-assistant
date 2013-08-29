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

#ifndef QTSPLITTERBASE_H
#define QTSPLITTERBASE_H

#include <QtDeclarative>


class QtSplitterAttached : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal minimumWidth READ minimumWidth WRITE setMinimumWidth NOTIFY minimumWidthChanged)
    Q_PROPERTY(qreal maximumWidth READ maximumWidth WRITE setMaximumWidth NOTIFY maximumWidthChanged)
    Q_PROPERTY(qreal minimumHeight READ minimumHeight WRITE setMinimumHeight NOTIFY minimumHeightChanged)
    Q_PROPERTY(qreal maximumHeight READ maximumHeight WRITE setMaximumHeight NOTIFY maximumHeightChanged)
    Q_PROPERTY(qreal percentageSize READ percentageSize WRITE setPercentageSize NOTIFY percentageWidthSize)
    Q_PROPERTY(bool expanding READ expanding WRITE setExpanding NOTIFY expandingChanged)
    Q_PROPERTY(int itemIndex READ itemIndex WRITE setItemIndex NOTIFY itemIndexChanged)

public:
    explicit QtSplitterAttached(QObject *object);

    qreal minimumWidth() const { return m_minimumWidth; }
    void setMinimumWidth(qreal width);

    qreal maximumWidth() const { return m_maximumWidth; }
    void setMaximumWidth(qreal width);

    qreal minimumHeight() const { return m_minimumHeight; }
    void setMinimumHeight(qreal width);

    qreal maximumHeight() const { return m_maximumHeight; }
    void setMaximumHeight(qreal width);

    bool expanding() const { return m_expanding; }
    void setExpanding(bool expanding);

    qreal percentageSize() const { return m_percentageSize; }

    int itemIndex() const { return m_itemIndex; }

    void setPercentageSize(qreal arg) { m_percentageSize = arg; }
    void setItemIndex(int arg) {
        if (m_itemIndex != arg) {
            m_itemIndex = arg;
            emit itemIndexChanged(arg);
        }
    }

signals:
    void minimumWidthChanged(qreal arg);
    void maximumWidthChanged(qreal arg);
    void minimumHeightChanged(qreal arg);
    void maximumHeightChanged(qreal arg);
    void expandingChanged(bool arg);
    void percentageWidthSize(qreal arg);
    void itemIndexChanged(int arg);

private:
    qreal m_minimumWidth;
    qreal m_maximumWidth;
    qreal m_minimumHeight;
    qreal m_maximumHeight;
    qreal m_percentageSize;
    int m_itemIndex;
    bool m_expanding;

    friend class QtSplitterBase;
};


class QtSplitterBase : public QDeclarativeItem
{
    Q_OBJECT
public:
    explicit QtSplitterBase(QDeclarativeItem *parent = 0);
    ~QtSplitterBase() {}

    static QtSplitterAttached *qmlAttachedProperties(QObject *object);
};

QML_DECLARE_TYPEINFO(QtSplitterBase, QML_HAS_ATTACHED_PROPERTIES)

#endif // QTSPLITTERBASE_H
