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
import QtDesktop 0.1
//import RegisterMyType 0.1
//import SessionType 0.1
//import SystemType 0.1
//import Ubuntu.Components.ListItems 0.1 as ListItem
import "common" as Common
Item {
    height: threadListView.height + pictureImage.height
    width: parent.width
//    property Dispatcher dis: mydispather
    Component.onCompleted: {
        streamModel.clear();
        if (item_flags == "clear_rubbish") {
            streamModel.append({"title1": "Pizza1", "title2": "kobe1"});
            streamModel.append({"title1": "Pizza2", "title2": "kobe2"});
            streamModel.append({"title1": "Pizza3", "title2": "kobe3"});
        }
        else if (item_flags == "clear_history") {
            streamModel.append({"title1": "KKK", "title2": "kobe1"});
            streamModel.append({"title1": "BBB", "title2": "kobe2"});
            streamModel.append({"title1": "CCC", "title2": "kobe3"});
            streamModel.append({"title1": "KKK", "title2": "kobe1"});
            streamModel.append({"title1": "BBB", "title2": "kobe2"});
            streamModel.append({"title1": "CCC", "title2": "kobe3"});
            streamModel.append({"title1": "KKK", "title2": "kobe1"});
            streamModel.append({"title1": "BBB", "title2": "kobe2"});
            streamModel.append({"title1": "CCC", "title2": "kobe3"});
            streamModel.append({"title1": "KKK", "title2": "kobe1"});
            streamModel.append({"title1": "BBB", "title2": "kobe2"});
            streamModel.append({"title1": "CCC", "title2": "kobe3"});
            streamModel.append({"title1": "KKK", "title2": "kobe1"});
            streamModel.append({"title1": "BBB", "title2": "kobe2"});
            streamModel.append({"title1": "CCC", "title2": "kobe3"});
        }
        else if (item_flags == "clear_cookies") {
            streamModel.append({"title1": "AAA", "title2": "kobe1"});
            streamModel.append({"title1": "BBB", "title2": "kobe2"});
        }
        else if (item_flags == "clear_package") {
            streamModel.append({"title1": "PS", "title2": "kobe1"});
            streamModel.append({"title1": "Shuang", "title2": "kobe2"});
            streamModel.append({"title1": "Er", "title2": "kobe3"});
        }
        else if (item_flags == "net_scan") {
            streamModel.append({"title1": "net_scan", "title2": "kobe1"});
            streamModel.append({"title1": "net_scan", "title2": "kobe2"});
            streamModel.append({"title1": "net_scan", "title2": "kobe3"});
        }
        else if (item_flags == "system_use") {
            streamModel.append({"title1": "system_use", "title2": "kobe1"});
            streamModel.append({"title1": "system_use", "title2": "kobe2"});
            streamModel.append({"title1": "system_use", "title2": "kobe3"});
        }
        else if (item_flags == "software_use") {
            streamModel.append({"title1": "software_use", "title2": "kobe1"});
            streamModel.append({"title1": "software_use", "title2": "kobe2"});
            streamModel.append({"title1": "software_use", "title2": "kobe3"});
        }
        else if (item_flags == "usb_use") {
            streamModel.append({"title1": "usb_use", "title2": "kobe1"});
            streamModel.append({"title1": "usb_use", "title2": "kobe2"});
            streamModel.append({"title1": "usb_use", "title2": "kobe3"});
        }
        else if (item_flags == "office_use") {
            streamModel.append({"title1": "office_use", "title2": "kobe1"});
            streamModel.append({"title1": "office_use", "title2": "kobe2"});
            streamModel.append({"title1": "office_use", "title2": "kobe3"});
        }
        else if (item_flags == "cookie_use") {
            streamModel.append({"title1": "cookie_use", "title2": "kobe1"});
            streamModel.append({"title1": "cookie_use", "title2": "kobe2"});
            streamModel.append({"title1": "cookie_use", "title2": "kobe3"});
        }
        else {
            streamModel.append({"title1": "111", "title2": "kobe1"});
            streamModel.append({"title1": "222", "title2": "kobe2"});
            streamModel.append({"title1": "333", "title2": "kobe3"});
        }

//        streamModel.sync();
    }

    ListModel {
        id: streamModel
        ListElement {
            title1: "kobe111"
            title2: "lixiang"
        }
    }

    Column {
        id: threadListView
        width: parent.width
        Repeater {
            width: parent.width
            model: streamModel
            delegate: Item {
                id: threadItem
                width: parent.width
                anchors {
                    right: parent.right
                    leftMargin: 10
                    rightMargin: 10
                    bottomMargin: 2
                }
                height: status_update_content.height

//                Common.CheckBox {
//                    id: avatarImage
//                    checked: check!="" ? true : false
//                    anchors {
//                        left: parent.left
//                        top: parent.top
//                        leftMargin: 20
//                        topMargin: 10
//                    }
//                    onCheckedChanged: {
//                        //kobe: wait for adding function
//                        if (check == "clear_rubbish")
//                            console.log("clear_rubbish check ");
//                        else if (check == "clear_traces")
//                            console.log("clear_traces check");
//                        else if (check == "clear_package")
//                            console.log("clear_package check");
//                    }
//                }

                Item {
                    id: status_update_content
//                    anchors {
//                        left: avatarImage.right
//                        right: parent.right
//                        top: parent.top
//                        topMargin: 10
//                        leftMargin: 20
//                        bottomMargin: 10
//                        rightMargin: 10
//                    }

                    anchors {
                        left: parent.left
                        top: parent.top
                        leftMargin: 20
                        topMargin: 10
                    }

//                    width: parent.width - avatarImage.width
                    width: parent.width
                    height: childrenRect.height + 10 //10 is spacing

                    Column {
                        width: parent.width
                        spacing: 0
                        anchors {
                            left: parent.left;
                            right: parent.right
                            bottomMargin: 2
                        }
                        Label {
                            text: title1
                            font.bold: true
                            width: parent.width
                        }
                        Label {
                            id: messageText
                            text: title2
//                            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                            onLinkActivated: {
                                //kobe: wait for adding function
                            }
                        }
                    }
                    Row {
                        anchors.right: parent.right
                        anchors.rightMargin: 10
                        anchors.top: parent.top
                        spacing: 10

                        Text {
                            id: time
                            text: "kobe test"
                            font.family: "Ubuntu"
                            font.pointSize: 8
                            color: "gray"
                        }
                    }
                }
            }
        }
    }
}










