/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  Kobe Lee    kobe24_lixiang@126.com
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
import SessionType 0.1
import SystemType 0.1
import "common" as Common
Item {
    id:root
    width: parent.width
    height: 435//420//340
    property string btn_text: "开始扫描"
    property string apt_title: "包管理深度清理"
    property string apt_description: "深度清理包管理残留的deb包,节省磁盘空间"
    property string apt_btn_flag: "apt_scan"
    property ListModel listmodel: apt_mainModel
    property ListModel apt_submodel: apt_subModel
    property SystemDispatcher dis: systemdispatcher
    property int apt_sub_num: 0
    property string apt_work_result: ""
    property bool apt_check_flag: true
    property bool apt_null_flag: false
    property int apt_num: apt_sub_num


    signal apt_signal(string apt_msg);
    onApt_signal: {
        if (apt_msg == "AptWork") {
            //get data of cookies
            var apt_data = sessiondispatcher.scan_apt_cruft_qt();
            if (apt_data == "")
                root.apt_null_flag = true;
            else
                root.apt_null_flag = false;
            root.apt_sub_num = apt_data.length;
            systemdispatcher.clear_apt_args();
            apt_subModel.clear();
            var num = 0;
            for (var i=0; i< apt_data.length; i++) {
            //sina.com.cn<2_2>10
                var splitlist = apt_data[i].split("<2_2>");
                if (splitlist[0] == "") {
                    num++;
                }
                else {
                    apt_subModel.append({"itemTitle": splitlist[0], "desc": "","number": splitlist[1] + "字节"});
                    systemdispatcher.set_apt_args(splitlist[0]);
                }
            }
            root.apt_sub_num -= num;
            apt_num=apt_sub_num
            if(apt_num!=0)
                check_flag=true;
            apt_mainModel.clear();
            apt_mainModel.append({"itemTitle": "包管理清理",
                             "picture": "../img/toolWidget/apt-min.png",
                             "detailstr": "用户可以根据扫描结果选择性地清理包管理残留包,缓存路径为:/var/cache/apt/archives/",
                             "flags": "clear_apt",
                            "attributes":
                                 [{"subItemTitle": "Cookies1"},
                                 {"subItemTitle": "Cookies2"},
                                 {"subItemTitle": "Cookies3"},
                                 {"subItemTitle": "Cookies4"}]
                             })
        }
    }



    Connections
    {
        target: systemdispatcher
//         onFinishScanWork: {
//             if (apt_btn_flag == "apt_scan") {
//                 titleBar.apt_work_result = msg;
//                 titleBar.state = "AptWork";
//             }
//         }
        onFinishCleanWork: {
            if (apt_btn_flag == "apt_work") {
                if (msg == "apt") {
                    root.apt_work_result = msg;
                    root.state = "AptWorkFinish";
                }
            }
        }
    }

    ListModel {
        id: apt_mainModel
        ListElement {
            itemTitle: "包管理清理"
            picture: "../img/toolWidget/apt-min.png"
            detailstr: "用户可以根据扫描结果选择性地清理包管理残留包"
            flags: "clear_apt"
            attributes: [
                ListElement { subItemTitle: "" }
            ]
        }
    }

    ListModel {
        id: apt_subModel
        ListElement {itemTitle: ""; desc: ""; number: ""}
    }

    //背景
    Image {
        source: "../img/skin/bg-bottom-tab.png"
        anchors.fill: parent
    }
    //titlebar
    Row {
        id: apt_titlebar
        spacing: 20
        width: parent.width
//        height: 50
        anchors { top: parent.top; topMargin: 20; left: parent.left; leftMargin: 20 }
        Image {
            id: apt_refreshArrow
            source: "../img/toolWidget/apt.png"
            Behavior on rotation { NumberAnimation { duration: 200 } }
        }
        Column {
            anchors.verticalCenter: parent.verticalCenter
            spacing: 10
            Text {
                text: root.apt_title
                font.bold: true
                font.pixelSize: 14
                color: "#383838"
            }
            Text {
                text: root.apt_description
                font.pixelSize: 12
                color: "#7a7a7a"
            }
        }
    }
    Row{
        anchors { top: parent.top; topMargin: 30;right: parent.right ; rightMargin: 40 }
        spacing: 20

        //status picture
//        Image {
//            id: apt_statusImage
//            source: "../img/toolWidget/unfinish.png"
//            fillMode: "PreserveAspectFit"
//            smooth: true
//            anchors.verticalCenter: parent.verticalCenter
//        }
        Common.StatusImage {
            id: apt_statusImage
            iconName: "yellow.png"
            text: "未完成"
            anchors.verticalCenter: parent.verticalCenter
        }

        Common.Label {
            id: apt_label
            visible: false
            text: ""
            anchors.verticalCenter: parent.verticalCenter
        }


        Common.Button {
            id: apt_bitButton
            width: 120
            height: 39
            hoverimage: "green1.png"
            text: root.btn_text
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                if(apt_check_flag)
                {
                //apt cruft
                 if (apt_btn_flag == "apt_scan") {
                     apt_signal("AptWork");
                     if(root.apt_null_flag == true) {
                        root.state = "AptWorkEmpty";
                        sessiondispatcher.send_warningdialog_msg("友情提示：","扫描内容为空，不再执行清理！");
                     }
                     else if(root.apt_null_flag == false)
                        root.state = "AptWork";
                 }
                 else if (apt_btn_flag == "apt_work") {
                     systemdispatcher.clean_file_cruft_qt(systemdispatcher.get_apt_args(), "apt");
                 }
                }
                else
                     sessiondispatcher.send_warningdialog_msg("友情提示：","对不起，您没有选择需要清理的项，请确认！")
            }
        }
//        Common.Button {
//            id: apt_bitButton
//            width: 120
//            height: 39
////            hoverimage: "scan-start.png"
//            text:"开始扫描"
//            bold:true
//            textsize: 12
//            anchors.verticalCenter: parent.verticalCenter
//            onClicked: {
//                if(apt_check_flag)
//                {
//                //apt cruft
//                 if (apt_btn_flag == "apt_scan") {
//                     apt_signal("AptWork");
//                     if(root.apt_null_flag == true) {
//                        root.state = "AptWorkEmpty";
//                        sessiondispatcher.send_warningdialog_msg("友情提示：","扫描内容为空，不再执行清理！");
//                     }
//                     else if(root.apt_null_flag == false)
//                        root.state = "AptWork";
//                 }
//                 else if (apt_btn_flag == "apt_work") {
//                     systemdispatcher.clean_file_cruft_qt(systemdispatcher.get_apt_args(), "apt");
//                 }
//                }
//                else
//                     sessiondispatcher.send_warningdialog_msg("友情提示：","对不起，您没有选择需要清理的项，请确认！")
//            }
//        }
    }
    //分割条
    Rectangle {
        id: apt_splitbar
        anchors {
            top: apt_titlebar.bottom
            topMargin: 18
            left: parent.left
            leftMargin: 2
        }
        width: parent.width - 4
        height: 1
        color: "#b9c5cc"
    }

