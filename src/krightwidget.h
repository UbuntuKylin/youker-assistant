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
#ifndef KRIGHTWIDGET_H
#define KRIGHTWIDGET_H

#include <QWidget>
#include <QToolButton>
#include <QMenu>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedWidget>

#include "kaaboutdialog.h"

class KRightWidget : public QWidget
{
    Q_OBJECT
public:
    explicit KRightWidget(QWidget *parent = nullptr);

    void initUI();
    void initConnections();
    void createAboutDialog();

    void addPanel(QWidget* pWidget, QString strName, QString strIcon);
    int currentIndex();

public slots:
    void onMinBtnClicked();
    void onMaxBtnClicked();
    void onCloseBtnClicked();
    void onSwichPanel(int nIndex);

signals:
    void maximizeWindow();
    void minimizeWindow();

protected:
    void paintEvent(QPaintEvent *) override;

private:
    QToolButton *m_btnOption = nullptr;
    QToolButton *m_btnMin = nullptr;
    QToolButton *m_btnClose = nullptr;
    QMenu       *m_mainMenu = nullptr;
    QStackedWidget *m_stackedWidget = nullptr;

    KAAboutDialog *m_aboutDlg = nullptr;

    QVBoxLayout *m_mainLayout = nullptr;
    QHBoxLayout *m_titleLayout = nullptr;
};

#endif // KRIGHTWIDGET_H
