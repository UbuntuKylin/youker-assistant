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
    id: home; width: parent.width; height: 475
    color: "transparent"

    Component.onCompleted: {
        systemdispatcher.get_computer_info_qt();//获取详细信息
        var vendorName = systemdispatcher.getHWSingleInfo("ComVendor", "computer").toUpperCase();
        logo.source = InfoGroup.judgeName(vendorName) ? ("../../img/logo/Manufacturer/" + vendorName + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");

        comvendorText.text = vendorName;
        comproductText.text = systemdispatcher.getHWSingleInfo("ComProduct", "computer");
        comversionText.text = systemdispatcher.getHWSingleInfo("ComVersion", "computer");
        comserialText.text = systemdispatcher.getHWSingleInfo("ComSerial", "computer");
        nodeText.text = systemdispatcher.getHWSingleInfo("node", "computer");
        systemText.text = systemdispatcher.getHWSingleInfo("system", "computer");
        platformText.text = systemdispatcher.getHWSingleInfo("platform", "computer");
        architectureText.text = systemdispatcher.getHWSingleInfo("architecture", "computer");
        releaseText.text = systemdispatcher.getHWSingleInfo("release", "computer");
        machineText.text = systemdispatcher.getHWSingleInfo("machine", "computer");


        var timeValue = systemdispatcher.getHWSingleInfo("uptime", "computer");
        var valueHour = Math.floor(timeValue/60);//返回小于等于timeValue/60的最大整数
//        var aa = valueHour.toFixed(0);
        var valueMinute = timeValue % 60;
        if(valueHour == 0) {
            uptimeText.text = valueMinute + qsTr(" Minutes");//分钟
        }
        else {
            uptimeText.text = valueHour + qsTr(" Hours ") + valueMinute + qsTr(" Minutes");//小时 分钟
        }
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
            Common.Label {
                id: titlebar
                text: qsTr("Computer Basic Info")//电脑基本信息
                font.bold: true
                font.pixelSize: 14
                color: "#383838"
            }
            Common.Separator {
                anchors.verticalCenter: parent.verticalCenter
                width: home.width - titlebar.width - 30 * 2
            }
        }
        Column {
            anchors.left: parent.left
            anchors.leftMargin: 20
            spacing: 15
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Vendor: ")//制造商：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 120
                }
                Text {
                    id: comvendorText
                    text: ""//systemdispatcher.getHWSingleInfo("ComVendor")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Model: ")//电脑型号：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 120
                }
                Text {
                    id: comproductText
                    text: ""//systemdispatcher.getHWSingleInfo("ComProduct")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Version: ")//电脑版本：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 120
                }
                Text {
                    id: comversionText
                    text: ""//systemdispatcher.getHWSingleInfo("ComVersion")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Serial Number: ")//序列号：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 120
                }
                Text {
                    id: comserialText
                    text: ""//systemdispatcher.getHWSingleInfo("ComSerial")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Hostname: ")//主机名：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 120
                }
                Text {
                    id: nodeText
                    text: ""//systemdispatcher.getHWSingleInfo("node")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Running Time: ")//持续运行时间：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 120
                }
                Text {
                    id: uptimeText
                    text: ""//systemdispatcher.getHWSingleInfo("uptime")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("OS Types: ")//操作系统类型：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 120
                }
                Text {
                    id: systemText
                    text: ""//systemdispatcher.getHWSingleInfo("system")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("OS Version: ")//操作系统版本：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 120
                }
                Text {
                    id: platformText
                    text: ""//systemdispatcher.getHWSingleInfo("platform")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Kernel Bit: ")//系统位数：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 120
                }
                Text {
                    id: architectureText
                    text: ""//systemdispatcher.getHWSingleInfo("architecture")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Kernel Version: ")//内核版本：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 120
                }
                Text {
                    id: releaseText
                    text: ""//systemdispatcher.getHWSingleInfo("release")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Kernel Arch: ")//内核架构：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 120
                }
                Text {
                    id: machineText
                    text: ""//systemdispatcher.getHWSingleInfo("machine")
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
            topMargin: 80
            right: parent.right
            rightMargin: 30
        }
    }
    Timer{
        interval: 2000*60;running: true;repeat: true
        onTriggered: {
            var timeValue = systemdispatcher.get_time_value_qt();
            var valueHour = Math.floor(timeValue/60);//返回小于等于timeValue/60的最大整数
            var valueMinute = timeValue % 60;
            if(valueHour == 0) {
                uptimeText.text = valueMinute + qsTr(" Minutes");//分钟
            }
            else {
                uptimeText.text = valueHour + qsTr(" Hours ") + valueMinute + qsTr(" Minutes");//小时 分钟
            }
        }
    }
}
