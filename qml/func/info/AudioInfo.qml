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

/*------------------最多支持四个声卡的显示------------------*/
Rectangle {
    id: home; width: parent.width; height: 475
    color: "transparent"
    property int itemNum: 4//每个模块的子项个数
    property int viewSpace: 20
    property bool firstFlag: false
    property bool secondFlag: false
    property bool thirdFlag: false
    property bool fourthFlag: false
    ListModel {id: firstModel}
    ListModel {id: secondModel}
    ListModel {id: thirdModel}
    ListModel {id: fourthModel}

    function show_several_audio(num)
    {
        var audiomodel = systemdispatcher.getSingleInfo("MulProduct", "audiocard").split("/");//声卡型号：
        var vendorname = systemdispatcher.getSingleInfo("MulVendor", "audiocard").split("/");//制造商：
        var address = systemdispatcher.getSingleInfo("MulBusinfo", "audiocard").split("/");//总线地址：
        var drivers = systemdispatcher.getSingleInfo("MulDrive", "audiocard").split("/");//声卡驱动：

        //--------------first--------------
        home.firstFlag = true;
        firstView.visible = true;
        firstModel.clear();

        firstModel.append({"title": qsTr("Vendor:"), "result": vendorname[0]});//制造商：
        firstModel.append({"title": qsTr("Bus Address:"), "result": address[0]});//总线地址：
        firstModel.append({"title": qsTr("Audio Driver:"), "result": drivers[0]});//声卡驱动：
        firstModel.append({"title": qsTr("Audio Model:"), "result": audiomodel[0]});//声卡型号：

        splitbar1.visible = true;
        logo1.visible = true;
        logo1.source = InfoGroup.judgeName(vendorname[0].toUpperCase()) ? ("../../img/logo/Manufacturer/" + vendorname[0].toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
        //--------------second--------------
        home.secondFlag = true;
        secondView.visible = true;
        secondModel.clear();

        secondModel.append({"title": qsTr("Vendor:"), "result": vendorname[1]});//制造商：
        secondModel.append({"title": qsTr("Bus Address:"), "result": address[1]});//总线地址：
        secondModel.append({"title": qsTr("Audio Driver:"), "result": drivers[1]});//声卡驱动：
        secondModel.append({"title": qsTr("Audio Model:"), "result": audiomodel[1]});//声卡型号：
        splitbar2.visible = true;
        logo2.visible = true;
        logo2.source = InfoGroup.judgeName(vendorname[1].toUpperCase()) ? ("../../img/logo/Manufacturer/" + vendorname[1].toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
        if(num == 2) {
            //(每个ListView子项的个数×子项高度 + (子项个数-1)×子项与子项的间隔 + 分隔条的上下间隔) × 内存条个数
            listItem.height = (home.itemNum*20 + (home.itemNum - 1)*10 + 10*2) *2;
        }
        else if(num >= 3) {
            //--------------third--------------
            home.thirdFlag = true;
            thirdView.visible = true;
            thirdModel.clear();

            thirdModel.append({"title": qsTr("Vendor:"), "result": vendorname[2]});//制造商：
            thirdModel.append({"title": qsTr("Bus Address:"), "result": address[2]});//总线地址：
            thirdModel.append({"title": qsTr("Audio Driver:"), "result": drivers[2]});//声卡驱动：
            thirdModel.append({"title": qsTr("Audio Model:"), "result": audiomodel[2]});//声卡型号：
            splitbar3.visible = true;
            logo3.visible = true;
            logo3.source = InfoGroup.judgeName(vendorname[2].toUpperCase()) ? ("../../img/logo/Manufacturer/" + vendorname[2].toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
            if(num == 3) {
                //(每个ListView子项的个数×子项高度 + (子项个数-1)×子项与子项的间隔 + 分隔条的上下间隔) × 内存条个数
                listItem.height = (home.itemNum*20 + (home.itemNum - 1)*10 + 10*2) *3;
            }
            else if(num == 4) {
                home.fourthFlag = true;
                fourthView.visible = true;
                fourthModel.clear();

                fourthModel.append({"title": qsTr("Vendor:"), "result": vendorname[3]});//制造商：
                fourthModel.append({"title": qsTr("Bus Address:"), "result": address[3]});//总线地址：
                fourthModel.append({"title": qsTr("Audio Driver:"), "result": drivers[3]});//声卡驱动：
                fourthModel.append({"title": qsTr("Audio Model:"), "result": audiomodel[3]});//声卡型号：
                splitbar4.visible = true;
                logo4.visible = true;
                logo4.source = InfoGroup.judgeName(vendorname[3].toUpperCase()) ? ("../../img/logo/Manufacturer/" + vendorname[3].toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
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
        systemdispatcher.get_audiocard_info_qt();//获取详细信息
        var num = systemdispatcher.getSingleInfo("MulNum", "audiocard");
        if(num == 1) {
            home.firstFlag = true;
            firstView.visible = true;
            var vendorName = systemdispatcher.getSingleInfo("MulVendor", "audiocard");
            firstModel.clear();
            firstModel.append({"title": qsTr("Audio Model:"), "result": systemdispatcher.getSingleInfo("MulProduct", "audiocard")});//声卡型号：
            firstModel.append({"title": qsTr("Vendor:"), "result": vendorName});//制造商：
            firstModel.append({"title": qsTr("Bus Address:"), "result": systemdispatcher.getSingleInfo("MulBusinfo", "audiocard")});//总线地址：
            firstModel.append({"title": qsTr("Audio Driver:"), "result": systemdispatcher.getSingleInfo("MulDrive", "audiocard")});//声卡驱动：

            splitbar1.visible = true;
            logo1.visible = true;
            logo1.source = InfoGroup.judgeName(vendorName.toUpperCase()) ? ("../../img/logo/Manufacturer/" + vendorName.toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
            //(每个ListView子项的个数×子项高度 + (子项个数-1)×子项与子项的间隔 + 分隔条的上下间隔) × 内存条个数
            listItem.height = home.itemNum*20 + (home.itemNum - 1)*home.viewSpace + home.viewSpace*2;
        }
        else if(num >= 2){
            home.show_several_audio(num);
        }
    }

    Component {
        id: audioDelegate
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
                width: 500
                wrapMode: Text.WordWrap
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
            text: qsTr("Audio Card Info")//声卡信息
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
                    height: home.firstFlag ? (home.itemNum*20 + (home.itemNum - 1)*home.viewSpace) : 0
                    ListView {
                        id: firstView
                        anchors.fill: parent
                        model: firstModel
                        delegate: audioDelegate
                        visible: false
                        spacing: home.viewSpace
                    }
                    Image {
                        id: logo1
                        visible: false
                        source: ""
                        anchors {
                            top: parent.top
                            topMargin: 50
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
                Item {
                    width: parent.width
                    height: home.secondFlag ? (home.itemNum*20 + (home.itemNum - 1)*home.viewSpace) : 0
                    ListView {
                        id: secondView
                        anchors.fill: parent
                        model: secondModel
                        delegate: audioDelegate
                        visible: false
                        spacing: home.viewSpace
                    }
                    Image {
                        id: logo2
                        visible: false
                        source: ""
                        anchors {
                            top: parent.top
                            topMargin: 50
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
                Item {
                    width: parent.width
                    height: home.thirdFlag ? (home.itemNum*20 + (home.itemNum - 1)*home.viewSpace) : 0
                    ListView {
                        id: thirdView
                        anchors.fill: parent
                        model: thirdModel
                        delegate: audioDelegate
                        visible: false
                        spacing: home.viewSpace
                    }
                    Image {
                        id: logo3
                        visible: false
                        source: ""
                        anchors {
                            top: parent.top
                            topMargin: 50
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
                    height: home.fourthFlag ? (home.itemNum*20 + (home.itemNum - 1)*home.viewSpace) : 0
                    ListView {
                        id: fourthView
                        anchors.fill: parent
                        model: fourthModel
                        delegate: audioDelegate
                        visible: false
                        spacing: home.viewSpace
                    }
                    Image {
                        id: logo4
                        visible: false
                        source: ""
                        anchors {
                            top: parent.top
                            topMargin: 50
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
