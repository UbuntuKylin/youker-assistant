/*
 * Copyright (C) 2013 ~ 2015 National University of Defense Technology(NUDT) & Kylin Ltd.
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

#include "shredmanager.h"
#include <QApplication>
#include <QDesktopWidget>

//ShredManager::ShredManager(QObject *parent)
//:QObject(parent), shred_dialog(this)
//{

//}
ShredManager::ShredManager(QObject *parent)
    : QObject(parent)
{
    shred_dialog = new ShredDialog;
}

ShredManager::~ShredManager()
{
    if (shred_dialog) {
        delete shred_dialog;
        shred_dialog = nullptr;
    }
}

QString ShredManager::getGuid()
{
    return "UBUNTU-KYLIN-SHRED";
}

 QString ShredManager::getName()
{
    return tr("Shred Manager");
}

QString ShredManager::getDescribe()
{
    return tr("Delete files makes it unable to recover");//彻底删除文件使其无法恢复
}

QString ShredManager::getPicture()
{
    return "shredder.png";
}

void  ShredManager::doAction()
{
//    int windowWidth = QApplication::desktop()->width();
//    int windowHeight = QApplication::desktop()->height();
//    shred_dialog->resetSkin();
//    shred_dialog->move((windowWidth - 500) / 2,(windowHeight - 471) / 2);
    shred_dialog->show();
    shred_dialog->raise();
}

QWidget *ShredManager::centralWidget()
{
    return shred_dialog;
}

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
Q_EXPORT_PLUGIN2(ShredManager, ShredManager)
#endif
