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
//import SystemType 0.1
import "../common" as Common
import "../bars" as Bars
Rectangle {
    id: launcherthemepage
    property bool on: true
    width: parent.width
    height: 475
    property string fontName: "Helvetica"
    property int fontSize: 12
    property color fontColor: "black"

    property SessionDispatcher dis: sessiondispatcher
    property int launcher_size: 24
    property string actiontitle: "启动器设置"
    property string actiontext: "用户可以根据需要设置启动器的自动隐藏功能和启动器上图标的显示尺寸；拖动滑动条，点击“确定”按钮完成大小设置。"


    //背景
    Image {
        source: "../../img/skin/bg-bottom-tab.png"
        anchors.fill: parent
    }

    Component.onCompleted: {
        launcherthemepage.launcher_size = slider.value;

        if (sessiondispatcher.get_launcher_autohide_qt())
            launcherswitcher.switchedOn = true;
        else
            launcherswitcher.switchedOn = false;

        if (sessiondispatcher.get_launcher_have_showdesktopicon_qt())
            showdesktopswitcher.switchedOn = true;
        else
            showdesktopswitcher.switchedOn = false;
    }

    Column {
        spacing: 10
        anchors.top: parent.top
        anchors.topMargin: 44
        anchors.left: parent.left
        anchors.leftMargin: 80
        Row {
            spacing: 50
            Text {
                 text: launcherthemepage.actiontitle
                 font.bold: true
                 font.pixelSize: 14
                 color: "#383838"
             }
            //status picture
            Image {
                id: statusImage
                visible: false
                source: "../../img/toolWidget/finish.png"
                fillMode: "PreserveAspectFit"
                smooth: true
                anchors.verticalCenter: parent.verticalCenter
            }
        }
         Text {
             text: launcherthemepage.actiontext
             font.pixelSize: 12
             color: "#7a7a7a"
         }
    }


    Row {
        id: settitle
        anchors{
            left: parent.left
            leftMargin: 40
            top: parent.top
            topMargin: 120

        }
        spacing: 5
        Text{
            text: "启动器设置"
            font.bold: true
            font.pixelSize: 12
            color: "#383838"
        }
        Rectangle{
            width:700
            height:1
            color:"#b9c5cc"
            anchors.verticalCenter: parent.verticalCenter
        }
    }


    Column {
        spacing: 20
        anchors{
            left: parent.left
            leftMargin: 60
            top: settitle.bottom
            topMargin: 10
        }
        Row {
            spacing: 20
            Common.Label {
                id: launcherlabel
                width: 150
                text: "启动器自动隐藏:"
                font.pixelSize: 12
                color: "#7a7a7a"
                anchors.verticalCenter: parent.verticalCenter
            }
            Common.Switch {
                id: launcherswitcher
//                width: launcherlabel.width
                onSwitched: {
                    if (launcherswitcher.switchedOn) {
                        sessiondispatcher.set_launcher_autohide_qt(true);
                    }
                    else if(!launcherswitcher.switchedOn) {
                        sessiondispatcher.set_launcher_autohide_qt(false);
                    }
                }
            }
        }

        Row {
            spacing: 20
            Common.Label {
                id: iconsizelabel
                width: 150
                text: "启动器上的图标大小:"
                font.pixelSize: 12
                color: "#7a7a7a"
                anchors.verticalCenter: parent.verticalCenter
            }
            Common.Slider {
                id: slider
                value: sessiondispatcher.get_launcher_icon_size_qt()
                width: 150
                maximumValue: 64
                minimumValue: 32
//                tickmarksEnabled: true
                stepSize: 1
                animated: true
            }

            Text {
                id: displaynum
                text: slider.value
                font.pixelSize: 12
                color: "#7a7a7a"
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Row {
            spacing: 20
            Common.Label {
                id: showdesktoplabel
                width: 150
                text: "桌面图标显示在启动器上:"
                font.pixelSize: 12
                color: "#7a7a7a"
                anchors.verticalCenter: parent.verticalCenter
            }
            Common.Switch {
                id: showdesktopswitcher
//                width: showdesktoplabel.width
                onSwitched: {
                    if (showdesktopswitcher.switchedOn) {
                        sessiondispatcher.set_launcher_have_showdesktopicon_qt(true);
                    }
                    else if(!showdesktopswitcher.switchedOn) {
                        sessiondispatcher.set_launcher_have_showdesktopicon_qt(false);
                    }
                }
            }
        }
    }//Column

    //顶层工具栏
    Bars.TopBar {
        id: topBar
        width: 28
        height: 26
        anchors.top: parent.top
        anchors.topMargin: 40
        anchors.left: parent.left
        anchors.leftMargin: 40
        opacity: 0.9
        onButtonClicked: {
            var num = sessiondispatcher.get_page_num();
            if (num == 0)
                pageStack.push(homepage)
            else if (num == 3)
                pageStack.push(systemset)
            else if (num == 4)
                pageStack.push(functioncollection)
        }
    }
    //底层工具栏
    Bars.ToolBar {
        id: toolBar
        height: 50; anchors.bottom: parent.bottom; width: parent.width; opacity: 0.9
        onQuitBtnClicked: {
            var num = sessiondispatcher.get_page_num();
            if (num == 0)
                pageStack.push(homepage)
            else if (num == 3)
                pageStack.push(systemset)
            else if (num == 4)
                pageStack.push(functioncollection)
        }
        onOkBtnClicked: {
            if (launcherthemepage.launcher_size != slider.value) {
                launcherthemepage.launcher_size = slider.value;
                sessiondispatcher.set_launcher_icon_size_qt(slider.value);
                statusImage.visible = true;
            }
        }

        Timer {
                 interval: 5000; running: true; repeat: true
                 onTriggered: statusImage.visible = false
             }
    }
}
