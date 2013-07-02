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

import RegisterMyType 0.1

Rectangle {
    width: parent.width
    height: 460
    property Dispatcher dis: mydispather

    Item {
        Column {
            anchors.fill: parent
            Row {
                Image {
                    id: refreshArrow
                    source: "../img/icons/bug.png"
                    Behavior on rotation { NumberAnimation { duration: 200 } }
                }
                Text {
                    id: text1
                    x: 30
                    y: 11
                    width: 69
                    height: 20
                    text: qsTr("查杀木马:")
                    font.bold: true
                    font.pointSize: 13
                    font.pixelSize: 12

                    Column {
                        Text {
                            x: 65
                            height: 20
                            //text: qsTr("CPU: Intel(R) Core(TM) i5-3210M CPU @ 2.50GHz")
                            text: qsTr("CPU: "+ mydispather.get_value("cpu"))
                        }
                        Text {
                            x: 65
                            height: 20
                            text: qsTr("内存: " + mydispather.get_value("ram"))
//                            text: qsTr("内存: 1.8 GB")
                        }
                    }
                }
            }
        }
    }
}


//import QtQuick 2.0
//import Ubuntu.Components 0.1
//import Ubuntu.Components.ListItems 0.1 as ListItem
//import RegisterMyType 0.1

//Rectangle {
//    width: parent.width
//    height: 460
//    property Dispatcher dis: mydispather

//    Column {
//        width: parent.width
//        ListItem.ValueSelector {
//            text: "Standard"
//            values: ["Value 1", "Value 2", "Value 3", "Value 4"]
//        }
//        ListItem.ValueSelector {
//            text: "Disabled"
//            values: ["Value 1", "Value 2", "Value 3", "Value 4"]
//            enabled: false
//        }
//        ListItem.ValueSelector {
//            text: "Expanded"
//            values: ["Value 1", "Value 2", "Value 3", "Value 4"]
//            expanded: true
//        }
//        ListItem.ValueSelector {
//            text: "Icon"
////            icon: Qt.resolvedUrl("icon.png")
//            values: ["Value 1", "Value 2", "Value 3", "Value 4"]
//            selectedIndex: 2
//        }
//    }
//}
