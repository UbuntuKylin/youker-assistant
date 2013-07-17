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
    width: parent.width
    height: 475//460
//    property Dispatcher dis: mydispather
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
        position: "North"  //tabPositionGroup.checkedButton == r2 ? "South" : "North"
//        KeyNavigation.tab:button1
//        KeyNavigation.backtab: button2
        width: parent.width
        height: parent.height
        onCurrentChanged: {}

//        Tab {
//            title: qsTr("一键清理")
//            contentMargin: 20
//            FastclearModel {
//                id: screen
//            }

//        }
        Tab {
            id:mytab
            title: qsTr("清理垃圾")
            contentMargin: 20
            RubbishModel {
                id: rubbishitem
            }
        }
        Tab {
            title: qsTr("清理浏览器历史记录")
            contentMargin: 20
            BrowserHistroy {
                id: historyitem
            }
        }
        Tab {
            title: qsTr("清理浏览器Cookies")
            contentMargin: 20
            BrowserCookies {
                id: cookiesitem
            }
        }
        Tab {
            title: qsTr("清理插件")
            contentMargin: 20
            PluginModel {
                id: pluginmodel
            }

        }
//        Tab {
//            title: qsTr("测试隐藏框")
//            contentMargin: 20
//            Panel {
//                anchors.fill:parent
//            }
//        }
//        Tab {
//            title: qsTr("测试列表")
//            contentMargin: 20
//            ItemListModel {
////                id: pluginlist
//            }
//        }
//        Tab {
//            title: qsTr("测试旋转")
//            contentMargin: 20
//            RotateModel {
////                id: pluginlist
//            }
//        }
//        Tab {
//            title: qsTr("测试垃圾")
//            contentMargin: 20
//            RubbishModelTest {
////                id: pluginlist
//            }
//        }
//        Tab {
//            title: qsTr("测试痕迹")
//            contentMargin: 20
//            TracesModelTest {
////                id: pluginlist
//            }
//        }
//        Tab {
//            title: qsTr("测试插件")
//            contentMargin: 20
//            PluginModelTest {
////                id: pluginlist
//            }
//        }
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
//                    btn_flag: "plugins"
//                }


////                Common.TitleBar {
////                    id: titleBar
////                    width: parent.width
////                    height: 45
////                    opacity: 0.9
////                    btn_text: "开始扫描"
////                    title: "清理电脑中的插件"
////                    description:  "清理插件可以给系统和浏览器“减负”，减少干扰，提供系统和浏览器速度"
////                    btn_flag: "plugins"
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
