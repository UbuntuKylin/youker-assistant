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
import SudoType 0.1
import "common" as Common

Item {
    id:root
    width: parent.width
    height: 435//420//340
    property string btn_text: "开始扫描"
    property string title: "卸载不必要的程序"
    property string description: "清理软件安装过程中安装的依赖程序，提高系统性能"
    property string btn_flag: "package_scan"
    property SystemDispatcher dis: systemdispatcher
    property ListModel listmodel: mainModel
    property ListModel submodel: subModel
    property int pac_sub_num: 0
    property int sub_num: pac_sub_num
    property string work_result: ""
    property bool check_flag:true
    property bool null_flag: false
    property int deleget_arrow :0

    signal unneed_signal(string unneed_msg);
    onUnneed_signal: {
        if (unneed_msg == "UnneedWork") {
            //get data of unneed
//            var unneed_data = systemdispatcher.scan_unneed_packages_qt();
            var unneed_data = sessiondispatcher.scan_unneed_packages_qt();
            if (unneed_data == "") {
                root.null_flag = true;
                if(statusImage.visible == true)
                    statusImage.visible = false;
            }
            else {
                root.null_flag = false;
                statusImage.visible = true;
            }
            root.pac_sub_num = unneed_data.length;
            systemdispatcher.clear_package_args();
            subModel.clear();
            var num = 0;
            for (var i=0; i< unneed_data.length; i++) {
            //linux-headers-3.8.0-19<2_2>Header files related to Linux kernel version 3.8.0<2_2>60094464
                var splitlist = unneed_data[i].split("<2_2>");
                if (splitlist[0] == "") {
                    num++;
                }
                else {
                    subModel.append({"itemTitle": splitlist[0], "desc": splitlist[1], "number": splitlist[2]});
                    systemdispatcher.set_package_args(splitlist[0]);
                }
            }
            root.pac_sub_num -= num;
            sub_num= pac_sub_num
            if(sub_num!=0)
                check_flag=true;
            mainModel.clear();
            mainModel.append({"itemTitle": "卸载不必要的程序",
                             "picture": "../img/toolWidget/deb-min.png",
                             "detailstr": "用户可以根据扫描结果选择性地清理不再需要的安装程序,让系统更瘦",
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
            itemTitle: "卸载不必要的程序"
            picture: "../img/toolWidget/deb-min.png"
            detailstr: "用户可以根据扫描结果选择性地清理不再需要的安装程序,让系统更瘦"
            flags: "clear_package"
            attributes: [
                ListElement { subItemTitle: "" }
            ]
        }
    }

    ListModel {
        id: subModel
        ListElement {itemTitle: ""; desc: ""; number: ""}
    }

    Connections
    {
        target: sudodispatcher
        onFinishCleanDebError: {
            if (btn_flag == "package_work") {
//                titleBar.work_result = msg;
                titleBar.state = "UnneedWorkError";
                toolkits.alertMSG("清理出现异常！", mainwindow.pos.x, mainwindow.pos.y);
            }

         }
        onFinishCleanDeb: {
            if (btn_flag == "package_work") {
                if (msg == "") {
                    resetBtn.visible = true;
                }
                else if (msg == "package") {
//                    root.work_result = msg;
                    root.state = "UnneedWorkFinish";
                    toolkits.alertMSG("清理完毕！", mainwindow.pos.x, mainwindow.pos.y);
                    unneed_signal("UnneedWork");
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
        anchors { top: parent.top; topMargin: 20; left: parent.left; leftMargin: 27}
        Image {
            id: refreshArrow
            source: "../img/toolWidget/deb-max.png"
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
//        Image {
//            id: statusImage
//            source: "../img/toolWidget/unfinish.png"
//            fillMode: "PreserveAspectFit"
//            smooth: true
//            anchors.verticalCenter: parent.verticalCenter
//        }
        Common.StatusImage {
            id: statusImage
            visible: false
            iconName: "yellow.png"
            text: "未完成"
            anchors.verticalCenter: parent.verticalCenter
        }
        Common.Button {
            id: bitButton
            width: 120
            height: 39
            hoverimage: "green1.png"
            text: root.btn_text
            fontsize: 15
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                if(sudodispatcher.get_sudo_daemon_qt() == "SudoDaemon") {
                    if(!sudodispatcher.getUKSignalFlag()) {
                        sudodispatcher.setUKSignalFlag(true);
                        sudodispatcher.bind_signals_after_dbus_start();
                    }
                    resetBtn.visible = false;
                    if(root.check_flag)
                    {
                        //package cruft
                        if (btn_flag == "package_scan") {
                            unneed_signal("UnneedWork");
                            if(root.null_flag == true) {
                                root.state = "UnneedWorkEmpty";
                                deleget_arrow=0;
                                sessiondispatcher.showWarningDialog("友情提示：","扫描内容为空，不再执行清理！", mainwindow.pos.x, mainwindow.pos.y);
                            }
                            else if(root.null_flag == false)
                            {
                                root.state = "UnneedWork";
                                deleget_arrow=1;
                                toolkits.alertMSG("扫描完成！", mainwindow.pos.x, mainwindow.pos.y);
                            }
                        }
                        else if (btn_flag == "package_work") {
                            sudodispatcher.clean_package_cruft_qt(systemdispatcher.get_package_args());
                            deleget_arrow=1;
                        }
                    }
                    else
                        sessiondispatcher.showWarningDialog("友情提示：","对不起，您没有选择需要清理的项，请确认！", mainwindow.pos.x, mainwindow.pos.y);
                }
                else {
                    sudodispatcher.showPasswdDialog(mainwindow.pos.x, mainwindow.pos.y);
                }
            }
        }
        SetBtn {
            id: resetBtn
            width: 12
            height: 15
            iconName: "revoke.png"
            visible: false
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                resetBtn.visible = false;
                subModel.clear();
                root.state = "UnneedWorkAGAIN";
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
        color: "#d8e0e6"
    }

    Common.ScrollArea {
        frame:false
        anchors.top: titlebar.bottom
        anchors.topMargin: 20//30
        anchors.left:parent.left
        anchors.leftMargin: 27
        height: root.height -titlebar.height - 37//50
        width: parent.width - 27 -2
        Item {
            width: parent.width
            height: (root.sub_num + 1) * 40 //450 + //this height must be higher than root.height, then the slidebar can display
            //垃圾清理显示内容
            ListView {
                id: listView
                height: parent.height
                model: mainModel
                delegate: Cleardelegate{
                    sub_num:root.pac_sub_num;sub_model: subModel ;btn_flag:root.btn_flag;arrow_display:deleget_arrow;
                    delegate_flag: false
                    onSubpressed: {root.sub_num=hMark}
                    onCheckchanged: {root.check_flag=checkchange}
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
            name: "UnneedWork"
            PropertyChanges { target: bitButton; text:"开始清理" }
            PropertyChanges { target: root; btn_flag: "package_work" }
            PropertyChanges { target: statusImage; visible: true; iconName: "yellow.png"; text: "未完成"}
        },
        State {
            name: "UnneedWorkAGAIN"
            PropertyChanges { target: bitButton; text:"开始扫描" }
            PropertyChanges { target: root; btn_flag: "package_scan" }
            PropertyChanges { target: statusImage; visible: false }
        },
        State {
            name: "UnneedWorkError"
            PropertyChanges { target: bitButton; text:"开始扫描" }
            PropertyChanges { target: root; btn_flag: "package_scan" }
            PropertyChanges { target: statusImage; visible: true; iconName: "red.png"; text: "出现异常"}
        },
        State {
            name: "UnneedWorkFinish"
            PropertyChanges { target: bitButton; text:"开始扫描" }
            PropertyChanges { target: root; btn_flag: "package_scan" }
            PropertyChanges { target: statusImage; visible: true; iconName: "green.png"; text: "已完成"}
        },
        State {
            name: "UnneedWorkEmpty"
            PropertyChanges { target: bitButton; text:"开始扫描"}
            PropertyChanges { target: root; btn_flag: "package_scan" }
            PropertyChanges { target: statusImage; visible: false}
        }
    ]
}
