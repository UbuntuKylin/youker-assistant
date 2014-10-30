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
import "../common/InfoGroup.js" as InfoGroup

Rectangle {
    id: home
    width: parent.width; height: 476

    property string homepath
    Component.onCompleted: {
        home.homepath = sessiondispatcher.getHomePath();
    }


    function init_data() {
        systemdispatcher.get_cpu_info_qt();//获取详细信息
        var cpuName = systemdispatcher.getHWSingleInfo("CpuVendor", "cpu");
        logo.source = InfoGroup.judgeName(cpuName.toUpperCase()) ? (home.homepath + "/.cache/youker-assistant/uk-img/Manufacturer/" + cpuName.toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
        cpuversionText.text = systemdispatcher.getHWSingleInfo("CpuVersion", "cpu");
        cpuverdorText.text = cpuName;
        cpuserialText.text = systemdispatcher.getHWSingleInfo("CpuSerial", "cpu");
        slotText.text = systemdispatcher.getHWSingleInfo("CpuSlot", "cpu");
        maxText.text = systemdispatcher.getHWSingleInfo("CpuCapacity", "cpu");// + "MHz";
        curText.text = systemdispatcher.getHWSingleInfo("CpuSize", "cpu");// + "MHz";
        frontText.text = systemdispatcher.getHWSingleInfo("CpuClock", "cpu");// + "MHz";
        coresText.text = systemdispatcher.getHWSingleInfo("cpu_cores", "cpu") + qsTr("cores") + "/" + systemdispatcher.getHWSingleInfo("cpu_siblings", "cpu") + qsTr("thread");//核//线程
        cache1.text = systemdispatcher.getHWSingleInfo("clflush_size", "cpu") + "KB";
        cache2.text = systemdispatcher.getHWSingleInfo("cache_size", "cpu") + "KB";
    }

    Connections
    {
        target: sessiondispatcher
        onTellDetailPageUpdateData: {
            if (infoFlag == "cpu") {
                home.init_data();
            }
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
                id: bartitle
                text: qsTr("CPU Info")//处理器信息
                font.bold: true
                font.pixelSize: 14
                color: "#383838"
            }
            Common.Separator {
                anchors.verticalCenter: parent.verticalCenter
                width: home.width - bartitle.width - 30 * 2
            }
        }
        Column {
            anchors.left: parent.left
            anchors.leftMargin: 20
            spacing: 10
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("CPU: ")//处理器：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 150
                }
                Text {
                    id: cpuversionText
                    text: ""
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Vendor: ")//制造商：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 150
                }
                Text {
                    id: cpuverdorText
                    text: ""
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
                    width: 150
                }
                Text {
                    id: cpuserialText
                    text: ""
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Socket/Slot: ")//插座/插槽：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 150
                }
                Text {
                    id: slotText
                    text: ""
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Maximum Frequency: ")//最大主频：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 150
                }
                Text {
                    id: maxText
                    text: ""
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Current Frequency: ")//当前主频：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 150
                }
                Text {
                    id: curText
                    text: ""
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("FSB: ")//前端总线：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 150
                }
                Text {
                    id: frontText
                    text: ""
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Core Number: ")//核心数目：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 150
                }
                Text {
                    id: coresText
                    text: ""
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("L1 Cache: ")//一级缓存：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 150
                }
                Text {
                    id: cache1
                    text: ""
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("L2 Cache: ")//二级缓存：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 150
                }
                Text {
                    id: cache2
                    text: ""
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
        opacity: 0.5
        anchors {
            top: parent.top
            topMargin: 80
            right: parent.right
            rightMargin: 30
        }
    }
}
