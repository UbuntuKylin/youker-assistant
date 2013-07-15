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
//import Ubuntu.Components 0.1
//import RegisterMyType 0.1
import SessionType 0.1
import SystemType 0.1
import QtDesktop 0.1
import "common" as Common

//右边栏
Rectangle {
    id: rightbar
    width: screen.width - 600; height: 460
    property SessionDispatcher dis1: sessiondispatcher
//    property SystemDispatcher dis2: systemdispatcher
    ListModel {
        id: clearModel
        ListElement {
            icon: "../img/icons/themeset.png"
            name: "主题"
            flag: "theme"
        }
        ListElement {
            icon: "../img/icons/iconbeauty.png"
            name: "桌面图标"
            flag: "desktopicon"
        }
        ListElement {
            icon: "../img/icons/bootanimation.png"
            name: "开机动画"
            flag: "touchpad"
//                    flag: "bootanimation"
        }
        ListElement {
            icon: "../img/icons/systemsound.png"
            name: "系统声音"
            flag: "sound"
        }
        ListElement {
            icon: "../img/icons/deepclear.png"
            name: "深度清理"
            flag: "fonts"
        }

        ListElement {
            icon: "../img/icons/systemreduce.png"
            name: "系统瘦身"
            flag: "unity"
        }

    }
    //背景
    Image {
        source: "../img/skin/rightbackground.png"
        anchors.fill: parent
    }

    //-------------------
    Column {
        anchors.fill: parent
        spacing: 10
        Image {
            id: logoimage
            anchors {
                top: parent.top
                topMargin: 20
                horizontalCenter: parent.horizontalCenter
            }
            source: "../img/icons/admin.png"
        }
        Row {
            id: setrow
            anchors {
                horizontalCenter: parent.horizontalCenter
                top: logoimage.bottom
                topMargin: 1
            }
            SetBtn {iconName: "set.png"}
            SetBtn {iconName: "message.png"}
        }
        Column {
            anchors {
                left: parent.left; leftMargin: 10
                top: setrow.bottom
            }
            Label {
                id: hareware
                text: qsTr("<h1>硬件信息</h1>")
                font.family: "楷体"
            }
            Text {
                text: qsTr("CPU:" + systemdispatcher.get_value("cpu") + "; "+ "内存:" + systemdispatcher.get_value("ram"))
            }
        }
    }
    //上下分割条
    Rectangle {id: splitbar; y: 270; width: parent.width; height: 1; color: "#cccccc" }
    //-------------------

    GridView {
        id: gridView
        height: parent.height
        width: parent.width
        anchors {
            top: splitbar.bottom
            topMargin: 5
            left: parent.left
            leftMargin: 5
        }
        model: clearModel
        delegate: ToolsDelegate {}
        cellWidth: (parent.width-2)/3; cellHeight: cellWidth
//                        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }//kobe:设置选中项深色块
        focus: true
    }

    Row {
        id: versionrow
        spacing: 40
        anchors {
            bottom: parent.bottom
            left: parent.left
            leftMargin: 20
        }

        Label {
            id: helplabel
            text: "论坛求助"
            color: "green"
            MouseArea {
                  anchors.fill: helplabel

                  hoverEnabled: true
                  onEntered: btnImg1.source = "../img/toolWidget/menu_hover.png"
                  onPressed: btnImg1.source = "../img/toolWidget/menu_press.png"
                  //要判断松开是鼠标位置
                  onReleased: btnImg1.source = "../img/toolWidget/menu_hover.png"
                  onExited: btnImg1.source = ""

                  onClicked: {
                      Qt.openUrlExternally("http://www.ubuntukylin.com/ukylin/forum.php")
                  }
            }
        }
        Label {
            id: versionlabel
            text: "新版本特性"
            color: "green"
            MouseArea {
                  anchors.fill: versionlabel
                  hoverEnabled: true
                  onEntered: btnImg2.source = "../img/toolWidget/menu_hover.png"
                  onPressed: btnImg2.source = "../img/toolWidget/menu_press.png"
                  //要判断松开是鼠标位置
                  onReleased: btnImg2.source = "../img/toolWidget/menu_hover.png"
                  onExited: btnImg2.source = ""

                  onClicked: {
                      sessiondispatcher.send_dialog_msg("modeless");
                  }
            }
        }

        Image {
            id: btnImg1
            anchors.fill: helplabel
            source: ""
        }
        Image {
            id: btnImg2
            anchors.fill: versionlabel
            source: ""
        }
    }

    //颜色渐变
//                    gradient: Gradient{
//                           GradientStop{
//                               position: 0.0
//                               color: "purple"
//                           }
//                           GradientStop{
//                               position: 1.0
//                               color: "white"
//                           }
//                       }
}//右边栏Rectangle
