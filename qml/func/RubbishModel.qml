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
    width: parent.width
    height: 435
//    color:"#c3c3c3"
    //垃圾清理自定义标题栏
    property string btn_text: "开始扫描"
    property string title: "清理电脑中的垃圾"
    property string description: "清理垃圾可以提高系统速度"
    property string btn_flag: "cruft_scan"
    property ListModel listmodel: mainModel
    property ListModel submodel: subModel

    property int sub_num: 0

    signal cruft_signal(string cruft_msg);
    onCruft_signal: {
        if (cruft_msg == "CruftWork") {
            //get data of cookies
            console.log("xiang1111");
            systemdispatcher.scan_cache_cruft_qt();
            var apt_data = systemdispatcher.get_apt_data();
//            var center_data = systemdispatcher.get_center_data();

            sub_num = apt_data.length;// + center_data.legth;

            subModel.clear();
            for (var i=0; i< apt_data.length; i++) {
                console.log(apt_data[i]);//sina.com.cn<2_2>10
                var splitlist = apt_data[i].split("<2_2>");
                subModel.append({"itemTitle": splitlist[0], "number": splitlist[1] + "字节"});
//                subModel.append({"itemTitle": cookies_data[i], "number": i});
            }
            mainModel.clear();
            mainModel.append({"itemTitle": "清理apt",
                             "picture": "../img/icons/user.png",
                             "detailstr": "清理系统apt，让系统运行跟流畅",
                             "flags": "clear_rubbish",
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
            itemTitle: "清理apt"
            picture: "../img/icons/user.png"
            detailstr: "清理系统垃圾，让系统运行跟流畅"
            flags: "clear_rubbish"
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
//        title: "清理电脑中的垃圾"
//        description:  "清理垃圾可以提高系统速度"
//        btn_flag: "rubbish"
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
//                    title: "清理垃圾"
//                    picture: "../img/icons/user.png"
//                    detailstr: "清理系统垃圾，让系统运行跟流畅"
//                    flags: "clear_rubbish"
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









//Item {
//    id: rubbishitem
//    property Dispatcher dis: mydispather
//    Component {
//        id: statusDelegate
//        RubbishStatus {
//            id: content
//            width: listView.width//  - units.gu(1)
//            height: childrenRect.height
//        }
//    }
//    ListModel {
//        id: streamModel
//        ListElement {
//            title: "1、清理垃圾"
//            picture: "../img/icons/user.png"
//            detailstr: "清理系统垃圾，让系统运行跟流畅"
//            flags: "clear_rubbish"
//        }
//        ListElement {
//            title: "2、清理痕迹"
//            picture: "../img/icons/at.png"
//            detailstr: "清理使用计算机时留下的各种痕迹，保护个人隐私"
//            flags: "clear_traces"
//        }
//        ListElement {
//            title: "3、清理注册表"
//            picture: "../img/icons/pen.png"
//            detailstr: "清理电脑日常使用中产生的无用注册表项，提高系统性能"
//            flags: "clear_registry"
//        }
//    }

//    Column {
//        anchors.fill: parent
//        //垃圾清理自定义标题栏
//        Common.TitleBar {
//            id: titlebar
//            anchors.top: parent.top
//            anchors.topMargin: 80
//            width: parent.width
//            height: 45
//            opacity: 0.9
//            btn_text: "开始扫描"
//            title: "清理电脑中的垃圾"
//            description:  "清理垃圾可以提高系统速度"
//            btn_flag: "rubbish"
//        }
//        //垃圾清理显示内容
//        ListView {
//            id: listView
////            objectName: "listView"
//            height: rubbishitem.height - titlebar.height// - units.gu(2)
//            width: rubbishitem.width
////            focus: true
//            anchors.fill: parent
//            anchors.top: titlebar.bottom
//            anchors.topMargin: 133
////            highlight: Rectangle { color: "white" }
////            anchors {
////                top: updatesBanner.bottom
////                topMargin: 100//units.gu(1)
////            }
//            opacity: 1
//            spacing: units.gu(1)
//            model: streamModel
//            snapMode: ListView.NoSnap
//            cacheBuffer: parent.height
//            boundsBehavior: Flickable.DragOverBounds
//            currentIndex: 0
//            delegate: statusDelegate
//            preferredHighlightBegin: 0
//            preferredHighlightEnd: preferredHighlightBegin
//            highlightRangeMode: ListView.StrictlyEnforceRange
//        }
//        Scrollbar {
//            flickableItem: listView
//            align: Qt.AlignTrailing
//        }

//        Item {
//            id: updatesBanner
//            anchors {
//                top: parent.top
//                left: parent.left
//                right: parent.right
//            }
//            visible: true
//            height: visible ? units.gu(3) : 0
//            Text {
//                id: updatesText
//                anchors {
//                    centerIn: parent
//                    bottom: parent.bottom
//                }
//                text: ""
//                font.family: "Ubuntu"
//                font.bold: true
//                font.pointSize: 12
//                color: "gray"
//            }
//            MouseArea {
//                anchors.fill: parent
//                onClicked: {

//                }
//            }
//        }//Item
//    }//Column
//}//Item







//Rectangle {
//    color: "#f8f8f8"
//    Item {
//        id: clear_line
//        anchors {fill: parent; top: parent.top; topMargin: 80}
//        TitleBar {
//            id: titleBar
//            width: parent.width
//            height: 45
//            opacity: 0.9
//            btn_text: "开始扫描"
//            title: "清理电脑中的垃圾"
//            description:  "清理垃圾可以提高系统速度"
//        }
//    }


////    Item {
////        id: clear_line
////        anchors {fill: parent; top: parent.top; topMargin: 80; left: parent.left; leftMargin: 30}
////        Column {
////            Text {
////                text: "清理电脑中的插件"
////                font.pointSize: 11
////                color: "black"
////            }
////            Text {
////                text:  "清理插件可以给系统和浏览器“减负”，减少干扰，提供系统和浏览器速度"
////                font.pointSize: 9
////                color: "gray"
////            }
////        }
////        Button {
////            id: pluginBtn
////            width: 90
////            color: "gray"
////            anchors {
////                left: parent.left
////                leftMargin: 700
////            }
////            text: "开始扫描"
////            onClicked: {
////                //kobe: wait for adding function
//////                mydispather.send_btn_msg("clearfast")
//////                pageStack.pop()
//////                pageStack.push(clearprogress)
////            }
////        }
////    }


//    Rectangle {
//        anchors {fill: parent; top: parent.top; topMargin: 130; left: parent.left}
//        Component {
//            id: statusDelegate
//            RubbishStatus {
//                id: content
//                width: listView.width  - units.gu(1)
//                height: childrenRect.height
//    //            title1: title
//    //            title2: detailstr
//    //            icon_source: picture
//    //            ListView.onAdd: SequentialAnimation {
//    //                ScriptAction { script: {unseen++; console.log(column_0[0][0] + " " + column_0[0][1] + " " + column_0[0][2]) }}
//    //            }
//    //            Connections {
//    //                target: updateTimestampsTimer
//    //                onTriggered: {
//    //                    recalculateTimeString();
//    //                }
//    //            }
//            }
//        }
//        ListModel {
//            id: streamModel
//            ListElement {
//                title: "1、清理垃圾"
//                picture: "../img/icons/user.png"
//                detailstr: "清理系统垃圾，让系统运行跟流畅"
//                flags: "clear_rubbish"
//            }
//            ListElement {
//                title: "2、清理痕迹"
//                picture: "../img/icons/at.png"
//                detailstr: "清理使用计算机时留下的各种痕迹，保护个人隐私"
//                flags: "clear_traces"
//            }
//            ListElement {
//                title: "3、清理注册表"
//                picture: "../img/icons/pen.png"
//                detailstr: "清理电脑日常使用中产生的无用注册表项，提高系统性能"
//                flags: "clear_registry"
//            }

//        }

//        ListView {
//            id: listView
//            objectName: "listView"
//            height: parent.height - toolbar.height - units.gu(2)
//            width: parent.width
//            anchors {
//                top: updatesBanner.bottom
//                topMargin: units.gu(1)
//            }
//            opacity: 1
//            spacing: units.gu(1)
//            model: streamModel
//            snapMode: ListView.NoSnap
//            cacheBuffer: parent.height
//            boundsBehavior: Flickable.DragOverBounds
//            currentIndex: 0
//            delegate: statusDelegate

//            preferredHighlightBegin: 0
//            preferredHighlightEnd: preferredHighlightBegin
//            highlightRangeMode: ListView.StrictlyEnforceRange
//        }

//        Item {
//            id: updatesBanner
//            anchors {
//                top: parent.top
//                left: parent.left
//                right: parent.right
//            }
////            visible: unseen > 0
//            visible: true
//            height: visible ? units.gu(3) : 0
//            Text {
//                id: updatesText
//                anchors {
//                    centerIn: parent
//                    bottom: parent.bottom
//                }
//                text: ""
//                font.family: "Ubuntu"
//                font.bold: true
//                font.pointSize: 12
//                color: "gray"
//            }
//            MouseArea {
//                anchors.fill: parent
//                onClicked: {

//                }
//            }
//        }

//        Scrollbar {
//            flickableItem: listView
//            align: Qt.AlignTrailing
//        }
//    }
//}
