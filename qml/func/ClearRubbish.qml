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
import SessionType 0.1
import SystemType 0.1
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
        Common.Tab {
            title: qsTr("一键清理")
            anchors.fill: parent
            FastclearModel {
                id: fastitem
            }
        }
        Common.TabPage {
            title:qsTr("包管理缓存")
            anchors.fill: parent
            AptCruft{
               id: aptitem
           }
        }
        Common.TabPage {
            title:qsTr("软件中心缓存")
            anchors.fill: parent
            SoftwareCruft {
                id: softwareitem
            }

        }
        Common.TabPage {
            title:qsTr("历史记录")
            anchors.fill: parent
            BrowserHistroy {
                id: historyitem
            }
        }
        Common.TabPage {
            title:qsTr("Cookies")
            anchors.fill: parent
            BrowserCookies {
                id: cookiesitem
            }
        }
        Common.TabPage {
            title:qsTr("包卸载")
            anchors.fill: parent
            PackageModel {
                id: packagemodel
            }
        }
        Common.TabPage{
            title:qsTr("文件排序")
            anchors.fill: parent
            LargestFile {
                id: largestitem
            }
        }
    }
}



//Item {
//    id: clearmode
//    width: parent.width
//    height: 475
//    property SessionDispatcher dis1: sessiondispatcher
//    property SystemDispatcher dis2: systemdispatcher
//    ListModel {
//        id: choices
//        ListElement { text: "kobe333" }
//        ListElement { text: "lixiang" }
//        ListElement { text: "ps" }
//        ListElement { text: "baby" }
//    }

//    Common.TabFrame {
//        id:frame
//        //position decides the tabBar's location ,when is "South", the tabBar on Sourth, and when is "North", the tabBar on North
//        position: "North"
//        width: parent.width
//        height: parent.height
//        onCurrentChanged: {}

//        Common.Tab {
//            title: qsTr("一键清理")
//            contentMargin: 20
//            FastclearModel {
//                id: fastitem
//            }
//        }
//        Common.Tab {
//            title: qsTr("包管理缓存")
//            contentMargin: 20
//            AptCruft {
//                id: aptitem
//            }
//        }
//        Common.Tab {

//            title: qsTr("软件中心缓存")
//            contentMargin: 20
//            SoftwareCruft {
//                id: softwareitem
//            }
//        }
//        Common.Tab {
//            title: qsTr("历史记录")
//            contentMargin: 20
//            BrowserHistroy {
//                id: historyitem
//            }
//        }
//        Common.Tab {

//            title: qsTr("Cookies")
//            contentMargin: 20
//            BrowserCookies {
//                id: cookiesitem
//            }
//        }
//        Common.Tab {
//            title: qsTr("包卸载")
//            contentMargin: 20
//            PackageModel {
//                id: packagemodel
//            }
//        }
//        Common.Tab {
//            title: qsTr("文件排序")
//            contentMargin: 20
//            LargestFile {
//                id: largestitem
//            }
//        }
//    }
//}
