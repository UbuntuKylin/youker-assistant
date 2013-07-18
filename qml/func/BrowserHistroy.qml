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
import QtDesktop 0.1
//import RegisterMyType 0.1
import SessionType 0.1
//import SystemType 0.1
import "common" as Common

Item {
    id:root
//    property Dispatcher dis: mydispather
    width: parent.width
    height: 435//420//340
//    color:"#c3c3c3"
    //垃圾清理自定义标题栏
    property string btn_text: "开始扫描"
    property string title: "清理浏览器历史记录"
    property string description: "清理浏览器历史记录可以保障系统安全"
    property string btn_flag: "history_scan"
    property ListModel listmodel: mainModel
    property ListModel submodel: subModel

    property int sub_num: 0

    signal history_signal(string history_msg);
    onHistory_signal: {
        if (history_msg == "HistoryWork") {
            console.log("&&&&&&&&&&&&&&&&&&&&&&&");
            console.log(history_msg);


            //get data of cookies
//            var cookies_data = systemdispatcher.scan_cookies_records_qt();
//            console.log("****************************8");
//            root.sub_num = cookies_data.length;
//            subModel.clear();
//            for (var i=0; i< cookies_data.length; i++) {
//                console.log(cookies_data[i]);
//                subModel.append({"itemTitle": cookies_data[i], "number": i});
//            }

//            console.log("****************************9");
            mainModel.clear();
            mainModel.append({"itemTitle": "清理浏览器历史记录",
                             "picture": "../img/icons/user.png",
                             "detailstr": "清理浏览器历史记录，让系统更安全",
                             "flags": "clear_history",
                            "attributes":
                                 [{"subItemTitle": "111"},
                                 {"subItemTitle": "222"},
                                 {"subItemTitle": "333"},
                                 {"subItemTitle": "444"}]
                             })
            console.log("%%%%%%%%%%%%%%%%%%%%%%%55");
        }

    }

    ListModel {
        id: mainModel
        ListElement {
            itemTitle: "清理浏览器历史记录"
            picture: "../img/icons/user.png"
            detailstr: "清理浏览器历史记录，让系统更安全"
            flags: "clear_history"
            attributes: [
                ListElement { subItemTitle: "" }
            ]
        }
    }

    ListModel {
        id: subModel
        ListElement {itemTitle: ""; desc: ""; number: ""}
    }


    ItemListModel {
        id: pluginlist
        height: parent.height
        btn_text: root.btn_text
        title: root.title
        description: root.description
        btn_flag: root.btn_flag
        listmodel: root.listmodel
        submodel: root.submodel
        num: root.sub_num
    }
}

//Rectangle {
//    id:root
////    property Dispatcher dis: mydispather
//    property SessionDispatcher dis: sessiondispatcher
//    width: parent.width
//    height: 420//340
////    color:"#c3c3c3"
//    //垃圾清理自定义标题栏

//    Component.onCompleted: {
//    }


//    Common.TitleBar {
//        id: titleBar; width: parent.width; height: 45; opacity: 0.9
//        btn_text: "开始扫描"
//        title: "清理浏览器历史记录"
//        description:  "清理浏览器历史记录可以保障系统安全"
//        btn_flag: "history_scan"
//    }

//    ScrollArea {
//        frame:false
//        anchors.fill: parent
//        anchors.top: titleBar.bottom
//        anchors.topMargin: 50
//        Item {
//            width:parent.width
//            height:450//content.height + 50//1000//this height must be higher than root.height, then the slidebar can display
////            Component {
////                id: statusDelegate
////                RubbishStatus {
////                    id: content
////                }
////            }
//            ListModel {
//                id: streamModel
//                ListElement {
//                    title: "清理浏览器历史记录"
//                    picture: "../img/icons/user.png"
//                    detailstr: "清理浏览器历史记录，让系统更安全"
//                    flags: "clear_history"
//                }
//            }

//            //垃圾清理显示内容
//            ListView {
//                id: listView
//                height: parent.height - titleBar.height
//                width: parent.width
//                model: streamModel
//                delegate: RubbishDelegate {}


////                model: myModel
////                 delegate: Rectangle {
////                     height: 25
////                     width: 100
////                     Text { text: modelData }
////                 }


//                cacheBuffer: 1000


//                opacity: 1
//                spacing: 10
//                snapMode: ListView.NoSnap
////                cacheBuffer: parent.height
//                boundsBehavior: Flickable.DragOverBounds
//                currentIndex: 0
//                preferredHighlightBegin: 0
//                preferredHighlightEnd: preferredHighlightBegin
//                highlightRangeMode: ListView.StrictlyEnforceRange
//            }
//        }//Item
//    }//ScrollArea
//}




