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
    Component.onCompleted: {
        //QMap(("DiskCapacity", QVariant(QString, "320.1 GB") ) ( "DiskFw" ,  QVariant(QString, "0004LVM1") )
        // ( "DiskName" ,  QVariant(QString, "/dev/sda") ) ( "DiskNum" ,  QVariant(int, 1) )
        //( "DiskProduct" ,  QVariant(QString, "ST320LT007-9ZV142") )
        //( "DiskSerial" ,  QVariant(QString, "W0Q62SF7") ) ( "DiskVendor" ,  QVariant(QString, "Seagate") ) )
        systemdispatcher.get_harddisk_info_qt();//获取详细信息
        firstlogo.source = "../../img/logo/Manufacturer/" + systemdispatcher.getSingleInfo("DiskVendor", "harddisk").toUpperCase() + ".jpg";
        modelText.text = systemdispatcher.getSingleInfo("DiskProduct", "harddisk");
        vendorText.text = systemdispatcher.getSingleInfo("DiskVendor", "harddisk");
        capacityText.text = systemdispatcher.getSingleInfo("DiskCapacity", "harddisk");
        deviceText.text = systemdispatcher.getSingleInfo("DiskName", "harddisk");
        fwText.text = systemdispatcher.getSingleInfo("DiskFw", "harddisk");
        serialText.text = systemdispatcher.getSingleInfo("DiskSerial", "harddisk");
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
                text: qsTr("HardDisk information")//硬盘s信息
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
                    text: qsTr("HardDisk Model:")//硬盘型号：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 140
                }
                Text {
                    id: modelText
                    text: ""//systemdispatcher.getSingleInfo("DiskProduct")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("Motherboard Vendor:")//硬盘厂商：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 140
                }
                Text {
                    id: vendorText
                    text: ""//systemdispatcher.getSingleInfo("DiskVendor")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("HardDisk Capacity:")//硬盘容量：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 140
                }
                Text {
                    id: capacityText
                    text: ""//systemdispatcher.getSingleInfo("DiskCapacity")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("Device Name:")//设备名称：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 140
                }
                Text {
                    id: deviceText
                    text: ""//systemdispatcher.getSingleInfo("DiskName")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("Fireware:")//固件版本：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 140
                }
                Text {
                    id: fwText
                    text: ""//systemdispatcher.getSingleInfo("DiskFw")
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
                    width: 140
                }
                Text {
                    id: serialText
                    text: ""//systemdispatcher.getSingleInfo("BoaSerial")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
        }

    }
    //logo
    Image {
        id: firstlogo
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
        id: secondogo
        source: ""
        anchors {
            top: parent.top
            topMargin: 200
            right: parent.right
            rightMargin: 30
        }
    }
}
