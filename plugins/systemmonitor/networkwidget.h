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

#ifndef NETWORKWIDGET_H
#define NETWORKWIDGET_H

#include <QWidget>
#include <QRadioButton>
#include <QImage>
#include <QLabel>
#include <QVBoxLayout>

class NetworkFlow;

class NetworkWidget : public QWidget
{
    Q_OBJECT

public:
    NetworkWidget(QWidget *parent = 0);
    ~NetworkWidget();

public slots:
    void onUpdateNetworkStatus(long recvTotalBytes, long sentTotalBytes, long recvRateKbs, long sentRateKbs);
    void setRadioButtonRowStatus();

private:
    QLabel *m_title = nullptr;
    NetworkFlow *m_networkFlow = nullptr;
    QVBoxLayout *m_widgetLayout = nullptr;
    QHBoxLayout *mainLayout = nullptr;
//    QRadioButton *math1_radio;
//    QRadioButton *math2_radio;
};

#endif // NETWORKWIDGET_H
