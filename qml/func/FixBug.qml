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
//import Ubuntu.Components.ListItems 0.1 as ListItem

import RegisterMyType 0.1

Rectangle {
    width: parent.width
    height: 460
    property Dispatcher dis: mydispather

    Item {
        Column {
            anchors.fill: parent
            Row {
                Image {
                    id: refreshArrow
                    source: "../img/icons/bug.png"
                    Behavior on rotation { NumberAnimation { duration: 200 } }
                }
                Text {
                    id: text1
                    x: 30
                    y: 11
                    width: 69
                    height: 20
                    text: qsTr("漏洞:")
                    font.bold: true
                    font.pointSize: 13
                    font.pixelSize: 12

                    Column {
                        Text {
                            x: 65
                            height: 20
                            //text: qsTr("CPU: Intel(R) Core(TM) i5-3210M CPU @ 2.50GHz")
                            text: qsTr("CPU: "+ mydispather.get_value("cpu"))
                        }
                        Text {
                            x: 65
                            height: 20
                            text: qsTr("内存: " + mydispather.get_value("ram"))
//                            text: qsTr("内存: 1.8 GB")
                        }
                    }
                }
            }
        }
    }
}





//Rectangle {
//    height: 460
//    property Dispatcher dis: mydispather
//    Page {
//        Rectangle {
//            anchors {fill: parent; top: parent.top; topMargin: 10; left: parent.left; leftMargin: 30}
//            Column {
//                Text {
//                    text: "清理电脑中的插件"
//                    font.pointSize: 11
//                    color: "black"
//                }
//                Text {
//                    text:  "清理插件可以给系统和浏览器“减负”，减少干扰，提供系统和浏览器速度"
//                    font.pointSize: 9
//                    color: "gray"
//                }
//            }
//            Button {
//                id: pluginBtn
//                width: 90
//                color: "gray"
//                anchors {
//                    left: parent.left; leftMargin: 700}
//                text: "开始扫描"
//                onClicked: {
//                    //kobe: wait for adding function
//                }
//            }
//        }
////        Rectangle {  //分割条
////            width: parent.width; height: 1
////            anchors { top: parent.top; topMargin: 50}
////            color: "gray"
////        }
//        ListItem.ThinDivider {} //can be used as header for list


//        Column {
//            anchors {fill: parent; top: parent.top; topMargin: 52}
//            /*------------上网浏览产生的缓存垃圾-----------*/
//            ListItem.Standard {
//                id: netrubbish
//                progression: true
//                iconFrame: false
//                icon: Qt.resolvedUrl("../img/icons/settings.png")
////                text: i18n.tr("上网浏览产生的缓存垃圾")
//                Column {
//                    spacing: 5
//                    anchors {
//                        top: parent.top; topMargin: 10
//                        left: parent.left; leftMargin: 80}
//                    Text {
//                        text: "上网浏览产生的缓存垃圾"
//                        font.pointSize: 9
//                        color: "black"
//                    }
//                    Text {
//                        text: "清理上网浏览时产生的缓存文件，可以加快上网速度"
//                        font.pointSize: 7
//                        color: "gray"
//                    }
//                }
//                onClicked: netListView.visible = !netListView.visible
//            }
//            Component {
//                id: netDelegate
//                ListItem.Standard {
////                    text: i18n.tr(title)
//                    height: 38
//                    width: parent.width
////                    control: Button {
////                        iconSource: Qt.resolvedUrl("../img/icons/clinic.png")
////                        onClicked: {
////                            netListView.visible = false
////                        }
////                    }
//                    Row {
//                        id: netLayout
//                        anchors {fill: parent; left: parent.left; leftMargin: 50}
//                        height: 38; width: parent.width
//                        spacing: 10

//                        CheckBox {
//                            checked: true
//                            anchors { top: netLayout.top; topMargin: 1 }
//                            onCheckedChanged: {
//                                //kobe: wait for adding function
//                            }
//                        }
//                        Text {
//                            text: title
//                            anchors { top: netLayout.top; topMargin: 8 }
//                            font.pointSize: 9
//                            color: "black"
//                        }
//                    }
//                    iconFrame: true
//                }
//            }
//            ListModel {
//                id: netCache
//                ListElement {
//                    title: "浏览器缓存"
//                }
//            }
//            ListView {
//                id: netListView
//                width: parent.width
//                height: 38
//                model: netCache
//                delegate: netDelegate
//                visible: false
//            }