//import QtQuick 2.0
////import Ubuntu.Components 0.1
//import RegisterMyType 0.1
////import QtQuick.LocalStorage 2.0



//Item {
//    height: threadListView.height + pictureImage.height
//    width: parent.width
//    property Dispatcher dis: mydispather
//    property string last_flag: item_flags
//    anchors {
//        bottomMargin: units.gu(2)
//    }


////    Component.onCompleted: {
////        streamModel.clear();
////        if (item_flags == "clear_rubbish") {

//////        console.log("11111111111");
//////        console.log(mydispather.get_str());
//////        console.log("222222222222");
//////        if (mydispather.get_str() == "clear_rubbish") {
////            streamModel.append({"title1": "Pizza1", "title2": "kobe1"});
////            streamModel.append({"title1": "Pizza2", "title2": "kobe2"});
////            streamModel.append({"title1": "Pizza3", "title2": "kobe3"});
////        }
////        else if (item_flags == "clear_traces") {
////            streamModel.append({"title1": "KKK", "title2": "kobe1"});
////            streamModel.append({"title1": "BBB", "title2": "kobe2"});
////            streamModel.append({"title1": "CCC", "title2": "kobe3"});
////        }
////        else if (item_flags == "clear_registry") {
////            streamModel.append({"title1": "PS", "title2": "kobe1"});
////            streamModel.append({"title1": "Shuang", "title2": "kobe2"});
////            streamModel.append({"title1": "Er", "title2": "kobe3"});
////        }
////        else if (item_flags == "net_scan") {
////            streamModel.append({"title1": "net_scan", "title2": "kobe1"});
////            streamModel.append({"title1": "net_scan", "title2": "kobe2"});
////            streamModel.append({"title1": "net_scan", "title2": "kobe3"});
////        }
////        else if (item_flags == "system_use") {
////            streamModel.append({"title1": "system_use", "title2": "kobe1"});
////            streamModel.append({"title1": "system_use", "title2": "kobe2"});
////            streamModel.append({"title1": "system_use", "title2": "kobe3"});
////        }
////        else if (item_flags == "software_use") {
////            streamModel.append({"title1": "software_use", "title2": "kobe1"});
////            streamModel.append({"title1": "software_use", "title2": "kobe2"});
////            streamModel.append({"title1": "software_use", "title2": "kobe3"});
////        }
////        else if (item_flags == "usb_use") {
////            streamModel.append({"title1": "usb_use", "title2": "kobe1"});
////            streamModel.append({"title1": "usb_use", "title2": "kobe2"});
////            streamModel.append({"title1": "usb_use", "title2": "kobe3"});
////        }
////        else if (item_flags == "office_use") {
////            streamModel.append({"title1": "office_use", "title2": "kobe1"});
////            streamModel.append({"title1": "office_use", "title2": "kobe2"});
////            streamModel.append({"title1": "office_use", "title2": "kobe3"});
////        }
////        else if (item_flags == "cookie_use") {
////            streamModel.append({"title1": "cookie_use", "title2": "kobe1"});
////            streamModel.append({"title1": "cookie_use", "title2": "kobe2"});
////            streamModel.append({"title1": "cookie_use", "title2": "kobe3"});
////        }
////        else {
////            streamModel.append({"title1": "111", "title2": "kobe1"});
////            streamModel.append({"title1": "222", "title2": "kobe2"});
////            streamModel.append({"title1": "333", "title2": "kobe3"});
////        }

