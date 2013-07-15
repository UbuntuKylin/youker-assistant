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
import QtDesktop 0.1
import SessionType 0.1
import SystemType 0.1
import "./func/common" as Common
import "./func/settings" as Settings
import "func"
//Rectangle {
Item {
    id:content
    width: parent.width
    height: parent.height - 30  //去掉StatusWidget所占用的高度30

//    radius: 10
//    color: "lightgray"

    property string text: "homepage"
    SessionDispatcher {
        id: sessiondispatcher
    }
    SystemDispatcher {
        id: systemdispatcher
    }


    Rectangle {
        id: rectangle1
        width: parent.width
//        height: titlebar.height + toolwidget.height + 30
        height: 84 + 20
//        height: 40 + 20
        color: "transparent"
//        Image {
//            id: bgImg
//            width: parent.width
//            height: 84 + 20  //标题栏 + 功能图标栏的高度
//            source: "./img/skin/background.png"
//        }

        Image {
            id: bgImg
            anchors.fill: parent
            source: "./img/skin/titlebar.png"
        }

        //优客助手logo
        Image {
            id: logo
            anchors.right: parent.right
            anchors.rightMargin: 4
            anchors.verticalCenter: parent.verticalCenter
//            height: 50
    //        width: 140
    //        height: 70
            source: "./img/icons/logo.png"
        }

        Column {
            id: layout1
            anchors.fill: parent
            spacing: 0

            //标题栏
            TitleWidget {
                id: titlebar
                height: 20
//                opacity: 0.3
            }
            //功能图标栏
            ToolWidget {
                id: toolwidget
                height: 84
                anchors {
                    top: titlebar.bottom
                    topMargin: 45
                }

//                opacity: 0.3
            }
        }
    }

    //内容展示区域
    /*widget for displaying contents*/
    Item {
        id:display_content
        width: parent.width
        height: parent.height - 104 -30 //去掉标题栏 + 功能图标栏 + StatusWidget的高度
//        height: parent.height - titlebar.height - toolwidget.height -30 //去掉标题栏 + 功能图标栏 + StatusWidget的高度
        anchors.top: parent.top
        anchors.topMargin: 106
//        anchors.topMargin: titlebar.height + toolwidget.height + 20
        opacity: 1.0
        property string text: "homepage"

        Common.PageStack {
            id: pageStack
//            anchors.fill: parent
            Component.onCompleted: {
                pageStack.push(homepage);
            }
            Common.Page {
                id: homepage
                visible: false
                HomePage {dis1: sessiondispatcher; dis2: systemdispatcher}
            }
            Common.Page {
                id: clearrubbish
                visible: false
//                title: "clearrubbish by kobe"
                ClearRubbish {dis1: sessiondispatcher; dis2: systemdispatcher}
            }
            Common.Page {
                id: systemset
                visible: false
//                title: "softwaremanager by kobe"
                SystemSet {dis1: sessiondispatcher; dis2: systemdispatcher}
            }
            Common.Page {
                id: systemmessage
                visible: false
//                title: "search by kobe"
                SystemMessage {dis1: sessiondispatcher; dis2: systemdispatcher}
            }
            Common.Page {
                id: functioncollection
                visible: false
//                title: "allfunction by kobe"
                FunctionCollection {dis: systemdispatcher}
            }

        }
    }
}








//Rectangle {
//    id:content
//    width: parent.width
////    height: parent.height - 142 + 84 + 30
//    height: parent.height - 30

//    property string text: "homepage"
//    Dispatcher
//    {
//        id: mydispather
//    }



//    Rectangle {
//        id: rectangle1
//        width: parent.width
//        height: 84 + 20
//        color: "transparent"
//        Image {
//            id: bgImg
//            width: parent.width
//            height: 84 + 20
//            source: "./img/skin/background.png"
//        }

//        Rectangle {
//            id: titlebar
//            height: 20
//            width: parent.width
//            color: "transparent"
//            Text {
//                anchors.top: parent.top
//                anchors.topMargin: 4
//                anchors.left: parent.left
//                anchors.leftMargin: 14
//                color: "black"
//                font.bold: true
//                text: qsTr("系统助手 0.1.0")
//            }

