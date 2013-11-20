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

//-------------1105
Item {
    id:root
    width: parent.width
    height: 435
    property string btn_text: qsTr("Start scanning")//开始扫描
    property string title: qsTr("Clean the login information and protect personal privacy")//清理浏览器登录信息,保护个人隐私
    property string description: qsTr("Clean up the login information, support Firefox and Chromium browser")//清理上网时留下的登录信息,支持Firefox和Chromium浏览器
    property string btn_flag: "cookies_scan"
    property string btn_flag2: "cookies_scanc"
//    property string work_result: ""
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
    property bool mainStatus1: true//存放firefox主checkbox的状态
    property bool mainStatus2: true//存放chromium主checkbox的状态

    property bool hasFirefox//是否有firefox的标记
    property bool hasChromium//是否有chromium的标记

    property bool flag: false

//    onNull_flag2Changed: {
//        console.log("flag2 change..");
//        console.log(null_flag2);
//    }

//    onNull_flagChanged: {
//        console.log("flag change..");
//        console.log(null_flag);
//    }
    function getDataOfFirefox() {
        console.log("kobe.........1");
//        var cookies_data = sessiondispatcher.scan_cookies_records_qt();
        var cookies_data = sessiondispatcher.cookies_scan_function_qt("f");
//        console.log(cookies_data);
//        console.log(cookies_data.length);
        if(cookies_data == "None") {//没有安装Firefox
            root.deleget_arrow=0;
            //友情提示
            sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("No Firefox browser installed!"), mainwindow.pos.x, mainwindow.pos.y);
        }
        else {
            if (cookies_data.length === 0) {
//                console.log("kobe.........2");
                //如果扫描到的数据为空，把空标记置为true，未完成的状态图标隐藏。
                if(root.null_flag == true) {
                    root.null_flag = false;
                }
                root.null_flag = true;
    //            if(statusImage.visible == true)
    //                statusImage.visible = false;
            }
            else {
//                console.log("kobe.........3");
                //如果扫描到的数据不为空，把空标记置为false，未完成的状态图标显示。
                if(root.null_flag == false) {
                    root.null_flag = true;
                }
                root.null_flag = false;
    //            statusImage.visible = true;
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
                root.deleget_arrow=0;
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
                root.deleget_arrow = 1;
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

    function getDataOfChromium() {
        console.log("lixiang.........1");
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
    //            if(statusImage.visible == true)
    //                statusImage.visible = false;
            }
            else {
                //如果扫描到的数据不为空，把空标记置为false，未完成的状态图标显示。
                if(root.null_flag2 == false) {
                    root.null_flag2 = true;
                }
                root.null_flag2 = false;
    //            statusImage.visible = true;
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
    //                                        chromiumTitle.state = "CookiesWorkEmptyC";
    //                                            console.log("iiiiiiiiiii");
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
//        else if(root.hasChromium == false) {
//            root.deleget_arrow2=0;
//            //友情提示
//            sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("No Chromium browser installed!"), mainwindow.pos.x, mainwindow.pos.y);
//        }
    }

    signal cookies_signal(string cookies_msg);
    //获取cookies：包括两种情况，一是扫描时获取，二是清理完毕后重新获取
    onCookies_signal: {
        if (cookies_msg == "CookiesWork") {
            //get data of firefox cookies
//            console.log("kobe.........");
            root.getDataOfFirefox();
        }
        else if (cookies_msg == "CookiesWorkC") {
            //get data of chromium cookies
            root.getDataOfChromium();
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
            checkbox_status: root.mainStatus1//根据firefox主checkbox实时的状态来更新子checkbox的状态
            btn_flag: root.btn_flag
            bgImage: ""
            browserFlag: "firefox"
            onClicked: {
//                console.log("wahahaha");
                cookies_signal("CookiesWork");
//                console.log("pppppppppppp")
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
            checkbox_status: root.mainStatus2//根据chromium主checkbox实时的状态来更新子checkbox的状态
            btn_flag: root.btn_flag
            bgImage: ""
            browserFlag: "chromium"
            onClicked: {
                cookies_signal("CookiesWorkC");
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

    //信号绑定，绑定qt的信号，判断浏览器是否安装了
//    Connections
//    {
//        target: sessiondispatcher
//        onJudge_deb_exists_firefox: {
//            if(flag == "yes") {
//                console.log("firefox is ok");
//                root.hasFirefox = true;
//            }
//            else if(flag == "no") {
//                console.log("firefox is no");
//                root.hasFirefox = false;
//            }
//        }
//        onJudge_deb_exists_chromium: {
//            if(flag == "yes") {
//                console.log("chromium is ok");
//                root.hasChromium = true;
//            }
//            else if(flag == "no") {
//                console.log("chromium is no");
//                root.hasChromium = false;
//            }
//        }
//    }

    //信号绑定，绑定qt的信号finishCleanWork，该信号emit时触发onFinishCleanWork
    Connections
    {
        target: systemdispatcher
//        onFinishCleanWorkError: {
//            if (btn_flag == "cookies_work") {
//                if (msg == "cookies") {
//                    root.work_result = msg;
//                    root.state = "CookiesWorkError";
//                    toolkits.alertMSG("清理出现异常！", mainwindow.pos.x, mainwindow.pos.y);
//                }
//            }
//         }
        onFinishCleanWork: {
            if (btn_flag == "cookies_work") {
                if (msg == "") {
                    console.log("0000000000");
//                    root.deleget_arrow = 1;//清理中断时，显示伸缩箭头
                }
                else if (msg == "cookies") {
                    //清理完毕后重新获取cookies
                    console.log("11111111111");
                    root.flag = true;
                    root.cookies_signal("CookiesWork");
                    root.deleget_arrow = 0;//清理完毕后隐藏箭头图标
//                    root.expanded = false;
                }
            }
            if (btn_flag == "cookies_workc") {
                if (msg == "") {
//                    root.deleget_arrow2 = 1;//清理中断时，显示伸缩箭头
                }
                else if (msg == "cookies") {
                    //清理完毕后重新获取cookies
                    root.flag = true;
                    root.cookies_signal("CookiesWorkC");
                    root.deleget_arrow2 = 0;//清理完毕后隐藏箭头图标
//                    root.expanded = false;
                }
            }
//            if (btn_flag == "cookies_work") {
//                if (msg == "") {
//                    resetBtn.visible = true;
//                }
//                else if (msg == "cookies") {
//                    root.work_result = msg;
//                    root.state = "CookiesWorkFinish";
//                    toolkits.alertMSG("清理完毕！", mainwindow.pos.x, mainwindow.pos.y);
//                    //清理完毕后重新获取cookies
//                    root.cookies_signal("CookiesWork");
//                }
//            }
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
                    sub_num: root.firefoxNum
                    arrow_display: root.deleget_arrow
                    flag: "firefox"
                    btnFlag: root.btn_flag
                    nullFlag: root.null_flag
                    onClicked: {
                        yourselfListView.visible = !yourselfListView.visible;
                        root.expanded = !root.expanded;
                        scrollItem.height = yourselfListView.height + systemListView.height + 30*2 + 15*4 + 20 + 10;
                    }
//                    onResetclicked : {
//                        if(yourselfListView.visible == true) {
//                            yourselfListView.visible = false;
//                        }
//                        if(root.expanded == true) {
//                            root.expanded = false;
//                        }
//                    }

                    onSendBrowserType: {
//                        console.log("aaaaaaaaa");
                        if(flag == "firefox") {
//                            console.log("firefox");
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
                                        cookies_signal("CookiesWork");
//                                        if(root.null_flag == true) {
//    //                                        firefoxTitle.state = "CookiesWorkEmpty";
////                                            console.log("yyyyyy");
//                                            sessiondispatcher.tellNullToListTitle("firefox", true);
//                                            root.deleget_arrow=0;
//                                            //友情提示      扫描内容为空，不再执行清理！
//                                            sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Scanning content is empty, no longer to perform cleanup!"), mainwindow.pos.x, mainwindow.pos.y);
//                                        }
//                                        else if(root.null_flag == false)
//                                        {
////                                            console.log("uuuuuu");
//                                            sessiondispatcher.tellNullToListTitle("firefox", false);
//                                            root.deleget_arrow = 1;
//                                            toolkits.alertMSG(qsTr("Scan completed!"), mainwindow.pos.x, mainwindow.pos.y);//扫描完成！
//                                        }
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
                                        systemdispatcher.cookies_clean_records_function_qt("f");
    //                                    systemdispatcher.clean_cookies_records_qt(systemdispatcher.get_cookies_args());
//                                        root.deleget_arrow=1;
                                    }
                                }
                                else
                                    sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Sorry, you have no choice to clean up the items, please confirm!"), mainwindow.pos.x, mainwindow.pos.y);
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
                    sub_num: root.chromiumNum
                    arrow_display: root.deleget_arrow2
                    flag: "chromium"
                    btnFlag: root.btn_flag2
                    nullFlag: root.null_flag2
                    onClicked: {
                        systemListView.visible = !systemListView.visible;
                        root.expanded2 = !root.expanded2;
                        scrollItem.height = yourselfListView.height + systemListView.height + 30*2 + 15*4 + 20 + 10;
                    }
//                    onResetclicked : {
//                        if(systemListView.visible == true) {
//                            systemListView.visible = false;
//                        }
//                        if(root.expanded2 == true) {
//                            root.expanded2 = false;
//                        }
//                    }
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
                                        cookies_signal("CookiesWorkC");
//                                        if(root.null_flag2 == true) {
//    //                                        chromiumTitle.state = "CookiesWorkEmptyC";
////                                            console.log("iiiiiiiiiii");
//                                            sessiondispatcher.tellNullToListTitle("chromium", true);
//                                            root.deleget_arrow2=0;
//                                            //友情提示      扫描内容为空，不再执行清理！
//                                            sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Scanning content is empty, no longer to perform cleanup!"), mainwindow.pos.x, mainwindow.pos.y);
//                                        }
//                                        else if(root.null_flag2 == false)
//                                        {
//                                            root.deleget_arrow2=1;
////                                            console.log("pppppppppppp");
//                                            sessiondispatcher.tellNullToListTitle("chromium", false);
//    //                                        toolkits.alertMSG("扫描完成！", mainwindow.pos.x, mainwindow.pos.y);
//                                        }
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
                                        systemdispatcher.cookies_clean_records_function_qt("c");
    //                                    systemdispatcher.clean_cookies_records_qt(systemdispatcher.get_cookies_args());
//                                        root.deleget_arrowc=1;
                                    }
                                }
                                else
                                    sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Sorry, you have no choice to clean up the items, please confirm!"), mainwindow.pos.x, mainwindow.pos.y);
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





////-------------1104
//Item {
//    id:root
//    width: parent.width
//    height: 435
//    property string btn_text: "开始扫描"
//    property string title: "清理浏览器登录信息,保护个人隐私"
//    property string description: "清理上网时留下的登录信息,目前仅支持Firefox浏览器"
//    property string btn_flag: "cookies_scan"
//    property string work_result: ""
//    property int firefoxNum: 0//扫描到firefox的有效子项的总数
//    property int chromiumNum: 0//扫描到chromium的有效子项的总数
//    property bool check_flag: true
//    property bool null_flag: false
//    property int deleget_arrow :0
//    property bool expanded: true
//    property bool delegate_flag: false
//    property int check_fnum: firefoxNum   //记录子项个数，在确定总checkbox状态时需要的变量
//    property int check_cnum: chromiumNum   //记录子项个数，在确定总checkbox状态时需要的变量
//    property bool mainStatus1: true//存放firefox主checkbox的状态
//    property bool mainStatus2: true//存放chromium主checkbox的状态

////    property string imageSource: "../img/toolWidget/cookies.png"
////    signal sendMainStatus(bool status, string flag);
////    onSendMainStatus: {
////        //主checkbox的状态,以便实时改变所有子chechbox的状态
////        if(flag == "firefox") {
////            root.mainStatus1 = status;
////        }
////        //主checkbox的状态,以便实时改变所有子chechbox的状态
////        else if(flag == "chromium") {
////            root.mainStatus2 = status;
////        }
////    }

////    Connections {
////        target: sessiondispatcher
////        //子chechbox改变后，得到信号，改变主checkbox的状态
////        onStartChangeMaincheckboxStatus: {
////            check.checked = status;
////        }
////    }


//    function getDataOfFirefox() {
//        var cookies_data = sessiondispatcher.scan_cookies_records_qt();
//        if (cookies_data === "") {
//            //如果扫描到的数据为空，把空标记置为true，未完成的状态图标隐藏。
//            root.null_flag = true;
//            if(statusImage.visible == true)
//                statusImage.visible = false;
//        }
//        else {
//            //如果扫描到的数据不为空，把空标记置为false，未完成的状态图标显示。
//            root.null_flag = false;
//            statusImage.visible = true;
//        }
//        root.firefoxNum = cookies_data.length;
//        systemdispatcher.clear_cookies_args();
//        firefoxModel.clear();
//        var num = 0;
//        for (var i=0; i< cookies_data.length; i++) {
//            //sina.com.cn<2_2>10
//            var splitlist = cookies_data[i].split("<2_2>");
//            if (splitlist[0] === "") {
//                num++;
//            }
//            else {
//                firefoxModel.append({"itemTitle": splitlist[0], "desc": "","number": splitlist[1] + "个Cookie"});
//                systemdispatcher.set_cookies_args(splitlist[0]);
//            }
//        }

//        root.firefoxNum -= num;
//        if(root.firefoxNum != 0) {
//            check_flag=true;
//        }
//    }

//    function getDataOfChromium() {
//        var cookies_data = sessiondispatcher.scan_apt_cruft_qt();
//        if (cookies_data === "") {
//            //如果扫描到的数据为空，把空标记置为true，未完成的状态图标隐藏。
//            root.null_flag = true;
//            if(statusImage.visible == true)
//                statusImage.visible = false;
//        }
//        else {
//            //如果扫描到的数据不为空，把空标记置为false，未完成的状态图标显示。
//            root.null_flag = false;
//            statusImage.visible = true;
//        }
//        root.chromiumNum = cookies_data.length;
//        systemdispatcher.clear_cookies_args();
//        chromiumModel.clear();
//        var num = 0;
//        for (var i=0; i< cookies_data.length; i++) {
//            //sina.com.cn<2_2>10
//            var splitlist = cookies_data[i].split("<2_2>");
//            if (splitlist[0] === "") {
//                num++;
//            }
//            else {
//                chromiumModel.append({"itemTitle": splitlist[0], "desc": "","number": splitlist[1] + "个Cookie"});
//                systemdispatcher.set_cookies_args(splitlist[0]);
//            }
//        }

//        root.chromiumNum -= num;
//        if(root.chromiumNum != 0) {
//            check_flag=true;
//        }
//    }


//    Component{
//        id: firefoxDelegate
//        ListItem {
//            split_status: root.delegate_flag//false
//            text: itemTitle
//            descript: desc
//            size_num: number
//            checkbox_status: root.mainStatus1//根据firefox主checkbox实时的状态来更新子checkbox的状态
//            btn_flag: root.btn_flag
//            bgImage: ""
//            browserFlag: "firefox"

//            //当单个checkbox状态变化时会发送change_num信号，这里收到信号，接收其变化的值：check_status
//            onChange_num: {
////                if (browser_flag == "firefox") {
//////                    console.log("firefox.");
////                    if(check_status==true)//已经勾上的子项数量统计,check_fnum记录
////                        check_fnum=check_fnum+1;//勾选了，加1
////                    else
////                        check_fnum=check_fnum-1;//去掉勾选了，减1
////                    if(firefoxNum != 0){  //在扫描出子项并下拉显示了子项的前提下,根据已经勾上的子项个数确定总checkbox处于三种状态中的哪种
////                        if(check_fnum == 0) {
////                            sessiondispatcher.change_maincheckbox_status("false");
////                        }
////                        else if(check_fnum == firefoxNum) {
////                            sessiondispatcher.change_maincheckbox_status("true");
////                        }
////                        else {
////                            sessiondispatcher.change_maincheckbox_status("mid");
////                        }
////                    }
////                    if(check_fnum == firefoxNum && firefoxNum > 0)   //根据是否有勾选项给清理页面传值判断是否能进行清理工作
////                        root.check_flag = true;
////                    else
////                        root.check_flag = false;
////                }
//            }
//        }
//    }

//    Component{
//        id: chromiumDelegate
//        ListItem {
//            split_status: root.delegate_flag//false
//            text: itemTitle
//            descript: desc
//            size_num: number
//            checkbox_status: root.mainStatus2//根据chromium主checkbox实时的状态来更新子checkbox的状态
//            btn_flag: root.btn_flag
//            bgImage: ""
//            browserFlag: "chromium"

//            //当单个checkbox状态变化时，收到其变化的值：check_status
//            onChange_num: {
////                if (browser_flag == "chromium") {
//////                    console.log("chromium.");
////                    if(check_status==true)//已经勾上的子项数量统计,check_cnum记录
////                        check_cnum=check_cnum+1;
////                    else
////                        check_cnum=check_cnum-1;
////                    if(chromiumNum != 0){  //在扫描出子项并下拉显示了子项的前提下,根据已经勾上的子项个数确定总checkbox处于三种状态中的哪种
////                        if(check_cnum == 0) {
////                            sessiondispatcher.change_maincheckbox_status("false");
////                        }
////                        else if(check_cnum == chromiumNum) {
////                            sessiondispatcher.change_maincheckbox_status("true");
////                        }
////                        else {
////                            sessiondispatcher.change_maincheckbox_status("mid");
////                        }
////                    }
////                    if(check_cnum == chromiumNum && chromiumNum > 0)   //根据是否有勾选项给清理页面传值判断是否能进行清理工作
////                        root.check_flag = true;
////                    else
////                        root.check_flag = false;
////                }
//            }
//        }
//    }
//    signal cookies_signal(string cookies_msg);
//    //获取cookies：包括两种情况，一是扫描时获取，二是清理完毕后重新获取
//    onCookies_signal: {
//        if (cookies_msg == "CookiesWork") {
//            //get data of firefox cookies
//            root.getDataOfFirefox();
//            //get data of chromium cookies
//            root.getDataOfChromium();
//        }
//    }
//    ListModel {
//        id: firefoxModel
////        ListElement {itemTitle: ""; desc: ""; number: ""}
//    }
//    ListModel {
//        id: chromiumModel
//    }



//    //信号绑定，绑定qt的信号finishCleanWork，该信号emit时触发onFinishCleanWork
//    Connections
//    {
//        target: systemdispatcher
//        onFinishCleanWorkError: {
//            if (btn_flag == "cookies_work") {
//                if (msg == "cookies") {
//                    root.work_result = msg;
//                    root.state = "CookiesWorkError";
//                    toolkits.alertMSG("清理出现异常！", mainwindow.pos.x, mainwindow.pos.y);
//                }
//            }
//         }
//        onFinishCleanWork: {
//            if (btn_flag == "cookies_work") {
//                if (msg == "") {
//                    resetBtn.visible = true;
//                }
//                else if (msg == "cookies") {
//                    root.work_result = msg;
//                    root.state = "CookiesWorkFinish";
//                    toolkits.alertMSG("清理完毕！", mainwindow.pos.x, mainwindow.pos.y);
//                    //清理完毕后重新获取cookies
//                    root.cookies_signal("CookiesWork");
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
////        height: 50
//        anchors { top: parent.top; topMargin: 20; left: parent.left; leftMargin: 27 }
//        Image {
//            id: refreshArrow
//            source: "../img/toolWidget/trace.png"
//            Behavior on rotation { NumberAnimation { duration: 200 } }
//        }
//        Column {
//            anchors.verticalCenter: parent.verticalCenter
//            spacing: 10
//            Text {
//                text: root.title
//                font.bold: true
//                font.pixelSize: 14
//                color: "#383838"
//            }
//            Text {
//                text: root.description
//                font.pixelSize: 12
//                color: "#7a7a7a"
//            }
//        }
//    }
//    Row{
//        anchors { top: parent.top; topMargin: 30;right: parent.right ; rightMargin: 40 }
//        spacing: 20
//        //status picture
//        Common.StatusImage {
//            id: statusImage
//            visible: false
//            iconName: "yellow.png"
//            text: "未完成"
//            anchors.verticalCenter: parent.verticalCenter
//        }
//        Common.Button {
//            id: bitButton
//            width: 120
//            height: 39
//            text: root.btn_text
//            hoverimage: "green1.png"
//            anchors.verticalCenter: parent.verticalCenter
//            fontsize: 15
//            onClicked: {
//                resetBtn.visible = false;
//                if(root.check_flag)
//                {
//                //broswer cookies
//                 if (btn_flag == "cookies_scan") {
//                     //开始扫描时获取cookies
//                     cookies_signal("CookiesWork");
//                     if(root.null_flag == true) {
//                        root.state = "CookiesWorkEmpty";
//                         root.deleget_arrow=0;
//                         sessiondispatcher.showWarningDialog("友情提示：","扫描内容为空，不再执行清理！", mainwindow.pos.x, mainwindow.pos.y);
//                     }
//                     else if(root.null_flag == false)
//                     {
//                        root.state = "CookiesWork";
//                         root.deleget_arrow=1;
//                         toolkits.alertMSG("扫描完成！", mainwindow.pos.x, mainwindow.pos.y);
//                     }
//                 }
//                 else if (btn_flag == "cookies_work") {
//                     systemdispatcher.set_user_homedir_qt();
//                     systemdispatcher.clean_cookies_records_qt(systemdispatcher.get_cookies_args());
//                     root.deleget_arrow=1;
//                 }
//                }
//                else
//                    sessiondispatcher.showWarningDialog("友情提示：","对不起，您没有选择需要清理的项，请确认！", mainwindow.pos.x, mainwindow.pos.y);
//            }
//        }
//        SetBtn {
//            id: resetBtn
//            width: 12
//            height: 15
//            iconName: "revoke.png"
//            visible: false
//            anchors.verticalCenter: parent.verticalCenter
//            onClicked: {
//                resetBtn.visible = false;
//                firefoxModel.clear();
//                chromiumModel.clear();
//                root.state = "CookiesWorkAGAIN";
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
//        width: parent.width
//        Item {
//            width: parent.width
//            height: (root.firefoxNum + 1) * 40 + (root.chromiumNum + 1) * 40
//            Column {
//                spacing: 30
//                anchors.top: parent.top
//                anchors.topMargin: 20
//                anchors.left: parent.left
//                anchors.leftMargin: 30
//                //firefox
//                //-------------------------------------------
////                Row {
////                    id: chromium
////                    height: 40
////                    spacing: 15
////                    Common.MainCheckBox{
////                        id: firefoxcheck
////                        checked: "true"
////                        anchors.verticalCenter: parent.verticalCenter
////                        onCheckedChanged: {
////                            root.sendMainStatus(firefoxcheck.checkedbool, "firefox");
////                        }
////                    }
////                    Image {
////                        id: chromiumImage
////                        fillMode: "PreserveAspectFit"
////                        height: parent.height*0.9
////                        source: root.imageSource
////                        smooth: true
////                    }
////                    Column {
////                        id: chromiumColumn
////                        spacing: 5
////                        anchors.verticalCenter: parent.verticalCenter
////                        Text {
////                            text: "清理Cookies"
////                            font.pointSize: 11
////                            color: "black"
////                        }
////                        Text {
////                            text: "清理Firefox浏览器自动保存的登录信息(Cookies)"
////                            font.family: "URW Bookman L"
////                            font.pointSize: 9
////                            color: "gray"
////                        }
////                    }
////                    Image {
////                        id: chromiumarrow
////                        fillMode: "PreserveAspectFit"
////                        height: 28
////                        width: 26
////                        source: "../img/icons/arrow.png"
////                        opacity: root.deleget_arrow//这里初始为0,可以初始时将箭头隐藏,以后根据扫描内容确定其值
////                        rotation: root.expanded ? 0 : -180
////                        smooth: true
////                        MouseArea {
////                            anchors.fill: parent
////                            onClicked: {
////                                yourselfListView.visible = !yourselfListView.visible;
//////                                itemtitle.clicked();
////                                root.expanded = !root.expanded;//扫描出的子项是否下拉显示的控制变量
//////                                if(itemtitle.heightMark == itemtitle.sub_num){//通过对heightMark的赋值来实现子项的下拉显示与收缩不显示
//////                                    check.checkedbool=false;//子项收缩时,将总checkbox回到勾选状态
//////                                    check.checked="true";
//////                                    itemtitle.heightMark=0;
//////                                }
//////                                else if(itemtitle.heightMark==0) {
//////                                    if(itemtitle.sub_num>0){//子项下拉显示时，根据总checkbox状态进行赋值控制
//////                                        if(check.checked=="true") {
//////                                            check.checkedbool = true;
//////                                            itemtitle.check_num = itemtitle.sub_num;
//////                                            check.checked = "true"
//////                                        }
//////                                        else if(check.checked=="false") {
//////                                            itemtitle.check_num = itemtitle.sub_num-1;
//////                                            check.checkedbool = false;
//////                                            check.checked = "false"
//////                                        }
//////                                    }
//////                                    itemtitle.heightMark=itemtitle.sub_num;
//////                                }
//////                                itemtitle.subpressed(itemtitle.heightMark); //将heightMark的值传给清理界面实现对是否下拉显示子项的控制
////                            }
////                        }
////                    }
////                }
//                //-------------------------------------------
//                ItemTitle {
//                    id: firefoxTitle
//                    imageSource: "../img/toolWidget/cookies.png"
//                    itemTitle: "清理Cookies"
//                    detailstr: "清理Firefox浏览器自动保存的登录信息(Cookies)"
//                    sub_num: root.firefoxNum
//                    arrow_display: root.deleget_arrow
//                    flag: "firefox"
//                    onClicked: {
//                        yourselfListView.visible = !yourselfListView.visible;
//                    }
//                    onSendMainStatus: {
//                        //主checkbox的状态,以便实时改变所有子chechbox的状态
//                        if(flag == "firefox") {
//                            root.mainStatus1 = status;
//                        }
//                    }

////                    onSubpressed: {root.sub_num = hMark}
//                }
//                ListView {
//                    id: yourselfListView
//                    width: parent.width
//                    height: expanded ? yourselfListView.count * 40 : 0
//                    model: firefoxModel
//                    delegate: firefoxDelegate
//                    visible: false
//                }
//                //chromium
//                ItemTitle {
//                    id: chromiumTitle
//                    imageSource: "../img/toolWidget/cookies.png"
//                    itemTitle: "清理Cookies"
//                    detailstr: "清理Chromium浏览器自动保存的登录信息(Cookies)"
//                    sub_num: root.chromiumNum
//                    arrow_display: root.deleget_arrow
//                    flag: "chromium"
//                    onClicked: {
//                        systemListView.visible = !systemListView.visible;
//                    }
//                    onSendMainStatus: {
//                        //主checkbox的状态,以便实时改变所有子chechbox的状态
//                        if(flag == "chromium") {
//                            root.mainStatus2 = status;
//                        }
//                    }
////                    onSubpressed: {root.sub_num = hMark}
//                }
//                ListView {
//                    id: systemListView
//                    width: parent.width
//                    height: expanded ? systemListView.count * 40 : 0
//                    model: chromiumModel
//                    delegate: chromiumDelegate
//                    visible: false
//                }
//            }
//        }
//    }
//    states: [
//        State {
//            name: "CookiesWork"
//            PropertyChanges { target: bitButton; text:"开始清理"}
//            PropertyChanges { target: root; btn_flag: "cookies_work" }
//            PropertyChanges { target: statusImage; visible: true; iconName: "yellow.png"; text: "未完成"}
//        },
//        State {
//            name: "CookiesWorkAGAIN"
//            PropertyChanges { target: bitButton; text:"开始扫描" }
//            PropertyChanges { target: root; btn_flag: "cookies_scan" }
//            PropertyChanges { target: statusImage; visible: false }
//        },
//        State {
//            name: "CookiesWorkError"
//            PropertyChanges { target: bitButton; text:"开始扫描" }
//            PropertyChanges { target: root; btn_flag: "cookies_scan" }
//            PropertyChanges { target: statusImage; visible: true; iconName: "red.png"; text: "出现异常"}
//        },
//        State {
//            name: "CookiesWorkFinish"
//            PropertyChanges { target: bitButton; text:"开始扫描"}
//            PropertyChanges { target: root; btn_flag: "cookies_scan" }
//            PropertyChanges { target: statusImage; visible: true; iconName: "green.png"; text: "已完成"}
//        },
//        State {
//            name: "CookiesWorkEmpty"
//            PropertyChanges { target: bitButton; text:"开始扫描"}
//            PropertyChanges { target: root; btn_flag: "cookies_scan" }
//            PropertyChanges { target: statusImage; visible: false}
//        }
//    ]
//}










////-------------1031-2
//Item {
//    id:root
//    width: parent.width
//    height: 435
//    property string btn_text: "开始扫描"
//    property string title: "清理浏览器登录信息,保护个人隐私"
//    property string description: "清理上网时留下的登录信息,目前仅支持Firefox浏览器"
//    property string btn_flag: "cookies_scan"
//    property string work_result: ""
//    property int firefoxNum: 0//扫描到firefox的有效子项的总数
//    property int chrominumNum: 0//扫描到chrominum的有效子项的总数
//    property bool check_flag: true
//    property bool null_flag: false
//    property int deleget_arrow :0
//    property bool expanded: true
//    property bool delegate_flag: false
//    property int check_fnum: firefoxNum   //记录子项个数，在确定总checkbox状态时需要的变量
//    property int check_cnum: chrominumNum   //记录子项个数，在确定总checkbox状态时需要的变量
//    property bool mainStatus1: true//存放firefox主checkbox的状态
//    property bool mainStatus2: true//存放chrominum主checkbox的状态


//    function getDataOfFirefox() {
//        var cookies_data = sessiondispatcher.scan_cookies_records_qt();
//        if (cookies_data === "") {
//            //如果扫描到的数据为空，把空标记置为true，未完成的状态图标隐藏。
//            root.null_flag = true;
//            if(statusImage.visible == true)
//                statusImage.visible = false;
//        }
//        else {
//            //如果扫描到的数据不为空，把空标记置为false，未完成的状态图标显示。
//            root.null_flag = false;
//            statusImage.visible = true;
//        }
//        root.firefoxNum = cookies_data.length;
//        systemdispatcher.clear_cookies_args();
//        firefoxModel.clear();
//        var num = 0;
//        for (var i=0; i< cookies_data.length; i++) {
//            //sina.com.cn<2_2>10
//            var splitlist = cookies_data[i].split("<2_2>");
//            if (splitlist[0] === "") {
//                num++;
//            }
//            else {
//                firefoxModel.append({"itemTitle": splitlist[0], "desc": "","number": splitlist[1] + "个Cookie"});
//                systemdispatcher.set_cookies_args(splitlist[0]);
//            }
//        }

//        root.firefoxNum -= num;
//        if(root.firefoxNum != 0) {
//            check_flag=true;
//        }
//    }

//    function getDataOfChrominum() {
//        var cookies_data = sessiondispatcher.scan_apt_cruft_qt();
//        if (cookies_data === "") {
//            //如果扫描到的数据为空，把空标记置为true，未完成的状态图标隐藏。
//            root.null_flag = true;
//            if(statusImage.visible == true)
//                statusImage.visible = false;
//        }
//        else {
//            //如果扫描到的数据不为空，把空标记置为false，未完成的状态图标显示。
//            root.null_flag = false;
//            statusImage.visible = true;
//        }
//        root.chrominumNum = cookies_data.length;
//        systemdispatcher.clear_cookies_args();
//        chrominumModel.clear();
//        var num = 0;
//        for (var i=0; i< cookies_data.length; i++) {
//            //sina.com.cn<2_2>10
//            var splitlist = cookies_data[i].split("<2_2>");
//            if (splitlist[0] === "") {
//                num++;
//            }
//            else {
//                chrominumModel.append({"itemTitle": splitlist[0], "desc": "","number": splitlist[1] + "个Cookie"});
//                systemdispatcher.set_cookies_args(splitlist[0]);
//            }
//        }

//        root.chrominumNum -= num;
//        if(root.chrominumNum != 0) {
//            check_flag=true;
//        }
//    }


//    Component{
//        id: firefoxDelegate
//        ListItem {
//            split_status: root.delegate_flag//false
//            text: itemTitle
//            descript: desc
//            size_num: number
//            checkbox_status: root.mainStatus1//根据firefox主checkbox实时的状态来更新子checkbox的状态
//            btn_flag: root.btn_flag
//            bgImage: ""
//            browserFlag: "firefox"

//            //当单个checkbox状态变化时会发送change_num信号，这里收到信号，接收其变化的值：check_status
//            onChange_num: {
////                if (browser_flag == "firefox") {
//////                    console.log("firefox.");
////                    if(check_status==true)//已经勾上的子项数量统计,check_fnum记录
////                        check_fnum=check_fnum+1;//勾选了，加1
////                    else
////                        check_fnum=check_fnum-1;//去掉勾选了，减1
////                    if(firefoxNum != 0){  //在扫描出子项并下拉显示了子项的前提下,根据已经勾上的子项个数确定总checkbox处于三种状态中的哪种
////                        if(check_fnum == 0) {
////                            sessiondispatcher.change_maincheckbox_status("false");
////                        }
////                        else if(check_fnum == firefoxNum) {
////                            sessiondispatcher.change_maincheckbox_status("true");
////                        }
////                        else {
////                            sessiondispatcher.change_maincheckbox_status("mid");
////                        }
////                    }
////                    if(check_fnum == firefoxNum && firefoxNum > 0)   //根据是否有勾选项给清理页面传值判断是否能进行清理工作
////                        root.check_flag = true;
////                    else
////                        root.check_flag = false;
////                }
//            }
//        }
//    }

//    Component{
//        id: chrominumDelegate
//        ListItem {
//            split_status: root.delegate_flag//false
//            text: itemTitle
//            descript: desc
//            size_num: number
//            checkbox_status: root.mainStatus2//根据chrominum主checkbox实时的状态来更新子checkbox的状态
//            btn_flag: root.btn_flag
//            bgImage: ""
//            browserFlag: "chrominum"

//            //当单个checkbox状态变化时，收到其变化的值：check_status
//            onChange_num: {
////                if (browser_flag == "chrominum") {
//////                    console.log("chrominum.");
////                    if(check_status==true)//已经勾上的子项数量统计,check_cnum记录
////                        check_cnum=check_cnum+1;
////                    else
////                        check_cnum=check_cnum-1;
////                    if(chrominumNum != 0){  //在扫描出子项并下拉显示了子项的前提下,根据已经勾上的子项个数确定总checkbox处于三种状态中的哪种
////                        if(check_cnum == 0) {
////                            sessiondispatcher.change_maincheckbox_status("false");
////                        }
////                        else if(check_cnum == chrominumNum) {
////                            sessiondispatcher.change_maincheckbox_status("true");
////                        }
////                        else {
////                            sessiondispatcher.change_maincheckbox_status("mid");
////                        }
////                    }
////                    if(check_cnum == chrominumNum && chrominumNum > 0)   //根据是否有勾选项给清理页面传值判断是否能进行清理工作
////                        root.check_flag = true;
////                    else
////                        root.check_flag = false;
////                }
//            }
//        }
//    }
//    signal cookies_signal(string cookies_msg);
//    //获取cookies：包括两种情况，一是扫描时获取，二是清理完毕后重新获取
//    onCookies_signal: {
//        if (cookies_msg == "CookiesWork") {
//            //get data of firefox cookies
//            root.getDataOfFirefox();
//            //get data of chrominum cookies
//            root.getDataOfChrominum();
//        }
//    }
//    ListModel {
//        id: firefoxModel
////        ListElement {itemTitle: ""; desc: ""; number: ""}
//    }
//    ListModel {
//        id: chrominumModel
//    }



//    //信号绑定，绑定qt的信号finishCleanWork，该信号emit时触发onFinishCleanWork
//    Connections
//    {
//        target: systemdispatcher
//        onFinishCleanWorkError: {
//            if (btn_flag == "cookies_work") {
//                if (msg == "cookies") {
//                    root.work_result = msg;
//                    root.state = "CookiesWorkError";
//                    toolkits.alertMSG("清理出现异常！", mainwindow.pos.x, mainwindow.pos.y);
//                }
//            }
//         }
//        onFinishCleanWork: {
//            if (btn_flag == "cookies_work") {
//                if (msg == "") {
//                    resetBtn.visible = true;
//                }
//                else if (msg == "cookies") {
//                    root.work_result = msg;
//                    root.state = "CookiesWorkFinish";
//                    toolkits.alertMSG("清理完毕！", mainwindow.pos.x, mainwindow.pos.y);
//                    //清理完毕后重新获取cookies
//                    root.cookies_signal("CookiesWork");
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
////        height: 50
//        anchors { top: parent.top; topMargin: 20; left: parent.left; leftMargin: 27 }
//        Image {
//            id: refreshArrow
//            source: "../img/toolWidget/trace.png"
//            Behavior on rotation { NumberAnimation { duration: 200 } }
//        }
//        Column {
//            anchors.verticalCenter: parent.verticalCenter
//            spacing: 10
//            Text {
//                text: root.title
//                font.bold: true
//                font.pixelSize: 14
//                color: "#383838"
//            }
//            Text {
//                text: root.description
//                font.pixelSize: 12
//                color: "#7a7a7a"
//            }
//        }
//    }
//    Row{
//        anchors { top: parent.top; topMargin: 30;right: parent.right ; rightMargin: 40 }
//        spacing: 20
//        //status picture
//        Common.StatusImage {
//            id: statusImage
//            visible: false
//            iconName: "yellow.png"
//            text: "未完成"
//            anchors.verticalCenter: parent.verticalCenter
//        }
//        Common.Button {
//            id: bitButton
//            width: 120
//            height: 39
//            text: root.btn_text
//            hoverimage: "green1.png"
//            anchors.verticalCenter: parent.verticalCenter
//            fontsize: 15
//            onClicked: {
//                resetBtn.visible = false;
//                if(root.check_flag)
//                {
//                //broswer cookies
//                 if (btn_flag == "cookies_scan") {
//                     //开始扫描时获取cookies
//                     cookies_signal("CookiesWork");
//                     if(root.null_flag == true) {
//                        root.state = "CookiesWorkEmpty";
//                         root.deleget_arrow=0;
//                         sessiondispatcher.showWarningDialog("友情提示：","扫描内容为空，不再执行清理！", mainwindow.pos.x, mainwindow.pos.y);
//                     }
//                     else if(root.null_flag == false)
//                     {
//                        root.state = "CookiesWork";
//                         root.deleget_arrow=1;
//                         toolkits.alertMSG("扫描完成！", mainwindow.pos.x, mainwindow.pos.y);
//                     }
//                 }
//                 else if (btn_flag == "cookies_work") {
//                     systemdispatcher.set_user_homedir_qt();
//                     systemdispatcher.clean_cookies_records_qt(systemdispatcher.get_cookies_args());
//                     root.deleget_arrow=1;
//                 }
//                }
//                else
//                    sessiondispatcher.showWarningDialog("友情提示：","对不起，您没有选择需要清理的项，请确认！", mainwindow.pos.x, mainwindow.pos.y);
//            }
//        }
//        SetBtn {
//            id: resetBtn
//            width: 12
//            height: 15
//            iconName: "revoke.png"
//            visible: false
//            anchors.verticalCenter: parent.verticalCenter
//            onClicked: {
//                resetBtn.visible = false;
//                firefoxModel.clear();
//                chrominumModel.clear();
//                root.state = "CookiesWorkAGAIN";
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
//        width: parent.width
//        Item {
//            width: parent.width
//            height: (root.firefoxNum + 1) * 40 + (root.chrominumNum + 1) * 40
//            Column {
//                spacing: 30
//                anchors.top: parent.top
//                anchors.topMargin: 20
//                anchors.left: parent.left
//                anchors.leftMargin: 30
//                //firefox
//                ItemTitle {
//                    id: firefoxTitle
//                    imageSource: "../img/toolWidget/cookies.png"
//                    itemTitle: "清理Cookies"
//                    detailstr: "清理Firefox浏览器自动保存的登录信息(Cookies)"
//                    sub_num: root.firefoxNum
//                    arrow_display: root.deleget_arrow
//                    flag: "firefox"
//                    onClicked: {
//                        yourselfListView.visible = !yourselfListView.visible;
//                    }
//                    onSendMainStatus: {
//                        //主checkbox的状态,以便实时改变所有子chechbox的状态
//                        if(flag == "firefox") {
//                            root.mainStatus1 = status;
//                        }
//                    }

////                    onSubpressed: {root.sub_num = hMark}
//                }
//                ListView {
//                    id: yourselfListView
//                    width: parent.width
//                    height: expanded ? yourselfListView.count * 40 : 0
//                    model: firefoxModel
//                    delegate: firefoxDelegate
//                    visible: false
//                }
//                //chrominum
//                ItemTitle {
//                    id: chrominumTitle
//                    imageSource: "../img/toolWidget/cookies.png"
//                    itemTitle: "清理Cookies"
//                    detailstr: "清理Chrominum浏览器自动保存的登录信息(Cookies)"
//                    sub_num: root.chrominumNum
//                    arrow_display: root.deleget_arrow
//                    flag: "chrominum"
//                    onClicked: {
//                        systemListView.visible = !systemListView.visible;
//                    }
//                    onSendMainStatus: {
//                        //主checkbox的状态,以便实时改变所有子chechbox的状态
//                        if(flag == "chrominum") {
//                            root.mainStatus2 = status;
//                        }
//                    }
////                    onSubpressed: {root.sub_num = hMark}
//                }
//                ListView {
//                    id: systemListView
//                    width: parent.width
//                    height: expanded ? systemListView.count * 40 : 0
//                    model: chrominumModel
//                    delegate: chrominumDelegate
//                    visible: false
//                }
//            }
//        }
//    }
//    states: [
//        State {
//            name: "CookiesWork"
//            PropertyChanges { target: bitButton; text:"开始清理"}
//            PropertyChanges { target: root; btn_flag: "cookies_work" }
//            PropertyChanges { target: statusImage; visible: true; iconName: "yellow.png"; text: "未完成"}
//        },
//        State {
//            name: "CookiesWorkAGAIN"
//            PropertyChanges { target: bitButton; text:"开始扫描" }
//            PropertyChanges { target: root; btn_flag: "cookies_scan" }
//            PropertyChanges { target: statusImage; visible: false }
//        },
//        State {
//            name: "CookiesWorkError"
//            PropertyChanges { target: bitButton; text:"开始扫描" }
//            PropertyChanges { target: root; btn_flag: "cookies_scan" }
//            PropertyChanges { target: statusImage; visible: true; iconName: "red.png"; text: "出现异常"}
//        },
//        State {
//            name: "CookiesWorkFinish"
//            PropertyChanges { target: bitButton; text:"开始扫描"}
//            PropertyChanges { target: root; btn_flag: "cookies_scan" }
//            PropertyChanges { target: statusImage; visible: true; iconName: "green.png"; text: "已完成"}
//        },
//        State {
//            name: "CookiesWorkEmpty"
//            PropertyChanges { target: bitButton; text:"开始扫描"}
//            PropertyChanges { target: root; btn_flag: "cookies_scan" }
//            PropertyChanges { target: statusImage; visible: false}
//        }
//    ]
//}











//-----------origianal
//Item {
//    id:root
//    width: parent.width
//    height: 435//420//340
//    property string btn_text: "开始扫描"
//    property string title: "清理浏览器登录信息,保护个人隐私"
//    property string description: "清理上网时留下的登录信息,目前仅支持Firefox浏览器"
//    property string btn_flag: "cookies_scan"
//    property ListModel listmodel: mainModel
//    property ListModel submodel: subModel
//    property int coo_sub_num: 0//number of subitem
//    property string work_result: ""
//    property int sub_num:coo_sub_num
//    property bool check_flag: true
//    property bool null_flag: false
//    property int deleget_arrow :0

//    signal cookies_signal(string cookies_msg);
//    onCookies_signal: {
//        if (cookies_msg == "CookiesWork") {
//            //get data of cookies
////            var cookies_data = systemdispatcher.scan_cookies_records_qt();
//            var cookies_data = sessiondispatcher.scan_cookies_records_qt();
//            if (cookies_data == "") {
//                root.null_flag = true;
//                if(statusImage.visible == true)
//                    statusImage.visible = false;
//            }
//            else {
//                root.null_flag = false;
//                statusImage.visible = true;
//            }
//            root.coo_sub_num = cookies_data.length;
//            systemdispatcher.clear_cookies_args();
//            subModel.clear();
//            var num = 0;
//            for (var i=0; i< cookies_data.length; i++) {
//                //sina.com.cn<2_2>10
//                var splitlist = cookies_data[i].split("<2_2>");
//                if (splitlist[0] == "") {
//                    num++;
//                }
//                else {
//                    subModel.append({"itemTitle": splitlist[0], "desc": "","number": splitlist[1] + "个Cookie"});
//                    systemdispatcher.set_cookies_args(splitlist[0]);
//                }
//            }

//            root.coo_sub_num -= num;
//            sub_num=coo_sub_num
//            if(sub_num!=0)
//                check_flag=true;
//            mainModel.clear();
//            mainModel.append({"itemTitle": "清理Cookies ( 发现" + root.coo_sub_num + "处记录 )",
//                             "picture": "../img/toolWidget/cookies.png",
//                             "detailstr": "清理Firefox浏览器自动保存的登录信息(Cookies)",
//                             "flags": "clear_cookies",
//                            "attributes":
//                                 [{"subItemTitle": "Cookies1"},
//                                 {"subItemTitle": "Cookies2"},
//                                 {"subItemTitle": "Cookies3"},
//                                 {"subItemTitle": "Cookies4"}]
//                             })

//        }
//    }


//    ListModel {
//        id: mainModel
//        ListElement {
//            itemTitle: "清理Cookies"
//            picture: "../img/toolWidget/cookies.png"
//            detailstr: "清理Firefox浏览器自动保存的登录信息(Cookies)"
//            flags: "clear_cookies"
//            attributes: [
//                ListElement { subItemTitle: "" }
//            ]
//        }
//    }

//    ListModel {
//        id: subModel
//        ListElement {itemTitle: ""; desc: ""; number: ""}
//    }


//    //信号绑定，绑定qt的信号finishCleanWork，该信号emit时触发onFinishCleanWork
//    Connections
//    {
////        target: sessiondispatcher
//        target: systemdispatcher
////         onFinishScanWork: {
//        //             if (btn_flag == "cookies_scan") {
//        ////                 titleBar.work_result = msg;
//        //                 titleBar.state = "CookiesWork";
//        //             }

////         }
//        onFinishCleanWorkError: {
//            if (btn_flag == "cookies_work") {
//                if (msg == "cookies") {
//                    root.work_result = msg;
//                    root.state = "CookiesWorkError";
//                    toolkits.alertMSG("清理出现异常！", mainwindow.pos.x, mainwindow.pos.y);
//                }
//            }
//         }
//        onFinishCleanWork: {
//            if (btn_flag == "cookies_work") {
//                if (msg == "") {
//                    resetBtn.visible = true;
//                }
//                else if (msg == "cookies") {
//                    root.work_result = msg;
//                    root.state = "CookiesWorkFinish";
//                    toolkits.alertMSG("清理完毕！", mainwindow.pos.x, mainwindow.pos.y);
//                    cookies_signal("CookiesWork");
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
////        height: 50
//        anchors { top: parent.top; topMargin: 20; left: parent.left; leftMargin: 27 }
//        Image {
//            id: refreshArrow
//            source: "../img/toolWidget/trace.png"
//            Behavior on rotation { NumberAnimation { duration: 200 } }
//        }
//        Column {
//            anchors.verticalCenter: parent.verticalCenter
//            spacing: 10
//            Text {
//                text: root.title
//                font.bold: true
//                font.pixelSize: 14
//                color: "#383838"
//            }
//            Text {
//                text: root.description
//                font.pixelSize: 12
//                color: "#7a7a7a"
//            }
//        }
//    }
//    Row{
//        anchors { top: parent.top; topMargin: 30;right: parent.right ; rightMargin: 40 }
//        spacing: 20
//        //status picture
////        Image {
////            id: statusImage
////            source: "../img/toolWidget/unfinish.png"
////            fillMode: "PreserveAspectFit"
////            smooth: true
////            anchors.verticalCenter: parent.verticalCenter
////        }
//        Common.StatusImage {
//            id: statusImage
//            visible: false
//            iconName: "yellow.png"
//            text: "未完成"
//            anchors.verticalCenter: parent.verticalCenter
//        }

//        Common.Button {
//            id: bitButton
//            width: 120
//            height: 39
//            text: root.btn_text
//            hoverimage: "green1.png"
//            anchors.verticalCenter: parent.verticalCenter
//            fontsize: 15
//            onClicked: {
//                resetBtn.visible = false;
//                if(root.check_flag)
//                {
//                //broswer cookies
//                 if (btn_flag == "cookies_scan") {
//                     cookies_signal("CookiesWork");
//                     if(root.null_flag == true) {
//                        root.state = "CookiesWorkEmpty";
//                         deleget_arrow=0;
//                         sessiondispatcher.showWarningDialog("友情提示：","扫描内容为空，不再执行清理！", mainwindow.pos.x, mainwindow.pos.y);
//                     }
//                     else if(root.null_flag == false)
//                     {
//                        root.state = "CookiesWork";
//                         deleget_arrow=1;
//                         toolkits.alertMSG("扫描完成！", mainwindow.pos.x, mainwindow.pos.y);
//                     }
//                 }
//                 else if (btn_flag == "cookies_work") {
//                     systemdispatcher.set_user_homedir_qt();
//                     systemdispatcher.clean_cookies_records_qt(systemdispatcher.get_cookies_args());
//                     deleget_arrow=1;
//                 }
//                }
//                else
//                    sessiondispatcher.showWarningDialog("友情提示：","对不起，您没有选择需要清理的项，请确认！", mainwindow.pos.x, mainwindow.pos.y);
//            }
//        }
//        SetBtn {
//            id: resetBtn
//            width: 12
//            height: 15
//            iconName: "revoke.png"
//            visible: false
//            anchors.verticalCenter: parent.verticalCenter
//            onClicked: {
//                resetBtn.visible = false;
//                subModel.clear();
//                root.state = "CookiesWorkAGAIN";
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
//        anchors.topMargin: 20//30
//        anchors.left:parent.left
//        anchors.leftMargin: 27
//        height: root.height -titlebar.height - 37//50
//        width: parent.width -27 -2
//        Item {
//            width: parent.width
//            height: (root.sub_num + 1) * 40 //450 + //this height must be higher than root.height, then the slidebar can display
//            //垃圾清理显示内容
//            ListView {
//                id: listView
//                height: parent.height
//                model: mainModel
//                delegate: Cleardelegate{
//                    sub_num:root.coo_sub_num;sub_model:subModel;btn_flag:root.btn_flag;arrow_display:deleget_arrow;
//                    delegate_flag: false
//                    onSubpressed: {root.sub_num = hMark}
//                    onCheckchanged: {root.check_flag = checkchange}
//                }
//                cacheBuffer: 1000
//                opacity: 1
//                spacing: 10
//                snapMode: ListView.NoSnap
//                boundsBehavior: Flickable.DragOverBounds
//                currentIndex: 0
//                preferredHighlightBegin: 0
//                preferredHighlightEnd: preferredHighlightBegin
//                highlightRangeMode: ListView.StrictlyEnforceRange
//            }
//        }//Item
//    }//ScrollArea

//    states: [
//        State {
//            name: "CookiesWork"
//             PropertyChanges { target: bitButton; text:"开始清理"}
//            PropertyChanges { target: root; btn_flag: "cookies_work" }
//            PropertyChanges { target: statusImage; visible: true; iconName: "yellow.png"; text: "未完成"}
//        },
//        State {
//            name: "CookiesWorkAGAIN"
//            PropertyChanges { target: bitButton; text:"开始扫描" }
//            PropertyChanges { target: root; btn_flag: "cookies_scan" }
//            PropertyChanges { target: statusImage; visible: false }
//        },
//        State {
//            name: "CookiesWorkError"
//            PropertyChanges { target: bitButton; text:"开始扫描" }
//            PropertyChanges { target: root; btn_flag: "cookies_scan" }
//            PropertyChanges { target: statusImage; visible: true; iconName: "red.png"; text: "出现异常"}
//        },
//        State {
//            name: "CookiesWorkFinish"
//            PropertyChanges { target: bitButton; text:"开始扫描"}
//            PropertyChanges { target: root; btn_flag: "cookies_scan" }
//            PropertyChanges { target: statusImage; visible: true; iconName: "green.png"; text: "已完成"}
//        },
//        State {
//            name: "CookiesWorkEmpty"
//            PropertyChanges { target: bitButton; text:"开始扫描"}
//            PropertyChanges { target: root; btn_flag: "cookies_scan" }
//            PropertyChanges { target: statusImage; visible: false}
//        }
//    ]
//}
