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
    id: screen; width: parent.width; height: 460
//    property Dispatcher dis: mydispather
    property SessionDispatcher dis1: sessiondispatcher
    property SystemDispatcher dis2: systemdispatcher

    Rectangle {
        id: setting_widget
        anchors.fill: parent; color: "white"
        Item {
            id: views
            width: parent.width
            height: parent.height
            ListModel {
                id: clearModel
                ListElement {
                    icon: "../img/icons/themeset.png"
                    name: "主题"
                    flag: "theme"
                }
                ListElement {
                    icon: "../img/icons/systemsound.png"
                    name: "声音"
                    flag: "sound"
                }
                ListElement {
                    icon: "../img/icons/bootanimation.png"
                    name: "字体"
                    flag: "fonts"
                }
                ListElement {
                    icon: "../img/icons/systemreduce.png"
                    name: "触摸板"
                    flag: "touchpad"
                }
//                ListElement {
//                    icon: "../img/toolWidget/computerclinic.png"
//                    name: "登录设置"
//                    flag: "login"
//                }
                ListElement {
                    icon: "../img/icons/deepclear.png"
                    name: "Unity"
                    flag: "unity"
                }
                ListElement {
                    icon: "../img/icons/iconbeauty.png"
                    name: "桌面图标"
                    flag: "desktopicon"
                }
//                ListElement {
//                    icon: "../img/toolWidget/optimalacceleration.png"
//                    name: "壁纸"
//                    flag: "wallpaper"
//                }
                ListElement {
                    icon: "../img/icons/iconbeauty.png"
                    name: "窗口"
                    flag: "window"
                }
                ListElement {
                    icon: "../img/icons/iconbeauty.png"
                    name: "滑动条"
                    flag: "scrollbar"
                }
            }

            Common.Border {
                id: leftborder
//                width: 2
//                height: parent.height
            }
            Common.Border {
                id: roightborder
//                width: 2
//                height: parent.height
                anchors.right: parent.right
            }

            Label {
                id: label
                text: qsTr("系统美化 >")
                height: 30
                font.bold: true
                font.family: "Ubuntu"
                elide: Text.ElideRight
                font.pointSize: 20
                anchors {
                    top: parent.top
                    topMargin: 10
                    left: parent.left
                    leftMargin: 15
                }
            }

            GridView {
                id: gridView
                height: parent.height -label.height
                width: parent.width
                anchors {
                    top: label.bottom
                    topMargin: 10
                    left: parent.left
                    leftMargin: 15
                }

                model: clearModel
                delegate: SettingsDelegate {}
                cacheBuffer: 1000
                //竖列
//                cellWidth: (parent.width-2)/8; cellHeight: cellWidth
                //横列
                cellWidth: (parent.width-2)/6; cellHeight: cellWidth
                highlight: Rectangle { color: "lightsteelblue"; radius: 5 }//kobe:设置选中项深色块
                focus: true
            }

            SettingsDetails {
                id: settigsDetails
                width: parent.width
                anchors.left: views.right
                height: parent.height
            }
            Item { id: foreground; anchors.fill: parent }
        }

        //工具栏
        Common.ToolBar {
            id: toolBar
            visible: false
            height: 40; anchors.bottom: parent.bottom; width: parent.width; opacity: 0.9
            button1Label: qsTr("返回")
            button2Label: qsTr("确定")
            onButton1Clicked: {}
            onButton2Clicked: {}
        }

        states: State {
            name: "DetailedView"
            PropertyChanges { target: views; x: -parent.width }
            PropertyChanges { target: toolBar; visible: true }
        }

        transitions: Transition {
            NumberAnimation { properties: "x"; duration: 500; easing.type: Easing.InOutQuad }
        }
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
