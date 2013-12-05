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

    function show_several_memory(num)
    {
//        var slot = systemdispatcher.getSingleInfo("MemSlot", "memory").split("/");
//        var product = systemdispatcher.getSingleInfo("MemProduct", "memory").split("/");
//        var vendor = systemdispatcher.getSingleInfo("MemVendor", "memory").split("/");
//        var serial = systemdispatcher.getSingleInfo("MemSerial", "memory").split("/");
//        var sizeValue = systemdispatcher.getSingleInfo("MemSize", "memory").split("/");
//        var widthValue = systemdispatcher.getSingleInfo("MemWidth", "memory").split("/");
//        var info = systemdispatcher.getSingleInfo("MemInfo", "memory").split("/");

//        splitbar.visible = true;
//        slotLabel2.visible = true;
//        modelLabel2.visible = true;
//        vendorLabel2.visible = true;
//        serialLabel2.visible = true;
//        sizeLabel2.visible = true;
//        widthLabel2.visible = true;
//        infoLabel2.visible = true;

//        for (var i=0; i < num; i++) {
//            if(i == 0) {
//                logo.source = "../../img/logo/Manufacturer/" + vendor[0].toUpperCase() + ".jpg";
//                slotText.text = slot[0];
//                modelText.text = product[0];
//                vendorText.text = vendor[0];
//                serialText.text = serial[0];
//                sizeText.text = sizeValue[0]/1024/1024/1024 + "GB";
//                widthText.text = widthValue[0];
//                infoText.text = info[0];
//            }
//            else if(i == 1) {
//                logo2.source = "../../img/logo/Manufacturer/" + vendor[1].toUpperCase() + ".jpg";
//                slotText2.text = slot[1];
//                modelText2.text = product[1];
//                vendorText2.text = vendor[1];
//                serialText2.text = serial[1];
//                sizeText2.text = sizeValue[1]/1024/1024/1024 + "GB";
//                widthText2.text = widthValue[1];
//                infoText2.text = info[1];
//            }
//        }
    }


    Component.onCompleted: {
        home.firstFlag = false;
        home.secondFlag = false;
        systemdispatcher.get_memory_info_qt();//获取详细信息
        var num = systemdispatcher.getSingleInfo("Memnum", "memory");
        if(num == 1) {
            home.firstFlag = true;
            firstView.visible = true;
//            logo.source = "../../img/logo/Manufacturer/" + systemdispatcher.getSingleInfo("MemVendor", "memory").toUpperCase() + ".jpg";
            firstModel.clear();
            firstModel.append({"title": qsTr("Slot Number:"), "result": systemdispatcher.getSingleInfo("MemSlot", "memory")});
            firstModel.append({"title": qsTr("Memory Model:"), "result": systemdispatcher.getSingleInfo("MemProduct", "memory")});
            firstModel.append({"title": qsTr("Vendor:"), "result": systemdispatcher.getSingleInfo("MemVendor", "memory")});
            firstModel.append({"title": qsTr("Serial:"), "result": systemdispatcher.getSingleInfo("MemSerial", "memory")});
            firstModel.append({"title": qsTr("Size:"), "result": systemdispatcher.getSingleInfo("MemSize", "memory")});
            firstModel.append({"title": qsTr("Data Width:"), "result": systemdispatcher.getSingleInfo("MemWidth", "memory")});
            firstModel.append({"title": qsTr("Memory Info:"), "result": systemdispatcher.getSingleInfo("MemInfo", "memory")});
            splitbar1.visible = true;
            logo1.visible = true;
            logo1.source = "../../img/logo/Manufacturer/" + systemdispatcher.getSingleInfo("MemVendor", "memory").toUpperCase() + ".jpg";



            home.secondFlag = true;
            secondView.visible = true;
            secondModel.clear();
            secondModel.append({"title": qsTr("Slot Number:"), "result": "111"});
            secondModel.append({"title": qsTr("Memory Model:"), "result": "222"});
            secondModel.append({"title": qsTr("Vendor:"), "result": "333"});
            secondModel.append({"title": qsTr("Serial:"), "result": systemdispatcher.getSingleInfo("MemSerial", "memory")});
            secondModel.append({"title": qsTr("Size:"), "result": systemdispatcher.getSingleInfo("MemSize", "memory")});
            secondModel.append({"title": qsTr("Data Width:"), "result": systemdispatcher.getSingleInfo("MemWidth", "memory")});
            secondModel.append({"title": qsTr("Memory Info:"), "result": systemdispatcher.getSingleInfo("MemInfo", "memory")});
            splitbar2.visible = true;
            logo2.visible = true;
            logo2.source = "../../img/logo/Manufacturer/" + systemdispatcher.getSingleInfo("MemVendor", "memory").toUpperCase() + ".jpg";


            home.thirdFlag = true;
            thirdView.visible = true;
            thirdModel.clear();
            thirdModel.append({"title": qsTr("Serial:"), "result": systemdispatcher.getSingleInfo("MemSerial", "memory")});
            thirdModel.append({"title": qsTr("Size:"), "result": systemdispatcher.getSingleInfo("MemSize", "memory")});
            thirdModel.append({"title": qsTr("Data Width:"), "result": systemdispatcher.getSingleInfo("MemWidth", "memory")});
            thirdModel.append({"title": qsTr("Memory Info:"), "result": systemdispatcher.getSingleInfo("MemInfo", "memory")});
            thirdModel.append({"title": qsTr("Slot Number:"), "result": "444"});
            thirdModel.append({"title": qsTr("Memory Model:"), "result": "555"});
            thirdModel.append({"title": qsTr("Vendor:"), "result": "666"});
            splitbar3.visible = true;
            logo3.visible = true;
            logo3.source = "../../img/logo/Manufacturer/" + systemdispatcher.getSingleInfo("MemVendor", "memory").toUpperCase() + ".jpg";


            home.fourthFlag = true;
            fourthView.visible = true;
            fourthModel.clear();
            fourthModel.append({"title": qsTr("Serial:"), "result": systemdispatcher.getSingleInfo("MemSerial", "memory")});
            fourthModel.append({"title": qsTr("Size:"), "result": systemdispatcher.getSingleInfo("MemSize", "memory")});
            fourthModel.append({"title": qsTr("Data Width:"), "result": systemdispatcher.getSingleInfo("MemWidth", "memory")});
            fourthModel.append({"title": qsTr("Memory Info:"), "result": systemdispatcher.getSingleInfo("MemInfo", "memory")});
            fourthModel.append({"title": qsTr("Slot Number:"), "result": "444"});
            fourthModel.append({"title": qsTr("Memory Model:"), "result": "555"});
            fourthModel.append({"title": qsTr("Vendor:"), "result": "666"});
            splitbar4.visible = true;
            logo4.visible = true;
            logo4.source = "../../img/logo/Manufacturer/" + systemdispatcher.getSingleInfo("MemVendor", "memory").toUpperCase() + ".jpg";

            //(每个ListView子项的个数×子项高度 + (子项个数-1)×子项与子项的间隔 + 分隔条的上下间隔) × 内存条个数
            listItem.height = (7*20 + 6*10 + 10*2) *4;
        }
        else if(num >= 2){
            home.show_several_memory(2);
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
            text: qsTr("Memory information")//内存信息
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
                    height: home.firstFlag ? (7*20 + 6*10) : 0
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

                Rectangle {
                    id: splitbar1
                    width: 680 - 4 - 30*2
                    height: 1; color: "#ccdadd"
                    visible: false
                }
                Item {
                    width: parent.width
                    height: home.secondFlag ? (7*20 + 6*10) : 0
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
                Rectangle {
                    id: splitbar2
                    width: 680 - 4 - 30*2
                    height: 1; color: "#ccdadd"
                    visible: false
                }
                Item {
                    width: parent.width
                    height: home.thirdFlag ? (7*20 + 6*10) : 0
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
                Rectangle {
                    id: splitbar3
                    width: 680 - 4 - 30*2
                    height: 1; color: "#ccdadd"
                    visible: false
                }
                Item {
                    width: parent.width
                    height: home.fourthFlag ? (7*20 + 6*10) : 0
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







/*------------------最多支持两个内存槽的显示------------------*/
//Rectangle {
//    id: home; width: parent.width; height: 475
//    color: "transparent"

//    function show_several_memory(num)
//    {
//        var slot = systemdispatcher.getSingleInfo("MemSlot", "memory").split("/");
//        var product = systemdispatcher.getSingleInfo("MemProduct", "memory").split("/");
//        var vendor = systemdispatcher.getSingleInfo("MemVendor", "memory").split("/");
//        var serial = systemdispatcher.getSingleInfo("MemSerial", "memory").split("/");
//        var sizeValue = systemdispatcher.getSingleInfo("MemSize", "memory").split("/");
//        var widthValue = systemdispatcher.getSingleInfo("MemWidth", "memory").split("/");
//        var info = systemdispatcher.getSingleInfo("MemInfo", "memory").split("/");

//        splitbar.visible = true;
//        slotLabel2.visible = true;
//        modelLabel2.visible = true;
//        vendorLabel2.visible = true;
//        serialLabel2.visible = true;
//        sizeLabel2.visible = true;
//        widthLabel2.visible = true;
//        infoLabel2.visible = true;

//        for (var i=0; i < num; i++) {
//            if(i == 0) {
//                logo.source = "../../img/logo/Manufacturer/" + vendor[0].toUpperCase() + ".jpg";
//                slotText.text = slot[0];
//                modelText.text = product[0];
//                vendorText.text = vendor[0];
//                serialText.text = serial[0];
//                sizeText.text = sizeValue[0]/1024/1024/1024 + "GB";
//                widthText.text = widthValue[0];
//                infoText.text = info[0];
//            }
//            else if(i == 1) {
//                logo2.source = "../../img/logo/Manufacturer/" + vendor[1].toUpperCase() + ".jpg";
//                slotText2.text = slot[1];
//                modelText2.text = product[1];
//                vendorText2.text = vendor[1];
//                serialText2.text = serial[1];
//                sizeText2.text = sizeValue[1]/1024/1024/1024 + "GB";
//                widthText2.text = widthValue[1];
//                infoText2.text = info[1];
//            }
//        }
//    }


//    Component.onCompleted: {
//        systemdispatcher.get_memory_info_qt();//获取详细信息
//        var num = systemdispatcher.getSingleInfo("Memnum", "memory");
//        if(num == 1) {
//            logo.source = "../../img/logo/Manufacturer/" + systemdispatcher.getSingleInfo("MemVendor", "memory").toUpperCase() + ".jpg";
//            slotText.text = systemdispatcher.getSingleInfo("MemSlot", "memory");
//            modelText.text = systemdispatcher.getSingleInfo("MemProduct", "memory");
//            vendorText.text = systemdispatcher.getSingleInfo("MemVendor", "memory");
//            serialText.text = systemdispatcher.getSingleInfo("MemSerial", "memory");
//            var sizeValue = systemdispatcher.getSingleInfo("MemSize", "memory");
//            sizeValue = sizeValue/1024/1024/1024;
//            sizeText.text = sizeValue + "GB";
//            widthText.text = systemdispatcher.getSingleInfo("MemWidth", "memory");
//            infoText.text = systemdispatcher.getSingleInfo("MemInfo", "memory");

////            splitbar.visible = false;
////            slotLabel2.visible = false;
////            modelLabel2.visible = false;
////            vendorLabel2.visible = false;
////            serialLabel2.visible = false;
////            sizeLabel2.visible = false;
////            widthLabel2.visible = false;
////            infoLabel2.visible = false;
//        }
//        else if(num >= 2){
//            home.show_several_memory(2);
//        }
//    }
//    Column {
//        anchors {
//            top: parent.top
//            topMargin: 40
//            left: parent.left
//            leftMargin: 30
//        }
//        spacing: 20

//        Row {
//            Common.Label {
//                id: titlebar
//                text: qsTr("Memory information")//内存信息
//                font.bold: true
//                font.pixelSize: 14
//                color: "#383838"
//            }
//            Rectangle {width: home.width - titlebar.width - 30 * 2
//                anchors.verticalCenter: parent.verticalCenter
//                height: 1; color: "#ccdadd"
//            }
//        }


//        Common.ScrollArea {
////            frame:false
//            anchors.left: parent.left
//            anchors.leftMargin: 20
//            height: 390
//            width: 650 - 4
//            Item {
//                width: parent.width   //列表宽度
//                height: 500     //列表长度,前面的数字为列表行数
//                Column {
////                    anchors.left: parent.left
////                    anchors.leftMargin: 20
//                    spacing: 10
//                    Row {
//                        spacing: 10
//                        Common.Label {
//                            text: qsTr("Slot Number:")//插槽号：
//                            font.pixelSize: 14
//                            color: "#7a7a7a"
//                            width: 100
//                        }
//                        Text {
//                            id: slotText
//                            text: ""//systemdispatcher.getSingleInfo("MemSlot")
//                            font.pixelSize: 14
//                            color: "#7a7a7a"
//                        }
//                    }
//                    Row {
//                        spacing: 10
//                        Common.Label {
//                            text: qsTr("Memory Model:")//内存型号：
//                            font.pixelSize: 14
//                            color: "#7a7a7a"
//                            width: 100
//                        }
//                        Text {
//                            id: modelText
//                            text: ""//systemdispatcher.getSingleInfo("MemProduct")
//                            font.pixelSize: 14
//                            color: "#7a7a7a"
//                        }
//                    }
//                    Row {
//                        spacing: 10
//                        Common.Label {
//                            text: qsTr("Vendor:")//制造商：
//                            font.pixelSize: 14
//                            color: "#7a7a7a"
//                            width: 100
//                        }
//                        Text {
//                            id: vendorText
//                            text: ""//systemdispatcher.getSingleInfo("MemVendor")
//                            font.pixelSize: 14
//                            color: "#7a7a7a"
//                        }
//                    }
//                    Row {
//                        spacing: 10
//                        Common.Label {
//                            text: qsTr("Serial:")//序列号：
//                            font.pixelSize: 14
//                            color: "#7a7a7a"
//                            width: 100
//                        }
//                        Text {
//                            id: serialText
//                            text: ""//systemdispatcher.getSingleInfo("MemSerial")
//                            font.pixelSize: 14
//                            color: "#7a7a7a"
//                        }
//                    }
//                    Row {
//                        spacing: 10
//                        Common.Label {
//                            text: qsTr("Size:")//内存大小：
//                            font.pixelSize: 14
//                            color: "#7a7a7a"
//                            width: 100
//                        }
//                        Text {
//                            id: sizeText
//                            text: ""//systemdispatcher.getSingleInfo("MemSize")
//                            font.pixelSize: 14
//                            color: "#7a7a7a"
//                        }
//                    }
//                    Row {
//                        spacing: 10
//                        Common.Label {
//                            text: qsTr("Data Width:")//数据宽度：
//                            font.pixelSize: 14
//                            color: "#7a7a7a"
//                            width: 100
//                        }
//                        Text {
//                            id: widthText
//                            text: ""//systemdispatcher.getSingleInfo("MemWidth")
//                            font.pixelSize: 14
//                            color: "#7a7a7a"
//                        }
//                    }
//                    Row {
//                        spacing: 10
//                        Common.Label {
//                            text: qsTr("Memory Info:")//内存条信息：
//                            font.pixelSize: 14
//                            color: "#7a7a7a"
//                            width: 100
//                        }
//                        Text {
//                            id: infoText
//                            text: ""//systemdispatcher.getSingleInfo("MemInfo")
//                            font.pixelSize: 14
//                            color: "#7a7a7a"
//                        }
//                    }





//                    Rectangle {
//                        id: splitbar
//                        width: home.width - 30 * 2
//                        height: 1; color: "#ccdadd"
//                    }
//                    Row {
//                        spacing: 10
//                        Common.Label {
//                            id: slotLabel2
//                            text: qsTr("Slot Number:")//插槽号：
//                            font.pixelSize: 14
//                            color: "#7a7a7a"
//                            width: 100
//                        }
//                        Common.Label {
//                            id: slotText2
//                            text: ""//systemdispatcher.getSingleInfo("MemSlot")
//                            font.pixelSize: 14
//                            color: "#7a7a7a"
//                        }
//                    }
//                    Row {
//                        spacing: 10
//                        Common.Label {
//                            id: modelLabel2
//                            text: qsTr("Memory Model:")//内存型号：
//                            font.pixelSize: 14
//                            color: "#7a7a7a"
//                            width: 100
//                        }
//                        Text {
//                            id: modelText2
//                            text: ""//systemdispatcher.getSingleInfo("MemProduct")
//                            font.pixelSize: 14
//                            color: "#7a7a7a"
//                        }
//                    }
//                    Row {
//                        spacing: 10
//                        Common.Label {
//                            id: vendorLabel2
//                            text: qsTr("Vendor:")//制造商：
//                            font.pixelSize: 14
//                            color: "#7a7a7a"
//                            width: 100
//                        }
//                        Text {
//                            id: vendorText2
//                            text: ""//systemdispatcher.getSingleInfo("MemVendor")
//                            font.pixelSize: 14
//                            color: "#7a7a7a"
//                        }
//                    }
//                    Row {
//                        spacing: 10
//                        Common.Label {
//                            id: serialLabel2
//                            text: qsTr("Serial:")//序列号：
//                            font.pixelSize: 14
//                            color: "#7a7a7a"
//                            width: 100
//                        }
//                        Common.Label {
//                            id: serialText2
//                            text: ""//systemdispatcher.getSingleInfo("MemSerial")
//                            font.pixelSize: 14
//                            color: "#7a7a7a"
//                        }
//                    }
//                    Row {
//                        spacing: 10
//                        Common.Label {
//                            id: sizeLabel2
//                            text: qsTr("Size:")//内存大小：
//                            font.pixelSize: 14
//                            color: "#7a7a7a"
//                            width: 100
//                        }
//                        Text {
//                            id: sizeText2
//                            text: ""//systemdispatcher.getSingleInfo("MemSize")
//                            font.pixelSize: 14
//                            color: "#7a7a7a"
//                        }
//                    }
//                    Row {
//                        spacing: 10
//                        Common.Label {
//                            id: widthLabel2
//                            text: qsTr("Data Width:")//数据宽度：
//                            font.pixelSize: 14
//                            color: "#7a7a7a"
//                            width: 100
//                        }
//                        Text {
//                            id: widthText2
//                            text: ""//systemdispatcher.getSingleInfo("MemWidth")
//                            font.pixelSize: 14
//                            color: "#7a7a7a"
//                        }
//                    }
//                    Row {
//                        spacing: 10
//                        Common.Label {
//                            id: infoLabel2
//                            text: qsTr("Memory Info:")//内存条信息：
//                            font.pixelSize: 14
//                            color: "#7a7a7a"
//                            width: 100
//                        }
//                        Text {
//                            id: infoText2
//                            text: ""//systemdispatcher.getSingleInfo("MemInfo")
//                            font.pixelSize: 14
//                            color: "#7a7a7a"
//                        }
//                    }
//                }
//            }//Item
//        }//ScrollArea


////        Column {
////            anchors.left: parent.left
////            anchors.leftMargin: 20
////            spacing: 10
////            Row {
////                spacing: 10
////                Common.Label {
////                    text: qsTr("Slot Number:")//插槽号：
////                    font.pixelSize: 14
////                    color: "#7a7a7a"
////                    width: 100
////                }
////                Text {
////                    id: slotText
////                    text: ""//systemdispatcher.getSingleInfo("MemSlot")
////                    font.pixelSize: 14
////                    color: "#7a7a7a"
////                }
////            }
////            Row {
////                spacing: 10
////                Common.Label {
////                    text: qsTr("Memory Model:")//内存型号：
////                    font.pixelSize: 14
////                    color: "#7a7a7a"
////                    width: 100
////                }
////                Text {
////                    id: modelText
////                    text: ""//systemdispatcher.getSingleInfo("MemProduct")
////                    font.pixelSize: 14
////                    color: "#7a7a7a"
////                }
////            }
////            Row {
////                spacing: 10
////                Common.Label {
////                    text: qsTr("Vendor:")//制造商：
////                    font.pixelSize: 14
////                    color: "#7a7a7a"
////                    width: 100
////                }
////                Text {
////                    id: vendorText
////                    text: ""//systemdispatcher.getSingleInfo("MemVendor")
////                    font.pixelSize: 14
////                    color: "#7a7a7a"
////                }
////            }
////            Row {
////                spacing: 10
////                Common.Label {
////                    text: qsTr("Serial:")//序列号：
////                    font.pixelSize: 14
////                    color: "#7a7a7a"
////                    width: 100
////                }
////                Text {
////                    id: serialText
////                    text: ""//systemdispatcher.getSingleInfo("MemSerial")
////                    font.pixelSize: 14
////                    color: "#7a7a7a"
////                }
////            }
////            Row {
////                spacing: 10
////                Common.Label {
////                    text: qsTr("Size:")//内存大小：
////                    font.pixelSize: 14
////                    color: "#7a7a7a"
////                    width: 100
////                }
////                Text {
////                    id: sizeText
////                    text: ""//systemdispatcher.getSingleInfo("MemSize")
////                    font.pixelSize: 14
////                    color: "#7a7a7a"
////                }
////            }
////            Row {
////                spacing: 10
////                Common.Label {
////                    text: qsTr("Data Width:")//数据宽度：
////                    font.pixelSize: 14
////                    color: "#7a7a7a"
////                    width: 100
////                }
////                Text {
////                    id: widthText
////                    text: ""//systemdispatcher.getSingleInfo("MemWidth")
////                    font.pixelSize: 14
////                    color: "#7a7a7a"
////                }
////            }
////            Row {
////                spacing: 10
////                Common.Label {
////                    text: qsTr("Memory Info:")//内存条信息：
////                    font.pixelSize: 14
////                    color: "#7a7a7a"
////                    width: 100
////                }
////                Text {
////                    id: infoText
////                    text: ""//systemdispatcher.getSingleInfo("MemInfo")
////                    font.pixelSize: 14
////                    color: "#7a7a7a"
////                }
////            }





////            Rectangle {
////                id: splitbar
////                width: home.width - 30 * 2
////                height: 1; color: "#ccdadd"
////            }
////            Row {
////                spacing: 10
////                Common.Label {
////                    id: slotLabel2
////                    text: qsTr("Slot Number:")//插槽号：
////                    font.pixelSize: 14
////                    color: "#7a7a7a"
////                    width: 100
////                }
////                Common.Label {
////                    id: slotText2
////                    text: ""//systemdispatcher.getSingleInfo("MemSlot")
////                    font.pixelSize: 14
////                    color: "#7a7a7a"
////                }
////            }
////            Row {
////                spacing: 10
////                Common.Label {
////                    id: modelLabel2
////                    text: qsTr("Memory Model:")//内存型号：
////                    font.pixelSize: 14
////                    color: "#7a7a7a"
////                    width: 100
////                }
////                Text {
////                    id: modelText2
////                    text: ""//systemdispatcher.getSingleInfo("MemProduct")
////                    font.pixelSize: 14
////                    color: "#7a7a7a"
////                }
////            }
////            Row {
////                spacing: 10
////                Common.Label {
////                    id: vendorLabel2
////                    text: qsTr("Vendor:")//制造商：
////                    font.pixelSize: 14
////                    color: "#7a7a7a"
////                    width: 100
////                }
////                Text {
////                    id: vendorText2
////                    text: ""//systemdispatcher.getSingleInfo("MemVendor")
////                    font.pixelSize: 14
////                    color: "#7a7a7a"
////                }
////            }
////            Row {
////                spacing: 10
////                Common.Label {
////                    id: serialLabel2
////                    text: qsTr("Serial:")//序列号：
////                    font.pixelSize: 14
////                    color: "#7a7a7a"
////                    width: 100
////                }
////                Common.Label {
////                    id: serialText2
////                    text: ""//systemdispatcher.getSingleInfo("MemSerial")
////                    font.pixelSize: 14
////                    color: "#7a7a7a"
////                }
////            }
////            Row {
////                spacing: 10
////                Common.Label {
////                    id: sizeLabel2
////                    text: qsTr("Size:")//内存大小：
////                    font.pixelSize: 14
////                    color: "#7a7a7a"
////                    width: 100
////                }
////                Text {
////                    id: sizeText2
////                    text: ""//systemdispatcher.getSingleInfo("MemSize")
////                    font.pixelSize: 14
////                    color: "#7a7a7a"
////                }
////            }
////            Row {
////                spacing: 10
////                Common.Label {
////                    id: widthLabel2
////                    text: qsTr("Data Width:")//数据宽度：
////                    font.pixelSize: 14
////                    color: "#7a7a7a"
////                    width: 100
////                }
////                Text {
////                    id: widthText2
////                    text: ""//systemdispatcher.getSingleInfo("MemWidth")
////                    font.pixelSize: 14
////                    color: "#7a7a7a"
////                }
////            }
////            Row {
////                spacing: 10
////                Common.Label {
////                    id: infoLabel2
////                    text: qsTr("Memory Info:")//内存条信息：
////                    font.pixelSize: 14
////                    color: "#7a7a7a"
////                    width: 100
////                }
////                Text {
////                    id: infoText2
////                    text: ""//systemdispatcher.getSingleInfo("MemInfo")
////                    font.pixelSize: 14
////                    color: "#7a7a7a"
////                }
////            }
////        }
//    }
//    //logo
//    Image {
//        id: logo
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
//        id: logo2
//        source: ""
//        anchors {
//            top: parent.top
//            topMargin: 300
//            right: parent.right
//            rightMargin: 30
//        }
//    }
//}

