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
    property string title: "清理历史记录,保护个人隐私"
    property string description: "清理浏览器上网记录和系统最近打开文件记录"
    property string btn_flag: "history_scan"

    property string work_result: ""

    property string keypage: "history"
    property int browserstatus_num: 0
    property int systemstatus_num: 0
    property int checknum:2     //checkbox num
    property int check_num: checknum

    //母项字体
    property string headerItemFontName: "Helvetica"
    property int headerItemFontSize: 12
    property color headerItemFontColor: "black"

    property bool check_flag: true
    property bool null_flag: false


    signal history_bnt_signal(string history_msg);
    onHistory_bnt_signal: {
        if (history_msg == "BrowserWork") {
            browserstatus_num = sessiondispatcher.scan_history_records_qt();
            console.log("BrowserWork"+"  "+browserstatus_num);
            if (browserstatus_num == 0) {
                root.null_flag = true;
//                if(browserstatus.visible == true) {
                    browserstatus.visible = false;
                    browserstatus.state = "BrowserWorkEmpty";
                    sessiondispatcher.send_warningdialog_msg("友情提示：","扫描内容为空，不再执行清理！", mainwindow.pos.x, mainwindow.pos.y);
//                }
            }
            else {
                browserstatus.state="BrowserWork";
                root.null_flag = false;
                browserstatus.visible = true;
                checkboxe2.enabled=false;

            }
        }
        else if (history_msg == "SystemWork") {
            systemstatus_num = sessiondispatcher.scan_system_history_qt();
            console.log("SystemWork"+"  "+systemstatus_num);
            if (systemstatus_num == 0) {
                root.null_flag = true;
//                if(systemstatus.visible == true){
                    systemstatus.visible = false;
                    systemstatus.state = "OpenWorkEmpty";
                    sessiondispatcher.send_warningdialog_msg("友情提示：","扫描内容为空，不再执行清理！", mainwindow.pos.x, mainwindow.pos.y);
//                }
            }
            else {
                systemstatus.state ="OpenWork";
                root.null_flag = false;
                systemstatus.visible = true;
                checkboxe1.enabled=false;
            }
        }
        else if (history_msg == "AllWork") {
            browserstatus_num = sessiondispatcher.scan_history_records_qt()
            systemstatus_num = sessiondispatcher.scan_system_history_qt();
//            console.log("AllWork"+"  "+(browserstatus_num + systemstatus_num));
            if (browserstatus_num + systemstatus_num == 0) {
                root.null_flag = true;
                if(browserstatus.visible == true)
                    browserstatus.visible = false;
                if(systemstatus.visible == true)
                    systemstatus.visible = false;
                browserstatus.state = "BrowserWorkEmpty";
                systemstatus.state = "OpenWorkEmpty";
                sessiondispatcher.send_warningdialog_msg("友情提示：","扫描内容为空，不再执行清理！", mainwindow.pos.x, mainwindow.pos.y);
            }
            else {
                browserstatus.state="BrowserWork";
                systemstatus.state ="OpenWork";
                root.null_flag = false;
                browserstatus.visible = true;
                systemstatus.visible = true;
            }
        }
    }

