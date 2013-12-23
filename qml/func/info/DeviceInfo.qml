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

/*(" Host bridge: Intel Corporation 2nd Generation Core Processor Family DRAM Controller (rev 09)",
 " VGA compatible controller: Intel Corporation 2nd Generation Core Processor Family Integrated Graphics Controller (rev 09);driver in use: i915",
" USB controller: Intel Corporation 7 Series/C210 Series Chipset Family USB xHCI Host Controller (rev 04);driver in use: xhci_hcd",
" Communication controller: Intel Corporation 7 Series/C210 Series Chipset Family MEI Controller #1 (rev 04);driver in use: mei_me",
" Ethernet controller: Intel Corporation 82579LM Gigabit Network Connection (rev 04);driver in use: e1000e",
" USB controller: Intel Corporation 7 Series/C210 Series Chipset Family USB Enhanced Host Controller #2 (rev 04);driver in use: ehci-pci",
" Audio device: Intel Corporation 7 Series/C210 Series Chipset Family High Definition Audio Controller (rev 04);driver in use: snd_hda_intel",
" PCI bridge: Intel Corporation 7 Series/C210 Series Chipset Family PCI Express Root Port 1 (rev c4);driver in use: pcieport",
" PCI bridge: Intel Corporation 7 Series/C210 Series Chipset Family PCI Express Root Port 2 (rev c4);driver in use: pcieport",
" PCI bridge: Intel Corporation 7 Series/C210 Series Chipset Family PCI Express Root Port 3 (rev c4);driver in use: pcieport",
" USB controller: Intel Corporation 7 Series/C210 Series Chipset Family USB Enhanced Host Controller #1 (rev 04);driver in use: ehci-pci",
" ISA bridge: Intel Corporation QM77 Express Chipset LPC Controller (rev 04);driver in use: lpc_ich",
" SATA controller: Intel Corporation 7 Series Chipset Family 6-port SATA Controller [AHCI mode] (rev 04);driver in use: ahci",
" SMBus: Intel Corporation 7 Series/C210 Series Chipset Family SMBus Controller (rev 04)",
" System peripheral: Ricoh Co Ltd PCIe SDXC/MMC Host Controller (rev 07);driver in use: sdhci-pci") */

Rectangle {
    id: home
    width: parent.width; height: 475
    color: "transparent"
    property int rowNumber: 0//对有效行计数

    function appendDataList() {
        dataModel.clear();//清空dataModel
        home.rowNumber = 0;

        var list = devicemanager.getDeviceMsg();
        for (var i=0 ; i < list.length ; i++) {
            //        var pat = new RegExp('Intel');
            //        if(pat.test(msg)) {
            //            logo.source =  "../../img/logo/Manufacturer/INTEL.jpg";
            //        }
            var splitlist = list[i].split(";");
            if(splitlist.length == 1) {
//                console.log('----------111-----------');
                var name = splitlist[0].split(":");
//                console.log(name[0]);
//                console.log(name[1]);
                dataModel.append({"deviceName": name[0],  "deviceNameText": name[1], "inUseName": "", "inUseNameText": "", "existName": "", "existNameText": ""});
                home.rowNumber += 1;
            }
            else if(splitlist.length == 2) {
//                console.log('----------222-----------');
                var name1 = splitlist[0].split(":");
//                console.log(name1[0]);
//                console.log(name1[1]);
                var name2 = splitlist[1].split(":");
//                console.log(name2[0]);
//                console.log(name2[1]);
                dataModel.append({"deviceName": name1[0],  "deviceNameText": name1[1], "inUseName": name2[0], "inUseNameText": name2[1], "existName": "", "existNameText": ""});
                home.rowNumber += 2;
            }
            else if(splitlist.length == 3) {
//                console.log('----------333-----------');
                var name3 = splitlist[0].split(":");
//                console.log(name3[0]);
//                console.log(name3[1]);
                var name4 = splitlist[1].split(":");
//                console.log(name4[0]);
//                console.log(name4[1]);
                var name5 = splitlist[2].split(":");
//                console.log(name5[0]);
//                console.log(name5[1]);
                dataModel.append({"deviceName": name3[0],  "deviceNameText": name3[1], "inUseName": name4[0], "inUseNameText": name4[1], "existName": name5[0], "existNameText": name5[1]});
                home.rowNumber += 3;
            }
        }
    }

    ListModel {
        id: dataModel
        Component.onCompleted: {
            home.appendDataList();
        }
    }

    Component {
        id: deviceDelegate
        Column {
            spacing: 5
            Row {
                spacing: 10
                Common.Label {
                    text: deviceName
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 120
                    height: 20
                }
                Text {
                    text: deviceNameText
                    font.pixelSize: 14
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
                    width: 120
                    height: 20
                }
                Text {
                    text: inUseNameText
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
                    width: 120
                    height: 20
                }
                Text {
                    text: existNameText
                    visible: (existNameText == "") ? false : true
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    height: 20
                }
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
            text: qsTr("Device Driver Information")//设备驱动信息
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
            height: home.rowNumber*20 + (home.rowNumber - 1)*10
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
