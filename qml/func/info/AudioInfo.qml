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

/*------------------最多支持四个声卡的显示------------------*/
Rectangle {
    id: home; width: parent.width; height: 476

    property int itemNum: 4//每个模块的子项个数
    property int viewSpace: 10
    property bool firstFlag: false
    property bool secondFlag: false
    property bool thirdFlag: false
    property bool fourthFlag: false
    property string homepath
    ListModel {id: firstModel}
    ListModel {id: secondModel}
    ListModel {id: thirdModel}
    ListModel {id: fourthModel}

    Component.onCompleted: {
        home.homepath = sessiondispatcher.getHomePath();
    }

    function show_several_audio(num)
    {
        var audiomodel = systemdispatcher.getHWSingleInfo("MulProduct", "audiocard").split("<1_1>");//声卡型号：
        var vendorname = systemdispatcher.getHWSingleInfo("MulVendor", "audiocard").split("<1_1>");//制造商：
        var address = systemdispatcher.getHWSingleInfo("MulBusinfo", "audiocard").split("<1_1>");//总线地址：
        var drivers = systemdispatcher.getHWSingleInfo("MulDrive", "audiocard").split("<1_1>");//声卡驱动：

        //--------------first--------------
        home.firstFlag = true;
        firstView.visible = true;
        firstModel.clear();
        firstModel.append({"title": qsTr("Audio Model:"), "result": audiomodel[0]});//声卡型号：
        firstModel.append({"title": qsTr("Vendor:"), "result": vendorname[0]});//制造商：
        firstModel.append({"title": qsTr("Bus Address:"), "result": address[0]});//总线地址：
        firstModel.append({"title": qsTr("Audio Driver:"), "result": drivers[0]});//声卡驱动：

        splitbar1.visible = true;
        logo1.visible = true;
        logo1.source = InfoGroup.judgeName(vendorname[0].toUpperCase()) ? (home.homepath + "/.cache/youker-assistant/uk-img/Manufacturer/" + vendorname[0].toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
        //--------------second--------------
        home.secondFlag = true;
        secondView.visible = true;
        secondModel.clear();

        secondModel.append({"title": qsTr("Audio Model:"), "result": audiomodel[1]});//声卡型号：
        secondModel.append({"title": qsTr("Vendor:"), "result": vendorname[1]});//制造商：
        secondModel.append({"title": qsTr("Bus Address:"), "result": address[1]});//总线地址：
        secondModel.append({"title": qsTr("Audio Driver:"), "result": drivers[1]});//声卡驱动：
        splitbar2.visible = true;
        logo2.visible = true;
        logo2.source = InfoGroup.judgeName(vendorname[1].toUpperCase()) ? (home.homepath + "/.cache/youker-assistant/uk-img/Manufacturer/" + vendorname[1].toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
        if(num == 2) {
            //(每个ListView子项的个数×子项高度 + (子项个数-1)×子项与子项的间隔 + 分隔条的上下间隔) × 内存条个数
            listItem.height = (home.itemNum*20 + (home.itemNum - 1)*10 + 10*2) *2 + 40;
        }
        else if(num >= 3) {
            //--------------third--------------
            home.thirdFlag = true;
            thirdView.visible = true;
            thirdModel.clear();

            thirdModel.append({"title": qsTr("Audio Model:"), "result": audiomodel[2]});//声卡型号：
            thirdModel.append({"title": qsTr("Vendor:"), "result": vendorname[2]});//制造商：
            thirdModel.append({"title": qsTr("Bus Address:"), "result": address[2]});//总线地址：
            thirdModel.append({"title": qsTr("Audio Driver:"), "result": drivers[2]});//声卡驱动：
            splitbar3.visible = true;
            logo3.visible = true;
            logo3.source = InfoGroup.judgeName(vendorname[2].toUpperCase()) ? (home.homepath + "/.cache/youker-assistant/uk-img/Manufacturer/" + vendorname[2].toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
            if(num == 3) {
                //(每个ListView子项的个数×子项高度 + (子项个数-1)×子项与子项的间隔 + 分隔条的上下间隔) × 内存条个数
                listItem.height = (home.itemNum*20 + (home.itemNum - 1)*10 + 10*2) *3 + 60;
            }
            else if(num == 4) {
                home.fourthFlag = true;
                fourthView.visible = true;
                fourthModel.clear();

                fourthModel.append({"title": qsTr("Audio Model:"), "result": audiomodel[3]});//声卡型号：
                fourthModel.append({"title": qsTr("Vendor:"), "result": vendorname[3]});//制造商：
                fourthModel.append({"title": qsTr("Bus Address:"), "result": address[3]});//总线地址：
                fourthModel.append({"title": qsTr("Audio Driver:"), "result": drivers[3]});//声卡驱动：
                splitbar4.visible = true;
                logo4.visible = true;
                logo4.source = InfoGroup.judgeName(vendorname[3].toUpperCase()) ? (home.homepath + "/.cache/youker-assistant/uk-img/Manufacturer/" + vendorname[3].toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
                //(每个ListView子项的个数×子项高度 + (子项个数-1)×子项与子项的间隔 + 分隔条的上下间隔) × 内存条个数
                listItem.height = (home.itemNum*20 + (home.itemNum - 1)*10 + 10*2) * + 80;
            }
        }
    }


    function init_data() {
        home.firstFlag = false;
        home.secondFlag = false;
        home.thirdFlag = false;
        home.fourthFlag = false;
        systemdispatcher.get_audiocard_info_qt();//获取详细信息
        var num = systemdispatcher.getHWSingleInfo("MulNum", "audiocard");
        if(num == 1) {
            home.firstFlag = true;
            firstView.visible = true;
            var vendorName = systemdispatcher.getHWSingleInfo("MulVendor", "audiocard");
            firstModel.clear();
            firstModel.append({"title": qsTr("Audio Model:"), "result": systemdispatcher.getHWSingleInfo("MulProduct", "audiocard")});//声卡型号：
            firstModel.append({"title": qsTr("Vendor:"), "result": vendorName});//制造商：
            firstModel.append({"title": qsTr("Bus Address:"), "result": systemdispatcher.getHWSingleInfo("MulBusinfo", "audiocard")});//总线地址：
            firstModel.append({"title": qsTr("Audio Driver:"), "result": systemdispatcher.getHWSingleInfo("MulDrive", "audiocard")});//声卡驱动：

            splitbar1.visible = true;
            logo1.visible = true;
            logo1.source = InfoGroup.judgeName(vendorName.toUpperCase()) ? (home.homepath + "/.cache/youker-assistant/uk-img/Manufacturer/" + vendorName.toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
            //(每个ListView子项的个数×子项高度 + (子项个数-1)×子项与子项的间隔 + 分隔条的上下间隔) × 内存条个数
            listItem.height = home.itemNum*20 + (home.itemNum - 1)*home.viewSpace + home.viewSpace*2 + 20;
        }
        else if(num >= 2){
            home.show_several_audio(num);
        }
    }

    Connections
    {
        target: sessiondispatcher
        onTellDetailPageUpdateData: {
            if (infoFlag == "audiocard") {
                home.init_data();
            }
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
            text: qsTr("Audio Info")//音频信息
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
                    height: home.firstFlag ? (home.itemNum*20 + (home.itemNum - 1)*home.viewSpace) + 20 : 0
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
                        opacity: 0.5
                        source: ""
                        anchors {
                            top: parent.top
                            topMargin: 30
                            right: parent.right
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
                    height: home.secondFlag ? (home.itemNum*20 + (home.itemNum - 1)*home.viewSpace) + 20 : 0
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
                        opacity: 0.5
                        source: ""
                        anchors {
                            top: parent.top
                            topMargin: 30
                            right: parent.right
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
                    height: home.thirdFlag ? (home.itemNum*20 + (home.itemNum - 1)*home.viewSpace) + 20 : 0
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
                        opacity: 0.5
                        source: ""
                        anchors {
                            top: parent.top
                            topMargin: 30
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
                    height: home.fourthFlag ? (home.itemNum*20 + (home.itemNum - 1)*home.viewSpace) + 20 : 0
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
                        opacity: 0.5
                        source: ""
                        anchors {
                            top: parent.top
                            topMargin: 30
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
