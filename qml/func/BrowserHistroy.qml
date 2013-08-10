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
//import SystemType 0.1
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
            console.log(history_msg);
            root.num = systemdispatcher.scan_history_records_qt();
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
        target: systemdispatcher
//         onFinishScanWork: {
//             console.log("begin onFinishScanWork..............");
        //             if (btn_flag == "history_scan") {
        //                 console.log("******history_scan Signal handler received  Start******");
        ////                 console.log(msg);
        //                 titleBar.work_result = msg;
        //                 titleBar.state = "HistoryWork";
        ////                 console.log("******End******");
        //             }

//         }
        onFinishCleanWork: {
//            console.log("33333333333333");
//            console.log(msg);//apt software   package   history   cookies
//            console.log(btn_flag);
            if (btn_flag == "history_work") {
                if (msg == "history") {
                    console.log("******Clear Signal handler received  Start history_work******");
    //                 console.log(msg);
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
//        anchors {
//            fill: parent
//            left: parent.left
//            leftMargin: -2
//        }
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
        Common.Label {
            id: label
            visible: false
            text: ""
            anchors.right: bitButton.left
            anchors.rightMargin: 20
            anchors.verticalCenter: parent.verticalCenter
        }
//        ScanBtn {
//            id: historyBtn
//            iconName: "scan-start.png"
//            setbtn_flag: btn_flag
//            anchors {
//                left: parent.left; leftMargin: 480
//            }
//            width: 120
//            height: 39
//        }


//        Rectangle {
//            id: btnItem
//            anchors.left: parent.left
//            anchors.leftMargin: 600
//            Image {
//                id: bitButton
//        //        anchors.horizontalCenter: parent.horizontalCenter
//                source: "../img/icons/scan-start.png"
//            }

//            Image {
//                id: btnImg
//                anchors.fill: parent
//                source: ""
//            }
//            MouseArea {
//                hoverEnabled: true
//                anchors.fill: parent
//                onEntered: {
//                        btnImg.source = "../img/icons/onekeyBtn-hover.png"
//                }
//                onClicked: {
//                    //broswer history
//                    console.log("1231232134");
//                     if (btn_flag == "history_scan") {
//                         console.log("history_scan---------------");
//                         if (systemdispatcher.get_history_flag())
//                            root.state = "HistoryWork";
//                         else
//                             sessiondispatcher.send_warningdialog_msg("对不起，您没有选中历史记录扫描项，请确认！");
//    //                     history_signal("HistoryWork");
//                     }
//                     else if (btn_flag == "history_work") {
//                         console.log("history_work---------------");
//                         if (systemdispatcher.get_history_flag())
//                            systemdispatcher.clean_history_records_qt();
//                         else
//                             sessiondispatcher.send_warningdialog_msg("对不起，您没有选中历史记录清理项，请确认！");
//                     }
//                }
//            }
//        }



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
                //broswer history
                 if (btn_flag == "history_scan") {
                     console.log("history_scan---------------");
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
                     console.log("history_work---------------");
                     if (systemdispatcher.get_history_flag())
                        systemdispatcher.clean_history_records_qt();
                     else
                         sessiondispatcher.send_warningdialog_msg("友情提示：","对不起，您没有选中历史记录清理项，请确认！");
                 }
            }
        }

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
//            PropertyChanges { target: bitButton; text: "开始清理" }
             PropertyChanges { target: bitButton; hoverimage: "clear-start.png" }
            PropertyChanges { target: root; btn_flag: "history_work" }
        },
        State {
            name: "HistoryWorkFinish"
            PropertyChanges { target: label; visible: true; text: root.work_result + "清理完毕！" }
//            PropertyChanges { target: bitButton; text: "开始扫描" }
            PropertyChanges { target: bitButton; hoverimage: "scan-start.png" }
            PropertyChanges { target: root; btn_flag: "history_scan" }
            PropertyChanges { target: historystatus; source: "../img/toolWidget/finish.png"}
        },
        State {
            name: "HistoryWorkEmpty"
            PropertyChanges { target: label; visible: true; text: "扫描内容为空，不再执行清理！" }
            PropertyChanges { target: bitButton; hoverimage: "scan-start.png" }
            PropertyChanges { target: root; btn_flag: "history_scan" }
            PropertyChanges { target: historystatus; source: "../img/toolWidget/finish.png"}
        }
    ]
}












//Item {
//    id:root
////    property Dispatcher dis: mydispather
//    width: parent.width
//    height: 435//420//340
////    color:"#c3c3c3"
//    //垃圾清理自定义标题栏
//    property string btn_text: "开始扫描"
//    property string title: "清理浏览器历史记录"
//    property string description: "清理浏览器历史记录可以保障系统安全"
//    property string btn_flag: "history_scan"
//    property ListModel listmodel: mainModel
//    property ListModel submodel: subModel
//    property string work_result: ""
//    property int sub_num: 0


