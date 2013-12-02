/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
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
import "common" as Common

Item {
    id: clearmode
    width: parent.width
    height: 475
    Image {     //背景图片
        id: background
        anchors.fill: parent
        source: "../img/skin/bg-middle-tab.png"
    }
    Common.Tabs {
        id: tabs
        width: parent.width; height: 435

//        Common.TabPage {
//            title: qsTr("A key to clean up")//一键清理
//            anchors.fill: parent
//            FastclearModel {
//                id: fastitem
//            }
//        }
        Common.TabPage {
            title:qsTr("Deb cache")//包管理缓存
            anchors.fill: parent
            AptCruft{
               id: aptitem
           }
        }
        Common.TabPage {
            title:qsTr("Software cache")//软件中心缓存
            anchors.fill: parent
            SoftwareCruft {
                id: softwareitem
            }

        }
        Common.TabPage {
            title:qsTr("Historical records")//历史记录
            anchors.fill: parent
            BrowserHistroy {
                id: historyitem
            }
        }
        Common.TabPage {
            title:qsTr("Cookies")//Cookies
            anchors.fill: parent
            BrowserCookies {
                id: cookiesitem
            }
        }
        Common.TabPage {
            title:qsTr("Deb uninstalled")//包卸载
            anchors.fill: parent
            PackageModel {
                id: packagemodel
            }
        }
        Common.TabPage{
            title:qsTr("Clean LargeFile ")//大文件清理
            anchors.fill: parent
            LargestFile {
                id: largestitem
            }
        }
    }
}