//信号绑定，绑定qt的信号finishCleanWork，该信号emit时触发onFinishCleanWork
    Connections
    {
        target: systemdispatcher
        onFinishCleanWorkError: {
            if (btn_flag == "history_work") {
                if (msg == "history") {
                    browserstatus.state = "BrowserWorkError";
                    checkboxe2.enabled = true;
                }
                else if (msg == "system") {
                    systemstatus.state = "OpenWorkError";
                    checkboxe1.enabled = true;
                }
            }
         }
        onFinishCleanWork: {
            if (btn_flag == "history_work") {
                if (msg == "") {
                    if (browserstatus.visible == true){
                        browserstatus.visible = false;
                        checkboxe2.enabled=true;
                    }
                    if (systemstatus.visible == true){
                        systemstatus.visible = false;
                        checkboxe1.enabled=true;
                    }
                }
                else if (msg == "history") {
                    browserstatus.state = "BrowserWorkFinish";
                    checkboxe2.enabled=true;
                }
                else if (msg == "system") {
                    systemstatus.state = "OpenWorkFinish";
                    checkboxe1.enabled=true;
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
    Row{
        anchors { top: parent.top; topMargin: 30;right: parent.right ; rightMargin: 40 }
        spacing: 20

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
                     if(!checkboxe1.checked && !checkboxe2.checked) {
                         browserstatus.visible = false;
                         systemstatus.visible = false;
                        sessiondispatcher.send_warningdialog_msg("友情提示：","对不起，您没有选中历史记录扫描项，请确认！", mainwindow.pos.x, mainwindow.pos.y);
                     }
                     else {
                         if(checkboxe1.checked && !checkboxe2.checked)
                             history_bnt_signal("BrowserWork");
                         else if(!checkboxe1.checked && checkboxe2.checked)
                             history_bnt_signal("SystemWork");
                         else if(checkboxe1.checked && checkboxe2.checked)
                             history_bnt_signal("AllWork");
//                          if(root.null_flag == true) {
//                             root.state = "HistoryWorkEmpty";
//                              sessiondispatcher.send_warningdialog_msg("友情提示：","扫描内容为空，不再执行清理！", mainwindow.pos.x, mainwindow.pos.y);
//                          }
//                          else if(root.null_flag == false) {
//                             root.state = "HistoryWork";
//                              historystatus.visible = true;
//                          }
                     }
                 }
                else if (btn_flag == "history_work") {
                     if(!checkboxe1.checked && !checkboxe2.checked)
                         sessiondispatcher.send_warningdialog_msg("友情提示：","对不起，您没有选中记录清理项，请确认！", mainwindow.pos.x, mainwindow.pos.y);
                    else {
                         systemdispatcher.set_user_homedir_qt();

                         if(checkboxe1.checked) {
                             browserstatus.visible = true;
                             if(checkboxe2.checked) {
                                 systemstatus.visible = true;
                                 systemdispatcher.clean_history_records_qt(systemdispatcher.get_history_args("all"));
                             }
                             else
                                 systemdispatcher.clean_history_records_qt(systemdispatcher.get_history_args("history"));
                         }
                         else {
                             if(checkboxe2.checked) {
                                 systemstatus.visible = true;
                                 systemdispatcher.clean_history_records_qt(systemdispatcher.get_history_args("system"));
                             }
                             else
                                 systemdispatcher.clean_history_records_qt(systemdispatcher.get_history_args("null"));
                         }
//                        if(checkboxe1.checked) {
////                            console.log("checkboxe1"+"  "+checkboxe1.checked)
//                            browserstatus.visible = true;
//                            systemdispatcher.clean_history_records_qt();
//                        }
//                        if(checkboxe2.checked) {
////                            console.log("checkboxe2"+"  "+checkboxe2.checked)
//                            systemstatus.visible = true;
//                            systemdispatcher.clean_system_history_qt();
//                        }
                     }
                }
            }
        }
    }//Row


    //================================
    Row{
        id: checkrow
        spacing: 10
        anchors {
            top: parent.top
            topMargin: 110
            left: parent.left
            leftMargin: 30
        }
        Common.Label {
            id: itemtip
            text: "历史记录清理项目"
            font.bold: true
            font.pixelSize: 14
            color: "#008000"
        }
        Common.MainCheckBox {
            id:chek
            checked:"true"    //将所有选项都check
            onCheckedboolChanged: {
                checkboxe1.checked = chek.checkedbool;
                checkboxe2.checked = chek.checkedbool;
            }
        }
    }
    onCheck_numChanged: {
        if(check_num==0)
            chek.checked="false"
        else if(check_num==root.checknum)
            chek.checked="true"
        else
            chek.checked="mid"
    }
    Column {
        anchors.left: parent.left
        anchors.leftMargin: 45
        anchors.top: checkrow.bottom
        anchors.topMargin: 30
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
                            if(checkboxe1.checked)
                                root.check_num=root.check_num+1;
                            else
                                root.check_num=root.check_num-1;
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
                        top:parent.top
                        left: parent.left; leftMargin: 450
                    }
                    states: [
                        State {
                            name: "BrowserWork"
                            PropertyChanges { target: browserstatus_label; visible: true; text: "(扫描到"+ browserstatus_num + "条记录)"}
                            PropertyChanges { target: bitButton; text:"开始清理"}
                            PropertyChanges { target: root; btn_flag: "history_work" }
                            PropertyChanges { target: browserstatus; iconName: "yellow.png"; text: "未完成"}
                        },
                        State {
                            name: "BrowserWorkError"
                            PropertyChanges { target: browserstatus_label; visible: true; text: "清理出现异常"}
                            PropertyChanges { target: bitButton; text:"开始扫描" }
                            PropertyChanges { target: root; btn_flag: "history_scan" }
                            PropertyChanges { target: browserstatus; visible: true; iconName: "red.png"; text: "出现异常"}
                        },
                        State {
                            name: "BrowserWorkFinish"
                            PropertyChanges { target: browserstatus_label; visible: true; text: root.work_result + "(已清理"+ browserstatus_num + "条记录)" }
                            PropertyChanges { target: bitButton; text:"开始扫描"}
                            PropertyChanges { target: root; btn_flag: "history_scan" }
                            PropertyChanges { target: browserstatus; visible: true; iconName: "green.png"; text: "已完成"}
                        },
                        State {
                            name: "BrowserWorkEmpty"
                            PropertyChanges { target: browserstatus_label; visible: true; text: "扫描内容为空，不再执行清理！" }
                            PropertyChanges { target: bitButton; text:"开始扫描" }
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
        property SessionDispatcher dis: sessiondispatcher
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
                        if(checkboxe2.checked)
                            root.check_num=root.check_num+1;
                        else
                            root.check_num=root.check_num-1;
                    }
                }
                Image {
                    id: clearImage2
                    width: 40; height: 42
                    source: "../img/toolWidget/history.png"//picturename
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
                    top:parent.top
                    left: parent.left; leftMargin: 450
                }
                states: [
                    State {
                        name: "OpenWork"
                        PropertyChanges { target: systemstatus_label; visible: true; text: "(扫描到"+ systemstatus_num + "条记录)"}
                        PropertyChanges { target: bitButton; /*hoverimage: "clear-start.png"*/ text:"开始清理"}
                        PropertyChanges { target: root; btn_flag: "history_work" }
                        PropertyChanges { target: systemstatus; iconName: "yellow.png"; text: "未完成"}
                    },
                    State {
                        name: "OpenWorkError"
                        PropertyChanges { target: systemstatus_label; visible: true; text: "清理出现异常"}
                        PropertyChanges { target: bitButton; text:"开始扫描" }
                        PropertyChanges { target: root; btn_flag: "history_scan" }
                        PropertyChanges { target: systemstatus; iconName: "red.png"; text: "出现异常"}
                    },
                    State {
                        name: "OpenWorkFinish"
                        PropertyChanges { target: systemstatus_label; visible: true; text: root.work_result + "(已清理"+ systemstatus_num + "条记录)"}
                        PropertyChanges { target: bitButton; /*hoverimage: "scan-start.png"*/ text:"开始扫描"}
                        PropertyChanges { target: root; btn_flag: "history_scan" }
                        PropertyChanges { target: systemstatus; iconName: "green.png"; text: "已完成"}
                    },
                    State {
                        name: "OpenWorkEmpty"
                        PropertyChanges { target: systemstatus_label; visible: true; text: "扫描内容为空，不再执行清理！" }
                        PropertyChanges { target: bitButton; /*hoverimage: "scan-start.png"*/text:"开始扫描" }
                        PropertyChanges { target: root; btn_flag: "history_scan" }
                        PropertyChanges { target: systemstatus; iconName: "green.png"; text: "已完成"}
                    }
                ]
            }
        }
      }
    }
    //================================




