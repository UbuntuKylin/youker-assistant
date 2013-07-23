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
    width: parent.width
    height: 435//420//340
    property string btn_text: "开始扫描"
    property string title: "清理浏览器Cookies"
    property string description: "清理浏览器Cookies可以保障系统安全"
    property string btn_flag: "cookies_scan"
    property SystemDispatcher dis: systemdispatcher
    property ListModel listmodel: mainModel
    property ListModel submodel: subModel
    property int sub_num: 0
    property string work_result: ""

    signal cookies_signal(string cookies_msg);
    onCookies_signal: {
        if (cookies_msg == "CookiesWork") {
            console.log("1111111");
            console.log(cookies_msg);

            //get data of cookies
            var cookies_data = systemdispatcher.scan_cookies_records_qt();
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

//                subModel.append({"itemTitle": cookies_data[i], "number": i});
            }

//            console.log("**********************");
//            console.log(systemdispatcher.get_cookies_args());

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
//            console.log("33333333333333");
//            console.log(msg);//apt software   package   history   cookies
//            console.log(btn_flag);
            if (btn_flag == "cookies_work") {
                if (msg == "cookies") {
                    console.log("******Clear Signal handler received  Start cookies_work******");
    //                 console.log(msg);
                    root.work_result = msg;
                    root.state = "CookiesWorkFinish";
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
                  if (btn_flag == "cookies_scan") {
                      console.log("cookies_scan---------------");
                      root.state = "CookiesWork";
                      cookies_signal("CookiesWork");
                  }
                  else if (btn_flag == "cookies_work") {
                      console.log("cookies_work---------------");
                      console.log(systemdispatcher.get_cookies_args());
                      systemdispatcher.clean_cookies_records_qt(systemdispatcher.get_cookies_args());
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
            name: "CookiesWork"
             PropertyChanges { target: label; visible: true; text: "cookies扫描完成"}
            PropertyChanges { target: bitButton; text: "开始清理" }
            PropertyChanges { target: root; btn_flag: "cookies_work" }
        },
        State {
            name: "CookiesWorkFinish"
            PropertyChanges { target: label; visible: true; text: root.work_result + "清理完毕！" }
            PropertyChanges { target: bitButton; text: "开始扫描" }
            PropertyChanges { target: root; btn_flag: "cookies_scan" }
        }
    ]
}
