/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef QTMLMENU_H
#define QTMLMENU_H

#include <QtGui/qmenu.h>
#include <QtDeclarative/qdeclarative.h>
#include <QtDeclarative/QDeclarativeListProperty>
#include <QtCore/qabstractitemmodel.h>
#include <QtCore/QVariant>
#include "qtmenuitem.h"

class QtMenu : public QtMenuBase
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(QVariant model READ model WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(int selectedIndex READ selectedIndex WRITE setSelectedIndex NOTIFY selectedIndexChanged)
    Q_PROPERTY(int hoveredIndex READ hoveredIndex WRITE setHoveredIndex NOTIFY hoveredIndexChanged)
    Q_PROPERTY(QDeclarativeListProperty<QtMenuBase> menuItems READ menuItems)
    Q_CLASSINFO("DefaultProperty", "menuItems")
public:
    QtMenu(QObject *parent = 0);
    virtual ~QtMenu();

    void setText(const QString &text);
    QString text() const;

    int selectedIndex() const { return m_selectedIndex; }
    void setSelectedIndex(int index);
    int hoveredIndex() const { return m_highlightedIndex; }
    void setHoveredIndex(int index);

    QDeclarativeListProperty<QtMenuBase> menuItems();
    QMenu* qmenu() { return m_qmenu; }

    QAction* action();

    Q_INVOKABLE int minimumWidth() const { return m_qmenu->minimumWidth(); }
    Q_INVOKABLE void setMinimumWidth(int w) { m_qmenu->setMinimumWidth(w); }
    Q_INVOKABLE void showPopup(qreal x, qreal y, int atActionIndex = -1);
    Q_INVOKABLE void hidePopup();
    Q_INVOKABLE void clearMenuItems();
    Q_INVOKABLE void addMenuItem(const QString &text);
    Q_INVOKABLE QString itemTextAt(int index) const;
    Q_INVOKABLE QString modelTextAt(int index) const;
    Q_INVOKABLE int modelCount() const;

    QVariant model() const { return m_model; }
    Q_INVOKABLE bool hasNativeModel() const { return m_hasNativeModel; }

public slots:
    void setModel(const QVariant &newModel);

public:
Q_SIGNALS:
    void menuClosed();
    void selectedIndexChanged();
    void hoveredIndexChanged();
    void modelChanged(const QVariant &newModel);
    void rebuldMenu();

private Q_SLOTS:
    void emitSelected();
    void emitHovered();

private:
    static void append_qmenuItem(QDeclarativeListProperty<QtMenuBase> *list, QtMenuBase *menuItem);

private:
    QWidget *dummy;
    QMenu *m_qmenu;
    QList<QtMenuBase *> m_qmenuItems;
    int m_selectedIndex;
    int m_highlightedIndex;
    bool m_hasNativeModel;
    QVariant m_model;
};

QML_DECLARE_TYPE(QtMenu)

#endif // QTMLMENU_H
