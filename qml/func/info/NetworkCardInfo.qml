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
import "../common" as Common
import "../bars" as Bars

Rectangle {
    id: home; width: parent.width; height: 475
    color: "transparent"
    Component.onCompleted: {
        systemdispatcher.get_networkcard_info_qt();//获取详细信息
        var msg = systemdispatcher.getSingleInfo("NetVendor", "networkcard");
        var pat = new RegExp('Intel');
        if(pat.test(msg)) {
            logo.source =  "../../img/logo/Manufacturer/INTEL.jpg";
        }
        modelText.text = systemdispatcher.getSingleInfo("NetProduct", "networkcard");
        vendorText.text = msg;
        busText.text = systemdispatcher.getSingleInfo("NetBusinfo", "networkcard");
        deviceText.text = systemdispatcher.getSingleInfo("NetLogicalname", "networkcard");
        fwText.text = systemdispatcher.getSingleInfo("NetVersion", "networkcard");
        macText.text = systemdispatcher.getSingleInfo("NetSerial", "networkcard");
        sizeText.text = systemdispatcher.getSingleInfo("NetSize", "networkcard");
        maxText.text = systemdispatcher.getSingleInfo("NetCapacity", "networkcard");
        bitText.text = systemdispatcher.getSingleInfo("NetWidth", "networkcard");
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
                id: basictitle
                text: qsTr("Network Card information")//网卡信息
                font.bold: true
                font.pixelSize: 14
                color: "#383838"
            }
            Rectangle {width: home.width - basictitle.width - 30 * 2
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
                    text: qsTr("Network Card Model:")//网卡型号：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 130
                }
                Text {
                    id: modelText
                    text: ""//systemdispatcher.getSingleInfo("NetProduct")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("Vendor:")//制造商：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 130
                }
                Text {
                    id: vendorText
                    text: ""//systemdispatcher.getSingleInfo("NetVendor")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("Bus Address:")//总线地址：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 130
                }
                Text {
                    id: busText
                    text: ""//systemdispatcher.getSingleInfo("NetBusinfo")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("Device Name:")//设备名称：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 130
                }
                Text {
                    id: deviceText
                    text: ""//systemdispatcher.getSingleInfo("NetLogicalname")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("Fireware Version:")//固件版本：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 130
                }
                Text {
                    id: fwText
                    text: ""//systemdispatcher.getSingleInfo("NetVersion")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("Mac Address:")//MAC地址：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 130
                }
                Text {
                    id: macText
                    text: ""//systemdispatcher.getSingleInfo("NetSerial")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("Net Size:")//带宽大小：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 130
                }
                Text {
                    id: sizeText
                    text: ""//systemdispatcher.getSingleInfo("NetSize")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("Max Size:")//最大带宽：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 130
                }
                Text {
                    id: maxText
                    text: ""//systemdispatcher.getSingleInfo("NetCapacity")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("Bit Size:")//网卡位宽：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 130
                }
                Text {
                    id: bitText
                    text: ""//systemdispatcher.getSingleInfo("NetWidth")
                    font.pixelSize: 14
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