//    Item {
//        id: views
//        width: parent.width ////ListView不会随鼠标上下移动
////                width:fastmode.width -10 //ListView会随鼠标上下移动
//        anchors.top: parent.top
//        anchors.topMargin: 130

//        ListModel {
//            id: clearModel
//            ListElement {
//                titlename: "清理浏览器上网记录"
//                picturename: "../img/toolWidget/history-min.png"
//                detailstr: "清理上网时留下的历史记录,目前仅支持Firefox浏览器"
//                clearflag: "history"
//            }
//        }

//        ListView {
//            id: listView
//            height: parent.height
//            width: parent.width
//            anchors.top: parent.top
////                    anchors.topMargin: titlebar.height + 45
//            model: clearModel
//            delegate: FastDelegate {pagenum: root.keypage}//"history"
//            cacheBuffer: 1000
//        }
//    }
//    Common.StatusImage {
//        id: historystatus
//        visible: false
//        iconName: "yellow.png"
//        text: "未完成"
//        anchors {
//            top: parent.top; topMargin: 120
//            left: parent.left; leftMargin: 650
//        }
//    }
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

//    states: [
//        State {
//            name: "HistoryWork"
//            PropertyChanges { target: label; visible: true; text: "history扫描完成:" + root.num + "条记录"}
//             PropertyChanges { target: bitButton; /*hoverimage: "clear-start.png"*/ text:"开始清理"}
//            PropertyChanges { target: root; btn_flag: "history_work" }
//        },
//        State {
//            name: "HistoryWorkError"
//            PropertyChanges { target: label; visible: true; text: "清理出现异常"}
//            PropertyChanges { target: bitButton; text:"开始扫描" }
//            PropertyChanges { target: root; btn_flag: "history_scan" }
//            PropertyChanges { target: historystatus; iconName: "red.png"; text: "出现异常"}
//        },
//        State {
//            name: "HistoryWorkFinish"
//            PropertyChanges { target: label; visible: true; text: root.work_result + "清理完毕！" }
//            PropertyChanges { target: bitButton; /*hoverimage: "scan-start.png"*/ text:"开始扫描"}
//            PropertyChanges { target: root; btn_flag: "history_scan" }
//            PropertyChanges { target: historystatus; iconName: "green.png"; text: "已完成"}
//        },
//        State {
//            name: "HistoryWorkEmpty"
//            PropertyChanges { target: label; visible: true; text: "扫描内容为空，不再执行清理！" }
//            PropertyChanges { target: bitButton; /*hoverimage: "scan-start.png"*/text:"开始扫描" }
//            PropertyChanges { target: root; btn_flag: "history_scan" }
//            PropertyChanges { target: historystatus; iconName: "green.png"; text: "已完成"}
//        }
//    ]
}





