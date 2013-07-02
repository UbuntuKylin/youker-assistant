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
import RegisterMyType 0.1
import QtDesktop 0.1
import "common" as Common

Item {
    id: screen; width: parent.width; height: 420
//    frame:false
    property Dispatcher dis: mydispather
    property bool inListView : false

    Rectangle {
        id: background
        anchors.fill: parent; color: "white"
        Item {
            id: views
            width: parent.width
            anchors.top: parent.top
            anchors.topMargin: titleBar.height + 45
            anchors.bottom: toolBar.top
            ListModel {
                id: clearModel
                ListElement {
                    title: "清理垃圾"
                    picture: "../img/icons/user.png"
                    detailstr: "清理系统垃圾，让系统运行跟流畅"
                }
                ListElement {
                    title: "清理痕迹"
                    picture: "../img/icons/at.png"
                    detailstr: "清理使用计算机时留下的各种痕迹，保护个人隐私"
                }
                ListElement {
                    title: "清理插件"
                    picture: "../img/icons/pen.png"
                    detailstr: "清理电脑日常使用中下载的插件，提高系统性能"
                }
            }
//            ListModel {
//                id: scanModel
//                ListElement {
//                    title: "清理垃圾scan"
//                    picture: "../img/icons/user.png"
//                    detailstr: "清理系统垃圾，让系统运行跟流畅"
//                }
//                ListElement {
//                    title: "清理痕迹scan"
//                    picture: "../img/icons/at.png"
//                    detailstr: "清理使用计算机时留下的各种痕迹，保护个人隐私"
//                }
//                ListElement {
//                    title: "清理注册表scan"
//                    picture: "../img/icons/pen.png"
//                    detailstr: "清理电脑日常使用中产生的无用注册表项，提高系统性能"
//                }
//            }

            //默认情况下显示这个ListView:垃圾清理显示内容
            ListView {
                id: listView
                height: parent.height //- titlebar.height
                width: parent.width
                model: clearModel
//                delegate: RotateDelegate {}
                delegate: SettingsDelegate {}
                cacheBuffer: 1000
            }

            //当screen.inListView == true时，显示这个listview
//            ListView {
//                id: scanlistView
//                height: parent.height - titlebar.height
//                width: parent.width
//                x: -(parent.width * 1.5)
//                model: scanModel
//                delegate: RotateDelegate {}
//                cacheBuffer: 1000
//            }


            //页面变化，当screen.inListView == true时，用scanlistView替换listView页面
//            states: State {
//                name: "ListView"; when: screen.inListView == true
//                PropertyChanges { target: scanlistView; x: 0 }
//                PropertyChanges { target: listView; x: -(parent.width * 1.5) }
//            }

//            //动画效果
//            transitions: Transition {
//                NumberAnimation { properties: "x"; duration: 500; easing.type: Easing.InOutQuad }
//            }

//            Common.RotateDetails { id: rotateDetails; width: parent.width; anchors.left: views.right; height: parent.height }

//            Item { id: foreground; anchors.fill: parent }
        }

        //垃圾清理自定义标题栏
//        Common.MyTitleBar {
//            id: titleBar; width: parent.width; height: 45; opacity: 0.9}

        //工具栏
        Common.ToolBar {
            id: toolBar
            visible: false
            height: 40; anchors.bottom: parent.bottom; width: parent.width; opacity: 0.9
            button1Label: qsTr("无效")
            button2Label: qsTr("页面切换测试")
            onButton1Clicked: {

            }
            onButton2Clicked: {
                if (screen.inListView == true) screen.inListView = false; else screen.inListView = true
            }
        }

//        states: State {
//            name: "DetailedView"
//            PropertyChanges { target: views; x: -parent.width }
//            PropertyChanges { target: toolBar; button1Label: qsTr("开始翻转") }
//            PropertyChanges {
//                target: toolBar
//                onButton1Clicked: if (rotateDetails.state=='') rotateDetails.state='Back'; else rotateDetails.state=''
//            }
//            PropertyChanges { target: toolBar; button2Label: qsTr("返回列表") }
//            PropertyChanges { target: toolBar; onButton2Clicked: rotateDetails.closed() }
//        }

//        transitions: Transition {
//            NumberAnimation { properties: "x"; duration: 500; easing.type: Easing.InOutQuad }
//        }
    }
}



//Rectangle {
//    width: parent.width
//    height: 460
//    property Dispatcher dis: mydispather
//    Item {

//        Column {
//            anchors.fill: parent
//            //---------------------Unity设置start---------------------
////            Common.SetTitle {
////                id: unity_title
////            }

