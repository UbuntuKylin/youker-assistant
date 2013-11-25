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
                        text: qsTr("ComVendor:")//制造商:
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        width: 100
                    }
                    Text {
                        text: systemdispatcher.getSingleInfo("ComVendor")
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
                Row {
                    spacing: 10
                    Text {
                        text: qsTr("ComProduct:")//电脑型号:
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        width: 100
                    }
                    Text {
                        text: systemdispatcher.getSingleInfo("ComProduct")
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
                        text: qsTr("ComVersion:")//电脑版本:
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        width: 100
                    }
                    Text {
                        text: systemdispatcher.getSingleInfo("ComVersion")
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
                Row {
                    spacing: 10
                    Text {
                        text: qsTr("ComSerial:")//序列号:
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        width: 100
                    }
                    Text {
                        text: systemdispatcher.getSingleInfo("ComSerial")
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
                Row {
                    spacing: 10
                    Text {
                        text: qsTr("node:")//主机名:
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        width: 100
                    }
                    Text {
                        text: systemdispatcher.getSingleInfo("node")
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
                Row {
                    spacing: 10
                    Text {
                        text: qsTr("uptime:")//持续运行时间:
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        width: 100
                    }
                    Text {
                        text: systemdispatcher.getSingleInfo("uptime")
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
                Row {
                    spacing: 10
                    Text {
                        text: qsTr("system:")//操作系统类型:
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        width: 100
                    }
                    Text {
                        text: systemdispatcher.getSingleInfo("system")
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
                        text: qsTr("platform:")//操作系统:
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        width: 100
                    }
                    Text {
                        text: systemdispatcher.getSingleInfo("platform")
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
                Row {
                    spacing: 10
                    Text {
                        text: qsTr("architecture:")//系统位数:
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        width: 100
                    }
                    Text {
                        text: systemdispatcher.getSingleInfo("architecture")
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
                Row {
                    spacing: 10
                    Text {
                        text: qsTr("release:")//内核版本:
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        width: 100
                    }
                    Text {
                        text: systemdispatcher.getSingleInfo("release")
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
                Row {
                    spacing: 10
                    Text {
                        text: qsTr("machine:")//内核架构:
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        width: 100
                    }
                    Text {
                        text: systemdispatcher.getSingleInfo("machine")
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
            }
        }
    }
}
