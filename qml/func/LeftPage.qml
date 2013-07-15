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
        source: "../img/skin/leftbackground.png"
        anchors.fill: parent
    }
    Column {

        Row {
            id: myrow
            spacing: 10
            anchors { top: parent.top; topMargin: 20; left: parent.left; leftMargin: 20 }
            Image {
                id: refreshArrow
                source: "../img/toolWidget/hardware.png"
                width: 120; height: 120
                Behavior on rotation { NumberAnimation { duration: 200 } }
            }
            Column {
                spacing: 10
                id: mycolumn
                Text {
                    id: text0
                    width: 69
                    text: qsTr("一键清理系统垃圾，有效提高系统运行效率")
                    font.bold: true
                    font.pointSize: 13
                    font.pixelSize: 12
    //                        anchors { top: lineLayout.top; topMargin: refreshArrow.height/2; left: parent.left; leftMargin: 45 + refreshArrow.width }
                }
                Text {
                    id: text1
                    width: 69
                    text: qsTr("全面清理垃圾、痕迹、注册表，高效率解决系统清理问题.")
    //                        font.bold: true
                    font.pointSize: 13
                    font.pixelSize: 12
    //                        anchors { top: lineLayout.top; topMargin: refreshArrow.height/2; left: parent.left; leftMargin: 45 + refreshArrow.width }
                }
                SetBtn {
                    iconName: "onekeyBtn.png"
                    anchors {
                        top: text1.bottom; topMargin: 30
                        left: parent.left; leftMargin: 80
                    }
                    width: 186
                    height: 45
                }
            }

        }//Row


        Column {
            anchors { top: myrow.bottom; topMargin: 20; left: parent.left; leftMargin: 10 }
            Label {
                id: itemtip
                text: qsTr("<h1>安全项目</h1>")
                font.family: "楷体"
                color: "green"
    //            anchors { top: refreshArrow.bottom; topMargin: 10; left: parent.left; leftMargin: 5 }
            }
            ScrollArea {
                frame:false
                width:leftbar.width -10 //因为左边移位了10
                //leftbar.height - refreshArrow.height - refreshArrow顶部距离10 - refreshArrow底部距离10 - 顶部距离20 -顶部距离10
                height: leftbar.height - refreshArrow.height - itemtip.height - 10*2 - 20 -10
                anchors.top: itemtip.bottom
                anchors.topMargin: 10
                Item {
                    width:parent.width
                    height:330
                    Component {
                        id: statusDelegate
                        Row {
                            Text {
                                text: title
                            }
                        }
                    }
                    ListModel {
                        id: streamModel
                        ListElement {
                            title: "清理垃圾1"
                        }
                        ListElement {
                            title: "清理垃圾2"
                        }
                        ListElement {
                            title: "清理垃圾3"
                        }
                        ListElement {
                            title: "清理垃圾4"
                        }
                        ListElement {
                            title: "清理垃圾5"
                        }
                        ListElement {
                            title: "清理垃圾6"
                        }
                        ListElement {
                            title: "清理垃圾7"
                        }
                        ListElement {
                            title: "清理垃圾8"
                        }

                    }

                    //垃圾清理显示内容
                    ListView {
                        id: listView
                        height: parent.height
                        width: parent.width
                        model: streamModel
                        delegate: statusDelegate
                        cacheBuffer: 1000
                        opacity: 1
                        spacing: 10
                        snapMode: ListView.NoSnap
        //                            cacheBuffer: parent.height
                        boundsBehavior: Flickable.DragOverBounds
                        currentIndex: 0
                        preferredHighlightBegin: 0
                        preferredHighlightEnd: preferredHighlightBegin
                        highlightRangeMode: ListView.StrictlyEnforceRange
                    }
                }//Item
            }//ScrollArea
        }//Column
    }//Column


}//坐边栏Rectangle
