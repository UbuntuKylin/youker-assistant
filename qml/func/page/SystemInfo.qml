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
import "../info" as Info
import "../others" as Others
import "../common" as Common

Rectangle {
    id: window
    width: parent.width; height: 476
    property string current_flag: "computer"

    //背景
    Image {
        source: "../../img/skin/bg-middle.png"
        anchors.fill: parent
    }

    function currentChanged(curIndex) {
        content.currentChanged(curIndex);
    }

    function addList() {
        listModel.clear();//清空
        listModel.append({"name": qsTr("Computer"), "flag": "computer", "iconName": "computer"});//电脑概述
        listModel.append({"name": qsTr("Desktop"), "flag": "desktop", "iconName": "unity"});//桌面
        listModel.append({"name": qsTr("CPU"), "flag": "cpu", "iconName": "cpu"});//中央处理器
        listModel.append({"name": qsTr("Memory"), "flag": "memory", "iconName": "memory"});//内存条
        listModel.append({"name": qsTr("Motherboard"), "flag": "board", "iconName": "board"});//主板
        listModel.append({"name": qsTr("HD"), "flag": "harddisk", "iconName": "harddisk"});//硬盘
        listModel.append({"name": qsTr("NIC"), "flag": "networkcard", "iconName": "network"});//网卡
        listModel.append({"name": qsTr("VGA"), "flag": "monitor", "iconName": "monitor"});//显卡
        listModel.append({"name": qsTr("SB"), "flag": "audiocard", "iconName": "audio"});//声卡
        var cdromNumber = systemdispatcher.getHWSingleInfo("Dvdnum", "cdrom");//光驱个数
        if(cdromNumber > 0) {//存在光驱时才会增加该页面的显示
            listModel.append({"name": qsTr("CD-ROM"), "flag": "cdrom", "iconName": "cdrom"});//光驱
        }
        if (sessiondispatcher.judge_power_is_exists_qt() === true) {
            listModel.append({"name": qsTr("Battery"), "flag": "battery", "iconName": "battery"});//电源
        }
        listModel.append({"name": qsTr("Device Driver"), "flag": "drive", "iconName": "drive"});//设备驱动
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
            id: toolbar
            width: 150; height: window.height - 10
            anchors {
                top: parent.top
                topMargin: 10
            }
            color: "transparent"

            property int current: 0
            onCurrentChanged:setCurrentToolBtn()
            function setCurrentToolBtn() {
                for(var i = 0; i < toolbar.children.length; i++) {
                    toolbar.children[i].state = (toolbar.current == i ? 'checked' : 'leave');
                }
                window.currentChanged(toolbar.current);
            }

            ListView {
                focus: true
                id: categories
                anchors.fill: parent
                model: listModel
//                footer: returnDelegate
                delegate: Others.InfoDelegate {
                    onSendIndex: {
                        window.current_flag = flag;
                        toolbar.current=myindex;
                        sessiondispatcher.let_detail_info_page_to_update_data(window.current_flag);//tell page to update data
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

        Rectangle
        {
            id:content
            width: window.width - 150 - 4; height: window.height
            property int current: 0
            function currentChanged(curIndex)
            {
                if (window.current_flag == "battery" && curIndex !== 10) {
                    content.children[10].state='active';
                    content.children[current].state='hide';
                    current = 10;
                }
                else if (window.current_flag == "drive" && curIndex !== 11) {
                    content.children[11].state='active';
                    content.children[current].state='hide';
                    current = 11;
                }
                else {
                    content.children[curIndex].state='active';
                    content.children[current].state='hide';
                    current = curIndex;
                }
            }
            Common.ShowHide {
                anchors.fill: parent
                state:"active"
                Info.ComputerInfo {
                    width: parent.width
                    height: parent.height
                }
            }
            Common.ShowHide {
                anchors.fill: parent
                Info.DesktopInfo {
                    width: parent.width
                    height: parent.height
                }
            }
            Common.ShowHide {
                anchors.fill: parent
                Info.CpuInfo {
                    width: parent.width
                    height: parent.height
                }
            }
            Common.ShowHide {
                anchors.fill: parent
                Info.MemoryInfo {
                    width: parent.width
                    height: parent.height
                }
            }
            Common.ShowHide {
                anchors.fill: parent
                Info.BoardInfo {
                    width: parent.width
                    height: parent.height
                }
            }
            Common.ShowHide {
                anchors.fill: parent
                Info.HDInfo {
                    width: parent.width
                    height: parent.height
                }
            }
            Common.ShowHide {
                anchors.fill: parent
                Info.NICInfo {}
            }
            Common.ShowHide {
                anchors.fill: parent
                Info.MonitorInfo {
                    width: parent.width
                    height: parent.height
                }
            }
            Common.ShowHide {
                anchors.fill: parent
                Info.AudioInfo {
                    width: parent.width
                    height: parent.height
                }
            }
            Common.ShowHide {
                anchors.fill: parent
                Info.CDROMInfo {
                    width: parent.width
                    height: parent.height
                }
            }
            Common.ShowHide {
                anchors.fill: parent
                Info.BatteryInfo {
                    width: parent.width
                    height: parent.height
                }
            }
            Common.ShowHide {
                anchors.fill: parent
                Info.DriveInfo {
                    width: parent.width
                    height: parent.height
                }
            }
        }
    }
    Rectangle { x: 150; height: window.height; width: 1; color: "#1790c9" }
}
