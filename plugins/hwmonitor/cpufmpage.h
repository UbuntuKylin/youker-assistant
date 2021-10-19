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

#ifndef CPUFMPAGE_H
#define CPUFMPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <qgsettings.h>

#include "cpufmsetwidget.h"

class CpuFMPage : public QWidget
{
    Q_OBJECT
public:
    explicit CpuFMPage(QWidget *parent = nullptr);
    virtual ~CpuFMPage();

    void initUI();
    void initConnections();
    void refreshInfo();

public slots:
    void onCpuFMChange(QString strModel, QString strCurFreq);
    void onUpdateInfo(unsigned uStatus, QString strInfoJson);
    void onUpdateCoreFreq(QString strFreq);

private:
    void initStyleTheme();

private:
    QVBoxLayout *m_layoutMain = nullptr;
    QHBoxLayout *m_layoutFreq = nullptr;
    QHBoxLayout *m_layoutSetting = nullptr;
    QHBoxLayout *m_layoutTips = nullptr;
    QVBoxLayout *m_layoutFreqRight = nullptr;

    CpuFMSetWidget *m_cpuFMSetWidget = nullptr;
    QLabel *m_iconFreq = nullptr;
    QLabel *m_labelFreqValue = nullptr;
    QLabel *m_labelFreq = nullptr;
    QLabel *m_labelTips = nullptr;

    QGSettings *m_styleSettings = nullptr;
};

#endif // CPUFMPAGE_H
