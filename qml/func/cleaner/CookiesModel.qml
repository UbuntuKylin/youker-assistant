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

Item {
    id:cookiespage
    width: parent.width; height: 437

    property string title: qsTr("Cleanup browser Cookies information, to protect your privacy")//清理浏览器 Cookies 信息，保护个人隐私
    property string description: qsTr("Clean up user login information, support Firefox and Chromium browser")//清理用户登陆网站信息, 支持 Firefox 和 Chromium 浏览器
    property bool firefoxResultFlag: false//判断扫描后的实际内容是否为空，为空时为false，有内容时为true
    property bool chromiumResultFlag: false//判断扫描后的实际内容是否为空，为空时为false，有内容时为true
    property int firefoxNum: 0//扫描后得到的apt的项目总数
    property int chromiumNum: 0//扫描后得到的apt的项目总数
    property bool splitFlag: true//传递给ClearDelegate.qml,为true时切割字符串，为false时不切割字符串
    property bool flag: false//记录是清理后重新获取数据（true），还是点击开始扫描后获取数据（false）
    property int spaceValue: 20
    property int firefox_arrow_show: 0//传递给CookiesDelegate.qml是否显示伸缩图标，为1时显示，为0时隐藏
    property int chromium_arrow_show: 0//传递给CookiesDelegate.qml是否显示伸缩图标，为1时显示，为0时隐藏
    property bool firefox_expanded: false//传递给CookiesDelegate.qml,觉得伸缩图标是扩展还是收缩
    property bool chromium_expanded: false//传递给CookiesDelegate.qml,觉得伸缩图标是扩展还是收缩
    property bool firefox_maincheck: true
    property bool chromium_maincheck: true
    property bool firefox_showNum: false//决定firefox的扫描结果数是否显示
    property bool chromium_showNum: false//决定chromium的扫描结果数是否显示
    ListModel { id: firefoxmainModel }
    ListModel { id: firefoxsubModel }
    ListModel { id: chromiummainModel }
    ListModel { id: chromiumsubModel }
    property string firefox_btn_text: qsTr("Start scanning")//开始扫描
    property string chromium_btn_text: qsTr("Start scanning")//开始扫描
    property bool firefox_reset: false//firefox重置按钮默认隐藏
    property bool chromium_reset: false//chromium重置按钮默认隐藏
    property string firefox_btn_flag: "cookies_scan"//扫描或者清理的标记
    property string chromium_btn_flag: "cookies_scanc"//扫描或者清理的标记
    property int item_height: 30

    Connections
    {
        target: sessiondispatcher
        onAppendCookiesContentToModel: {
            //QString flag, QString domain, QString num
            if(flag == "firefox") {
                firefoxsubModel.append({"itemTitle": domain, "desc": "", "number": num, "index": cookiespage.firefoxNum});
                cookiespage.firefoxNum += 1;
            }
            else if(flag == "chromium") {
                chromiumsubModel.append({"itemTitle": domain, "desc": "", "number": num, "index": cookiespage.chromiumNum});
                cookiespage.chromiumNum += 1;
            }
        }
        onTellQMLCookiesOver: {
            if (cookiesFlag == "funinstall") {
                //友情提示    没有安装 Firefox！
                sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Firefox is not installed!"));
            }
            else if (cookiesFlag == "cuninstall") {
                //友情提示        没有安装 Chromium！
                sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Chromium is not installed!"));
            }
            else {
                if (cookiesFlag == "firefox") {
                    if(cookiespage.firefoxNum != 0) {
                        cookiespage.firefoxResultFlag = true;//扫描的实际有效内容存在
                        firefoxmainModel.clear();
                        //清理 Firefox 保存的 Cookies                清理 Firefox 浏览器自动保存的登录信息 (Cookies)
                        firefoxmainModel.append({
                                         "itemTitle": qsTr("Cleanup the Cookies saving in Firefox"),
                                         "picture": "../../img/toolWidget/firefox.png"})
//                                       "detailstr": qsTr("Clean up automatically saved logon information by Firefox browser(Cookies)")})
                    }
                    else {
                        cookiespage.firefoxResultFlag = false;//扫描的实际有效内容不存在
                    }
                    if(cookiespage.firefoxResultFlag == false) {
                        cookiespage.firefox_expanded = false;//伸缩箭头不扩展
                        cookiespage.firefox_arrow_show = 0;//伸缩箭头不显示
                        cookiespage.firefox_showNum = false;
                        if(cookiespage.flag == false) {//点击扫描时的获取数据，此时显示该对话框
                            //友情提示：      扫描内容为空，无需清理！
                            sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("The scan results are empty, no need to clean up !"));
                        }
                        else {//清理apt后的重新获取数据，此时不需要显示对话框
                            cookiespage.flag = false;
                        }
                        cookiespage.firefox_btn_flag = "cookies_scan";//1206
                        cookiespage.firefox_btn_text = qsTr("Start scanning")//开始扫描//1206
                        cookiespage.firefox_reset = false;//1206
                        if(cookiespage.chromium_expanded) {
                            scrollItem.height = cookiespage.item_height + (cookiespage.chromiumNum + 1) * cookiespage.item_height + cookiespage.spaceValue*4;
                        }
                        else {
                            scrollItem.height = 2 * cookiespage.item_height + cookiespage.spaceValue*4;
                        }
                    }
                    else if(cookiespage.firefoxResultFlag == true) {
                        cookiespage.firefox_expanded = true;//伸缩箭头扩展
                        cookiespage.firefox_arrow_show = 1;//伸缩箭头显示
                        cookiespage.firefox_showNum = true;
                        if(cookiespage.flag == false) {//点击扫描时的获取数据，此时显示该对话框
                            toolkits.alertMSG(qsTr("Scan completed!"));//扫描完成！
                        }
                        else {//清理software后的重新获取数据，此时不需要显示对话框
                            cookiespage.flag = false;
                        }

                        //当真正扫描到内容时：按钮状态改变、显示文字改变、重置按钮显示
                        cookiespage.firefox_btn_flag = "cookies_work";//1206
                        cookiespage.firefox_btn_text = qsTr("All cleanup");//全部清理//1206
                        cookiespage.firefox_reset = true;//1206
                        if(cookiespage.chromium_expanded) {
                            scrollItem.height = (cookiespage.firefoxNum + 1) * cookiespage.item_height + (cookiespage.chromiumNum + 1) * cookiespage.item_height + cookiespage.spaceValue*4;
                        }
                        else {
                            scrollItem.height = (cookiespage.firefoxNum + 1) * cookiespage.item_height + cookiespage.item_height + cookiespage.spaceValue*4;
                        }
                    }
                }
                else if (cookiesFlag == "chromium") {
                    if(cookiespage.chromiumNum != 0) {
                        cookiespage.chromiumResultFlag = true;//扫描的实际有效内容存在
                        chromiummainModel.clear();
                        //清理 Chromium 保存的 Cookies             清理 Chromium 浏览器自动保存的登录信息 (Cookies)
                        chromiummainModel.append({
                                         "itemTitle": qsTr("Cleanup the Cookies saving in Chromium"),
                                         "picture": "../../img/toolWidget/chromium.png"})
//                                       "detailstr": qsTr("Clean up automatically saved logon information by Chromium browser(Cookies)")})
                    }
                    else {
                        cookiespage.chromiumResultFlag = false;//扫描的实际有效内容不存在
                    }
                    if(cookiespage.chromiumResultFlag == false) {
                        cookiespage.chromium_expanded = false;//伸缩箭头不扩展
                        cookiespage.chromium_arrow_show = 0;//伸缩箭头不显示
                        cookiespage.chromium_showNum = false;

                        if(cookiespage.flag == false) {//点击扫描时的获取数据，此时显示该对话框
                            //友情提示：      扫描内容为空，无需清理！
                            sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("The scan results are empty, no need to clean up !"));
                        }
                        else {//清理apt后的重新获取数据，此时不需要显示对话框
                            cookiespage.flag = false;
                        }

                        cookiespage.chromium_btn_flag = "cookies_scanc";//1206
                        cookiespage.chromium_btn_text = qsTr("Start scanning")//开始扫描
                        cookiespage.chromium_reset = false;//1206
                        if(cookiespage.firefox_expanded) {
                            scrollItem.height = cookiespage.item_height + (cookiespage.firefoxNum + 1) * cookiespage.item_height + cookiespage.spaceValue*4;
                        }
                        else {
                            scrollItem.height = 2 * cookiespage.item_height + cookiespage.spaceValue*4;
                        }
                    }
                    else if(cookiespage.chromiumResultFlag == true) {
                        cookiespage.chromium_expanded = true;//伸缩箭头扩展
                        cookiespage.chromium_arrow_show = 1;//伸缩箭头显示
                        cookiespage.chromium_showNum = true;

                        if(cookiespage.flag == false) {//点击扫描时的获取数据，此时显示该对话框
                            toolkits.alertMSG(qsTr("Scan completed!"));//扫描完成！
                        }
                        else {//清理software后的重新获取数据，此时不需要显示对话框
                            cookiespage.flag = false;
                        }
                        //当真正扫描到内容时：按钮状态改变、显示文字改变、重置按钮显示
                        cookiespage.chromium_btn_flag = "cookies_workc";//1206
                        cookiespage.chromium_btn_text = qsTr("All cleanup");//全部清理
                        cookiespage.chromium_reset = true;//1206
                        if(cookiespage.firefox_expanded) {
                            scrollItem.height = (cookiespage.firefoxNum + 1) * cookiespage.item_height + (cookiespage.chromiumNum + 1) * cookiespage.item_height + cookiespage.spaceValue*4;
                        }
                        else {
                            scrollItem.height = (cookiespage.chromiumNum + 1) * cookiespage.item_height + cookiespage.item_height + cookiespage.spaceValue*4;
                        }
                    }
                }
            }
        }
    }


    Component.onCompleted: {
        //清理 Firefox 保存的 Cookies                清理 Firefox 浏览器自动保存的登录信息 (Cookies)
        firefoxmainModel.append({
                         "itemTitle": qsTr("Cleanup the Cookies saving in Firefox"),
                         "picture": "../../img/toolWidget/firefox.png"})
//                         "detailstr": qsTr("Clean up automatically saved logon information by Firefox browser(Cookies)")})
        //清理 Chromium 保存的 Cookies             清理 Chromium 浏览器自动保存的登录信息 (Cookies)
        chromiummainModel.append({
                         "itemTitle": qsTr("Cleanup the Cookies saving in Chromium"),
                         "picture": "../../img/toolWidget/chromium.png"})
//                         "detailstr": qsTr("Clean up automatically saved logon information by Chromium browser(Cookies)")})
    }

    //信号绑定，绑定qt的信号finishCleanWork，该信号emit时触发onFinishCleanWork
    Connections
    {
        target: systemdispatcher
        onQuitCleanWork: {//用户在policykit验证时直接关闭验证或者点击取消
            if (msg == "firefox") {
                toolkits.alertMSG(qsTr("Cleanup interrupted!"));//清理中断！
            }
            else if (msg == "chromium") {
                toolkits.alertMSG(qsTr("Cleanup interrupted!"));//清理中断！
            }
        }

        onFinishCleanWorkError: {//清理过程中出错
            if (msg == "firefox") {
                if (cookiespage.firefox_btn_flag == "cookies_work") {
                    toolkits.alertMSG(qsTr("Cleanup abnormal!"));//清理出现异常！
                }
            }
            else if (msg == "chromium") {
                if (cookiespage.chromium_btn_flag == "cookies_workc") {
                    toolkits.alertMSG(qsTr("Cleanup abnormal!"));//清理出现异常！
                }
            }
        }

        onFinishCleanWork: {//清理正常完成
            if (msg == "firefox") {
                if (cookiespage.firefox_btn_flag == "cookies_work") {
//                    systemdispatcher.clear_cookies_args();
                    firefoxsubModel.clear();//内容清空
                    firefoxmainModel.clear();
                    //清理 Firefox 保存的 Cookies                清理 Firefox 浏览器自动保存的登录信息 (Cookies)
                    firefoxmainModel.append({
                                     "itemTitle": qsTr("Cleanup the Cookies saving in Firefox"),
                                     "picture": "../../img/toolWidget/firefox.png",
                                     "detailstr": qsTr("Clean up automatically saved logon information by Firefox browser(Cookies)")})
                    cookiespage.firefox_expanded = false;//伸缩箭头不扩展
                    cookiespage.firefox_arrow_show = 0;//伸缩箭头不显示
                    cookiespage.firefox_showNum = false;
                    cookiespage.firefox_btn_flag = "cookies_scan";//1206
                    cookiespage.firefox_btn_text = qsTr("Start scanning")//开始扫描//1206
                    cookiespage.firefox_reset = false;//1206
                    cookiespage.firefoxNum = 0;//隐藏滑动条
                    if(cookiespage.chromium_expanded) {
                        scrollItem.height = cookiespage.item_height + (cookiespage.chromiumNum + 1) * cookiespage.item_height + cookiespage.spaceValue*4;
                    }
                    else {
                        scrollItem.height = 2 * cookiespage.item_height + cookiespage.spaceValue*4;
                    }
                    toolkits.alertMSG(qsTr("Cleared"));//清理完毕！
                }
            }
            else if (msg == "chromium") {
                if (cookiespage.chromium_btn_flag == "cookies_workc") {
                    chromiumsubModel.clear();//内容清空
                    chromiummainModel.clear();
                    //清理 Chromium 保存的 Cookies             清理 Chromium 浏览器自动保存的登录信息 (Cookies)
                    chromiummainModel.append({
                                     "itemTitle": qsTr("Cleanup the Cookies saving in Chromium"),
                                     "picture": "../../img/toolWidget/chromium.png"})
//                                     "detailstr": qsTr("Clean up automatically saved logon information by Chromium browser(Cookies)")})
                    cookiespage.chromium_expanded = false;//伸缩箭头不扩展
                    cookiespage.chromium_arrow_show = 0;//伸缩箭头不显示
                    cookiespage.chromium_showNum = false;
                    cookiespage.chromium_btn_flag = "cookies_scanc";//1206
                    cookiespage.chromium_btn_text = qsTr("Start scanning")//开始扫描//1206
                    cookiespage.chromium_reset = false;//1206
                    cookiespage.chromiumNum = 0;//隐藏滑动条
                    if(cookiespage.firefox_expanded) {
                        scrollItem.height = cookiespage.item_height + (cookiespage.firefoxNum + 1) * cookiespage.item_height + cookiespage.spaceValue*4;
                    }
                    else {
                        scrollItem.height = 2 * cookiespage.item_height + cookiespage.spaceValue*4;
                    }
                    toolkits.alertMSG(qsTr("Cleared"));//清理完毕！
                }
            }
        }
    }

    //背景
    Image {
        source: "../../img/skin/bg-middle.png"
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
            source: "../../img/toolWidget/cookies-bg.png"
            Behavior on rotation { NumberAnimation { duration: 200 } }
        }
        Column {
            anchors.verticalCenter: parent.verticalCenter
            spacing: 10
            Text {
                width: 500
                text: cookiespage.title
                wrapMode: Text.WordWrap
                font.bold: true
                font.pixelSize: 14
                color: "#383838"
            }
            Text {
                width: 500
                text: cookiespage.description
                wrapMode: Text.WordWrap
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

    Common.ScrollArea {
        frame:false
        anchors.top: titlebar.bottom
        anchors.topMargin: 30
        anchors.left:parent.left
//        anchors.leftMargin: 27
        height: cookiespage.height -titlebar.height - 47
        width: parent.width -2//parent.width - 27 -2
        Item {
            id: scrollItem
            width: parent.width
            height: cookiespage.item_height*2 + cookiespage.spaceValue*2*2
            Column {
                spacing: cookiespage.spaceValue*2
                //垃圾清理显示内容
                ListView {
                    id: aptListView
                    width: parent.width
                    height: cookiespage.firefox_expanded ? (cookiespage.firefoxNum + 1) * cookiespage.item_height : cookiespage.item_height
                    model: firefoxmainModel
                    delegate: CookiesDelegate{
                        sub_num: cookiespage.firefoxNum
                        sub_model: firefoxsubModel
                        btn_flag: cookiespage.firefox_btn_flag
                        flag: "firefox"
                        actionTitle: cookiespage.firefox_btn_text
                        resetStatus: cookiespage.firefox_reset
                        showNum: cookiespage.firefox_showNum
                        arrow_display: cookiespage.firefox_arrow_show//为0时隐藏伸缩图标，为1时显示伸缩图标
                        expanded: cookiespage.firefox_expanded//firefox_expanded为true时，箭头向下，内容展开;firefox_expanded为false时，箭头向上，内容收缩
                        delegate_flag: cookiespage.splitFlag
                        onSendBrowserType: {
                            if(browserFlag == "firefox") {
                                if(status == "reset") {//点击重置按钮，清空数据
                                    firefoxsubModel.clear();
                                    cookiespage.firefoxNum = 0;
                                    cookiespage.firefox_btn_flag = "cookies_scan";//1206
                                    cookiespage.firefox_btn_text = qsTr("Start scanning")//开始扫描//1206
                                    cookiespage.firefox_reset = false;//1206
                                    if(cookiespage.firefox_expanded == true) {
                                        cookiespage.firefox_expanded = false;//1、先传递给CookiesDelegate.qml的伸缩值设为默认的false
                                    }
                                    cookiespage.firefox_arrow_show = 0;//2、然后传递给CookiesDelegate.qml去隐藏伸展按钮
                                    cookiespage.firefox_showNum = false;//隐藏扫描的数目
                                    if(cookiespage.chromium_expanded) {
                                        scrollItem.height = cookiespage.item_height + (cookiespage.chromiumNum + 1) * cookiespage.item_height + cookiespage.spaceValue*4;
                                    }
                                    else {
                                        scrollItem.height = 2 * cookiespage.item_height + cookiespage.spaceValue*4;
                                    }
                                }
                                else if(status == "rescan") {//点击重新扫描按钮
                                    firefoxsubModel.clear();
                                    cookiespage.firefoxNum = 0;
                                    cookiespage.firefox_btn_flag = "cookies_scan";//1206
                                    cookiespage.firefox_btn_text = qsTr("Start scanning")//开始扫描//1206
                                    cookiespage.firefox_reset = false;//1206
                                    if(cookiespage.firefox_expanded == true) {
                                        cookiespage.firefox_expanded = false;//1、先传递给CookiesDelegate.qml的伸缩值设为默认的false
                                    }
                                    cookiespage.firefox_arrow_show = 0;//2、然后传递给CookiesDelegate.qml去隐藏伸展按钮
                                    cookiespage.firefox_showNum = false;//隐藏扫描的数目
                                    cookiespage.flag = false;
                                    sessiondispatcher.cookies_scan_function_qt("firefox");
//                                    cookiespage.getDataOfFirefox();
                                }
                                else if(status == "refresh") {//清理完某个子项后自动刷新列表
                                    console.log("---*****2222------");
                                    firefoxsubModel.clear();
                                    cookiespage.firefoxNum = 0;
                                    cookiespage.firefox_btn_flag = "cookies_scan";//1206
                                    cookiespage.firefox_btn_text = qsTr("Start scanning")//开始扫描//1206
                                    cookiespage.firefox_reset = false;//1206
                                    if(cookiespage.firefox_expanded == true) {
                                        cookiespage.firefox_expanded = false;//1、先传递给CookiesDelegate.qml的伸缩值设为默认的false
                                    }
                                    cookiespage.firefox_arrow_show = 0;//2、然后传递给CookiesDelegate.qml去隐藏伸展按钮
                                    cookiespage.firefox_showNum = false;//隐藏扫描的数目
                                    cookiespage.flag = true;
                                    sessiondispatcher.cookies_scan_function_qt("firefox");
//                                    cookiespage.getDataOfFirefox();
                                }
                                else {
                                    cookiespage.firefox_btn_flag = status;
                                    if (cookiespage.firefox_btn_flag == "cookies_scan") {
//                                        console.log("scan---f......");
                                        //开始扫描时获取cookies
                                        cookiespage.firefoxNum = 0;
                                        cookiespage.flag = false;
                                        sessiondispatcher.cookies_scan_function_qt("firefox");
//                                        cookiespage.getDataOfFirefox();
                                    }
                                    else if (cookiespage.firefox_btn_flag == "cookies_work") {
//                                        if(cookiespage.firefox_check_flag) {
                                            console.log("clean---f......");
                                            //开始清理cookies
                                            systemdispatcher.set_user_homedir_qt();
                                            systemdispatcher.cookies_clean_records_function_qt("firefox");
                                    }
                                }
                            }
                        }
                        onBrowserArrowClicked: {
                            if(browserFlag == "firefox") {
                                if(expand_flag == true) {
                                    cookiespage.firefox_expanded = true;
                                    if(cookiespage.chromium_expanded == true) {
                                        scrollItem.height = (cookiespage.firefoxNum + 1) * cookiespage.item_height + (cookiespage.chromiumNum + 1) * cookiespage.item_height + cookiespage.spaceValue*4;
                                    }
                                    else {
                                        scrollItem.height = (cookiespage.firefoxNum + 2) * cookiespage.item_height + cookiespage.spaceValue*4;
                                    }
                                }
                                else {
                                    cookiespage.firefox_expanded = false;
                                    if(cookiespage.chromium_expanded == true) {
                                        scrollItem.height = (cookiespage.chromiumNum + 2) * cookiespage.item_height + cookiespage.spaceValue*4;
                                    }
                                    else {
                                        scrollItem.height = 2* cookiespage.item_height + cookiespage.spaceValue*4;
                                    }
                                }
                            }
                        }
                    }
                    cacheBuffer: 1000
                    opacity: 1
//                    spacing: 10
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
                    height: cookiespage.chromium_expanded ? (cookiespage.chromiumNum + 1) * cookiespage.item_height : cookiespage.item_height
                    model: chromiummainModel
                    delegate: CookiesDelegate{
                        sub_num: cookiespage.chromiumNum
                        sub_model: chromiumsubModel
                        btn_flag: cookiespage.chromium_btn_flag
                        showNum: cookiespage.chromium_showNum
                        flag: "chromium"
                        actionTitle: cookiespage.chromium_btn_text
                        resetStatus: cookiespage.chromium_reset
                        arrow_display: cookiespage.chromium_arrow_show//为0时隐藏伸缩图标，为1时显示伸缩图标
                        expanded: cookiespage.chromium_expanded//firefox_expanded为true时，箭头向下，内容展开;firefox_expanded为false时，箭头向上，内容收缩
                        delegate_flag: cookiespage.splitFlag
                        onSendBrowserType: {
                            if(browserFlag == "chromium") {
                                if(status == "reset") {//点击重置按钮，清空数据
                                    chromiumsubModel.clear();
                                    cookiespage.chromiumNum = 0;
                                    cookiespage.chromium_btn_flag = "cookies_scanc";//1206
                                    cookiespage.chromium_btn_text = qsTr("Start scanning")//开始扫描//1206
                                    cookiespage.chromium_reset = false;//1206
                                    if(cookiespage.chromium_expanded == true) {
                                        cookiespage.chromium_expanded = false;//1、先传递给CookiesDelegate.qml的伸缩值设为默认的false
                                    }
                                    cookiespage.chromium_arrow_show = 0;//2、然后传递给CookiesDelegate.qml去隐藏伸展按钮
                                    cookiespage.chromium_showNum = false;//隐藏扫描的数目
                                    if(cookiespage.firefox_expanded) {
                                        scrollItem.height = cookiespage.item_height + (cookiespage.firefoxNum + 1) * cookiespage.item_height + cookiespage.spaceValue*4;
                                    }
                                    else {
                                        scrollItem.height = 2 * cookiespage.item_height + cookiespage.spaceValue*4;
                                    }
                                }
                                else if(status == "rescan") {
                                    chromiumsubModel.clear();
                                    cookiespage.chromiumNum = 0;
                                    cookiespage.chromium_btn_flag = "cookies_scanc";//1206
                                    cookiespage.chromium_btn_text = qsTr("Start scanning")//开始扫描//1206
                                    cookiespage.chromium_reset = false;//1206
                                    if(cookiespage.chromium_expanded == true) {
                                        cookiespage.chromium_expanded = false;//1、先传递给CookiesDelegate.qml的伸缩值设为默认的false
                                    }
                                    cookiespage.chromium_arrow_show = 0;//2、然后传递给CookiesDelegate.qml去隐藏伸展按钮
                                    cookiespage.chromium_showNum = false;//隐藏扫描的数目
                                    cookiespage.flag = false;
                                    sessiondispatcher.cookies_scan_function_qt("chromium");
//                                    cookiespage.getDataOfChromium();
                                }
                                else if(status == "refresh") {//清理完某个子项后自动刷新列表
                                    chromiumsubModel.clear();
                                    cookiespage.chromiumNum = 0;
                                    cookiespage.chromium_btn_flag = "cookies_scanc";//1206
                                    cookiespage.chromium_btn_text = qsTr("Start scanning")//开始扫描//1206
                                    cookiespage.chromium_reset = false;//1206
                                    if(cookiespage.chromium_expanded == true) {
                                        cookiespage.chromium_expanded = false;//1、先传递给CookiesDelegate.qml的伸缩值设为默认的false
                                    }
                                    cookiespage.chromium_arrow_show = 0;//2、然后传递给CookiesDelegate.qml去隐藏伸展按钮
                                    cookiespage.chromium_showNum = false;//隐藏扫描的数目
                                    cookiespage.flag = true;
                                    sessiondispatcher.cookies_scan_function_qt("chromium");
//                                    cookiespage.getDataOfChromium();
                                }
                                else {
                                    cookiespage.chromium_btn_flag = status;
                                    if (cookiespage.chromium_btn_flag == "cookies_scanc") {
//                                        console.log("scan---c......");
                                        //开始扫描时获取cookies
                                        cookiespage.flag = false;
                                        cookiespage.chromiumNum = 0;
                                        sessiondispatcher.cookies_scan_function_qt("chromium");
//                                        cookiespage.getDataOfChromium();
                                    }
                                    else if (cookiespage.chromium_btn_flag == "cookies_workc") {
//                                        if(cookiespage.chromium_check_flag)
//                                        {
                                            console.log("clean---c......");
                                            //开始清理cookies
                                            systemdispatcher.set_user_homedir_qt();
                                            systemdispatcher.cookies_clean_records_function_qt("chromium");
                                    }
                                }
                            }
                        }
                        onBrowserArrowClicked: {
                            if(browserFlag == "chromium") {//1212
                                if(expand_flag == true) {
                                    cookiespage.chromium_expanded = true;
                                    if(cookiespage.firefox_expanded == true) {
                                        scrollItem.height = (cookiespage.firefoxNum + 1) * cookiespage.item_height + (cookiespage.chromiumNum + 1) * cookiespage.item_height + cookiespage.spaceValue*4;
                                    }
                                    else {
                                        scrollItem.height = (cookiespage.chromiumNum + 2) * cookiespage.item_height + cookiespage.spaceValue*4;
                                    }
                                }
                                else {
                                    cookiespage.chromium_expanded = false;
                                    if(cookiespage.firefox_expanded == true) {
                                        scrollItem.height = (cookiespage.firefoxNum + 2) * cookiespage.item_height + cookiespage.spaceValue*4;
                                    }
                                    else {
                                        scrollItem.height = 2* cookiespage.item_height + cookiespage.spaceValue*4;
                                    }
                                }
                            }
                        }
                    }
                    cacheBuffer: 1000
                    opacity: 1
//                    spacing: 10
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
}