//Item {
//    id:root
//    width: parent.width
//    height: 435//420//340
//    property string btn_text: "开始扫描"
//    property string title: "清理浏览器上网记录,保护个人隐私"
//    property string description: "清理上网时留下的历史记录,目前仅支持Firefox浏览器"
//    property string btn_flag: "history_scan"

//    property string work_result: ""

//    property string keypage: "history"
//    property int num: 0

//    //母项字体
//    property string headerItemFontName: "Helvetica"
//    property int headerItemFontSize: 12
//    property color headerItemFontColor: "black"

//    property bool check_flag: true
//    property bool null_flag: false

//    signal history_bnt_signal(string history_msg);
//    onHistory_bnt_signal: {
//        if (history_msg == "HistoryWork") {
//            root.num = sessiondispatcher.scan_history_records_qt();
//            if (root.num == 0) {
//                root.null_flag = true;
//                if(historystatus.visible == true)
//                    historystatus.visible = false;
//            }
//            else {
//                root.null_flag = false;
//                historystatus.visible = true;
//            }
////            root.state = "HistoryWork";
//        }
//    }


//    //信号绑定，绑定qt的信号finishCleanWork，该信号emit时触发onFinishCleanWork
//    Connections
//    {
//        target: systemdispatcher
////         onFinishScanWork: {
//        //             if (btn_flag == "history_scan") {
//        //                 titleBar.work_result = msg;
//        //                 titleBar.state = "HistoryWork";
//        //             }

