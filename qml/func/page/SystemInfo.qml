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
import "../bars" as Bars
import "../info" as Info
import "../others" as Others
Rectangle {
    id: window
    width: parent.width; height: 475
    //背景
    Image {
        source: "../../img/skin/bg-bottom-tab.png"
        anchors.fill: parent
    }

    function addList() {
        listModel.clear();//清空
        listModel.append({"name": qsTr("Computer"), "flag": "computer", "iconName": "computer"});
        listModel.append({"name": qsTr("Desktop"), "flag": "desktop", "iconName": "unity"});
        listModel.append({"name": qsTr("CPU"), "flag": "cpu", "iconName": "cpu"});
        listModel.append({"name": qsTr("Memory"), "flag": "memory", "iconName": "memory"});
        listModel.append({"name": qsTr("Board"), "flag": "board", "iconName": "board"});
        listModel.append({"name": qsTr("HardDisk"), "flag": "harddisk", "iconName": "harddisk"});
        listModel.append({"name": qsTr("NetworkCard"), "flag": "networkcard", "iconName": "network"});
        listModel.append({"name": qsTr("Monitor"), "flag": "monitor", "iconName": "monitor"});
        listModel.append({"name": qsTr("AudioCard"), "flag": "audiocard", "iconName": "memory"});
        var cdromNumber = systemdispatcher.getSingleInfo("Dvdnum", "cdrom");//光驱个数
        if(cdromNumber > 0) {//存在光驱时才会增加该页面的显示
            listModel.append({"name": qsTr("CD-ROM"), "flag": "cdrom", "iconName": "computer"});
        }
    }

    ListModel {
        id: listModel
        Component.onCompleted: {
            systemdispatcher.get_cdrom_info_qt();//获取光驱详细信息
            window.addList();
        }
    }
    Row {
        anchors {
            left: parent.left
            leftMargin: 2
        }
        //左边标题栏
        Rectangle {
            width: 150; height: window.height - 10
            anchors {
                top: parent.top
                topMargin: 10
            }
            color: "transparent"
            ListView {
                focus: true
                id: categories
                anchors.fill: parent
                model: listModel
//                footer: returnDelegate
                delegate: Others.InfoDelegate {
                    onSendFlag: {
                        if(flag == "computer") {
                            window.state = "ComputerPage";
                        }
                        else if(flag == "desktop") {
                            window.state = "DesktopPage";
                        }
                        else if(flag == "cpu") {
                            window.state = "CPUPage";
                        }
                        else if(flag == "board") {
                            window.state = "BiosPage";
                        }
                        else if(flag == "memory") {
                            window.state = "MemoryPage";
                        }
                        else if(flag == "harddisk") {
                            window.state = "HarddiskPage";
                        }
                        else if(flag == "networkcard") {
                            window.state = "NetworkPage";
                        }
                        else if(flag == "monitor") {
                            window.state = "MonitorPage";
                        }
                        else if(flag == "cdrom") {
                            window.state = "CDROMPage";
                        }
                        else if(flag == "audiocard") {
                            window.state = "AudioPage";
                        }
                    }
                }
                highlight: Rectangle { width: ListView.view.width - 2; color: "steelblue" }//选中后的深色块
                highlightMoveSpeed: 9999999
            }
//            Bars.ScrollBar {
//                scrollArea: categories; height: categories.height; width: 8
//                anchors.right: categories.right
//            }
        }

        //右边内容栏
        Item {
            width: window.width - 150 - 4; height: window.height
            Info.ComputerInfo {
                id: computerLayer
                width: parent.width
                height: parent.height
                visible: true
            }
            Info.DesktopInfo {
                id: desktopLayer
                width: parent.width
                height: parent.height
                visible: false
            }
            Info.CpuInfo {
                id: cpuLayer
                width: parent.width
                height: parent.height
                visible: false
            }
            Info.BoardInfo {
                id: biosLayer
                width: parent.width
                height: parent.height
                visible: false
            }
            Info.MemoryInfo {
                id: memoryLayer
                width: parent.width
                height: parent.height
                visible: false
            }
            Info.HardDiskInfo {
                id: hardLayer
                width: parent.width
                height: parent.height
                visible: false
            }
            Info.NetworkCardInfo {
                id: networkLayer
                width: parent.width
                height: parent.height
                visible: false
            }
            Info.MonitorInfo {
                id: monitorLayer
                width: parent.width
                height: parent.height
                visible: false
            }
            Info.AudioCardInfo {
                id: audioLayer
                width: parent.width
                height: parent.height
                visible: false
            }
            Info.CDROMInfo {
                id: cdromLayer
                width: parent.width
                height: parent.height
                visible: false
            }
        }
    }
//    Component {
//        id: returnDelegate
//        Item {
//            width: categories.width; height: 40
//            Row {
//                spacing: 10
//                anchors {
//                    left: parent.left; leftMargin: 15
//                    verticalCenter: parent.verticalCenter
//                }
//                Image {
//                    width: 30
//                    height: 20
//                    source: "../img/sysButton/reback.png"
//                    anchors.verticalCenter: parent.verticalCenter
//                }
//                Text {
//                    anchors.verticalCenter: parent.verticalCenter
//                    text: qsTr("Back")
//                    font { family: "Helvetica"; pixelSize: 14; bold: true }
//                }
//            }
//            MouseArea {
//                anchors.fill: parent
//                onClicked: pageStack.push(systemmessage);
//            }
//        }
//    }
    Rectangle { x: 150; height: window.height; width: 1; color: "#1790c9" }

    states: [
        State {
            name: "ComputerPage"
            PropertyChanges { target: computerLayer; visible: true }
            PropertyChanges { target: desktopLayer; visible: false }
            PropertyChanges { target: cpuLayer;  visible: false }
            PropertyChanges { target: biosLayer; visible: false }
            PropertyChanges { target: memoryLayer; visible: false }
            PropertyChanges { target: hardLayer; visible: false }
            PropertyChanges { target: networkLayer; visible: false }
            PropertyChanges { target: monitorLayer; visible: false }
            PropertyChanges { target: audioLayer; visible: false }
            PropertyChanges { target: cdromLayer; visible: false }
        },
        State {
            name: "DesktopPage"
            PropertyChanges { target: computerLayer; visible: false }
            PropertyChanges { target: desktopLayer; visible: true }
            PropertyChanges { target: cpuLayer;  visible: false }
            PropertyChanges { target: biosLayer; visible: false }
            PropertyChanges { target: memoryLayer; visible: false }
            PropertyChanges { target: hardLayer; visible: false }
            PropertyChanges { target: networkLayer; visible: false }
            PropertyChanges { target: monitorLayer; visible: false }
            PropertyChanges { target: audioLayer; visible: false }
            PropertyChanges { target: cdromLayer; visible: false }
        },
        State {
            name: "CPUPage"
            PropertyChanges { target: computerLayer; visible: false }
            PropertyChanges { target: desktopLayer; visible: false }
            PropertyChanges { target: cpuLayer;  visible: true }
            PropertyChanges { target: biosLayer; visible: false }
            PropertyChanges { target: memoryLayer; visible: false }
            PropertyChanges { target: hardLayer; visible: false }
            PropertyChanges { target: networkLayer; visible: false }
            PropertyChanges { target: monitorLayer; visible: false }
            PropertyChanges { target: audioLayer; visible: false }
            PropertyChanges { target: cdromLayer; visible: false }
        },
        State {
            name: "BiosPage"
            PropertyChanges { target: computerLayer; visible: false }
            PropertyChanges { target: desktopLayer; visible: false }
            PropertyChanges { target: cpuLayer;  visible: false }
            PropertyChanges { target: biosLayer; visible: true }
            PropertyChanges { target: memoryLayer; visible: false }
            PropertyChanges { target: hardLayer; visible: false }
            PropertyChanges { target: networkLayer; visible: false }
            PropertyChanges { target: monitorLayer; visible: false }
            PropertyChanges { target: audioLayer; visible: false }
            PropertyChanges { target: cdromLayer; visible: false }
        },
        State {
            name: "MemoryPage"
            PropertyChanges { target: computerLayer; visible: false }
            PropertyChanges { target: desktopLayer; visible: false }
            PropertyChanges { target: cpuLayer;  visible: false }
            PropertyChanges { target: biosLayer; visible: false }
            PropertyChanges { target: memoryLayer; visible: true }
            PropertyChanges { target: hardLayer; visible: false }
            PropertyChanges { target: networkLayer; visible: false }
            PropertyChanges { target: monitorLayer; visible: false }
            PropertyChanges { target: audioLayer; visible: false }
            PropertyChanges { target: cdromLayer; visible: false }
        },
        State {
            name: "HarddiskPage"
            PropertyChanges { target: computerLayer; visible: false }
            PropertyChanges { target: desktopLayer; visible: false }
            PropertyChanges { target: cpuLayer;  visible: false }
            PropertyChanges { target: biosLayer; visible: false }
            PropertyChanges { target: memoryLayer; visible: false }
            PropertyChanges { target: hardLayer; visible: true }
            PropertyChanges { target: networkLayer; visible: false }
            PropertyChanges { target: monitorLayer; visible: false }
            PropertyChanges { target: audioLayer; visible: false }
            PropertyChanges { target: cdromLayer; visible: false }
        },
        State {
            name: "NetworkPage"
            PropertyChanges { target: computerLayer; visible: false }
            PropertyChanges { target: desktopLayer; visible: false }
            PropertyChanges { target: cpuLayer;  visible: false }
            PropertyChanges { target: biosLayer; visible: false }
            PropertyChanges { target: memoryLayer; visible: false }
            PropertyChanges { target: hardLayer; visible: false }
            PropertyChanges { target: networkLayer; visible: true }
            PropertyChanges { target: monitorLayer; visible: false }
            PropertyChanges { target: audioLayer; visible: false }
            PropertyChanges { target: cdromLayer; visible: false }
        },
        State {
            name: "MonitorPage"
            PropertyChanges { target: computerLayer; visible: false }
            PropertyChanges { target: desktopLayer; visible: false }
            PropertyChanges { target: cpuLayer;  visible: false }
            PropertyChanges { target: biosLayer; visible: false }
            PropertyChanges { target: memoryLayer; visible: false }
            PropertyChanges { target: hardLayer; visible: false }
            PropertyChanges { target: networkLayer; visible: false }
            PropertyChanges { target: monitorLayer; visible: true }
            PropertyChanges { target: audioLayer; visible: false }
            PropertyChanges { target: cdromLayer; visible: false }
        },
        State {
            name: "AudioPage"
            PropertyChanges { target: computerLayer; visible: false }
            PropertyChanges { target: desktopLayer; visible: false }
            PropertyChanges { target: cpuLayer;  visible: false }
            PropertyChanges { target: biosLayer; visible: false }
            PropertyChanges { target: memoryLayer; visible: false }
            PropertyChanges { target: hardLayer; visible: false }
            PropertyChanges { target: networkLayer; visible: false }
            PropertyChanges { target: monitorLayer; visible: false }
            PropertyChanges { target: audioLayer; visible: true }
            PropertyChanges { target: cdromLayer; visible: false }
        },
        State {
            name: "CDROMPage"
            PropertyChanges { target: computerLayer; visible: false }
            PropertyChanges { target: desktopLayer; visible: false }
            PropertyChanges { target: cpuLayer;  visible: false }
            PropertyChanges { target: biosLayer; visible: false }
            PropertyChanges { target: memoryLayer; visible: false }
            PropertyChanges { target: hardLayer; visible: false }
            PropertyChanges { target: networkLayer; visible: false }
            PropertyChanges { target: monitorLayer; visible: false }
            PropertyChanges { target: audioLayer; visible: false }
            PropertyChanges { target: cdromLayer; visible: true }
        }
    ]
}
