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
/*------------------最多支持两个硬盘的显示------------------*/

Rectangle {
    id: home; width: parent.width; height: 475
    color: "transparent"

    property bool firstFlag: false
    property bool secondFlag: false
    property bool thirdFlag: false
    property bool fourthFlag: false
    ListModel {id: firstModel}
    ListModel {id: secondModel}
    ListModel {id: thirdModel}
    ListModel {id: fourthModel}

    function show_several_harddisk(num)
    {
//        var diskmodel = systemdispatcher.getSingleInfo("DiskProduct", "harddisk").split("/");
//        var diskvendor = systemdispatcher.getSingleInfo("DiskVendor", "harddisk").split("/");
//        var diskcapacity = systemdispatcher.getSingleInfo("DiskCapacity", "harddisk").split("/");
//        var diskname = systemdispatcher.getSingleInfo("DiskName", "harddisk").split("/");
//        var diskfw = systemdispatcher.getSingleInfo("DiskFw", "harddisk").split("/");
//        var diskserial = systemdispatcher.getSingleInfo("DiskSerial", "harddisk").split("/");

//        splitbar.visible = true;
//        modelLabel2.visible = true;
//        vendorLabel2.visible = true;
//        capacityLabel2.visible = true;
//        deviceLabel2.visible = true;
//        fwLabel2.visible = true;
//        serialLabel2.visible = true;

//        for (var i=0; i < num; i++) {
//            if(i == 0) {
//                firstlogo.source = "../../img/logo/Manufacturer/" + diskvendor[0].toUpperCase() + ".jpg";
//                modelText.text = diskmodel[0];
//                vendorText.text = diskvendor[0];
//                capacityText.text = diskcapacity[0];
//                deviceText.text = diskname[0];
//                fwText.text = diskfw[0];
//                serialText.text = diskserial[0];
//            }
//            else if(i == 1) {
//                secondlogo.source = "../../img/logo/Manufacturer/" + diskvendor[1].toUpperCase() + ".jpg";
//                modelText2.text = diskmodel[1];
//                vendorText2.text = diskvendor[1];
//                capacityText2.text = diskcapacity[1];
//                deviceText2.text = diskname[1];
//                fwText2.text = diskfw[1];
//                serialText2.text = diskserial[1];
//            }
//        }
    }


    Component.onCompleted: {
        home.firstFlag = false;
        home.secondFlag = false;

        systemdispatcher.get_harddisk_info_qt();//获取详细信息
        var num = systemdispatcher.getSingleInfo("DiskNum", "harddisk");
        if(num == 1) {
            home.firstFlag = true;
            firstView.visible = true;
            firstModel.clear();
            firstModel.append({"title": qsTr("HardDisk Model:"), "result": systemdispatcher.getSingleInfo("DiskProduct", "harddisk")});
            firstModel.append({"title": qsTr("HardDisk Vendor:"), "result": systemdispatcher.getSingleInfo("DiskVendor", "harddisk")});
            firstModel.append({"title": qsTr("HardDisk Capacity:"), "result": systemdispatcher.getSingleInfo("DiskCapacity", "harddisk")});
            firstModel.append({"title": qsTr("Device Name:"), "result": systemdispatcher.getSingleInfo("DiskName", "harddisk")});
            firstModel.append({"title": qsTr("Firmware Version:"), "result": systemdispatcher.getSingleInfo("DiskFw", "harddisk")});
            firstModel.append({"title": qsTr("Serial:"), "result": systemdispatcher.getSingleInfo("DiskSerial", "harddisk")});
            splitbar1.visible = true;
            logo1.visible = true;
            logo1.source = "../../img/logo/Manufacturer/" + systemdispatcher.getSingleInfo("DiskVendor", "harddisk").toUpperCase() + ".jpg";



            home.secondFlag = true;
            secondView.visible = true;
            secondModel.clear();
            secondModel.append({"title": qsTr("HardDisk Model:"), "result": systemdispatcher.getSingleInfo("DiskProduct", "harddisk")});
            secondModel.append({"title": qsTr("HardDisk Vendor:"), "result": systemdispatcher.getSingleInfo("DiskVendor", "harddisk")});
            secondModel.append({"title": qsTr("HardDisk Capacity:"), "result": systemdispatcher.getSingleInfo("DiskCapacity", "harddisk")});
            secondModel.append({"title": qsTr("Device Name:"), "result": systemdispatcher.getSingleInfo("DiskName", "harddisk")});
            secondModel.append({"title": qsTr("Firmware Version:"), "result": systemdispatcher.getSingleInfo("DiskFw", "harddisk")});
            secondModel.append({"title": qsTr("Serial:"), "result": systemdispatcher.getSingleInfo("DiskSerial", "harddisk")});
            splitbar2.visible = true;
            logo2.visible = true;
            logo2.source = "../../img/logo/Manufacturer/" + systemdispatcher.getSingleInfo("DiskVendor", "harddisk").toUpperCase() + ".jpg";


            home.thirdFlag = true;
            thirdView.visible = true;
            thirdModel.clear();
            thirdModel.append({"title": qsTr("HardDisk Model:"), "result": systemdispatcher.getSingleInfo("DiskProduct", "harddisk")});
            thirdModel.append({"title": qsTr("HardDisk Vendor:"), "result": systemdispatcher.getSingleInfo("DiskVendor", "harddisk")});
            thirdModel.append({"title": qsTr("HardDisk Capacity:"), "result": systemdispatcher.getSingleInfo("DiskCapacity", "harddisk")});
            thirdModel.append({"title": qsTr("Device Name:"), "result": systemdispatcher.getSingleInfo("DiskName", "harddisk")});
            thirdModel.append({"title": qsTr("Firmware Version:"), "result": systemdispatcher.getSingleInfo("DiskFw", "harddisk")});
            thirdModel.append({"title": qsTr("Serial:"), "result": systemdispatcher.getSingleInfo("DiskSerial", "harddisk")});
            splitbar3.visible = true;
            logo3.visible = true;
            logo3.source = "../../img/logo/Manufacturer/" + systemdispatcher.getSingleInfo("DiskVendor", "harddisk").toUpperCase() + ".jpg";


            home.fourthFlag = true;
            fourthView.visible = true;
            fourthModel.clear();
            fourthModel.append({"title": qsTr("HardDisk Model:"), "result": systemdispatcher.getSingleInfo("DiskProduct", "harddisk")});
            fourthModel.append({"title": qsTr("HardDisk Vendor:"), "result": systemdispatcher.getSingleInfo("DiskVendor", "harddisk")});
            fourthModel.append({"title": qsTr("HardDisk Capacity:"), "result": systemdispatcher.getSingleInfo("DiskCapacity", "harddisk")});
            fourthModel.append({"title": qsTr("Device Name:"), "result": systemdispatcher.getSingleInfo("DiskName", "harddisk")});
            fourthModel.append({"title": qsTr("Firmware Version:"), "result": systemdispatcher.getSingleInfo("DiskFw", "harddisk")});
            fourthModel.append({"title": qsTr("Serial:"), "result": systemdispatcher.getSingleInfo("DiskSerial", "harddisk")});
            splitbar4.visible = true;
            logo4.visible = true;
            logo4.source = "../../img/logo/Manufacturer/" + systemdispatcher.getSingleInfo("DiskVendor", "harddisk").toUpperCase() + ".jpg";

            //(每个ListView子项的个数×子项高度 + (子项个数-1)×子项与子项的间隔 + 分隔条的上下间隔) × 硬盘个数
            listItem.height = (6*20 + 5*10 + 10*2) *4;
        }
        else if(num >= 2){
            home.show_several_harddisk(2);
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
            text: qsTr("HardDisk information")//硬盘信息
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
        height: 390
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
                    height: home.firstFlag ? (6*20 + 5*10) : 0
                    ListView {
                        id: firstView
                        anchors.fill: parent
//                        width: parent.width
//                        height: home.firstFlag ? (6*20 + 5*10) : 0
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

                Rectangle {
                    id: splitbar1
                    width: 680 - 4 - 30*2
                    height: 1; color: "#ccdadd"
                    visible: false
                }
                Item {
                    width: parent.width
                    height: home.secondFlag ? (6*20 + 5*10) : 0
                    ListView {
                        id: secondView
                        anchors.fill: parent
//                        width: parent.width
//                        height: home.secondFlag ? (6*20 + 5*10) : 0
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
                Rectangle {
                    id: splitbar2
                    width: 680 - 4 - 30*2
                    height: 1; color: "#ccdadd"
                    visible: false
                }
                Item {
                    width: parent.width
                    height: home.thirdFlag ? (6*20 + 5*10) : 0
                    ListView {
                        id: thirdView
                        anchors.fill: parent
//                        width: parent.width
//                        height: home.thirdFlag ? (6*20 + 5*10) : 0
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
                Rectangle {
                    id: splitbar3
                    width: 680 - 4 - 30*2
                    height: 1; color: "#ccdadd"
                    visible: false
                }
                Item {
                    width: parent.width
                    height: home.fourthFlag ? (6*20 + 5*10) : 0
                    ListView {
                        id: fourthView
                        anchors.fill: parent
//                        width: parent.width
//                        height: home.fourthFlag ? (6*20 + 5*10) : 0
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
                Rectangle {
                    id: splitbar4
                    width: 680 - 4 - 30*2
                    height: 1; color: "#ccdadd"
                    visible: false
                }
            }
        }//Item
    }//ScrollArea
}



























//Rectangle {
//    id: home; width: parent.width; height: 475
//    color: "transparent"

//    function show_several_harddisk(num)
//    {
//        var diskmodel = systemdispatcher.getSingleInfo("DiskProduct", "harddisk").split("/");
//        var diskvendor = systemdispatcher.getSingleInfo("DiskVendor", "harddisk").split("/");
//        var diskcapacity = systemdispatcher.getSingleInfo("DiskCapacity", "harddisk").split("/");
//        var diskname = systemdispatcher.getSingleInfo("DiskName", "harddisk").split("/");
//        var diskfw = systemdispatcher.getSingleInfo("DiskFw", "harddisk").split("/");
//        var diskserial = systemdispatcher.getSingleInfo("DiskSerial", "harddisk").split("/");

//        splitbar.visible = true;
//        modelLabel2.visible = true;
//        vendorLabel2.visible = true;
//        capacityLabel2.visible = true;
//        deviceLabel2.visible = true;
//        fwLabel2.visible = true;
//        serialLabel2.visible = true;

//        for (var i=0; i < num; i++) {
//            if(i == 0) {
//                firstlogo.source = "../../img/logo/Manufacturer/" + diskvendor[0].toUpperCase() + ".jpg";
//                modelText.text = diskmodel[0];
//                vendorText.text = diskvendor[0];
//                capacityText.text = diskcapacity[0];
//                deviceText.text = diskname[0];
//                fwText.text = diskfw[0];
//                serialText.text = diskserial[0];
//            }
//            else if(i == 1) {
//                secondlogo.source = "../../img/logo/Manufacturer/" + diskvendor[1].toUpperCase() + ".jpg";
//                modelText2.text = diskmodel[1];
//                vendorText2.text = diskvendor[1];
//                capacityText2.text = diskcapacity[1];
//                deviceText2.text = diskname[1];
//                fwText2.text = diskfw[1];
//                serialText2.text = diskserial[1];
//            }
//        }
//    }

//    Component.onCompleted: {
//        systemdispatcher.get_harddisk_info_qt();//获取详细信息
//        var num = systemdispatcher.getSingleInfo("DiskNum", "harddisk");
//        if(num == 1) {
//            firstlogo.source = "../../img/logo/Manufacturer/" + systemdispatcher.getSingleInfo("DiskVendor", "harddisk").toUpperCase() + ".jpg";
//            modelText.text = systemdispatcher.getSingleInfo("DiskProduct", "harddisk");
//            vendorText.text = systemdispatcher.getSingleInfo("DiskVendor", "harddisk");
//            capacityText.text = systemdispatcher.getSingleInfo("DiskCapacity", "harddisk");
//            deviceText.text = systemdispatcher.getSingleInfo("DiskName", "harddisk");
//            fwText.text = systemdispatcher.getSingleInfo("DiskFw", "harddisk");
//            serialText.text = systemdispatcher.getSingleInfo("DiskSerial", "harddisk");

//            splitbar.visible = false;
//            modelLabel2.visible = false;
//            vendorLabel2.visible = false;
//            capacityLabel2.visible = false;
//            deviceLabel2.visible = false;
//            fwLabel2.visible = false;
//            serialLabel2.visible = false;
//        }
//        else if(num >= 2){
//            home.show_several_harddisk(2);
//        }
//    }

//    Column {
//        anchors {
//            top: parent.top
//            topMargin: 20
//            left: parent.left
//            leftMargin: 30
//        }
//        spacing: 20

//        Row {
//            Common.Label {
//                id: basictitle
//                text: qsTr("HardDisk information")//硬盘信息
//                font.bold: true
//                font.pixelSize: 14
//                color: "#383838"
//            }
//            Rectangle {width: home.width - basictitle.width - 30 * 2
//                anchors.verticalCenter: parent.verticalCenter
//                height: 1; color: "#ccdadd"
//            }
//        }
//        Column {
//            anchors.left: parent.left
//            anchors.leftMargin: 20
//            spacing: 10
//            Row {
//                spacing: 10
//                Common.Label {
//                    text: qsTr("HardDisk Model:")//硬盘型号：
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                    width: 140
//                }
//                Text {
//                    id: modelText
//                    text: ""//systemdispatcher.getSingleInfo("DiskProduct")
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                }
//            }
//            Row {
//                spacing: 10
//                Common.Label {
//                    text: qsTr("HardDisk Vendor:")//硬盘厂商：
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                    width: 140
//                }
//                Text {
//                    id: vendorText
//                    text: ""//systemdispatcher.getSingleInfo("DiskVendor")
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                }
//            }
//            Row {
//                spacing: 10
//                Common.Label {
//                    text: qsTr("HardDisk Capacity:")//硬盘容量：
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                    width: 140
//                }
//                Text {
//                    id: capacityText
//                    text: ""//systemdispatcher.getSingleInfo("DiskCapacity")
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                }
//            }
//            Row {
//                spacing: 10
//                Common.Label {
//                    text: qsTr("Device Name:")//设备名称：
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                    width: 140
//                }
//                Text {
//                    id: deviceText
//                    text: ""//systemdispatcher.getSingleInfo("DiskName")
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                }
//            }
//            Row {
//                spacing: 10
//                Common.Label {
//                    text: qsTr("Firmware Version:")//固件版本：
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                    width: 140
//                }
//                Text {
//                    id: fwText
//                    text: ""//systemdispatcher.getSingleInfo("DiskFw")
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                }
//            }
//            Row {
//                spacing: 10
//                Common.Label {
//                    text: qsTr("Serial:")//序列号：
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                    width: 140
//                }
//                Text {
//                    id: serialText
//                    text: ""//systemdispatcher.getSingleInfo("BoaSerial")
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                }
//            }


