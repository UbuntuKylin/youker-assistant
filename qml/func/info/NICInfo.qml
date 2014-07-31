/*
 * Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd.
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
    id: home; width: parent.width; height: 476
//    color: "transparent"
//    color: "#e4f2fc"
    property int fontSize: 14

//    Component.onCompleted: {
    function init_data() {
        systemdispatcher.get_networkcard_info_qt();//获取详细信息
        var netName = systemdispatcher.getHWSingleInfo("NetVendor", "networkcard");
        logo.source = InfoGroup.judgeName(netName.toUpperCase()) ? ("../../img/logo/Manufacturer/" + netName.toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");

        modelText.text = systemdispatcher.getHWSingleInfo("NetProduct", "networkcard");
        vendorText.text = netName;
        driverText.text = systemdispatcher.getHWSingleInfo("NetDrive", "networkcard");
        busText.text = systemdispatcher.getHWSingleInfo("NetBusinfo", "networkcard");
        deviceText.text = systemdispatcher.getHWSingleInfo("NetLogicalname", "networkcard");
        ipText.text = systemdispatcher.getHWSingleInfo("NetIp", "networkcard");
        macText.text = systemdispatcher.getHWSingleInfo("NetSerial", "networkcard");
        linkText.text = systemdispatcher.getHWSingleInfo("NetLink", "networkcard");
        maxText.text = systemdispatcher.getHWSingleInfo("NetCapacity", "networkcard") + " Mbit/s";
//        bitText.text = systemdispatcher.getHWSingleInfo("NetWidth", "networkcard");

        var wnetName = systemdispatcher.getHWSingleInfo("WlanVendor", "networkcard");
        wlogo.source = InfoGroup.judgeName(wnetName.toUpperCase()) ? ("../../img/logo/Manufacturer/" + wnetName.toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
        wdriverText.text = systemdispatcher.getHWSingleInfo("WlanDrive", "networkcard");
        wvendorText.text = wnetName;
        wmodelText.text = systemdispatcher.getHWSingleInfo("WlanProduct", "networkcard");
        wbusText.text = systemdispatcher.getHWSingleInfo("WlanBusinfo", "networkcard");
        wdeviceText.text = systemdispatcher.getHWSingleInfo("WlanLogicalname", "networkcard");
        wmacText.text = systemdispatcher.getHWSingleInfo("WlanSerial", "networkcard");
        wipText.text = systemdispatcher.getHWSingleInfo("WlanIp", "networkcard");
    }

    Connections
    {
        target: sessiondispatcher
        onTellDetailPageUpdateData: {
            if (infoFlag == "networkcard") {
                home.init_data();
            }
        }
    }

    Common.ScrollArea {
        frame:false
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: 30
        height: parent.height - 40
        width: parent.width
        Column {
            anchors {
                top: parent.top
                topMargin: 10
                left: parent.left
                leftMargin: 30
            }
            spacing: 18

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
                        width: 150
                    }
                    Text {
                        id: modelText
                        width: 450
                        wrapMode: Text.WordWrap
                        text: ""//systemdispatcher.getHWSingleInfo("NetProduct")
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
                        width: 150
                    }
                    Text {
                        id: vendorText
                        text: ""//systemdispatcher.getHWSingleInfo("NetVendor")
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
                        width: 150
                    }
                    Text {
                        id: driverText
                        text: ""//systemdispatcher.getHWSingleInfo("NetDrive")
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
                        width: 150
                    }
                    Text {
                        id: busText
                        text: ""//systemdispatcher.getHWSingleInfo("NetBusinfo")
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
                        width: 150
                    }
                    Text {
                        id: deviceText
                        text: ""//systemdispatcher.getHWSingleInfo("NetLogicalname")
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
                        width: 150
                    }
                    Text {
                        id: ipText
                        text: ""//systemdispatcher.getHWSingleInfo("NetIp")
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
                        width: 150
                    }
                    Text {
                        id: macText
                        text: ""//systemdispatcher.getHWSingleInfo("NetSerial")
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
                        width: 150
                    }
                    Text {
                        id: linkText
                        text: ""//systemdispatcher.getHWSingleInfo("NetLink")
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
                        width: 150
                    }
                    Text {
                        id: maxText
                        text: ""//systemdispatcher.getHWSingleInfo("NetCapacity")
                        font.pixelSize: home.fontSize
                        color: "#7a7a7a"
                    }
                }
            }
            Row {
                visible: (wmodelText.text != "" && wvendorText.text != "") ? true:false
                Common.Label {
                    id: biostitle
                    text: qsTr("WLan NIC Info")//无线网卡信息
                    font.bold: true
                    font.pixelSize: 14
                    color: "#383838"
                }
                Common.Separator {
                    id: splitbar
                    anchors.verticalCenter: parent.verticalCenter
                    width: home.width - biostitle.width - 30 * 2
                }
            }
            Column {
                anchors.left: parent.left
                anchors.leftMargin: 20
                spacing: 10
                Row {
                    spacing: 10
                    visible: wmodelText.text ? true:false
                    Common.Label {
                        text: qsTr("WLan NIC Model:")//网卡型号：
                        font.pixelSize: home.fontSize
                        color: "#7a7a7a"
                        width: 150
                    }
                    Text {
                        id: wmodelText
                        width: 450
                        wrapMode: Text.WordWrap
                        text: ""//systemdispatcher.getHWSingleInfo("WlanProduct")
                        font.pixelSize: home.fontSize
                        color: "#7a7a7a"
                    }
                }
                Row {
                    spacing: 10
                    visible: wvendorText.text ? true:false
                    Common.Label {
                        text: qsTr("Vendor:")//制造商：
                        font.pixelSize: home.fontSize
                        color: "#7a7a7a"
                        width: 150
                    }
                    Text {
                        id: wvendorText
                        text: ""//systemdispatcher.getHWSingleInfo("WlanVendor")
                        font.pixelSize: home.fontSize
                        color: "#7a7a7a"
                    }
                }
                Row {
                    spacing: 10
                    visible: wdriverText.text ? true:false
                    Common.Label {
                        text: qsTr("WLan NIC Driver:")//无线网卡驱动：
                        font.pixelSize: home.fontSize
                        color: "#7a7a7a"
                        width: 150
                    }
                    Text {
                        id: wdriverText
                        text: ""//systemdispatcher.getHWSingleInfo("WlanDrive")
                        font.pixelSize: home.fontSize
                        color: "#7a7a7a"
                    }
                }
                Row {
                    spacing: 10
                    visible: wbusText.text ? true:false
                    Common.Label {
                        text: qsTr("Bus Address:")//总线地址：
                        font.pixelSize: home.fontSize
                        color: "#7a7a7a"
                        width: 150
                    }
                    Text {
                        id: wbusText
                        text: ""//systemdispatcher.getHWSingleInfo("WlanBusinfo")
                        font.pixelSize: home.fontSize
                        color: "#7a7a7a"
                    }
                }
                Row {
                    spacing: 10
                    visible: wdeviceText.text ? true:false
                    Common.Label {
                        text: qsTr("Device Name:")//设备名称：
                        font.pixelSize: home.fontSize
                        color: "#7a7a7a"
                        width: 150
                    }
                    Text {
                        id: wdeviceText
                        text: ""//systemdispatcher.getHWSingleInfo("WlanLogicalname")
                        font.pixelSize: home.fontSize
                        color: "#7a7a7a"
                    }
                }

                Row {
                    spacing: 10
                    visible: wipText.text ? true:false
                    Common.Label {
                        text: qsTr("IP Address:")//IP地址：
                        font.pixelSize: home.fontSize
                        color: "#7a7a7a"
                        width: 150
                    }
                    Text {
                        id: wipText
                        text: ""//systemdispatcher.getHWSingleInfo("WlanIp")
                        font.pixelSize: home.fontSize
                        color: "#7a7a7a"
                    }
                }
                Row {
                    spacing: 10
                    height: 40
                    visible: wmacText.text ? true:false
                    Common.Label {
                        text: qsTr("Serial Number: ")//序列号：
                        font.pixelSize: home.fontSize
                        color: "#7a7a7a"
                        width: 150
                    }
                    Text {
                        id: wmacText
                        text: ""//systemdispatcher.getHWSingleInfo("WlanSerial")
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
            opacity: 0.5
            anchors {
                top: parent.top
                topMargin: 65
                left: parent.left
                leftMargin: 570
            }
        }
        //logo
        Image {
            id: wlogo
            visible: (wmodelText.text != "" && wvendorText.text != "") ? true:false
            opacity: 0.5
            source: ""
            anchors {
                top: parent.top
                topMargin: (wmodelText.text != "" && wvendorText.text != "") ? 385 : 0
                left: parent.left
                leftMargin: 570
            }
        }
    }
}
