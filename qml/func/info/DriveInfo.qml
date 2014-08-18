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
import "./InfoGroup.js" as InfoGroup

Rectangle {
    id: home
    width: parent.width; height: 476
//    color: "transparent"
//    color: "#e4f2fc"
    property int rowNumber: 0//对有效行计数
    property int itemNumber: 0//对项目的计数s
    property string hbridge: qsTr("Host bridge:")//主桥
    property string vga: qsTr("VGA Model:")//VGA兼容控制器
    property string usb: qsTr("USB Model:")//USB控制器
    property string communication: qsTr("Communication Model:")//通信控制器
    property string ethernet: qsTr("Ethernet Model:")//以太网控制器
    property string audio: qsTr("Audio Model:")//音频设备
    property string pci: qsTr("PCI bridge:")//PCI桥
    property string isa: qsTr("ISA bridge:")//ISA桥
    property string sata: qsTr("SATA Model:")//SATA控制器
    property string smbus: qsTr("SMBus:")//系统管理总线
    property string peripheral: qsTr("System peripheral:")//系统外围
    property string usedriver: qsTr("Driver in use:")//使用的驱动
    property string existdriver: qsTr("existing drivers:")//可选的驱动
    property string ide : qsTr("IDE interface:")//IDE接口
    property string sp : qsTr("SP controller:")//信号处理控制器
    property string net : qsTr("Network controller:")//网络控制器
    property string multi : qsTr("Multimedia audio controller:")//多媒体音频控制器

    function transTitle(str) {
        //去掉前后空格
        str = str.replace(/^(\s|\u00A0)+/,'');
        for(var i=str.length-1; i>=0; i--){
            if(/\S/.test(str.charAt(i))){
                str = str.substring(0, i+1);
                break;
            }
        }
        //开始国际化
        var pat1 = new RegExp('Host bridge');
        var pat2 = new RegExp('VGA compatible controller');
        var pat3 = new RegExp('USB controller');
        var pat4 = new RegExp('Communication controller');
        var pat5 = new RegExp('Ethernet controller');
        var pat6 = new RegExp('Audio device');
        var pat7 = new RegExp('PCI bridge');
        var pat8 = new RegExp('ISA bridge');
        var pat9 = new RegExp('SATA controller');
        var pat10 = new RegExp('SMBus');
        var pat11 = new RegExp('System peripheral');
        var pat12 = new RegExp('driver in use');
        var pat13 = new RegExp('existing drivers');
        var pat14 = new RegExp('IDE interface');
        var pat15 = new RegExp('Signal processing controller');
        var pat16 = new RegExp('Network controlle');
        var pat17 = new RegExp('Multimedia audio controller');
        if(pat1.test(str)) {
            return home.hbridge.toString();
        }
        else if(pat2.test(str)) {
            return home.vga.toString();
        }
        else if(pat3.test(str)) {
            return home.usb.toString();
        }
        else if(pat4.test(str)) {
            return home.communication.toString();
        }
        else if(pat5.test(str)) {
            return home.ethernet.toString();
        }
        else if(pat6.test(str)) {
            return home.audio.toString();
        }
        else if(pat7.test(str)) {
            return home.pci.toString();
        }
        else if(pat8.test(str)) {
            return home.isa.toString();
        }
        else if(pat9.test(str)) {
            return home.sata.toString();
        }
        else if(pat10.test(str)) {
            return home.smbus.toString();
        }
        else if(pat11.test(str)) {
            return home.peripheral.toString();
        }
        else if(pat12.test(str)) {
            return home.usedriver.toString();
        }
        else if(pat13.test(str)) {
            return home.existdriver.toString();
        }
        else if(pat14.test(str)) {
            return home.ide.toString();
        }
        else if(pat15.test(str)) {
            return home.sp.toString();
        }
        else if(pat16.test(str)) {
            return home.net.toString();
        }
        else if(pat17.test(str)) {
            return home.multi.toString();//"多媒体音频控制器：";
        }
        return str;
    }

    function appendDataList() {
        dataModel.clear();//清空dataModel
        home.rowNumber = 0;
        home.itemNumber += 0;

        var list = devicemanager.getDeviceMsg();
        for (var i=0 ; i < list.length ; i++) {
            var splitlist = list[i].split(";");
            if(splitlist.length == 1) {
                var name = splitlist[0].split(":");
                dataModel.append({"deviceName": home.transTitle(name[0]),  "deviceNameText": name[1], "inUseName": "", "inUseNameText": "", "existName": "", "existNameText": ""});
                //设备名字太长，让其使用两行
                home.rowNumber += 1;
                home.itemNumber += 1;
            }
            else if(splitlist.length == 2) {
                var name1 = splitlist[0].split(":");
                var name2 = splitlist[1].split(":");
                dataModel.append({"deviceName": home.transTitle(name1[0]),  "deviceNameText": name1[1], "inUseName": home.transTitle(name2[0]), "inUseNameText": name2[1], "existName": "", "existNameText": ""});
                //设备名字太长，让其使用两行
                home.rowNumber += 2;
                home.itemNumber += 1;
            }
            else if(splitlist.length == 3) {
                var name3 = splitlist[0].split(":");
                var name4 = splitlist[1].split(":");
                var name5 = splitlist[2].split(":");
                dataModel.append({"deviceName": home.transTitle(name3[0]),  "deviceNameText": name3[1], "inUseName": home.transTitle(name4[0]), "inUseNameText": name4[1], "existName": home.transTitle(name5[0]), "existNameText": name5[1]});
                //设备名字太长，让其使用两行
                home.rowNumber += 3;
                home.itemNumber += 1;
            }
        }
    }

    ListModel {
        id: dataModel
//        Component.onCompleted: {
//            home.appendDataList();
//        }
    }

    Connections
    {
        target: sessiondispatcher
        onTellDetailPageUpdateData: {
            if (infoFlag == "drive") {
                home.appendDataList();
            }
        }
    }

    Component {
        id: deviceDelegate
        Column {
//            spacing: 1
            Column {
                spacing: 20
                Row {
                    spacing: 10
                    Common.Label {
                        id:device
                        text: deviceName
                        font.pixelSize: 14
                        color: "#7a7a7a"
                        width: 140
                        clip: true
                        height: 20
                    }
                    Text {
                        text: deviceNameText
                        width: 480
                        elide: Text.ElideRight
//                        elide: Text.ElideMiddle
                        font.pixelSize: 14
                        wrapMode: Text.WordWrap
                        color: "#7a7a7a"
                        height: 20
                    }
                }
                Row {
                    spacing: 10
                    Common.Label {
                        text: inUseName
                        visible: (inUseName == "") ? false : true
                        font.pixelSize: 14
                        color: "#7a7a7a"
                        width: 140
                        clip: true
                        height: 20
                    }
                    Text {
                        text: inUseNameText
                        width: 480
                        elide: Text.ElideRight
                        visible: (inUseNameText == "") ? false : true
                        font.pixelSize: 14
                        color: "#7a7a7a"
                        height: 20
                    }
                }
                Row {
                    spacing: 10
                    Common.Label {
                        text: existName
                        visible: (existName == "") ? false : true
                        font.pixelSize: 14
                        color: "#7a7a7a"
                        width: 140
                        clip: true
                        height: 20
                    }
                    Text {
                        text: existNameText
                        width: 480
                        elide: Text.ElideRight
                        visible: (existNameText == "") ? false : true
                        font.pixelSize: 14
                        color: "#7a7a7a"
                        height: 20
                    }
                }
            }
            Common.Separator {
                width: parent.width - 20
                visible: (device.text == "") ? false : true
            }
        }
    }
    Row {
        id: titleRow
        anchors {
            top: parent.top
            topMargin: 40
            left: parent.left
            leftMargin: 20
        }
        Common.Label {
            id: titlebar
            text: qsTr("Device Driver Info")//设备驱动信息
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
        anchors.leftMargin: 30
        anchors.top: titleRow.bottom
        anchors.topMargin: 20
        height: 396
        width: 680 - 14
        Item {
            id: listItem
            width: parent.width
            height: home.rowNumber*20 + (home.rowNumber - 1)*20 + (home.itemNumber - 1) * 10 + 20
            ListView {
                id: deviceView
                anchors.fill: parent
                model: dataModel
                delegate: deviceDelegate
                spacing: 10
            }
        }
    }
}
