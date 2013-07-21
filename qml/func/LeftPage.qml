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
//import SessionType 0.1
//import SystemType 0.1
import QtDesktop 0.1
import "common" as Common
//坐边栏
Rectangle {
    id: leftbar
    width: 600; height: 460
    //背景
    Image {
        source: "../img/skin/bg-left.png"
        anchors.fill: parent
    }
    Column {
        anchors.fill: parent
        Row {
            id: myrow
            spacing: 10
            anchors { top: parent.top; topMargin: 20; left: parent.left; leftMargin: 20 }
//            Image {
//                id: refreshArrow
//                source: "../img/toolWidget/clear-logo.gif"
////                width: 120; height: 120
//                Behavior on rotation { NumberAnimation { duration: 200 } }
//            }
            AnimatedImage {
                id: refreshArrow
                source: "../img/toolWidget/clear-logo.gif"
            }

            Column {
                spacing: 10
                id: mycolumn
                Text {
                    id: text0
                    width: 69
                    text: qsTr("一键清理系统垃圾，有效提高系统运行效率")
                    font.bold: true
                    font.pixelSize: 14
                    color: "#383838"
//                    font.pointSize: 13
//                    font.pixelSize: 12
    //                        anchors { top: lineLayout.top; topMargin: refreshArrow.height/2; left: parent.left; leftMargin: 45 + refreshArrow.width }
                }
                Text {
                    id: text1
                    width: 69
//                    text: qsTr("全面清理垃圾、痕迹、注册表，高效率解决系统清理问题.")
                    text: qsTr("       一键清理将会直接清理掉下面四个勾选项的内容,如果您不想直接清理掉某项")
                    font.pixelSize: 12
                    color: "#7a7a7a"
//                    font.pointSize: 13
//                    font.pixelSize: 12
    //                        anchors { top: lineLayout.top; topMargin: refreshArrow.height/2; left: parent.left; leftMargin: 45 + refreshArrow.width }
                }
                Text {
                    id: text2
                    width: 69
//                    text: qsTr("全面清理垃圾、痕迹、注册表，高效率解决系统清理问题.")
                    text: qsTr("内容,请去掉该项的勾选框,进入系统清理页面进行更细致地选择性清理。")
                    font.pixelSize: 12
                    color: "#7a7a7a"
//                    font.pointSize: 13
//                    font.pixelSize: 12
    //                        anchors { top: lineLayout.top; topMargin: refreshArrow.height/2; left: parent.left; leftMargin: 45 + refreshArrow.width }
                }
                SetBtn {
                    iconName: "onekeyBtn.png"
                    setbtn_flag: "onekey"
                    anchors {
                        top: text2.bottom; topMargin: 10
                        left: parent.left; leftMargin: 100
                    }
                    width: 186
                    height: 45
                }
            }

        }//Row


        Column {
            anchors { top: myrow.bottom; topMargin: 20; left: parent.left; leftMargin: 20 }
            Label {
                id: itemtip
//                text: qsTr("<h1>一键清理项目</h1>")
                text: "一键清理项目"
//                font.family: "楷体"
                font.bold: true
                font.pixelSize: 14
                color: "#008000"
    //            anchors { top: refreshArrow.bottom; topMargin: 10; left: parent.left; leftMargin: 5 }
            }
//            ScrollArea {
//                frame:false
//                width:leftbar.width -10 //因为左边移位了10
//                //leftbar.height - refreshArrow.height - refreshArrow顶部距离10 - refreshArrow底部距离10 - 顶部距离20 -顶部距离10
//                height: leftbar.height - refreshArrow.height - itemtip.height - 10*2 - 20 -10
//                anchors.top: itemtip.bottom
//                anchors.topMargin: 10
//                Item {
//                    width:parent.width
//                    height:330
//                    Component {
//                        id: statusDelegate
//                        Row {
//                            Text {
//                                text: title
//                            }
//                        }
//                    }
//                    ListModel {
//                        id: streamModel
//                        ListElement {
//                            title: ""
//                        }
//                    }

//                    //垃圾清理显示内容
//                    ListView {
//                        id: listView
//                        height: parent.height
//                        width: parent.width
//                        model: streamModel
//                        delegate: statusDelegate
//                        cacheBuffer: 1000
//                        opacity: 1
//                        spacing: 10
//                        snapMode: ListView.NoSnap
//        //                            cacheBuffer: parent.height
//                        boundsBehavior: Flickable.DragOverBounds
//                        currentIndex: 0
//                        preferredHighlightBegin: 0
//                        preferredHighlightEnd: preferredHighlightBegin
//                        highlightRangeMode: ListView.StrictlyEnforceRange
//                    }
//                }//Item
//            }//ScrollArea



            Item {
                id: views
                width: parent.width ////ListView不会随鼠标上下移动
//                width:leftbar.width -10 //ListView会随鼠标上下移动
                height: leftbar.height - refreshArrow.height - itemtip.height - 10*2 - 20 -10
                anchors.top: itemtip.bottom
                anchors.topMargin: 30

                ListModel {
                    id: clearModel
                    ListElement {
                        title: "清理垃圾"
                        picture: "../img/toolWidget/brush.png"
                        detailstr: "清理系统中的垃圾文件，释放磁盘空间"
                        flag: "cache"
                    }
                    ListElement {
                        title: "清理历史记录"
                        picture: "../img/toolWidget/history.png"
                        detailstr: "清理上网时留下的历史记录，保护您的个人隐私"
                        flag: "history"
                    }
                    ListElement {
                        title: "清理Cookies"
                        picture: "../img/toolWidget/cookies.png"
                        detailstr: "清理上网时产生的Cookies，还浏览器一片天空"
                        flag: "cookies"
                    }
                    ListElement {
                        title: "卸载不必要的安装程序"
                        picture: "../img/toolWidget/deb.png"
                        detailstr: "清理软件安装过程中安装的依赖程序，提高系统性能"
                        flag: "unneed"
                    }
                }

                ListView {
                    id: listView
                    height: parent.height
                    width: parent.width
                    anchors.top: parent.top
//                    anchors.topMargin: titlebar.height + 45
                    model: clearModel
                    delegate: FastDelegate {}
                    cacheBuffer: 1000
                }
            }




        }//Column
    }//Column


}//坐边栏Rectangle
