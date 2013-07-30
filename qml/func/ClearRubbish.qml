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
//import RegisterMyType 0.1
import SessionType 0.1
import SystemType 0.1
import QtDesktop 0.1
import "common" as Common

Item {
    id: clearmode
    width: parent.width
    height: 475
    property SessionDispatcher dis1: sessiondispatcher
    property SystemDispatcher dis2: systemdispatcher
    ListModel {
        id: choices
        ListElement { text: "kobe333" }
        ListElement { text: "lixiang" }
        ListElement { text: "ps" }
        ListElement { text: "baby" }
    }

    TabFrame {
        id:frame
        //position decides the tabBar's location ,when is "South", the tabBar on Sourth, and when is "North", the tabBar on North
        position: "North"
        width: parent.width
        height: parent.height
        onCurrentChanged: {}
        Tab {
            title: qsTr("一键清理")
            contentMargin: 20
            FastclearModel {
                id: fastitem
            }
        }
        Tab {
            title: qsTr("包管理缓存")
            contentMargin: 20
            AptCruft {
                id: aptitem
            }
        }
        Tab {

            title: qsTr("软件中心缓存")
            contentMargin: 20
            SoftwareCruft {
                id: softwareitem
            }
        }
        Tab {
            title: qsTr("历史记录")
            contentMargin: 20
            BrowserHistroy {
                id: historyitem
            }
        }
        Tab {

            title: qsTr("Cookies")
            contentMargin: 20
            BrowserCookies {
                id: cookiesitem
            }
        }
        Tab {

            title: qsTr("包卸载")
            contentMargin: 20
            PackageModel {
                id: packagemodel
            }
        }
        Tab {
            title: qsTr("文件排序")
            contentMargin: 20
            LargestFile {
                id: largestitem
            }
        }
        Tab {
            title: qsTr("同名文件")
            contentMargin: 20
            SamenameFile {
                id: samenameitem
            }
        }
    }
}



//import QtQuick 2.0
//import Ubuntu.Components 0.1
//import Ubuntu.Components.ListItems 0.1 as ListItem
//import RegisterMyType 0.1
//import "common" as Common
//MainView {
//    width: parent.width
//    height: 460
//    property Dispatcher dis: mydispather
//    Tabs {
//        id: tabs
//        Tab {
//            id: fastTab
//            title: qsTr("一键清理")
//            iconSource: "../img/icons/kysoft.png"
//            page: Loader {
//                parent: fastTab
//                anchors.fill: parent

//                source: (tabs.selectedTab === fastTab) ? Qt.resolvedUrl("FastclearModel.qml") : ""
//            }
//        }

//        Tab {
//            id: externalTab
//            title: qsTr("清理垃圾")
//            iconSource: "../img/icons/kysoft.png"
//            page: Loader {
//                parent: externalTab
//                anchors.fill: parent
//                source: (tabs.selectedTab === externalTab) ? Qt.resolvedUrl("RubbishModel.qml") : ""
//            }
//        }

//        Tab {
//            id: pluginTab
//            title: qsTr("清理插件")
//            page: Page {

//                //垃圾清理自定义标题栏
//                Common.TitleBar {
//                    id: titleBar; width: parent.width; height: 45; opacity: 0.9
//                    btn_text: "开始扫描"
//                    title: "清理电脑中的插件"
//                    description:  "清理插件可以给系统和浏览器“减负”，减少干扰，提供系统和浏览器速度"
//                    btn_flag: "package"
//                }


////                Common.TitleBar {
////                    id: titleBar
////                    width: parent.width
////                    height: 45
////                    opacity: 0.9
////                    btn_text: "开始扫描"
////                    title: "清理电脑中的插件"
////                    description:  "清理插件可以给系统和浏览器“减负”，减少干扰，提供系统和浏览器速度"
////                    btn_flag: "package"
////                }

////                Rectangle {
////                    anchors.fill: parent
////                    Column {
////                        anchors {
////                            fill: parent
////                            top: parent.top
////                            topMargin: 10
////                            left: parent.left
////                            leftMargin: 30
////                        }
////                        Text {
////                            text: "清理电脑中的插件"
////                            font.pointSize: 11
////                            color: "black"
////                        }
////                        Text {
////                            text:  "清理插件可以给系统和浏览器“减负”，减少干扰，提供系统和浏览器速度"
////                            font.pointSize: 9
////                            color: "gray"
////                        }
////                    }
////                    Button {
////                        id: pluginBtn
////                        width: 90
////                        color: "gray"
////                        anchors {
////                            top: parent.top
////                            topMargin: 10
////                            left: parent.left
////                            leftMargin: 700
////                        }
////                        text: "开始扫描"
////                        onClicked: {
////                            //kobe: wait for adding function
////                        }
////                    }
////                }
//            }
//        }


//        Tab {
//            id: tracesTab
//            title: qsTr("清理痕迹")
//            iconSource: "../img/icons/kysoft.png"
//            page: Loader {
//                parent: tracesTab
//                anchors.fill: parent
////                (tabs.selectedTab == tracesTab) ? mydispather.set_str("tracesmodel") : ""
//                source: (tabs.selectedTab === tracesTab) ? Qt.resolvedUrl("TracesModel.qml") : ""
//            }

//        }
//    }
//}
