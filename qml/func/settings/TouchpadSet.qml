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
import "../common" as Common
import "../bars" as Bars

Rectangle {
    id: touchpadsetpage
    property bool on: true
    width: parent.width
    height: 475
    property string fontName: "Helvetica"
    property int fontSize: 12
    property color fontColor: "black"
    property string scrollbars_mode: ""
    property string touchscrolling_mode: ""
    property string actiontitle: qsTr("Touchpad settings")//触摸板设置
    property string actiontext: qsTr("Adjust touchpad settings, make the operation more convenient.")//通过调整您触摸板的相关设置，使操作更加便捷。
    //背景
    Image {
        source: "../../img/skin/bg-bottom-tab.png"
        anchors.fill: parent
    }

    Component.onCompleted: {
        touchpadsetpage.scrollbars_mode = sessiondispatcher.get_scrollbars_mode_qt();
        touchpadsetpage.touchscrolling_mode = sessiondispatcher.get_touchscrolling_mode_qt();//edge-scrolling
        if (sessiondispatcher.get_touchpad_enable_qt())
            touchpadswitcher.switchedOn = true;
        else
            touchpadswitcher.switchedOn = false;

        if (sessiondispatcher.get_touchscrolling_use_horizontal_qt())
            horizontalswitcher.switchedOn = true;
        else
            horizontalswitcher.switchedOn = false;
    }

    Column {
        spacing: 10
        anchors.top: parent.top
        anchors.topMargin: 44
        anchors.left: parent.left
        anchors.leftMargin: 80
        Text {
             text: touchpadsetpage.actiontitle
             font.bold: true
             font.pixelSize: 14
             color: "#383838"
         }
         Text {
             width: touchpadsetpage.width - 80 - 20
             text: touchpadsetpage.actiontext
             wrapMode: Text.WordWrap
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
            id: switchtitle
            text: qsTr("Switch setting")//开关设置
            font.bold: true
            font.pixelSize: 12
            color: "#383838"
        }
        //横线
        Rectangle{
            width: touchpadsetpage.width - switchtitle.width - 40 * 2
            height:1
            color:"#b9c5cc"
            anchors.verticalCenter: parent.verticalCenter
        }
    }


    Row {
        id: setcontext
        anchors{
            left: parent.left
            leftMargin: 60
            top: settitle.bottom
            topMargin: 10

        }
        spacing: 40
        Common.Label {
            width: 110
            text: qsTr("Enable/disable touchpad:")//启用/禁用触摸板:
            font.pixelSize: 12
            color: "#7a7a7a"
            anchors.verticalCenter: parent.verticalCenter
        }
        Common.Switch {
            id: touchpadswitcher
            width: 110
            onSwitched: {
                if (touchpadswitcher.switchedOn) {
                    sessiondispatcher.set_touchpad_enable_qt(true);
                }
                else if(!touchpadswitcher.switchedOn) {
                    sessiondispatcher.set_touchpad_enable_qt(false);
                }
            }
        }
    }

    Row {
        id: scrollrow
        anchors{
            left: parent.left
            leftMargin: 40
            top: setcontext.bottom
            topMargin: 50

        }
        spacing: 5
        Text{
            id: scrolltitle
            text: qsTr("Scrollbar settings")//滚动条设置
            font.bold: true
            font.pixelSize: 12
            color: "#383838"
        }
        //横线
        Rectangle{
            width: touchpadsetpage.width - scrolltitle.width - 40 * 2
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
            top: scrollrow.bottom
            topMargin: 10
        }

        Row {
            id: workmode
            spacing: 40
            Common.Label {
                width: 110
                text: qsTr("Scrollbar type:")//滚动条类型:
                font.pixelSize: 12
                color: "#7a7a7a"
                anchors.verticalCenter: parent.verticalCenter
            }
    //        GroupBox {
    //            anchors.verticalCenter: parent.verticalCenter
    //                title: qsTr("触摸板滚动条触发方式:")
    //            adjustToContentSize: true
                Common.ButtonRow {
                    exclusive: true//控制是否联动
                    spacing: 100
                    Common.CheckBox {
                        id:overlay
                        titleName: qsTr("overlay") //overlay模式        特色类型
                        checked: (touchpadsetpage.scrollbars_mode == "overlay-auto") ? true : false
                        flag: "radio"
                        onClicked: {
                            if (overlay.checked == true) {
                                sessiondispatcher.set_scrollbars_mode_overlay_qt();
                            }
                        }
                    }
                    Common.CheckBox {
                        id: legacy
                        titleName: qsTr("legacy")  //legacy模式       标准类型
                        checked: (touchpadsetpage.scrollbars_mode == "normal") ? true : false
                        flag: "radio"
                        onClicked: {
                            if (legacy.checked == true) {
                                sessiondispatcher.set_scrollbars_mode_legacy_qt();
                            }
                        }
                    }
    //            }
            }
        }



        Row {
            id: scrollstyle
            spacing: 40
            Common.Label {
                width: 110
                text: qsTr("Touchpad rolling mode:")//触摸板滚动触发方式:
                font.pixelSize: 12
                color: "#7a7a7a"
                anchors.verticalCenter: parent.verticalCenter
            }
    //        GroupBox {
    //            anchors.verticalCenter: parent.verticalCenter
    //                title: qsTr("触摸板滚动模式:")
    //            adjustToContentSize: true
                Common.ButtonRow {
                    exclusive: true//控制是否联动
                    spacing: 100
                    Common.CheckBox {
                        id:edge
                        titleName: qsTr("edge")//"edge模式"        边缘触发
                        checked: (touchpadsetpage.touchscrolling_mode == "edge-scrolling") ? true : false
                        flag: "radio"
                        onClicked: {
                            if (edge.checked == true) {
                                sessiondispatcher.set_touchscrolling_mode_edge_qt();
                            }
                        }
                    }
                    Common.CheckBox {
                        id: twofinger
                        titleName: qsTr("twofinger")//"twofinger模式"       双指触发
                        checked: (touchpadsetpage.touchscrolling_mode == "two-finger-scrolling") ? true : false
                        flag: "radio"
                        onClicked: {
                            if (twofinger.checked == true) {
                                sessiondispatcher.set_touchscrolling_mode_twofinger_qt();
                            }
                        }
                    }
    //            }
            }
        }


        Row {
            id: horizontalscroll
            spacing: 40
            Common.Label {
                width: 110
                text: qsTr("Scrollbar horizontal scroll:")//触摸板横向滚动:
                font.pixelSize: 12
                color: "#7a7a7a"
                anchors.verticalCenter: parent.verticalCenter
            }
            Common.Switch {
                id: horizontalswitcher
                width: 110
                onSwitched: {
                    if (horizontalswitcher.switchedOn) {
                        sessiondispatcher.set_touchscrolling_use_horizontal_qt(true);
                    }
                    else if(!horizontalswitcher.switchedOn) {
                        sessiondispatcher.set_touchscrolling_use_horizontal_qt(false);
                    }
                }
            }
        }
    }



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
        showok: false
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
    }
}
