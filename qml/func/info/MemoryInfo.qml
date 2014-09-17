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

/*------------------最多支持四个内存条的显示------------------*/
Rectangle {
    id: home; width: parent.width; height: 476
//    color: "transparent"
//    color: "#eeedf0"
    property bool firstFlag: false
    property bool secondFlag: false
    property bool thirdFlag: false
    property bool fourthFlag: false
    property int itemNum: 7//每个模块的子项个数
    ListModel {id: firstModel}
    ListModel {id: secondModel}
    ListModel {id: thirdModel}
    ListModel {id: fourthModel}

    property string homepath
    Component.onCompleted: {
        home.homepath = sessiondispatcher.getHomePath();
    }

    function show_several_memory(num)
    {
        var slot = systemdispatcher.getHWSingleInfo("MemSlot", "memory").split("<1_1>");
        var product = systemdispatcher.getHWSingleInfo("MemProduct", "memory").split("<1_1>");
        var vendor = systemdispatcher.getHWSingleInfo("MemVendor", "memory").split("<1_1>");
        var serial = systemdispatcher.getHWSingleInfo("MemSerial", "memory").split("<1_1>");
        var sizeValue = systemdispatcher.getHWSingleInfo("MemSize", "memory").split("<1_1>");
        var widthValue = systemdispatcher.getHWSingleInfo("MemWidth", "memory").split("<1_1>");
        var info = systemdispatcher.getHWSingleInfo("MemInfo", "memory").split("<1_1>");
        //--------------first--------------
        home.firstFlag = true;
        firstView.visible = true;
        firstModel.clear();
        firstModel.append({"title": qsTr("Slot Number: "), "result": slot[0]});//插槽号：
        firstModel.append({"title": qsTr("Memory Model: "), "result": product[0]});//内存型号：
        firstModel.append({"title": qsTr("Vendor: "), "result": vendor[0]});//制造商：
        firstModel.append({"title": qsTr("Serial Number: "), "result": serial[0]});//序列号：
        firstModel.append({"title": qsTr("Memory Size: "), "result": sizeValue[0]});//内存大小：
        firstModel.append({"title": qsTr("Data Width: "), "result": widthValue[0]});//数据宽度：
        firstModel.append({"title": qsTr("Memory Info: "), "result": info[0]});//内存条信息：
        splitbar1.visible = true;
        logo1.visible = true;
//        logo1.source = InfoGroup.judgeName(vendor[0].toUpperCase()) ? ("../../img/logo/Manufacturer/" + vendor[0].toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
        logo1.source = InfoGroup.judgeName(vendor[0].toUpperCase()) ? (home.homepath + "/.cache/youker-assistant/uk-img/Manufacturer/" + vendor[0].toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
        //--------------second--------------
        home.secondFlag = true;
        secondView.visible = true;
        secondModel.clear();
        secondModel.append({"title": qsTr("Slot Number: "), "result": slot[1]});
        secondModel.append({"title": qsTr("Memory Model: "), "result": product[1]});
        secondModel.append({"title": qsTr("Vendor: "), "result": vendor[1]});
        secondModel.append({"title": qsTr("Serial Number: "), "result": serial[1]});
        secondModel.append({"title": qsTr("Size: "), "result": sizeValue[1]});
        secondModel.append({"title": qsTr("Data Width: "), "result": widthValue[1]});
        secondModel.append({"title": qsTr("Memory Info: "), "result": info[1]});
        splitbar2.visible = true;
        logo2.visible = true;
//        logo2.source = InfoGroup.judgeName(vendor[1].toUpperCase()) ? ("../../img/logo/Manufacturer/" + vendor[1].toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
        logo2.source = InfoGroup.judgeName(vendor[1].toUpperCase()) ? (home.homepath + "/.cache/youker-assistant/uk-img/Manufacturer/" + vendor[1].toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
        if(num == 2) {
            //(每个ListView子项的个数×子项高度 + (子项个数-1)×子项与子项的间隔 + 分隔条的上下间隔) × 内存条个数
            listItem.height = (home.itemNum*20 + (home.itemNum - 1)*10 + 10*2) *2;
        }
        else if(num >= 3) {
            //--------------third--------------
            home.thirdFlag = true;
            thirdView.visible = true;
            thirdModel.clear();
            thirdModel.append({"title": qsTr("Slot Number: "), "result": slot[2]});
            thirdModel.append({"title": qsTr("Memory Model: "), "result": product[2]});
            thirdModel.append({"title": qsTr("Vendor: "), "result": vendor[2]});
            thirdModel.append({"title": qsTr("Serial Number: "), "result": serial[2]});
            thirdModel.append({"title": qsTr("Memory Size: "), "result": sizeValue[2]});
            thirdModel.append({"title": qsTr("Data Width: "), "result": widthValue[2]});
            thirdModel.append({"title": qsTr("Memory Info: "), "result": info[2]});
            splitbar3.visible = true;
            logo3.visible = true;
//            logo3.source = InfoGroup.judgeName(vendor[2].toUpperCase()) ? ("../../img/logo/Manufacturer/" + vendor[2].toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
            logo3.source = InfoGroup.judgeName(vendor[2].toUpperCase()) ? (home.homepath + "/.cache/youker-assistant/uk-img/Manufacturer/" + vendor[2].toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
            if(num == 3) {
                //(每个ListView子项的个数×子项高度 + (子项个数-1)×子项与子项的间隔 + 分隔条的上下间隔) × 内存条个数
                listItem.height = (home.itemNum*20 + (home.itemNum - 1)*10 + 10*2) *3;
            }
            else if(num == 4) {
                home.fourthFlag = true;
                fourthView.visible = true;
                fourthModel.clear();
                fourthModel.append({"title": qsTr("Slot Number: "), "result": slot[3]});
                fourthModel.append({"title": qsTr("Memory Model: "), "result": product[3]});
                fourthModel.append({"title": qsTr("Vendor: "), "result": vendor[3]});
                fourthModel.append({"title": qsTr("Serial Number: "), "result": serial[3]});
                fourthModel.append({"title": qsTr("Size: "), "result": sizeValue[3]});
                fourthModel.append({"title": qsTr("Data Width: "), "result": widthValue[3]});
                fourthModel.append({"title": qsTr("Memory Info: "), "result": info[3]});
                splitbar4.visible = true;
                logo4.visible = true;
//                logo4.source = InfoGroup.judgeName(vendor[3].toUpperCase()) ? ("../../img/logo/Manufacturer/" + vendor[3].toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
                logo4.source = InfoGroup.judgeName(vendor[3].toUpperCase()) ? (home.homepath + "/.cache/youker-assistant/uk-img/Manufacturer/" + vendor[3].toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
                //(每个ListView子项的个数×子项高度 + (子项个数-1)×子项与子项的间隔 + 分隔条的上下间隔) × 内存条个数
                listItem.height = (home.itemNum*20 + (home.itemNum - 1)*10 + 10*2) *4;
            }
        }
    }


//    Component.onCompleted: {
    function init_data() {
        home.firstFlag = false;
        home.secondFlag = false;
        home.thirdFlag = false;
        home.fourthFlag = false;
        systemdispatcher.get_memory_info_qt();//获取详细信息
        var num = systemdispatcher.getHWSingleInfo("Memnum", "memory");
        if(num == 1) {
            home.firstFlag = true;
            firstView.visible = true;
            var vendorName = systemdispatcher.getHWSingleInfo("MemVendor", "memory");
            firstModel.clear();
            firstModel.append({"title": qsTr("Slot Number: "), "result": systemdispatcher.getHWSingleInfo("MemSlot", "memory")});//插槽号：
            firstModel.append({"title": qsTr("Memory Model: "), "result": systemdispatcher.getHWSingleInfo("MemProduct", "memory")});//内存型号：
            firstModel.append({"title": qsTr("Vendor: "), "result": vendorName});//制造商：
            firstModel.append({"title": qsTr("Serial Number: "), "result": systemdispatcher.getHWSingleInfo("MemSerial", "memory")});//序列号：
            firstModel.append({"title": qsTr("Memory Size: "), "result": systemdispatcher.getHWSingleInfo("MemSize", "memory")});//内存大小：
            firstModel.append({"title": qsTr("Data Width: "), "result": systemdispatcher.getHWSingleInfo("MemWidth", "memory")});//数据宽度：
            firstModel.append({"title": qsTr("Memory Info: "), "result": systemdispatcher.getHWSingleInfo("MemInfo", "memory")});//内存条信息：
            splitbar1.visible = true;
            logo1.visible = true;
            logo1.source = InfoGroup.judgeName(vendorName.toUpperCase()) ? (home.homepath + "/.cache/youker-assistant/uk-img/Manufacturer/" + vendorName.toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
//            logo1.source = InfoGroup.judgeName(vendorName.toUpperCase()) ? ("../../img/logo/Manufacturer/" + vendorName.toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
            //(每个ListView子项的个数×子项高度 + (子项个数-1)×子项与子项的间隔 + 分隔条的上下间隔) × 内存条个数
            listItem.height = home.itemNum*20 + (home.itemNum - 1)*10 + 10*2;
        }
        else if(num >= 2){
            home.show_several_memory(num);
        }
    }

    Connections
    {
        target: sessiondispatcher
        onTellDetailPageUpdateData: {
            if (infoFlag == "memory") {
                home.init_data();
            }
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
                width: 150
            }
            Text {
                id: slotText
                text: result
                width: 450
                wrapMode: Text.WordWrap
                font.pixelSize: 14
                color: "#7a7a7a"
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
            text: qsTr("Memory Info")//内存信息
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
                        model: firstModel
                        delegate: memoryDelegate
                        visible: false
                        spacing: 10
                    }
                    Image {
                        id: logo1
                        visible: false
                        opacity: 0.5
                        source: ""
                        anchors {
                            right: parent.right
//                            rightMargin: 30
                        }
                    }
                }
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
                        model: secondModel
                        delegate: memoryDelegate
                        visible: false
                        spacing: 10
                    }
                    Image {
                        id: logo2
                        visible: false
                        opacity: 0.5
                        source: ""
                        anchors {
                            right: parent.right
//                            rightMargin: 30
                        }
                    }
                }
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
                        model: thirdModel
                        delegate: memoryDelegate
                        visible: false
                        spacing: 10
                    }
                    Image {
                        id: logo3
                        visible: false
                        opacity: 0.5
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
                Item {
                    width: parent.width
                    height: home.fourthFlag ? (home.itemNum*20 + (home.itemNum - 1)*10) : 0
                    ListView {
                        id: fourthView
                        anchors.fill: parent
                        model: fourthModel
                        delegate: memoryDelegate
                        visible: false
                        spacing: 10
                    }
                    Image {
                        id: logo4
                        visible: false
                        opacity: 0.5
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
            }
        }//Item
    }//ScrollArea
}
