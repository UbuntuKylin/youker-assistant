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
    property string firefox_btn_text: qsTr("Start scanning")//开始扫描
    property string chromium_btn_text: qsTr("Start scanning")//开始扫描
    property bool firefox_reset: false//firefox重置按钮默认隐藏
    property bool chromium_reset: false//chromium重置按钮默认隐藏

    property string title: qsTr("Clean the login information and protect personal privacy")//清理浏览器登录信息,保护个人隐私
    property string description: qsTr("Clean up the login information, support Firefox and Chromium browser")//清理上网时留下的登录信息,支持Firefox和Chromium浏览器

    property string firefoxImage: "../img/toolWidget/cookies.png"
    property string firefoxTitle: qsTr("Clean Firefox's Cookies")//清理Firefox保存的Cookies
    property string firefoxDetail: qsTr("Clean up automatically saved logon information by Firefox browser(Cookies)")//清理Firefox浏览器自动保存的登录信息(Cookies)
    property string chromiumImage: "../img/toolWidget/chrome.png"
    property string chromiumTitle: qsTr("Clean Chromium's Cookies")//清理Chromium保存的Cookies
    property string chromiumDetail: qsTr("Clean up automatically saved logon information by Chromium browser(Cookies)")//清理Chromium浏览器自动保存的登录信息(Cookies)

    property string firefox_btn_flag: "cookies_scan"
    property string chromium_btn_flag: "cookies_scanc"
    property int firefoxNum: 0//扫描到firefox的有效子项的总数
    property int chromiumNum: 0//扫描到chromium的有效子项的总数
    property bool firefox_check_flag: true
    property bool chromium_check_flag: true
    property bool firefox_null_flag: false
    property bool chromium_null_flag: false
    property int firefox_arrow_show: 0
    property int chromium_arrow_show: 0
    property bool firefox_expanded: false
    property bool chromium_expanded: false
    property bool split_flag: false//是否切割每行内容
    property bool flag: false//记录是单个清理后重新获取数据（true），还是点击开始扫描后获取数据（false）
    property int space_value: 28//空间距离

    //数据
    ListModel { id: firefoxModel }
    ListModel { id: chromiumModel }

    //获取firefox的cookies
    function getDataOfFirefox() {
        var cookies_data = sessiondispatcher.cookies_scan_function_qt("f");
        if(cookies_data == "None") {//没有安装Firefox
            root.firefox_arrow_show = 0;//没有安装Firefox时隐藏伸缩图标
            //友情提示
            sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("No Firefox browser installed!"), mainwindow.pos.x, mainwindow.pos.y);
        }
        else {
            if (cookies_data.length == 0) {
                //如果扫描到的数据为空，把空标记置为true，未完成的状态图标隐藏。
                if(root.firefox_null_flag == true) {
                    root.firefox_null_flag = false;
                }
                root.firefox_null_flag = true;
            }
            else {
                //如果扫描到的数据不为空，把空标记置为false，未完成的状态图标显示。
                if(root.firefox_null_flag == false) {
                    root.firefox_null_flag = true;
                }
                root.firefox_null_flag = false;
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
                root.firefox_check_flag = true;//存在实际有效内容
            }
            else {
                root.firefox_check_flag = false;//无实际有效内容
            }
            //--------------------------------
            if(root.firefox_check_flag == false) {//无实际有效内容
                yourselfListView.visible = false;
                root.firefox_expanded = false;
                root.firefox_arrow_show = 0;//Firefox的cookies为空时隐藏伸缩图标

                if(root.flag == false) {//点击“开始扫描”按钮时的操作
                    //友情提示      扫描内容为空，不再执行清理！
                    sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Scanning content is empty, no longer to perform cleanup!"), mainwindow.pos.x, mainwindow.pos.y);
                }
                else {//清除操作完成后的操作
                    root.flag = false;
                    //此时若是通过一个一个单项清除导致的清空全部完成，则按钮状态改变、显示文字改变、重置按钮显示
                    root.firefox_btn_flag = "cookies_scan";//1206
                    root.firefox_btn_text = qsTr("Start scanning")//开始扫描//1206
                    root.firefox_reset = false;//1206
                }
            }
            else if(root.firefox_check_flag == true) {//存在实际有效内容
                root.firefox_arrow_show = 1;//Firefox的cookies不为空时显示伸缩图标
                if(flag == false) {//点击“开始扫描”按钮时的操作
                    toolkits.alertMSG(qsTr("Scan completed!"), mainwindow.pos.x, mainwindow.pos.y);//扫描完成！
                    //当真正扫描到内容时：按钮状态改变、显示文字改变、重置按钮显示
                    root.firefox_btn_flag = "cookies_work";//1206
                    root.firefox_btn_text = qsTr("All clean");//全部清理//1206
                    root.firefox_reset = true;//1206
                }
                else {//清除操作完成后的操作
                    root.flag = false;
                }
                //---------------
                yourselfListView.visible = true;
                root.firefox_expanded = true;
                root.firefox_arrow_show = 1;//传递给ListTitle.qml去隐藏伸展按钮
                scrollItem.height = yourselfListView.height + systemListView.height + 30*2 + root.space_value*4 + 20 + 10;
            }
        }
    }

    //获取chromium的cookies
    function getDataOfChromium() {
        var cookies_data = sessiondispatcher.cookies_scan_function_qt("c");
        if(cookies_data == "None") {//没有安装Chromium
            root.chromium_arrow_show = 0;
            //友情提示
            sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("No Chromium browser installed!"), mainwindow.pos.x, mainwindow.pos.y);
        }
        else {
            if (cookies_data.length === 0) {
                //如果扫描到的数据为空，把空标记置为true，未完成的状态图标隐藏。
                if(root.chromium_null_flag == true) {
                    root.chromium_null_flag = false;
                }
                root.chromium_null_flag = true;
            }
            else {
                //如果扫描到的数据不为空，把空标记置为false，未完成的状态图标显示。
                if(root.chromium_null_flag == false) {
                    root.chromium_null_flag = true;
                }
                root.chromium_null_flag = false;
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
                root.chromium_check_flag = true;//存在实际有效内容
            }
            else {
                root.chromium_check_flag = false;//无实际有效内容
            }

            //------------------------------------------
            if(root.chromium_check_flag == false) {//无实际有效内容
                systemListView.visible = false;
                root.chromium_expanded = false;
                root.chromium_arrow_show = 0;//Firefox的cookies为空时隐藏伸缩图标
                if(root.flag == false) {//点击“开始扫描”按钮时的操作
                    //友情提示      扫描内容为空，不再执行清理！
                    sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Scanning content is empty, no longer to perform cleanup!"), mainwindow.pos.x, mainwindow.pos.y);
                }
                else {//清除操作完成后的操作
                    root.flag = false;

                    //此时若是通过一个一个单项清除导致的清空全部完成，则按钮状态改变、显示文字改变、重置按钮显示
                    root.chromium_btn_flag = "cookies_scanc";//1206
                    root.chromium_btn_text = qsTr("Start scanning")//开始扫描//1206
                    root.chromium_reset = false;//1206
                }
            }
            else if(root.chromium_check_flag == true)//存在实际有效内容
            {
                root.chromium_arrow_show = 1;
                if(root.flag == false) {//点击“开始扫描”按钮时的操作
                    toolkits.alertMSG(qsTr("Scan completed!"), mainwindow.pos.x, mainwindow.pos.y);//扫描完成！
                    //当真正扫描到内容时：按钮状态改变、显示文字改变、重置按钮显示
                    root.chromium_btn_flag = "cookies_workc";//1206
                    root.chromium_btn_text = qsTr("All clean");//全部清理//1206
                    root.chromium_reset = true;//1206
                }
                else {//清除操作完成后的操作
                    root.flag = false;
                }
                systemListView.visible = true;
                root.chromium_expanded = true;
                root.chromium_arrow_show = 1;//传递给ListTitle.qml去隐藏伸展按钮
                scrollItem.height = yourselfListView.height + systemListView.height + 30*2 + root.space_value*4 + 20 + 10;
            }
            //------------------------------------------
        }
    }

    //委托
    Component{
        id: firefoxDelegate
        CookiesItem {
            split_status: root.split_flag//false
            text: itemTitle
            descript: desc
            size_num: number
            bgImage: ""
            browserFlag: "firefox"
            onClicked: {
                root.flag = true;
                root.getDataOfFirefox();
            }
        }
    }
    Component{
        id: chromiumDelegate
        CookiesItem {
            split_status: root.split_flag//false
            text: itemTitle
            descript: desc
            size_num: number
            bgImage: ""
            browserFlag: "chromium"
            onClicked: {//清理完单个数据后，再次扫描刷新数据
                root.flag = true;
                root.getDataOfChromium();
            }
        }
    }

