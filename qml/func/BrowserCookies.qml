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
//import SessionType 0.1
import SystemType 0.1
import "common" as Common

Item {
    id:root
//    property Dispatcher dis: mydispather
    width: parent.width
    height: 435//420//340
//    color:"#c3c3c3"
    //垃圾清理自定义标题栏
    property string btn_text: "开始扫描"
    property string title: "清理浏览器Cookies"
    property string description: "清理浏览器Cookies可以保障系统安全"
    property string btn_flag: "cookies_scan"
    property SystemDispatcher dis: systemdispatcher
    property ListModel listmodel: mainModel
    property ListModel submodel: subModel
    property int sub_num: 0



    signal cookies_signal(string cookies_msg);
    onCookies_signal: {
        if (cookies_msg == "CookiesWork") {
//            console.log("&&&&&&&&&&&&&&&&&&&&&&&");
//            console.log(cookies_msg);

            //get data of cookies
            var cookies_data = systemdispatcher.scan_cookies_records_qt();
//            console.log("****************************8");
            root.sub_num = cookies_data.length;
            systemdispatcher.clear_cookies_args();
            subModel.clear();
            var num = 0;
            for (var i=0; i< cookies_data.length; i++) {
                console.log(cookies_data[i]);//sina.com.cn<2_2>10
                var splitlist = cookies_data[i].split("<2_2>");
                if (splitlist[0] == "") {
                    num++;
                }
                else {
                    subModel.append({"itemTitle": splitlist[0], "desc": "","number": splitlist[1] + "个Cookie"});
                    systemdispatcher.set_apt_args(splitlist[0]);
                }

//                subModel.append({"itemTitle": cookies_data[i], "number": i});
            }
            root.sub_num -= num;
//            console.log("****************************9");
            mainModel.clear();
            mainModel.append({"itemTitle": "清理浏览器Cookies",
                             "picture": "../img/icons/user.png",
                             "detailstr": "清理Cookies，让系统更安全",
                             "flags": "clear_cookies",
                            "attributes":
                                 [{"subItemTitle": "Cookies1"},
                                 {"subItemTitle": "Cookies2"},
                                 {"subItemTitle": "Cookies3"},
                                 {"subItemTitle": "Cookies4"}]
                             })



//            mainModel.clear();
//            for (var i=0; i< cookies_data.length; i++) {
//                mainModel.append({"attributes":[{"subItemTitle": cookies_data[i]}]});
//            }

//            mainModel.append({
//                            "attributes":
//                                 [{"subItemTitle": "Cookies1"},
//                                 {"subItemTitle": "Cookies2"},
//                                 {"subItemTitle": "Cookies3"},
//                                 {"subItemTitle": "Cookies4"}]
//                             })
//            console.log("%%%%%%%%%%%%%%%%%%%%%%%55");
        }
    }


    ListModel {
        id: mainModel
        ListElement {
            itemTitle: "清理浏览器Cookies"
            picture: "../img/icons/user.png"
            detailstr: "清理Cookies，让系统更安全"
            flags: "clear_cookies"
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
//    width: parent.width
//    height: 420//340
//    color:"#c3c3c3"
//    //垃圾清理自定义标题栏
//    Common.TitleBar {
//        id: titleBar; width: parent.width; height: 45; opacity: 0.9
//        btn_text: "开始扫描"
//        title: "清理浏览器Cookies"
//        description:  "清理浏览器Cookies可以保障系统安全"
//        btn_flag: "cookies_scan"
//    }

//    ScrollArea {
//        frame:false
//        anchors.fill: parent
//        anchors.top: titleBar.bottom
//        anchors.topMargin: 50
//        Item {
//            width:parent.width
//            height: 450
////            height:content.height + 50//1000//this height must be higher than root.height, then the slidebar can display
////            Component {
////                id: statusDelegate
////                RubbishStatus {
////                    id: content
////                }
////            }
//            ListModel {
//                id: streamModel
//                ListElement {
//                    title: "清理Cookies"
//                    picture: "../img/icons/user.png"
//                    detailstr: "清理Cookies，让系统更安全"
//                    flags: "clear_cookies"
//                }
//            }

//            //垃圾清理显示内容
//            ListView {
//                id: listView
//                height: parent.height - titleBar.height
//                width: parent.width
//                model: streamModel
//                delegate: RubbishDelegate {}
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