//            Row {
//                anchors.right: parent.right
//                anchors.rightMargin: 3
//                SysBtn {iconName: "title_bar_menu.png"}
//                SysBtn {
//                    iconName: "sys_button_min.png"
//                    MouseArea {
//                        anchors.fill: parent
//                        onClicked: {
//                        }
//                    }
//                }
////                SysBtn {iconName: "sys_button_max.png"}
//                SysBtn {
//                    iconName: "sys_button_close.png"
//                    // describe the close button
//                    MouseArea {
//                        anchors.fill: parent
//                        onClicked: {
//                            Qt.quit();
//                        }
//                    }
//                }
//            }
//        }



//        Row {
//            id: tool_line
//            anchors.left: parent.left
//            anchors.leftMargin: 3
//            anchors.top: titlebar.bottom
//            spacing: 0
//            ToolBtn {iconName: "homepage.png"; method: "首页"; text: "homepage"; /*dis: mydispather;*/
//            onSend: pageStack.push(homepage)}
//            ToolBtn {iconName: "clearrubbish.png"; method: "电脑清理"; text: "clearrubbish"; /*dis: mydispather;*/
//            onSend: pageStack.push(clearrubbish)}
//            ToolBtn {iconName: "systemset.png"; method: "系统设置"; text: "systemset"; /*dis: mydispather;*/
//            onSend: pageStack.push(systemset)}
//            ToolBtn {iconName: "optimalacceleration.png"; method: "优化加速"; text: "optimalacceleration"; /*dis: mydispather;*/
//            onSend: pageStack.push(optimalacceleration)}
//            ToolBtn {iconName: "searchtrojan.png"; method: "查杀木马"; text: "searchtrojan"; /*dis: mydispather;*/
//            onSend: pageStack.push(searchtrojan)}
//            ToolBtn {iconName: "computerclinic.png"; method: "电脑门诊"; text: "computerclinic"; /*dis: mydispather;*/
//            onSend: pageStack.push(computerclinic)}
//            ToolBtn {iconName: "fixbug.png"; method: "修复漏洞"; text: "fixbug"; /*dis: mydispather;*/
//            onSend: pageStack.push(fixbug)}
//            ToolBtn {iconName: "systemrepair.png"; method: "系统修复"; text: "systemrepair"; /*dis: mydispather;*/
//            onSend: pageStack.push(systemrepair)}
//            ToolBtn {iconName: "allfunction.png"; method: "功能大全"; text: "allfunction"; /*dis: mydispather;*/
//            onSend: pageStack.push(allfunction)}

//        }

//        Image {
//            id: logo
//            anchors.top: titlebar.bottom
//            anchors.right: parent.right
//            anchors.rightMargin: 4
//            width: 140
//            height: 70
//            source: "./img/logo.png"
//        }
//    }

//    /*widget for displaying contents*/
//    Item {
//        id:content1
//        width: parent.width
////        height: parent.height - 142 + 84 + 30
//        height: parent.height - 104 -30
////        anchors.top: tool_line.bottom
//        anchors.top: parent.top
//        anchors.topMargin: 106
//        property string text: "homepage"
//        PageStack {
//            id: pageStack
////            anchors.fill: parent
//            Component.onCompleted: {
//                pageStack.push(homepage);
//            }
//            Page {
//                id: homepage
//                HomePage {dis: mydispather}
//            }
//            Page {
//                id: clearrubbish
////                title: "clearrubbish by kobe"
//                ClearRubbish {dis: mydispather}
//            }
//            Page {
//                id: systemset
////                title: "softwaremanager by kobe"
//                SystemSet {dis: mydispather}
//            }
//            Page {
//                id: searchtrojan
////                title: "search by kobe"
//                SearchTrojan {dis: mydispather}
//            }
//            Page {
//                id: fixbug
////                title: "fixbug by kobe"
//                FixBug {dis: mydispather}
//            }
//            Page {
//                id: computerclinic
////                title: "computerclinic by kobe"
//                ComputerClinic {dis: mydispather}
//            }
//            Page {
//                id: systemrepair
////                title: "systemrepair by kobe"
//                SystemRepair {dis: mydispather}
//            }
//            Page {
//                id: optimalacceleration
////                title: "optimalacceleration by kobe"
//                OptimalAcceleration {dis: mydispather}
//            }
//            Page {
//                id: allfunction
////                title: "allfunction by kobe"
//                AllFunction {dis: mydispather}
//            }

//            /*-----------pages of system settings-----------*/
//            Page {
//                id: launcher
//                Launcher {}
//            }
//            Page {
//                id: search
//                Search {}
//            }
//            Page {
//                id: clearprogress
//                ClearProgress {}
//            }
//        }
//    }
//}

