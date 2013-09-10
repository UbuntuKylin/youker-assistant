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
import "common" as Common

Item {
    id:root
    width: parent.width
    height: 435//420//340
    property string sof_title: "软件中心缓存深度清理"
    property string sof_description: "深度清理软件中心缓存,节省磁盘空间"
    property string sof_btn_flag: "software_scan"
    property string btn_text: "开始扫描"
    property SystemDispatcher dis: systemdispatcher
    property int sof_sub_num: 0
    property string sof_work_result: ""
    property int sof_num:sof_sub_num
    property bool sof_null_flag: false
    property bool sof_check_flag:true
    property int deleget_arrow :0



    function remove_last_name(str)
    {
        var need_str = str;
        need_str = need_str.substr(0, need_str.lastIndexOf("/"));
        return need_str;
    }

    signal software_signal(string software_msg);
    onSoftware_signal: {
        if (software_msg == "SoftwareWork") {
            //get data of cookies
//            var software_data = systemdispatcher.scan_softwarecenter_cruft_qt();
            var software_data = sessiondispatcher.scan_softwarecenter_cruft_qt();
            if (software_data == "") {
                root.sof_null_flag = true;
                if(sof_statusImage.visible == true)
                    sof_statusImage.visible = false;
            }
            else {
                root.sof_null_flag = false;
                sof_statusImage.visible == true
            }
            root.sof_sub_num = software_data.length;
            systemdispatcher.clear_software_args();
            sof_subModel.clear();
            var num = 0;
            for (var i=0; i< software_data.length; i++) {
            //  /home/kobe/.cache/software-center/piston-helper<2_2>3026257
                var splitlist = software_data[i].split("<2_2>");
                if (splitlist[0] == "") {
                    num++;
                }
                else {
                    sof_subModel.append({"itemTitle": splitlist[0], "desc": "","number": splitlist[1] + "字节"});
                    systemdispatcher.set_software_args(splitlist[0]);
                }
            }
            root.sof_sub_num -= num;
            sof_num=sof_sub_num
            if(sof_num!=0)
                sof_check_flag=true;
            sof_mainModel.clear();
            sof_mainModel.append({"itemTitle": "软件中心缓存清理",
                             "picture": "../img/toolWidget/software-min.png",
                                 "detailstr": "用户可以根据扫描结果选择性地清理软件中心缓存,缓存路径为:" + sessiondispatcher.get_home_path() + "/.cache/software-center/",
                             "flags": "clear_software",
                            "attributes":
                                 [{"subItemTitle": "Cookies1"},
                                 {"subItemTitle": "Cookies2"},
                                 {"subItemTitle": "Cookies3"},
                                 {"subItemTitle": "Cookies4"}]
                             })
        }
    }


    ListModel {
        id: sof_mainModel
        ListElement {
            itemTitle: "软件中心缓存清理"
            picture: "../img/toolWidget/software-min.png"
            detailstr: "用户可以根据扫描结果选择性地清理软件中心缓存"
            flags: "clear_software"
            attributes: [
                ListElement { subItemTitle: "" }
            ]
        }
    }

    ListModel {
        id: sof_subModel
        ListElement {itemTitle: ""; desc: ""; number: ""}
    }



    //信号绑定，绑定qt的信号finishCleanWork，该信号emit时触发onFinishCleanWork
    Connections
    {
        target: systemdispatcher
//         onFinishScanWork: {
        //             if (sof_btn_flag == "software_scan") {
        //                 sof_titlebar.work_result = msg;
        //                 sof_titlebar.state = "SoftwareWork";
        //             }

//         }
        onFinishCleanWorkError: {
            if (sof_btn_flag == "software_work") {
                if (msg == "software") {
                    root.sof_work_result = msg;
                    root.state = "SoftwareWorkError";
                }
            }
         }
        onFinishCleanWork: {
            if (sof_btn_flag == "software_work") {
                if (msg == "software") {
                    root.sof_work_result = msg;
                    root.state = "SoftwareWorkFinish";
                }
            }
        }
    }

//    //背景
    Image {
        source: "../img/skin/bg-bottom-tab.png"
        anchors.fill: parent
    }


    //sof_titlebar
    Row {
        id: sof_titlebar
        spacing: 20
        width: parent.width
//        height: 50
        anchors { top: parent.top; topMargin: 20; left: parent.left; leftMargin: 20 }
        Image {
            id: refreshArrow
            source: "../img/toolWidget/software-max.png"
            Behavior on rotation { NumberAnimation { duration: 200 } }
        }
        Column {
            anchors.verticalCenter: parent.verticalCenter
            spacing: 10
            Text {
                text: root.sof_title
                font.bold: true
                font.pixelSize: 14
                color: "#383838"
            }
            Text {
                text: root.sof_description
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
//            id: sof_statusImage
//            source: "../img/toolWidget/unfinish.png"
//            fillMode: "PreserveAspectFit"
//            smooth: true
//            anchors.verticalCenter: parent.verticalCenter
//        }
        Common.StatusImage {
            id: sof_statusImage
            visible: false
            iconName: "yellow.png"
            text: "未完成"
            anchors.verticalCenter: parent.verticalCenter
        }

        Common.Label {
            id: sof_label
            visible: false
            text: ""
            anchors.verticalCenter: parent.verticalCenter
        }


        Common.Button {
            id: sof_bitButton
            width: 120
            height: 39
            hoverimage: "green1.png"
            text: root.btn_text
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                if(root.sof_check_flag)
                {
                //software cruft
                 if (sof_btn_flag == "software_scan") {
                     software_signal("SoftwareWork");
                     if(root.sof_null_flag == true) {
                        root.state = "SoftwareWorkEmpty";
                         deleget_arrow=0;
                         sessiondispatcher.send_warningdialog_msg("友情提示：","扫描内容为空，不再执行清理！");
                     }
                     else if(root.sof_null_flag == false)
                     {
                        root.state = "SoftwareWork";
                         deleget_arrow=1;
                     }
                 }
                 else if (sof_btn_flag == "software_work") {
                     systemdispatcher.clean_file_cruft_qt(systemdispatcher.get_software_args(), "software");
                     deleget_arrow=1;
                 }
                }
                else
                    sessiondispatcher.send_warningdialog_msg("友情提示：","对不起，您没有选择需要清理的项，请确认！");
            }
        }
//        Common.Button {
//            id: sof_bitButton
//            width: 120
//            height: 39
////            hoverimage: "scan-start.png"
//            text:"开始扫描"
//            bold:true
//            textsize: 12
//            anchors.verticalCenter: parent.verticalCenter
//            onClicked: {
//                if(root.sof_check_flag)
//                {
//                //software cruft
//                 if (sof_btn_flag == "software_scan") {
//                     software_signal("SoftwareWork");
//                     if(root.sof_null_flag == true) {
//                        root.state = "SoftwareWorkEmpty";
//                         sessiondispatcher.send_warningdialog_msg("友情提示：","扫描内容为空，不再执行清理！");
//                     }
//                     else if(root.sof_null_flag == false)
//                        root.state = "SoftwareWork";
//                 }
//                 else if (sof_btn_flag == "software_work") {
//                     systemdispatcher.clean_file_cruft_qt(systemdispatcher.get_software_args(), "software");
////                     sessiondispatcher.clean_file_cruft_qt(systemdispatcher.get_software_args(), "software");
//                 }
//                }
//                else
//                    sessiondispatcher.send_warningdialog_msg("友情提示：","对不起，您没有选择需要清理的项，请确认！");
//            }
//        }
    }
    //分割条
    Rectangle {
        id: splitbar
        anchors {
            top: sof_titlebar.bottom
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
////                    height: parent.height*0.3
//                height: 28
//                width: 26
//                x:740
//                y:15
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
//                        model: sof_subModel
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
//                            checkbox_status: root.sof_check_flag
////                            bgImage: "../../img/icons/list_subitem.png"
//                            bgImage: ""
//                            fontName: root.subItemFontName
//                            fontSize: root.subItemFontSize
//                            fontColor: root.subItemFontColor
//                            textIndent: 20

//                            btn_flag: root.sof_btn_flag

//                            onClicked: {}
//                        }

//                    }//Repeater
//                }//Column
//            }//子项Item
//        }
//    }//Component


    Common.ScrollArea {
        frame:false
        anchors.top: sof_titlebar.bottom
        anchors.topMargin: 30
        height: root.height -sof_titlebar.height - 50
        width: parent.width
        Item {
            width: parent.width
            height: (root.sof_num + 1) * 40 //450 + //this height must be higher than root.height, then the slidebar can display
            //垃圾清理显示内容
            ListView {
                id: sof_listView
                height: parent.height
                model: sof_mainModel
                delegate: Cleardelegate{
                    sub_num: sof_sub_num;sub_model: sof_subModel;btn_flag: sof_btn_flag;arrow_display:deleget_arrow;
                    delegate_flag: true
                    onSubpressed: {root.sof_num=hMark}
                    onCheckchanged: {root.sof_check_flag=checkchange}
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
            name: "SoftwareWork"
             PropertyChanges { target: sof_label; visible: true; text: "software扫描完成"}
             PropertyChanges { target: sof_bitButton; /*hoverimage: "clear-start.png"*/text:"开始清理" }
            PropertyChanges { target: root; sof_btn_flag: "software_work" }
            PropertyChanges { target: sof_statusImage; visible: true; iconName: "yellow.png"; text: "未完成"}
        },
        State {
            name: "SoftwareWorkError"
            PropertyChanges { target: sof_label; visible: true; text: "清理出现异常"}
            PropertyChanges { target: sof_bitButton; text:"开始扫描" }
            PropertyChanges { target: root; sof_btn_flag: "software_scan" }
            PropertyChanges { target: sof_statusImage; visible: true; iconName: "red.png"; text: "出现异常"}
        },
        State {
            name: "SoftwareWorkFinish"
            PropertyChanges { target: sof_label; visible: true; text: root.sof_work_result + "清理完毕！" }
            PropertyChanges { target: sof_bitButton; /*hoverimage: "scan-start.png"*/text:"开始扫描" }
            PropertyChanges { target: root; sof_btn_flag: "software_scan" }
            PropertyChanges { target: sof_statusImage; visible: true; iconName: "green.png"; text: "已完成"}
        },
        State {
            name: "SoftwareWorkEmpty"
            PropertyChanges { target: sof_label; visible: true; text: "扫描内容为空，不再执行清理！" }
            PropertyChanges { target: sof_bitButton; /*hoverimage: "scan-start.png"*/text:"开始扫描" }
            PropertyChanges { target: root; sof_btn_flag: "software_scan" }
            PropertyChanges { target: sof_statusImage; visible: false}
        }
    ]
}