//    signal history_signal(string history_msg);
//    onHistory_signal: {
//        if (history_msg == "HistoryWork") {
//            console.log("&&&&&&&&&&&&&&&&&&&&&&&");
//            console.log(history_msg);


//            //get data of cookies
////            var cookies_data = systemdispatcher.scan_cookies_records_qt();
////            console.log("****************************8");
////            root.sub_num = cookies_data.length;
////            subModel.clear();
////            for (var i=0; i< cookies_data.length; i++) {
////                console.log(cookies_data[i]);
////                subModel.append({"itemTitle": cookies_data[i], "number": i});
////            }

////            console.log("****************************9");

//            mainModel.clear();
//            mainModel.append({"itemTitle": "清理浏览器历史记录",
//                             "picture": "../img/icons/user.png",
//                             "detailstr": "清理浏览器历史记录，让系统更安全",
//                             "flags": "clear_history",
//                            "attributes":
//                                 [{"subItemTitle": "111"},
//                                 {"subItemTitle": "222"},
//                                 {"subItemTitle": "333"},
//                                 {"subItemTitle": "444"}]
//                             })
//            console.log("%%%%%%%%%%%%%%%%%%%%%%%55");
//        }

//    }

//    ListModel {
//        id: mainModel
//        ListElement {
//            itemTitle: "清理浏览器历史记录"
//            picture: "../img/icons/user.png"
//            detailstr: "清理浏览器历史记录，让系统更安全"
//            flags: "clear_history"
//            attributes: [
//                ListElement { subItemTitle: "" }
//            ]
//        }
//    }

//    ListModel {
//        id: subModel
//        ListElement {itemTitle: ""; desc: ""; number: ""}
//    }

//    //信号绑定，绑定qt的信号finishCleanWork，该信号emit时触发onFinishCleanWork
//    Connections
//    {
//        target: systemdispatcher
////         onFinishScanWork: {
////             console.log("begin onFinishScanWork..............");
//        //             if (btn_flag == "history_scan") {
//        //                 console.log("******history_scan Signal handler received  Start******");
//        ////                 console.log(msg);
//        //                 titleBar.work_result = msg;
//        //                 titleBar.state = "HistoryWork";
//        ////                 console.log("******End******");
//        //             }

////         }
//        onFinishCleanWork: {
////            console.log("33333333333333");
////            console.log(msg);//apt software   package   history   cookies
////            console.log(btn_flag);
//            if (btn_flag == "history_work") {
//                if (msg == "history") {
//                    console.log("******Clear Signal handler received  Start history_work******");
//    //                 console.log(msg);
//                    root.work_result = msg;
//                    root.state = "HistoryWorkFinish";
//                }
//            }
//        }
//    }

//    //titlebar
//    Row {
//        id: titlebar
//        spacing: 50
//        width: parent.width
//        height: 50
//        Column {
//            anchors.verticalCenter: parent.verticalCenter
//            anchors.left: parent.left
//            anchors.leftMargin: 30
////                width: parent.width - 150
//            spacing: 2
//            Text {
//                text: root.title
//                font.bold: true
//                font.pixelSize: 14
//            }
//            Text {
//                text: root.description
//                font.pixelSize: 12
//                color: "#7a7a7a"
//            }
//        }
//        Label {
//            id: label
//            visible: false
//            text: ""
//            anchors.right: bitButton.left
//            anchors.rightMargin: 20
//            anchors.verticalCenter: parent.verticalCenter
//        }
//        Button {
//            id: bitButton
//            width: 95
//            height: 32
//            text: root.btn_text
//            anchors.right: parent.right
//            anchors.rightMargin: 50
//            anchors.verticalCenter: parent.verticalCenter
//            onClicked: {
//                 //broswer history
//                  if (btn_flag == "history_scan") {
//                      console.log("history_scan---------------");
//                      root.state = "HistoryWork";
//                      history_signal("HistoryWork");
//                  }
//                  else if (btn_flag == "history_work") {
//                      console.log("history_work---------------");
//                      systemdispatcher.clean_history_records_qt();
//                  }
//            }
//        }
//    }

//    ItemListModel {
//        id: pluginlist
//        anchors.top: titlebar.bottom
//        height: parent.height -titlebar.height
//        listmodel: root.listmodel
//        submodel: root.submodel
//        num: root.sub_num
//        btn_flag: root.btn_flag
//    }


//    states: [
//        State {
//            name: "HistoryWork"
//             PropertyChanges { target: label; visible: true; text: "history扫描完成"}
//            PropertyChanges { target: bitButton; text: "开始清理" }
//            PropertyChanges { target: root; btn_flag: "history_work" }
//        },
//        State {
//            name: "HistoryWorkFinish"
//            PropertyChanges { target: label; visible: true; text: root.work_result + "清理完毕！" }
//            PropertyChanges { target: bitButton; text: "开始扫描" }
//            PropertyChanges { target: root; btn_flag: "history_scan" }
//        }
//    ]
//}
