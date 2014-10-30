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
    id:browserpage
    width: parent.width; height: 437

    property string title: qsTr("Deep cleaning up the browser cache")//深度清理浏览器缓存
    property string description: qsTr("Deep cleaning up the browser cache, to save disk space")//深度清理浏览器缓存，节省磁盘空间！
    property string btnFlag: "browser_scan"//browser_scan/browser_work
    property bool firefoxresultFlag: false//判断firefox扫描后的实际内容是否为空，为空时为false，有内容时为true
    property bool chromiumresultFlag: false//判断chromium扫描后的实际内容是否为空，为空时为false，有内容时为true
    property int firefoxNum//扫描后得到的firefox的项目总数
    property int chromiumNum//扫描后得到的chromium的项目总数
    property bool splitFlag: true//传递给CacheDelegate.qml,为true时切割字符串，为false时不切割字符串
    property bool flag: false//记录是清理后重新获取数据（true），还是点击开始扫描后获取数据（false）
    property int spaceValue: 20
    property int firefox_arrow_show: 0//传递给CacheDelegate.qml是否显示伸缩图标，为1时显示，为0时隐藏
    property int chromium_arrow_show: 0//传递给CacheDelegate.qml是否显示伸缩图标，为1时显示，为0时隐藏
    property bool firefox_expanded: false//传递给CacheDelegate.qml,觉得伸缩图标是扩展还是收缩
    property bool chromium_expanded: false//传递给CacheDelegate.qml,觉得伸缩图标是扩展还是收缩
    property bool firefox_maincheck: true
    property bool chromium_maincheck: true
    property bool firefox_showNum: false//决定firefox的扫描结果数是否显示
    property bool chromium_showNum: false//决定chromium的扫描结果数是否显示
    property bool firefoxEmpty: false//决定是否显示扫描内容为空的状态图
    property bool chromiumEmpty: false//决定是否显示扫描内容为空的状态图
    property int mode: 0//扫描模式：0表示两者都扫描，1表示只选中了firefox，2表示只选中了chromium

    property int item_height: 30

    ListModel { id: firefoxmainModel }
    ListModel { id: firefoxsubModel }
    ListModel { id: chromiummainModel }
    ListModel { id: chromiumsubModel }

    Connections
    {
        target: sessiondispatcher
        onAppendContentToCacheModel: {
            //QString flag, QString path, QString fileFlag, QString sizeValue
            if(flag == "firefox") {
                firefoxsubModel.append({"itemTitle": path, "desc": fileFlag, "number": sizeValue, "index": browserpage.firefoxNum, "checked": true});
                browserpage.firefoxNum += 1;
            }
            else if(flag == "chromium") {
                chromiumsubModel.append({"itemTitle": path, "desc": fileFlag, "number": sizeValue, "index": browserpage.chromiumNum, "checked": true});
                browserpage.chromiumNum += 1;
            }
        }

        onTellQMLCaheOver: {
            if(flag == "browser") {
                doingImage.visible = false;
                firefoxmainModel.clear();
                chromiummainModel.clear();
                //Firefox缓存清理
                firefoxmainModel.append({"mstatus": browserpage.firefox_maincheck ? "true": "false",
                                 "itemTitle": qsTr("Cleanup Firefox Cache"),
                                 "picture": "../../img/toolWidget/firefox.png"})
                //Chromium缓存清理
                chromiummainModel.append({"mstatus": browserpage.chromium_maincheck ? "true": "false",
                                 "itemTitle": qsTr("Cleanup Chromium Cache"),
                                 "picture": "../../img/toolWidget/chromium.png"})

                if(browserpage.firefoxNum != 0) {
                    browserpage.firefoxresultFlag = true;//扫描的实际有效内容存在
                }
                else {
                    if(browserpage.mode == 0 || browserpage.mode == 1) {
                        browserpage.firefoxEmpty = true;
                    }
                    browserpage.firefoxresultFlag = false;//扫描的实际有效内容不存在
                }
                if(browserpage.chromiumNum != 0) {
                    browserpage.chromiumresultFlag = true;//扫描的实际有效内容存在
                }
                else {
                    if(browserpage.mode == 0 || browserpage.mode == 2) {
                        browserpage.chromiumEmpty = true;
                    }
                    browserpage.chromiumresultFlag = false;//扫描的实际有效内容不存在
                }

                if(browserpage.firefoxresultFlag == false) {
                    browserpage.firefox_showNum = false;
                    browserpage.firefox_expanded = false;//伸缩箭头不扩展
                    browserpage.firefox_arrow_show = 0;//伸缩箭头不显示
                }
                else if(browserpage.firefoxresultFlag == true) {
                    browserpage.firefox_showNum = true;
                    browserpage.firefox_expanded = true;//伸缩箭头扩展
                    browserpage.firefox_arrow_show = 1;//伸缩箭头显示
                }
                if(browserpage.chromiumresultFlag == false) {
                    browserpage.chromium_showNum = false;
                    browserpage.chromium_expanded = false;//伸缩箭头不扩展
                    browserpage.chromium_arrow_show = 0;//伸缩箭头不显示
                }
                else if(browserpage.chromiumresultFlag == true) {
                    browserpage.chromium_showNum = true;
                    browserpage.chromium_expanded = true;//伸缩箭头扩展
                    browserpage.chromium_arrow_show = 1;//伸缩箭头显示
                }

                if(browserpage.firefoxresultFlag == false && browserpage.chromiumresultFlag == false) {
                    browserpage.state = "BrowserWorkEmpty";
                    if(browserpage.flag == false) {//点击扫描时的获取数据，此时显示该对话框
                        //友情提示：      扫描内容为空，无需清理！
                        sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("The scan reslut is empty, nothing has been done!"));
                    }
                    else {//清理firefox后的重新获取数据，此时不需要显示对话框
                        browserpage.flag = false;
                    }
                }
                else {
                    if(browserpage.flag == false) {//点击扫描时的获取数据，此时显示该对话框
                        toolkits.alertMSG(qsTr("Scan completed!"));//扫描完成！
                    }
                    else {//清理chromium后的重新获取数据，此时不需要显示对话框
                        browserpage.flag = false;
                    }
                    browserpage.state = "BrowserWork";
                    actionBtn.text = qsTr("Begin cleanup");//开始清理
                    browserpage.btnFlag = "browser_work";
                    backBtn.visible = true;
                }
                scrollItem.height = (browserpage.firefoxNum + 1) * browserpage.item_height + (browserpage.chromiumNum + 1) * browserpage.item_height + browserpage.spaceValue*4;
                //扫描完成后恢复按钮的使能
                actionBtn.enabled = true;
            }
        }
    }

    Component.onCompleted: {
        //Firefox缓存清理
        firefoxmainModel.append({"mstatus": browserpage.firefox_maincheck ? "true": "false",
                         "itemTitle": qsTr("Cleanup Firefox Cache"),
                         "picture": "../../img/toolWidget/firefox.png"})
        //Chromium缓存清理
        chromiummainModel.append({"mstatus": browserpage.chromium_maincheck ? "true": "false",
                         "itemTitle": qsTr("Cleanup Chromium Cache"),
                         "picture": "../../img/toolWidget/chromium.png"})
    }

    Connections
    {
        target: systemdispatcher
        onFinishCleanWorkError: {//清理出错时收到的信号
            if (btnFlag == "browser_work") {
                if (msg == "browsercache") {
                    doingImage.visible = false;
                    browserpage.state = "BrowserWorkError";
                    //清理过程中发生错误，解禁按钮
                    actionBtn.enabled = true;
                    toolkits.alertMSG(qsTr("Cleanup abnormal!"));//清理出现异常！
                }
            }
        }
        onFinishCleanWork: {//清理成功时收到的信号
            if (browserpage.btnFlag == "browser_work") {
                doingImage.visible = false;
                if (msg == "") {
                    //清理取消，解禁按钮
                    actionBtn.enabled = true;
                    toolkits.alertMSG(qsTr("Cleanup interrupted!"));//清理中断！
                }
                else if (msg == "browsercache") {
                    browserpage.state = "BrowserWorkFinish";
                    toolkits.alertMSG(qsTr("Cleared!"));//清理完毕！
                    //清理完毕后重新获取数据
                    browserpage.flag = true;
                    if(browserpage.firefox_maincheck && browserpage.chromium_maincheck) {
                        firefoxmainModel.clear();
                        chromiummainModel.clear();
                        //Firefox缓存清理
                        firefoxmainModel.append({"mstatus": browserpage.firefox_maincheck ? "true": "false",
                                         "itemTitle": qsTr("Cleanup Firefox Cache"),
                                         "picture": "../../img/toolWidget/firefox.png"})
                        //Chromium缓存清理
                        chromiummainModel.append({"mstatus": browserpage.chromium_maincheck ? "true": "false",
                                         "itemTitle": qsTr("Cleanup Chromium Cache"),
                                         "picture": "../../img/toolWidget/chromium.png"})
                        firefoxsubModel.clear();//内容清空
                        chromiumsubModel.clear();//内容清空
                        browserpage.firefoxNum = 0;//隐藏滑动条
                        browserpage.chromiumNum = 0;//隐藏滑动条
                        browserpage.mode = 0;
                        sessiondispatcher.cache_scan_function_qt(sessiondispatcher.get_browser_cache_arglist(), 'browser');
                    }
                    else {
                        if(browserpage.firefox_maincheck) {
                            firefoxmainModel.clear();
                            //Firefox缓存清理
                            firefoxmainModel.append({"mstatus": browserpage.firefox_maincheck ? "true": "false",
                                             "itemTitle": qsTr("Cleanup Firefox Cache"),
                                             "picture": "../../img/toolWidget/firefox.png"})
                            firefoxsubModel.clear();//内容清空
                            chromiumsubModel.clear();//内容清空
                            browserpage.firefoxNum = 0;//隐藏滑动条
                            browserpage.chromiumNum = 0;//隐藏滑动条
                            browserpage.mode = 1;
                            sessiondispatcher.cache_scan_function_qt("firefox", 'browser');
                        }
                        else if(browserpage.chromium_maincheck) {
                            chromiummainModel.clear();
                            //Chromium缓存清理
                            chromiummainModel.append({"mstatus": browserpage.chromium_maincheck ? "true": "false",
                                             "itemTitle": qsTr("Cleanup Chromium Cache"),
                                             "picture": "../../img/toolWidget/chromium.png"})
                            firefoxsubModel.clear();//内容清空
                            chromiumsubModel.clear();//内容清空
                            browserpage.firefoxNum = 0;//隐藏滑动条
                            browserpage.chromiumNum = 0;//隐藏滑动条
                            browserpage.mode = 2;
                            sessiondispatcher.cache_scan_function_qt("chromium", 'browser');
                        }
                    }
                    //清理成功完成，解禁按钮
                    actionBtn.enabled = true;
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
            id: apt_refreshArrow
            source: "../../img/toolWidget/browser.png"
            Behavior on rotation { NumberAnimation { duration: 200 } }
        }
        Column {
            anchors.verticalCenter: parent.verticalCenter
            spacing: 10
            Text {
                width: 500
                text: browserpage.title
                wrapMode: Text.WordWrap
                font.bold: true
                font.pixelSize: 14
                color: "#383838"
            }
            Text {
                width: 500
                text: browserpage.description
                wrapMode: Text.WordWrap
                font.pixelSize: 12
                color: "#7a7a7a"
            }
        }
    }

    Row{
        anchors { top: parent.top; topMargin: 30;right: parent.right ; rightMargin: 20 }
        spacing: 20
        Row {
            spacing: 20
            anchors.verticalCenter: parent.verticalCenter
            Common.StyleButton {
                id: backBtn
                visible: false
                anchors.verticalCenter: parent.verticalCenter
                wordname: qsTr("Back")//返回
                width: 40
                height: 20
                onClicked: {
                    actionBtn.visible = true;
                    actionBtn.enabled = true;
                    browserpage.firefoxEmpty = false;
                    browserpage.chromiumEmpty = false;
                    if(browserpage.firefox_maincheck == false) {
                        browserpage.firefox_maincheck = true;
                    }
                    if(browserpage.chromium_maincheck == false) {
                        browserpage.chromium_maincheck = true;
                    }
                    browserpage.firefox_showNum = false;
                    browserpage.chromium_showNum = false;
                    firefoxmainModel.clear();
                    chromiummainModel.clear();
                    //Firefox缓存清理
                    firefoxmainModel.append({"mstatus": browserpage.firefox_maincheck ? "true": "false",
                                     "itemTitle": qsTr("Cleanup Firefox Cache"),
                                     "picture": "../../img/toolWidget/firefox.png"})
                    //Chromium缓存清理
                    chromiummainModel.append({"mstatus": browserpage.chromium_maincheck ? "true": "false",
                                     "itemTitle": qsTr("Cleanup Chromium Cache"),
                                     "picture": "../../img/toolWidget/chromium.png"})
                    firefoxsubModel.clear();//内容清空
                    browserpage.firefoxNum = 0;//隐藏滑动条
                    browserpage.firefox_arrow_show = 0;//伸缩图标隐藏
                    chromiumsubModel.clear();//内容清空
                    browserpage.chromiumNum = 0;//隐藏滑动条
                    browserpage.chromium_arrow_show = 0;//伸缩图标隐藏
                    scrollItem.height = 2 * browserpage.item_height + browserpage.spaceValue*4;
                    browserpage.state = "BrowserWorkAGAIN";//按钮的状态恢复初始值
                }
            }
        }
        Common.Button {
            id: actionBtn
            picNormal: "../../img/icons/button16.png"
            picHover: "../../img/icons/button16-hover.png"
            picPressed: "../../img/icons/button16-hover.png"
            fontcolor:"#ffffff"
            fontsize: 16
            width: 120; height: 36
            text: qsTr("Start scanning")//开始扫描
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                //扫描过程中禁用按钮
                actionBtn.enabled = false;
                browserpage.firefoxEmpty = false;
                browserpage.chromiumEmpty = false;

                if (browserpage.btnFlag == "browser_scan") {//扫描
                    browserpage.flag = false;

                    if(browserpage.firefox_maincheck && browserpage.chromium_maincheck) {
                        doingImage.visible = true;
                        browserpage.mode = 0;
                        browserpage.firefoxNum = 0;
                        browserpage.chromiumNum = 0;
                        sessiondispatcher.cache_scan_function_qt(sessiondispatcher.get_browser_cache_arglist(), 'browser');
                    }
                    else {
                        if(browserpage.firefox_maincheck) {
                            doingImage.visible = true;
                            browserpage.mode = 1;
                            browserpage.firefoxNum = 0;
                            sessiondispatcher.cache_scan_function_qt("firefox", 'browser');
                        }
                        else if(browserpage.chromium_maincheck) {
                            doingImage.visible = true;
                            browserpage.mode = 2;
                            browserpage.chromiumNum = 0;
                            sessiondispatcher.cache_scan_function_qt("chromium", 'browser');
                        }
                        else{
                            doingImage.visible = false;
                            actionBtn.enabled = true;
                            //友情提示：        对不起，您没有选择需要扫描的内容，请确认！
                            sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Sorry, You did not choose the content to be scanned, please confirm!"));
                        }
                    }
                }
                else if (browserpage.btnFlag == "browser_work") {//清理
                    if(browserpage.firefoxresultFlag || browserpage.chromiumresultFlag) {//扫描得到的实际内容存在时
                        if(!browserpage.firefox_maincheck && !browserpage.chromium_maincheck) {
                            //友情提示：        对不起，您没有选择需要清理的内容，请确认！
                            sessiondispatcher.showWarningDialog(qsTr("Tips:"), qsTr("Sorry, You did not choose the content to be cleaned up, please confirm!"));
                        }
                        else {
                            var browserlist = new Array();
                            for(var i=0; i<firefoxsubModel.count; i++) {
                                if(firefoxsubModel.get(i).checked) {
                                    browserlist.push(firefoxsubModel.get(i).itemTitle);
                                }
                            }
                            for(var j=0; j<chromiumsubModel.count; j++) {
                                if(chromiumsubModel.get(j).checked) {
                                    browserlist.push(chromiumsubModel.get(j).itemTitle);
                                }
                            }

                            doingImage.visible = true;
                            //开始清理时，禁用按钮，等到清理完成后解禁
                            actionBtn.enabled = false;
                            systemdispatcher.clean_file_cruft_qt(browserlist, "browsercache");
                        }
                    }
                }
            }
        }
        AnimatedImage {
            id: doingImage
            anchors.verticalCenter: parent.verticalCenter
            width: 16
            height: 16
            visible: false
            source: "../../img/icons/move.gif"
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
        height: browserpage.height - titlebar.height - 47
        width: parent.width -2//parent.width - 27 -2
        Item {
            id: scrollItem
            width: parent.width
            height: browserpage.item_height*2 + browserpage.spaceValue*2*2
            Column {
                spacing: browserpage.spaceValue * 2
                //垃圾清理显示内容
                ListView {
                    id: aptListView
                    width: parent.width
                    height: browserpage.firefox_expanded ? (browserpage.firefoxNum + 1) * browserpage.item_height : browserpage.item_height
                    model: firefoxmainModel
                    delegate: CacheDelegate{
                        sub_num: browserpage.firefoxNum//browserpage.aptsubNum//1212
                        sub_model: firefoxsubModel
                        btn_flag: browserpage.btnFlag
                        arrowFlag: "firefoxcache"
                        showNum: browserpage.firefox_showNum
                        arrow_display: browserpage.firefox_arrow_show//为0时隐藏伸缩图标，为1时显示伸缩图标
                        expanded: browserpage.firefox_expanded//firefox_expanded为true时，箭头向下，内容展开;firefox_expanded为false时，箭头向上，内容收缩
                        delegate_flag: browserpage.splitFlag
                        emptyTip: browserpage.firefoxEmpty


                        //test 0410
                        onTransmitCacheItemMainCheckBoxStatus: {
                            if(flag == "firefoxcache") {
                                if(status) {
                                    for(var i=0; i<firefoxsubModel.count; i++) {
                                        firefoxsubModel.setProperty(i, "checked", true);
                                    }
                                }
                                else {
                                    for(var j=0; j<firefoxsubModel.count; j++) {
                                        firefoxsubModel.setProperty(j, "checked", false);
                                    }
                                }
                            }
                        }

                        onTransmitCacheItemCheckBoxStatus: {
                            if(flag == "firefoxcache") {
                                if(status) {
                                    firefoxsubModel.setProperty(index, "checked", true);
                                }
                                else {
                                    firefoxsubModel.setProperty(index, "checked", false);
                                }
                            }
                        }

                        onTellModelToOpenFolder: {
                            if(category == "firefoxcache") {
                                sessiondispatcher.open_folder_qt(path);
                            }
                        }

                        //Cleardelegate中返回是否有项目勾选上，有为true，没有为false
                        onCheckchanged: {
                            browserpage.firefox_maincheck = checkchange;
                        }
                        onArrowClicked: {
                            if(cacheFlag == "firefoxcache") {//1212
                                if(expand_flag == true) {
                                    browserpage.firefox_expanded = true;
                                    if(browserpage.chromium_expanded == true) {
                                        scrollItem.height = (browserpage.firefoxNum + 1) * browserpage.item_height + (browserpage.chromiumNum + 1) * browserpage.item_height + browserpage.spaceValue*4;
                                    }
                                    else {
                                        scrollItem.height = (browserpage.firefoxNum + 2) * browserpage.item_height + browserpage.spaceValue*4;
                                    }
                                }
                                else {
                                    browserpage.firefox_expanded = false;
                                    if(browserpage.chromium_expanded == true) {
                                        scrollItem.height = (browserpage.chromiumNum + 2) * browserpage.item_height + browserpage.spaceValue*4;
                                    }
                                    else {
                                        scrollItem.height = 2* browserpage.item_height + browserpage.spaceValue*4;
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
                    height: browserpage.chromium_expanded ? (browserpage.chromiumNum + 1) * browserpage.item_height : browserpage.item_height
                    model: chromiummainModel
                    delegate: CacheDelegate{
                        sub_num: browserpage.chromiumNum
                        sub_model: chromiumsubModel
                        btn_flag: browserpage.btnFlag
                        showNum: browserpage.chromium_showNum
                        arrowFlag: "chromiumcache"
                        arrow_display: browserpage.chromium_arrow_show//为0时隐藏伸缩图标，为1时显示伸缩图标
                        expanded: browserpage.chromium_expanded//chromium_expanded为true时，箭头向下，内容展开;chromium_expanded为false时，箭头向上，内容收缩
                        delegate_flag: browserpage.splitFlag
                        emptyTip: browserpage.chromiumEmpty

                        onTransmitCacheItemMainCheckBoxStatus: {
                            if(flag == "chromiumcache") {
                                if(status) {
                                    for(var i=0; i<chromiumsubModel.count; i++) {
                                        chromiumsubModel.setProperty(i, "checked", true);
                                    }
                                }
                                else {
                                    for(var j=0; j<chromiumsubModel.count; j++) {
                                        chromiumsubModel.setProperty(j, "checked", false);
                                    }
                                }
                            }
                        }

                        onTransmitCacheItemCheckBoxStatus: {
                            if(flag == "chromiumcache") {
                                if(status) {
                                    chromiumsubModel.setProperty(index, "checked", true);
                                }
                                else {
                                    chromiumsubModel.setProperty(index, "checked", false);
                                }
                            }
                        }

                        onTellModelToOpenFolder: {
                            if(category == "chromiumcache") {
                                sessiondispatcher.open_folder_qt(path);
                            }
                        }
                        //Cleardelegate中返回是否有项目勾选上，有为true，没有为false
                        onCheckchanged: {
                            browserpage.chromium_maincheck = checkchange;
                        }
                        onArrowClicked: {
                            if(cacheFlag == "chromiumcache") {//1212
                                if(expand_flag == true) {
                                    browserpage.chromium_expanded = true;
                                    if(browserpage.firefox_expanded == true) {
                                        scrollItem.height = (browserpage.firefoxNum + 1) * browserpage.item_height + (browserpage.chromiumNum + 1) * browserpage.item_height + browserpage.spaceValue*4;
                                    }
                                    else {
                                        scrollItem.height = (browserpage.chromiumNum + 2) * browserpage.item_height + browserpage.spaceValue*4;
                                    }
                                }
                                else {
                                    browserpage.chromium_expanded = false;
                                    if(browserpage.firefox_expanded == true) {
                                        scrollItem.height = (browserpage.firefoxNum + 2) * browserpage.item_height + browserpage.spaceValue*4;
                                    }
                                    else {
                                        scrollItem.height = 2* browserpage.item_height + browserpage.spaceValue*4;
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
            name: "BrowserWork"
            PropertyChanges { target: actionBtn; text:qsTr("Begin cleanup")}//开始清理
            PropertyChanges { target: browserpage; btnFlag: "browser_work" }
            PropertyChanges { target: backBtn; visible: true}
        },
        State {
            name: "BrowserWorkAGAIN"
            PropertyChanges { target: actionBtn; text:qsTr("Start scanning") }//开始扫描
            PropertyChanges { target: browserpage; btnFlag: "browser_scan" }
            PropertyChanges { target: backBtn; visible: false}
        },
        State {
            name: "BrowserWorkError"
            PropertyChanges { target: actionBtn; text:qsTr("Start scanning") }//开始扫描
            PropertyChanges { target: browserpage; btnFlag: "browser_scan" }
            PropertyChanges { target: backBtn; visible: false}
        },
        State {
            name: "BrowserWorkFinish"
            PropertyChanges { target: actionBtn; text:qsTr("Start scanning") }//开始扫描
            PropertyChanges { target: browserpage; btnFlag: "browser_scan" }
            PropertyChanges { target: backBtn; visible: false}
        },
        State {
            name: "BrowserWorkEmpty"
            PropertyChanges { target: actionBtn; text:qsTr("Start scanning")}//开始扫描
            PropertyChanges { target: browserpage; btnFlag: "browser_scan" }
            PropertyChanges { target: backBtn; visible: false}
        }
    ]
}
