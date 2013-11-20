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
    height: 435
    property string btn_text: qsTr("Start scanning")//开始扫描
    property string title: qsTr("Clean the login information and protect personal privacy")//清理浏览器登录信息,保护个人隐私
    property string description: qsTr("Clean up the login information, support Firefox and Chromium browser")//清理上网时留下的登录信息,支持Firefox和Chromium浏览器
    property string btn_flag: "cookies_scan"
    property string btn_flag2: "cookies_scanc"
    property int firefoxNum: 0//扫描到firefox的有效子项的总数
    property int chromiumNum: 0//扫描到chromium的有效子项的总数
    property bool firefox_check_flag: true
    property bool chromium_check_flag: true
    property bool null_flag: false
    property bool null_flag2: false
    property int deleget_arrow: 0
    property int deleget_arrow2: 0
    property bool expanded: false
    property bool expanded2: false
    property bool delegate_flag: false
    property int check_fnum: firefoxNum   //记录子项个数，在确定总checkbox状态时需要的变量
    property int check_cnum: chromiumNum   //记录子项个数，在确定总checkbox状态时需要的变量
    property bool flag: false//记录是单个清理后重新获取数据（true），还是点击开始扫描后获取数据（false）

    //获取firefox的cookies
    function getDataOfFirefox() {
        var cookies_data = sessiondispatcher.cookies_scan_function_qt("f");
        if(cookies_data == "None") {//没有安装Firefox
            root.deleget_arrow=0;//没有安装Firefox时隐藏伸缩图标
            //友情提示
            sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("No Firefox browser installed!"), mainwindow.pos.x, mainwindow.pos.y);
        }
        else {
            if (cookies_data.length === 0) {
                //如果扫描到的数据为空，把空标记置为true，未完成的状态图标隐藏。
                if(root.null_flag == true) {
                    root.null_flag = false;
                }
                root.null_flag = true;
            }
            else {
                //如果扫描到的数据不为空，把空标记置为false，未完成的状态图标显示。
                if(root.null_flag == false) {
                    root.null_flag = true;
                }
                root.null_flag = false;
            }
            root.firefoxNum = cookies_data.length;
            systemdispatcher.clear_cookies_args();
            firefoxModel.clear();
            var num = 0;
            for (var i=0; i< cookies_data.length; i++) {
                //sina.com.cn<2_2>10
                var splitlist = cookies_data[i].split("<2_2>");
                if (splitlist[0] === "") {
                    num++;
                }
                else {
                    firefoxModel.append({"itemTitle": splitlist[0], "desc": "","number": splitlist[1] + "个Cookie"});
                    systemdispatcher.set_cookies_args(splitlist[0]);
                }
            }
            root.firefoxNum -= num;
            if(root.firefoxNum != 0) {
                firefox_check_flag=true;
            }


            //--------------------------------
            if(root.null_flag == true) {
                sessiondispatcher.tellNullToListTitle("firefox", true);
                root.deleget_arrow=0;//Firefox的cookies为空时隐藏伸缩图标
                if(root.flag == false) {
                    //友情提示      扫描内容为空，不再执行清理！
                    sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Scanning content is empty, no longer to perform cleanup!"), mainwindow.pos.x, mainwindow.pos.y);
                }
                else {
                    root.flag = false;
                }
            }
            else if(root.null_flag == false)
            {
                sessiondispatcher.tellNullToListTitle("firefox", false);
                root.deleget_arrow = 1;//Firefox的cookies不为空时显示伸缩图标
                if(flag == false) {
                    toolkits.alertMSG(qsTr("Scan completed!"), mainwindow.pos.x, mainwindow.pos.y);//扫描完成！
                }
                else {
                    root.flag = false;
                }
            }
            //--------------------------------
        }
    }

    //获取chromium的cookies
    function getDataOfChromium() {
        var cookies_data = sessiondispatcher.cookies_scan_function_qt("c");
        if(cookies_data == "None") {//没有安装Chromium
            root.deleget_arrow2=0;
            //友情提示
            sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("No Chromium browser installed!"), mainwindow.pos.x, mainwindow.pos.y);
        }
        else {
            if (cookies_data.length === 0) {
                //如果扫描到的数据为空，把空标记置为true，未完成的状态图标隐藏。
                if(root.null_flag2 == true) {
                    root.null_flag2 = false;
                }
                root.null_flag2 = true;
            }
            else {
                //如果扫描到的数据不为空，把空标记置为false，未完成的状态图标显示。
                if(root.null_flag2 == false) {
                    root.null_flag2 = true;
                }
                root.null_flag2 = false;
            }
            root.chromiumNum = cookies_data.length;
            systemdispatcher.clear_cookies_args();
            chromiumModel.clear();
            var num = 0;
            for (var i=0; i< cookies_data.length; i++) {
                //sina.com.cn<2_2>10
                var splitlist = cookies_data[i].split("<2_2>");
                if (splitlist[0] === "") {
                    num++;
                }
                else {
                    chromiumModel.append({"itemTitle": splitlist[0], "desc": "","number": splitlist[1] + "Cookie"});
                    systemdispatcher.set_cookies_args(splitlist[0]);
                }
            }
            root.chromiumNum -= num;
            if(root.chromiumNum != 0) {
                chromium_check_flag = true;
            }


            //------------------------------------------
            if(root.null_flag2 == true) {
                sessiondispatcher.tellNullToListTitle("chromium", true);
                root.deleget_arrow2=0;
                if(root.flag == false) {
                    //友情提示      扫描内容为空，不再执行清理！
                    sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Scanning content is empty, no longer to perform cleanup!"), mainwindow.pos.x, mainwindow.pos.y);
                }
                else {
                    root.flag = false;
                }
            }


            else if(root.null_flag2 == false)
            {
                root.deleget_arrow2=1;
                sessiondispatcher.tellNullToListTitle("chromium", false);
                if(root.flag == false) {
                    toolkits.alertMSG(qsTr("Scan completed!"), mainwindow.pos.x, mainwindow.pos.y);//扫描完成！
                }
                else {
                    root.flag = false;
                }
            }
            //------------------------------------------
        }
    }

    //委托
    Component{
        id: firefoxDelegate
        ListItems {
            split_status: root.delegate_flag//false
            text: itemTitle
            descript: desc
            size_num: number
            btn_flag: root.btn_flag
            bgImage: ""
            browserFlag: "firefox"
            onClicked: {
                root.getDataOfFirefox();
            }
        }
    }
    Component{
        id: chromiumDelegate
        ListItems {
            split_status: root.delegate_flag//false
            text: itemTitle
            descript: desc
            size_num: number
            btn_flag: root.btn_flag
            bgImage: ""
            browserFlag: "chromium"
            onClicked: {
                root.getDataOfChromium();
            }
        }
    }
    //数据
    ListModel {
        id: firefoxModel
    }
    ListModel {
        id: chromiumModel
    }

    //信号绑定，绑定qt的信号finishCleanWork，该信号emit时触发onFinishCleanWork
    Connections
    {
        target: systemdispatcher
        onFinishCleanWork: {
            if (btn_flag == "cookies_work") {
                if (msg == "") {
                }
                else if (msg == "cookies") {
                    //清理完毕后重新获取cookies
                    root.flag = true;
                    root.getDataOfFirefox();
                }
            }
            if (btn_flag == "cookies_workc") {
                if (msg == "") {
                }
                else if (msg == "cookies") {
                    //清理完毕后重新获取cookies
                    root.flag = true;
                    root.getDataOfChromium();
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
            source: "../img/toolWidget/trace.png"
            Behavior on rotation { NumberAnimation { duration: 200 } }
        }
        Column {
            spacing: 10
            id: mycolumn
            Text {
                id: text0
                width: 700
                text: root.title
                wrapMode: Text.WrapAnywhere
                font.bold: true
                font.pixelSize: 14
                color: "#383838"
            }
            Text {
                id: text
                width: 700
                text: root.description
                wrapMode: Text.WrapAnywhere
                font.pixelSize: 12
                color: "#7a7a7a"
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
        anchors.topMargin: 20
        height: root.height -titlebar.height- 37
        width: parent.width - 2
        Item {
            id: scrollItem
            width: parent.width
            //firefoxNum*30 + chromiumNum*30 + 两个title高度 + spacing高度×4 + topmagin + bottommagin
//            height: root.firefoxNum * 30 + root.chromiumNum * 30 + 30*2 + 15*4 + 20 + 10
            height: 30*2 + 15*4 + 20 + 10
            Column {
                spacing: 15
                anchors.top: parent.top
                anchors.topMargin: 20
                anchors.left: parent.left
                anchors.leftMargin: 30
                //firefox
                ListTitle {
                    id: firefoxTitle
                    imageSource: "../img/toolWidget/cookies.png"
                    itemTitle: qsTr("Clean Firefox's Cookies")//清理Firefox保存的Cookies
                    detailstr: qsTr("Clean up automatically saved logon information by Firefox browser(Cookies)")//清理Firefox浏览器自动保存的登录信息(Cookies)
                    arrow_display: root.deleget_arrow//为0时隐藏伸缩图标，为1时显示伸缩图标
                    flag: "firefox"
                    btnFlag: root.btn_flag
                    nullFlag: root.null_flag
                    expanded: root.expanded//expanded为true时，箭头向下，内容展开;expanded为false时，箭头向上，内容收缩
                    onClicked: {
                        yourselfListView.visible = !yourselfListView.visible;
                        root.expanded = !root.expanded;
                        scrollItem.height = yourselfListView.height + systemListView.height + 30*2 + 15*4 + 20 + 10;
                    }

                    onSendBrowserType: {
                        if(flag == "firefox") {
                            if(status == "reset") {//点击重置按钮，清空数据
                                firefoxModel.clear();
                                root.deleget_arrow=0;//传递给ListTitle.qml去隐藏伸展按钮
                                if(yourselfListView.visible == true) {
                                    yourselfListView.visible = false;
                                }
                                if(root.expanded == true) {
                                    root.expanded = false;
                                }
                            }
                            else {
                                root.btn_flag = status;
                                if(root.firefox_check_flag)
                                {
                                    //broswer cookies
                                    if (root.btn_flag == "cookies_scan") {
                                        console.log("scan---f......");
                                        //开始扫描时获取cookies
                                        root.getDataOfFirefox();
                                    }
                                    else if (root.btn_flag == "cookies_work") {
                                        console.log("clean---f......");
                                        if(yourselfListView.visible == true) {
                                            yourselfListView.visible = false;
                                        }
                                        if(root.expanded == true) {
                                            root.expanded = false;
                                        }
                                        systemdispatcher.set_user_homedir_qt();
                                        systemdispatcher.cookies_clean_records_function_qt("firefox");
                                    }
                                }
                                else {
                                    sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Sorry, you have no choice to clean up the items, please confirm!"), mainwindow.pos.x, mainwindow.pos.y);
                                }
                            }
                        }
                    }
                }
                ListView {
                    id: yourselfListView
                    width: parent.width
                    height: root.expanded ? yourselfListView.count * 30 : 0
                    model: firefoxModel
                    delegate: firefoxDelegate
                    visible: false
                }
                //chromium
                ListTitle {
                    id: chromiumTitle
                    imageSource: "../img/toolWidget/chrome.png"
                    itemTitle: qsTr("Clean Chromium's Cookies")//清理Chromium保存的Cookies
                    detailstr: qsTr("Clean up automatically saved logon information by Chromium browser(Cookies)")//清理Chromium浏览器自动保存的登录信息(Cookies)
                    arrow_display: root.deleget_arrow2
                    flag: "chromium"
                    btnFlag: root.btn_flag2
                    nullFlag: root.null_flag2
                    expanded: root.expanded2//expanded为true时，箭头向下，内容展开;expanded为false时，箭头向上，内容收缩
                    onClicked: {
                        systemListView.visible = !systemListView.visible;
                        root.expanded2 = !root.expanded2;
                        scrollItem.height = yourselfListView.height + systemListView.height + 30*2 + 15*4 + 20 + 10;
                    }
                    onSendBrowserType: {
                        if(flag == "chromium") {
                            console.log("chromium");

                            if(status == "reset") {//点击重置按钮，清空数据
                                chromiumModel.clear();
                                root.deleget_arrow2=0;//传递给ListTitle.qml去隐藏伸展按钮
                                if(systemListView.visible == true) {
                                    systemListView.visible = false;
                                }
                                if(root.expanded2 == true) {
                                    root.expanded2 = false;
                                }
                            }
                            else {
                                root.btn_flag2 = status;
                                if(root.chromium_check_flag)
                                {
                                    //broswer cookies
                                    if (root.btn_flag2 == "cookies_scanc") {
                                        console.log("scan---c......");
                                        //开始扫描时获取cookies
                                        root.getDataOfChromium();
                                    }
                                    else if (root.btn_flag2 == "cookies_workc") {
                                        console.log("clean---c......");
                                        root.deleget_arrow2=0;
                                        if(systemListView.visible == true) {
                                            systemListView.visible = false;
                                        }
                                        if(root.expanded2 == true) {
                                            root.expanded2 = false;
                                        }
                                        systemdispatcher.set_user_homedir_qt();
                                        systemdispatcher.cookies_clean_records_function_qt("chromium");
                                    }
                                }
                                else {
                                    sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Sorry, you have no choice to clean up the items, please confirm!"), mainwindow.pos.x, mainwindow.pos.y);
                                }
                            }
                        }
                    }
                }
                ListView {
                    id: systemListView
                    width: parent.width
                    height: root.expanded2 ? systemListView.count * 30 : 0
                    model: chromiumModel
                    delegate: chromiumDelegate
                    visible: false
                }
            }
        }
    }
}









//Item {
//    id:root
//    width: parent.width
//    height: 435
//    property string btn_text: qsTr("Start scanning")//开始扫描
//    property string title: qsTr("Clean the login information and protect personal privacy")//清理浏览器登录信息,保护个人隐私
//    property string description: qsTr("Clean up the login information, support Firefox and Chromium browser")//清理上网时留下的登录信息,支持Firefox和Chromium浏览器
//    property string btn_flag: "cookies_scan"
//    property string btn_flag2: "cookies_scanc"
//    property int firefoxNum: 0//扫描到firefox的有效子项的总数
//    property int chromiumNum: 0//扫描到chromium的有效子项的总数
//    property bool firefox_check_flag: true
//    property bool chromium_check_flag: true
//    property bool null_flag: false
//    property bool null_flag2: false
//    property int deleget_arrow: 0
//    property int deleget_arrow2: 0
//    property bool expanded: false
//    property bool expanded2: false
//    property bool delegate_flag: false
//    property int check_fnum: firefoxNum   //记录子项个数，在确定总checkbox状态时需要的变量
//    property int check_cnum: chromiumNum   //记录子项个数，在确定总checkbox状态时需要的变量
//    property bool mainStatus1: true//存放firefox主checkbox的状态
//    property bool mainStatus2: true//存放chromium主checkbox的状态

//    property bool hasFirefox//是否有firefox的标记
//    property bool hasChromium//是否有chromium的标记

//    property bool flag: false

//    function getDataOfFirefox() {
////        var cookies_data = sessiondispatcher.scan_cookies_records_qt();
//        var cookies_data = sessiondispatcher.cookies_scan_function_qt("f");
//        if(cookies_data == "None") {//没有安装Firefox
//            root.deleget_arrow=0;
//            //友情提示
//            sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("No Firefox browser installed!"), mainwindow.pos.x, mainwindow.pos.y);
//        }
//        else {
//            if (cookies_data.length === 0) {
//                //如果扫描到的数据为空，把空标记置为true，未完成的状态图标隐藏。
//                if(root.null_flag == true) {
//                    root.null_flag = false;
//                }
//                root.null_flag = true;
//            }
//            else {
//                //如果扫描到的数据不为空，把空标记置为false，未完成的状态图标显示。
//                if(root.null_flag == false) {
//                    root.null_flag = true;
//                }
//                root.null_flag = false;
//            }
//            root.firefoxNum = cookies_data.length;
//            systemdispatcher.clear_cookies_args();
//            firefoxModel.clear();
//            var num = 0;
//            for (var i=0; i< cookies_data.length; i++) {
//                //sina.com.cn<2_2>10
//                var splitlist = cookies_data[i].split("<2_2>");
//                if (splitlist[0] === "") {
//                    num++;
//                }
//                else {
//                    firefoxModel.append({"itemTitle": splitlist[0], "desc": "","number": splitlist[1] + "个Cookie"});
//                    systemdispatcher.set_cookies_args(splitlist[0]);
//                }
//            }
//            root.firefoxNum -= num;
//            if(root.firefoxNum != 0) {
//                firefox_check_flag=true;
//            }


//            //--------------------------------
//            if(root.null_flag == true) {
//                sessiondispatcher.tellNullToListTitle("firefox", true);
//                root.deleget_arrow=0;
//                if(root.flag == false) {
//                    //友情提示      扫描内容为空，不再执行清理！
//                    sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Scanning content is empty, no longer to perform cleanup!"), mainwindow.pos.x, mainwindow.pos.y);
//                }
//                else {
//                    root.flag = false;
//                }
//            }
//            else if(root.null_flag == false)
//            {
//                sessiondispatcher.tellNullToListTitle("firefox", false);
//                root.deleget_arrow = 1;
//                if(flag == false) {
//                    toolkits.alertMSG(qsTr("Scan completed!"), mainwindow.pos.x, mainwindow.pos.y);//扫描完成！
//                }
//                else {
//                    root.flag = false;
//                }
//            }
//            //--------------------------------
//        }
//    }

//    function getDataOfChromium() {
//        var cookies_data = sessiondispatcher.cookies_scan_function_qt("c");
//        if(cookies_data == "None") {//没有安装Chromium
//            root.deleget_arrow2=0;
//            //友情提示
//            sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("No Chromium browser installed!"), mainwindow.pos.x, mainwindow.pos.y);
//        }
//        else {
//            if (cookies_data.length === 0) {
//                //如果扫描到的数据为空，把空标记置为true，未完成的状态图标隐藏。
//                if(root.null_flag2 == true) {
//                    root.null_flag2 = false;
//                }
//                root.null_flag2 = true;
//            }
//            else {
//                //如果扫描到的数据不为空，把空标记置为false，未完成的状态图标显示。
//                if(root.null_flag2 == false) {
//                    root.null_flag2 = true;
//                }
//                root.null_flag2 = false;
//            }
//            root.chromiumNum = cookies_data.length;
//            systemdispatcher.clear_cookies_args();
//            chromiumModel.clear();
//            var num = 0;
//            for (var i=0; i< cookies_data.length; i++) {
//                //sina.com.cn<2_2>10
//                var splitlist = cookies_data[i].split("<2_2>");
//                if (splitlist[0] === "") {
//                    num++;
//                }
//                else {
//                    chromiumModel.append({"itemTitle": splitlist[0], "desc": "","number": splitlist[1] + "Cookie"});
//                    systemdispatcher.set_cookies_args(splitlist[0]);
//                }
//            }
//            root.chromiumNum -= num;
//            if(root.chromiumNum != 0) {
//                chromium_check_flag = true;
//            }

//            //------------------------------------------
//            if(root.null_flag2 == true) {
//                sessiondispatcher.tellNullToListTitle("chromium", true);
//                root.deleget_arrow2=0;
//                if(root.flag == false) {
//                    //友情提示      扫描内容为空，不再执行清理！
//                    sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Scanning content is empty, no longer to perform cleanup!"), mainwindow.pos.x, mainwindow.pos.y);
//                }
//                else {
//                    root.flag = false;
//                }
//            }
//            else if(root.null_flag2 == false)
//            {
//                root.deleget_arrow2=1;
//                sessiondispatcher.tellNullToListTitle("chromium", false);
//                if(root.flag == false) {
//                    toolkits.alertMSG(qsTr("Scan completed!"), mainwindow.pos.x, mainwindow.pos.y);//扫描完成！
//                }
//                else {
//                    root.flag = false;
//                }
//            }
//            //------------------------------------------
//        }
//    }

//    signal cookies_signal(string cookies_msg);
//    //获取cookies：包括两种情况，一是扫描时获取，二是清理完毕后重新获取
//    onCookies_signal: {
//        if (cookies_msg == "CookiesWork") {
//            //get data of firefox cookies
////            console.log("kobe.........");
//            root.getDataOfFirefox();
//        }
//        else if (cookies_msg == "CookiesWorkC") {
//            //get data of chromium cookies
//            root.getDataOfChromium();
//        }
//    }

//    //委托
//    Component{
//        id: firefoxDelegate
//        ListItems {
//            split_status: root.delegate_flag//false
//            text: itemTitle
//            descript: desc
//            size_num: number
//            checkbox_status: root.mainStatus1//根据firefox主checkbox实时的状态来更新子checkbox的状态
//            btn_flag: root.btn_flag
//            bgImage: ""
//            browserFlag: "firefox"
//            onClicked: {
//                cookies_signal("CookiesWork");
//            }
//        }
//    }
//    Component{
//        id: chromiumDelegate
//        ListItems {
//            split_status: root.delegate_flag//false
//            text: itemTitle
//            descript: desc
//            size_num: number
//            checkbox_status: root.mainStatus2//根据chromium主checkbox实时的状态来更新子checkbox的状态
//            btn_flag: root.btn_flag
//            bgImage: ""
//            browserFlag: "chromium"
//            onClicked: {
//                cookies_signal("CookiesWorkC");
//            }
//        }
//    }
//    //数据
//    ListModel {
//        id: firefoxModel
//    }
//    ListModel {
//        id: chromiumModel
//    }

//    //信号绑定，绑定qt的信号finishCleanWork，该信号emit时触发onFinishCleanWork
//    Connections
//    {
//        target: systemdispatcher
//        onFinishCleanWork: {
//            if (btn_flag == "cookies_work") {
//                if (msg == "") {
//                }
//                else if (msg == "cookies") {
//                    //清理完毕后重新获取cookies
//                    root.flag = true;
//                    root.cookies_signal("CookiesWork");
//                    root.deleget_arrow = 0;//清理完毕后隐藏箭头图标
//                }
//            }
//            if (btn_flag == "cookies_workc") {
//                if (msg == "") {
//                }
//                else if (msg == "cookies") {
//                    //清理完毕后重新获取cookies
//                    root.flag = true;
//                    root.cookies_signal("CookiesWorkC");
//                    root.deleget_arrow2 = 0;//清理完毕后隐藏箭头图标
//                }
//            }
//        }
//    }
//    //背景
//    Image {
//        source: "../img/skin/bg-bottom-tab.png"
//        anchors.fill: parent
//    }
//    //titlebar
//    Row {
//        id: titlebar
//        spacing: 20
//        width: parent.width
//        anchors { top: parent.top; topMargin: 20; left: parent.left; leftMargin: 27 }
//        Image {
//            id: refreshArrow
//            source: "../img/toolWidget/trace.png"
//            Behavior on rotation { NumberAnimation { duration: 200 } }
//        }
//        Column {
//            spacing: 10
//            id: mycolumn
//            Text {
//                id: text0
//                width: 700
//                text: root.title
//                wrapMode: Text.WrapAnywhere
//                font.bold: true
//                font.pixelSize: 14
//                color: "#383838"
//            }
//            Text {
//                id: text
//                width: 700
//                text: root.description
//                wrapMode: Text.WrapAnywhere
//                font.pixelSize: 12
//                color: "#7a7a7a"
//            }
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
//        color: "#d8e0e6"
//    }

//    Common.ScrollArea {
//        frame:false
//        anchors.top: titlebar.bottom
//        anchors.topMargin: 20
//        height: root.height -titlebar.height- 37
//        width: parent.width - 2
//        Item {
//            id: scrollItem
//            width: parent.width
//            //firefoxNum*30 + chromiumNum*30 + 两个title高度 + spacing高度×4 + topmagin + bottommagin
////            height: root.firefoxNum * 30 + root.chromiumNum * 30 + 30*2 + 15*4 + 20 + 10
//            height: 30*2 + 15*4 + 20 + 10
//            Column {
//                spacing: 15
//                anchors.top: parent.top
//                anchors.topMargin: 20
//                anchors.left: parent.left
//                anchors.leftMargin: 30
//                //firefox
//                ListTitle {
//                    id: firefoxTitle
//                    imageSource: "../img/toolWidget/cookies.png"
//                    itemTitle: qsTr("Clean Firefox's Cookies")//清理Firefox保存的Cookies
//                    detailstr: qsTr("Clean up automatically saved logon information by Firefox browser(Cookies)")//清理Firefox浏览器自动保存的登录信息(Cookies)
//                    sub_num: root.firefoxNum
//                    arrow_display: root.deleget_arrow
//                    flag: "firefox"
//                    btnFlag: root.btn_flag
//                    nullFlag: root.null_flag
//                    onClicked: {
//                        yourselfListView.visible = !yourselfListView.visible;
//                        root.expanded = !root.expanded;
//                        scrollItem.height = yourselfListView.height + systemListView.height + 30*2 + 15*4 + 20 + 10;
//                    }

//                    onSendBrowserType: {
//                        if(flag == "firefox") {
//                            if(status == "reset") {//点击重置按钮，清空数据
//                                firefoxModel.clear();
//                                root.deleget_arrow=0;//传递给ListTitle.qml去隐藏伸展按钮
//                                if(yourselfListView.visible == true) {
//                                    yourselfListView.visible = false;
//                                }
//                                if(root.expanded == true) {
//                                    root.expanded = false;
//                                }
//                            }
//                            else {
//                                root.btn_flag = status;
//                                if(root.firefox_check_flag)
//                                {
//                                    //broswer cookies
//                                    if (root.btn_flag == "cookies_scan") {
//                                        console.log("scan---f......");
//                                        //开始扫描时获取cookies
//                                        cookies_signal("CookiesWork");
//                                    }
//                                    else if (root.btn_flag == "cookies_work") {
//                                        console.log("clean---f......");
//                                        if(yourselfListView.visible == true) {
//                                            yourselfListView.visible = false;
//                                        }
//                                        if(root.expanded == true) {
//                                            root.expanded = false;
//                                        }
//                                        systemdispatcher.set_user_homedir_qt();
//                                        systemdispatcher.cookies_clean_records_function_qt("firefox");
//                                    }
//                                }
//                                else {
//                                    sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Sorry, you have no choice to clean up the items, please confirm!"), mainwindow.pos.x, mainwindow.pos.y);
//                                }
//                            }
//                        }
//                    }
//                }
//                ListView {
//                    id: yourselfListView
//                    width: parent.width
//                    height: root.expanded ? yourselfListView.count * 30 : 0
//                    model: firefoxModel
//                    delegate: firefoxDelegate
//                    visible: false
//                }
//                //chromium
//                ListTitle {
//                    id: chromiumTitle
//                    imageSource: "../img/toolWidget/chrome.png"
//                    itemTitle: qsTr("Clean Chromium's Cookies")//清理Chromium保存的Cookies
//                    detailstr: qsTr("Clean up automatically saved logon information by Chromium browser(Cookies)")//清理Chromium浏览器自动保存的登录信息(Cookies)
//                    sub_num: root.chromiumNum
//                    arrow_display: root.deleget_arrow2
//                    flag: "chromium"
//                    btnFlag: root.btn_flag2
//                    nullFlag: root.null_flag2
//                    onClicked: {
//                        systemListView.visible = !systemListView.visible;
//                        root.expanded2 = !root.expanded2;
//                        scrollItem.height = yourselfListView.height + systemListView.height + 30*2 + 15*4 + 20 + 10;
//                    }
//                    onSendBrowserType: {
//                        if(flag == "chromium") {
//                            console.log("chromium");

//                            if(status == "reset") {//点击重置按钮，清空数据
//                                chromiumModel.clear();
//                                root.deleget_arrow2=0;//传递给ListTitle.qml去隐藏伸展按钮
//                                if(systemListView.visible == true) {
//                                    systemListView.visible = false;
//                                }
//                                if(root.expanded2 == true) {
//                                    root.expanded2 = false;
//                                }
//                            }
//                            else {
//                                root.btn_flag2 = status;
//                                if(root.chromium_check_flag)
//                                {
//                                    //broswer cookies
//                                    if (root.btn_flag2 == "cookies_scanc") {
//                                        console.log("scan---c......");
//                                        //开始扫描时获取cookies
//                                        cookies_signal("CookiesWorkC");
//                                    }
//                                    else if (root.btn_flag2 == "cookies_workc") {
//                                        console.log("clean---c......");
//                                        root.deleget_arrow2=0;
//                                        if(systemListView.visible == true) {
//                                            systemListView.visible = false;
//                                        }
//                                        if(root.expanded2 == true) {
//                                            root.expanded2 = false;
//                                        }
//                                        systemdispatcher.set_user_homedir_qt();
//                                        systemdispatcher.cookies_clean_records_function_qt("chromium");
//                                    }
//                                }
//                                else {
//                                    sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Sorry, you have no choice to clean up the items, please confirm!"), mainwindow.pos.x, mainwindow.pos.y);
//                                }
//                            }
//                        }
//                    }
//                }
//                ListView {
//                    id: systemListView
//                    width: parent.width
//                    height: root.expanded2 ? systemListView.count * 30 : 0
//                    model: chromiumModel
//                    delegate: chromiumDelegate
//                    visible: false
//                }
//            }
//        }
//    }
//}
