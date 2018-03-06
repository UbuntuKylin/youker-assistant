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

#ifndef SETTINGMODULEPAGE_H
#define SETTINGMODULEPAGE_H

#include <QDebug>
#include <QFile>
#include <QFrame>

class SettingModulePage : public QFrame
{
    Q_OBJECT

public:
    SettingModulePage(QWidget *parent = 0)
        :QFrame(parent)
    {

    }

    virtual QString settingModuleName() = 0;
    virtual void initSettingData() = 0;
};

#endif // SETTINGMODULEPAGE_H
