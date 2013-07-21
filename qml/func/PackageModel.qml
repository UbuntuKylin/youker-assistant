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
    property string title: "卸载不必要的安装程序"
    property string description: "清理软件安装过程中安装的依赖程序，提高系统性能"
    property string btn_flag: "package_scan"
    property SystemDispatcher dis: systemdispatcher
    property ListModel listmodel: mainModel
    property ListModel submodel: subModel
    property int sub_num: 0
    property string work_result: ""

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
            mainModel.append({"itemTitle": "卸载不必要的安装程序",
                             "picture": "../img/icons/user.png",
                             "detailstr": "卸载不再需要的安装程序,让系统更瘦",
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



    //信号绑定，绑定qt的信号finishCleanWork，该信号emit时触发onFinishCleanWork
    Connections
    {
        target: systemdispatcher
//         onFinishScanWork: {
        //             if (btn_flag == "package_scan") {
        //                 console.log("******package_scan Signal handler received  Start******");
        ////                 console.log("33333333333333");
        ////                 console.log(msg);
        //                 titleBar.work_result = msg;
        //                 titleBar.state = "UnneedWork";
        //             }

//         }
        onFinishCleanWork: {
            console.log("33333333333333");
            console.log(msg);//apt software   package   history   cookies
            console.log(btn_flag);
            if (msg == "package") {
                console.log("******Clear Signal handler received  Start package_work******");
//                 console.log(msg);
                root.work_result = msg;
                root.state = "UnneedWorkFinish";
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
                 //software cruft
                  if (btn_flag == "package_scan") {
                      console.log("package_scan---------------");
                      root.state = "UnneedWork";
                      unneed_signal("UnneedWork");
                  }
                  else if (btn_flag == "package_work") {
                      console.log("package_work---------------");
                      console.log(systemdispatcher.get_package_args());
                      systemdispatcher.clean_package_cruft_qt(systemdispatcher.get_package_args());
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
            name: "UnneedWork"
            PropertyChanges { target: label; visible: true; text: "unneed扫描完成"}
            PropertyChanges { target: bitButton; text: "开始清理" }
            PropertyChanges { target: root; btn_flag: "package_work" }
        },
        State {
            name: "UnneedWorkFinish"
            PropertyChanges { target: label; visible: true; text: root.work_result + "清理完毕！" }
            PropertyChanges { target: bitButton; text: "开始扫描" }
            PropertyChanges { target: root; btn_flag: "package_scan" }
        }
    ]
}
