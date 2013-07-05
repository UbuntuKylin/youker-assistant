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
//import SessionType 0.1
import SystemType 0.1
import QtDesktop 0.1
Rectangle {
    width: parent.width
    height: 460
//    property Dispatcher dis: mydispather
    property SystemDispatcher dis: systemdispatcher


    GroupBox {
        title: "Animation options"
        adjustToContentSize: true
        ButtonColumn {
            exclusive: true//控制是否联动
            CheckBox {
                id:fade
                text: "Fade on hover"
            }
            CheckBox {
                id: scale
                text: "Scale on hover"
            }
            CheckBox {
                id: scale1
                text: "Scale on hover1"
            }
        }
    }


//    Item {
//        Column {
//            anchors.fill: parent
//            Row {
//                Image {
//                    id: refreshArrow
//                    source: "../img/icons/system.png"
//                    Behavior on rotation { NumberAnimation { duration: 200 } }
//                }
//                Text {
//                    id: text1
//                    x: 30
//                    y: 11
//                    width: 69
//                    height: 20
//                    text: qsTr("优化加速:")
//                    font.bold: true
//                    font.pointSize: 13
//                    font.pixelSize: 12

//                    Column {
//                        Text {
//                            x: 65
//                            height: 20
//                            //text: qsTr("CPU: Intel(R) Core(TM) i5-3210M CPU @ 2.50GHz")
//                            text: qsTr("CPU: "+ mydispather.get_value("cpu"))
//                        }
//                        Text {
//                            x: 65
//                            height: 20
//                            text: qsTr("内存: " + mydispather.get_value("ram"))
////                            text: qsTr("内存: 1.8 GB")
//                        }
//                    }
//                }
//            }
//        }
//    }
}

//import QtQuick 2.0
//import Ubuntu.Components 0.1
//import Ubuntu.Components 0.1 as Theming
//import Ubuntu.Components.ListItems 0.1 as ListItem
//import Ubuntu.Components.Popups 0.1
//import QtQuick.LocalStorage 2.0
//import RegisterMyType 0.1

//Rectangle {
//    width: parent.width
//    height: 460
//    property Dispatcher dis: mydispather

//    Page {
//        Column {
//            anchors.fill: parent
//            ListItem.Standard {
//                id: yourself
//                progression: true
//                iconFrame: false
//                icon: Qt.resolvedUrl("../img/icons/user.png")
//                text: i18n.tr("需要优化的系统设置项")
//                onClicked: yourselfListView.visible = !yourselfListView.visible
//            }
//            Component {
//                id: yourselfDelegate
//                ListItem.Standard {
//                    id: listItem
////                    text: i18n.tr(title)
//                    height: 38
//                    width: parent.width
////                    control: Button {
////                        iconSource: Qt.resolvedUrl("../img/icons/clinic.png")
////                        onClicked: {
////                            yourselfListView.visible = false
////                        }
////                    }
//                    Rectangle {
//                        id: lineLayout
//                        x: 50; y:0
//                        height: clearImage.height; width: parent.width
////                        spacing: 10

//                        CheckBox {
//                            checked: true
//                            anchors { top: lineLayout.top; topMargin: 1 }
//                            onCheckedChanged: {
//                                //kobe: wait for adding function
//                            }
//                        }

//                        Image {
//                            id: clearImage
//                            anchors { top: lineLayout.top; topMargin: 8 }
//                            width: 16; height: 16
//                            source: picture
//                            anchors { left: parent.left; leftMargin: 45}

//                        }

//                        Column {
//                            spacing: 5
//                            anchors {
//                                top: parent.top; topMargin: 3
//                                left: clearImage.right; leftMargin: 15}
//                            Text {
//                                text: title
//                                font.pointSize: 9
//                                color: "black"
//                            }
//                            Text {
//                                text: detailstr
//                                font.pointSize: 7
//                                color: "gray"
//                            }
//                        }
//                    }
////                    icon: yourselfIcon
//                    iconFrame: true
//                }
//            }
//            ListModel {
//                id: systemModel
//                ListElement {
//                    title: "清理垃圾"
//                    picture: "../img/icons/settings.png"
//                    detailstr: "清理系统垃圾，让系统运行跟流畅"
//                    y_trans: 8
//                }
//                ListElement {
//                    title: "清理痕迹"
//                    picture: "../img/icons/history.png"
//                    detailstr: "清理使用计算机时留下的各种痕迹，保护个人隐私"
//                    y_trans: 68
//                }
//                ListElement {
//                    title: "清理注册表"
//                    picture: "../img/icons/about.png"
//                    detailstr: "清理电脑日常使用中产生的无用注册表项，提高系统性能"
//                    y_trans: 128
//                }
//            }

//            ListView {
//                id: yourselfListView
//                width: parent.width
//                height: 38 * 3
//                model: systemModel
//                delegate: yourselfDelegate
//                visible: false
//            }


//            ListItem.Standard {
//                id: systemHeader
//                iconFrame: false
//                icon: Qt.resolvedUrl("../img/icons/at.png")
//                text: i18n.tr("需要优化的网络设置项")
//                progression: true
//                onClicked: systemListView.visible = !systemListView.visible
//            }
//            Component {
//                id: systemDelegate
//                ListItem.Standard {
//                    id: listItem
////                    text: title
//                    height: 38
//                    width: parent.width
////                    control: Button {
////                        iconSource: Qt.resolvedUrl("../img/icons/book_close.png")
////                        onClicked: {
////                            systemListView.visible = false
////                        }
////                    }
//                    Rectangle {
//                        id: lineLayout
//                        x: 50; y:0
//                        height: clearImage.height; width: parent.width
////                        spacing: 10

//                        CheckBox {
//                            checked: true
//                            anchors { top: lineLayout.top; topMargin: 1 }
//                            onCheckedChanged: {
//                                //kobe: wait for adding function
//                            }
//                        }

//                        Image {
//                            id: clearImage
//                            anchors { top: lineLayout.top; topMargin: 8 }
//                            width: 16; height: 16
//                            source: picture
//                            anchors { left: parent.left; leftMargin: 45}

//                        }
//                        Column {
//                            spacing: 5
//                            anchors {
//                                top: parent.top; topMargin: 3
//                                left: clearImage.right; leftMargin: 15}
//                            Text {
//                                text: title
//                                font.pointSize: 9
//                                color: "black"
//                            }
//                            Text {
//                                text: detailstr
//                                font.pointSize: 7
//                                color: "gray"
//                            }
//                        }
//                    }
//                    iconFrame: true
//                }
//            }

//            ListModel {
//                id: networkModel
//                ListElement {
//                    title: "清理垃圾"
//                    picture: "../img/icons/settings.png"
//                    detailstr: "清理系统垃圾，让系统运行跟流畅"
//                    y_trans: 8
//                }
//                ListElement {
//                    title: "清理痕迹"
//                    picture: "../img/icons/history.png"
//                    detailstr: "清理使用计算机时留下的各种痕迹，保护个人隐私"
//                    y_trans: 48
//                }
//                ListElement {
//                    title: "清理注册表"
//                    picture: "../img/icons/about.png"
//                    detailstr: "清理电脑日常使用中产生的无用注册表项，提高系统性能"
//                    y_trans: 88
//                }
//            }


//            ListView {
//                id: systemListView
//                width: parent.width
//                height: 38 * 3
//                model: networkModel
//                delegate: systemDelegate
//                visible: false
//            }

//        }
//    }
//}
