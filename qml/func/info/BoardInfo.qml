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
        systemdispatcher.get_board_info_qt();//获取详细信息

        var basicName = systemdispatcher.getHWSingleInfo("BoaVendor", "board").toUpperCase();
        var biosName = systemdispatcher.getHWSingleInfo("BioVendor", "board").toUpperCase();
        basiclogo.source = InfoGroup.judgeName(basicName) ? ("../../img/logo/Manufacturer/" + basicName + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
        bioslogo.source = InfoGroup.judgeName(biosName) ? ("../../img/logo/Manufacturer/" + biosName + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");

        productText.text = systemdispatcher.getHWSingleInfo("BoaProduct", "board");
        vendorText.text = basicName;
        serialText.text = systemdispatcher.getHWSingleInfo("BoaSerial", "board");
        biosvendorText.text = biosName;
        biosversionText.text = systemdispatcher.getHWSingleInfo("BioVersion", "board");
        biosreleaseText.text = systemdispatcher.getHWSingleInfo("BioRelease", "board");
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
                id: basictitle
                text: qsTr("Motherboard Basics Info")//主板基本信息
                font.bold: true
                font.pixelSize: 14
                color: "#383838"
            }
            Common.Separator {
                anchors.verticalCenter: parent.verticalCenter
                width: home.width - basictitle.width - 30 * 2
            }
        }
        Column {
            anchors.left: parent.left
            anchors.leftMargin: 20
            spacing: 10
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Motherboard Model: ")//主板型号：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 150
                }
                Text {
                    id: productText
                    text: ""//systemdispatcher.getHWSingleInfo("BoaProduct")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Motherboard Vendor: ")//主板产商：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 150
                }
                Text {
                    id: vendorText
                    text: ""//systemdispatcher.getHWSingleInfo("BoaVendor")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Serial Number: ")//序列号：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 150
                }
                Text {
                    id: serialText
                    text: ""//systemdispatcher.getHWSingleInfo("BoaSerial")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
        }
        Row {
            Common.Label {
                id: biostitle
                text: qsTr("BIOS Info")//BIOS信息
                font.bold: true
                font.pixelSize: 14
                color: "#383838"
            }
            Common.Separator {
                anchors.verticalCenter: parent.verticalCenter
                width: home.width - biostitle.width - 30 * 2
            }
        }
        Column {
            anchors.left: parent.left
            anchors.leftMargin: 20
            spacing: 10
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("BIOS Vendor: ")//BIOS产商：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 150
                }
                Text {
                    id: biosvendorText
                    text: ""//systemdispatcher.getHWSingleInfo("BioVendor")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("BIOS Version: ")//BIOS版本：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 150
                }
                Text {
                    id: biosversionText
                    text: ""//systemdispatcher.getHWSingleInfo("BioVersion")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Release Date: ")//发布日期：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 150
                }
                Text {
                    id: biosreleaseText
                    text: ""//systemdispatcher.getHWSingleInfo("BioRelease")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
        }
    }
    //logo
    Image {
        id: basiclogo
        source: ""
        opacity: 0.5
        anchors {
            top: parent.top
            topMargin: 80
            right: parent.right
            rightMargin: 30
        }
    }
    //logo
    Image {
        id: bioslogo
        source: ""
        opacity: 0.5
        anchors {
            top: parent.top
            topMargin: 220
            right: parent.right
            rightMargin: 30
        }
    }
}
