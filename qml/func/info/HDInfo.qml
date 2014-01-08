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

/*------------------最多支持四个硬盘的显示------------------*/
Rectangle {
    id: home; width: parent.width; height: 475
    color: "transparent"
    property bool firstFlag: false
    property bool secondFlag: false
    property bool thirdFlag: false
    property bool fourthFlag: false
    property int itemNum: 6//每个模块的子项个数
    ListModel {id: firstModel}
    ListModel {id: secondModel}
    ListModel {id: thirdModel}
    ListModel {id: fourthModel}

    function show_several_harddisk(num)
    {
        var diskmodel = systemdispatcher.getHWSingleInfo("DiskProduct", "harddisk").split("<1_1>");
        var diskvendor = systemdispatcher.getHWSingleInfo("DiskVendor", "harddisk").split("<1_1>");
        var diskcapacity = systemdispatcher.getHWSingleInfo("DiskCapacity", "harddisk").split("<1_1>");
        var diskname = systemdispatcher.getHWSingleInfo("DiskName", "harddisk").split("<1_1>");
        var diskfw = systemdispatcher.getHWSingleInfo("DiskFw", "harddisk").split("<1_1>");
        var diskserial = systemdispatcher.getHWSingleInfo("DiskSerial", "harddisk").split("<1_1>");

        //--------------first--------------
        home.firstFlag = true;
        firstView.visible = true;
        firstModel.clear();
        firstModel.append({"title": qsTr("HDD Model: "), "result": diskmodel[0]});//硬盘型号：
        firstModel.append({"title": qsTr("HDD Vendor: "), "result": diskvendor[0]});//硬盘厂商：
        firstModel.append({"title": qsTr("HDD Capacity: "), "result": diskcapacity[0]});//硬盘容量：
        firstModel.append({"title": qsTr("Device Name: "), "result": diskname[0]});//设备名称：
        firstModel.append({"title": qsTr("Firmware Version: "), "result": diskfw[0]});//固件版本：
        firstModel.append({"title": qsTr("Serial Number: "), "result": diskserial[0]});//序列号：
        splitbar1.visible = true;
        logo1.visible = true;
        if(diskvendor[0] == "Western Digital") {
            logo1.source = "../../img/logo/Manufacturer/WDC.jpg";
        }
        else {
            logo1.source = InfoGroup.judgeName(diskvendor[0].toUpperCase()) ? ("../../img/logo/Manufacturer/" + diskvendor[0].toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
        }

        //--------------second--------------
        home.secondFlag = true;
        secondView.visible = true;
        secondModel.clear();
        secondModel.append({"title": qsTr("HDD Model: "), "result": diskmodel[1]});
        secondModel.append({"title": qsTr("HDD Vendor: "), "result": diskvendor[1]});
        secondModel.append({"title": qsTr("HDD Capacity: "), "result": diskcapacity[1]});
        secondModel.append({"title": qsTr("Device Name: "), "result": diskname[1]});
        secondModel.append({"title": qsTr("Firmware Version: "), "result": diskfw[1]});
        secondModel.append({"title": qsTr("Serial Number: "), "result": diskserial[1]});
        splitbar2.visible = true;
        logo2.visible = true;
        if(diskvendor[1] == "Western Digital") {
            logo2.source = "../../img/logo/Manufacturer/WDC.jpg";
        }
        else {
            logo2.source = InfoGroup.judgeName(diskvendor[1].toUpperCase()) ? ("../../img/logo/Manufacturer/" + diskvendor[1].toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
        }
        if(num == 2) {
            //(每个ListView子项的个数×子项高度 + (子项个数-1)×子项与子项的间隔 + 分隔条的上下间隔) × 内存条个数
            listItem.height = (home.itemNum*20 + (home.itemNum - 1)*10 + 10*2) *2;
        }
        else if(num >= 3) {
            //--------------third--------------
            home.thirdFlag = true;
            thirdView.visible = true;
            thirdModel.clear();
            thirdModel.append({"title": qsTr("HDD Model: "), "result": diskmodel[2]});
            thirdModel.append({"title": qsTr("HDD Vendor: "), "result": diskvendor[2]});
            thirdModel.append({"title": qsTr("HDD Capacity: "), "result": diskcapacity[2]});
            thirdModel.append({"title": qsTr("Device Name: "), "result": diskname[2]});
            thirdModel.append({"title": qsTr("Firmware Version: "), "result": diskfw[2]});
            thirdModel.append({"title": qsTr("Serial Number: "), "result": diskserial[2]});
            splitbar3.visible = true;
            logo3.visible = true;
            if(diskvendor[2] == "Western Digital") {
                logo3.source = "../../img/logo/Manufacturer/WDC.jpg";
            }
            else {
                logo3.source = InfoGroup.judgeName(diskvendor[2].toUpperCase()) ? ("../../img/logo/Manufacturer/" + diskvendor[2].toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
            }
            if(num == 3) {
                //(每个ListView子项的个数×子项高度 + (子项个数-1)×子项与子项的间隔 + 分隔条的上下间隔) × 内存条个数
                listItem.height = (home.itemNum*20 + (home.itemNum - 1)*10 + 10*2) *3;
            }
            else if(num == 4) {
                home.fourthFlag = true;
                fourthView.visible = true;
                fourthModel.clear();
                fourthModel.append({"title": qsTr("HDD Model: "), "result": diskmodel[3]});
                fourthModel.append({"title": qsTr("HDD Vendor: "), "result": diskvendor[3]});
                fourthModel.append({"title": qsTr("HDD Capacity: "), "result": diskcapacity[3]});
                fourthModel.append({"title": qsTr("Device Name: "), "result": diskname[3]});
                fourthModel.append({"title": qsTr("Firmware Version: "), "result": diskfw[3]});
                fourthModel.append({"title": qsTr("Serial Number: "), "result": diskserial[3]});
                splitbar4.visible = true;
                logo4.visible = true;
                if(diskvendor[3] == "Western Digital") {
                    logo4.source = "../../img/logo/Manufacturer/WDC.jpg";
                }
                else {
                    logo4.source = InfoGroup.judgeName(diskvendor[3].toUpperCase()) ? ("../../img/logo/Manufacturer/" + diskvendor[3].toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
                }
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
        systemdispatcher.get_harddisk_info_qt();//获取详细信息
        var num = systemdispatcher.getHWSingleInfo("DiskNum", "harddisk");
        if(num == 1) {
            home.firstFlag = true;
            firstView.visible = true;
            var vendorName = systemdispatcher.getHWSingleInfo("DiskVendor", "harddisk");
            firstModel.clear();
            firstModel.append({"title": qsTr("HDD Model: "), "result": systemdispatcher.getHWSingleInfo("DiskProduct", "harddisk")});
            firstModel.append({"title": qsTr("HDD Vendor: "), "result": vendorName});
            firstModel.append({"title": qsTr("HDD Capacity: "), "result": systemdispatcher.getHWSingleInfo("DiskCapacity", "harddisk")});
            firstModel.append({"title": qsTr("Device Name: "), "result": systemdispatcher.getHWSingleInfo("DiskName", "harddisk")});
            firstModel.append({"title": qsTr("Firmware Version: "), "result": systemdispatcher.getHWSingleInfo("DiskFw", "harddisk")});
            firstModel.append({"title": qsTr("Serial Number: "), "result": systemdispatcher.getHWSingleInfo("DiskSerial", "harddisk")});
            splitbar1.visible = true;
            logo1.visible = true;
            if(vendorName == "Western Digital") {
                logo1.source = "../../img/logo/Manufacturer/WDC.jpg";
            }
            else {
                logo1.source = InfoGroup.judgeName(vendorName.toUpperCase()) ? ("../../img/logo/Manufacturer/" + vendorName.toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
            }

            //(每个ListView子项的个数×子项高度 + (子项个数-1)×子项与子项的间隔 + 分隔条的上下间隔) × 硬盘个数
            listItem.height = home.itemNum*20 + (home.itemNum - 1)*10 + 10*2;
        }
        else if(num >= 2) {
            home.show_several_harddisk(num);
        }
    }

    Component {
        id: hddDelegate
        Row {
            spacing: 10
            Common.Label {
                text: title
                font.pixelSize: 14
                color: "#7a7a7a"
                width: 120
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
            text: qsTr("HDD Info")//硬盘信息
            font.bold: true
            font.pixelSize: 14
            color: "#383838"
        }
        Common.Separator {
            anchors.verticalCenter: parent.verticalCenter
            width: home.width - titlebar.width - 30 * 2
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
//                        height: home.firstFlag ? (6*20 + 5*10) : 0
                        model: firstModel
                        delegate: hddDelegate
                        visible: false
                        spacing: 10
                    }
                    Image {
                        id: logo1
                        visible: false
                        source: ""
                        anchors {
                            right: parent.right
//                            rightMargin: 30
                        }
                    }
                }

//                Rectangle {
//                    id: splitbar1
//                    width: 680 - 4 - 30*2
//                    height: 1; color: "#ccdadd"
//                    visible: false
//                }
                Common.Separator {
                    id: splitbar1
                    width: 680 - 4 - 30*2
                    visible: false
                }
                Item {
                    width: parent.width
                    height: home.secondFlag ? (home.itemNum*20 + (home.itemNum - 1)*10) : 0
                    ListView {
                        id: secondView
                        anchors.fill: parent
//                        width: parent.width
//                        height: home.secondFlag ? (6*20 + 5*10) : 0
                        model: secondModel
                        delegate: hddDelegate
                        visible: false
                        spacing: 10
                    }
                    Image {
                        id: logo2
                        visible: false
                        source: ""
                        anchors {
                            right: parent.right
//                            rightMargin: 30
                        }
                    }
                }
//                Rectangle {
//                    id: splitbar2
//                    width: 680 - 4 - 30*2
//                    height: 1; color: "#ccdadd"
//                    visible: false
//                }
                Common.Separator {
                    id: splitbar2
                    width: 680 - 4 - 30*2
                    visible: false
                }
                Item {
                    width: parent.width
                    height: home.thirdFlag ? (home.itemNum*20 + (home.itemNum - 1)*10) : 0
                    ListView {
                        id: thirdView
                        anchors.fill: parent
//                        width: parent.width
//                        height: home.thirdFlag ? (6*20 + 5*10) : 0
                        model: thirdModel
                        delegate: hddDelegate
                        visible: false
                        spacing: 10
                    }
                    Image {
                        id: logo3
                        visible: false
                        source: ""
                        anchors {
                            right: parent.right
//                            rightMargin: 30
                        }
                    }
                }
//                Rectangle {
//                    id: splitbar3
//                    width: 680 - 4 - 30*2
//                    height: 1; color: "#ccdadd"
//                    visible: false
//                }
                Common.Separator {
                    id: splitbar3
                    width: 680 - 4 - 30*2
                    visible: false
                }
                Item {
                    width: parent.width
                    height: home.fourthFlag ? (home.itemNum*20 + (home.itemNum - 1)*10) : 0
                    ListView {
                        id: fourthView
                        anchors.fill: parent
//                        width: parent.width
//                        height: home.fourthFlag ? (6*20 + 5*10) : 0
                        model: fourthModel
                        delegate: hddDelegate
                        visible: false
                        spacing: 10
                    }
                    Image {
                        id: logo4
                        visible: false
                        source: ""
                        anchors {
                            right: parent.right
//                            rightMargin: 30
                        }
                    }
                }
//                Rectangle {
//                    id: splitbar4
//                    width: 680 - 4 - 30*2
//                    height: 1; color: "#ccdadd"
//                    visible: false
//                }
                Common.Separator {
                    id: splitbar4
                    width: 680 - 4 - 30*2
                    visible: false
                }
            }
        }//Item
    }//ScrollArea
}
