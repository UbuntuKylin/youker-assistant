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
    id: home; width: parent.width; height: 476
//    color: "transparent"
//    color: "#eeedf0"
    property int itemNum: 5//每个模块的子项个数
    property bool firstFlag: false
    property bool secondFlag: false
    property bool thirdFlag: false
    property bool fourthFlag: false
    property int columnSpace: 10
    ListModel {id: firstModel}
    ListModel {id: secondModel}
    ListModel {id: thirdModel}
    ListModel {id: fourthModel}

    property string homepath
    Component.onCompleted: {
        home.homepath = sessiondispatcher.getHomePath();
    }

    function show_several_monitor(num)
    {
        var Vgaproduct = systemdispatcher.getHWSingleInfo("Vga_product", "monitor").split("<1_1>");//显卡型号：
        var Monchip = systemdispatcher.getHWSingleInfo("Mon_chip", "monitor").split("<1_1>");//当前显卡：
        var Vgavendor = systemdispatcher.getHWSingleInfo("Vga_vendor", "monitor").split("<1_1>");//显卡制造商：
        var VgaDrive = systemdispatcher.getHWSingleInfo("Vga_Drive", "monitor").split("<1_1>");//显卡驱动：
        var Vgabusinfo = systemdispatcher.getHWSingleInfo("Vga_businfo", "monitor").split("<1_1>");//显卡总线地址：

        //--------------first--------------
        home.firstFlag = true;
        firstView.visible = true;
        firstModel.clear();

        firstModel.append({"title": qsTr("Graphics Card Model:"), "result": Vgaproduct[0]});//显卡型号：
        firstModel.append({"title": qsTr("Current Graphics Card:"), "result": Monchip[0]});//当前显卡：
        firstModel.append({"title": qsTr("Graphics Card Vendor:"), "result": Vgavendor[0]});//显卡制造商：
        firstModel.append({"title": qsTr("Graphics Driver:"), "result": VgaDrive[0]});//显卡驱动：
        firstModel.append({"title": qsTr("Bus Address:"), "result": Vgabusinfo[0]});//显卡总线地址：

//        splitbar1.visible = true;
        logo1.visible = true;
//        logo1.source = InfoGroup.judgeName(Vgavendor[0].toUpperCase()) ? ("../../img/logo/Manufacturer/" + Vgavendor[0].toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
        logo1.source = InfoGroup.judgeName(Vgavendor[0].toUpperCase()) ? (home.homepath + "/.cache/youker-assistant/uk-img/Manufacturer/" + Vgavendor[0].toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
        //--------------second--------------
        home.secondFlag = true;
        secondView.visible = true;
        secondModel.clear();

        secondModel.append({"title": qsTr("Graphics Card Model:"), "result": Vgaproduct[1]});//显卡型号：
        secondModel.append({"title": qsTr("Current Graphics Card:"), "result": Monchip[1]});//当前显卡：
        secondModel.append({"title": qsTr("Graphics Card Vendor:"), "result": Vgavendor[1]});//显卡制造商：
        secondModel.append({"title": qsTr("Graphics Driver:"), "result": VgaDrive[1]});//显卡驱动：
        secondModel.append({"title": qsTr("Bus Address:"), "result": Vgabusinfo[1]});//显卡总线地址：
        splitbar2.visible = true;
        logo2.visible = true;
//        logo2.source = InfoGroup.judgeName(Vgavendor[1].toUpperCase()) ? ("../../img/logo/Manufacturer/" + Vgavendor[1].toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
        logo2.source = InfoGroup.judgeName(Vgavendor[1].toUpperCase()) ? (home.homepath + "/.cache/youker-assistant/uk-img/Manufacturer/" + Vgavendor[1].toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
        if(num == 2) {
            //(每个ListView子项的个数×子项高度 + (子项个数-1)×子项与子项的间隔 + 分隔条的上下间隔) × 内存条个数
            listItem.height = (home.itemNum*20 + (home.itemNum - 1)*home.columnSpace + 10*2) *2 + 40;
        }
        else if(num >= 3) {
            //--------------third--------------
            home.thirdFlag = true;
            thirdView.visible = true;
            thirdModel.clear();

            thirdModel.append({"title": qsTr("Graphics Card Model:"), "result": Vgaproduct[2]});//显卡型号：
            thirdModel.append({"title": qsTr("Current Graphics Card:"), "result": Monchip[2]});//当前显卡：
            thirdModel.append({"title": qsTr("Graphics Card Vendor:"), "result": Vgavendor[2]});//显卡制造商：
            thirdModel.append({"title": qsTr("Graphics Driver:"), "result": VgaDrive[2]});//显卡驱动：
            thirdModel.append({"title": qsTr("Bus Address:"), "result": Vgabusinfo[2]});//显卡总线地址：
            splitbar3.visible = true;
            logo3.visible = true;
            logo3.source = InfoGroup.judgeName(Vgavendor[2].toUpperCase()) ? (home.homepath + "/.cache/youker-assistant/uk-img/Manufacturer/" + Vgavendor[2].toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
//            logo3.source = InfoGroup.judgeName(Vgavendor[2].toUpperCase()) ? ("../../img/logo/Manufacturer/" + Vgavendor[2].toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
            if(num == 3) {
                //(每个ListView子项的个数×子项高度 + (子项个数-1)×子项与子项的间隔 + 分隔条的上下间隔) × 内存条个数
                listItem.height = (home.itemNum*20 + (home.itemNum - 1)*home.columnSpace + 10*2) *3 + 60;
            }
            else if(num == 4) {
                home.fourthFlag = true;
                fourthView.visible = true;
                fourthModel.clear();

                fourthModel.append({"title": qsTr("Graphics Card Model:"), "result": Vgaproduct[3]});//显卡型号：
                fourthModel.append({"title": qsTr("Current Graphics Card:"), "result": Monchip[3]});//当前显卡：
                fourthModel.append({"title": qsTr("Graphics Card Vendor:"), "result": Vgavendor[3]});//显卡制造商：
                fourthModel.append({"title": qsTr("Graphics Driver:"), "result": VgaDrive[3]});//显卡驱动：
                fourthModel.append({"title": qsTr("Bus Address:"), "result": Vgabusinfo[3]});//显卡总线地址：
                splitbar4.visible = true;
                logo4.visible = true;
                logo4.source = InfoGroup.judgeName(Vgavendor[3].toUpperCase()) ? (home.homepath + "/.cache/youker-assistant/uk-img/Manufacturer/" + Vgavendor[3].toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
//                logo4.source = InfoGroup.judgeName(Vgavendor[3].toUpperCase()) ? ("../../img/logo/Manufacturer/" + Vgavendor[3].toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
                //(每个ListView子项的个数×子项高度 + (子项个数-1)×子项与子项的间隔 + 分隔条的上下间隔) × 内存条个数
                listItem.height = (home.itemNum*20 + (home.itemNum - 1)*home.columnSpace + 10*2) *4 + 80;
            }
        }
    }

//    Component.onCompleted: {
    function init_data() {
        systemdispatcher.get_monitor_info_qt();//获取光驱详细信息
        home.firstFlag = false;
        home.secondFlag = false;
        home.thirdFlag = false;
        home.fourthFlag = false;
//        systemdispatcher.get_audiocard_info_qt();//获取详细信息
        var num = systemdispatcher.getHWSingleInfo("Vga_num", "monitor");
        if(num == 1) {
            home.firstFlag = true;
            firstView.visible = true;
            var vendorName = systemdispatcher.getHWSingleInfo("Vga_vendor", "monitor");//制造商
            firstModel.clear();
            firstModel.append({"title": qsTr("Graphics Card Model:"), "result": systemdispatcher.getHWSingleInfo("Vga_product", "monitor")});//显卡型号：
            firstModel.append({"title": qsTr("Current Graphics Card:"), "result": systemdispatcher.getHWSingleInfo("Mon_chip", "monitor")});//当前显卡：
            firstModel.append({"title": qsTr("Graphics Card Vendor:"), "result": vendorName});//显卡制造商：
            firstModel.append({"title": qsTr("Graphics Driver:"), "result": systemdispatcher.getHWSingleInfo("Vga_Drive", "monitor")});//显卡驱动：
            firstModel.append({"title": qsTr("Bus Address:"), "result": systemdispatcher.getHWSingleInfo("Vga_businfo", "monitor")});//显卡总线地址：
//            splitbar1.visible = true;
            logo1.visible = true;
            logo1.source = InfoGroup.judgeName(vendorName.toUpperCase()) ? (home.homepath + "/.cache/youker-assistant/uk-img/Manufacturer/" + vendorName.toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
//            logo1.source = InfoGroup.judgeName(vendorName.toUpperCase()) ? ("../../img/logo/Manufacturer/" + vendorName.toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
            //(每个ListView子项的个数×子项高度 + (子项个数-1)×子项与子项的间隔 + 分隔条的上下间隔) × 内存条个数
            listItem.height = home.itemNum*20 + (home.itemNum - 1)*home.columnSpace + 20 ;
        }
        else if(num >= 2){
            home.show_several_monitor(num);
        }

        var vendor = systemdispatcher.getHWSingleInfo("Mon_vendor", "monitor");
        if(vendor.length !== 0 ) {
            productLabel.visible = true;
            vendorLabel.visible = true;
            dateLabel.visible = true;
            sizeLabel.visible = true;
            inLabel.visible = true;
            maxmodeLabel.visible = true;
            gammaLabel.visible = true;
            outputLabel.visible = true;
            supportLabel.visible = true;
            monitortitlebar.visible = true;
            montitle.visible = true;
            monitorlogo.visible = true;
            var vendorName = systemdispatcher.getHWSingleInfo("Mon_vendor", "monitor");
            monitorlogo.source = InfoGroup.judgeName(vendorName.toUpperCase()) ? (home.homepath + "/.cache/youker-assistant/uk-img/Manufacturer/" + vendorName.toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
//            monitorlogo.source = InfoGroup.judgeName(vendorName.toUpperCase()) ? ("../../img/logo/Manufacturer/" + vendorName.toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
            productText.text = systemdispatcher.getHWSingleInfo("Mon_product", "monitor");
            vendorText.text = vendorName;
            dateText.text = systemdispatcher.getHWSingleInfo("Mon_year", "monitor") + "/" + systemdispatcher.getHWSingleInfo("Mon_week", "monitor");
            sizeText.text = systemdispatcher.getHWSingleInfo("Mon_size", "monitor");
            inText.text = systemdispatcher.getHWSingleInfo("Mon_in", "monitor");
            maxmodeText.text = systemdispatcher.getHWSingleInfo("Mon_maxmode", "monitor");
            gammaText.text = systemdispatcher.getHWSingleInfo("Mon_gamma", "monitor");
            outputText.text = systemdispatcher.getHWSingleInfo("Mon_output", "monitor");
            supportText.text = systemdispatcher.getHWSingleInfo("Mon_support", "monitor");
        }
        else {
            productLabel.visible = false;
            vendorLabel.visible = false;
            dateLabel.visible = false;
            sizeLabel.visible = false;
            inLabel.visible = false;
            maxmodeLabel.visible = false;
            gammaLabel.visible = false;
            outputLabel.visible = false;
            supportLabel.visible = false;
            monitortitlebar.visible = false;
            montitle.visible = false;
            monitorlogo.visible = false;
        }
    }

    Connections
    {
        target: sessiondispatcher
        onTellDetailPageUpdateData: {
            if (infoFlag == "monitor") {
                home.init_data();
            }
        }
    }

    Component {
        id: monitorDelegate
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

    Common.ScrollArea {
        frame:false
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: 30
        height: parent.height - 40
        width: parent.width
        Column {
            anchors {
                top: parent.top
                topMargin: 10
                left: parent.left
                leftMargin: 30
            }
            spacing: 18

            Row {
                Common.Label {
                    id: titlebar
                    text: qsTr("Graphics Card Info")//显卡信息
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
                spacing: 10
                Item {
                    id: listItem
                    width: parent.width
                    height: 0
                    Column {
                        spacing: home.columnSpace
                        anchors {
                            left: parent.left
//                            leftMargin: 30
                        }
                        Item {
                            width: 680 - 4 - 30*2
                            height: home.firstFlag ? (home.itemNum*20 + (home.itemNum - 1)*10) + 20 : 0
                            ListView {
                                id: firstView
                                anchors.fill: parent
                                model: firstModel
                                delegate: monitorDelegate
                                visible: false
                                spacing: home.columnSpace
                            }
                            Image {
                                id: logo1
                                visible: false
                                opacity: 0.5
                                source: ""
                                anchors {
                                    right: parent.right
                                    top:parent.top
                                    topMargin: 40
                                }
                            }
                        }

                        Common.Separator {
                            id: splitbar2
                            width: 680 - 4 - 30*2
                            visible: false
                        }
                        Item {
                            width: 680 - 4 - 30*2
                            height: home.secondFlag ? (home.itemNum*20 + (home.itemNum - 1)*10) + 20 : 0
                            ListView {
                                id: secondView
                                anchors.fill: parent
                                model: secondModel
                                delegate: monitorDelegate
                                visible: false
                                spacing: home.columnSpace
                            }
                            Image {
                                id: logo2
                                visible: false
                                opacity: 0.5
                                source: ""
                                anchors {
                                    right: parent.right
                                    top:parent.top
                                    topMargin: 40
                                }
                            }
                        }
                        Common.Separator {
                            id: splitbar3
                            width: 680 - 4 - 30*2
                            visible: false
                        }
                        Item {
                            width: 680 - 4 - 30*2
                            height: home.thirdFlag ? (home.itemNum*20 + (home.itemNum - 1)*10) + 20 : 0
                            ListView {
                                id: thirdView
                                anchors.fill: parent
                                model: thirdModel
                                delegate: monitorDelegate
                                visible: false
                                spacing: home.columnSpace
                            }
                            Image {
                                id: logo3
                                visible: false
                                opacity: 0.5
                                source: ""
                                anchors {
                                    right: parent.right
                                    top:parent.top
                                    topMargin: 40
                                }
                            }
                        }
                        Common.Separator {
                            id: splitbar4
                            width: 680 - 4 - 30*2
                            visible: false
                        }
                        Item {
                            width: 680 - 4 - 30*2
                            height: home.fourthFlag ? (home.itemNum*20 + (home.itemNum - 1)*10) + 20 : 0
                            ListView {
                                id: fourthView
                                anchors.fill: parent
                                model: fourthModel
                                delegate: monitorDelegate
                                visible: false
                                spacing: home.columnSpace
                            }
                            Image {
                                id: logo4
                                visible: false
                                opacity: 0.5
                                source: ""
                                anchors {
                                    right: parent.right
                                    top:parent.top
                                    topMargin: 40
                                }
                            }
                        }
                    }
                }//Item
            }

            Row {
                Common.Label {
                    id: monitortitlebar
                    text: qsTr("Monitor Info")//显示器信息
                    font.bold: true
                    font.pixelSize: 14
                    color: "#383838"
                }
                Common.Separator {
                    id: montitle
                    anchors.verticalCenter: parent.verticalCenter
                    width: home.width - monitortitlebar.width - 30 * 2
                }
            }
            Row{
                anchors.left: parent.left
                anchors.leftMargin: 20
                Column {
                    spacing: 10
                    Row {
                        spacing: home.columnSpace
                        Common.Label {
                            id: productLabel
                            text: qsTr("Monitor: ")//显示器：
                            font.pixelSize: 14
                            color: "#7a7a7a"
                            width: 150
                        }
                        Text {
                            id: productText
                            text: ""//systemdispatcher.getHWSingleInfo("Mon_product")
                            width:360
                            font.pixelSize: 14
                            color: "#7a7a7a"
                        }
                    }
                    Row {
                        spacing: 10
                        Common.Label {
                            id: vendorLabel
                            text: qsTr("Vendor: ")//制造商：
                            font.pixelSize: 14
                            color: "#7a7a7a"
                            width: 150
                        }
                        Text {
                            id: vendorText
                            text: ""//systemdispatcher.getHWSingleInfo("Mon_vendor")
                            font.pixelSize: 14
                            color: "#7a7a7a"
                        }
                    }
                    Row {
                        spacing: 10
                        Common.Label {
                            id: dateLabel
                            text: qsTr("Production(year/week): ")//生产日期(年/周)：
                            font.pixelSize: 14
                            color: "#7a7a7a"
                            width: 150
                        }
                        Text {
                            id: dateText
                            text: ""//systemdispatcher.getHWSingleInfo("Mon_year")
                            font.pixelSize: 14
                            color: "#7a7a7a"
                        }
                    }
                    Row {
                        spacing: 10
                        Common.Label {
                            id: sizeLabel
                            text: qsTr("Display Area: ")//可视面积：
                            font.pixelSize: 14
                            color: "#7a7a7a"
                            width: 150
                        }
                        Text {
                            id: sizeText
                            text: ""//systemdispatcher.getHWSingleInfo("Mon_size")
                            font.pixelSize: 14
                            color: "#7a7a7a"
                        }
                    }
                    Row {
                        spacing: 10
                        Common.Label {
                            id: inLabel
                            text: qsTr("Dimensions: ")//屏幕尺寸：
                            font.pixelSize: 14
                            color: "#7a7a7a"
                            width: 150
                        }
                        Text {
                            id: inText
                            text: ""//systemdispatcher.getHWSingleInfo("Mon_in")
                            font.pixelSize: 14
                            color: "#7a7a7a"
                        }
                    }
                    Row {
                        spacing: 10
                        Common.Label {
                            id: maxmodeLabel
                            text: qsTr("Max Resolution: ")//最大分辨率：
                            font.pixelSize: 14
                            color: "#7a7a7a"
                            width: 150
                        }
                        Text {
                            id: maxmodeText
                            text: ""//systemdispatcher.getHWSingleInfo("Mon_maxmode")
                            font.pixelSize: 14
                            color: "#7a7a7a"
                        }
                    }
                    Row {
                        spacing: 10
                        Common.Label {
                            id: gammaLabel
                            text: qsTr("Gamma Value: ")//伽马值：
                            font.pixelSize: 14
                            color: "#7a7a7a"
                            width: 150
                        }
                        Text {
                            id: gammaText
                            text: ""//systemdispatcher.getHWSingleInfo("Mon_gamma")
                            font.pixelSize: 14
                            color: "#7a7a7a"
                        }
                    }
                    Row {
                        spacing: 10
                        Common.Label {
                            id: outputLabel
                            text: qsTr("Current Output: ")//当前接口：
                            font.pixelSize: 14
                            color: "#7a7a7a"
                            width: 150
                        }
                        Text {
                            id: outputText
                            text: ""//systemdispatcher.getHWSingleInfo("Mon_output")
                            font.pixelSize: 14
                            color: "#7a7a7a"
                        }
                    }
                    Row {
                        spacing: 10
                        height: 40
                        Common.Label {
                            id: supportLabel
                            text: qsTr("Support Output: ")//支持接口：
                            font.pixelSize: 14
                            color: "#7a7a7a"
                            width: 150
                        }
                        Text {
                            id: supportText
                            text: ""//systemdispatcher.getHWSingleInfo("Mon_support")
                            font.pixelSize: 14
                            color: "#7a7a7a"
                        }
                    }
                }
                Image {
                    id: monitorlogo
                    source: ""
                    opacity: 0.5
                    anchors {
                        top: parent.top
                    }
                }
            }
        }
    }
}
