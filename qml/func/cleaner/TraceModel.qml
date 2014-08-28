/*
 * Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd.
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
import "../common" as Common

Rectangle {
    id:tracepage
    width: parent.width; height: 437
//    color: "#e4f2fc"

    property string btn_text: qsTr("Start scanning")//开始扫描
    property string title: qsTr("Cleanup history, to protect your privacy")//清理历史记录，保护个人隐私
    property string description: qsTr("Cleaning the internet and opened documents recently records")//清理浏览器上网记录和系统最近打开文件记录
    property string btn_flag: "history_scan"
    property string btn_flag3: "chromium_scan"
    property string btn_flag2: "system_scan"
    property string keypage: "history"
    property int browserstatus_num: 0
    property int chromium_num: 0
    property int systemstatus_num: 0
    //母项字体
    property string headerItemFontName: "Helvetica"
    property int headerItemFontSize: 12
    property color headerItemFontColor: "black"
    property bool check_flag: true
    property bool null_flag: false
    property bool null_flag3: false
    property bool null_flag2: false

    Connections
    {
        target: sessiondispatcher
        onTellQMLHistoryNumber: {
            if(flag == "firefox") {
                tracepage.browserstatus_num = num;
                if(tracepage.browserstatus_num == -1) {
                    toolkits.alertMSG(qsTr("Firefox is not installed!"));//没有安装Firefox！
                }
                else if (tracepage.browserstatus_num == 0) {
                    tracepage.null_flag = true;
                    internetBtnRow.state = "BrowserWorkEmpty";
                    //友情提示：      扫描内容为空，无需清理！
                    sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("The scan reslut is empty, nothing has been done!"));
                }
                else {
                    tracepage.null_flag = false;
                    internetBtnRow.state = "BrowserWork";
                    toolkits.alertMSG(qsTr("Scan completed!"));//扫描完成！
                    internetcacheBtn.text = qsTr("Begin cleanup");//开始清理
                    tracepage.btn_flag = "history_work";
                    browserstatus_label.visible = true;
                    internetbackBtn.visible = true;
                    internetrescanBtn.visible = true;
                }
            }
            else if(flag == "chromium") {
                tracepage.chromium_num = num;
                if(tracepage.chromium_num == -1) {
                    toolkits.alertMSG(qsTr("Chromium is not installed!"));//没有安装Chromium！
                }
                else if(tracepage.chromium_num == -99) {
                    //友情提示：      Chromium 正在运行。当浏览器运行的时候，不能执行扫描或者清理操作。
                    sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Chromium is running. When the browser is running, could not perform scan or cleanup operations."));//Chromium正在运行中。当它正在运行的时候，不能执行扫描或者清理操作。
                }
                else if (tracepage.chromium_num == 0) {
                    tracepage.null_flag3 = true;
                    chromiumBtnRow.state = "ChromiumWorkEmpty";
                    //友情提示：      扫描内容为空，无需清理！
                    sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("The scan reslut is empty, nothing has been done!"));
                }
                else {
                    tracepage.null_flag3 = false;
                    chromiumBtnRow.state = "ChromiumWork";
                    toolkits.alertMSG(qsTr("Scan completed!"));//扫描完成！
                    chromiumcacheBtn.text = qsTr("Begin cleanup");//开始清理
                    tracepage.btn_flag3 = "chromium_work";
                    chromiumstatus_label.visible = true;
                    chromiumbackBtn.visible = true;
                    chromiumrescanBtn.visible = true;
                }
            }
            else if(flag == "system") {
                tracepage.systemstatus_num = num;
                if (tracepage.systemstatus_num == 0) {
                    tracepage.null_flag2 = true;
                    fileBtnRow.state = "SystemWorkEmpty";
                    //友情提示      扫描内容为空，无需清理！
                    sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("The scan reslut is empty, nothing has been done!"));
                }
                else {
                    tracepage.null_flag2 = false;
                    fileBtnRow.state ="SystemWork";
                    toolkits.alertMSG(qsTr("Scan completed!"));//扫描完成！
                    syscacheBtn.text = qsTr("Begin cleanup");//开始清理
                    tracepage.btn_flag2 = "system_work";
                    systemstatus_label.visible = true;
                    filebackBtn.visible = true;
                    filerescanBtn.visible = true;
                }
            }
        }
    }

    //获取数据
    function getData(history_msg) {
        if (history_msg == "BrowserWork") {
            sessiondispatcher.scan_history_records_qt("firefox");
        }
        else if (history_msg == "ChromiumWork") {
            sessiondispatcher.scan_history_records_qt("chromium");
        }
        else if (history_msg == "SystemWork") {
            sessiondispatcher.scan_system_history_qt();
        }
    }

    Connections
    {
        target: systemdispatcher
        onFinishCleanWorkError: {//清理出错时收到的信号
            if (msg == "firefox") {
                if (tracepage.btn_flag == "history_work") {
                    internetBtnRow.state = "BrowserWorkError";
                    toolkits.alertMSG(qsTr("Cleanup abnormal!"));//清理出现异常！
                }
            }
            else if (msg == "chromium") {
                if (tracepage.btn_flag3 == "chromium_work") {
                    chromiumBtnRow.state = "ChromiumWorkError";
                    toolkits.alertMSG(qsTr("Cleanup abnormal!"));//清理出现异常！
                }
            }
            else if (msg == "system") {
                if(tracepage.btn_flag2 == "system_work") {
                    fileBtnRow.state = "SystemWorkError";
                    toolkits.alertMSG(qsTr("Cleanup abnormal!"));//清理出现异常！
                }
            }
         }
        onFinishCleanWork: {//清理成功时收到的信号
            if (msg == "") {
                toolkits.alertMSG(qsTr("Cleanup interrupted!"));//清理中断！
            }
            else if (msg == "firefox") {
                if (tracepage.btn_flag == "history_work") {
                    internetBtnRow.state = "BrowserWorkFinish";
                }
            }
            else if (msg == "chromium") {
                if (tracepage.btn_flag3 == "chromium_work") {
                    chromiumBtnRow.state = "ChromiumWorkFinish";
                }
            }
            else if (msg == "system") {
                if (tracepage.btn_flag2 == "system_work") {
                    fileBtnRow.state = "SystemWorkFinish";
                }
            }
        }
    }

    //titlebar
    Row {
        id: titlebar
        spacing: 20
        width: parent.width
        anchors { top: parent.top; topMargin: 20; left: parent.left; leftMargin: 27 }
        Image {
            id: refreshArrow
            source: "../../img/toolWidget/history-max.png"
            Behavior on rotation { NumberAnimation { duration: 200 } }
        }
        Column {
            spacing: 10
            id: mycolumn
            Text {
                id: text0
                width: 700
                text: tracepage.title
                wrapMode: Text.WordWrap
                font.bold: true
                font.pixelSize: 14
                color: "#383838"
            }
            Text {
                id: text
                width: 700
                wrapMode: Text.WordWrap
                text: tracepage.description
                font.pixelSize: 12
                color: "#7a7a7a"
            }
        }
    }
    //分割条
    Common.Separator {
        id: splitbar
        anchors {
            top: titlebar.bottom
            topMargin: 18
            left: parent.left
            leftMargin: 2
        }
        width: parent.width - 4
    }

    //文字显示Column
    Column {
        anchors {
            top: titlebar.bottom
            topMargin: 50
            left: parent.left
            leftMargin: 45
        }
        spacing:30
        //Internet browser record of firefox
        Row {
            id: internetRow
            spacing: 15
            Image {
                id: clearImage1
                width: 32; height: 32
                source: "../../img/toolWidget/firefox.png"
            }
            Column {
                spacing: 5
                Row{
                    spacing: 15
                    Text {
                        text: qsTr("Clean up the Firefox Internet records")//清理 Firefox 浏览器上网记录
                        wrapMode: Text.WordWrap
                        font.bold: true
                        font.pixelSize: 14
                        color: "#383838"
                    }
                    Common.Label {//显示扫描后的结果
                        id: browserstatus_label
                        visible: false
                        text: ""
                        color: "#318d11"
                    }
                }
                Text {
                    width: 450
                    text: qsTr("Clean up the Firefox history records")//清理 Firefox 浏览器上的历史记录
                    wrapMode: Text.WordWrap
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
        }

        //Internet browser record of chromium
        Row {
            id: chromiumRow
            spacing: 15
            Image {
                width: 32; height: 32
                source: "../../img/toolWidget/chromium.png"
            }
            Column {
                spacing: 5
                Row{
                    spacing: 15
                    Text {
                        text: qsTr("Clean up the Chromium Internet records")//清理 Chromium 浏览器上网记录
                        wrapMode: Text.WordWrap
                        font.bold: true
                        font.pixelSize: 14
                        color: "#383838"
                    }
                    Common.Label {//显示扫描后的结果
                        id: chromiumstatus_label
                        visible: false
                        text: ""
                        color: "#318d11"
                    }
                }
                Text {
                    width: 450
                    text: qsTr("Clean up the Chromium history records")//清理 Chromium 浏览器上的历史记录
                    wrapMode: Text.WordWrap
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
        }

        //opened documents recently
        Row {
            id: fileRow
            spacing: 15
            Image {
                id: clearImage2
                width: 32; height: 32
                source: "../../img/toolWidget/systemtrace.png"
            }
            Column {
                spacing: 5
                Row{
                    spacing: 15
                    Text {
                        text: qsTr("Clean up the recently opened documents records")//清理最近打开文件记录
                        wrapMode: Text.WordWrap
                        font.bold: true
                        font.pixelSize: 14
                        color: "#383838"
                    }
                    Common.Label {
                        id: systemstatus_label
                        visible: false
                        text: ""
                        color: "#318d11"
                    }
                }
                Text {
                    width: 450
                    text: qsTr("Clean up the recently opened documents in your system, to protect your privacy")//清理系统上最近的文件打开记录，保护您的个人隐私
                    wrapMode: Text.WordWrap
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
        }
    }

    //按钮显示Column
    Column {
        anchors {
            top: titlebar.bottom
            topMargin: 50
            right: parent.right
            rightMargin: 20
        }
        spacing:40
        Row{
            id: internetBtnRow
            spacing: 20
            anchors {
                right: parent.right
                rightMargin: 20
            }//add
            Row {
                spacing: 20
                anchors.verticalCenter: parent.verticalCenter
                Common.StyleButton {
                    id: internetbackBtn
                    visible: false
                    anchors.verticalCenter: parent.verticalCenter
                    wordname: qsTr("Back")//返回
                    width: 40
                    height: 20
                    onClicked: {
                        internetBtnRow.state = "BrowserWorkAGAIN";
                    }
                }
                Common.StyleButton {
                    id: internetrescanBtn
                    visible: false
                    anchors.verticalCenter: parent.verticalCenter
                    wordname: qsTr("Rescan")//重新扫描
                    width: 40
                    height: 20
                    onClicked: {
                        internetcacheBtn.text = qsTr("Start scanning");//开始扫描
                        tracepage.btn_flag = "history_scan";
                        internetbackBtn.visible = false;
                        internetrescanBtn.visible = false;
                        browserstatus_label.visible = false;
                        tracepage.getData("BrowserWork");
                    }
                }
            }
            Common.Button {
                id: internetcacheBtn
                picNormal: "../../img/icons/button12.png"
                picHover: "../../img/icons/button12-hover.png"
                picPressed: "../../img/icons/button12-hover.png"
                fontcolor:"#ffffff"
                fontsize: 12
                width: 100; height: 28
                text: tracepage.btn_text
                onClicked: {
                    if (tracepage.btn_flag == "history_scan") {
                        tracepage.getData("BrowserWork");
                    }
                    else if (tracepage.btn_flag == "history_work") {
                        if(tracepage.null_flag == true) {
                            internetBtnRow.state = "BrowserWorkEmpty";
                            //友情提示：      扫描内容为空，无需清理！
                            sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("The scan reslut is empty, nothing has been done!"));
                        }
                        else {
                            systemdispatcher.set_user_homedir_qt();
                            systemdispatcher.clean_history_records_qt("firefox");
                        }
                    }
                }
            }

            states: [
                State {
                    name: "BrowserWork"
                    PropertyChanges { target: internetcacheBtn; text:qsTr("Begin cleanup")}//开始清理
                    PropertyChanges { target: tracepage; btn_flag: "history_work" }
                    PropertyChanges { target: browserstatus_label; visible: true; text: qsTr("(Scan to ")+ tracepage.browserstatus_num + qsTr(" records)")}//（扫描到     条记录）
                    PropertyChanges { target: internetbackBtn; visible: true}
                    PropertyChanges { target: internetrescanBtn; visible: true}
                },
                State {
                    name: "BrowserWorkAGAIN"
                    PropertyChanges { target: internetcacheBtn; text:qsTr("Start scanning") }//开始扫描
                    PropertyChanges { target: tracepage; btn_flag: "history_scan" }
                    PropertyChanges { target: browserstatus_label; visible: false}
                    PropertyChanges { target: internetbackBtn; visible: false}
                    PropertyChanges { target: internetrescanBtn; visible: false}
                },
                State {
                    name: "BrowserWorkError"
                    PropertyChanges { target: internetcacheBtn; text:qsTr("Start scanning") }//开始扫描
                    PropertyChanges { target: tracepage; btn_flag: "history_scan" }
                    PropertyChanges { target: browserstatus_label; visible: false}
                    PropertyChanges { target: internetbackBtn; visible: false}
                    PropertyChanges { target: internetrescanBtn; visible: false}
                },
                State {
                    name: "BrowserWorkFinish"
                    PropertyChanges { target: internetcacheBtn; text:qsTr("Start scanning")}//开始扫描
                    PropertyChanges { target: tracepage; btn_flag: "history_scan" }
                    PropertyChanges { target: browserstatus_label; visible: true; text: qsTr("(Have been cleared ")+ tracepage.browserstatus_num + qsTr(" records)") }//（已清理     条记录）
                    PropertyChanges { target: internetbackBtn; visible: false}
                    PropertyChanges { target: internetrescanBtn; visible: false}

                },
                State {
                    name: "BrowserWorkEmpty"
                    PropertyChanges { target: internetcacheBtn; text:qsTr("Start scanning") }//开始扫描
                    PropertyChanges { target: tracepage; btn_flag: "history_scan" }
                    PropertyChanges { target: browserstatus_label; visible: false}
                    PropertyChanges { target: internetbackBtn; visible: false}
                    PropertyChanges { target: internetrescanBtn; visible: false}
                }
            ]
        }

        Row{
            id: chromiumBtnRow
            spacing: 20
            anchors {
                right: parent.right
                rightMargin: 20
            }//add
            Row {
                spacing: 20
                anchors.verticalCenter: parent.verticalCenter
                Common.StyleButton {
                    id: chromiumbackBtn
                    visible: false
                    anchors.verticalCenter: parent.verticalCenter
                    wordname: qsTr("Back")//返回
                    width: 40
                    height: 20
                    onClicked: {
                        chromiumBtnRow.state = "ChromiumWorkAGAIN";
                    }
                }
                Common.StyleButton {
                    id: chromiumrescanBtn
                    visible: false
                    anchors.verticalCenter: parent.verticalCenter
                    wordname: qsTr("Rescan")//重新扫描
                    width: 40
                    height: 20
                    onClicked: {
                        chromiumcacheBtn.text = qsTr("Start scanning");//开始扫描
                        tracepage.btn_flag3 = "chromium_scan";
                        chromiumbackBtn.visible = false;
                        chromiumrescanBtn.visible = false;
                        chromiumstatus_label.visible = false;
                        tracepage.getData("ChromiumWork");
                    }
                }
            }
            Common.Button {
                id: chromiumcacheBtn
                picNormal: "../../img/icons/button12.png"
                picHover: "../../img/icons/button12-hover.png"
                picPressed: "../../img/icons/button12-hover.png"
                fontcolor:"#ffffff"
                fontsize: 12
                width: 100; height: 28
                text: tracepage.btn_text
                onClicked: {
                    if (tracepage.btn_flag3 == "chromium_scan") {
                        tracepage.getData("ChromiumWork");
                    }
                    else if (tracepage.btn_flag3 == "chromium_work") {
                        if(tracepage.null_flag3 == true) {
                            internetBtnRow.state = "ChromiumWorkEmpty";
                            //友情提示：      扫描内容为空，无需清理！
                            sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("The scan reslut is empty, nothing has been done!"));
                        }
                        else {
                            systemdispatcher.set_user_homedir_qt();
                            systemdispatcher.clean_history_records_qt("chromium");
                        }
                    }
                }
            }

            states: [
                State {
                    name: "ChromiumWork"
                    PropertyChanges { target: chromiumcacheBtn; text:qsTr("Begin cleanup")}//开始清理
                    PropertyChanges { target: tracepage; btn_flag3: "chromium_work" }
                    PropertyChanges { target: chromiumstatus_label; visible: true; text: qsTr("(Scan to ")+ tracepage.chromium_num + qsTr(" records)")}//（扫描到     条记录）
                    PropertyChanges { target: chromiumbackBtn; visible: true}
                    PropertyChanges { target: chromiumrescanBtn; visible: true}
                },
                State {
                    name: "ChromiumWorkAGAIN"
                    PropertyChanges { target: chromiumcacheBtn; text:qsTr("Start scanning") }//开始扫描
                    PropertyChanges { target: tracepage; btn_flag3: "chromium_scan" }
                    PropertyChanges { target: chromiumstatus_label; visible: false}
                    PropertyChanges { target: chromiumbackBtn; visible: false}
                    PropertyChanges { target: chromiumrescanBtn; visible: false}
                },
                State {
                    name: "ChromiumWorkError"
                    PropertyChanges { target: chromiumcacheBtn; text:qsTr("Start scanning") }//开始扫描
                    PropertyChanges { target: tracepage; btn_flag3: "chromium_scan" }
                    PropertyChanges { target: chromiumstatus_label; visible: false}
                    PropertyChanges { target: chromiumbackBtn; visible: false}
                    PropertyChanges { target: chromiumrescanBtn; visible: false}
                },
                State {
                    name: "ChromiumWorkFinish"
                    PropertyChanges { target: chromiumcacheBtn; text:qsTr("Start scanning")}//开始扫描
                    PropertyChanges { target: tracepage; btn_flag3: "chromium_scan" }
                    PropertyChanges { target: chromiumstatus_label; visible: true; text: qsTr("(Have been cleared ")+ tracepage.chromium_num + qsTr(" records)") }//（已清理     条记录）
                    PropertyChanges { target: chromiumbackBtn; visible: false}
                    PropertyChanges { target: chromiumrescanBtn; visible: false}

                },
                State {
                    name: "ChromiumWorkEmpty"
                    PropertyChanges { target: chromiumcacheBtn; text:qsTr("Start scanning") }//开始扫描
                    PropertyChanges { target: tracepage; btn_flag3: "chromium_scan" }
                    PropertyChanges { target: chromiumstatus_label; visible: false}
                    PropertyChanges { target: chromiumbackBtn; visible: false}
                    PropertyChanges { target: chromiumrescanBtn; visible: false}
                }
            ]
        }

        Row{
            id: fileBtnRow
            spacing: 20
            anchors {
                right: parent.right
                rightMargin: 20
            }//add
            Row {
                spacing: 20
                anchors.verticalCenter: parent.verticalCenter
                Common.StyleButton {
                    id: filebackBtn
                    visible: false
                    anchors.verticalCenter: parent.verticalCenter
                    wordname: qsTr("Back")//返回
                    width: 40
                    height: 20
                    onClicked: {
                        fileBtnRow.state = "SystemWorkAGAIN";
                    }
                }
                Common.StyleButton {
                    id: filerescanBtn
                    visible: false
                    anchors.verticalCenter: parent.verticalCenter
                    wordname: qsTr("Rescan")//重新扫描
                    width: 40
                    height: 20
                    onClicked: {
                        syscacheBtn.text = qsTr("Start scanning");//开始扫描
                        tracepage.btn_flag2 = "system_scan";
                        filebackBtn.visible = false;
                        filerescanBtn.visible = false;
                        systemstatus_label.visible = false;
                        tracepage.getData("SystemWork");
                    }
                }
            }
            Common.Button {
                id: syscacheBtn
                picNormal: "../../img/icons/button12.png"
                picHover: "../../img/icons/button12-hover.png"
                picPressed: "../../img/icons/button12-hover.png"
                fontcolor:"#ffffff"
                fontsize: 12
                width: 100; height: 28
                text: tracepage.btn_text
                onClicked: {
                    if (tracepage.btn_flag2 == "system_scan") {
                        tracepage.getData("SystemWork");
                    }
                    else if (tracepage.btn_flag2 == "system_work") {
                        if(tracepage.null_flag2 == true) {
                            tracepage.state = "SystemWorkEmpty";
                            //友情提示：      扫描内容为空，无需清理！
                            sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("The scan reslut is empty, nothing has been done!"));
                        }
                        else {
                            systemdispatcher.set_user_homedir_qt();
                            systemdispatcher.clean_system_history_qt();
                        }
                    }
                }
            }

            states: [
                State {
                    name: "SystemWork"
                    PropertyChanges { target: syscacheBtn; text:qsTr("Begin cleanup")}//开始清理
                    PropertyChanges { target: tracepage; btn_flag2: "system_work" }
                    PropertyChanges { target: systemstatus_label; visible: true; text: qsTr("(Scan to ")+ tracepage.systemstatus_num + qsTr(" records)")}//（扫描到     条记录）
                    PropertyChanges { target: filebackBtn; visible: true}
                    PropertyChanges { target: filerescanBtn; visible: true}
                },
                State {
                    name: "SystemWorkAGAIN"
                    PropertyChanges { target: syscacheBtn; text:qsTr("Start scanning") }//开始扫描
                    PropertyChanges { target: tracepage; btn_flag2: "system_scan" }
                    PropertyChanges { target: systemstatus_label; visible: false}
                    PropertyChanges { target: filebackBtn; visible: false}
                    PropertyChanges { target: filerescanBtn; visible: false}
                },
                State {
                    name: "SystemWorkError"
                    PropertyChanges { target: syscacheBtn; text:qsTr("Start scanning") }//开始扫描
                    PropertyChanges { target: tracepage; btn_flag2: "system_scan" }
                    PropertyChanges { target: systemstatus_label; visible: false}
                    PropertyChanges { target: filebackBtn; visible: false}
                    PropertyChanges { target: filerescanBtn; visible: false}
                },
                State {
                    name: "SystemWorkFinish"
                    PropertyChanges { target: syscacheBtn; text:qsTr("Start scanning") }//开始扫描
                    PropertyChanges { target: tracepage; btn_flag2: "system_scan" }
                    PropertyChanges { target: systemstatus_label; visible: true; text: qsTr("(Have been cleared ")+ tracepage.systemstatus_num + qsTr(" records)")}//（已清理     条记录）
                    PropertyChanges { target: filebackBtn; visible: false}
                    PropertyChanges { target: filerescanBtn; visible: false}
                },
                State {
                    name: "SystemWorkEmpty"
                    PropertyChanges { target: syscacheBtn; text:qsTr("Start scanning") }//开始扫描
                    PropertyChanges { target: tracepage; btn_flag2: "system_scan" }
                    PropertyChanges { target: systemstatus_label; visible: false}
                    PropertyChanges { target: filebackBtn; visible: false}
                    PropertyChanges { target: filerescanBtn; visible: false}
                }
            ]
        }
    }
}