//            /*------------看视频听音乐产生的垃圾文件-----------*/
//            ListItem.Standard {
//                id: mediarubbish
//                progression: true
//                iconFrame: false
//                icon: Qt.resolvedUrl("../img/icons/history.png")
////                text: i18n.tr("看视频听音乐产生的垃圾文件")
//                Column {
//                    spacing: 5
//                    anchors {
//                        top: parent.top; topMargin: 10
//                        left: parent.left; leftMargin: 80}
//                    Text {
//                        text: "看视频听音乐产生的垃圾文件"
//                        font.pointSize: 9
//                        color: "black"
//                    }
//                    Text {
//                        text: "清理后会导致网络播放器不能读取已下载的缓存文件，请慎重选择"
//                        font.pointSize: 7
//                        color: "gray"
//                    }
//                }
//                onClicked: mediaListView.visible = !mediaListView.visible
//            }
//            Component {
//                id: mediaDelegate
//                ListItem.Standard {
////                    text: title
//                    height: 38
//                    width: parent.width
////                    control: Button {
////                        iconSource: Qt.resolvedUrl("../img/icons/book_close.png")
////                        onClicked: {
////                            mediaListView.visible = false
////                        }
////                    }
//                    Row {
//                        id: mediaLayout
//                        x: 50; y:0
//                        height: 38; width: parent.width
//                        spacing: 10

//                        CheckBox {
//                            checked: true
//                            anchors { top: mediaLayout.top; topMargin: 1 }
//                            onCheckedChanged: {
//                                //kobe: wait for adding function
//                            }
//                        }
//                        Text {
//                            text: title
//                            anchors { top: mediaLayout.top; topMargin: 8 }
//                            font.pointSize: 9
//                            color: "black"
//                        }
//                    }
//                    iconFrame: true
//                }
//            }
//            ListModel {
//                id: mediaCache
//                ListElement {
//                    title: "视频播放器缓存文件"
//                }
//                ListElement {
//                    title: "音频播放器缓存文件"
//                }
//            }
//            ListView {
//                id: mediaListView
//                width: parent.width
//                height: 38 * 2
//                model: mediaCache
//                delegate: mediaDelegate
//                visible: false
//            }

//            /*------------应用程序垃圾文件-----------*/
//            ListItem.Standard {
//                id: apprubbish
//                progression: true
//                iconFrame: false
//                icon: Qt.resolvedUrl("../img/icons/about.png")
////                text: i18n.tr("应用程序垃圾文件")
//                Column {
//                    spacing: 5
//                    anchors {
//                        top: parent.top; topMargin: 10
//                        left: parent.left; leftMargin: 80}
//                    Text {
//                        text: "应用程序垃圾文件"
//                        font.pointSize: 9
//                        color: "black"
//                    }
//                    Text {
//                        text: "清理系统第三方软件产生的垃圾文件，节约磁盘空间"
//                        font.pointSize: 7
//                        color: "gray"
//                    }
//                }
//                onClicked: appListView.visible = !appListView.visible
//            }
//            Component {
//                id: appDelegate
//                ListItem.Standard {
////                    text: title
//                    height: 38
//                    width: parent.width
////                    control: Button {
////                        iconSource: Qt.resolvedUrl("../img/icons/book_close.png")
////                        onClicked: {
////                            appListView.visible = false
////                        }
////                    }
//                    Row {
//                        id: appLayout
//                        x: 50; y:0
//                        height: 38; width: parent.width
//                        spacing: 10
//                        CheckBox {
//                            checked: true
//                            anchors { top: appLayout.top; topMargin: 1 }
//                            onCheckedChanged: {
//                                //kobe: wait for adding function
//                            }
//                        }
//                        Text {
//                            text: title
//                            anchors { top: appLayout.top; topMargin: 8 }
//                            font.pointSize: 9
//                            color: "black"
//                        }
//                    }
//                    iconFrame: true
//                }
//            }
//            ListModel {
//                id: appCache
//                ListElement {
//                    title: "麒麟助手缓存文件"
//                }
//                ListElement {
//                    title: "浏览器更新日志"
//                }
//                ListElement {
//                    title: "WPS缓存文件"
//                }
//                ListElement {
//                    title: "Flash缓存文件"
//                }
//            }
//            ListView {
//                id: appListView
//                width: parent.width
//                height: 38 * 4
//                model: appCache
//                delegate: appDelegate
//                visible: false
//            }
//        }
//    }
//}
