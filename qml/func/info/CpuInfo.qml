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
import SystemType 0.1
import "../common" as Common
import "../bars" as Bars

Item {
    id: home; width: parent.width; height: 475
    Rectangle {
        anchors.fill: parent
//        //背景
//        Image {
//            source: "../../img/skin/bg-bottom-tab.png"
//            anchors.fill: parent
//        }

        Component.onCompleted: {
        }


        Column {
            anchors {
                top: parent.top
                topMargin: 40
                left: parent.left
                leftMargin: 30
            }
            spacing: 20

            Row {
                Text {
                    id: hardwaretitle
                    text: qsTr("Hardware information")//硬件信息
                    font.bold: true
                    font.pixelSize: 14
                    color: "#383838"
                }
                Rectangle {width: home.width - hardwaretitle.width - 30 * 2
                    anchors.verticalCenter: parent.verticalCenter
                    height: 1; color: "#ccdadd"
                }
            }
            Column {
                anchors.left: parent.left
                anchors.leftMargin: 20
                spacing: 10
                Row {
                    spacing: 10
                    Text {
                        text: qsTr("CpuVersion:")//处理器版本:
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        width: 100
                    }
                    Text {
                        text: systemdispatcher.getSingleInfo("CpuVersion")
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
                Row {
                    spacing: 10
                    Text {
                        text: qsTr("CpuVendor:")//制造商:
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        width: 100
                    }
                    Text {
                        text: systemdispatcher.getSingleInfo("CpuVendor")
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
            }

            Row {
                Text {
                    id: desktoptitle
                    text: qsTr("Desktop information")//桌面信息
                    font.bold: true
                    font.pixelSize: 14
                    color: "#383838"
                }
                Rectangle {width: home.width - desktoptitle.width - 30 * 2
                    anchors.verticalCenter: parent.verticalCenter
                    height: 1; color: "#ccdadd"
                }
            }
            Column {
                anchors.left: parent.left
                anchors.leftMargin: 20
                spacing: 10
                Row {
                    spacing: 10
                    Text {
                        text: qsTr("CpuSlot:")//插槽:
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        width: 100
                    }
                    Text {
                        text: systemdispatcher.getSingleInfo("CpuSlot")
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
                Row {
                    spacing: 10
                    Text {
                        text: qsTr("model_name:")//处理器:
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        width: 100
                    }
                    Text {
                        text: systemdispatcher.getSingleInfo("model_name")
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
                Row {
                    spacing: 10
                    Text {
                        text: qsTr("cpu_MHz:")//cpu主频:
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        width: 100
                    }
                    Text {
                        text: systemdispatcher.getSingleInfo("cpu_MHz")
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
                Row {
                    spacing: 10
                    Text {
                        text: qsTr("cpu_cores:")//cpu内核数:
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        width: 100
                    }
                    Text {
                        text: systemdispatcher.getSingleInfo("cpu_cores")
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
                Row {
                    spacing: 10
                    Text {
                        text: qsTr("cpu_siblings:")//cpu线程数:
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        width: 100
                    }
                    Text {
                        text: systemdispatcher.getSingleInfo("cpu_siblings")
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
            }

            Row {
                Text {
                    id: usertitle
                    text: qsTr("User information")//用户信息
                    font.bold: true
                    font.pixelSize: 14
                    color: "#383838"
                }
                Rectangle {width: home.width - usertitle.width - 30 * 2
                    anchors.verticalCenter: parent.verticalCenter
                    height: 1; color: "#ccdadd"
                }
            }
            Column {
                anchors.left: parent.left
                anchors.leftMargin: 20
                spacing: 10
                Row {
                    spacing: 10
                    Text {
                        text: qsTr("clflush_size:")//一级缓存:
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        width: 100
                    }
                    Text {
                        text: systemdispatcher.getSingleInfo("clflush_size")
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
                Row {
                    spacing: 10
                    Text {
                        text: qsTr("cache_size:")//二级缓存:
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        width: 100
                    }
                    Text {
                        text: systemdispatcher.getSingleInfo("cache_size")
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
            }
        }
    }
}