//    Component {
//        id: listViewDelegate
//        Item {
//            id: delegate
//            property alias expandedItemCount: subItemRepeater.count
//            x: 5; y: 2
//            width: root.width
//            height: headerItemRect.height + subItemsRect.height

//            //母项
//            //checkbox, picture and words
//            Row {
//                id: headerItemRect
//                x: 5; y: 2
//                width: root.width
//                height: root.itemHeight
//                spacing: 170
//                Row{
//                    spacing: 15
//                    Image {
//                        id: clearImage
//                        fillMode: "PreserveAspectFit"
//                        height: parent.height*0.9
//                        source: picture
//                        smooth: true
//                    }

//                    Column {
//                        id: status_update_content
//                        spacing: 5
//                        anchors.verticalCenter: parent.verticalCenter
//                        Text {
//                            id: mytext
//                            text: itemTitle
//                            font.pointSize: 11
//                            color: "black"
//                        }
//                        Text {
//                            text: detailstr
//                            font.pointSize: 9
//                            color: "gray"
//                        }
//                    }
//                }
//            }//母项Row
//            Image {
//                id: arrow
//                fillMode: "PreserveAspectFit"
//                height: 28
//                width: 26
//                x:740
//                y:15
////                    height: parent.height*0.3
//                source: root.arrow
//                //当鼠标点击后,箭头图片旋转90度
////                    rotation: expanded ? 90 : 0
//                rotation: expanded ? 0 : -180
//                smooth: true
//                MouseArea {
//                    id: mouseRegion
//                    anchors.fill: parent
//                    onPressed: {
//                        expanded = !expanded
//                    }
//                }
//            }

