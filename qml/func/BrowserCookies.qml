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
//    property string title: "清理浏览器Cookies"
//    property string description: "清理浏览器Cookies可以保障系统安全"
    property string title: "清理浏览器登录信息,保护个人隐私"
    property string description: "清理上网时留下的登录信息,目前仅支持Firefox浏览器"
    property string btn_flag: "cookies_scan"
    property SystemDispatcher dis: systemdispatcher
    property ListModel listmodel: mainModel
    property ListModel submodel: subModel
    property int sub_num: 0//number of subitem
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
    property bool null_flag: false

    property int itemHeight: 40
//    property alias expandedItemCount: subItemRepeater.count
    property bool expanded: true //kobe:子项扩展默认打开

    signal cookies_signal(string cookies_msg);
    onCookies_signal: {
        if (cookies_msg == "CookiesWork") {
            console.log("1111111");
            console.log(cookies_msg);

            //get data of cookies
//            var cookies_data = systemdispatcher.scan_cookies_records_qt();
            var cookies_data = sessiondispatcher.scan_cookies_records_qt();
            if (cookies_data == "")
                root.null_flag = true;
            else
                root.null_flag = false;
            console.log("****************************8");
            console.log(cookies_data);
            root.sub_num = cookies_data.length;
            console.log(root.sub_num);
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
                    systemdispatcher.set_cookies_args(splitlist[0]);
                }
            }

            root.sub_num -= num;
            mainModel.clear();
            mainModel.append({"itemTitle": "清理Cookies ( 发现" + root.sub_num + "处记录 )",
                             "picture": "../img/toolWidget/cookies.png",
                             "detailstr": "清理Firefox浏览器自动保存的登录信息(Cookies)",
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
            itemTitle: "清理Cookies"
            picture: "../img/toolWidget/cookies.png"
            detailstr: "清理Firefox浏览器自动保存的登录信息(Cookies)"
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


    //信号绑定，绑定qt的信号finishCleanWork，该信号emit时触发onFinishCleanWork
    Connections
    {
        target: systemdispatcher
//         onFinishScanWork: {
//             console.log("begin onFinishScanWork..............");
        //             if (btn_flag == "cookies_scan") {
        //                 console.log("******cookies_scan Signal handler received  Start******");
        ////                 console.log(msg);
        ////                 titleBar.work_result = msg;
        //                 titleBar.state = "CookiesWork";
        //             }

//         }
        onFinishCleanWork: {
//            console.log(msg);//apt software   package   history   cookies
            if (btn_flag == "cookies_work") {
                if (msg == "cookies") {
                    root.work_result = msg;
                    root.state = "CookiesWorkFinish";
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
            source: "../img/toolWidget/trace.png"
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

        //status picture
        Image {
            id: statusImage
            source: "../img/toolWidget/unfinish.png"
            fillMode: "PreserveAspectFit"
            smooth: true
            anchors {
//                        top: parent.top; topMargin: 110
//                        left: parent.left; leftMargin: 650
                right: label.left
                rightMargin: 20
                verticalCenter: parent.verticalCenter
            }
        }

        Common.Label {
            id: label
            visible: false
            text: ""
            anchors.right: bitButton.left
            anchors.rightMargin: 20
            anchors.verticalCenter: parent.verticalCenter
        }

        Common.Button {
            id: bitButton
            width: 120
            height: 39
            hoverimage: "scan-start.png"
//            text: root.btn_text
            anchors.right: parent.right
            anchors.rightMargin: 50
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                //broswer cookies
                 if (btn_flag == "cookies_scan") {
                     cookies_signal("CookiesWork");
                     if(root.null_flag == true) {
                        root.state = "CookiesWorkEmpty";
                         sessiondispatcher.send_warningdialog_msg("友情提示：","扫描内容为空，不再执行清理！");
                     }
                     else if(root.null_flag == false)
                        root.state = "CookiesWork";
                 }
                 else if (btn_flag == "cookies_work") {
                     console.log(systemdispatcher.get_cookies_args());
                     systemdispatcher.clean_cookies_records_qt(systemdispatcher.get_cookies_args());
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
                spacing: 10
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
                    anchors {
                        left: clearImage.right; leftMargin: 15
                        verticalCenter: parent.verticalCenter
                    }
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


                Image {
                    id: arrow
                    fillMode: "PreserveAspectFit"
//                    height: parent.height*0.3
                    height: 28
                    width: 26
                    source: root.arrow
                    //当鼠标点击后,箭头图片旋转90度
//                    rotation: expanded ? 90 : 0
                    rotation: expanded ? 0 : -180
                    smooth: true
                    anchors {
                        left: clearImage.right
                        verticalCenter: parent.verticalCenter
                        leftMargin: 750
                    }
                }

                MouseArea {
                    id: mouseRegion
                    anchors.fill: status_update_content
                    onPressed: {
//                        console.log(root.width)
                        expanded = !expanded
                    }
                }
            }//母项Row

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
//                        model: attributes
                        model: subModel
//                        model: mysubmodel
                        width: subItemsRect.width
                        ListItem {
                            id: subListItem
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

                            onClicked: {/*console.log(number)*/}
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
            name: "CookiesWork"
             PropertyChanges { target: label; visible: true; text: "cookies扫描完成"}
             PropertyChanges { target: bitButton; hoverimage: "clear-start.png" }
            PropertyChanges { target: root; btn_flag: "cookies_work" }
        },
        State {
            name: "CookiesWorkFinish"
            PropertyChanges { target: label; visible: true; text: root.work_result + "清理完毕！" }
            PropertyChanges { target: bitButton; hoverimage: "scan-start.png" }
            PropertyChanges { target: root; btn_flag: "cookies_scan" }
            PropertyChanges { target: statusImage; source: "../img/toolWidget/finish.png"}
        },
        State {
            name: "CookiesWorkEmpty"
            PropertyChanges { target: label; visible: true; text: "扫描内容为空，不再执行清理！" }
            PropertyChanges { target: bitButton; hoverimage: "scan-start.png" }
            PropertyChanges { target: root; btn_flag: "cookies_scan" }
            PropertyChanges { target: statusImage; source: "../img/toolWidget/finish.png"}
        }
    ]
}