////         }
//        onFinishCleanWorkError: {
//            if (btn_flag == "history_work") {
//                if (msg == "history") {
//                    root.work_result = msg;
//                    root.state = "HistoryWorkError";
//                }
//            }
//         }
//        onFinishCleanWork: {
//            if (btn_flag == "history_work") {
//                if (msg == "history") {
//                    root.work_result = msg;
//                    root.state = "HistoryWorkFinish";
//                }
//            }
//        }
//    }

////    //背景
//    Image {
//        source: "../img/skin/bg-bottom-tab.png"
//        anchors.fill: parent
//    }


//    //titlebar
//    Row {
//        id: titlebar
//        spacing: 20
//        width: parent.width
//        anchors { top: parent.top; topMargin: 20; left: parent.left; leftMargin: 20 }
//        Image {
//            id: refreshArrow
//            source: "../img/toolWidget/history-max.png"
//            Behavior on rotation { NumberAnimation { duration: 200 } }
//        }
//        Column {
//            spacing: 10
//            id: mycolumn
//            Text {
//                id: text0
//                width: 69
//                text: root.title
//                font.bold: true
//                font.pixelSize: 14
//                color: "#383838"
//            }
//            Text {
//                id: text
//                width: 69
//                text: root.description
//                font.pixelSize: 12
//                color: "#7a7a7a"
//            }
//        }
//    }
//    Row{
//        anchors { top: parent.top; topMargin: 30;right: parent.right ; rightMargin: 40 }
//        spacing: 20
//        Common.Label {
//            id: label
//            visible: false
//            text: ""
//            anchors.verticalCenter: parent.verticalCenter
//        }

//        Common.Button {
//            id: bitButton
//            width: 120
//            height: 39
//            hoverimage: "green1.png"
//            text: root.btn_text
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
//                         else if(root.null_flag == false) {
//                            root.state = "HistoryWork";
//                             historystatus.visible = true;
//                         }
//                     }
//                     else {
//                         historystatus.visible = false;
//                         sessiondispatcher.send_warningdialog_msg("友情提示：","对不起，您没有选中历史记录扫描项，请确认！");
//                     }
////                     history_signal("HistoryWork");
//                 }
//                 else if (btn_flag == "history_work") {
//                     if (systemdispatcher.get_history_flag()) {
//                         historystatus.visible = true;
////                         sessiondispatcher.clean_history_records_qt();
//                         systemdispatcher.set_user_homedir_qt();
//                         systemdispatcher.clean_history_records_qt();
//                     }
//                     else
//                         sessiondispatcher.send_warningdialog_msg("友情提示：","对不起，您没有选中历史记录清理项，请确认！");
//                 }
//            }
//        }
////        Common.Button {
////            id: bitButton
////            width: 120
////            height: 39
//////            hoverimage: "scan-start.png"
////            text:"开始扫描"
////            bold:true
////            textsize: 12
////            anchors.verticalCenter: parent.verticalCenter
////            onClicked: {
////                //broswer history
////                 if (btn_flag == "history_scan") {
////                     if (systemdispatcher.get_history_flag()) {
////                        history_bnt_signal("HistoryWork");
////                         if(root.null_flag == true) {
////                            root.state = "HistoryWorkEmpty";
////                             sessiondispatcher.send_warningdialog_msg("友情提示：","扫描内容为空，不再执行清理！");
////                         }
////                         else if(root.null_flag == false)
////                            root.state = "HistoryWork";
////                     }
////                     else
////                         sessiondispatcher.send_warningdialog_msg("友情提示：","对不起，您没有选中历史记录扫描项，请确认！");
//////                     history_signal("HistoryWork");
////                 }
////                 else if (btn_flag == "history_work") {
////                     if (systemdispatcher.get_history_flag()) {
//////                         sessiondispatcher.clean_history_records_qt();
////                         systemdispatcher.set_user_homedir_qt();
////                         systemdispatcher.clean_history_records_qt();
////                     }
////                     else
////                         sessiondispatcher.send_warningdialog_msg("友情提示：","对不起，您没有选中历史记录清理项，请确认！");
////                 }
////            }
////        }

