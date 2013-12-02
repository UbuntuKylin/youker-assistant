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
import SystemType 0.1
import "../common" as Common
import "../bars" as Bars

Rectangle {
    id: home; width: parent.width; height: 475
    color: "transparent"
    Component.onCompleted: {
        systemdispatcher.get_board_info_qt();//获取详细信息
        basiclogo.source = "../../img/logo/Manufacturer/" + systemdispatcher.getSingleInfo("BoaVendor", "board") + ".jpg";
        bioslogo.source = "../../img/logo/Manufacturer/" + systemdispatcher.getSingleInfo("BioVendor", "board") + ".jpg";
        productText.text = systemdispatcher.getSingleInfo("BoaProduct", "board");
        vendorText.text = systemdispatcher.getSingleInfo("BoaVendor", "board");
        serialText.text = systemdispatcher.getSingleInfo("BoaSerial", "board");
        biosvendorText.text = systemdispatcher.getSingleInfo("BioVendor", "board");
        biosversionText.text = systemdispatcher.getSingleInfo("BioVersion", "board");
        biosreleaseText.text = systemdispatcher.getSingleInfo("BioRelease", "board");
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
            Text {
                id: basictitle
                text: qsTr("Basic information")//主板基本信息
                font.bold: true
                font.pixelSize: 14
                color: "#383838"
            }
            Rectangle {width: home.width - basictitle.width - 30 * 2
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
                Text {
                    text: qsTr("Motherboard Model:")//主板型号：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 120
                }
                Text {
                    id: productText
                    text: ""//systemdispatcher.getSingleInfo("BoaProduct")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("Motherboard Vendor:")//主板产商：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 120
                }
                Text {
                    id: vendorText
                    text: ""//systemdispatcher.getSingleInfo("BoaVendor")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("Serial:")//序列号：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 120
                }
                Text {
                    id: serialText
                    text: ""//systemdispatcher.getSingleInfo("BoaSerial")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
        }
        Row {
            Text {
                id: biostitle
                text: qsTr("Bios information")//BIOS信息
                font.bold: true
                font.pixelSize: 14
                color: "#383838"
            }
            Rectangle {
                id: splitbar
                width: home.width - biostitle.width - 30 * 2
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
                Text {
                    text: qsTr("Bios Vendor:")//BIOS产商：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 120
                }
                Text {
                    id: biosvendorText
                    text: ""//systemdispatcher.getSingleInfo("BioVendor")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("Bios Version:")//BIOS版本：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 120
                }
                Text {
                    id: biosversionText
                    text: ""//systemdispatcher.getSingleInfo("BioVersion")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("Release Date:")//发布日期：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 120
                }
                Text {
                    id: biosreleaseText
                    text: ""//systemdispatcher.getSingleInfo("BioRelease")
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
        anchors {
            top: parent.top
            topMargin: 50
            right: parent.right
            rightMargin: 30
        }
    }
    //logo
    Image {
        id: bioslogo
        source: ""
        anchors {
            top: parent.top
            topMargin: 200
            right: parent.right
            rightMargin: 30
        }
    }
}
