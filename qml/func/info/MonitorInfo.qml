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
    id: home; width: parent.width; height: 475
    color: "transparent"

    Component.onCompleted: {
        systemdispatcher.get_monitor_info_qt();//获取详细信息
        chipText.text = systemdispatcher.getHWSingleInfo("Mon_chip", "monitor");
        chipmodelText.text = systemdispatcher.getHWSingleInfo("Vga_product", "monitor");
        var cardVendor = systemdispatcher.getHWSingleInfo("Vga_vendor", "monitor");
        chipvendorText.text = cardVendor;
        driverText.text = systemdispatcher.getHWSingleInfo("Vga_Drive", "monitor");
        cardlogo.source = InfoGroup.judgeName(cardVendor.toUpperCase()) ? ("../../img/logo/Manufacturer/" + cardVendor.toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
        chipbusText.text = systemdispatcher.getHWSingleInfo("Vga_businfo", "monitor");
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
            var vendorName = systemdispatcher.getHWSingleInfo("Mon_vendor", "monitor");
            monitorlogo.source = InfoGroup.judgeName(vendorName.toUpperCase()) ? ("../../img/logo/Manufacturer/" + vendorName.toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
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
                Row {
                    spacing: 10
                    Common.Label {
                        text: qsTr("Graphics Card Model: ")//显卡型号：
                        font.pixelSize: 14
                        color: "#7a7a7a"
                        width: 150
                    }
                    Text {
                        id: chipmodelText
                        width: 450
                        text: ""//systemdispatcher.getHWSingleInfo("Vga_product")
                        font.pixelSize: 14
                        wrapMode: Text.WordWrap
                        color: "#7a7a7a"
                    }
                }
                Row {
                    spacing: 10
                    Common.Label {
                        text: qsTr("Current Graphics Card: ")//当前显卡：
                        font.pixelSize: 14
                        color: "#7a7a7a"
                        width: 150
                    }
                    Text {
                        id: chipText
                        text: ""//systemdispatcher.getHWSingleInfo("Mon_chip")
                        font.pixelSize: 14
                        color: "#7a7a7a"
                    }
                }
                Row {
                    spacing: 10
                    Common.Label {
                        text: qsTr("Graphics Card Vendor: ")//显卡制造商：
                        font.pixelSize: 14
                        color: "#7a7a7a"
                        width: 150
                    }
                    Text {
                        id: chipvendorText
                        text: ""//systemdispatcher.getHWSingleInfo("Vga_vendor")
                        font.pixelSize: 14
                        color: "#7a7a7a"
                    }
                }
                Row {
                    spacing: 10
                    Common.Label {
                        text: qsTr("Graphics Driver: ")//显卡驱动：
                        font.pixelSize: 14
                        color: "#7a7a7a"
                        width: 150
                    }
                    Text {
                        id: driverText
                        text: ""//systemdispatcher.getHWSingleInfo("Vga_Drive")
                        font.pixelSize: 14
                        color: "#7a7a7a"
                    }
                }
                Row {
                    spacing: 10
                    Common.Label {
                        text: qsTr("Bus Address: ")//显卡总线地址：
                        font.pixelSize: 14
                        color: "#7a7a7a"
                        width: 150
                    }
                    Text {
                        id: chipbusText
                        text: ""//systemdispatcher.getHWSingleInfo("Vga_businfo")
                        font.pixelSize: 14
                        color: "#7a7a7a"
                    }
                }
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
                    anchors.verticalCenter: parent.verticalCenter
                    width: home.width - monitortitlebar.width - 30 * 2
                }
            }
            Column {
                anchors.left: parent.left
                anchors.leftMargin: 20
                spacing: 10
                Row {
                    spacing: 10
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
        }

        //logo
        Image {
            id: cardlogo
            source: ""
            anchors {
                top: parent.top
                topMargin: 75
                left: parent.left
                leftMargin: 570
            }
        }
        //logo
        Image {
            id: monitorlogo
            source: ""
            anchors {
                top: parent.top
                topMargin: 250
                left: parent.left
                leftMargin: 570
            }
        }
    }
}
