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
import "./InfoGroup.js" as InfoGroup

Rectangle {
    id: home; width: parent.width; height: 475
    color: "transparent"
    property int fontSize: 12
    Component.onCompleted: {
        systemdispatcher.get_networkcard_info_qt();//获取详细信息
        var netName = systemdispatcher.getSingleInfo("NetVendor", "networkcard");
        logo.source = InfoGroup.judgeName(netName.toUpperCase()) ? ("../../img/logo/Manufacturer/" + netName.toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
//        var pat = new RegExp('Intel');
//        if(pat.test(msg)) {
//            logo.source =  "../../img/logo/Manufacturer/INTEL.jpg";
//        }
        modelText.text = systemdispatcher.getSingleInfo("NetProduct", "networkcard");
        vendorText.text = netName;
        driverText.text = systemdispatcher.getSingleInfo("NetDrive", "networkcard");
        busText.text = systemdispatcher.getSingleInfo("NetBusinfo", "networkcard");
        deviceText.text = systemdispatcher.getSingleInfo("NetLogicalname", "networkcard");
        ipText.text = systemdispatcher.getSingleInfo("NetIp", "networkcard");
        macText.text = systemdispatcher.getSingleInfo("NetSerial", "networkcard");
        linkText.text = systemdispatcher.getSingleInfo("NetLink", "networkcard");
        maxText.text = systemdispatcher.getSingleInfo("NetCapacity", "networkcard") + " Mbit/s";
//        bitText.text = systemdispatcher.getSingleInfo("NetWidth", "networkcard");

        var wnetName = systemdispatcher.getSingleInfo("WlanVendor", "networkcard");
        wlogo.source = InfoGroup.judgeName(wnetName.toUpperCase()) ? ("../../img/logo/Manufacturer/" + wnetName.toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
        wdriverText.text = systemdispatcher.getSingleInfo("WlanDrive", "networkcard");
        wvendorText.text = wnetName;
        wmodelText.text = systemdispatcher.getSingleInfo("WlanProduct", "networkcard");
        wbusText.text = systemdispatcher.getSingleInfo("WlanBusinfo", "networkcard");
        wdeviceText.text = systemdispatcher.getSingleInfo("WlanLogicalname", "networkcard");
        wmacText.text = systemdispatcher.getSingleInfo("WlanSerial", "networkcard");
        wipText.text = systemdispatcher.getSingleInfo("WlanIp", "networkcard");
    }

    Column {
        anchors {
            top: parent.top
            topMargin: 10
            left: parent.left
            leftMargin: 30
        }
        spacing: 10

        Row {
            Common.Label {
                id: basictitle
                text: qsTr("NIC Info")//有线网卡信息
                font.bold: true
                font.pixelSize: 14
                color: "#383838"
            }
            Common.Separator {
                anchors.verticalCenter: parent.verticalCenter
                width: home.width - basictitle.width - 30 * 2
            }
        }

        Column {
            anchors.left: parent.left
            anchors.leftMargin: 20
            spacing: 10
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("NIC Model:")//有线网卡型号：
                    font.pixelSize: home.fontSize
                    color: "#7a7a7a"
                    width: 130
                }
                Text {
                    id: modelText
                    text: ""//systemdispatcher.getSingleInfo("NetProduct")
                    font.pixelSize: home.fontSize
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Vendor:")//制造商：
                    font.pixelSize: home.fontSize
                    color: "#7a7a7a"
                    width: 130
                }
                Text {
                    id: vendorText
                    text: ""//systemdispatcher.getSingleInfo("NetVendor")
                    font.pixelSize: home.fontSize
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("NIC Driver:")//有线网卡驱动：
                    font.pixelSize: home.fontSize
                    color: "#7a7a7a"
                    width: 130
                }
                Text {
                    id: driverText
                    text: ""//systemdispatcher.getSingleInfo("NetDrive")
                    font.pixelSize: home.fontSize
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Bus Address:")//总线地址：
                    font.pixelSize: home.fontSize
                    color: "#7a7a7a"
                    width: 130
                }
                Text {
                    id: busText
                    text: ""//systemdispatcher.getSingleInfo("NetBusinfo")
                    font.pixelSize: home.fontSize
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Device Name:")//设备名称：
                    font.pixelSize: home.fontSize
                    color: "#7a7a7a"
                    width: 130
                }
                Text {
                    id: deviceText
                    text: ""//systemdispatcher.getSingleInfo("NetLogicalname")
                    font.pixelSize: home.fontSize
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("IP Address:")//IP地址：
                    font.pixelSize: home.fontSize
                    color: "#7a7a7a"
                    width: 130
                }
                Text {
                    id: ipText
                    text: ""//systemdispatcher.getSingleInfo("NetIp")
                    font.pixelSize: home.fontSize
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Mac Address:")//MAC地址：
                    font.pixelSize: home.fontSize
                    color: "#7a7a7a"
                    width: 130
                }
                Text {
                    id: macText
                    text: ""//systemdispatcher.getSingleInfo("NetSerial")
                    font.pixelSize: home.fontSize
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Connection Status: ")//连接状态：
                    font.pixelSize: home.fontSize
                    color: "#7a7a7a"
                    width: 130
                }
                Text {
                    id: linkText
                    text: ""//systemdispatcher.getSingleInfo("NetLink")
                    font.pixelSize: home.fontSize
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Max Bandwidth: ")//最大带宽：
                    font.pixelSize: home.fontSize
                    color: "#7a7a7a"
                    width: 130
                }
                Text {
                    id: maxText
                    text: ""//systemdispatcher.getSingleInfo("NetCapacity")
                    font.pixelSize: home.fontSize
                    color: "#7a7a7a"
                }
            }
        }
        Row {
            Common.Label {
                id: biostitle
                text: qsTr("WLan NIC Info")//无线网卡信息
                font.bold: true
                font.pixelSize: 14
                color: "#383838"
            }
            Rectangle {
                id: splitbar
                width: home.width - biostitle.width - 30 * 2
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
                Common.Label {
                    text: qsTr("WLan NIC Model:")//网卡型号：
                    font.pixelSize: home.fontSize
                    color: "#7a7a7a"
                    width: 130
                }
                Text {
                    id: wmodelText
                    text: ""//systemdispatcher.getSingleInfo("WlanProduct")
                    font.pixelSize: home.fontSize
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Vendor:")//制造商：
                    font.pixelSize: home.fontSize
                    color: "#7a7a7a"
                    width: 130
                }
                Text {
                    id: wvendorText
                    text: ""//systemdispatcher.getSingleInfo("WlanVendor")
                    font.pixelSize: home.fontSize
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("WLan NIC Driver:")//无线网卡驱动：
                    font.pixelSize: home.fontSize
                    color: "#7a7a7a"
                    width: 130
                }
                Text {
                    id: wdriverText
                    text: ""//systemdispatcher.getSingleInfo("WlanDrive")
                    font.pixelSize: home.fontSize
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Bus Address:")//总线地址：
                    font.pixelSize: home.fontSize
                    color: "#7a7a7a"
                    width: 130
                }
                Text {
                    id: wbusText
                    text: ""//systemdispatcher.getSingleInfo("WlanBusinfo")
                    font.pixelSize: home.fontSize
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Device Name:")//设备名称：
                    font.pixelSize: home.fontSize
                    color: "#7a7a7a"
                    width: 130
                }
                Text {
                    id: wdeviceText
                    text: ""//systemdispatcher.getSingleInfo("WlanLogicalname")
                    font.pixelSize: home.fontSize
                    color: "#7a7a7a"
                }
            }

            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("IP Address:")//IP地址：
                    font.pixelSize: home.fontSize
                    color: "#7a7a7a"
                    width: 130
                }
                Text {
                    id: wipText
                    text: ""//systemdispatcher.getSingleInfo("WlanIp")
                    font.pixelSize: home.fontSize
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Serial Number: ")//序列号：
                    font.pixelSize: home.fontSize
                    color: "#7a7a7a"
                    width: 130
                }
                Text {
                    id: wmacText
                    text: ""//systemdispatcher.getSingleInfo("WlanSerial")
                    font.pixelSize: home.fontSize
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
            topMargin: 80
            right: parent.right
            rightMargin: 30
        }
    }
    //logo
    Image {
        id: wlogo
        source: ""
        anchors {
            top: parent.top
            topMargin: 320
            right: parent.right
            rightMargin: 30
        }
    }
}