//    }//Row

//    Item {
//        id: views
//        width: parent.width ////ListView不会随鼠标上下移动
////                width:fastmode.width -10 //ListView会随鼠标上下移动
//        anchors.top: parent.top
//        anchors.topMargin: 130

//        ListModel {
//            id: clearModel
//            ListElement {
//                titlename: "清理浏览器历史记录"
//                picturename: "../img/toolWidget/history-min.png"
//                detailstr: "清理Firefox地址栏历史记录"
//                clearflag: "history"
//            }
//        }

//        ListView {
//            id: listView
//            height: parent.height
//            width: parent.width
//            anchors.top: parent.top
////                    anchors.topMargin: titlebar.height + 45
//            model: clearModel
//            delegate: FastDelegate {pagenum: root.keypage}//"history"
//            cacheBuffer: 1000
//        }
//    }



////    Image {
////        id: historystatus
////        source: "../img/toolWidget/unfinish.png"
////        anchors {
////            top: parent.top; topMargin: 120
////            left: parent.left; leftMargin: 650
////        }
////    }
//    Common.StatusImage {
//        id: historystatus
//        visible: false
//        iconName: "yellow.png"
//        text: "未完成"
//        anchors {
//            top: parent.top; topMargin: 120
//            left: parent.left; leftMargin: 650
//        }
//    }

//    //分割条
//    Rectangle {
//        id: splitbar
//        anchors {
//            top: titlebar.bottom
//            topMargin: 18
//            left: parent.left
//            leftMargin: 2
//        }
//        width: parent.width - 4
//        height: 1
//        color: "#b9c5cc"
//    }


//    states: [
//        State {
//            name: "HistoryWork"
//            PropertyChanges { target: label; visible: true; text: "history扫描完成:" + root.num + "条记录"}
//             PropertyChanges { target: bitButton; /*hoverimage: "clear-start.png"*/ text:"开始清理"}
//            PropertyChanges { target: root; btn_flag: "history_work" }
//        },
//        State {
//            name: "HistoryWorkError"
//            PropertyChanges { target: label; visible: true; text: "清理出现异常"}
//            PropertyChanges { target: bitButton; text:"开始扫描" }
//            PropertyChanges { target: root; btn_flag: "history_scan" }
//            PropertyChanges { target: historystatus; iconName: "red.png"; text: "出现异常"}
//        },
//        State {
//            name: "HistoryWorkFinish"
//            PropertyChanges { target: label; visible: true; text: root.work_result + "清理完毕！" }
//            PropertyChanges { target: bitButton; /*hoverimage: "scan-start.png"*/ text:"开始扫描"}
//            PropertyChanges { target: root; btn_flag: "history_scan" }
//            PropertyChanges { target: historystatus; iconName: "green.png"; text: "已完成"}
//        },
//        State {
//            name: "HistoryWorkEmpty"
//            PropertyChanges { target: label; visible: true; text: "扫描内容为空，不再执行清理！" }
//            PropertyChanges { target: bitButton; /*hoverimage: "scan-start.png"*/text:"开始扫描" }
//            PropertyChanges { target: root; btn_flag: "history_scan" }
//            PropertyChanges { target: historystatus; iconName: "green.png"; text: "已完成"}
//        }
//    ]
//}
