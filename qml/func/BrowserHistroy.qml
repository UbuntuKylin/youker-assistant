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
    property string work_result: ""
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

    //titlebar
    Row {
        id: titlebar
        spacing: 50
        width: parent.width
        height: 50
        Column {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 30
//                width: parent.width - 150
            spacing: 2
            Text {
                text: root.title
                font.bold: true
                font.pixelSize: 14
            }
            Text {
                text: root.description
                font.pixelSize: 12
                color: "#7a7a7a"
            }
        }
        Label {
            id: label
            visible: false
            text: ""
            anchors.right: bitButton.left
            anchors.rightMargin: 20
            anchors.verticalCenter: parent.verticalCenter
        }
        Button {
            id: bitButton
            width: 95
            height: 32
            text: root.btn_text
            anchors.right: parent.right
            anchors.rightMargin: 50
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                 //broswer cookies
                  if (btn_flag == "history_scan") {
                      console.log("history_scan---------------");
                      root.state = "HistoryWork";
                      history_signal("HistoryWork");
                  }
                  else if (btn_flag == "history_work") {
                      console.log("history_work---------------");
                      systemdispatcher.clean_history_records_qt();
                  }
            }
        }
    }

    ItemListModel {
        id: pluginlist
        anchors.top: titlebar.bottom
        height: parent.height -titlebar.height
        listmodel: root.listmodel
        submodel: root.submodel
        num: root.sub_num
        btn_flag: root.btn_flag
    }


    states: [
        State {
            name: "HistoryWork"
             PropertyChanges { target: label; visible: true; text: "history扫描完成"}
            PropertyChanges { target: bitButton; text: "开始清理" }
            PropertyChanges { target: root; btn_flag: "history_work" }
        },
        State {
            name: "HistoryWorkFinish"
            PropertyChanges { target: label; visible: true; text: root.work_result + "清理完毕！" }
            PropertyChanges { target: bitButton; text: "开始扫描" }
            PropertyChanges { target: root; btn_flag: "history_scan" }
        }
    ]
}
