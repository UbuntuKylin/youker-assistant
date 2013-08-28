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
    property string title: "清理浏览器上网记录,保护个人隐私"
    property string description: "清理上网时留下的历史记录,目前仅支持Firefox浏览器"
    property string btn_flag: "history_scan"

    property string work_result: ""

    property string keypage: "history"
    property int num: 0

    //母项字体
    property string headerItemFontName: "Helvetica"
    property int headerItemFontSize: 12
    property color headerItemFontColor: "black"

    property bool check_flag: true
    property bool null_flag: false

    signal history_bnt_signal(string history_msg);
    onHistory_bnt_signal: {
        if (history_msg == "HistoryWork") {
//            root.num = systemdispatcher.scan_history_records_qt();
            root.num = sessiondispatcher.scan_history_records_qt();
            if (root.num == 0)
                root.null_flag = true;
            else
                root.null_flag = false;
//            root.state = "HistoryWork";
        }
    }


    //信号绑定，绑定qt的信号finishCleanWork，该信号emit时触发onFinishCleanWork
    Connections
    {
//        target: sessiondispatcher
        target: systemdispatcher
//         onFinishScanWork: {
        //             if (btn_flag == "history_scan") {
        //                 titleBar.work_result = msg;
        //                 titleBar.state = "HistoryWork";
        //             }

//         }
        onFinishCleanWork: {
            if (btn_flag == "history_work") {
                if (msg == "history") {
                    root.work_result = msg;
                    root.state = "HistoryWorkFinish";
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
        anchors { top: parent.top; topMargin: 20; left: parent.left; leftMargin: 20 }
        Image {
            id: refreshArrow
            source: "../img/toolWidget/history-max.png"
            Behavior on rotation { NumberAnimation { duration: 200 } }
        }
        Column {
            spacing: 10
            id: mycolumn
            Text {
                id: text0
                width: 69
                text: root.title
                font.bold: true
                font.pixelSize: 14
                color: "#383838"
            }
            Text {
                id: text
                width: 69
                text: root.description
                font.pixelSize: 12
                color: "#7a7a7a"
            }
        }
    }
    Row{
        anchors { top: parent.top; topMargin: 30;right: parent.right ; rightMargin: 40 }
        spacing: 20
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
            hoverimage: "green1.png"
            text: root.btn_text
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                //broswer history
                 if (btn_flag == "history_scan") {
                     if (systemdispatcher.get_history_flag()) {
                        history_bnt_signal("HistoryWork");
                         if(root.null_flag == true) {
                            root.state = "HistoryWorkEmpty";
                             sessiondispatcher.send_warningdialog_msg("友情提示：","扫描内容为空，不再执行清理！");
                         }
                         else if(root.null_flag == false)
                            root.state = "HistoryWork";
                     }
                     else
                         sessiondispatcher.send_warningdialog_msg("友情提示：","对不起，您没有选中历史记录扫描项，请确认！");
//                     history_signal("HistoryWork");
                 }
                 else if (btn_flag == "history_work") {
                     if (systemdispatcher.get_history_flag()) {
//                         sessiondispatcher.clean_history_records_qt();
                         systemdispatcher.set_user_homedir_qt();
                         systemdispatcher.clean_history_records_qt();
                     }
                     else
                         sessiondispatcher.send_warningdialog_msg("友情提示：","对不起，您没有选中历史记录清理项，请确认！");
                 }
            }
        }
//        Common.Button {
//            id: bitButton
//            width: 120
//            height: 39
////            hoverimage: "scan-start.png"
//            text:"开始扫描"
//            bold:true
//            textsize: 12
//            anchors.verticalCenter: parent.verticalCenter
//            onClicked: {
//                //broswer history
//                 if (btn_flag == "history_scan") {
//                     if (systemdispatcher.get_history_flag()) {
//                        history_bnt_signal("HistoryWork");
//                         if(root.null_flag == true) {
//                            root.state = "HistoryWorkEmpty";
//                             sessiondispatcher.send_warningdialog_msg("友情提示：","扫描内容为空，不再执行清理！");
//                         }
//                         else if(root.null_flag == false)
//                            root.state = "HistoryWork";
//                     }
//                     else
//                         sessiondispatcher.send_warningdialog_msg("友情提示：","对不起，您没有选中历史记录扫描项，请确认！");
////                     history_signal("HistoryWork");
//                 }
//                 else if (btn_flag == "history_work") {
//                     if (systemdispatcher.get_history_flag()) {
////                         sessiondispatcher.clean_history_records_qt();
//                         systemdispatcher.set_user_homedir_qt();
//                         systemdispatcher.clean_history_records_qt();
//                     }
//                     else
//                         sessiondispatcher.send_warningdialog_msg("友情提示：","对不起，您没有选中历史记录清理项，请确认！");
//                 }
//            }
//        }

    }//Row

    Item {
        id: views
        width: parent.width ////ListView不会随鼠标上下移动
//                width:fastmode.width -10 //ListView会随鼠标上下移动
        anchors.top: parent.top
        anchors.topMargin: 130

        ListModel {
            id: clearModel
            ListElement {
                titlename: "清理浏览器历史记录"
                picturename: "../img/toolWidget/history-min.png"
                detailstr: "清理Firefox地址栏历史记录"
                clearflag: "history"
            }
        }

        ListView {
            id: listView
            height: parent.height
            width: parent.width
            anchors.top: parent.top
//                    anchors.topMargin: titlebar.height + 45
            model: clearModel
            delegate: FastDelegate {pagenum: root.keypage}//"history"
            cacheBuffer: 1000
        }
    }



    Image {
        id: historystatus
        source: "../img/toolWidget/unfinish.png"
        anchors {
            top: parent.top; topMargin: 120
            left: parent.left; leftMargin: 650
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


    states: [
        State {
            name: "HistoryWork"
            PropertyChanges { target: label; visible: true; text: "history扫描完成:" + root.num + "条记录"}
             PropertyChanges { target: bitButton; /*hoverimage: "clear-start.png"*/ text:"开始清理"}
            PropertyChanges { target: root; btn_flag: "history_work" }
        },
        State {
            name: "HistoryWorkFinish"
            PropertyChanges { target: label; visible: true; text: root.work_result + "清理完毕！" }
            PropertyChanges { target: bitButton; /*hoverimage: "scan-start.png"*/ text:"开始扫描"}
            PropertyChanges { target: root; btn_flag: "history_scan" }
            PropertyChanges { target: historystatus; source: "../img/toolWidget/finish.png"}
        },
        State {
            name: "HistoryWorkEmpty"
            PropertyChanges { target: label; visible: true; text: "扫描内容为空，不再执行清理！" }
            PropertyChanges { target: bitButton; /*hoverimage: "scan-start.png"*/text:"开始扫描" }
            PropertyChanges { target: root; btn_flag: "history_scan" }
            PropertyChanges { target: historystatus; source: "../img/toolWidget/finish.png"}
        }
    ]
}
