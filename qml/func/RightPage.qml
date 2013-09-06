/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  Kobe Lee    kobe24_lixiang@126.com
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

//右边栏
Rectangle {
    id: rightbar
    width: screen.width - 600; height: 460
    property SessionDispatcher dis1: sessiondispatcher

//推荐软件的三张图片
    property string image1: "../img/icons/irc.png"
    property string image2: "../img/icons/chromium.png"
    property string image3: "../img/icons/kugou.png"

//    property SystemDispatcher dis2: systemdispatcher
    ListModel {
        id: clearModel
        ListElement {
            icon: "../img/icons/checkscreen.png"
            name: "坏点检测"
            flag: "CheckScreen"
        }
        ListElement {
            icon: "../img/icons/iconbeauty.png"
            name: "桌面图标"
            flag: "DesktopiconSet"
        }
        ListElement {
            icon: "../img/icons/bootanimation.png"
            name: "开机动画"
            flag: "BootAnimation"
        }
        ListElement {
            icon: "../img/icons/systemsound.png"
            name: "系统声音"
            flag: "SoundEffects"
        }
        ListElement {
            icon: "../img/icons/mouse.png"
            name: "鼠标指针"
            flag: "MousePointer"
        }

        ListElement {
            icon: "../img/icons/touchpad.png"
            name: "触摸板"
            flag: "TouchpadSet"
        }
    }
    //背景
    Image {
        source: "../img/skin/bg-right.png"
        anchors.fill: parent
    }

    //-------------------

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
        SetBtn {iconName: "set.png"; setbtn_flag: "set"}
        SetBtn {iconName: "message.png"; setbtn_flag: "message"}
    }

    Item{
        id:software
        width: mage.width;height: mage.height
        anchors {
            top: parent.top
            topMargin: 160
            horizontalCenter: parent.horizontalCenter
        }
        Image {
            id: mage
            source: "../img/icons/kugou.png"
        }
        MouseArea{
            anchors.fill: parent
            onClicked:  {
                if(sudodispatcher.get_sudo_daemon_qt() == "SudoDaemon") {
                    sudodispatcher.bind_signals_after_dbus_start();
                    sudodispatcher.check_pkgs_status_qt(sudodispatcher.get_args());
                    pageStack.push(softwarerecommend);
                }
                else {
                    sudodispatcher.show_passwd_dialog();
                }

            }
        }
    }
//    Row{
//        anchors{
//            top:software.bottom
//            topMargin: 10
//            horizontalCenter: parent.horizontalCenter
//        }
//        spacing: 5
//        Common.Button{
//            id:button1
//            hoverimage: "radiobox.png"
//            onClicked: {
//                mage.source="../img/icons/kugou.png"
//            }
//        }
//        Common.Button{
//            id:button2
//            hoverimage: "radiobox.png"
//            onClicked: {
//                mage.source="../img/icons/kugou.png"
//            }
//        }
//        Common.Button{
//            id:button3
//            hoverimage: "radiobox.png"
//            onClicked: {
//                mage.source="../img/icons/kugou.png"
//            }
//        }
//    }

//    Text {
//        id: teamname
//        anchors {
//            top: setrow.bottom
//            topMargin: 30
//            horizontalCenter: parent.horizontalCenter
//        }
//        text: "UbuntuKylin Team"
////                wrapMode: Text.WordWrap
//        font.bold: true
//        font.pixelSize: 14
//        color: "#383838"
//    }
//    Text {
//        anchors {
//            top: teamname.bottom
//            topMargin: 10
//            horizontalCenter: parent.horizontalCenter
//        }
//        text: "优客助手"
////                wrapMode: Text.WordWrap
//        font.bold: true
//        font.pixelSize: 14
//        color: "#383838"
//    }

    //上下分割条
    Rectangle {id: splitbar1; x: 2; y: 270; width: parent.width; height: 1; color: "#b9c5cc" }
    Rectangle {id: splitbar2; x: 2; y: 272; width: parent.width; height: 1; color: "#fafcfe" }
    //-------------------


    Column {
        width: parent.width
        height: 200
        anchors {
            top: splitbar2.bottom
            topMargin: 5
            left: parent.left
            leftMargin: 5
        }
        Item {
            id: views
            width: parent.width
            height: parent.height
            GridView {
                id: gridView
                height: parent.height
                width: parent.width
                anchors.top: parent.top
//                    anchors.topMargin: titlebar.height + 45
                model: clearModel
                delegate: ToolsDelegate {}
                cellWidth: (parent.width-20)/3; cellHeight: cellWidth
                cacheBuffer: 1000
                focus: true
            }
        }
    }

    Row {
        id: versionrow
        spacing: 30
        anchors {
            bottom: parent.bottom
            bottomMargin: 10
            left: parent.left
            leftMargin: 20
        }

        Common.Label {
            id: helplabel
            text: "论坛求助"
            font.pixelSize: 12
            color: "#318d11"
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
            Image {
                id: btnImg1
                anchors.fill: helplabel
                source: ""
            }
        }
        Common.Label {
            id: versionlabel
            text: "新版本特性"
            font.pixelSize: 12
            color: "#318d11"
            MouseArea {
                  anchors.fill: versionlabel
                  hoverEnabled: true
                  onEntered: btnImg2.source = "../img/toolWidget/menu_hover.png"
                  onPressed: btnImg2.source = "../img/toolWidget/menu_press.png"
                  //要判断松开是鼠标位置
                  onReleased: btnImg2.source = "../img/toolWidget/menu_hover.png"
                  onExited: btnImg2.source = ""

                  onClicked: {
                      sessiondispatcher.send_message_dialog();
                  }
            }
            Image {
                id: btnImg2
                anchors.fill: versionlabel
                source: ""
            }

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
