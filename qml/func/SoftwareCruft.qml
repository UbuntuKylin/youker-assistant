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
    property string btn_text: "开始扫描"
    property string title: "软件中心缓存深度清理"
    property string description: "深度清理软件中心缓存,节省磁盘空间"
    property string btn_flag: "software_scan"
    property SystemDispatcher dis: systemdispatcher
    property ListModel listmodel: mainModel
    property ListModel submodel: subModel
    property int sub_num: 0
    property string work_result: ""


    //箭头图标
    property string arrow: '../img/icons/arrow.png'
    //母项字体
    property string headerItemFontName: "Helvetica"
    property int headerItemFontSize: 12
    property color headerItemFontColor: "black"
    //子项字体
    property string subItemFontName: "Helvetica"
    property int subItemFontSize: headerItemFontSize-2
    property color subItemFontColor: "black"
    property bool check_flag: true

    property int itemHeight: 40
//    property alias expandedItemCount: subItemRepeater.count
    property bool expanded: true //kobe:子项扩展默认打开

    property bool null_flag: false

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
            if (software_data == "")
                root.null_flag = true;
            else
                root.null_flag = false;
            root.sub_num = software_data.length;
            systemdispatcher.clear_software_args();
            subModel.clear();
            var num = 0;
            for (var i=0; i< software_data.length; i++) {
            //  /home/kobe/.cache/software-center/piston-helper<2_2>3026257
                var splitlist = software_data[i].split("<2_2>");
                if (splitlist[0] == "") {
                    num++;
                }
                else {
                    subModel.append({"itemTitle": splitlist[0], "desc": "","number": splitlist[1] + "字节"});
                    systemdispatcher.set_software_args(splitlist[0]);
                }
            }
            root.sub_num -= num;
            mainModel.clear();
            mainModel.append({"itemTitle": "软件中心缓存清理",
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
        id: mainModel
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
        id: subModel
        ListElement {itemTitle: ""; desc: ""; number: ""}
    }



    //信号绑定，绑定qt的信号finishCleanWork，该信号emit时触发onFinishCleanWork
    Connections
    {
        target: systemdispatcher
//         onFinishScanWork: {
        //             if (btn_flag == "software_scan") {
        //                 titleBar.work_result = msg;
        //                 titleBar.state = "SoftwareWork";
        //             }

//         }
        onFinishCleanWork: {
            if (btn_flag == "software_work") {
                if (msg == "software") {
                    root.work_result = msg;
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


    //titlebar
    Row {
        id: titlebar
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
                text: root.title
                font.bold: true
                font.pixelSize: 14
                color: "#383838"
            }
            Text {
                text: root.description
                font.pixelSize: 12
                color: "#7a7a7a"
            }
        }
    }
    Row{
        anchors { top: parent.top; topMargin: 30;right: parent.right ; rightMargin: 40 }
        spacing: 20
        //status picture
        Image {
            id: statusImage
            source: "../img/toolWidget/unfinish.png"
            fillMode: "PreserveAspectFit"
            smooth: true
            anchors.verticalCenter: parent.verticalCenter
        }

        Common.Label {
            id: label
            visible: false
            text: ""
            anchors.verticalCenter: parent.verticalCenter
        }

        Common.Button {
            id: bitButton
            width: 120
            height: 39
            hoverimage: "scan-start.png"
//            text: root.btn_text
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                //software cruft
                 if (btn_flag == "software_scan") {
                     software_signal("SoftwareWork");
                     if(root.null_flag == true) {
                        root.state = "SoftwareWorkEmpty";
                         sessiondispatcher.send_warningdialog_msg("友情提示：","扫描内容为空，不再执行清理！");
                     }
                     else if(root.null_flag == false)
                        root.state = "SoftwareWork";
                 }
                 else if (btn_flag == "software_work") {
                     systemdispatcher.clean_file_cruft_qt(systemdispatcher.get_software_args(), "software");
//                     sessiondispatcher.clean_file_cruft_qt(systemdispatcher.get_software_args(), "software");
                 }
            }
        }
    }
    //分割条
    Rectangle {
        id: splitbar
        anchors {
            top: titlebar.bottom
            topMargin: 18
            left: parent.left
            leftMargin: 2
        }
        width: parent.width - 4
        height: 1
        color: "#b9c5cc"
    }

    Component {
        id: listViewDelegate
        Item {
            id: delegate
            property alias expandedItemCount: subItemRepeater.count
            x: 5; y: 2
            width: root.width
            height: headerItemRect.height + subItemsRect.height

            //母项
            //checkbox, picture and words
            Row {
                id: headerItemRect
                x: 5; y: 2
                width: root.width
                height: root.itemHeight
                spacing: 170
                Row{
                    spacing: 15
                    Image {
                        id: clearImage
                        fillMode: "PreserveAspectFit"
                        height: parent.height*0.9
                        source: picture
                        smooth: true
                    }

                    Column {
                        id: status_update_content
                        spacing: 5
                        anchors.verticalCenter: parent.verticalCenter
                        Text {
                            text: itemTitle
                            font.pointSize: 11
                            color: "black"
                        }
                        Text {
                            text: detailstr
                            font.pointSize: 9
                            color: "gray"
                        }
                    }
                }

            }//母项Row
            Image {
                id: arrow
                fillMode: "PreserveAspectFit"
//                    height: parent.height*0.3
                height: 28
                width: 26
                x:740
                y:15
                source: root.arrow
                //当鼠标点击后,箭头图片旋转90度
//                    rotation: expanded ? 90 : 0
                rotation: expanded ? 0 : -180
                smooth: true
                MouseArea {
                    id: mouseRegion
                    anchors.fill: parent
                    onPressed: {
                        expanded = !expanded
                    }
                }
            }

            //子项
            Item {
                id: subItemsRect
                property int itemHeight: root.itemHeight
                y: headerItemRect.height
                width: root.width
                //当高度需要扩展时,根据expandedItemCount数目和itemHeight高度去扩展
                height: expanded ? delegate.expandedItemCount * itemHeight : 0
                clip: true
                opacity: 1
                Behavior on height {
                    SequentialAnimation {
                        NumberAnimation { duration: 100; easing.type: Easing.InOutQuad }
                    }
                }

                Column {
                    width: root.width
                    Repeater {
                        id: subItemRepeater
                        model: subModel
                        width: subItemsRect.width
                        ListItem {
                            id: subListItem
                            split_status: true
                            width: root.width
                            height: subItemsRect.itemHeight
//                            text: subItemTitle
                            text: itemTitle
                            descript: desc
                            size_num: number
                            checkbox_status: root.check_flag
//                            bgImage: "../../img/icons/list_subitem.png"
                            bgImage: ""
                            fontName: root.subItemFontName
                            fontSize: root.subItemFontSize
                            fontColor: root.subItemFontColor
                            textIndent: 20

                            btn_flag: root.btn_flag

                            onClicked: {}
                        }

                    }//Repeater
                }//Column
            }//子项Item
        }
    }//Component


    Common.ScrollArea {
        frame:false
        anchors.top: titlebar.bottom
        anchors.topMargin: 30
        height: root.height -titlebar.height - 50
        width: parent.width
        Item {
            width: parent.width
            height: (root.sub_num + 1) * 40 //450 + //this height must be higher than root.height, then the slidebar can display
            //垃圾清理显示内容
            ListView {
                id: listView
                height: parent.height
                model: mainModel
                delegate: listViewDelegate
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
             PropertyChanges { target: label; visible: true; text: "software扫描完成"}
             PropertyChanges { target: bitButton; hoverimage: "clear-start.png" }
            PropertyChanges { target: root; btn_flag: "software_work" }
        },
        State {
            name: "SoftwareWorkFinish"
            PropertyChanges { target: label; visible: true; text: root.work_result + "清理完毕！" }
            PropertyChanges { target: bitButton; hoverimage: "scan-start.png" }
            PropertyChanges { target: root; btn_flag: "software_scan" }
            PropertyChanges { target: statusImage; source: "../img/toolWidget/finish.png"}
        },
        State {
            name: "SoftwareWorkEmpty"
            PropertyChanges { target: label; visible: true; text: "扫描内容为空，不再执行清理！" }
            PropertyChanges { target: bitButton; hoverimage: "scan-start.png" }
            PropertyChanges { target: root; btn_flag: "software_scan" }
            PropertyChanges { target: statusImage; source: "../img/toolWidget/finish.png"}
        }
    ]
}
