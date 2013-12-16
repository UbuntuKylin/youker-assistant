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
import "common" as Common

Item {
    id:root
    width: parent.width
    height: 435
    property string title: qsTr("Clean the login information and protect personal privacy")//清理浏览器登录信息,保护个人隐私
    property string description: qsTr("Clean up the login information, support Firefox and Chromium browser")//清理上网时留下的登录信息,支持Firefox和Chromium浏览器

    property string btnFlag: "apt_scan"//扫描或者清理的标记：apt_scan/apt_work
    property bool resultFlag: false//判断扫描后的实际内容是否为空，为空时为false，有内容时为true
    property bool softresultFlag: false//判断扫描后的实际内容是否为空，为空时为false，有内容时为true
    property int aptsubNum: 0//扫描后得到的apt的项目总数
//    property int aptNum: aptsubNum//001
    property int aptNum
    property int softsubNum: 0//扫描后得到的apt的项目总数
    property int softNum: softsubNum//001
    property bool splitFlag: true//传递给ClearDelegate.qml,为true时切割字符串，为false时不切割字符串
    property bool flag: false//记录是清理后重新获取数据（true），还是点击开始扫描后获取数据（false）

    property int spaceValue: 20
    property int firefox_arrow_show: 0//传递给ClearDelegate.qml是否显示伸缩图标，为1时显示，为0时隐藏
    property int chromium_arrow_show: 0//传递给ClearDelegate.qml是否显示伸缩图标，为1时显示，为0时隐藏
    property bool firefox_expanded: false
    property bool chromium_expanded: false

    property bool maincheck1: true
    property bool maincheck2: true
    property bool showNum1: false
    property bool showNum2: false
    ListModel { id: mainModel }
    ListModel { id: subModel }
    ListModel { id: softmainModel }
    ListModel { id: softsubModel }
    property string firefox_btn_text: qsTr("Start scanning")//开始扫描
    property string chromium_btn_text: qsTr("Start scanning")//开始扫描
    property bool firefox_reset: false//firefox重置按钮默认隐藏
    property bool chromium_reset: false//chromium重置按钮默认隐藏
    property string firefox_btn_flag: "cookies_scan"
    property string chromium_btn_flag: "cookies_scanc"

    Component.onCompleted: {
        mainModel.append({
                         "itemTitle": qsTr("Clean Firefox's Cookies"),
                         "picture": "../img/toolWidget/cookies.png",
                         "detailstr": qsTr("Clean up automatically saved logon information by Firefox browser(Cookies)")})
        softmainModel.append({
                         "itemTitle": qsTr("Clean Chromium's Cookies"),
                         "picture": "../img/toolWidget/chromium.png",
                         "detailstr": qsTr("Clean up automatically saved logon information by Chromium browser(Cookies)")})
    }

    //获取firefox的cookies
    function getDataOfFirefox() {
        var cookies_data = sessiondispatcher.cookies_scan_function_qt("f");
        if(cookies_data == "None") {//没有安装Firefox
            //友情提示
            sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("No Firefox browser installed!"), mainwindow.pos.x, mainwindow.pos.y);
        }
        else {
            if (cookies_data.length == 0) {
                root.resultFlag = false;//扫描内容不存在
            }
            else {
                root.aptsubNum = cookies_data.length;//001
                systemdispatcher.clear_cookies_args();
                subModel.clear();
                var num = 0;
                for (var i=0; i< cookies_data.length; i++) {
                //sina.com.cn<2_2>10
                    var splitlist = cookies_data[i].split("<2_2>");
                    if (splitlist[0] == "") {
                        num++;
                    }
                    else {
                        subModel.append({"itemTitle": splitlist[0], "desc": "","number": splitlist[1]});
                        systemdispatcher.set_cookies_args(splitlist[0]);
                    }
                }
                root.aptsubNum -= num;//001
                root.aptNum = root.aptsubNum;//001
                console.log("apt num:");
                console.log(root.aptNum);
                if(root.aptNum != 0) {
                    root.resultFlag = true;//扫描的实际有效内容存在
                    mainModel.clear();
                    mainModel.append({
                                     "itemTitle": qsTr("Clean Firefox's Cookies"),
                                     "picture": "../img/toolWidget/cookies.png",
                                     "detailstr": qsTr("Clean up automatically saved logon information by Firefox browser(Cookies)")})
                }
                else {
                    root.resultFlag = false;//扫描的实际有效内容不存在
                }
            }
            if(root.resultFlag == false) {
                root.firefox_expanded = false;//伸缩箭头不扩展
                root.firefox_arrow_show = 0;//伸缩箭头不显示

                //此时若是通过一个一个单项清除导致的清空全部完成，则按钮状态改变、显示文字改变、重置按钮显示
                root.firefox_btn_flag = "cookies_scan";//1206
                root.firefox_btn_text = qsTr("Start scanning")//开始扫描//1206
                root.firefox_reset = false;//1206
            }
            else if(root.resultFlag == true) {
                root.firefox_expanded = true;//伸缩箭头扩展
                root.firefox_arrow_show = 1;//伸缩箭头显示

                //当真正扫描到内容时：按钮状态改变、显示文字改变、重置按钮显示
                root.firefox_btn_flag = "cookies_work";//1206
                root.firefox_btn_text = qsTr("All clean");//全部清理//1206
                root.firefox_reset = true;//1206
            }
        }
    }

    //获取chromium的cookies
    function getDataOfChromium() {
        var cookies_data = sessiondispatcher.cookies_scan_function_qt("c");
        if(cookies_data == "None") {//没有安装Chromium
            //友情提示
            sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("No Chromium browser installed!"), mainwindow.pos.x, mainwindow.pos.y);
        }
        else {
            root.softsubNum = cookies_data.length;//001
            systemdispatcher.clear_cookies_args();
            softsubModel.clear();
            var num = 0;
            for (var i=0; i< cookies_data.length; i++) {
            //  /home/kobe/.cache/software-center/piston-helper<2_2>3026257
                var splitlist = cookies_data[i].split("<2_2>");
                if (splitlist[0] == "") {
                    num++;
                }
                else {
                    softsubModel.append({"itemTitle": splitlist[0], "desc": "","number": splitlist[1]});
                    systemdispatcher.set_cookies_args(splitlist[0]);
                }
            }
            root.softsubNum -= num;//001
            root.softNum = root.softsubNum;//001
            console.log("soft num:");
            console.log(root.softNum);
            if(root.softNum != 0) {
                root.softresultFlag = true;//扫描的实际有效内容存在
                softmainModel.clear();
                softmainModel.append({
                                 "itemTitle": qsTr("Clean Chromium's Cookies"),
                                 "picture": "../img/toolWidget/chromium.png",
                                 "detailstr": qsTr("Clean up automatically saved logon information by Chromium browser(Cookies)")})
                }
            else {
                root.softresultFlag = false;//扫描的实际有效内容不存在
            }
        }
        if(root.softresultFlag == false) {
            root.chromium_expanded = false;//伸缩箭头不扩展
            root.chromium_arrow_show = 0;//伸缩箭头不显示

            //此时若是通过一个一个单项清除导致的清空全部完成，则按钮状态改变、显示文字改变、重置按钮显示
            root.chromium_btn_flag = "cookies_scanc";//1206
            root.chromium_btn_text = qsTr("Start scanning")//开始扫描//1206
            root.chromium_reset = false;//1206
        }
        else if(root.softresultFlag == true) {
            root.chromium_expanded = true;//伸缩箭头扩展
            root.chromium_arrow_show = 1;//伸缩箭头显示

            //当真正扫描到内容时：按钮状态改变、显示文字改变、重置按钮显示
            root.chromium_btn_flag = "cookies_workc";//1206
            root.chromium_btn_text = qsTr("All clean");//全部清理//1206
            root.chromium_reset = true;//1206
        }
    }

    function getData() {
        root.aptNum = 0;
        root.softNum =0;
        root.getDataOfFirefox();
//        root.getDataOfChromium();
        if(root.resultFlag == false && root.softresultFlag == false) {
            root.state = "AptWorkEmpty";
            if(root.flag == false) {//点击扫描时的获取数据，此时显示该对话框
                //友情提示：      扫描内容为空，不再执行清理！
                sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Scanning content is empty, no longer to perform cleanup!"), mainwindow.pos.x, mainwindow.pos.y);
            }
            else {//清理apt后的重新获取数据，此时不需要显示对话框
                root.flag = false;
            }
        }
        else {
            if(root.flag == false) {//点击扫描时的获取数据，此时显示该对话框
                toolkits.alertMSG(qsTr("Scan completed!"), mainwindow.pos.x, mainwindow.pos.y);//扫描完成！
            }
            else {//清理software后的重新获取数据，此时不需要显示对话框
                root.flag = false;
            }
            root.state = "AptWork";
            actionBtn.text = qsTr("Start cleaning");//开始清理
            root.btnFlag = "apt_work";
            backBtn.visible = true;
            rescanBtn.visible = true;
        }
        scrollItem.height = (root.aptNum + 1) * 40 + (root.softNum + 1) * 40 + root.spaceValue*2;
    }

    Connections
    {
        target: systemdispatcher
        onFinishCleanWorkError: {//清理出错时收到的信号
            if (btnFlag == "apt_work") {
                if (msg == "cache") {
                    root.state = "AptWorkError";
                    toolkits.alertMSG(qsTr("Exception occurred!"), mainwindow.pos.x, mainwindow.pos.y);//清理出现异常！
                }
            }
        }
        onFinishCleanWork: {//清理成功时收到的信号
            if (root.btnFlag == "apt_work") {
                if (msg == "") {
                    toolkits.alertMSG(qsTr("Cleanup interrupted!"), mainwindow.pos.x, mainwindow.pos.y);//清理中断了！
                }
                else if (msg == "cache") {
                    console.log("12--------");
                    root.state = "AptWorkFinish";
                    toolkits.alertMSG(qsTr("Cleaned"), mainwindow.pos.x, mainwindow.pos.y);//清理完毕！



//                    systemdispatcher.clear_cache_args();
//                    subModel.clear();//内容清空
//                    softsubModel.clear();//内容清空
//                    root.aptNum = 0;//隐藏滑动条
//                    root.softNum = 0;//隐藏滑动条

                    //清理完毕后重新获取数据
                    root.flag = true;
                    if(root.maincheck1 && root.maincheck2) {//software-center
                        console.log("123--------");
                        mainModel.clear();
                        softmainModel.clear();
                        mainModel.append({
                                         "itemTitle": qsTr("Clean Firefox's Cookies"),
                                         "picture": "../img/toolWidget/cookies.png",
                                         "detailstr": qsTr("Clean up automatically saved logon information by Firefox browser(Cookies)")})
                        softmainModel.append({
                                         "itemTitle": qsTr("Clean Chromium's Cookies"),
                                         "picture": "../img/toolWidget/chromium.png",
                                         "detailstr": qsTr("Clean up automatically saved logon information by Chromium browser(Cookies)")})
                        systemdispatcher.clear_cache_args();
                        subModel.clear();//内容清空
                        softsubModel.clear();//内容清空
                        root.aptNum = 0;//隐藏滑动条
                        root.softNum = 0;//隐藏滑动条
                        sessiondispatcher.cache_scan_function_qt(sessiondispatcher.get_cache_arglist());
                    }
                    else {
                        if(root.maincheck1) {
                            console.log("1234--------");
                            mainModel.clear();
                            mainModel.append({
                                             "itemTitle": qsTr("Clean Firefox's Cookies"),
                                             "picture": "../img/toolWidget/cookies.png",
                                             "detailstr": qsTr("Clean up automatically saved logon information by Firefox browser(Cookies)")})

                            systemdispatcher.clear_cache_args();
                            subModel.clear();//内容清空
                            softsubModel.clear();//内容清空
                            root.aptNum = 0;//隐藏滑动条
                            root.softNum = 0;//隐藏滑动条
                            sessiondispatcher.cache_scan_function_qt("apt");
                        }
                        else if(root.maincheck2) {
                            console.log("12345--------");
                            softmainModel.clear();
                            softmainModel.append({
                                             "itemTitle": qsTr("Clean Chromium's Cookies"),
                                             "picture": "../img/toolWidget/chromium.png",
                                             "detailstr": qsTr("Clean up automatically saved logon information by Chromium browser(Cookies)")})

                            systemdispatcher.clear_cache_args();
                            subModel.clear();//内容清空
                            softsubModel.clear();//内容清空
                            root.aptNum = 0;//隐藏滑动条
                            root.softNum = 0;//隐藏滑动条
                            sessiondispatcher.cache_scan_function_qt("software-center");
                        }
                    }
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
            id: apt_refreshArrow
            source: "../img/toolWidget/apt.png"
            Behavior on rotation { NumberAnimation { duration: 200 } }
        }
        Column {
            anchors.verticalCenter: parent.verticalCenter
            spacing: 10
            Text {
                width: 500
                text: root.title
                wrapMode: Text.WordWrap
                font.bold: true
                font.pixelSize: 14
                color: "#383838"
            }
            Text {
                width: 500
                text: root.description
                wrapMode: Text.WordWrap
                font.pixelSize: 12
                color: "#7a7a7a"
            }
        }
    }

    Row{
        anchors { top: parent.top; topMargin: 20;right: parent.right ; rightMargin: 40 }
        spacing: 20
        Row {
            spacing: 20
            anchors.verticalCenter: parent.verticalCenter
            Common.StyleButton {
                id: backBtn
                visible: false
                anchors.verticalCenter: parent.verticalCenter
                wordname: qsTr("Go back")//返回
                width: 40
                height: 20
                onClicked: {
                    if(root.maincheck1 == false) {
                        root.maincheck1 = true;
                    }
                    if(root.maincheck2 == false) {
                        root.maincheck2 = true;
                    }
                    systemdispatcher.clear_cache_args();
                    root.showNum1 = false;
                    root.showNum2 = false;
                    mainModel.clear();
                    softmainModel.clear();
                    mainModel.append({
                                     "itemTitle": qsTr("Clean Firefox's Cookies"),
                                     "picture": "../img/toolWidget/cookies.png",
                                     "detailstr": qsTr("Clean up automatically saved logon information by Firefox browser(Cookies)")})
                    softmainModel.append({
                                     "itemTitle": qsTr("Clean Chromium's Cookies"),
                                     "picture": "../img/toolWidget/chromium.png",
                                     "detailstr": qsTr("Clean up automatically saved logon information by Chromium browser(Cookies)")})

                    subModel.clear();//内容清空
                    root.aptNum = 0;//隐藏滑动条
                    root.firefox_arrow_show = 0;//伸缩图标隐藏
                    softsubModel.clear();//内容清空
                    root.softNum = 0;//隐藏滑动条
                    root.chromium_arrow_show = 0;//伸缩图标隐藏
                    scrollItem.height = 2 * 40 + root.spaceValue*2;
                    root.state = "AptWorkAGAIN";//按钮的状态恢复初始值
                }
            }
        }
        Common.Button {
            id: actionBtn
            width: 120
            height: 39
            hoverimage: "green1.png"
            text: qsTr("Start scanning")//开始扫描
            fontsize: 15
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                if (root.btnFlag == "apt_scan") {//扫描
                    root.flag = false;
                    root.getData();
                    if(root.maincheck1 && root.maincheck2) {//software-center
                        sessiondispatcher.cache_scan_function_qt(sessiondispatcher.get_cache_arglist());
                    }
                    else {
                        if(root.maincheck1) {
                            sessiondispatcher.cache_scan_function_qt("apt");
                        }
                        else if(root.maincheck2) {
                            sessiondispatcher.cache_scan_function_qt("software-center");
                        }
                    }
                }
                else if (root.btnFlag == "apt_work") {//清理
                    if(root.resultFlag || root.softresultFlag) {//扫描得到的实际内容存在时
                        console.log(systemdispatcher.get_cache_args());
                        systemdispatcher.clean_file_cruft_qt(systemdispatcher.get_cache_args(), "cache");
                    }
                    else {//扫描得到的实际内容不存在时
                        //友情提示：        对不起，您没有选择需要清理的项，请确认！
                        sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Sorry, you have no choice to clean up the items, please confirm!"), mainwindow.pos.x, mainwindow.pos.y);
                    }
                }
            }
        }
    }
    //分割条
    Rectangle {
        id: apt_splitbar
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
        anchors.topMargin: 20
        anchors.left:parent.left
        anchors.leftMargin: 27
        height: root.height -titlebar.height - 37
        width: parent.width - 27 -2
        Item {
            id: scrollItem
            width: parent.width
            height: 40*2 + root.spaceValue*2
            Column {
                spacing: root.spaceValue
                //垃圾清理显示内容
                ListView {
                    id: aptListView
                    width: parent.width
                    height: root.firefox_expanded ? (root.aptNum + 1) * 40 : 40
                    model: mainModel
                    delegate: CookiesDelegate{
                        sub_num: root.aptNum//root.aptsubNum//1212
                        sub_model: subModel
                        btn_flag: root.firefox_btn_flag
                        flag: "firefox"
                        actionTitle: root.firefox_btn_text
                        resetStatus: root.firefox_reset
                        showNum: root.showNum1
                        arrow_display: root.firefox_arrow_show//为0时隐藏伸缩图标，为1时显示伸缩图标
                        expanded: root.firefox_expanded//firefox_expanded为true时，箭头向下，内容展开;firefox_expanded为false时，箭头向上，内容收缩
                        delegate_flag: root.splitFlag
                        onSendBrowserType: {
                            if(browserFlag == "firefox") {
                                if(status == "reset") {//点击重置按钮，清空数据
                                    subModel.clear();
                                    root.firefox_btn_flag = "cookies_scan";//1206
                                    root.firefox_btn_text = qsTr("Start scanning")//开始扫描//1206
                                    root.firefox_reset = false;//1206
                                    if(root.firefox_expanded == true) {
                                        root.firefox_expanded = false;//1、先传递给CookiesDelegate.qml的伸缩值设为默认的false
                                    }
                                    root.firefox_arrow_show = 0;//2、然后传递给CookiesDelegate.qml去隐藏伸展按钮
                                }
                                else if(status == "rescan") {
                                    subModel.clear();
                                    root.firefox_btn_flag = "cookies_scan";//1206
                                    root.firefox_btn_text = qsTr("Start scanning")//开始扫描//1206
                                    root.firefox_reset = false;//1206
                                    if(root.firefox_expanded == true) {
                                        root.firefox_expanded = false;//1、先传递给CookiesDelegate.qml的伸缩值设为默认的false
                                    }
                                    root.firefox_arrow_show = 0;//2、然后传递给CookiesDelegate.qml去隐藏伸展按钮
                                    root.flag = false;
                                    root.getDataOfFirefox();
                                }
                                else {
                                    root.firefox_btn_flag = status;
                                    if (root.firefox_btn_flag == "cookies_scan") {
                                        console.log("scan---f......");
                                        //开始扫描时获取cookies
                                        root.flag = false;
                                        root.getDataOfFirefox();
                                    }
                                    else if (root.firefox_btn_flag == "cookies_work") {
                                        if(root.firefox_check_flag) {
                                            console.log("clean---f......");
                                            //开始清理cookies
//                                            systemdispatcher.set_user_homedir_qt();
//                                            systemdispatcher.cookies_clean_records_function_qt("firefox");
                                        }
                                        else {
                                            sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Sorry, you have no choice to clean up the items, please confirm!"), mainwindow.pos.x, mainwindow.pos.y);
                                        }
                                    }
                                }
                            }
                        }
                        onBrowserArrowClicked: {//
//                            console.lmaincheck1og("111");
//                            console.log(str);
//                            console.log(expand_flag);
//                            scrollItem.height = (root.aptNum + 1) * 40 + (root.softNum + 1) * 40 + root.spaceValue*2;
                            if(browserFlag == "firefox") {//1212
                                if(expand_flag == true) {
                                    root.firefox_expanded = true;
                                    if(root.chromium_expanded == true) {
                                        scrollItem.height = (root.aptNum + 1) * 40 + (root.softNum + 1) * 40 + root.spaceValue*2;
                                    }
                                    else {
                                        scrollItem.height = (root.aptNum + 2) * 40 + root.spaceValue*2;
                                    }
                                }
                                else {
                                    root.firefox_expanded = false;
                                    if(root.chromium_expanded == true) {
                                        scrollItem.height = (root.softNum + 2) * 40 + root.spaceValue*2;
                                    }
                                    else {
                                        scrollItem.height = 2* 40 + root.spaceValue*2;
                                    }
                                }
                            }
                        }
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
                //垃圾清理显示内容
                ListView {
                    id: softListView
                    width: parent.width
                    height: root.chromium_expanded ? (root.softNum + 1) * 40 : 40
                    model: softmainModel
                    delegate: CookiesDelegate{
                        sub_num: root.softNum//root.softsubNum//1212
                        sub_model: softsubModel
                        btn_flag: root.chromium_btn_flag
                        showNum: root.showNum2
                        flag: "chromium"
                        actionTitle: root.chromium_btn_text
                        resetStatus: root.chromium_reset
                        arrow_display: root.chromium_arrow_show//为0时隐藏伸缩图标，为1时显示伸缩图标
                        expanded: root.chromium_expanded//firefox_expanded为true时，箭头向下，内容展开;firefox_expanded为false时，箭头向上，内容收缩
                        delegate_flag: root.splitFlag
                        onSendBrowserType: {
                            if(browserFlag == "chromium") {
                                if(status == "reset") {//点击重置按钮，清空数据
                                    softsubModel.clear();
                                    root.chromium_btn_flag = "cookies_scanc";//1206
                                    root.chromium_btn_text = qsTr("Start scanning")//开始扫描//1206
                                    root.chromium_reset = false;//1206
                                    if(root.chromium_expanded == true) {
                                        root.chromium_expanded = false;//1、先传递给CookiesDelegate.qml的伸缩值设为默认的false
                                    }
                                    root.chromium_arrow_show = 0;//2、然后传递给CookiesDelegate.qml去隐藏伸展按钮
                                }
                                else if(status == "rescan") {
                                    softsubModel.clear();
                                    root.chromium_btn_flag = "cookies_scanc";//1206
                                    root.chromium_btn_text = qsTr("Start scanning")//开始扫描//1206
                                    root.chromium_reset = false;//1206
                                    if(root.chromium_expanded == true) {
                                        root.chromium_expanded = false;//1、先传递给CookiesDelegate.qml的伸缩值设为默认的false
                                    }
                                    root.chromium_arrow_show = 0;//2、然后传递给CookiesDelegate.qml去隐藏伸展按钮
                                    root.flag = false;
                                    root.getDataOfChromium();
                                }
                                else {
                                    root.chromium_btn_flag = status;
                                    if (root.chromium_btn_flag == "cookies_scanc") {
                                        console.log("scan---c......");
                                        //开始扫描时获取cookies
                                        root.flag = false;
                                        root.getDataOfChromium();
                                    }
                                    else if (root.chromium_btn_flag == "cookies_workc") {
                                        if(root.chromium_check_flag)
                                        {
                                            console.log("clean---c......");
                                            //开始清理cookies
//                                            systemdispatcher.set_user_homedir_qt();
//                                            systemdispatcher.cookies_clean_records_function_qt("chromium");
                                        }
                                        else {
                                            sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Sorry, you have no choice to clean up the items, please confirm!"), mainwindow.pos.x, mainwindow.pos.y);
                                        }
                                    }
                                }
                            }
                        }
                        onBrowserArrowClicked: {
//                            console.log("222");
//                            console.log(str);
//                            console.log(expand_flag);
//                            scrollItem.height = (root.aptNum + 1) * 40 + (root.softNum + 1) * 40 + root.spaceValue*2;
                            if(browserFlag == "chromium") {//1212
                                if(expand_flag == true) {
                                    root.chromium_expanded = true;
                                    if(root.firefox_expanded == true) {
                                        scrollItem.height = (root.aptNum + 1) * 40 + (root.softNum + 1) * 40 + root.spaceValue*2;
                                    }
                                    else {
                                        scrollItem.height = (root.softNum + 2) * 40 + root.spaceValue*2;
                                    }
                                }
                                else {
                                    root.chromium_expanded = false;
                                    if(root.firefox_expanded == true) {
                                        scrollItem.height = (root.aptNum + 2) * 40 + root.spaceValue*2;
                                    }
                                    else {
                                        scrollItem.height = 2* 40 + root.spaceValue*2;
                                    }
                                }
                            }
                        }
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
            }
        }
    }

    states: [
        State {
            name: "AptWork"
            PropertyChanges { target: actionBtn; text:qsTr("Start cleaning")}//开始清理
            PropertyChanges { target: root; btnFlag: "apt_work" }
            PropertyChanges { target: backBtn; visible: true}
//            PropertyChanges { target: rescanBtn; visible: true}
        },
        State {
            name: "AptWorkAGAIN"
            PropertyChanges { target: actionBtn; text:qsTr("Start scanning") }//开始扫描
            PropertyChanges { target: root; btnFlag: "apt_scan" }
            PropertyChanges { target: backBtn; visible: false}
//            PropertyChanges { target: rescanBtn; visible: false}
        },
        State {
            name: "AptWorkError"
            PropertyChanges { target: actionBtn; text:qsTr("Start scanning") }//开始扫描
            PropertyChanges { target: root; btnFlag: "apt_scan" }
            PropertyChanges { target: backBtn; visible: false}
//            PropertyChanges { target: rescanBtn; visible: false}
        },
        State {
            name: "AptWorkFinish"
            PropertyChanges { target: actionBtn; text:qsTr("Start scanning") }//开始扫描
            PropertyChanges { target: root; btnFlag: "apt_scan" }
            PropertyChanges { target: backBtn; visible: false}
//            PropertyChanges { target: rescanBtn; visible: false}
        },
        State {
            name: "AptWorkEmpty"
            PropertyChanges { target: actionBtn; text:qsTr("Start scanning")}//开始扫描
            PropertyChanges { target: root; btnFlag: "apt_scan" }
            PropertyChanges { target: backBtn; visible: false}
//            PropertyChanges { target: rescanBtn; visible: false}
        }
    ]
}
