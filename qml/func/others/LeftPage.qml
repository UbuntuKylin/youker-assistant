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
import "../common" as Common

Rectangle {
    id: leftbar
    width: 600; height: 435
    property int num: 3//子checkbox的个数
    property int check_num: num
    property string flag: "onekeyscan" //onekeyscan:scan      onekey:clean
    property string garbage
    property string trace
    property string cookies
    property string path: "../../img/en/"
    property bool garbageFlag: true
    property bool traceFlag: true
    property bool cookiesFlag: true

    Component.onCompleted: {
        if(sessiondispatcher.get_locale_version() == "zh_CN") {
            leftbar.path = "../../img/zh_CN/";
        }
        else {
            leftbar.path = "../../img/en/";
        }
        firstonekey.showImage = leftbar.path + "quickscan.png";
    }

    Connections
    {
        target: sessiondispatcher
        onIsScanning: {//扫描过程中收到的信号
            showLabel.visible = true;
            showText.text = msg;
        }
        onFinishScanWork: {
            if(msg == "onekey") {//扫描完成
                staticImage.visible = true;
                dynamicImage.visible = false;
                leftbar.flag = "onekey";
                firstonekey.showImage = leftbar.path + "quickclean.png";
//                firstonekey.text = qsTr("Quick cleanup");//一键清理
                //扫描完成后根据子checkbox的勾选情况置状态
                if(garbageCheck.checked) {
                    cachestatus.visible = true;
                    cachestatus.state = "GarbageNO";
                }
                else {
                    cachestatus.visible = false;
                }
                if(historyCheck.checked) {
                    historystatus.visible = true;
                    historystatus.state = "HistoryNo";
                }
                else {
                    historystatus.visible = false;
                }
                if(cookiesCheck.checked) {
                    cookiestatus.visible = true;
                    cookiestatus.state = "CookiesNO";
                }
                else {
                    cookiestatus.visible = false;
                }

                showLabel.visible = false;
                showText.text = "";
            }
        }

        onTellScanResultToQML: {
            if(flag == "h") {
                leftbar.trace = msg;
            }
            else if(flag == "k") {
                leftbar.cookies = msg;
            }
            else if(flag == "c") {
                leftbar.garbage = msg;
            }
        }
    }

    Connections
    {
        target: systemdispatcher
        onFinishCleanWorkMain: {//收到清理后的状态
            if (msg == "") {//在弹出输入密码验证时，点击了取消按钮
                //do nothing
            }
            else if (msg == "c") {
                cachestatus.state = "GarbageOK";
                firstonekey.showImage = leftbar.path + "cleaningup.png";
//                firstonekey.text = qsTr("Cleaning up...");//正在清理...
            }
            else if (msg == "h") {
                historystatus.state = "HistoryOK";
                firstonekey.showImage = leftbar.path + "cleaningup.png";
//                firstonekey.text = qsTr("Cleaning up...");//正在清理...
            }
            else if (msg == "k") {
                cookiestatus.state = "CookiesOK";
                firstonekey.showImage = leftbar.path + "cleaningup.png";
//                firstonekey.text = qsTr("Cleaning up...");//正在清理...
            }
            else if (msg == "o") {
                //清理完毕后显示清理总数
                if(leftbar.cookiesFlag) {
                    cookiedes.visible = true;
                    cookiedes.text = qsTr("(totally cleared") + leftbar.cookies + qsTr("Cookies)");//（共清理掉    条Cookies）
                }
                if(leftbar.garbageFlag) {
                    cachedes.visible = true;
                    cachedes.text = qsTr("(totally cleared") + leftbar.garbage + qsTr("garbage)");//（共清理掉      垃圾）
                }
                if(leftbar.traceFlag) {
                    historydes.visible = true;
                    historydes.text = qsTr("(totally cleared") + leftbar.trace + qsTr("historical records)");//（共清理掉     条历史记录）
                }
                //显示清理总数后把与之相关的一些标记和变量恢复默认值
//                leftbar.cookiesFlag = false;
//                leftbar.garbageFlag = false;
//                leftbar.traceFlag = false;
                leftbar.cookies = "";
                leftbar.garbage = "";
                leftbar.trace = "";

                showText.text = "";
                toolkits.alertMSG(qsTr("Cleared!"), mainwindow.pos.x, mainwindow.pos.y);//一键清理完毕！
                leftbar.flag = "onekeyscan";
                firstonekey.showImage = leftbar.path + "quickscan.png";
//                firstonekey.text = qsTr("Quick scan");//一键扫描
            }
            staticImage.visible = true;
            dynamicImage.visible = false;
        }

        onFinishCleanWorkMainError: {
            if (msg == "ce") {
                cachestatus.state = "GarbageException";
                if (cachedes.visible == true) {
                    cachedes.visible = false;
                }
            }
            else if (msg == "he") {
                historystatus.state = "HistoryException";
                if (historydes.visible == true) {
                    historydes.visible = false;
                }
            }
            else if (msg == "ke") {
                cookiestatus.state = "CookiesException";
                if (cookiedes.visible == true) {
                    cookiedes.visible = false;
                }
            }
        }
//        onFinishCleanDataMain: {//收到清理的内容
//            if (type == "c") {
//                cachedes.visible = true;
//                cachedes.text = qsTr("(totally cleared") + msg + qsTr("garbage)");//（共清理掉      垃圾）
//            }
//            else if (type == "h") {
//                historydes.visible = true;
//                historydes.text = qsTr("(totally cleared") + msg + qsTr("historical records)");//（共清理掉     条历史记录）
//            }
//            else if (type == "k") {
//                cookiedes.visible = true;
//                cookiedes.text = qsTr("(totally cleared") + msg + qsTr("Cookies)");//（共清理掉    条Cookies）
//            }
//        }
        onQuickCleanProcess: {
            if(type == "firefoxhistory") {
                if(status == "start") {
                    showText.text = qsTr("Cleaning up history trace of Firefox...");//正在清理Firefox的历史痕迹...
                }
                else if(status == "end") {
                    showText.text = qsTr("Firefox history trace had been cleared!");//Firefox的历史痕迹已清理完毕！
                }
            }
            else if(type == "chromiumhistory") {
                if(status == "start") {
                    showText.text = qsTr("Cleaning up history trace of Chromium...");//正在清理Chromium的历史痕迹...
                }
                else if(status == "end") {
                    showText.text = qsTr("Chromium history trace had been cleared!");//Chromium的历史痕迹已清理完毕！
                }
            }
            else if(type == "firefoxcookies") {
                if(status == "start") {
                    showText.text = qsTr("Cleaning up Cookies of Firefox...");//正在清理Firefox的Cookies...
                }
                else if(status == "end") {
                    showText.text = qsTr("Firefox Cookies had been cleared!");//Firefox的Cookies已清理完毕！
                }
            }
            else if(type == "chromiumcookies") {
                if(status == "start") {
                    showText.text = qsTr("Cleaning up Cookies of Chromium...");//正在清理Chromium的Cookies...
                }
                else if(status == "end") {
                    showText.text = qsTr("Chromium Cookies had been cleared!");//Chromium的Cookies已清理完毕！
                }
            }
            else if(type == "apt") {
                if(status == "end") {
                    showText.text = qsTr("Apt cache had been cleared!");//Apt缓存已清理完毕！
                }
                else {
                    showText.text = qsTr("Cleaning up Apt cache: ") + status;//正在清理Apt缓存：
                }
            }
            else if(type == "software_center") {
                if(status == "end") {
                    showText.text = qsTr("Software Center cache had been cleared!");//软件中心缓存已清理完毕！
                }
                else {
                    showText.text = qsTr("Cleaning up Software Center cache: ") + status;//正在清理软件中心缓存：
                }
            }
        }
    }

    //子checkbox勾选的个数变化时
    onCheck_numChanged: {
        if(check_num == 0) {//子checkbox勾选的个数为0，主checkbox状态置为"false"
            mainCheck.checked = "false";
        }
        else if(check_num == leftbar.num) {//子checkbox全部被勾选时，主checkbox状态置为"true"
            mainCheck.checked = "true";
        }
        else {//存在子checkbox被勾选，但没有全部被勾选时，主checkbox状态置为"mid"
            mainCheck.checked = "mid";
        }
    }
    //背景
    Image {
        source: "../../img/skin/bg-left.png"
        anchors.fill: parent
    }

    Row {
        id: myrow
        spacing: 10
        anchors { top: parent.top; topMargin: 35; left: parent.left; leftMargin: 30 }
        Image {//静态图片
            id: staticImage//staticImage
            visible: true
            source: "../../img/toolWidget/clear-logo.gif"
            width: 120
            height: 118
            Behavior on rotation { NumberAnimation { duration: 200 } }
        }
        AnimatedImage {//动态图片
            id: dynamicImage//dynamicImage
            visible: false
            width: 120
            height: 118
            source: "../../img/toolWidget/clear-logo.gif"
        }

        Column {
            spacing: 17
            id: mycolumn
            Text {
                id: text0
                width: leftbar.width-180
                text: qsTr("Quick clean up system junks, saving disk space and improving the system efficiency !")//一键清理系统垃圾，帮您节省磁盘空间，让系统运行更加有效率！
                font.bold: true
                wrapMode: Text.WordWrap
                font.pixelSize: 14
                color: "#383838"
            }
            Text {
                id: text1
                width: leftbar.width-180
                text: qsTr("To help you quick clean up the Cookies, garbage, traces and plug-ins in your system")//一键帮您清理系统中的 Cookies、垃圾、痕迹和插件！
                wrapMode: Text.WordWrap
                font.pixelSize: 12
                color: "#7a7a7a"
            }
            Common.KButton {
                id: firstonekey
                kflag: "quickscan"
                showImage: ""   //"../../img/zh_CN/quickscan.png"
                anchors {
                    left: parent.left; leftMargin: 100
                }
                width: 185
                height: 45
                onClicked: {
                    if(!(garbageCheck.checked || historyCheck.checked || cookiesCheck.checked)) {//没有有一个子项勾选了
                        sessiondispatcher.showWarningDialog("友情提示：","对不起，您没有选中清理项，请确认！", mainwindow.pos.x, mainwindow.pos.y);
                    }
                    else {
                        if (leftbar.flag == "onekeyscan") {//一键扫描
                            if (cachestatus.visible == true)
                                cachestatus.visible = false;
                            if (historystatus.visible == true)
                                historystatus.visible = false;
                            if (cookiestatus.visible == true)
                                cookiestatus.visible = false;
                            if (cachedes.visible == true)
                                cachedes.visible = false;
                            if (historydes.visible == true)
                                historydes.visible = false;
                            if (cookiedes.visible == true)
                                cookiedes.visible = false;

                            staticImage.visible = false;
                            dynamicImage.visible = true;
                            showLabel.visible = false;
                            showText.text = "";

                            if(garbageCheck.checked) {
                                leftbar.garbageFlag = true;
                            }
                            else {
                                leftbar.garbageFlag = false;
                            }
                            if(historyCheck.checked) {
                                leftbar.traceFlag = true;
                            }
                            else {
                                leftbar.traceFlag = false;
                            }
                            if(cookiesCheck.checked) {
                                leftbar.cookiesFlag = true;
                            }
                            else {
                                leftbar.cookiesFlag = false;
                            }
                            sessiondispatcher.onekey_scan_function_qt(systemdispatcher.get_onekey_args());
                        }
                        else if (leftbar.flag == "onekey") {//一键清理
                            if(garbageCheck.checked) {
                                if(!leftbar.garbageFlag) {
                                    leftbar.garbageFlag = false;
                                }
                            }
                            else {
                                leftbar.garbageFlag = false;
                            }
                            if(historyCheck.checked) {
                                if(!leftbar.traceFlag) {
                                    leftbar.traceFlag = false;
                                }
                            }
                            else {
                                leftbar.traceFlag = false;
                            }
                            if(cookiesCheck.checked) {
                                if(!leftbar.cookiesFlag) {
                                    leftbar.cookiesFlag = false;
                                }
                            }
                            else {
                                leftbar.cookiesFlag = false;
                            }

                            staticImage.visible = false;
                            dynamicImage.visible = true;
                            showLabel.visible = false;
                            showText.text = "";
                            systemdispatcher.set_user_homedir_qt();
                            systemdispatcher.clean_by_main_one_key_qt(leftbar.garbageFlag, leftbar.traceFlag, leftbar.cookiesFlag/*systemdispatcher.get_onekey_args()*/);
                        }
                    }
                }
            }//Button



        }
    }//Row

    Column {
        id: scanColumn
        anchors { top: parent.top; topMargin: 150; left: parent.left; leftMargin: 30 }
        spacing: 20
        Row {
            spacing: 10
            Text {
                id: showLabel
                width: 50
                visible: false
                text: qsTr("Scan to:  ")//扫描到：
            }
            Text {
                id: showText
                width: leftbar.width - 50 - 20 * 2 - 20
                height: 30
                text: ""
                wrapMode: Text.WrapAnywhere//Text.WordWrap
                color: "green"
            }
        }
        Row{
            spacing: 10
            Common.Label {
                id: itemtip
                text: qsTr("Quick Cleanup")//一键清理项目
                font.bold: true
                font.pixelSize: 14
                color: "#008000"
            }
            Common.MainCheckBox {
                id:mainCheck
                checked:"true"//默认情况将所有选项都勾选上
                //主checkbox的值改变时，当改变为true，即子checkbox全部勾选上;当改变为false，即子checkbox全部不被勾选
                onCheckedboolChanged: {
                    garbageCheck.checked = mainCheck.checkedbool;
                    historyCheck.checked = mainCheck.checkedbool;
                    cookiesCheck.checked = mainCheck.checkedbool;
                }
            }
        }
    }

    //列表
    Column {
        anchors.top: parent.top
        anchors.topMargin: 255
        anchors.left: parent.left
        anchors.leftMargin: 55
        spacing:30
        //-------------garbage--------------
        Item {
            width: parent.width
            height:45 //65
            Item {
                Behavior on scale { NumberAnimation { easing.type: Easing.InOutQuad} }
                //checkbox, picture and words
                Row {
                    spacing: 15
                    anchors.verticalCenter: parent.verticalCenter
                    Common.CheckBox {
                        id: garbageCheck
                        checked:true
                        anchors.verticalCenter: parent.verticalCenter
                        onCheckedChanged: {
                            if(garbageCheck.checked) {
                                leftbar.check_num = leftbar.check_num + 1;
                            }
                            else {
                                leftbar.check_num = leftbar.check_num - 1;
                            }
                            if (garbageCheck.checked) {
                                var rubbishlist = systemdispatcher.get_onekey_args();
                                var word_flag = "false";
                                for (var i=0; i<rubbishlist.length; i++) {
                                    if (rubbishlist[i] == "cache") {
                                        word_flag = "true";
                                        break;
                                    }
                                }
                                if (word_flag == "false") {
                                    systemdispatcher.set_onekey_args("cache");
                                }
                            }
                            else if (!garbageCheck.checked) {
                                systemdispatcher.del_onekey_args("cache");
                            }
                        }
                    }
                    Image {
                        width: 38; height: 38
                        source:"../../img/toolWidget/brush.png"
                    }
                    Column {
                        spacing: 5
                        Row {
                            spacing: 20
                            Text {
                                text: qsTr("Cleanup Garbage")//清理系统中的垃圾
                                font.bold: true
                                font.pixelSize: 14
                                color: "#383838"
                            }
                            Text {
                                id: cachedes
                                color: "green"
                                text: ""
                                visible: false
                            }
                        }
                        Text {
                            text: qsTr("Clean up system junk files, free disk space")//清理系统中的垃圾文件，释放磁盘空间
                            font.pixelSize: 12
                            color: "#7a7a7a"
                        }
                    }
                }
                Common.StatusImage {
                    id: cachestatus
                    visible: false
                    iconName: "yellow.png"
                    text: qsTr("Unfinished")//未完成
                    anchors {
                        left: parent.left; leftMargin: 450
                    }
                    states: [
                        State {
                            name: "GarbageOK"
                            PropertyChanges { target: cachestatus; iconName: "green.png"; text: qsTr("Completed")}//已完成
                        },
                        State {
                            name: "GarbageException"
                            PropertyChanges { target: cachestatus; iconName: "red.png"; text: qsTr("Exception occurred")}//出现异常
                        },
                        State {
                            name: "GarbageNO"
                            PropertyChanges { target: cachestatus; iconName: "yellow.png"; text: qsTr("Unfinished")}//未完成
                        }
                    ]
                }
//                Rectangle {  //分割条
//                    width: parent.width; height: 1
//                    anchors { top: lineLayout.bottom; topMargin: 5}
//                    color: "red"
//                }
            }
        }
        //---------------history-------------
        Item {
            width: parent.width
            height: 45//65
            Item {
                Behavior on scale { NumberAnimation { easing.type: Easing.InOutQuad} }
                //checkbox, picture and words
                Row {
                    spacing: 15
                    anchors.verticalCenter: parent.verticalCenter
                    Common.CheckBox {
                        id: historyCheck
                        checked:true    //将所有选项都check
                        anchors.verticalCenter: parent.verticalCenter
                        onCheckedChanged: {
                            if(historyCheck.checked) {
                                leftbar.check_num = leftbar.check_num+1;
                            }
                            else {
                                leftbar.check_num = leftbar.check_num-1;
                            }
                            if (historyCheck.checked) {
                                var historylist = systemdispatcher.get_onekey_args();
                                var word_flag1 = "false";
                                for (var j=0; j<historylist.length; j++) {
                                    if (historylist[j] == "history") {
                                        word_flag1 = "true";
                                        break;
                                    }
                                }
                                if (word_flag1 == "false") {
                                    systemdispatcher.set_onekey_args("history");
                                }
                            }
                            else if (!historyCheck.checked) {
                                systemdispatcher.del_onekey_args("history");
                            }
                        }
                    }
                    Image {
                        width: 38; height: 38
                        source: "../../img/toolWidget/history.png"
                    }
                    Column {
                        spacing: 5
                        Row {
                            spacing: 20
                            Text {
                                text: qsTr("Delete History")//清理历史记录
                                font.bold: true
                                font.pixelSize: 14
                                color: "#383838"
                            }
                            Text {
                                id: historydes
                                color: "green"
                                text: ""
                                visible: false
                            }
                        }
                        Text {
                            text: qsTr("Clean up the historical records, to protect your privacy")//清理上网时留下的历史记录，保护您的个人隐私
                            font.pixelSize: 12
                            color: "#7a7a7a"
                        }
                    }
                }
                Common.StatusImage {
                    id: historystatus
                    visible: false
                    iconName: "yellow.png"
                    text: qsTr("Unfinished")//未完成
                    anchors {
                        left: parent.left; leftMargin: 450
                    }
                    states: [
                        State {
                            name: "HistoryOK"
                            PropertyChanges { target: historystatus; iconName: "green.png"; text: qsTr("Completed")}//已完成
                        },

                        State {
                            name: "HistoryException"
                            PropertyChanges { target: historystatus; iconName: "red.png"; text: qsTr("Exception occurred")}//出现异常
                        },
                        State {
                            name: "HistoryNo"
                            PropertyChanges { target: historystatus; iconName: "yellow.png"; text: qsTr("Unfinished")}//未完成
                        }
                    ]
                }
            }
        }
        //---------------cookies-------------
        Item {
            width: parent.width
            height: 45//65
            Item {
                Behavior on scale { NumberAnimation { easing.type: Easing.InOutQuad} }
                //checkbox, picture and words
                Row {
                    spacing: 15
                    anchors.verticalCenter: parent.verticalCenter
                    Common.CheckBox {
                        id: cookiesCheck
                        checked:true    //将所有选项都check
                        anchors.verticalCenter: parent.verticalCenter
                        onCheckedChanged: {
                            if(cookiesCheck.checked) {
                                leftbar.check_num = leftbar.check_num+1;
                            }
                            else {
                                leftbar.check_num = leftbar.check_num-1;
                            }
                            if (cookiesCheck.checked) {
                                var cookieslist = systemdispatcher.get_onekey_args();
                                var word_flag2 = "false";
                                for (var k=0; k<cookieslist.length; k++) {
                                    if (cookieslist[k] == "cookies") {
                                        word_flag2 = "true";
                                        break;
                                    }
                                }
                                if (word_flag2 == "false") {
                                    systemdispatcher.set_onekey_args("cookies");
                                }
                            }
                            else if (!cookiesCheck.checked) {
                                systemdispatcher.del_onekey_args("cookies");
                            }
                        }
                    }
                    Image {
                        width: 38; height: 38
                        source: "../../img/toolWidget/cookies.png"//picturename
                    }
                    Column {
                        spacing: 5
                        Row {
                            spacing: 20
                            Text {
                                text: qsTr("Cleanup Cookies")//清理 Cookies
                                font.bold: true
                                font.pixelSize: 14
                                color: "#383838"
                            }
                            Text {
                                id: cookiedes
                                color: "green"
                                text: ""
                                visible: false
                            }
                        }
                        Text {
                            text: qsTr("Clean up the Cookies, including surfing and shopping records")//清理系统中的 Cookies，包含上网、购物、游戏等记录
                            font.pixelSize: 12
                            color: "#7a7a7a"
                        }
                    }
                }
                Common.StatusImage {
                    id: cookiestatus
                    visible: false
                    iconName: "yellow.png"
                    text: qsTr("Unfinished")//未完成
                    anchors {
                        left: parent.left; leftMargin: 450
                    }
                    states: [
                        State {
                            name: "CookiesOK"
                            PropertyChanges { target: cookiestatus; iconName: "green.png"; text: qsTr("Completed")}//已完成
                        },

                        State {
                            name: "CookiesException"
                            PropertyChanges { target: cookiestatus; iconName: "red.png"; text: qsTr("Exception occurred")}//出现异常
                        },
                        State {
                            name: "CookiesNO"
                            PropertyChanges { target: cookiestatus; iconName: "yellow.png"; text: qsTr("Unfinished")}//未完成
                        }
                    ]
                }
            }
        }
    }//Column
}
