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

Rectangle {
    id: home; width: parent.width; height: 475
    color: "transparent"
    Component.onCompleted: {
        systemdispatcher.get_detail_system_message_qt();//获取详细信息
        logo.source = "../../img/logo/Manufacturer/" + systemdispatcher.getSingleInfo("ComVendor") + ".jpg";
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
                id: titlebar
                text: qsTr("Basic information")//电脑基本信息
                font.bold: true
                font.pixelSize: 14
                color: "#383838"
            }
            Rectangle {width: home.width - titlebar.width - 30 * 2
                anchors.verticalCenter: parent.verticalCenter
                height: 1; color: "#ccdadd"
            }
        }
        Column {
            anchors.left: parent.left
            anchors.leftMargin: 20
            spacing: 15
            Row {
                spacing: 10
                Text {
                    text: qsTr("Vendor:")//制造商:
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    width: 120
                }
                Text {
                    id: comvendor
                    text: systemdispatcher.getSingleInfo("ComVendor")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("Model:")//电脑型号:
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    width: 120
                }
                Text {
                    id: comproduct
                    text: systemdispatcher.getSingleInfo("ComProduct")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("Version:")//电脑版本:
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    width: 120
                }
                Text {
                    id: comversion
                    text: systemdispatcher.getSingleInfo("ComVersion")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("Serial:")//序列号:
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    width: 120
                }
                Text {
                    id: comserial
                    text: systemdispatcher.getSingleInfo("ComSerial")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("Hostname:")//主机名:
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    width: 120
                }
                Text {
                    id: node
                    text: systemdispatcher.getSingleInfo("node")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("Running Time:")//持续运行:
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    width: 120
                }
                Text {
                    id: uptime
                    text: systemdispatcher.getSingleInfo("uptime")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("OS Model:")//操作系统类型:
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    width: 120
                }
                Text {
                    id: system
                    text: systemdispatcher.getSingleInfo("system")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("OS Version:")//操作系统:
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    width: 120
                }
                Text {
                    id: platform
                    text: systemdispatcher.getSingleInfo("platform")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("Kernel Bit:")//系统位数:
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    width: 120
                }
                Text {
                    id: architecture
                    text: systemdispatcher.getSingleInfo("architecture")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("Kernel Release:")//内核版本:
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    width: 120
                }
                Text {
                    id: release
                    text: systemdispatcher.getSingleInfo("release")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("Kernel Architecture:")//内核架构:
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    width: 120
                }
                Text {
                    id: machine
                    text: systemdispatcher.getSingleInfo("machine")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
        }
    }
    //logo
    Image {
        id: logo
        source: ""
        anchors {
            top: parent.top
            topMargin: 50
            right: parent.right
            rightMargin: 30
        }
    }
}