//            Row {
//                Image {
//                    id: refreshArrow0
//                    source: "../img/icons/settings.png"
//                    Behavior on rotation { NumberAnimation { duration: 200 } }
//                }
//                Text {
//                    id: text0
////                    x: 30
////                    y: 11
//                    width: 69
//                    height: 20
//                    text: qsTr("Unity")
//                    font.bold: true
//                    font.pointSize: 13
//                    font.pixelSize: 12
//                }
//            }
//            Row {
//                anchors.left: parent.left
//                anchors.leftMargin: 3
//                spacing: 25
//                SetBtn {iconName: "homepage.png"; method: "Launcher"; text: "launcher"}
//                SetBtn {iconName: "clearrubbish.png"; method: "Search"; text: "search"}
//                SetBtn {iconName: "optimalacceleration.png"; method: "Panel"; text: "panel"}
//                SetBtn {iconName: "searchtrojan.png"; method: "Switcher"; text: "switcher"}
//                SetBtn {iconName: "computerclinic.png"; method: "WebApps"; text: "webapps"}
//                SetBtn {iconName: "fixbug.png"; method: "Additonal_uinty"; text: "additonal_uinty"}
//            }
//            //---------------------Unity设置end---------------------


//            //---------------------窗体设置start---------------------
//            Row {
//                Image {
//                    id: refreshArrow1
//                    source: "../img/icons/about.png"
//                    Behavior on rotation { NumberAnimation { duration: 200 } }
//                }
//                Text {
//                    id: text1
//                    width: 69
//                    height: 20
//                    text: qsTr("Window Manager")
//                    font.bold: true
//                    font.pointSize: 13
//                    font.pixelSize: 12
//                }
//            }
//            Row {
//                anchors.left: parent.left
//                anchors.leftMargin: 3
//                spacing: 25
//                SetBtn {iconName: "homepage.png"; method: "General"; text: "general"}
//                SetBtn {iconName: "clearrubbish.png"; method: "WorkspaceSettings"; text: "workspacesettings"}
//                SetBtn {iconName: "optimalacceleration.png"; method: "WindowSpread"; text: "windowspread"}
//                SetBtn {iconName: "searchtrojan.png"; method: "WindowSnapping"; text: "windowsnapping"}
//                SetBtn {iconName: "computerclinic.png"; method: "Hotcorners"; text: "hotcorners"}
//                SetBtn {iconName: "fixbug.png"; method: "Additional_window"; text: "Additional_window"}
//            }
//            //---------------------窗体设置end---------------------

//            //---------------------皮肤设置start---------------------
//            Row {
//                Image {
//                    id: refreshArrow2
//                    source: "../img/icons/history.png"
//                    Behavior on rotation { NumberAnimation { duration: 200 } }
//                }
//                Text {
//                    id: text2
//                    width: 69
//                    height: 20
//                    text: qsTr("Apprearance")
//                    font.bold: true
//                    font.pointSize: 13
//                    font.pixelSize: 12
//                }
//            }
//            Row {
//                anchors.left: parent.left
//                anchors.leftMargin: 3
//                spacing: 25
//                SetBtn {iconName: "homepage.png"; method: "Theme"; text: "homepage"}
//                SetBtn {iconName: "clearrubbish.png"; method: "Icons"; text: "clearrubbish"}
//                SetBtn {iconName: "optimalacceleration.png"; method: "Cursor"}
//                SetBtn {iconName: "searchtrojan.png"; method: "Font"; text: "searchtrojan"}
//                SetBtn {iconName: "computerclinic.png"; method: "WindowControls"; text: "computerclinic"}
//            }
//            //---------------------皮肤设置end---------------------


//            //---------------------系统设置start---------------------
//            Row {
//                Image {
//                    id: refreshArrow3
//                    source: "../img/icons/about.png"
//                    Behavior on rotation { NumberAnimation { duration: 200 } }
//                }
//                Text {
//                    id: text3
//                    width: 69
//                    height: 20
//                    text: qsTr("System")
//                    font.bold: true
//                    font.pointSize: 13
//                    font.pixelSize: 12
//                }
//            }
//            Row {
//                anchors.left: parent.left
//                anchors.leftMargin: 3
//                spacing: 25
//                SetBtn {iconName: "homepage.png"; method: "DesktopIcons"; text: "desktopIcons"}
//                SetBtn {iconName: "clearrubbish.png"; method: "Security"; text: "security"}
//                SetBtn {iconName: "optimalacceleration.png"; method: "Scrolling"; text: "scrolling"}
//            }
//            //---------------------系统设置end---------------------
//        }//Column

//    }//Item

//}//Rectangle