//            //子项
//            Item {
//                id: subItemsRect
//                property int itemHeight: root.itemHeight
//                y: headerItemRect.height
//                width: root.width
//                //当高度需要扩展时,根据expandedItemCount数目和itemHeight高度去扩展
//                height: expanded ? delegate.expandedItemCount * itemHeight : 0
//                clip: true
//                opacity: 1
//                Behavior on height {
//                    SequentialAnimation {
//                        NumberAnimation { duration: 100; easing.type: Easing.InOutQuad }
//                    }
//                }

//                Column {
//                    width: root.width
//                    Repeater {
//                        id: subItemRepeater
//                        model: apt_subModel
//                        width: subItemsRect.width
//                        ListItem {
//                            id: subListItem
//                            split_status: true
//                            width: root.width
//                            height: subItemsRect.itemHeight
////                            text: subItemTitle
//                            text: itemTitle
//                            descript: desc
//                            size_num: number
//                            checkbox_status: root.apt_check_flag
////                            bgImage: "../../img/icons/list_subitem.png"
//                            bgImage: ""
//                            fontName: root.subItemFontName
//                            fontSize: root.subItemFontSize
//                            fontColor: root.subItemFontColor
//                            textIndent: 20
//                            btn_flag: root.apt_btn_flag
//                            onClicked: {}
//                        }

//                    }//Repeater
//                }//Column
//            }
//        }
//    }//Component


    Common.ScrollArea {
        frame:false
        anchors.top: apt_titlebar.bottom
        anchors.topMargin: 30
        height: root.height -apt_titlebar.height - 50
        width: parent.width
        Item {
            width: parent.width
            height: (root.apt_num + 1) * 40 //450 + //this height must be higher than root.height, then the slidebar can display
            //垃圾清理显示内容
            ListView {
                id: apt_listView
                height: parent.height
                model: apt_mainModel
                delegate: Cleardelegate{
                    sub_num: apt_sub_num;sub_model: apt_subModel;btn_flag: apt_btn_flag
                    onSubpressed: {root.apt_num=hMark}
                    onCheckchanged: {root.apt_check_flag=checkchange}
                  }
                cacheBuffer: 1000
                opacity: 1
                spacing: 10
                snapMode: ListView.NoSnap
                boundsBehavior: Flickable.DragOverBounds
                currentIndex: 0
                preferredHighlightBegin: 0
                preferredHighlightEnd: preferredHighlightBegin
                highlightRangeMode: ListView.StrictlyEnforceRange
            }
        }//Item
    }//ScrollArea

    states: [
        State {
            name: "AptWork"
             PropertyChanges { target: apt_label; visible: true; text: "apt扫描完成"}
             PropertyChanges { target: apt_bitButton; /*hoverimage: "clear-start.png"*/ text:"开始清理"}
            PropertyChanges { target: root; apt_btn_flag: "apt_work" }
        },

        State {
            name: "AptWorkFinish"
            PropertyChanges { target: apt_label; visible: true; text: root.apt_work_result + "清理完毕！" }
            PropertyChanges { target: apt_bitButton; /*hoverimage: "scan-start.png"*/text:"开始扫描" }
            PropertyChanges { target: root; apt_btn_flag: "apt_scan" }
            PropertyChanges { target: apt_statusImage; iconName: "green.png"; text: "已完成"}
        },
        State {
            name: "AptWorkEmpty"
            PropertyChanges { target: apt_label; visible: true; text: "扫描内容为空，不再执行清理！" }
            PropertyChanges { target: apt_bitButton; /*hoverimage: "scan-start.png"*/ text:"开始扫描"}
            PropertyChanges { target: root; apt_btn_flag: "apt_scan" }
            PropertyChanges { target: apt_statusImage; iconName: "green.png"; text: "已完成"}
        }
    ]
}
