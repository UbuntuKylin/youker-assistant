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
//import QtQuick 1.1
//import SessionType 0.1
//import "common" as Common
//import "./bars" as Bars
//Item {

//    id:root
//    width: parent.width
//    height: 475
//    property string btn_text: "开始扫描"
//    property string title: "清理浏览器登录信息,保护个人隐私"
//    property string description: "清理上网时留下的登录信息,目前仅支持Firefox浏览器"
//    property string btn_flag: "cookies_scan"
////    property ListModel listmodel: mainModel
////    property ListModel submodel: subModel
//    property int coo_sub_num: 0//number of subitem
//    property string work_result: ""
////    property int sub_num:coo_sub_num
//    property bool check_flag: true
//    property bool null_flag: false
//    property int deleget_arrow :0


//    ListModel {
//        id: systemModel
//        ListElement {
//            title: "清理垃圾"
//            picture: "../img/skin/note-bg.png"
//            detailstr: "清理系统垃圾，让系统运行跟流畅"
////                        y_trans: 8
//        }
//        ListElement {
//            title: "清理痕迹"
//            picture: "../img/skin/note-bg.png"
//            detailstr: "清理使用计算机时留下的各种痕迹，保护个人隐私"
////                        y_trans: 68
//        }
//        ListElement {
//            title: "清理注册表"
//            picture: "../img/skin/note-bg.png"
//            detailstr: "清理电脑日常使用中产生的无用注册表项，提高系统性能"
////                        y_trans: 128
//        }
//        ListElement {
//            title: "kobe"
//            picture: "../img/skin/note-bg.png"
//            detailstr: "清理电脑日常使用中产生的无用注册表项，提高系统性能"
////                        y_trans: 128
//        }
//        ListElement {
//            title: "lixinag"
//            picture: "../img/skin/note-bg.png"
//            detailstr: "清理电脑日常使用中产生的无用注册表项，提高系统性能"
////                        y_trans: 128
//        }
//    }
//    ListModel {
//        id: networkModel
//        ListElement {
//            title: "清理垃圾222"
//            picture: "../img/skin/note-bg.png"
//            detailstr: "清理系统垃圾，让系统运行跟流畅"
////            y_trans: 8
//        }
//        ListElement {
//            title: "清理痕迹333"
//            picture: "../img/skin/note-bg.png"
//            detailstr: "清理使用计算机时留下的各种痕迹，保护个人隐私"
////            y_trans: 48
//        }
//        ListElement {
//            title: "清理注册表444"
//            picture: "../img/skin/note-bg.png"
//            detailstr: "清理电脑日常使用中产生的无用注册表项，提高系统性能"
////            y_trans: 88
//        }
//    }
//    Component {
//        id: yourselfDelegate
//            Rectangle {
//                id: lineLayout
//                height: 40; width: parent.width
//                color: "transparent"
//                Row {
//                    spacing: 10
//                    anchors { top: lineLayout.top; topMargin: 1 }
//                    Common.CheckBox {
//                        checked: true
//                        onCheckedChanged: {
//                            //kobe: wait for adding function
//                        }
//                    }
//                    Column {
//                        spacing: 5
//                        Text {
//                            text: title
//                            font.pointSize: 9
//                            color: "black"
//                        }
//                        Text {
//                            text: detailstr
//                            font.pointSize: 7
//                            color: "gray"
//                        }
//                    }
//                }
//            }
////            }
//    }
////    Component.onCompleted: {
////    }


//    Rectangle {
//        anchors.fill: parent
//        //背景
//        Image {
//            source: "../img/skin/bg-bottom-tab.png"
//            anchors.fill: parent
//        }
//        Common.ScrollArea {
////            frame:false
//            height: parent.height
//            width: parent.width
//            Item {
//                width: parent.width
//                height: 500//parent.height + 20
//                Column {
//                    spacing: 30
//                    anchors.top: parent.top
//                    anchors.topMargin: 20
//                    anchors.left: parent.left
//                    anchors.leftMargin: 30

//                    Common.Button {
//                        id: yourself
//                        width: 120
//                        height: 39
//                        hoverimage: "green1.png"
//                        fontsize: 15
//                        text: "系统设置项"
//                        onClicked: yourselfListView.visible = !yourselfListView.visible
//                    }
//                    ListView {
//                        id: yourselfListView
//                        width: parent.width
//                        height: 38 * 5
//                        model: systemModel
//                        delegate: yourselfDelegate
//                        visible: false
//                    }


//                    Common.Button {
//                        id: systemHeader
//                        width: 120
//                        height: 39
//                        hoverimage: "green1.png"
//                        fontsize: 15
//                        text: "网络设置项"
//                        onClicked: systemListView.visible = !systemListView.visible
//                    }
//                    ListView {
//                        id: systemListView
//                        width: parent.width
//                        height: 38 * 3
//                        model: networkModel
//                        delegate: yourselfDelegate
//                        visible: false
//                    }
//                }
//            }

