/*
 * Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd.
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

import QtQuick 1.1
import "../common" as Common
import "../cleaner" as Cleaner

Item {
    id: clearmode
    width: 850; height: 476

    Common.Tabs {
        anchors.fill: parent

        Common.TabPage {
            title:qsTr("Cache Cleanup")//缓存管理
            anchors.fill: parent
            Cleaner.CacheModel {//pengshuang缓存
                id: aptitem
            }
        }
        Common.TabPage {
            title:qsTr("Uninstall Packages")//包卸载
            anchors.fill: parent
            Cleaner.PackageModel {
                id: packagemodel
            }
        }
        Common.TabPage {
            title:qsTr("Cookies Cleanup")//Cookies清除
            anchors.fill: parent
            Cleaner.CookiesModel {//pengshuang
                id: cookiesitem
            }
        }
        Common.TabPage {
            title:qsTr("Browser Cleanup")//浏览器清理
            anchors.fill: parent
            Cleaner.BrowserModel {
                id: browseritem
            }
        }
        Common.TabPage {
            title:qsTr("Trace Cleanup")//痕迹清理
            anchors.fill: parent
            Cleaner.TraceModel {
                id: historyitem
            }
        }
        Common.TabPage{
            title:qsTr("Find Large Files ")//查找大文件
            anchors.fill: parent
            Cleaner.FileModel {
                id: largestitem
            }
        }
    }
}
