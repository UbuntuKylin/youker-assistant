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
import SessionType 0.1
import SystemType 0.1
import "common" as Common

Item {
    id:root
    width: parent.width
    height: 435//420//340
    property string btn_text: "开始扫描"
    property string title: "清理历史记录,保护个人隐私"
    property string description: "清理浏览器上网记录和系统最近打开文件记录"
    property string btn_flag: "history_scan"
    property string btn_flag2: "system_scan"
    property string work_result: ""
    property string keypage: "history"
    property int browserstatus_num: 0
    property int systemstatus_num: 0
    //母项字体
    property string headerItemFontName: "Helvetica"
    property int headerItemFontSize: 12
    property color headerItemFontColor: "black"
    property bool check_flag: true
    property bool null_flag: false
    property bool null_flag2: false
    signal history_bnt_signal(string history_msg);
    onHistory_bnt_signal: {
        if (history_msg == "BrowserWork") {
            browserstatus_num = sessiondispatcher.scan_history_records_qt();
            if (browserstatus_num == 0) {
                root.null_flag = true;
                browserstatus.visible = false;
                browserstatus.state = "BrowserWorkEmpty";
                sessiondispatcher.showWarningDialog("友情提示：","扫描内容为空，不再执行清理！", mainwindow.pos.x, mainwindow.pos.y);
                resetcBtn.visible = false;
            }
            else {
                browserstatus.state="BrowserWork";
                root.null_flag = false;
                browserstatus.visible = true;
            }
        }
        else if (history_msg == "SystemWork") {
            systemstatus_num = sessiondispatcher.scan_system_history_qt();
            if (systemstatus_num == 0) {
                root.null_flag2 = true;
                systemstatus.visible = false;
                systemstatus.state = "SystemWorkEmpty";
                sessiondispatcher.showWarningDialog("友情提示：","扫描内容为空，不再执行清理！", mainwindow.pos.x, mainwindow.pos.y);
                resetsBtn.visible = false;
            }
            else {
                systemstatus.state ="SystemWork";
                root.null_flag2 = false;
                systemstatus.visible = true;
            }
        }
    }

    Connections
    {
        target: systemdispatcher
        onFinishCleanWorkError: {
            if (btn_flag == "history_work") {
                if (msg == "history") {
                    browserstatus.state = "BrowserWorkError";
                }
            }
            else if(btn_flag2 == "system_work") {
                if (msg == "system") {
                    systemstatus.state = "SystemWorkError";
                }
            }
         }
        onFinishCleanWork: {
            if (btn_flag == "history_work") {
                if (msg == "") {
                    resetcBtn.visible = true;
                    if (browserstatus.visible == true){
                        browserstatus.visible = false;
                    }
                }
                else if (msg == "history") {
                    browserstatus.state = "BrowserWorkFinish";
                }
            }
            else if (btn_flag2 == "system_work") {
                if (msg == "") {
                    resetsBtn.visible = true;
                    if (systemstatus.visible == true){
                        systemstatus.visible = false;
                    }
                }
                else if (msg == "system") {
                    systemstatus.state = "SystemWorkFinish";
                }
            }
        }
    }
    //背景
    Image {
        source: "../img/skin/bg-bottom-tab.png"
        anchors.fill: parent
    }
    //titlebar
    Row {
        id: titlebar
        spacing: 20
        width: parent.width
        anchors { top: parent.top; topMargin: 20; left: parent.left; leftMargin: 27 }
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

    Column {
        anchors {
            top: parent.top
            topMargin: 140
            left: parent.left
            leftMargin: 45
        }
        spacing:30
        Item {
            width: parent.width
            height:45 //65
            Item {
                Behavior on scale { NumberAnimation { easing.type: Easing.InOutQuad} }
                id: scaleMe
                Row {
                    id: lineLayout
                    spacing: 15
                    anchors.verticalCenter: parent.verticalCenter
                    Common.CheckBox {
                        id: checkboxe1
                        checked:true    //将所有选项都check
                        anchors.verticalCenter: parent.verticalCenter
                        onCheckedChanged: {
                        }
                    }
                    Image {
                        id: clearImage1
                        width: 40; height: 42
                        source:"../img/toolWidget/history-min.png"
                    }
                    Column {
                        spacing: 5
                        Row{
                            spacing: 15
                            Text {
                                text: "清理浏览器上网记录"
                                font.bold: true
                                font.pixelSize: 14
                                color: "#383838"
                            }
                            Common.Label {
                                id: browserstatus_label
                                visible: false
                                text: ""
        //                        anchors.verticalCenter: parent.verticalCenter
                            }
                        }
                        Text {
                            text: "清理上网时留下的历史记录,目前仅支持Firefox浏览器"
                            font.pixelSize: 12
                            color: "#7a7a7a"
                        }
                    }
                }
                Common.StatusImage {
                    id: browserstatus
                    visible: false
                    iconName: "yellow.png"
                    text: "未完成"
                    anchors {
//                        top:parent.top
                        left: parent.left; leftMargin: 450
                        verticalCenter: parent.verticalCenter
                    }
                    states: [
                        State {
                            name: "BrowserWork"
                            PropertyChanges { target: browserstatus_label; visible: true; text: "(扫描到"+ browserstatus_num + "条记录)"}
                            PropertyChanges { target: cacheBtn; text:"开始清理"}
                            PropertyChanges { target: root; btn_flag: "history_work" }
                            PropertyChanges { target: browserstatus; iconName: "yellow.png"; text: "未完成"}
                        },
                        State {
                            name: "BrowserWorkAGAIN"
                            PropertyChanges { target: browserstatus_label; visible: false}
                            PropertyChanges { target: cacheBtn; text:"开始扫描" }
                            PropertyChanges { target: root; btn_flag: "history_scan" }
                            PropertyChanges { target: browserstatus; visible: false }
                        },
                        State {
                            name: "BrowserWorkError"
                            PropertyChanges { target: browserstatus_label; visible: true; text: "清理出现异常"}
                            PropertyChanges { target: cacheBtn; text:"开始扫描" }
                            PropertyChanges { target: root; btn_flag: "history_scan" }
                            PropertyChanges { target: browserstatus; visible: true; iconName: "red.png"; text: "出现异常"}
                        },
                        State {
                            name: "BrowserWorkFinish"
                            PropertyChanges { target: browserstatus_label; visible: true; text: root.work_result + "(已清理"+ browserstatus_num + "条记录)" }
                            PropertyChanges { target: cacheBtn; text:"开始扫描"}
                            PropertyChanges { target: root; btn_flag: "history_scan" }
                            PropertyChanges { target: browserstatus; visible: true; iconName: "green.png"; text: "已完成"}
                        },
                        State {
                            name: "BrowserWorkEmpty"
                            PropertyChanges { target: browserstatus_label; visible: true; text: "扫描内容为空，不再执行清理！" }
                            PropertyChanges { target: cacheBtn; text:"开始扫描" }
                            PropertyChanges { target: root; btn_flag: "history_scan" }
                            PropertyChanges { target: browserstatus; iconName: "green.png"; text: "已完成"}
                        }
                    ]
                }
                Rectangle {  //分割条
                    width: parent.width; height: 1
                    anchors { top: lineLayout.bottom; topMargin: 5}
                    color: "gray"
                }
            }
        }
        //----------------------------
        Item {
        width: parent.width//clearDelegate.ListView.view.width
        height: 45//65

        Item {
            Behavior on scale { NumberAnimation { easing.type: Easing.InOutQuad} }
            id: scaleMe1
            //checkbox, picture and words
            Row {
                id: lineLayout1
                spacing: 15
                anchors.verticalCenter: parent.verticalCenter
               Common.CheckBox {
                    id: checkboxe2
                    checked:true    //将所有选项都check
                    anchors.verticalCenter: parent.verticalCenter
                    onCheckedChanged: {
                    }
                }
                Image {
                    id: clearImage2
                    width: 40; height: 42
                    source: "../img/toolWidget/systemtrace.png"
                }
                Column {
                    spacing: 5
                    Row{
                        spacing: 15
                        Text {
                            text: "清理最近打开文件记录"
                            font.bold: true
                            font.pixelSize: 14
                            color: "#383838"
                        }
                        Common.Label {
                            id: systemstatus_label
                            visible: false
                            text: ""
        //                    anchors.verticalCenter: parent.verticalCenter
                        }
                    }
                    Text {
                        text: "清理系统上最近的文件打开记录，保护您的个人隐私"
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
           }
            Common.StatusImage {
                id: systemstatus
                visible: false
                iconName: "yellow.png"
                text: "未完成"
                anchors {
//                    top:parent.top
                    left: parent.left; leftMargin: 450
                    verticalCenter: parent.verticalCenter
                }
                states: [
                    State {
                        name: "SystemWork"
                        PropertyChanges { target: systemstatus_label; visible: true; text: "(扫描到"+ systemstatus_num + "条记录)"}
                        PropertyChanges { target: sysBtn; text:"开始清理"}
                        PropertyChanges { target: root; btn_flag2: "system_work" }
                        PropertyChanges { target: systemstatus; iconName: "yellow.png"; text: "未完成"}
                    },
                    State {
                        name: "SystemWorkAGAIN"
                        PropertyChanges { target: systemstatus_label; visible: false}
                        PropertyChanges { target: sysBtn; text:"开始扫描" }
                        PropertyChanges { target: root; btn_flag2: "system_scan" }
                        PropertyChanges { target: systemstatus; visible: false }
                    },
                    State {
                        name: "SystemWorkError"
                        PropertyChanges { target: systemstatus_label; visible: true; text: "清理出现异常"}
                        PropertyChanges { target: sysBtn; text:"开始扫描" }
                        PropertyChanges { target: root; btn_flag2: "system_scan" }
                        PropertyChanges { target: systemstatus; iconName: "red.png"; text: "出现异常"}
                    },
                    State {
                        name: "SystemWorkFinish"
                        PropertyChanges { target: systemstatus_label; visible: true; text: root.work_result + "(已清理"+ systemstatus_num + "条记录)"}
                        PropertyChanges { target: sysBtn; text:"开始扫描"}
                        PropertyChanges { target: root; btn_flag2: "system_scan" }
                        PropertyChanges { target: systemstatus; iconName: "green.png"; text: "已完成"}
                    },
                    State {
                        name: "SystemWorkEmpty"
                        PropertyChanges { target: systemstatus_label; visible: true; text: "扫描内容为空，不再执行清理！" }
                        PropertyChanges { target: sysBtn; text:"开始扫描" }
                        PropertyChanges { target: root; btn_flag2: "system_scan" }
                        PropertyChanges { target: systemstatus; iconName: "green.png"; text: "已完成"}
                    }
                ]
            }
        }
      }
    }
    //================================
    Row {
        id:cacherow
        anchors {
            top: titlebar.bottom
            topMargin: 50
            right: parent.right
            rightMargin: 50
        }
        spacing: 20
        Common.Button {
            id: cacheBtn
            width: 95
            height: 30
            hoverimage: "green2.png"
            text: root.btn_text
            onClicked: {
                if (btn_flag == "history_scan") {
                    if(!checkboxe1.checked) {
                       browserstatus.visible = false;
                       sessiondispatcher.showWarningDialog("友情提示：","对不起，您没有选中历史记录扫描项，请确认！", mainwindow.pos.x, mainwindow.pos.y);
                    }
                    else {
                        resetcBtn.visible = true;
                        history_bnt_signal("BrowserWork");
                    }
                }
               else if (btn_flag == "history_work") {
                    if(checkboxe1.checked) {
                        if(root.null_flag == true) {
                            root.state = "BrowserWorkEmpty";
                            sessiondispatcher.showWarningDialog("友情提示：","扫描内容为空，不再执行清理！", mainwindow.pos.x, mainwindow.pos.y);
                        }
                        else {
                            resetcBtn.visible = false;
                            systemdispatcher.set_user_homedir_qt();
                            browserstatus.visible = true;
                            systemdispatcher.clean_history_records_qt();
                        }
                    }
                    else
                        sessiondispatcher.showWarningDialog("友情提示：","对不起，您没有选中记录清理项，请确认！", mainwindow.pos.x, mainwindow.pos.y);
                }
            }
        }
        SetBtn {
            id: resetcBtn
            width: 12
            height: 15
            iconName: "revoke.png"
            visible: false
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                resetcBtn.visible = false;
                browserstatus.state = "BrowserWorkAGAIN";
            }
        }
    }
    Row {
        anchors {
            top: cacherow.bottom
            topMargin: 43
            right: parent.right
            rightMargin: 50
        }
        spacing: 20
        Common.Button {
            id: sysBtn
            width: 95
            height: 30
            hoverimage: "green2.png"
            text: root.btn_text
            onClicked: {
                if (btn_flag2 == "system_scan") {
                    if(!checkboxe2.checked) {
                       systemstatus.visible = false;
                       sessiondispatcher.showWarningDialog("友情提示：","对不起，您没有选中历史记录扫描项，请确认！", mainwindow.pos.x, mainwindow.pos.y);
                    }
                    else {
                        resetsBtn.visible = true;
                        history_bnt_signal("SystemWork");
                    }
                }
               else if (btn_flag2 == "system_work") {
                    if(checkboxe2.checked) {
                        if(root.null_flag2 == true) {
                            root.state = "SystemWorkEmpty";
                            sessiondispatcher.showWarningDialog("友情提示：","扫描内容为空，不再执行清理！", mainwindow.pos.x, mainwindow.pos.y);
                        }
                        else {
                            resetsBtn.visible = false;
                            systemdispatcher.set_user_homedir_qt();
                            systemstatus.visible = true;
                            systemdispatcher.clean_system_history_qt();
                        }
                    }
                    else
                        sessiondispatcher.showWarningDialog("友情提示：","对不起，您没有选中记录清理项，请确认！", mainwindow.pos.x, mainwindow.pos.y);
                }
            }
        }
        SetBtn {
            id: resetsBtn
            width: 12
            height: 15
            iconName: "revoke.png"
            visible: false
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                resetsBtn.visible = false;
                systemstatus.state = "SystemWorkAGAIN";
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
}