//    quitCleanWork

    //信号绑定，绑定qt的信号finishCleanWork，该信号emit时触发onFinishCleanWork
    Connections
    {
        target: systemdispatcher
        onQuitCleanWork: {//用户在policykit验证时直接关闭验证或者点击取消
            if (msg == "firefox") {
//                root.firefox_reset = true;//1206
                toolkits.alertMSG(qsTr("Cleanup interrupted!"), mainwindow.pos.x, mainwindow.pos.y);//清理中断了！
            }
            else if (msg == "chromium") {
//                root.chromium_reset = true;//1206
                toolkits.alertMSG(qsTr("Cleanup interrupted!"), mainwindow.pos.x, mainwindow.pos.y);//清理中断了！
            }
        }

        onFinishCleanWorkError: {//清理过程中出错
            if (msg == "firefox") {
                if (root.firefox_btn_flag == "cookies_work") {
                    toolkits.alertMSG(qsTr("Exception occurred!"), mainwindow.pos.x, mainwindow.pos.y);//清理出现异常！
                }
            }
            else if (msg == "chromium") {
                if (root.chromium_btn_flag == "cookies_workc") {
                    toolkits.alertMSG(qsTr("Exception occurred!"), mainwindow.pos.x, mainwindow.pos.y);//清理出现异常！
                }
            }
        }

        onFinishCleanWork: {//清理正常完成
            if (msg == "firefox") {
                if (root.firefox_btn_flag == "cookies_work") {
                    //清理完毕后重新获取cookies
                    root.flag = true;
                    root.getDataOfFirefox();
                    toolkits.alertMSG(qsTr("Cleaned"), mainwindow.pos.x, mainwindow.pos.y);//清理完毕！
                }
            }
            else if (msg == "chromium") {
                if (root.chromium_btn_flag == "cookies_workc") {
                    //清理完毕后重新获取cookies
                    root.flag = true;
                    root.getDataOfChromium();
                    toolkits.alertMSG(qsTr("Cleaned"), mainwindow.pos.x, mainwindow.pos.y);//清理完毕！
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
                wrapMode: Text.WordWrap
                font.bold: true
                font.pixelSize: 14
                color: "#383838"
            }
            Text {
                id: text
                width: 700
                text: root.description
                wrapMode: Text.WordWrap
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
//            height: root.firefoxNum * 30 + root.chromiumNum * 30 + 30*2 + root.space_value*4 + 20 + 10
            height: 30*2 + root.space_value*4 + 20 + 10

            Column {
                id: broswerColumn
                spacing: root.space_value
                anchors {
                    top: parent.top
                    topMargin: 20
                    left: parent.left
                    leftMargin: 30
                }
                //firefox
                ListTitle {
                    id: firefoxTitle
                    imageSource: root.firefoxImage
                    itemTitle: root.firefoxTitle
                    detailstr: root.firefoxDetail
                    arrow_display: root.firefox_arrow_show//为0时隐藏伸缩图标，为1时显示伸缩图标
                    flag: "firefox"

                    title: root.firefox_btn_text
                    resetStatus: root.firefox_reset

                    btnFlag: root.firefox_btn_flag
//                    nullFlag: root.firefox_null_flag
                    expanded: root.firefox_expanded//firefox_expanded为true时，箭头向下，内容展开;firefox_expanded为false时，箭头向上，内容收缩
                    onClicked: {
                        //点击伸缩图标时，说明肯定是有内容的，设置其下内容的隐藏/显示以及高度
                        yourselfListView.visible = !yourselfListView.visible;
                        scrollItem.height = yourselfListView.height + systemListView.height + 30*2 + root.space_value*4 + 20 + 10;
                    }
                    onSendBrowserType: {
                        if(flag == "firefox") {
                            if(status == "reset") {//点击重置按钮，清空数据
                                firefoxModel.clear();
                                root.firefox_btn_flag = "cookies_scan";//1206
                                root.firefox_btn_text = qsTr("Start scanning")//开始扫描//1206
                                root.firefox_reset = false;//1206
                                if(root.firefox_expanded == true) {
                                    root.firefox_expanded = false;//1、先传递给ListTitle.qml的伸缩值设为默认的false
                                }
                                root.firefox_arrow_show = 0;//2、然后传递给ListTitle.qml去隐藏伸展按钮
                                if(yourselfListView.visible == true) {
                                    yourselfListView.visible = false;//3、隐藏扩展内容
                                }
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
                                        systemdispatcher.set_user_homedir_qt();
                                        systemdispatcher.cookies_clean_records_function_qt("firefox");
                                    }
                                    else {
                                        sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Sorry, you have no choice to clean up the items, please confirm!"), mainwindow.pos.x, mainwindow.pos.y);
                                    }
                                }
                            }
                        }
                    }
                }
                ListView {
                    id: yourselfListView
                    width: parent.width
                    height: root.firefox_expanded ? yourselfListView.count * 30 : 0
                    model: firefoxModel
                    delegate: firefoxDelegate
                    visible: false
                }
                //chromium
                ListTitle {
                    id: chromiumTitle
                    imageSource: root.chromiumImage
                    itemTitle: root.chromiumTitle
                    detailstr: root.chromiumDetail
                    arrow_display: root.chromium_arrow_show//为0时隐藏伸缩图标，为1时显示伸缩图标
                    flag: "chromium"

                    title: root.chromium_btn_text
                    resetStatus: root.chromium_reset

                    btnFlag: root.chromium_btn_flag
//                    nullFlag: root.chromium_null_flag
                    expanded: root.chromium_expanded//chromium_expanded为true时，箭头向下，内容展开;chromium_expanded为false时，箭头向上，内容收缩
                    onClicked: {//伸缩箭头被点击
                        systemListView.visible = !systemListView.visible;
                        root.chromium_expanded = !root.chromium_expanded;
                        scrollItem.height = yourselfListView.height + systemListView.height + 30*2 + root.space_value*4 + 20 + 10;
                    }
                    onSendBrowserType: {
                        if(status == "reset") {//点击重置按钮，清空数据
                            chromiumModel.clear();
                            root.chromium_btn_flag = "cookies_scanc";//1206
                            root.chromium_btn_text = qsTr("Start scanning")//开始扫描//1206
                            root.chromium_reset = false;//1206
                            if(root.chromium_expanded == true) {
                                root.chromium_expanded = false;//1、先传递给ListTitle.qml的伸缩值设为默认的false
                            }
                            root.chromium_arrow_show = 0;//2、然后传递给ListTitle.qml去隐藏伸展按钮
                            if(systemListView.visible == true) {
                                systemListView.visible = false;//3、隐藏扩展内容
                            }
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
                                    systemdispatcher.set_user_homedir_qt();
                                    systemdispatcher.cookies_clean_records_function_qt("chromium");
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
                    height: root.chromium_expanded ? systemListView.count * 30 : 0
                    model: chromiumModel
                    delegate: chromiumDelegate
                    visible: false
                }
            }//Column
        }
    }
}
