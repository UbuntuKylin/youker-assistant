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
//import Ubuntu.Components 0.1
//import Ubuntu.Components.ListItems 0.1 as ListItem
//import RegisterMyType 0.1
//import SessionType 0.1
import SystemType 0.1

//Item {
//    property Dispatcher dis: mydispather
//    ListView {
//        id: list
//        width: units.gu(37)
//        height: units.gu(37)
//        model: 30
//        delegate: Rectangle {
//            width: ListView.view.width
//            height: units.gu(5)
//            Text {
//                anchors.fill: parent
//                text: "Item " + modelData
//            }
//        }
//    }
//    Scrollbar {
//        flickableItem: list
//        align: Qt.AlignTrailing
//    }
//}


Rectangle {
    width: parent.width
    height: 460
//    property Dispatcher dis: mydispather
    property SystemDispatcher dis: systemdispatcher

    Item {
        Column {
            anchors.fill: parent
            Row {
                Image {
                    id: refreshArrow
                    source: "../img/icons/system.png"
                    Behavior on rotation { NumberAnimation { duration: 200 } }
                }
                Text {
                    id: text1
                    x: 30
                    y: 11
                    width: 69
                    height: 20
                    text: qsTr("修复:")
                    font.bold: true
                    font.pointSize: 13
                    font.pixelSize: 12

                    Column {
                        Text {
                            x: 65
                            height: 20
                            //text: qsTr("CPU: Intel(R) Core(TM) i5-3210M CPU @ 2.50GHz")
                            text: qsTr("CPU: "+ systemdispatcher.get_value("cpu"))
                        }
                        Text {
                            x: 65
                            height: 20
                            text: qsTr("内存: " + systemdispatcher.get_value("ram"))
//                            text: qsTr("内存: 1.8 GB")
                        }
                    }
                }
            }
        }
    }
}