//            Rectangle {
//                id: splitbar
//                width: home.width - 30 * 2
//                height: 1; color: "#ccdadd"
//            }
//            Row {
//                spacing: 10
//                Common.Label {
//                    id: modelLabel2
//                    text: qsTr("HardDisk Model:")//硬盘型号：
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                    width: 140
//                }
//                Text {
//                    id: modelText2
//                    text: ""//systemdispatcher.getSingleInfo("DiskProduct")
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                }
//            }
//            Row {
//                spacing: 10
//                Common.Label {
//                    id: vendorLabel2
//                    text: qsTr("HardDisk Vendor:")//硬盘厂商：
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                    width: 140
//                }
//                Text {
//                    id: vendorText2
//                    text: ""//systemdispatcher.getSingleInfo("DiskVendor")
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                }
//            }
//            Row {
//                spacing: 10
//                Common.Label {
//                    id: capacityLabel2
//                    text: qsTr("HardDisk Capacity:")//硬盘容量：
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                    width: 140
//                }
//                Text {
//                    id: capacityText2
//                    text: ""//systemdispatcher.getSingleInfo("DiskCapacity")
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                }
//            }
//            Row {
//                spacing: 10
//                Common.Label {
//                    id: deviceLabel2
//                    text: qsTr("Device Name:")//设备名称：
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                    width: 140
//                }
//                Text {
//                    id: deviceText2
//                    text: ""//systemdispatcher.getSingleInfo("DiskName")
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                }
//            }
//            Row {
//                spacing: 10
//                Common.Label {
//                    id: fwLabel2
//                    text: qsTr("Firmware Version:")//固件版本：
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                    width: 140
//                }
//                Text {
//                    id: fwText2
//                    text: ""//systemdispatcher.getSingleInfo("DiskFw")
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                }
//            }
//            Row {
//                spacing: 10
//                Common.Label {
//                    id: serialLabel2
//                    text: qsTr("Serial:")//序列号：
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                    width: 140
//                }
//                Text {
//                    id: serialText2
//                    text: ""//systemdispatcher.getSingleInfo("BoaSerial")
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                }
//            }
//        }
//    }
//    //logo
//    Image {
//        id: firstlogo
//        source: ""
//        anchors {
//            top: parent.top
//            topMargin: 50
//            right: parent.right
//            rightMargin: 30
//        }
//    }
//    //logo
//    Image {
//        id: secondlogo
//        source: ""
//        anchors {
//            top: parent.top
//            topMargin: 200
//            right: parent.right
//            rightMargin: 30
//        }
//    }
//}
