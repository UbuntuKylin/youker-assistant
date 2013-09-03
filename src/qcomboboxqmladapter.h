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

#ifndef QCOMBOBOXQMLADAPTER_H
#define QCOMBOBOXQMLADAPTER_H

#include
#include
#include
#include

//#include "entrylistmodel.h"

class CustomComboBox : public QComboBox {
    Q_OBJECT
public:
    explicit CustomComboBox(QWidget *parent = 0) : QComboBox(parent){}

protected:
    void focusInEvent(QFocusEvent *event){ QComboBox::focusInEvent(event); emit focusIn(); }
    void focusOutEvent(QFocusEvent *event){ QComboBox::focusOutEvent(event); emit focusOut(); }

signals:
    void focusIn();
    void focusOut();
};

class QComboBoxQmlAdapter : public QGraphicsProxyWidget
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
public:
    explicit QComboBoxQmlAdapter(QGraphicsItem *parent = 0);
    ~QComboBoxQmlAdapter();

    void setText(const QString text) { m_comboBox->setEditText(text); }
    QString text() { return m_comboBox->currentText(); }

    Q_INVOKABLE void setItems(const QStringList &items);

signals:
    void focusIn();
    void focusOut();

    void textChanged(QString text);

private:
    CustomComboBox *m_comboBox;

};
#endif // QCOMBOBOXQMLADAPTER_H
