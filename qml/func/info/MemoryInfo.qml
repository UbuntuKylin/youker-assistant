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
        logo.source = "../../img/logo/Manufacturer/" + systemdispatcher.getSingleInfo("MemVendor").toUpperCase() + ".jpg";
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
                text: qsTr("Memory information")//内存条信息
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
            spacing: 10
            Row {
                spacing: 10
                Text {
                    text: qsTr("Slot Number:")//插槽号:
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    width: 100
                }
                Text {
                    text: systemdispatcher.getSingleInfo("MemSlot")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("Memory Model:")//内存型号:
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    width: 100
                }
                Text {
                    text: systemdispatcher.getSingleInfo("MemProduct")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("Vendor:")//制造商:
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    width: 100
                }
                Text {
                    text: systemdispatcher.getSingleInfo("MemVendor")
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
                    width: 100
                }
                Text {
                    text: systemdispatcher.getSingleInfo("MemSerial")
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("Size:")//内存大小:
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    width: 100
                }
                Text {
                    text: systemdispatcher.getSingleInfo("MemSize")
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
