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
//import SystemType 0.1
import "common" as Common
Item {
    id:root
//    property Dispatcher dis: mydispather
//    property SystemDispatcher dis: systemdispatcher
    width: parent.width
    height: 435//340
//    color:"#c3c3c3"
    //垃圾清理自定义标题栏
    property string btn_text: "开始扫描"
    property string title: "清理不需要到deb包"
    property string description: "清理软件安装后不再需要的deb包，提高系统性能"
    property string btn_flag: "package_scan"

//    PluginListModel {
//        id: mainModel
//    }

    property ListModel listmodel: mainModel
    property ListModel submodel: subModel

    property int sub_num: 0


    signal unneed_signal(string unneed_msg);
    onUnneed_signal: {
        if (unneed_msg == "UnneedWork") {
            //get data of unneed
            var unneed_data = systemdispatcher.scan_unneed_packages_qt();

            root.sub_num = unneed_data.length;
            systemdispatcher.clear_package_args();
            subModel.clear();
            var num = 0;
            for (var i=0; i< unneed_data.length; i++) {
//                console.log(unneed_data[i]);//linux-headers-3.8.0-19<2_2>Header files related to Linux kernel version 3.8.0<2_2>60094464
                var splitlist = unneed_data[i].split("<2_2>");
                if (splitlist[0] == "") {
                    num++;
                }
                else {
                    subModel.append({"itemTitle": splitlist[0], "desc": splitlist[1], "number": splitlist[2] + "字节"});
                    systemdispatcher.set_package_args(splitlist[0]);
                }
            }
            root.sub_num -= num;
            mainModel.clear();
            console.log("unneed........................");
            console.log(systemdispatcher.get_package_args());
            mainModel.append({"itemTitle": "清理不再需要的安装包",
                             "picture": "../img/icons/user.png",
                             "detailstr": "不再需要的安装包,让系统更瘦",
                             "flags": "clear_cookies",
                            "attributes":
                                 [{"subItemTitle": "Cookies1"},
                                 {"subItemTitle": "Cookies2"},
                                 {"subItemTitle": "Cookies3"},
                                 {"subItemTitle": "Cookies4"}]
                             })
        }
    }



    ListModel {
        id: mainModel
        ListElement {
            itemTitle: "清理不再需要的安装包"
            picture: "../img/icons/user.png"
            detailstr: "不再需要的安装包,让系统更瘦"
            flags: "clear_package"
            attributes: [
                ListElement { subItemTitle: "" }
//                ListElement { subItemTitle: "kobe 2/1" }
            ]
        }
//        ListElement {
//            itemTitle: "Item title 2"
//            picture: "../img/icons/user.png"
//            detailstr: "清理deb，让系统更瘦2"
//            flags: "clear_package"
//            attributes: [
//                ListElement { subItemTitle: "kobe 1/3" },
//                ListElement { subItemTitle: "kobe 2/3" },
//                ListElement { subItemTitle: "kobe 3/3" }
//            ]
//        }
//        ListElement {
//            itemTitle: "Item title 3"
//            picture: "../img/icons/user.png"
//            detailstr: "清理deb，让系统更瘦3"
//            flags: "clear_package"
//            attributes: [
//                ListElement { subItemTitle: "kobe 1/4" },
//                ListElement { subItemTitle: "kobe 2/4" },
//                ListElement { subItemTitle: "kobe 3/4" },
//                ListElement { subItemTitle: "kobe 4/4" }
//            ]
//        }
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



//import QtQuick 1.1
//import QtDesktop 0.1
////import RegisterMyType 0.1
////import SessionType 0.1
////import SystemType 0.1
//import "common" as Common
//Item {
//    id:root
////    property Dispatcher dis: mydispather
//    width: parent.width
//    height: 420//340
////    color:"#c3c3c3"
//    //垃圾清理自定义标题栏
//    Common.TitleBar {
//        id: titleBar; width: parent.width; height: 45; opacity: 0.9
//        btn_text: "开始扫描"
//        title: "清理插件"
//        description:  "清理插件可以节省磁盘容量"
//        btn_flag: "plugins"
//    }

//    ScrollArea {
//        frame:false
//        anchors.fill: parent
//        anchors.top: titleBar.bottom
//        anchors.topMargin: 50
//        Item {
//            width:parent.width
//            height:content.height + 50//1000//this height must be higher than root.height, then the slidebar can display
//            Component {
//                id: statusDelegate
//                RubbishStatus {
//                    id: content
//                }
//            }
//            ListModel {
//                id: streamModel
//                ListElement {
//                    title: "清理插件"
//                    picture: "../img/icons/user.png"
//                    detailstr: "清理插件包，让系统更瘦"
//                    flags: "clear_package"
//                }
//            }

//            //垃圾清理显示内容
//            ListView {
//                id: listView
//                height: parent.height - titlebar.height
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
