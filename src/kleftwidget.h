/*
 * Copyright (C) 2021 KylinSoft Co., Ltd.
 *
 * Authors:
 *  Yang Min yangmin@kylinos.cn
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef KLEFTWIDGET_H
#define KLEFTWIDGET_H

#include <QWidget>
#include <QList>
#include <QMap>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QButtonGroup>
#include <qgsettings.h>

#include "kleftsideitem.h"

class KLeftWidget : public QWidget
{
    Q_OBJECT
public:
    explicit KLeftWidget(QWidget *parent = nullptr);
    virtual ~KLeftWidget();

    void initUI();
    void initConnections();
    int addItems(QString strText, QString strTip, QString strIcon);
    int currentIndex();

public slots:
    void onSwichPanel(int nIndex);

signals:
    void switchPage(int nIndex);

private:
    void initThemeMode();

private:
    QButtonGroup *m_buttonGroup = nullptr;
    QLabel  *m_labelTitle = nullptr;
    QLabel  *m_labelTitleIcon = nullptr;

    QVBoxLayout *m_mainLayout = nullptr;
    QHBoxLayout *m_titleLayout = nullptr;
    QVBoxLayout *m_itemsLayout = nullptr;
    QSpacerItem *m_verticalSpacer = nullptr;

    QGSettings *qtSettings = nullptr;
};

#endif // KLEFTWIDGET_H
