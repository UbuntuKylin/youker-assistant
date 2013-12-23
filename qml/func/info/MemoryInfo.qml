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

/*------------------最多支持四个内存条的显示------------------*/
Rectangle {
    id: home; width: parent.width; height: 475
    color: "transparent"
    property bool firstFlag: false
    property bool secondFlag: false
    property bool thirdFlag: false
    property bool fourthFlag: false
    property int itemNum: 7//每个模块的子项个数
    ListModel {id: firstModel}
    ListModel {id: secondModel}
    ListModel {id: thirdModel}
    ListModel {id: fourthModel}

    function show_several_memory(num)
    {
        var slot = systemdispatcher.getSingleInfo("MemSlot", "memory").split("/");
        var product = systemdispatcher.getSingleInfo("MemProduct", "memory").split("/");
        var vendor = systemdispatcher.getSingleInfo("MemVendor", "memory").split("/");
        var serial = systemdispatcher.getSingleInfo("MemSerial", "memory").split("/");
        var sizeValue = systemdispatcher.getSingleInfo("MemSize", "memory").split("/");
        var widthValue = systemdispatcher.getSingleInfo("MemWidth", "memory").split("/");
        var info = systemdispatcher.getSingleInfo("MemInfo", "memory").split("/");
        //--------------first--------------
        home.firstFlag = true;
        firstView.visible = true;
        firstModel.clear();
        firstModel.append({"title": qsTr("Slot Number:"), "result": slot[0]});
        firstModel.append({"title": qsTr("Memory Model:"), "result": product[0]});
        firstModel.append({"title": qsTr("Vendor:"), "result": vendor[0]});
        firstModel.append({"title": qsTr("Serial:"), "result": serial[0]});
        firstModel.append({"title": qsTr("Size:"), "result": sizeValue[0]});
        firstModel.append({"title": qsTr("Data Width:"), "result": widthValue[0]});
        firstModel.append({"title": qsTr("Memory Info:"), "result": info[0]});
        splitbar1.visible = true;
        logo1.visible = true;
        logo1.source = InfoGroup.judgeName(vendor[0].toUpperCase()) ? ("../../img/logo/Manufacturer/" + vendor[0].toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
        //--------------second--------------
        home.secondFlag = true;
        secondView.visible = true;
        secondModel.clear();
        secondModel.append({"title": qsTr("Slot Number:"), "result": slot[1]});
        secondModel.append({"title": qsTr("Memory Model:"), "result": product[1]});
        secondModel.append({"title": qsTr("Vendor:"), "result": vendor[1]});
        secondModel.append({"title": qsTr("Serial:"), "result": serial[1]});
        secondModel.append({"title": qsTr("Size:"), "result": sizeValue[1]});
        secondModel.append({"title": qsTr("Data Width:"), "result": widthValue[1]});
        secondModel.append({"title": qsTr("Memory Info:"), "result": info[1]});
        splitbar2.visible = true;
        logo2.visible = true;
        logo2.source = InfoGroup.judgeName(vendor[1].toUpperCase()) ? ("../../img/logo/Manufacturer/" + vendor[1].toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
        if(num == 2) {
            //(每个ListView子项的个数×子项高度 + (子项个数-1)×子项与子项的间隔 + 分隔条的上下间隔) × 内存条个数
            listItem.height = (home.itemNum*20 + (home.itemNum - 1)*10 + 10*2) *2;
        }
        else if(num >= 3) {
            //--------------third--------------
            home.thirdFlag = true;
            thirdView.visible = true;
            thirdModel.clear();
            thirdModel.append({"title": qsTr("Slot Number:"), "result": slot[2]});
            thirdModel.append({"title": qsTr("Memory Model:"), "result": product[2]});
            thirdModel.append({"title": qsTr("Vendor:"), "result": vendor[2]});
            thirdModel.append({"title": qsTr("Serial:"), "result": serial[2]});
            thirdModel.append({"title": qsTr("Size:"), "result": sizeValue[2]});
            thirdModel.append({"title": qsTr("Data Width:"), "result": widthValue[2]});
            thirdModel.append({"title": qsTr("Memory Info:"), "result": info[2]});
            splitbar3.visible = true;
            logo3.visible = true;
            logo3.source = InfoGroup.judgeName(vendor[2].toUpperCase()) ? ("../../img/logo/Manufacturer/" + vendor[2].toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
            if(num == 3) {
                //(每个ListView子项的个数×子项高度 + (子项个数-1)×子项与子项的间隔 + 分隔条的上下间隔) × 内存条个数
                listItem.height = (home.itemNum*20 + (home.itemNum - 1)*10 + 10*2) *3;
            }
            else if(num == 4) {
                home.fourthFlag = true;
                fourthView.visible = true;
                fourthModel.clear();
                fourthModel.append({"title": qsTr("Slot Number:"), "result": slot[3]});
                fourthModel.append({"title": qsTr("Memory Model:"), "result": product[3]});
                fourthModel.append({"title": qsTr("Vendor:"), "result": vendor[3]});
                fourthModel.append({"title": qsTr("Serial:"), "result": serial[3]});
                fourthModel.append({"title": qsTr("Size:"), "result": sizeValue[3]});
                fourthModel.append({"title": qsTr("Data Width:"), "result": widthValue[3]});
                fourthModel.append({"title": qsTr("Memory Info:"), "result": info[3]});
                splitbar4.visible = true;
                logo4.visible = true;
                logo4.source = InfoGroup.judgeName(vendor[3].toUpperCase()) ? ("../../img/logo/Manufacturer/" + vendor[3].toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
                //(每个ListView子项的个数×子项高度 + (子项个数-1)×子项与子项的间隔 + 分隔条的上下间隔) × 内存条个数
                listItem.height = (home.itemNum*20 + (home.itemNum - 1)*10 + 10*2) *4;
            }
        }
    }


    Component.onCompleted: {
        home.firstFlag = false;
        home.secondFlag = false;
        home.thirdFlag = false;
        home.fourthFlag = false;
        systemdispatcher.get_memory_info_qt();//获取详细信息
        var num = systemdispatcher.getSingleInfo("Memnum", "memory");
        if(num == 1) {
            home.firstFlag = true;
            firstView.visible = true;
            var vendorName = systemdispatcher.getSingleInfo("MemVendor", "memory");
            firstModel.clear();
            firstModel.append({"title": qsTr("Slot Number:"), "result": systemdispatcher.getSingleInfo("MemSlot", "memory")});//插槽号：
            firstModel.append({"title": qsTr("Memory Model:"), "result": systemdispatcher.getSingleInfo("MemProduct", "memory")});//内存型号：
            firstModel.append({"title": qsTr("Vendor:"), "result": vendorName});//制造商：
            firstModel.append({"title": qsTr("Serial Number:"), "result": systemdispatcher.getSingleInfo("MemSerial", "memory")});//序列号：
            firstModel.append({"title": qsTr("Size:"), "result": systemdispatcher.getSingleInfo("MemSize", "memory")});//内存大小：
            firstModel.append({"title": qsTr("Data Width:"), "result": systemdispatcher.getSingleInfo("MemWidth", "memory")});//数据宽度：
            firstModel.append({"title": qsTr("Memory Info:"), "result": systemdispatcher.getSingleInfo("MemInfo", "memory")});//内存条信息：
            splitbar1.visible = true;
            logo1.visible = true;
            logo1.source = InfoGroup.judgeName(vendorName.toUpperCase()) ? ("../../img/logo/Manufacturer/" + vendorName.toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
            //(每个ListView子项的个数×子项高度 + (子项个数-1)×子项与子项的间隔 + 分隔条的上下间隔) × 内存条个数
            listItem.height = home.itemNum*20 + (home.itemNum - 1)*10 + 10*2;
        }
        else if(num >= 2){
            home.show_several_memory(num);
        }
    }

    Component {
        id: memoryDelegate
        Row {
            spacing: 10
            Common.Label {
                text: title
                font.pixelSize: 14
                color: "#7a7a7a"
                width: 100
                height: 20
            }
            Text {
                id: slotText
                text: result
                font.pixelSize: 14
                color: "#7a7a7a"
                height: 20
            }
        }
    }

    Row {
        id: titleRow
        anchors {
            top: parent.top
            topMargin: 40
            left: parent.left
            leftMargin: 30
        }
        Common.Label {
            id: titlebar
            text: qsTr("Memory Information")//内存信息
            font.bold: true
            font.pixelSize: 14
            color: "#383838"
        }
        Rectangle {width: home.width - titlebar.width - 30 * 2
            anchors.verticalCenter: parent.verticalCenter
            height: 1; color: "#ccdadd"
        }
    }
    Common.ScrollArea {
        frame:false
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: titleRow.bottom
        anchors.topMargin: 20
        height: 398
        width: 680 - 4
        Item {
            id: listItem
            width: parent.width
            height: 0
            Column {
                spacing: 10
                anchors {
                    left: parent.left
                    leftMargin: 30
                }
                Item {
                    width: parent.width
                    height: home.firstFlag ? (home.itemNum*20 + (home.itemNum - 1)*10) : 0
                    ListView {
                        id: firstView
                        anchors.fill: parent
//                        width: parent.width
//                        height: home.firstFlag ? (7*20 + 6*10) : 0
                        model: firstModel
                        delegate: memoryDelegate
                        visible: false
                        spacing: 10
                    }
                    Image {
                        id: logo1
                        visible: false
                        source: ""
                        anchors {
                            right: parent.right
                            rightMargin: 30
                        }
                    }
                }
                Common.Separator {
                    id: splitbar1
                    width: 680 - 4 - 30*2
                    visible: false
                }

//                Rectangle {
//                    id: splitbar1
//                    width: 680 - 4 - 30*2
//                    height: 1; color: "#ccdadd"
//                    visible: false
//                }
                Item {
                    width: parent.width
                    height: home.secondFlag ? (home.itemNum*20 + (home.itemNum - 1)*10) : 0
                    ListView {
                        id: secondView
                        anchors.fill: parent
//                        width: parent.width
//                        height: home.secondFlag ? (7*20 + 6*10) : 0
                        model: secondModel
                        delegate: memoryDelegate
                        visible: false
                        spacing: 10
                    }
                    Image {
                        id: logo2
                        visible: false
                        source: ""
                        anchors {
                            right: parent.right
                            rightMargin: 30
                        }
                    }
                }
                Common.Separator {
                    id: splitbar2
                    width: 680 - 4 - 30*2
                    visible: false
                }
//                Rectangle {
//                    id: splitbar2
//                    width: 680 - 4 - 30*2
//                    height: 1; color: "#ccdadd"
//                    visible: false
//                }
                Item {
                    width: parent.width
                    height: home.thirdFlag ? (home.itemNum*20 + (home.itemNum - 1)*10) : 0
                    ListView {
                        id: thirdView
                        anchors.fill: parent
//                        width: parent.width
//                        height: home.thirdFlag ? (7*20 + 6*10) : 0
                        model: thirdModel
                        delegate: memoryDelegate
                        visible: false
                        spacing: 10
                    }
                    Image {
                        id: logo3
                        visible: false
                        source: ""
                        anchors {
                            right: parent.right
                            rightMargin: 30
                        }
                    }
                }
                Common.Separator {
                    id: splitbar3
                    width: 680 - 4 - 30*2
                    visible: false
                }
//                Rectangle {
//                    id: splitbar3
//                    width: 680 - 4 - 30*2
//                    height: 1; color: "#ccdadd"
//                    visible: false
//                }
                Item {
                    width: parent.width
                    height: home.fourthFlag ? (home.itemNum*20 + (home.itemNum - 1)*10) : 0
                    ListView {
                        id: fourthView
                        anchors.fill: parent
//                        width: parent.width
//                        height: home.fourthFlag ? (7*20 + 6*10) : 0
                        model: fourthModel
                        delegate: memoryDelegate
                        visible: false
                        spacing: 10
                    }
                    Image {
                        id: logo4
                        visible: false
                        source: ""
                        anchors {
                            right: parent.right
                            rightMargin: 30
                        }
                    }
                }
                Common.Separator {
                    id: splitbar4
                    width: 680 - 4 - 30*2
                    visible: false
                }
//                Rectangle {
//                    id: splitbar4
//                    width: 680 - 4 - 30*2
//                    height: 1; color: "#ccdadd"
//                    visible: false
//                }
            }
        }//Item
    }//ScrollArea
}