//////        streamModel.sync();
////    }

////    ListModel {
////        id: streamModel
////        ListElement {
////            title1: "kobe"
////            title2: "lixiang"
////        }
////    }



//    StorageModel {
//            id: storageModel
//        }

//    Column {
//        id: threadListView
//        width: parent.width
//        Repeater {
//            width: parent.width
//            model: storageModel

//            delegate: Item {
//                id: threadItem
//                width: parent.width - units.gu(8)
//                anchors {
//                    right: parent.right
//                    leftMargin: units.gu(8)
//                    rightMargin: units.gu(2)
//                    bottomMargin: units.gu(2)
//                }
//                height: status_update_content.height

//                CheckBox {
//                    id: avatarImage
//                    checked: true
//                    anchors {
//                        left: parent.left
//                        top: parent.top
//                        leftMargin: units.gu(1)
//                        topMargin: units.gu(1)
//                    }
//                    onCheckedChanged: {
//                        //kobe: wait for adding function
//                        if (item_flags == "clear_rubbish") {
//                            storageModel.addItem("111", "222");
//                        }
//                        else if (item_flags == "clear_traces") {
//                            storageModel.addItem("333", "444");
//                        }
//                        else if (item_flags == "clear_registry") {
//                            storageModel.addItem("555", "666");
//                        }
//                        else if (item_flags == "net_scan") {
//                            storageModel.addItem("777", "888");
//                        }
//                        else if (item_flags == "system_use") {
//                            storageModel.addItem("999", "000");
//                        }
//                        else if (item_flags == "software_use") {
//                            storageModel.addItem("aaa", "bbb");
//                        }
//                        else if (item_flags == "usb_use") {
//                            storageModel.addItem("ccc", "ddd");
//                        }
//                        else if (item_flags == "office_use") {
//                            storageModel.addItem("eee", "fff");
//                        }
//                        else if (item_flags == "cookie_use") {
//                            storageModel.addItem("ggg", "hhh");
//                        }
//                        else {
//                            storageModel.addItem("iii", "jjj");
//                        }
//                    }
//                }

//                Item {
//                    id: status_update_content
//                    anchors {
//                        left: avatarImage.right
//                        right: parent.right
//                        top: parent.top
//                        topMargin: units.gu(1)
//                        leftMargin: units.gu(1)
//                        bottomMargin: units.gu(1)
//                        rightMargin: units.gu(1)
//                    }
//                    width: parent.width - avatarImage.width
//                    height: childrenRect.height + units.gu(1)

//                    Column {
//                        width: parent.width
//                        spacing: 0
//                        anchors {
//                            left: parent.left;
//                            right: parent.right
//                            bottomMargin: units.gu(2)
//                        }
//                        Label {
//                            text: title1
//                            fontSize: "small"
//                            font.bold: true
//                            width: parent.width
//                        }
//                        Label {
//                            id: messageText
//                            text: title2
//                            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
//                            width: parent.width - units.gu(3)
//                            fontSize: "small"
//                            onLinkActivated: {
//                                //kobe: wait for adding function
//                            }
//                        }
//                    }
//                    Row {
//                        anchors.right: parent.right
//                        anchors.rightMargin: units.gu(1)
//                        anchors.top: parent.top
//                        spacing: units.gu(1)

//                        Text {
//                            id: time
//                            text: "kobe test"
//                            font.family: "Ubuntu"
//                            font.pointSize: 8
//                            color: "gray"
//                        }
//                    }

//                    //kobe:缓冲图，转动
////                    ActivityIndicator {
////                        id: sendSpinner
////                        visible: true
////                        running: visible
////                    }
//                }
//            }
//        }
//    }
//}