//        }
//    }
//}








import QtQuick 1.1
import SessionType 0.1
import "common" as Common

Item {
    id: home; width: parent.width; height: 475
    Rectangle {
        anchors.fill: parent
        //背景
        Image {
            source: "../img/skin/bg-bottom-tab.png"
            anchors.fill: parent
        }
        signal dialogmsg()

        Component.onCompleted: {
            sessiondispatcher.get_system_message_qt();
        }

        function openFile(file) {
             var component = Qt.createComponent(file)
             if (component.status == Component.Ready)
                 pageStack.push(component);
             else
                 console.log("Error loading component:", component.errorString());
         }


        //desktop logo
        Image {
            source: "../img/toolWidget/ubuntukylin.png"
            anchors {
                top: parent.top
                topMargin: 230
                right: parent.right
                rightMargin: 70
            }
        }

        Image {
            id: titleimage
            anchors {
                left: parent.left
                leftMargin: 2
            }
            width: parent.width - 4
            source: "../img/skin/note-bg.png"
        }
        Text {
            anchors {
                left: parent.left
                leftMargin: 50
                top: parent.top
                topMargin: titleimage.height/2 - 7
            }
            text: qsTr("You can view the relevant information, and understand the system at any time.")//您可以查看相关信息，随时了解系统情况。
            font.pixelSize: 12
            color: "#383838"
        }

        //上下分割条
        Rectangle {x: 100; y: 90; width: parent.width - 150; height: 1; color: "#ccdadd" }
        Rectangle {x: 100; y: 190; width: parent.width - 150; height: 1; color: "#ccdadd" }
        Rectangle {x: 100; y: 370; width: parent.width - 150; height: 1; color: "#ccdadd" }
        Column {
            anchors {
    //            fill: parent
                top: titleimage.bottom
                topMargin: 40
                left: parent.left
                leftMargin: 30
            }
            spacing: 20

            Text {
                id: hardwaretitle
                text: qsTr("Hardware information")//硬件信息
                font.bold: true
                font.pixelSize: 14
                color: "#383838"
            }
            Column {
                anchors.left: parent.left
                anchors.leftMargin: 20
                spacing: 10
                Row {
                    spacing: 8
                    Text {
                        text: qsTr("CPU:")//处理器:
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        width: 60
                    }
                    Text {
                        text: sessiondispatcher.getSingleInfo("cpu")
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
                Row {
                    spacing: 10
                    Text {
                        text: qsTr("Memory:")//内存:
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        width: 60
                    }
                    Text {
                        text: sessiondispatcher.getSingleInfo("ram")
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
            }


            Text {
                id: desktoptitle
                text: qsTr("Desktop information")//桌面信息
                font.bold: true
                font.pixelSize: 14
                color: "#383838"
            }
            Column {
                anchors.left: parent.left
                anchors.leftMargin: 20
                spacing: 10
                Row {
                    spacing: 10
                    Text {
                        text: qsTr("Host name:")//主机名:
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        width: 60
                    }
                    Text {
                        text: sessiondispatcher.getSingleInfo("hostname")
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
                Row {
                    spacing: 10
                    Text {
                        text: qsTr("Platform:")//平台:
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        width: 60
                    }
                    Text {
                        text: sessiondispatcher.getSingleInfo("platform")
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
                Row {
                    spacing: 10
                    Text {
                        text: qsTr("Distribution Edition:")//发行版:
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        width: 60
                    }
                    Text {
                        text: sessiondispatcher.getSingleInfo("distribution")
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
                Row {
                    spacing: 10
                    Text {
                        text: qsTr("Desktop Environment:")//桌面环境:
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        width: 60
                    }
                    Text {
                        text: sessiondispatcher.getSingleInfo("desktopenvironment")
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
                Row {
                    spacing: 10
                    Text {
                        text: qsTr("Language:")//语言:
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        width: 60
                    }
                    Text {
                        text: sessiondispatcher.getSingleInfo("language")
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
            }

            Text {
                id: usertitle
                text: qsTr("User information")//用户信息
                font.bold: true
                font.pixelSize: 14
                color: "#383838"
            }
            Column {
                anchors.left: parent.left
                anchors.leftMargin: 20
                spacing: 10
                Row {
                    spacing: 10
                    Text {
                        text: qsTr("Current user:")//当前用户:
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        width: 60
                    }
                    Text {
                        text: sessiondispatcher.getSingleInfo("currrent_user")
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
                Row {
                    spacing: 10
                    Text {
                        text: qsTr("User home directory:")//用户主目录:
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        width: 60
                    }
                    Text {
                        text: sessiondispatcher.getSingleInfo("home_path")
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
            }
        }
    }
}
