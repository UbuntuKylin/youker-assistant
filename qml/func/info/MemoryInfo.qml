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

/*------------------最多支持两个内存槽的显示------------------*/
Rectangle {
    id: home; width: parent.width; height: 475
    color: "transparent"

    function show_several_memory(num)
    {
        var slot = systemdispatcher.getSingleInfo("MemSlot", "memory").spit("/");
        var product = systemdispatcher.getSingleInfo("MemProduct", "memory").spit("/");
        var vendor = systemdispatcher.getSingleInfo("MemVendor", "memory").spit("/");
        var serial = systemdispatcher.getSingleInfo("MemSerial", "memory").spit("/");
        var sizeValue = systemdispatcher.getSingleInfo("MemSize", "memory").spit("/");

        splitbar.visible = true;
        slotLabel2.visible = true;
        modelLabel2.visible = true;
        vendorLabel2.visible = true;
        serialLabel2.visible = true;
        sizeLabel2.visible = true;

        for (var i=0; i < num; i++) {
            if(i == 0) {
                logo.source = "../../img/logo/Manufacturer/" + vendor[0].toUpperCase() + ".jpg";
                slotText.text = slot[0];
                modelText.text = product[0];
                vendorText.text = vendor[0];
                serialText.text = serial[0];
                sizeText.text = sizeValue[0]/1024/1024/1024 + "GB";
            }
            else if(i == 1) {
                logo2.source = "../../img/logo/Manufacturer/" + vendor[1].toUpperCase() + ".jpg";
                slotText2.text = slot[1];
                modelText2.text = product[1];
                vendorText2.text = vendor[1];
                serialText2.text = serial[1];
                sizeText2.text = sizeValue[1]/1024/1024/1024 + "GB";
            }
        }
    }


    Component.onCompleted: {
        systemdispatcher.get_memory_info_qt();//获取详细信息
        var num = systemdispatcher.getSingleInfo("Memnum", "memory");
        if(num == 1) {
            logo.source = "../../img/logo/Manufacturer/" + systemdispatcher.getSingleInfo("MemVendor", "memory").toUpperCase() + ".jpg";
            slotText.text = systemdispatcher.getSingleInfo("MemSlot", "memory");
            modelText.text = systemdispatcher.getSingleInfo("MemProduct", "memory");
            vendorText.text = systemdispatcher.getSingleInfo("MemVendor", "memory");
            serialText.text = systemdispatcher.getSingleInfo("MemSerial", "memory");
            var sizeValue = systemdispatcher.getSingleInfo("MemSize", "memory");
            sizeValue = sizeValue/1024/1024/1024;
            sizeText.text = sizeValue + "GB";

            splitbar.visible = false;
            slotLabel2.visible = false;
            modelLabel2.visible = false;
            vendorLabel2.visible = false;
            serialLabel2.visible = false;
            sizeLabel2.visible = false;
        }
        else if(num >= 2){
            home.show_several_memory(2);
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
        Column {
            anchors.left: parent.left
            anchors.leftMargin: 20
            spacing: 10
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Slot Number:")//插槽号：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 100
                }
                Text {
                    id: slotText
                    text: ""//systemdispatcher.getSingleInfo("MemSlot")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Memory Model:")//内存型号：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 100
                }
                Text {
                    id: modelText
                    text: ""//systemdispatcher.getSingleInfo("MemProduct")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Vendor:")//制造商：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 100
                }
                Text {
                    id: vendorText
                    text: ""//systemdispatcher.getSingleInfo("MemVendor")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Serial:")//序列号：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 100
                }
                Text {
                    id: serialText
                    text: ""//systemdispatcher.getSingleInfo("MemSerial")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Size:")//内存大小：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 100
                }
                Text {
                    id: sizeText
                    text: ""//systemdispatcher.getSingleInfo("MemSize")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }





            Rectangle {
                id: splitbar
                width: home.width - 30 * 2
                height: 1; color: "#ccdadd"
            }
            Row {
                spacing: 10
                Common.Label {
                    id: slotLabel2
                    text: qsTr("Slot Number:")//插槽号：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 100
                }
                Common.Label {
                    id: slotText2
                    text: ""//systemdispatcher.getSingleInfo("MemSlot")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    id: modelLabel2
                    text: qsTr("Memory Model:")//内存型号：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 100
                }
                Text {
                    id: modelText2
                    text: ""//systemdispatcher.getSingleInfo("MemProduct")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    id: vendorLabel2
                    text: qsTr("Vendor:")//制造商：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 100
                }
                Text {
                    id: vendorText2
                    text: ""//systemdispatcher.getSingleInfo("MemVendor")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    id: serialLabel2
                    text: qsTr("Serial:")//序列号：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 100
                }
                Common.Label {
                    id: serialText2
                    text: ""//systemdispatcher.getSingleInfo("MemSerial")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    id: sizeLabel2
                    text: qsTr("Size:")//内存大小：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 100
                }
                Text {
                    id: sizeText2
                    text: ""//systemdispatcher.getSingleInfo("MemSize")
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
            topMargin: 50
            right: parent.right
            rightMargin: 30
        }
    }
    //logo
    Image {
        id: logo2
        source: ""
        anchors {
            top: parent.top
            topMargin: 300
            right: parent.right
            rightMargin: 30
        }
    }
}


//Rectangle {
//    id: home; width: parent.width; height: 475
//    color: "transparent"

//    function get_last_name(num)
//    {
//        var slot = systemdispatcher.getSingleInfo("MemSlot", "memory").spit("/");
//        var product = systemdispatcher.getSingleInfo("MemProduct", "memory").spit("/");
//        var vendor = systemdispatcher.getSingleInfo("MemVendor", "memory").spit("/");
//        var serial = systemdispatcher.getSingleInfo("MemSerial", "memory").spit("/");
//        var sizeValue = systemdispatcher.getSingleInfo("MemSize", "memory").spit("/");

//        splitbar.visible = true;
//        slotLabel2.visible = true;
//        modelLabel2.visible = true;
//        vendorLabel2.visible = true;
//        serialLabel2.visible = true;
//        sizeLabel2.visible = true;

//        for (var i=0; i < num; i++) {
//            if(i == 0) {
//                logo.source = "../../img/logo/Manufacturer/" + vendor[0].toUpperCase() + ".jpg";
//                slotText.text = slot[0];
//                modelText.text = product[0];
//                vendorText.text = vendor[0];
//                serialText.text = serial[0];
//                sizeText.text = sizeValue[0]/1024/1024/1024 + "GB";
//            }
//            else if(i == 1) {
//                logo2.source = "../../img/logo/Manufacturer/" + vendor[1].toUpperCase() + ".jpg";
//                slotText2.text = slot[1];
//                modelText2.text = product[1];
//                vendorText2.text = vendor[1];
//                serialText2.text = serial[1];
//                sizeText2.text = sizeValue[1]/1024/1024/1024 + "GB";
//            }
//        }
//    }


//    Component.onCompleted: {
//        systemdispatcher.get_memory_info_qt();//获取详细信息
//        var num = systemdispatcher.getSingleInfo("Memnum", "memory");
////        console.log(num);
//        if(num == 1) {
//            logo.source = "../../img/logo/Manufacturer/" + systemdispatcher.getSingleInfo("MemVendor", "memory").toUpperCase() + ".jpg";
//            slotText.text = systemdispatcher.getSingleInfo("MemSlot", "memory");
//            modelText.text = systemdispatcher.getSingleInfo("MemProduct", "memory");
//            vendorText.text = systemdispatcher.getSingleInfo("MemVendor", "memory");
//            serialText.text = systemdispatcher.getSingleInfo("MemSerial", "memory");
//            var sizeValue = systemdispatcher.getSingleInfo("MemSize", "memory");
//            sizeValue = sizeValue/1024/1024/1024;
//            sizeText.text = sizeValue + "GB";

//            splitbar.visible = false;
//            slotLabel2.visible = false;
//            modelLabel2.visible = false;
//            vendorLabel2.visible = false;
//            serialLabel2.visible = false;
//            sizeLabel2.visible = false;
//        }
//        else if(num == 2){
//            home.get_last_name(2);
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
//            Text {
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
//        Column {
//            anchors.left: parent.left
//            anchors.leftMargin: 20
//            spacing: 10
//            Row {
//                spacing: 10
//                Text {
//                    text: qsTr("Slot Number:")//插槽号：
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                    width: 100
//                }
//                Text {
//                    id: slotText
//                    text: ""//systemdispatcher.getSingleInfo("MemSlot")
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                }
//            }
//            Row {
//                spacing: 10
//                Text {
//                    text: qsTr("Memory Model:")//内存型号：
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                    width: 100
//                }
//                Text {
//                    id: modelText
//                    text: ""//systemdispatcher.getSingleInfo("MemProduct")
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                }
//            }
//            Row {
//                spacing: 10
//                Text {
//                    text: qsTr("Vendor:")//制造商：
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                    width: 100
//                }
//                Text {
//                    id: vendorText
//                    text: ""//systemdispatcher.getSingleInfo("MemVendor")
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                }
//            }
//            Row {
//                spacing: 10
//                Text {
//                    text: qsTr("Serial:")//序列号：
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                    width: 100
//                }
//                Text {
//                    id: serialText
//                    text: ""//systemdispatcher.getSingleInfo("MemSerial")
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                }
//            }
//            Row {
//                spacing: 10
//                Text {
//                    text: qsTr("Size:")//内存大小：
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                    width: 100
//                }
//                Text {
//                    id: sizeText
//                    text: ""//systemdispatcher.getSingleInfo("MemSize")
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
//                Text {
//                    id: slotLabel2
//                    text: qsTr("Slot Number:")//插槽号：
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                    width: 100
//                }
//                Text {
//                    id: slotText2
//                    text: ""//systemdispatcher.getSingleInfo("MemSlot")
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                }
//            }
//            Row {
//                spacing: 10
//                Text {
//                    id: modelLabel2
//                    text: qsTr("Memory Model:")//内存型号：
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                    width: 100
//                }
//                Text {
//                    id: modelText2
//                    text: ""//systemdispatcher.getSingleInfo("MemProduct")
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                }
//            }
//            Row {
//                spacing: 10
//                Text {
//                    id: vendorLabel2
//                    text: qsTr("Vendor:")//制造商：
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                    width: 100
//                }
//                Text {
//                    id: vendorText2
//                    text: ""//systemdispatcher.getSingleInfo("MemVendor")
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                }
//            }
//            Row {
//                spacing: 10
//                Text {
//                    id: serialLabel2
//                    text: qsTr("Serial:")//序列号：
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                    width: 100
//                }
//                Text {
//                    id: serialText2
//                    text: ""//systemdispatcher.getSingleInfo("MemSerial")
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                }
//            }
//            Row {
//                spacing: 10
//                Text {
//                    id: sizeLabel2
//                    text: qsTr("Size:")//内存大小：
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                    width: 100
//                }
//                Text {
//                    id: sizeText2
//                    text: ""//systemdispatcher.getSingleInfo("MemSize")
//                    font.pixelSize: 14
//                    color: "#7a7a7a"
//                }
//            }
//        }
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
